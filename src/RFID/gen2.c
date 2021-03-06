
#include "gen2.h"
#include "as3993.h"
#include <string.h>

/*EPC Commands */
/** Definition for queryrep EPC command */
#define EPC_QUERYREP      0
/** Definition for acknowldege EPC command */
#define EPC_ACK           1
/** Definition for query EPC command */
#define EPC_QUERY         0x08
/** Definition for query adjust EPC command */
#define EPC_QUERYADJUST   0x09
/** Definition for select EPC command */
#define EPC_SELECT        0x0A
/** Definition for not acknowldege EPC command */
#define EPC_NAK           0xC0
/** Definition for request new RN16 or handle */
#define EPC_REQRN         0xC1
/** Definition for read EPC command */
#define EPC_READ          0xC2
/** Definition for write EPC command */
#define EPC_WRITE         0xC3
/** Definition for kill EPC command */
#define EPC_KILL          0xC4
/** Definition for lock EPC command */
#define EPC_LOCK          0xC5
/** Definition for access EPC command */
#define EPC_ACCESS        0xC6
/** Definition for blockwrite EPC command */
#define EPC_BLOCKWRITE    0xC7
/** Definition for blockerase EPC command */
#define EPC_BLOCKERASE    0xC8
/** Definition for block permalock EPC command */
#define EPC_BLOCKPERMALOCK 0xC9

#define GEN2_RESET_TIMEOUT 10

/** Maximum of consecutive select commands currently supported. */
#define MAX_SELECTS             2

/*------------------------------------------------------------------------- */
/* local types */
/*------------------------------------------------------------------------- */

struct gen2InternalConfig{
    struct gen2Config config;
    uint8_t DR; /* Division ratio */
    uint8_t no_resp_time; /* value for AS3993_REG_RXNORESPONSEWAITTIME */
};

/*------------------------------------------------------------------------- */
/*global variables */
/*------------------------------------------------------------------------- */
static uint16_t gen2ResetTimeout = GEN2_RESET_TIMEOUT;

/** Global buffer for generating data, sending to the Tag.\n
  * Caution: In case of a global variable pay attention to the sequence of generating
  * and executing epc commands.
  */
static uint8_t buf_[8+EPCLENGTH+PCLENGTH+CRCLENGTH]; /*8->tx_length+EPCcommand+wordptr+wordcount+handle+broken byte */

static struct gen2InternalConfig gen2IntConfig;

/** Default Gen2 configuration, can be changed callConfigGen2(). */
static struct gen2Config gen2Configuration = {TARI_125, GEN2_LF_256, GEN2_COD_MILLER4, TREXT_OFF, 0, GEN2_SESSION_S0, 0};

/** Start value for Q for Gen2 inventory rounds, can be changed callConfigGen2(). */
uint8_t gen2qbegin = 4;

/** Internal number of currently configured select commands. */
static int num_selects;
/** Parameters for select commands, can be changed via callSelectTag()*/
static struct gen2SelectParams selParams[MAX_SELECTS];

/** Internal variable which contains the number of received tags in the last inventory round. */
static uint8_t num_of_tags;

/** AS3993 init status. This is the return value of as3993Initialize() */
//uint16_t readerInitStatus;

/** Array of Structures which stores all necessary Information about the Tags.
 */
Tag __attribute__((far)) tags_[MAXTAG];

/**Pointer to data of currently selected Tag.*/
Tag *selectedTag;

/**Contains the list of used frequencies.*/
Freq Frequencies;

/*------------------------------------------------------------------------- */
/* local prototypes */
/*------------------------------------------------------------------------- */

static int8_t gen2ReadTID(Tag *tag);

/*------------------------------------------------------------------------- */
/** EPC REQRN command send to the Tag. This function is used to
  * request a new RN16 or a handle from the tag.
  *
  * @param *handle Pointer to the first byte of the handle.
  * @param *dest_handle Pointer to the first byte of the backscattered handle.
  * @return The function returns an errorcode.
                  0x00 means no Error occoured.
                  0xff means Error occoured.
  */
static int8_t gen2ReqRNHandleChar(uint8_t const * handle, uint8_t *dest_handle);

static uint8_t gen2InsertEBV(uint32_t value, uint8_t *p, uint8_t bitpos)
{
    uint8_t ebv[5];
    uint8_t ebvlen;
    u32ToEbv(value, ebv, &ebvlen);
    insertBitStream(p, ebv, ebvlen, bitpos);
    return ebvlen;
}

static void gen2GetAgcRssi(uint8_t *agc, uint8_t *rssi)
{
    uint8_t buf[2];
    as3993ContinuousRead(AS3993_REG_AGCANDSTATUS, 2, buf);
    *agc = buf[0];
    *rssi = buf[1];
}
/*------------------------------------------------------------------------- */
/* global functions */
/*------------------------------------------------------------------------- */

void gen2Select(struct gen2SelectParams *p)
{
    uint16_t len = p->mask_len;
    uint8_t ebvLen;
    uint16_t rxbits = 1;
    uint8_t *mask = p->mask;
    uint8_t j,i;
    uint8_t resp_null;

    as3993ClrResponse();
    memset(buf_,0,sizeof(buf_));

    buf_[0] = ((EPC_SELECT<<4)&0xF0) | ((p->target<<1)&0x0E)   | ((p->action>>2)&0x01);
    buf_[1] = ((p->action<<6)&0xC0)  | ((p->mem_bank<<4)&0x30);
    ebvLen = gen2InsertEBV(p->mask_address, buf_+1, 4);
    buf_[1+ebvLen] = ((p->mask_len>>4)&0x0F);
    buf_[2+ebvLen] = ((p->mask_len<<4)&0xF0);

    i = 2+ebvLen; /* the counter set to last buffer location */
    for (j = len; j >= 8 ; j -= 8, mask++)
    {
        buf_[i] |= 0x0F & (*mask >> 4);
        i++;
        buf_[i] = 0xF0 & (*mask << 4);
    }
    buf_[i] |=  ((p->truncation<<3)&0x08)/*Truncate*/;

    len += 21 + ebvLen * 8; /* Add the bits for EPC command before continuing */

    /* Pseudo 1-bit receival with small timeout to have AS3993 state machine 
       finished and avoiding spurious interrupts (no response) */
    as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRC, buf_, len, &resp_null, &rxbits, 1, 0, 1);

}

