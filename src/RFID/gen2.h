
#ifndef __GEN2_H__
#define __GEN2_H__

#include <stdint.h>
#include "as3993.h"

/* Protocol configuration settings */
#define GEN2_LF_40  0   /*!<link frequency 40 kHz*/
#define GEN2_LF_160 6   /*!<link frequency 160 kHz*/
#define GEN2_LF_213 8   /*!<link frequency 213 kHz*/
#define GEN2_LF_256 9   /*!<link frequency 213 kHz*/
#define GEN2_LF_320 12  /*!<link frequency 213 kHz*/
#define GEN2_LF_640 15  /*!<link frequency 640 kHz*/

/** Rx coding values */
#define GEN2_COD_FM0      0 /*!<FM coding for rx */
#define GEN2_COD_MILLER2  1 /*!<MILLER2 coding for rx*/
#define GEN2_COD_MILLER4  2 /*!<MILLER4 coding for rx*/
#define GEN2_COD_MILLER8  3 /*!<MILLER8 coding for rx*/

/* TrExt defines */
#define TREXT_OFF         0 /**< use short preamble */
#define TREXT_ON          1 /**< use long preamble */

/* Tari defines */
#define TARI_625          0 /**< set tari to 6.25us */
#define TARI_125          1 /**< set tari to 12.5us */
#define TARI_25           2 /**< set tari to 25us */

/*EPC Mem Banks */
/** Definition for EPC tag memory bank: reserved */
#define MEM_RES           0x00
/** Definition for EPC tag memory bank: EPC memory */
#define MEM_EPC           0x01
/** Definition for EPC tag memory bank: TID */
#define MEM_TID           0x02
/** Definition for EPC tag memory bank: user */
#define MEM_USER          0x03

/*EPC Wordpointer Addresses */
/** Definition for EPC wordpointer: Address for CRC value */
#define MEMADR_CRC        0x00
/** Definition for EPC wordpointer: Address for PC value Word position*/
#define MEMADR_PC         0x01
/** Definition for EPC wordpointer: Address for EPC value */
#define MEMADR_EPC        0x02

/** Definition for EPC wordpointer: Address for kill password value */
#define MEMADR_KILLPWD    0x00
/** Definition for EPC wordpointer: Address for access password value */
#define MEMADR_ACCESSPWD  0x02

/** Definition for EPC wordpointer: Address for TID value */
#define MEMADR_TID        0x00

/*EPC SELECT TARGET */
/** Definition for inventory: Inventoried (S0) */
#define GEN2_IINV_S0           0x00 /*Inventoried (S0) */
/** Definition for inventory: 001: Inventoried (S1) */
#define GEN2_IINV_S1           0x01 /*001: Inventoried (S1) */
/** Definition for inventory: 010: Inventoried (S2) */
#define GEN2_IINV_S2           0x02 /*010: Inventoried (S2) */
/** Definition for inventory: 011: Inventoried (S3) */
#define GEN2_IINV_S3           0x03 /*011: Inventoried (S3) */
/** Definition for inventory: 100: SL */
#define GEN2_IINV_SL           0x04 /*100: SL */

#define GEN2_SESSION_S0           0x00
#define GEN2_SESSION_S1           0x01
#define GEN2_SESSION_S2           0x02
#define GEN2_SESSION_S3           0x03

/** Defines for various return codes */
#define GEN2_OK                  ERR_NONE /**< No error */
#define GEN2_ERR_REQRN           ERR_GEN2_REQRN /**< Error sending ReqRN */
#define GEN2_ERR_ACCESS          ERR_GEN2_ACCESS /**< Error sending Access password */
#define GEN2_ERR_SELECT          ERR_GEN2_SELECT /**< Error when selecting tag*/
#define GEN2_ERR_CHANNEL_TIMEOUT ERR_GEN2_CHANNEL_TIMEOUT /**< Error RF channel timed out*/

/** Identifier for gen2 protocol session */
#define SESSION_GEN2            1

/** Definition for the maximal EPC length */
#define EPCLENGTH              12 //32  // number of bytes for EPC, standard allows up to 62 bytes
/** Definition for the PC length */
#define PCLENGTH                2
/** Definition for the CRC length */
#define CRCLENGTH               2

#define TID_LENGTH 12

struct gen2Config{
    uint8_t tari;        /*< Tari setting */
    uint8_t linkFreq;    /*< GEN2_LF_40, ... */
    uint8_t miller;      /*< GEN2_COD_FM0, ... */
    uint8_t trext;       /*< 1 if the preamble is long, i.e. with pilot tone */
    uint8_t sel;         /*< For QUERY Sel field */
    uint8_t session;     /*< GEN2_SESSION_S0, ... */
    uint8_t target;      /*< For QUERY Target field */
};