static void gen2PrepareQueryCmd(uint8_t *buf, uint8_t q)
{
    buf[0] = ((gen2IntConfig.DR<<5)&0x20)/*DR*/ |
              ((gen2IntConfig.config.miller<<3)&0x18)/*M*/ |
              ((gen2IntConfig.config.trext<<2)&0x04)/*TREXT*/ |
              ((gen2IntConfig.config.sel<<0)&0x03)/*SEL*/;
    buf[1] = ((gen2IntConfig.config.session<<6)&0xC0)/*SESSION*/ |
              ((gen2IntConfig.config.target<<5)&0x20)/*TARGET*/ |
              ((q<<1)&0x1E)/*Q*/;

}

int8_t gen2QueryMeasureRSSI(uint8_t *agc, uint8_t *log_rssis, int8_t *irssi, int8_t *qrssi)
{
    uint16_t rxlen;
    uint8_t rn16[2];
    int8_t ret = 0;
    uint8_t reg;
    uint8_t i = 100;

    reg = as3993SingleRead(AS3993_REG_MEASUREMENTCONTROL);

    /*********************************************************************************/
    /* Send simple query command, make the tag react immediately                     */
    /*********************************************************************************/
    gen2PrepareQueryCmd(buf_, 0);
    rxlen = 16;
    ret = as3993TxRxGen2Bytes(AS3993_CMD_QUERY,buf_,16,NULL,&rxlen,gen2IntConfig.no_resp_time,0,1);

    if (ret)
    {
        return ret;
    }

    while (i--)
    { /* Check rx_status, if 1 receive is in progress/has started */
        if (0x40 & as3993SingleRead(AS3993_REG_FIFOSTATUS)) break;
    }

    gen2GetAgcRssi(agc, log_rssis);
    as3993SingleWrite(AS3993_REG_MEASUREMENTCONTROL, (reg & ~0xf) | 0xb );
    *irssi = as3993GetADC(); /* RSSI I level */
    as3993SingleWrite(AS3993_REG_MEASUREMENTCONTROL, (reg & ~0xf) | 0xc );
    *qrssi = as3993GetADC(); /* RSSI Q level */

    rxlen = 16;
    ret = as3993TxRxGen2Bytes(0,NULL,NULL,rn16,&rxlen,gen2IntConfig.no_resp_time,0,0);

    return ret;
}

/*
 * Sends a Query, QueryRep or QueryAdjust command and checks for replies from tags.
 * If a tag is found, the Ack command is sent. If fast mode is not enabled the Reg_RN
 * command will be sent after receiving the Ack reply.\n
 * All of the data which is retrieved from the tag is written into parameter tag.
 * \param tag The reply data of the tag is written into this data structure
 * \param qCommand The command which should be sent. Should be Query, QueryRep or QueryAdjust
 * \param q Q as specified in the Gen2 spec
 * \param fast If fast mode is activated no Req_RN command will be sent after receiving the
 * Ack reply. If no QueryRep, QueryAdjust or Reg_RN is sent to the tag within T2 the tag will
 * go back to arbitrate state.
 * \param followCommand The command which will be sent after a slot has been processed
 * successfully (valid tag response). Usually this will be used to send a QueryRep
 * immediately after receiving a tag response to trigger a change of the current
 * session flag.
 * \return 1 if one tag has been succesfully read, 0 if no response in slot, -1 if error occured (collision)
 */
static int8_t gen2Slot(Tag *tag, uint8_t qCommand, uint8_t q, uint8_t fast, uint8_t followCommand)
{
    uint16_t rxlen;
    int8_t ret = 0;

    /*********************************************************************************/
    /* 1. Send proper query command */
    /*********************************************************************************/
    rxlen = 16;
    switch (qCommand)
    {
        case AS3993_CMD_QUERY:
            gen2PrepareQueryCmd(buf_, q);
            ret = as3993TxRxGen2Bytes(AS3993_CMD_QUERY,buf_,16,tag->rn16,&rxlen,gen2IntConfig.no_resp_time,AS3993_CMD_ACK,1);
            break;
        case 0: //query rep has already been sent
            ret = as3993TxRxGen2Bytes(0,NULL,0,tag->rn16,&rxlen,gen2IntConfig.no_resp_time,AS3993_CMD_ACK,1);
            break;
        default:
            ret = as3993TxRxGen2Bytes(qCommand,NULL,0,tag->rn16,&rxlen,gen2IntConfig.no_resp_time,AS3993_CMD_ACK,1);
    }
    if (ret == AS3993_ERR_NORES)
    {
        //EPCLOG("  query -> noresp\n");
        return 0;
    }
    if (ret < 0)
    {
        //EPCLOG("  query -> err %hhx\n", ret);
        return -1;
    }

    /*********************************************************************************/
    /* 2. Sent ACK, Receive pc, epc, send REQRN immediately after FIFO has the data  */
    /*********************************************************************************/
    rxlen = sizeof(buf_)*8;  //receive all data, length auto-calculated by AS3993
    ret = as3993TxRxGen2Bytes(0,buf_,0,buf_,&rxlen,gen2IntConfig.no_resp_time,fast?followCommand:AS3993_CMD_REQRN,0);
    tag->pc[0] = buf_[0];
    tag->pc[1] = buf_[1];
    if (ret < 0 || rxlen < 16)
    {
        //EPCLOG("  ack rx rest(pc=%hhx) -> err %hhx\n", tag->pc[0], ret);
        return -1;
    }
    tag->epclen = (rxlen+7)/8-2;
    if(tag->epclen > EPCLENGTH)
        tag->epclen = EPCLENGTH;
    memcpy(tag->epc, buf_+2, tag->epclen);

    if (fast)
    {
        gen2GetAgcRssi(&tag->agc, &tag->rssi);
        if (((tag->pc[0] & 0xF8) >> 2) != tag->epclen)
        {
            return -1;
        }
        return 1;
    }
    /*********************************************************************************/
    /* 3. Receive the two bytes handle */
    /*********************************************************************************/
    rxlen = 32;
    ret = as3993TxRxGen2Bytes(0,NULL,0,tag->handle,&rxlen,gen2IntConfig.no_resp_time,followCommand,0);
    gen2GetAgcRssi(&tag->agc, &tag->rssi);
    if (ret < 0)
    {
        //EPCLOG("  reqrn -> err %hhx\n", ret);
        return -1;
    }
    if (((tag->pc[0] & 0xF8) >> 2) != tag->epclen)
    {
        return -1;
    }
    return 1;
}


/** Same as gen2Slot() but uses autoACK feature of reader.
 */
static int8_t gen2SlotAutoAck(Tag *tag, uint8_t qCommand, uint8_t q, uint8_t fast, uint8_t followCommand)
{
    uint16_t rxlen;
    int8_t ret = 0;

    /*********************************************************************************/
    /* 1. Send proper query command */
    /*********************************************************************************/
    rxlen = sizeof(buf_)*8;  //receive all data, length auto-calculated by AS3993
    switch (qCommand)
    {
        case AS3993_CMD_QUERY:
            gen2PrepareQueryCmd(buf_, q);
            ret = as3993TxRxGen2Bytes(AS3993_CMD_QUERY,buf_,16,buf_,&rxlen,gen2IntConfig.no_resp_time,fast?followCommand:0,0);
            break;
        case 0:
            ret = as3993TxRxGen2Bytes(0,NULL,0,buf_,&rxlen,gen2IntConfig.no_resp_time,fast?followCommand:0,0);
            break;
        default:
            ret = as3993TxRxGen2Bytes(qCommand,NULL,0,buf_,&rxlen,gen2IntConfig.no_resp_time,fast?followCommand:0,0);
    }
    if (ret == AS3993_ERR_NORES)
    {
        //EPCLOG("  query -> noresp\n");
        return 0;
    }

    /*********************************************************************************/
    /* 2. ACK was sent automatically, pc and epc already received */
    /*********************************************************************************/
    tag->pc[0] = buf_[0];
    tag->pc[1] = buf_[1];
    if (ret < 0 || rxlen < 16)
    {
        //EPCLOG("  auto ack rx (pc=%hhx) -> err %hhx\n", tag->pc[0], ret);
        return -1;
    }
    tag->epclen = (rxlen+7)/8-2;
    if(tag->epclen > EPCLENGTH)
        tag->epclen = EPCLENGTH;
    memcpy(tag->epc, buf_+2, tag->epclen);

    if (fast)
    {
        gen2GetAgcRssi(&tag->agc, &tag->rssi);
        if (((tag->pc[0] & 0xF8) >> 2) != tag->epclen)
        {
            return -1;
        }
        return 1;
    }

    /*********************************************************************************/
    /* 4. Receive the two bytes handle */
    /*********************************************************************************/
    rxlen = 32;
    ret = as3993TxRxGen2Bytes(0,NULL,0,tag->handle,&rxlen,gen2IntConfig.no_resp_time,followCommand,0);
    gen2GetAgcRssi(&tag->agc, &tag->rssi);
    if (ret < 0)
    {
        //EPCLOG("  reqrn -> err %hhx\n", ret);
        return -1;
    }

    if (((tag->pc[0] & 0xF8) >> 2) != tag->epclen)
    {
        return -1;
    }
    return 1;
}

/*------------------------------------------------------------------------- */
static int8_t gen2ReqRNHandleChar(uint8_t const * handle, uint8_t *dest_handle)
{
    int8_t ret;
    uint16_t rxbits = 32;

    buf_[0] = EPC_REQRN;                 /*Command REQRN */
    buf_[1] = handle[0];
    buf_[2] = handle[1];

    ret = as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRC,buf_,24,dest_handle,&rxbits,gen2IntConfig.no_resp_time,0,1);

    if (ret < 0) return GEN2_ERR_REQRN;

    return GEN2_OK;
}

/*------------------------------------------------------------------------- */
int8_t gen2AccessTag(Tag const * tag, uint8_t const * password)
{
    int8_t ret;
    int8_t error;
    uint8_t count;
    uint16_t rxcount;
    uint8_t tagResponse[5];
    uint8_t temp_rn16[2];

    for (count = 0; count < 2; count++)
    {
        error = gen2ReqRNHandleChar(tag->handle, temp_rn16);
        if (error)
        {
            return(error);
        }

        buf_[0] = EPC_ACCESS;
        buf_[1] = password[0] ^ temp_rn16[0];
        buf_[2] = password[1] ^ temp_rn16[1];
        buf_[3] = tag->handle[0];
        buf_[4] = tag->handle[1];

        rxcount = 32;
        ret = as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRC,buf_,40,tagResponse,&rxcount,gen2IntConfig.no_resp_time,0,1);
        if (ret < 0)
        {
            //EPCLOG("access failed, tx-ret: %hhx\n", ret);
            return GEN2_ERR_ACCESS;
        }
        password += 2;  /* Increase pointer by two to fetch the next bytes;- */

        if  ((tagResponse[1] != tag->handle[1]) ||
                (tagResponse[0] != tag->handle[0]))
        {
            //EPCLOG("handle not correct\n");
            return GEN2_ERR_ACCESS;
        }

    }
    return ret;
}