struct gen2SelectParams{
    uint8_t target;
    uint8_t action;
    uint8_t mem_bank;
    uint8_t mask[32];
    uint32_t mask_address;
    uint8_t mask_len;
    uint8_t truncation;
};

/** @struct TagInfo_
  * This struct stores the whole information of one tag.
  *
  */
//typedef uint8_tx unsigned char __attribute__((far));

 //struct __attribute__((far)) TagInfo_

typedef struct
{   
    uint8_t memBankRawData[TID_LENGTH];  
    uint8_t serialNumberFormulated[TID_LENGTH];
    
    uint8_t class_id;
    uint8_t xtid_bit;
    uint8_t security_bit;
    uint8_t file_bit;
    uint16_t mask_designer_identifier;
    uint16_t tag_model_number;
    
    uint16_t xtid_header;
    uint64_t raw_serial_number_segment;   
    uint64_t serial_number_formulated;
    
    uint8_t data_available_flag; // use it to know when tid is read
    
}TidInfo_;

struct TagInfo_ {
    /** RN16 number */
    uint8_t rn16[2];
    /** PC value */
    uint8_t pc[2];
    /** EPC array */
    uint8_t epc[EPCLENGTH]; /* epc must immediately follow pc */
    /** EPC length */
    uint8_t epclen; /*length in bytes */
    /** TID struct  */
    TidInfo_ tid;
    /** Handle for write and read communication with the Tag */
    uint8_t handle[2];
    /** rssi which has been measured when reading this Tag. */
    uint8_t rssi;
    /** content of AGC and Internal Status Display Register 0x2A after reading a tag. */
    uint8_t agc;
};

/** Type definition struct: TagInfo_ is named Tag */
typedef struct TagInfo_ Tag;

extern Tag __attribute__((far)) tags_[MAXTAG];

/*------------------------------------------------------------------------- */
/** Search for tags (aka do an inventory round). Before calling any other
  * gen2 functions this routine has to be called. It first selects using the 
  * given mask a set of tags and then does an inventory round issuing query 
  * commands. All tags are stored in then tags array for examination by the 
  * user. 
  *
  * @param *tags an array for the found tags to be stored to
  * @param maxtags the size of the tags array
  * @param q 2^q slots will be done first, additional 2 round with increased 
  * or decreased q may be performed
  * @param cbContinueScanning callback is called after each slot to inquire if we should
  * continue scanning (e.g. for allowing a timeout)
  * @param singulate If set to true Req_RN command will be sent to get tag into Open state
  *                  otherwise it will end up in arbitrate
  * @param toggleSession If set to true, QueryRep commands will be sent immediately
  *                  after receiving tag reply to toggle session flag on tag.
  * @return the number of tags found
  */
unsigned gen2SearchForTags(Tag *tags
                          , uint8_t maxtags
                          , uint8_t q
                          , uint8_t (*cbContinueScanning)(void)
                          , uint8_t singulate
                          , uint8_t toggleSession
                          );


/** For reference see gen2SearchForTags(). The main difference is that it
  * uses the autoACK mode of the reader.
  */
unsigned gen2SearchForTagsAutoAck(Tag *tags_
                      , uint8_t maxtags
                      , uint8_t q
                      , uint8_t (*cbContinueScanning)(void)
                      , uint8_t singulate
                      , uint8_t toggleSession
                      );
/*------------------------------------------------------------------------- */
/** EPC ACCESS command send to the Tag.
  * This function is used to bring a tag with set access password from the Open
  * state to the Secured state.
  *
  * @attention This command works on the one tag which is currently in the open 
  *            state, i.e. on the last tag found by gen2SearchForTags().
  *
  * @param *tag Pointer to the Tag structure.
  * @param *password Pointer to first byte of the access password
  * @return The function returns an errorcode.
                  0x00 means no Error occoured.
                  Any other value is the backscattered error code from the tag.
  */
int8_t gen2AccessTag(Tag const * tag, uint8_t const * password);

/*------------------------------------------------------------------------- */
/** EPC LOCK command send to the Tag.
  * This function is used to lock some data region in the tag.
  *
  * @attention This command works on the one tag which is currently in the open 
  *            state, i.e. on the last tag found by gen2SearchForTags().
  *
  * @param *tag Pointer to the Tag structure.
  * @param *mask_action Pointer to the first byte of the mask and
                                    action array.
  * @param *tag_reply In case ERR_HEADER is returned this variable will 
  *                   contain the 8-bit error code from the tag.
  * @return The function returns an errorcode.
                  0x00 means no Error occoured.
                  Any other value is the backscattered error code from the tag.
  */
int8_t gen2LockTag(Tag *tag, const uint8_t *mask_action, uint8_t *tag_reply);