/*------------------------------------------------------------------------- */
int8_t gen2LockTag(Tag *tag, const uint8_t *mask_action, uint8_t *tag_reply)
{
    int8_t ret;

    uint16_t rxbits = 32+1;

    *tag_reply = 0xa5;

    buf_[0] = EPC_LOCK;                 /*Command EPC_LOCK */

    buf_[1] = mask_action[0];
    buf_[2] = mask_action[1];

    buf_[3] = ((mask_action[2] ) & 0xF0);
    insertBitStream(&buf_[3], tag->handle, 2, 4);

    ret = as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRCEHEAD, buf_, 44, buf_, &rxbits, 0xff, 0, 1);

    if (ERR_CHIP_HEADER == ret && rxbits) *tag_reply = buf_[0];
    return ret;
}

/*------------------------------------------------------------------------- */
int8_t gen2KillTag(Tag const * tag, uint8_t const * password, uint8_t rfu, uint8_t recom, uint8_t* tag_error)
{
    int8_t error;
    uint8_t count;
    uint8_t temp_rn16[2];
    uint16_t rxbits = 32;
    uint8_t cmd = AS3993_CMD_TRANSMCRC;/* first command has no header Bit */
    uint8_t no_resp_time = gen2IntConfig.no_resp_time;

    *tag_error = 0xa5;
    for (count = 0; count < 2; count++)
    {
        error = gen2ReqRNHandleChar(tag->handle, temp_rn16);
        if (error)
        {
            break;
        }

        if (count==1)
        { /* Values for second part of kill */
            cmd = AS3993_CMD_TRANSMCRCEHEAD; /* expect header bit */
            rxbits = 32 + 1; /* add header bit */
            rfu = recom; /* different data for rfu/recom */
            no_resp_time = 0xff; /* waiting time up to 20ms */
        }

        buf_[0] = EPC_KILL;

        buf_[1] = password[0] ^ temp_rn16[0];
        buf_[2] = password[1] ^ temp_rn16[1];

        buf_[3] = ((rfu << 5) & 0xE0);
        insertBitStream(&buf_[3], tag->handle, 2, 5);

        error = as3993TxRxGen2Bytes(cmd, buf_, 43, buf_, &rxbits, no_resp_time, 0, 1);

        if ( error ) 
        {
            break;
        }
        password += 2;
    }
    if(ERR_CHIP_HEADER == error && rxbits) *tag_error = buf_[0];
    return error;
}

/*------------------------------------------------------------------------- */
int8_t gen2WriteWordToTag(Tag const * tag, uint8_t memBank, uint32_t wordPtr,
                                  uint8_t const * databuf, uint8_t * tag_error)
{
    int8_t error;
    uint8_t datab;
    int8_t ret;
    uint8_t ebvlen;
    uint8_t temp_rn16[2];
    uint16_t rxbits = 32+1;
    *tag_error = 0xa5;

    error = gen2ReqRNHandleChar(tag->handle, temp_rn16);
    //EPCLOG("wDtT %hx%hx->%hhx%hhx\n",wordPtr,databuf[0],databuf[1]);
    if (error)
    {
        //EPCLOG("reqrn error\n");
        return(error);
    }

    buf_[0]  = EPC_WRITE;                 /*Command EPC_WRITE */

    buf_[1]  = (memBank << 6) & 0xC0;
    ebvlen = gen2InsertEBV(wordPtr, &buf_[1], 6);

    datab = databuf[0] ^ temp_rn16[0];
    buf_[1+ebvlen] |= ((datab >> 2) & 0x3F);
    buf_[2+ebvlen]  = (datab << 6) & 0xC0;

    datab = databuf[1] ^ temp_rn16[1];
    buf_[2+ebvlen] |= ((datab >> 2) & 0x3F);
    buf_[3+ebvlen]  = (datab << 6) & 0xC0;

    insertBitStream(&buf_[3+ebvlen], tag->handle, 2, 6);

    ret = as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRCEHEAD, buf_, 42+8*ebvlen, buf_, &rxbits, 0xff, 0, 1);

    if (ERR_CHIP_HEADER == ret && rxbits) *tag_error = buf_[0];
    //EPCLOG("  smo %hhx\n",ret);
    //EPCLOG("  handle %hhx %hhx\n",tag->handle[0],tag->handle[1]);
    //EPCLOG("  buf_ %hhx %hhx\n",buf_[0],buf_[1]);
    //EPCLOG("  rxbits = %hx\n",rxbits);
    return ret;
}

/*------------------------------------------------------------------------- */
int8_t gen2ReadFromTag(Tag *tag, uint8_t memBank, uint32_t wordPtr,
                          uint8_t wordCount, uint8_t *destbuf)
{
    uint16_t bit_count = (wordCount * 2 + 4) * 8 + 1; /* + 2 bytes rn16 + 2bytes crc + 1 header bit */
    int8_t ret;
    uint8_t ebvlen;

    buf_[0]  = EPC_READ;                 /*Command EPC_READ */
    buf_[1]  = (memBank << 6) & 0xC0;
    ebvlen = gen2InsertEBV(wordPtr, &buf_[1], 6);
    buf_[1+ebvlen] |= ((wordCount >> 2) & 0x3F);
    buf_[2+ebvlen]  = (wordCount << 6) & 0xC0;
    insertBitStream(&buf_[2+ebvlen], tag->handle, 2, 6);

    ret = as3993TxRxGen2Bytes(AS3993_CMD_TRANSMCRCEHEAD, buf_, 34+8*ebvlen, destbuf, &bit_count, gen2IntConfig.no_resp_time, 0, 1);
    
    return ret;
}

void gen2PrintGen2Settings()
{
    uint8_t buf[9];
    as3993ContinuousRead(AS3993_REG_PROTOCOLCTRL, 9, buf);
}

unsigned gen2SearchForTags(Tag *tags_
                      , uint8_t maxtags
                      , uint8_t q
                      , uint8_t (*cbContinueScanning)(void)
                      , uint8_t singulate
                      , uint8_t toggleSession
                      )
{
    uint16_t num_of_tags = 0;
    uint16_t collisions = 0;
    uint16_t slot_count;
    uint8_t i = 0;
    uint8_t addRounds = 1; /* the maximal number of rounds performed */
    uint8_t cmd = AS3993_CMD_QUERY;
    uint8_t followCmd = 0;
    
    as3993AntennaPower(1);
    as3993ContinuousRead(AS3993_REG_IRQSTATUS1, 2, &buf_[0]);    // ensure that IRQ bits are reset
    as3993ClrResponse();

    for (i=0; i < maxtags; i++)   /*Reseting the TAGLIST */
    {
        tags_[i].rn16[0] = 0;
        tags_[i].rn16[1] = 0;
        tags_[i].epclen=0;
    }
    do
    {
        uint8_t goOn;
        collisions = 0;
        slot_count = 1UL<<q;   /*get the maximum slot_count */
        do
        {
            if (num_of_tags >= maxtags)
            {/*    ERROR it is not possible to store more than maxtags Tags */
                break;
            }
            //EPCLOG("next slot, command: %x\n", cmd);
            slot_count--;
            switch (gen2Slot(tags_+num_of_tags, cmd, q, !singulate, followCmd))
            {
                case -1:
                    //EPCLOG("collision\n");
                    collisions++;
                    cmd = AS3993_CMD_QUERYREP;
                    break;
                case 1:
                    num_of_tags++;
                    
                    if (followCmd)
                        cmd = 0;    // query_rep has already been sent as followCmd
                    else
                        cmd = AS3993_CMD_QUERYREP;
                    break;
                case 0:
                    //EPCLOG("NO EPC response -> empty Slot\n");
                    cmd = AS3993_CMD_QUERYREP;
                    break;
                default:
                    break;
            }
            goOn = 1;// cbContinueScanning(); // timeout check routine
        } while (slot_count && goOn );
        addRounds--;
        //EPCLOG("q=%hhx, collisions=%x, num_of_tags=%x",q,collisions,num_of_tags);
        if( collisions )
            if( collisions >= (1UL<<q) /4)
            {
                q++;
                //EPCLOG("->++\n");
                cmd = AS3993_CMD_QUERYADJUSTUP;
            }
            else if( collisions < (1UL<<q) /8)
            {
                q--;
                //EPCLOG("->--\n");
                cmd = AS3993_CMD_QUERYADJUSTDOWN;
            }
            else
            {
                //EPCLOG("->==\n");
                cmd = AS3993_CMD_QUERYADJUSTNIC;
            }
        else
        {
            //EPCLOG("->!!\n");
            addRounds = 0;
        }
    }while(num_of_tags < maxtags && addRounds && cbContinueScanning() );

    if (num_of_tags == 0)
    {
        gen2ResetTimeout--;
        if (gen2ResetTimeout == 0)
        {
            as3993AntennaPower(0);      /* we do not want that rf power is turned on after reset */
            as3993Reset();
            gen2ResetTimeout = GEN2_RESET_TIMEOUT;
        }
    }
    else
    {
        gen2ResetTimeout = GEN2_RESET_TIMEOUT;
    }
    return num_of_tags;
}

unsigned gen2SearchForTagsAutoAck(Tag *tags_
                      , uint8_t maxtags
                      , uint8_t q
                      , uint8_t (*cbContinueScanning)(void)
                      , uint8_t singulate
                      , uint8_t toggleSession
                      )
{
    uint16_t num_of_tags = 0;
    uint16_t collisions = 0;
    uint16_t slot_count;
    uint8_t i = 0;
    uint8_t cmd = AS3993_CMD_QUERY;
    uint8_t followCmd = 0;
    uint8_t autoAck;
    uint8_t goOn = 1;
        
    as3993AntennaPower(1);
    as3993ContinuousRead(AS3993_REG_IRQSTATUS1, 2, &buf_[0]);    // ensure that IRQ bits are reset
    as3993ClrResponse();

    //configure autoACK mode
    autoAck = as3993SingleRead(AS3993_REG_PROTOCOLCTRL);
    autoAck &= ~0x30;
    if (singulate)
        autoAck |= 0x20;
    else
        autoAck |= 0x10;
    as3993SingleWrite(AS3993_REG_PROTOCOLCTRL, autoAck);

    for (i=0; i < maxtags; i++)   /*Reseting the TAGLIST */
    {
        tags_[i].rn16[0] = 0;
        tags_[i].rn16[1] = 0;
        tags_[i].epclen=0;
    }

    slot_count = 1UL<<q;   /*get the maximum slot_count */
    do
    {
        if (num_of_tags >= maxtags)
        {/*    ERROR it is not possible to store more than maxtags Tags */
            break;
        }
        slot_count--;
        switch (gen2SlotAutoAck(tags_+num_of_tags, cmd, q, !singulate, followCmd))
        {
            case -1:
                //EPCLOG("collision\n");
                collisions++;
                cmd = AS3993_CMD_QUERYREP;
                break;
            case 1:
                    num_of_tags++;
                    
                    if (followCmd)
                    {
                        cmd = 0;
                    }
                    else
                    {
                        cmd = AS3993_CMD_QUERYREP;
                        if( gen2ReadTID(tags_+(num_of_tags-1)) != ERR_NONE )
                        {
                            cmd = cmd; // breakpoint here
                        }
                    }
                    break;
            case 0:
                //EPCLOG("NO EPC response -> empty Slot\n");
                cmd = AS3993_CMD_QUERYREP;
                break;
            default:
                break;
        }
        goOn = cbContinueScanning();
    } while (slot_count && goOn );

    //unset autoACK mode again
    autoAck = as3993SingleRead(AS3993_REG_PROTOCOLCTRL);
    autoAck &= ~0x30;
    as3993SingleWrite(AS3993_REG_PROTOCOLCTRL, autoAck);

    if (num_of_tags == 0)
    {
        gen2ResetTimeout--;
        if (gen2ResetTimeout == 0)
        {           
            //as3993AntennaPower(0); //FWEMP_1303_V01R03.hex     /* we do not want that rf power is turned on after reset */
            //as3993Reset();         //FWEMP_1303_V01R02.hex
            gen2ResetTimeout = GEN2_RESET_TIMEOUT;
        }
    }
    else
    {
        gen2ResetTimeout = GEN2_RESET_TIMEOUT;
    }
    return num_of_tags;
}