/*------------------------------------------------------------------------- */
/** EPC KILL command send to the Tag.
  * This function is used to permanently kill a tag. After that the
  * tag will never ever respond again.
  *
  * @attention This command works on the one tag which is currently in the open 
  *            state, i.e. on the last tag found by gen2SearchForTags().
  *
  * @param *tag Pointer to the Tag structure.
  * @param *password Pointer to first byte of the kill password
  * @param rfu 3 bits used as rfu content for first half of kill, should be zero
  * @param recom 3 bits used as recom content for second half of kill, zero 
  *        for real kill, !=0 for recommisioning
  * @param *tag_error: in case header bit is set this will be the return code from the tag
  * @return The function returns an errorcode.
                  0x00 means no Error occoured.
                  Any other value is the backscattered error code from the tag.
  */
int8_t gen2KillTag(Tag const * tag, uint8_t const * password, uint8_t rfu, uint8_t recom, uint8_t *tag_error);

/*------------------------------------------------------------------------- */
/** EPC WRITE command send to the Tag.
  * This function writes one word (16 bit) to the tag.
  * It first requests a new handle. The handle is then exored with the data.
  *
  * @attention This command works on the one tag which is currently in the open 
  *            state, i.e. on the last tag found by gen2SearchForTags().
  *
  * @param *tag Pointer to the Tag structure.
  * @param memBank Memory Bank to which the data should be written.
  * @param wordPtr Word Pointer Address to which the data should be written.
  * @param *databuf Pointer to the first byte of the data array. The data buffer
                             has to be 2 bytes long.
  * @param *tag_error In case tag returns an error (header bit set), this 
                      functions returns ERR_HEADER and inside tag_error the actual code
  * @return The function returns an errorcode.
                  0x00 means no error occoured.
                  0xFF unknown error occoured.
                  Any other value is the backscattered error code from the tag.
  */
int8_t gen2WriteWordToTag(Tag const * tag, uint8_t memBank, uint32_t wordPtr, uint8_t const * databuf, uint8_t * tag_error);

/*------------------------------------------------------------------------- */
/** EPC READ command send to the Tag.
  *
  * @attention This command works on the one tag which is currently in the open 
  *            state, i.e. on the last tag found by gen2SearchForTags().
  *
  * @param *tag Pointer to the Tag structure.
  * @param memBank Memory Bank to which the data should be written.
  * @param wordPtr Word Pointer Address to which the data should be written.
  * @param wordCount Number of bytes to read from the tag.
  * @param *destbuf Pointer to the first byte of the data array.
  * @return The function returns an errorcode.
                  0x00 means no error occoured.
                  0xFF unknown error occoured.
                  Any other value is the backscattered error code from the tag.
  */
int8_t gen2ReadFromTag(Tag *tag, uint8_t memBank, uint32_t wordPtr,
                          uint8_t wordCount, uint8_t *destbuf);

/*------------------------------------------------------------------------- */
/** EPC SELECT command. send to the tag.
  * This function does not take or return a parameter
  */
void gen2Select(struct gen2SelectParams *p);

/*------------------------------------------------------------------------------ */
/*Sends the tags EPC via the UART to the host */
/*The function needs the tags structure */
void gen2PrintEPC(Tag *tag);

/*------------------------------------------------------------------------- */
/** Prints the tag information out (UART).
  * @param *tag Pointer to the Tag structure.
  * @param epclen Length of the EPC.
  * @param tagNr Number of the tag.
  */
void gen2PrintTagInfo(Tag *tag, uint8_t epclen, uint8_t tagNr);

/*!
 *****************************************************************************
 *  \brief  Set the link frequency
 *
 *  Set the link frequency and gen2 specific parameters. After calling
 *  this function the AS3993 is in normal.
 *****************************************************************************
 */
void gen2Configure(const struct gen2Config *config);

/*!
 *****************************************************************************
 *  \brief  Open a session
 *
 * @param config: configuration to use 
 *
 *  Open a session for gen2 protocol
 *****************************************************************************
 */
void gen2Open(const struct gen2Config * config);

/*!
 *****************************************************************************
 *  \brief  Close a session
 *
 *  Close the session for gen2 protocol
 *****************************************************************************
 */
void gen2Close(void);

void u32ToEbv(uint32_t value, uint8_t *ebv, uint8_t *len);

/*!
 *****************************************************************************
 *  \brief  Perform a gen2 QUERY command and measure received signal strength
 *
 *****************************************************************************
 */
int8_t gen2QueryMeasureRSSI(uint8_t *agc, uint8_t *log_rssis, int8_t *irssi, int8_t *qrssi);

void checkAndSetSession( uint8_t newSession);

void insertBitStream(uint8_t *dest, uint8_t const *source, uint8_t len, uint8_t bitpos);

uint8_t inventoryGen2(void);

#endif