void gen2Configure(const struct gen2Config *config)
{
    /* depending on link frequency setting adjust */
    /* registers 01, 02, 03, 04, 05, 06, 07, 08 and 09 */
    uint8_t reg[9];
    uint8_t session = config->session;
    gen2IntConfig.DR = 1;
    gen2IntConfig.config = *config;
    if (session > GEN2_IINV_S3)
        session = GEN2_IINV_S0; /* limit SL and invalid settings */
    if (gen2IntConfig.config.miller == GEN2_COD_FM0 || gen2IntConfig.config.miller == GEN2_COD_MILLER2)
        gen2IntConfig.config.trext = TREXT_ON;

    switch (config->linkFreq) {
    case GEN2_LF_640:  /* 640kHz */
        reg[0] = 0x20; /* AS3993_REG_TXOPTIONS            */
        reg[1] = 0xF0; /* AS3993_REG_RXOPTIONS            */
        reg[2] = 0x01; /* AS3993_REG_TRCALHIGH            */
        reg[3] = 0x4D; /* AS3993_REG_TRCALLOW             */
        reg[4] = 0x03; /* AS3993_REG_AUTOACKTIMER         */
        reg[5] = 0x02; /* AS3993_REG_RXNORESPONSEWAITTIME */
        reg[6] = 0x01; /* AS3993_REG_RXWAITTIME           */
        if (gen2IntConfig.config.miller > GEN2_COD_MILLER2)
            reg[7] = 0x04; /* AS3993_REG_RXFILTER         */
        else
            reg[7] = 0x07; /* AS3993_REG_RXFILTER         */
        break;
    case GEN2_LF_320: /* 320kHz */
        reg[0] = 0x20;
        reg[1] = 0xC0;
        if (gen2IntConfig.config.tari == TARI_625)    /* if Tari = 6.25us */
        {   /* TRcal = 25us */
            gen2IntConfig.DR = 0;
            reg[2] = 0x00;
            reg[3] = 0xFA;
        } else
        {   /* TRcal = 66.7us */
            reg[2] = 0x02;
            reg[3] = 0x9B;
        }
        reg[4] = 0x04;
        reg[5] = 0x03;
        reg[6] = 0x02;
        if (gen2IntConfig.config.miller > GEN2_COD_MILLER2)
            reg[7] = 0x24; /* AS3993_REG_RXFILTER         */
        else
            reg[7] = 0x27; /* AS3993_REG_RXFILTER         */
        break;
    case GEN2_LF_256: /* 256kHz */
        reg[0] = 0x20;
        reg[1] = 0x90;
        if (gen2IntConfig.config.tari == TARI_625)    /* Tari = 6.25us */
        {   /* TRcal = 31.3us */
            gen2IntConfig.DR = 0;
            reg[2] = 0x01;
            reg[3] = 0x39;
        }
        else                                /* Tari = 25us or 12.5us */
        {   /* TRcal = 83.3us */
            reg[2] = 0x03;
            reg[3] = 0x41;
        }
        reg[4] = 0x05;
        reg[5] = 0x05;
        reg[6] = 0x04;
        if (gen2IntConfig.config.miller > GEN2_COD_MILLER2)
            reg[7] = 0x34; /* AS3993_REG_RXFILTER         */
        else
            reg[7] = 0x37; /* AS3993_REG_RXFILTER         */
        break;
    case GEN2_LF_213: /* 213.3kHz */
        reg[0] = 0x20;
        reg[1] = 0x80;
        if (gen2IntConfig.config.tari == TARI_625)    /* Tari = 6.25us */
        {   /* TRcal = 37.5us */
            gen2IntConfig.DR = 0;
            reg[2] = 0x01;
            reg[3] = 0x77;
        }
        else
        {   /* TRcal = 100us */
            reg[2] = 0x03;
            reg[3] = 0xE8;
        }
        reg[4] = 0x06;
        reg[5] = 0x05;
        reg[6] = 0x05;
        if (gen2IntConfig.config.miller > GEN2_COD_MILLER2)
            reg[7] = 0x34; /* AS3993_REG_RXFILTER         */
        else
            reg[7] = 0x37; /* AS3993_REG_RXFILTER         */
        break;
    case GEN2_LF_160: /* 160kHz */
        reg[0] = 0x20;
        reg[1] = 0x60;
        if (gen2IntConfig.config.tari == TARI_125)    /* Tari = 12.5us */
        {   /* TRcal = 50us */
            gen2IntConfig.DR = 0;
            reg[2] = 0x01;
            reg[3] = 0xF4;
        }
        else
        {   /* TRcal = 1333.3us */
            reg[2] = 0x05;
            reg[3] = 0x35;
        }
        reg[4] = 0x08;
        reg[5] = 0x05;
        reg[6] = 0x08;
        if (gen2IntConfig.config.miller > GEN2_COD_FM0)
            reg[7] = 0x3F; /* AS3993_REG_RXFILTER         */
        else
            reg[7] = 0xBF; /* AS3993_REG_RXFILTER         */
        break;
    case GEN2_LF_40: /* 40kHz */
        reg[0] = 0x30; /* AS3993_REG_TXOPTIONS            */
        reg[1] = 0x00; /* AS3993_REG_RXOPTIONS            */
        reg[2] = 0x07; /* AS3993_REG_TRCALHIGH            */
        reg[3] = 0xD0; /* AS3993_REG_TRCALLOW             */
        reg[4] = 0x20; /* AS3993_REG_AUTOACKTIMER         */
        reg[5] = 0x0C; /* AS3993_REG_RXNORESPONSEWAITTIME */
        reg[6] = 0x24; /* AS3993_REG_RXWAITTIME           */
        reg[7] = 0xFF; /* AS3993_REG_RXFILTER         */
        gen2IntConfig.DR = 0;
        break;
    default:
        return; /* use preset settings */
    }
    reg[0] |= gen2IntConfig.config.tari;
    reg[1] = (reg[1] & ~0x0F)
        | gen2IntConfig.config.miller
        | (gen2IntConfig.config.trext<<3);

    gen2IntConfig.no_resp_time = reg[5];
    /* Modify only the gen2 relevant settings */
    as3993ContinuousWrite(AS3993_REG_TXOPTIONS, reg+0, 8);

    reg[0] = as3993SingleRead(AS3993_REG_TXSETTING);
    reg[0] = (reg[0] & ~0x03) | gen2IntConfig.config.session;
    as3993SingleWrite(AS3993_REG_TXSETTING, reg[0]);
    reg[0] = as3993SingleRead(AS3993_REG_PROTOCOLCTRL);
    reg[0] = reg[0] & ~0x07;
    as3993SingleWrite(AS3993_REG_PROTOCOLCTRL, reg[0]);
}

void gen2Open(const struct gen2Config * config)
{
    gen2Configure( config );
}

void gen2Close(void)
{
}

/**
 * Converts u32 number into EBV format. The EBV is stored in parameter ebv.
 * Parameter len will be set to the length of data in ebv.
 * @param value u32 value to convert into EBV
 * @param ebv array to store the EBV
 * @param len number of data in ebv
 */
void u32ToEbv(uint32_t value, uint8_t *ebv, uint8_t *len)
{
    uint8_t lsbytefirst[6];  //additional byte for setting extension bit in loop
    uint8_t *buf = &lsbytefirst[0];
    int i;
    
    *len = 0;
    *buf = 0;
    do
    {
        (*buf) |= (uint8_t)(value & 0x7F);
        value = value >> 7;
        buf++;
        (*len)++;
        *buf = 0x80;   //set extension bit in next block
    }
    while (value > 0);
    //the EBV in buf starts with LSByte -> reorder the content into ebv array
    for (i=0; i<(*len); i++)
    {
        buf--;
        ebv[i] = *buf;
    }
}

/** This funcition checks the current session, if necessary closes it
and opens a new session. Valid session values are: #SESSION_GEN2 and #SESSION_ISO6B. */
void checkAndSetSession( uint8_t newSession)
{
    if (currentSession == newSession) return;
    switch (currentSession)
    {
        case SESSION_GEN2:
            gen2Close();
            break;
    }
    switch (newSession)
    {
        case SESSION_GEN2:
            gen2Open(&gen2Configuration);
            break;
    }
    currentSession = newSession;
}

void insertBitStream(uint8_t *dest, uint8_t const *source, uint8_t len, uint8_t bitpos)
{
    int16_t i;
    uint8_t mask0 = (1<<bitpos)-1;
    uint8_t mask1 = (1<<(8-bitpos))-1;

    for (i=0; i<len; i++)
    {
        dest[i+0] &= (~mask0);
        dest[i+0] |= ((source[i]>>(8-bitpos)) & mask0);
        dest[i+1] &= ((~mask1) << bitpos);
        dest[i+1] |= ((source[i] & mask1) << bitpos);
    }
}

static uint8_t continueCheckTimeout( ) 
{
        
    return 1;
}

void performSelects()
{
    int i;
    for (i = 0; i<num_selects; i++)
    {
        gen2Select(selParams + i);
        /* We would have to wait T4=2*RTcal here (max 140us). Logic analyzer showed enough time without delaying */
    }
}

uint8_t inventoryGen2(void)
{
    int8_t result;

    powerUpReader();
    as3993AntennaPower(1);
    RFID_AS3993_delay_ms(1);
    
    result = 0;// hopFrequencies();
    
    if( !result )
    {
        checkAndSetSession(SESSION_GEN2);
        as3993SingleWrite(AS3993_REG_STATUSPAGE, rssiMode);
        if (rssiMode == RSSI_MODE_PEAK)      //if we use peak rssi mode, we have to send anti collision commands
            as3993SingleCommand(AS3993_CMD_ANTI_COLL_ON);

        num_of_tags = 0;
        //total_tags = 0;
        performSelects();
        if( !autoAckMode )
            num_of_tags = gen2SearchForTags(tags_, MAXTAG, gen2qbegin, continueCheckTimeout, fastInventory?0:1, 1);
        else
            num_of_tags = gen2SearchForTagsAutoAck(tags_, MAXTAG, gen2qbegin, continueCheckTimeout, fastInventory?0:1, 1);
        //total_tags = num_of_tags;
        if (rssiMode == RSSI_MODE_PEAK)      //if we use peak rssi mode, we have to send anti collision commands
            as3993SingleCommand(AS3993_CMD_ANTI_COLL_OFF);
    }
    inventoryResult = result;
    
    as3993AntennaPower(0);
    powerDownReader();    

    //APPLOG("end inventory, found tags: %hhx\n", num_of_tags);
    return num_of_tags;
}

static void tidSerialNumberFormula(Tag *tag){ 
    
    tag->tid.serialNumberFormulated[0]  = tag->tid.memBankRawData[0];
    tag->tid.serialNumberFormulated[1]  = tag->tid.memBankRawData[1];
    tag->tid.serialNumberFormulated[2]  = tag->tid.memBankRawData[2];
    tag->tid.serialNumberFormulated[3]  = tag->tid.memBankRawData[3];
    
    tag->tid.serialNumberFormulated[4]  = ( ( tag->tid.memBankRawData[6]  & 0xE0 )      ) |
                                          ( ( tag->tid.memBankRawData[10] & 0xE0 ) >> 4 );
    
    tag->tid.serialNumberFormulated[5]  = 0x00;
    
    tag->tid.serialNumberFormulated[6]  = ( ( tag->tid.memBankRawData[10] & 0x18 ) >> 2 );
    
    tag->tid.serialNumberFormulated[7]  = ( ( tag->tid.memBankRawData[6]  & 0x08 ) << 3 ) |
                                          ( ( tag->tid.memBankRawData[10] & 0x07 ) << 3 ) |
                                          ( ( tag->tid.memBankRawData[11] & 0xE0 ) >> 5 );
    
    tag->tid.serialNumberFormulated[8]  = ( ( tag->tid.memBankRawData[11] & 0x1F ) << 3 ) |
                                          ( ( tag->tid.memBankRawData[8]  & 0xE0 ) >> 5 );
    
    tag->tid.serialNumberFormulated[9]  = ( ( tag->tid.memBankRawData[8]  & 0x1F ) << 3 ) |
                                          ( ( tag->tid.memBankRawData[9]  & 0xE0 ) >> 5 );
    
    tag->tid.serialNumberFormulated[10] = ( ( tag->tid.memBankRawData[9]  & 0x1F ) << 3 ) |
                                          ( ( tag->tid.memBankRawData[6]  & 0x07 )      );
    
    tag->tid.serialNumberFormulated[11] = tag->tid.memBankRawData[7];
    
    tag->tid.serial_number_formulated  = (uint64_t)tag->tid.serialNumberFormulated[6]  << 40;
    tag->tid.serial_number_formulated |= (uint64_t)tag->tid.serialNumberFormulated[7]  << 32;
    tag->tid.serial_number_formulated |= (uint64_t)tag->tid.serialNumberFormulated[8]  << 24;
    tag->tid.serial_number_formulated |= (uint64_t)tag->tid.serialNumberFormulated[9]  << 16;
    tag->tid.serial_number_formulated |= (uint64_t)tag->tid.serialNumberFormulated[10] << 8;
    tag->tid.serial_number_formulated |= tag->tid.serialNumberFormulated[11];
    
}

static int8_t gen2ReadTID(Tag *tag)
{
    // Every time we read, last word came with random values, so we read additional word
    // and ignore it when copying to tags_    
    uint8_t nbWords = (TID_LENGTH) / 2; // 12/2 = 6 + position 0 = 7 words
    //uint8_t tidlen = 0;
    uint8_t tmpBuf[TID_LENGTH+2]; // 12 + 2 dummy bytes (word)
    //uint8_t len = 0;
    int8_t ret = 0;
    uint8_t copyData = 0;
    
    memset(tmpBuf,0,sizeof(tmpBuf));

    ret = gen2ReadFromTag(tag, MEM_TID, 0, nbWords, tmpBuf); // Read all 7 words from Tid memory bank

    if (ret == ERR_NONE) 
    {
        copyData = 1;      
    } 
    else 
    {
        if (ret == ERR_NOMEM) 
        {
            // Reached last TID byte
            ret = ERR_NONE;         // Not an error 
            copyData = 1;
        } 
        else 
        {
            ret = ERR_CHIP_NORESP;
        }
        
        copyData = 0;
    }
    
    if (copyData)
    {
        memcpy(tag->tid.memBankRawData, tmpBuf, TID_LENGTH);  // If no errors, copy only 6 words (12 bytes) to tags_
        
        tag->tid.class_id                 = tag->tid.memBankRawData[0];
        
//        tag->tid.xtid_bit                 = tag->tid.memBankRawData[1] & 0x01; 
//        tag->tid.security_bit             = tag->tid.memBankRawData[1] & 0x02;
//        tag->tid.file_bit                 = tag->tid.memBankRawData[1] & 0x04;
        
        tag->tid.xtid_bit                 = tag->tid.memBankRawData[1] & 0x80 ? 1:0; 
        tag->tid.security_bit             = tag->tid.memBankRawData[1] & 0x40 ? 1:0;
        tag->tid.file_bit                 = tag->tid.memBankRawData[1] & 0x20 ? 1:0;
        
        tag->tid.mask_designer_identifier = ( (uint16_t)( tag->tid.memBankRawData[1] & 0x1F ) << 4 | (uint16_t)( tag->tid.memBankRawData[2] & 0xF0 ) >> 4 ) ;
        
        tag->tid.tag_model_number      = (uint16_t)( tag->tid.memBankRawData[2] & 0x0F ) << 8 | (uint16_t)tag->tid.memBankRawData[3]; 
        
        tag->tid.xtid_header           = (uint16_t)tag->tid.memBankRawData[4] << 8 | tag->tid.memBankRawData[5];
        
        tag->tid.raw_serial_number_segment = (uint64_t)tag->tid.memBankRawData[6]  << 40;
        tag->tid.raw_serial_number_segment |= (uint64_t)tag->tid.memBankRawData[7]  << 32;
        tag->tid.raw_serial_number_segment |= (uint64_t)tag->tid.memBankRawData[8]  << 24;
        tag->tid.raw_serial_number_segment |= (uint64_t)tag->tid.memBankRawData[9]  << 16;
        tag->tid.raw_serial_number_segment |= (uint64_t)tag->tid.memBankRawData[10] << 8;
        tag->tid.raw_serial_number_segment |= tag->tid.memBankRawData[11];
        
        tidSerialNumberFormula(tag);
        
        tag->tid.data_available_flag = 1;
    }
    else
    {
        // If error, clean all registers
        
        memset(tag->tid.memBankRawData,0,TID_LENGTH);
        
        memset(&tag->tid.class_id,0,sizeof(tag->tid.class_id));
        memset(&tag->tid.xtid_bit,0,sizeof(tag->tid.xtid_bit));
        memset(&tag->tid.security_bit,0,sizeof(tag->tid.security_bit));
        memset(&tag->tid.file_bit,0,sizeof(tag->tid.file_bit));
        memset(&tag->tid.mask_designer_identifier,0,sizeof(tag->tid.mask_designer_identifier));
        memset(&tag->tid.tag_model_number,0,sizeof(tag->tid.tag_model_number));

        memset(&tag->tid.xtid_header,0,sizeof(tag->tid.xtid_header));

        memset(&tag->tid.raw_serial_number_segment,0,sizeof(tag->tid.raw_serial_number_segment));
        tag->tid.data_available_flag = 0;
    }

    return ret;
}

