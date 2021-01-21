#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "as3993_config.h"
#include "platform.h"
#include "perifericos.h"
#include "stream_dispatcher.h"
#include "usb_hid_stream_driver.h"
#include "uart_driver.h"
#include "uart.h"
#include "errno.h"
#include "as3993_public.h"
#include "as3993.h"
#include "gen2.h"
#include "global.h"
#include "timer.h"
#include "appl_commands.h"
#include "uart_driver.h"
#include "tuner.h"
#include "config_i2c3.h"
#include "mem_i2c_24LC256.h"
#include "tags.h"
#include "empilhadeira.h"
#include "rtc.h"
#include "FSM_EventosDeParada.h"
#include "FSM_DataHora.h"
#include "FSM_TabelaDeExclusao.h"
#include "FSM_Ethernet.h"
#include "FSM_ESP8266.h"
#include "setup_usb.h"



#if (FEMTO2 || FEMTO2_1)
_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV3 & IESO_ON)
_CONFIG3(WPFP_WPFP0 & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM & SOSCSEL_IO)      // SOSCSEL_IO: get RA4 and RB4 as digital I/O
_CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)

#elif (__PIC24FJ256DA210__)
_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_ON & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV3 & IESO_OFF)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_LPSOSC & WUTSEL_LEG & ALTPMP_ALPMPDIS & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)

#endif

//u32 counter;
char num_serie[20];
char empilhadeira[20];


int dbm_tag_real;

extern void tick(void);
extern void ObtemID (char*);
extern Freq Frequencies;

extern Tag __attribute__((far)) tags_[MAXTAG];


int total_parcial = 0;

u8 cin,clen,cout = 0;

unsigned int total_tags = 0;

void lista_freq_anatel(void);

extern u8 inventoryGen2(void);


void ligaTimer2(void);
extern void uart4Tx(u8);

extern u16 readerInitStatus;
/** FW information which will be reported to host. */
static const char gAS3993FwInfo[] = FIRMWARE_ID"||"HARDWARE_ID;
/** FW information which will be logged on startup. Version information is included in logger. */
static const char gLogStartup[] = FIRMWARE_ID" %hhx.%hhx.%hhx on "HARDWARE_ID"\n";
/** FW version which will be reported to host */
const u32 firmwareNumber = FIRMWARE_VERSION;
//static u8 usedAntenna = 8;
int tem_ze_na_area;

#ifdef PORTAL
int TempoParaDesligarBuzzer;
#define  TEMPO_PARA_DESLIGAR_BUZZER 100
int antena_atual;
#endif 

int ContadorParaUmSegundo;
char ContadorParaUmCentessimo;

int ContadorParaEnviarArrayXbee;
int ContadorParaRemocaoDeTabelaDeExclusao;

void systemInit(void);

#if 0
static void calcBestSlotSize( void )
{
    u8 round;
    u8 powSlot;
    u8 numTags;

    for ( powSlot = 0; powSlot < 15 ; powSlot ++)
    {
        u8 maxTags=0;
        u16 tagsFound=0;
        for ( round = 0; round < 255 ; round ++)
        {
            numTags = gen2SearchForTags(tags_,16,0,0,powSlot,continueAlways,0,1);
            tagsFound+= numTags;
            if ( numTags > maxTags) maxTags = numTags;
        }
        LOG("found with powSlot=%hhx %x tags, max %hhx\n",
                                      powSlot,        tagsFound,maxTags);
    }
}
#endif



#ifdef TUNER
void mainSenCIN(int select)
{
    if (select) 
        SEN_TUNER_CIN(1);
    else
        SEN_TUNER_CIN(0);

}
void mainSenCLEN(int select)
{
    if (select) 
        SEN_TUNER_CLEN(1);
    else
        SEN_TUNER_CLEN(0);

}
void mainSenCOUT(int select)
{
    if (select) 
        SEN_TUNER_COUT(1);
    else
        SEN_TUNER_COUT(0);

}
#if RADON
void ant1SenCIN(int select)
{
    if (select) 
        SEN_ANT1_CINPIN(1);
    else
        SEN_ANT1_CINPIN(0);

}
void ant1SenCOUT(int select)
{
    if (select) 
        SEN_ANT1_COUTPIN(1);
    else
        SEN_ANT1_COUTPIN(0);

}
#endif

TunerConfiguration mainTuner = 
{
#if TUNER_CONFIG_CIN
    mainSenCIN,
#else
    NULL,
#endif
#if TUNER_CONFIG_CLEN
    mainSenCLEN,
#else
    NULL,
#endif
#if TUNER_CONFIG_COUT
    mainSenCOUT
#else
    NULL,
#endif
};

#if RADON
TunerConfiguration ant1Tuner = 
{
    ant1SenCIN,
    NULL,
    ant1SenCOUT
};
#endif
#endif

/** main function
 * Initializes board, cpu, reader, host communication, ...\n
 * After intialization a loop which waits for commands from host
 * and performs cyclic inventory rounds is entered.
 */


/*
void setaSensibilidade (unsigned char valor){
    signed char rascunho = 0;
    rascunho = rascunho - valor;
    as3993SetSensitivity(rascunho);
}
*/

#ifdef PORTAL
void PreTratamentoDeTagsParaOPortalFrango (int Antena, int AntenaReal){
    int Contador;
    //char rascunho;
    
    for (Contador = 0; Contador < MAXTAG;Contador = Contador + 1){
        if (tags_[Contador].epclen != 0){ // Tem tag na posicao?
            /*
            //Feira 
            rascunho = tags_[Contador].epc[0];
            if (rascunho == 0x10 ||  rascunho == 0x20){
                rascunho = rascunho | tags_[Contador].epc[1];
                rascunho = rascunho | tags_[Contador].epc[2];
            } else {
                rascunho = 0;                
            }
            if (rascunho != 0){
                (void)TrataTagDePortalFrango (&tags_[Contador].epc[0], Antena, AntenaReal);//Pego apenas os 3 primeiros bytes
            } else {
                (void)TrataTagDePortalFrango (&tags_[Contador].epc[EPCLENGTH - TAMANHO_DE_EPC_EM_PORTAL_FRANGO], Antena, AntenaReal);//Pego apenas os 3 primeiros bytes
            }
            */
            //(void)TrataTagDePortalFrango (tags_[Contador].epc[EPCLENGTH - TAMANHO_DE_EPC_EM_PORTAL_FRANGO], TAMANHO_DE_EPC_EM_PORTAL_FRANGO);//Pego apenas os 3 ultimos bytes
            if ((tags_[Contador].epc[0] == 0x30) || (tags_[Contador].epc[0] == 0x50)){
                (void)TrataTagDePortalFrango (&tags_[Contador].epc[0], Antena, AntenaReal);//Pego apenas os 3 ultimos bytes
            }
            memset(tags_[Contador].epc, 0, EPCLENGTH);
            memset(tags_[Contador].rn16, 0, 2);
            memset(tags_[Contador].pc, 0, 2);
            memset(tags_[Contador].handle, 0, 2);
            tags_[Contador].epclen = 0;
            tags_[Contador].agc = 0;
        }
    }
}
#endif 

void realizaAutoSintoniaDosCapacitores(int Metodo){
    //extern  TunerParameters tunerParams;
    static TunerParameters tunerParams = {2, 12, 12};
    extern TunerConfiguration mainTuner;
    TunerConfiguration *tuner = NULL;
    TunerParameters *params = NULL;
//    int Resultados[3];
    
    int endereco = 0;
    char enderecoRefl_MSB = 0;
    char enderecoRefl_LSB = 0;
    unsigned char aux1,aux2;
    
    char Mensagem[100];
    int Contador;
    
    tuner = &mainTuner;
    params = &tunerParams;
    
    int _AntenaASerLida;
    _AntenaASerLida = 1;
    sel_led(0,0);
    for(_AntenaASerLida=1;_AntenaASerLida<=4;_AntenaASerLida++){
        sel_led(_AntenaASerLida, 1);
        sel_antena(_AntenaASerLida);
        delay_ms(300);
        switch(Metodo){
            case (0):
                as3993AntennaPower(1);
                tunerOneHillClimb(tuner, params, 100);
                as3993AntennaPower(0);
                break;
            case (1): /* advanced: hill climb from more points */
                as3993AntennaPower(1);
                tunerMultiHillClimb(tuner, params);
                as3993AntennaPower(0);
                break;
            case (2):
                as3993AntennaPower(1);
                tunerTraversal(tuner, params);
                as3993AntennaPower(0);
        }

        sprintf(Mensagem, "Antena %d -> Cin: %d, Clen: %d, Cout: %d, Reflexao: %d\n", _AntenaASerLida,params->cin, params->clen, params->cout,params->reflectedPower);
        
        switch(_AntenaASerLida){
            case 1:
                endereco = END_AJUSTE_CAP0_ANTENA_1;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_1_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_1_LSB;
                break;
            case 2:
                endereco = END_AJUSTE_CAP0_ANTENA_2;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_2_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_2_LSB;
                break;
            case 3:
                endereco = END_AJUSTE_CAP0_ANTENA_3;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_3_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_3_LSB;
                break;
            case 4: 
                endereco = END_AJUSTE_CAP0_ANTENA_4;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_4_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_4_LSB;                       
                break;
        }
        
        EscreverNaEEprom(endereco, params->cin);
        EscreverNaEEprom(endereco+1, params->clen);
        EscreverNaEEprom(endereco+2, params->cout);
        
        aux1 = (unsigned char)(params->reflectedPower>>8);
        aux2 = (unsigned char)(params->reflectedPower & 0X00FF);
        EscreverNaEEprom(enderecoRefl_MSB,aux1);
        EscreverNaEEprom(enderecoRefl_LSB,aux2);
        
        Contador = 0;
        while(Mensagem[Contador]){
            uart3Tx(Mensagem[Contador]);
            Contador = Contador + 1;
        }
        sel_led(_AntenaASerLida, 0);
    }
}

int main(void){
    
    CNPU1bits.CN15PUE = 1;
 
    CNPU2bits.CN16PUE = 1;
    CNPU2bits.CN19PUE = 1;
    CNPU4bits.CN49PUE = 1;
    CNPU4bits.CN56PUE = 1;
    CNPU4bits.CN57PUE = 1;
    CNPU2bits.CN28PUE = 1;
    
    
    desliga_saida_pa();
    
    
    
    ld_saidas (0,0);

    u32 baudrate, realrate;
            
    //systemInit();
    timerInit();
    platformInit();
    spiInit();
    
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes
    
    baudrate = BAUDRATE;
   
    uart3TxInitialize(SYSCLK, baudrate, &realrate); // usb
    
    uart2TxInitialize(SYSCLK, baudrate, &realrate); // ethernet
  
    uartTxInitialize(SYSCLK, baudrate, &realrate); // wifi 
    
    uart4TxInitialize(SYSCLK, baudrate, &realrate);
 
    sel_led (0,0);
   
    sel_led (0,1);
    liga_led_tag ();
    liga_saida_pa ();
    liga_dir();
    liga_led_zig();
    liga_led_wifi();
    liga_led_3g();
    liga_led_gps();
    liga_buzzer();

    delay_ms (1000);

    desliga_saida_pa ();
 
    desliga_buzzer();
    desliga_led_vm();
    desliga_sirene();

    desliga_led_zig();
    desliga_led_wifi();
    desliga_led_3g();
    desliga_led_gps();
    sel_led (0,0);
    desliga_led_tag ();
    desliga_dir();

    delay_ms(1);
    lista_freq_anatel();
    readerInitStatus = as3993Initialize(Frequencies.freq[0]);
    
    USBModuleDisable();
    initCommands(); // USB report commands
    
    desliga_saida_pa();
    
    desliga_led_tag ();
   
#define normal
    ligaTimer2();
    uartRxInitialize();
   
    IniciaRTC();   
    inicializa_i2c3();
       
    obtemParametrosDaMemoria();
    
    inicializaMaquinaDeEstados_ESP8266();  
    
    num_serie[0] = idDoLeitor[0];
    num_serie[1] = idDoLeitor[1];
    num_serie[2] = idDoLeitor[2];
    num_serie[3] = idDoLeitor[3];
       
    delay_ms(1000);

    if(readerInitStatus){
        readerInitStatus = as3993Initialize(Frequencies.freq[0]);
    }
    
    iniciaLogicaDeEmpilhadeira();//Gilson, teste de novo cÃƒÆ’Ã‚Â³digo em 05/06/17
    //as3993SetSensitivity(-80);//Ajuste para diminuir a leitura para 8 metros
    as3993SetSensitivity(125);//Ajuste normal
    //as3993SetSensitivity(-90);
    
    
#ifdef ARCELOR_JUIZ_DE_FORA_EMPILHADEIRA_TRADMAQ_3_5_TONS
    logicaDeEmpilhadeiraV2();
#endif
    return 0;
}

void lista_freq_anatel(void)
{
    Frequencies.freq[0]= 902750;
    Frequencies.freq[1]= 903250;
    Frequencies.freq[2]= 903750;
    Frequencies.freq[3]= 904250;
    Frequencies.freq[4]= 904750;
    Frequencies.freq[5]= 905250;
    Frequencies.freq[6]= 905750;
    Frequencies.freq[7]= 906250;
    Frequencies.freq[8]= 906750;
    Frequencies.freq[9]= 907250;
    Frequencies.freq[10]= 912000;
    Frequencies.freq[11]= 912500;;
    Frequencies.freq[12]= 913000;
    Frequencies.freq[13]= 916250;
    Frequencies.freq[14]= 916750;
    Frequencies.freq[15]= 917250;
    Frequencies.freq[16]= 917750;
    Frequencies.freq[17]= 918250;
    Frequencies.freq[18]= 918750;
    //Frequencies.numFreqs=0;
    Frequencies.numFreqs=19;  
     
    //Frequencies.numFreqs=19;
    
    
    /*
    Frequencies.freq[0]= 902000;
    Frequencies.freq[1]= 902500;
    Frequencies.freq[2]= 903000;
    Frequencies.freq[3]= 904000;
    */
    //Frequencies.freq[4]= 904500;
    //Frequencies.freq[5]= 905000;
    
    
    /*
    Frequencies.freq[0]= 921500;
    Frequencies.freq[1]= 921750;
    Frequencies.freq[2]= 922000;
    Frequencies.freq[3]= 922250;
    Frequencies.numFreqs=4;
    */
    
    /*
    Frequencies.freq[0]= 916500;
    Frequencies.freq[1]= 916750;
    Frequencies.freq[2]= 917000;
    Frequencies.freq[3]= 917250;
    Frequencies.numFreqs=4;
    */
    //Pixys Air??
    /*
    Frequencies.freq[0]= 916800;
    Frequencies.freq[1]= 917291;
    Frequencies.numFreqs=2;
*/
    
    //Frequencies.numFreqs=4;
    

    
    //Ajustes para Antenas da China
    /*
    Frequencies.freq[0]= 902000;
    Frequencies.freq[1]= 904000;
    Frequencies.numFreqs=2;
    */


    //Pixys Air??
    /*
    Frequencies.freq[0]= 921833;
    Frequencies.freq[1]= 922291;
    Frequencies.numFreqs=2;
    */
    
    //Frequencies.freq[0]= 902750;//Frequencia otima ate 26/12/18, vou mudar porque le 20 metros ou mais e
// preciso que seja menos, entre 10 e 15 metros no maximo.
    //Frequencies.freq[0]= 910000;
    //Frequencies.freq[0]= 915000;
    //Frequencies.freq[0]= 920000;
    //Frequencies.freq[0]= 925000;
    //Frequencies.freq[0]= 930000;
    //Frequencies.freq[0]= 935000;
    //Frequencies.freq[0]= 935000;
    
    //Frequencies.freq[0]= 916800;
    //Frequencies.freq[0]= 917291;
    //Frequencies.freq[0]= 921833;//BOm para a Pixys Air
    //Frequencies.freq[0]= 922291;

    Frequencies.freq[0]= 915000;

    Frequencies.numFreqs=1;    
}




void systemInit(void)
{
#if RUN_ON_AS3994
    _RCDIV = 0;     // FIXME: why is our clock to slow without divider?
#endif
}


u8 applPeripheralReset(void)
{
    as3993Reset();
    return ERR_NONE;
}

u8 applProcessCmd( u8 protocol, u16 rxSize, const u8 * rxData, u16 * txSize, u8 * txData )
{
    /*LOG("applProcessCmds(ptcl=%hhx, tx=%hhx, rx=%hhx)\n",
            rxData[0], rxSize, txSize);*/
    return commands(protocol, rxSize, rxData, txSize, txData );
}

u8 applProcessCyclic( u8 * protocol, u16 * txSize, u8 * txData, u16 remainingSize )
{
    return sendTagData( protocol, txSize, txData, remainingSize );
}

const char * applFirmwareInformation()
{
    return gAS3993FwInfo;
}


/*!This function reads one or all registers from the AS3993. See also applReadReg().\n
  The format of the report from the host is as follows:
  <table>
    <tr><th>   Byte</th><th>       0</th><th>       1</th></tr>
    <tr><th>Content</th><td>  mode  </td><td>reg_addr</td></tr>
  </table>
  Where mode = 0 requests to read all registers and mode = 1 requests to read only
  the register with address reg_addr. If mode = 0 reg_addr is ignored. \n
  If mode = 0 the device sends back:
  <table>
    <tr>
        <th>Byte</th>
        <th>0</th>
        <th>..</th>
        <th>29</th>
        <th>30</th>
        <th>31</th>
        <th>..</th>
        <th>36</th>
        <th>37</th>
        <th>38</th>
        <th>48</th>
    </tr>
    <tr>
        <th>Content</th>
        <td>reg 0x00</td>
        <td>..</td>
        <td>reg 0x1D</td>
        <td>reg 0x22</td>
        <td>reg 0x29</td>
        <td>..</td>
        <td>reg 0x2E</td>
        <td>reg 0x33</td>
        <td>reg 0x35</td>
        <td>..</td>
        <td>reg 0x3F</td>
    </tr>
  </table>
  If mode = 1 the device sends back:
  <table>
    <tr><th>   Byte</th><th>        0</th></tr>
    <tr><th>Content</th><td>reg value</td></tr>
  </table>
 
  returns ERR_NONE if operation was successful, ERR_PARAM is invalid mode was set.
*/
u8 cmdReadReg(u16 rxSize, const u8 * rxData, u16 * txSize, u8 * txData)
{
    u8 status = ERR_PARAM;
    //LOG("cmdReadReg: cmd:%hhx, rxsize:%hhx, txsize:%hhx\n", rxData[0], rxSize, *txSize);
    if (rxSize < READ_REG_RX_SIZE)
        return status;
    switch (rxData[0])
    {
        case 0:     //read all regs
            status = readRegisters(txSize, txData);
            break;
        case 1:     // read one reg
            status = readRegister(rxData[1], txSize, txData);
            break;
        default:
            status = ERR_PARAM;
    }
    return status;
}

u8 applReadReg( u16 rxSize, const u8 * rxData, u16 * txSize, u8 * txData )
{
    return cmdReadReg(rxSize, rxData, txSize, txData);
}

/*!This function writes one register on the AS3993. See also applWriteReg(). \n
  The format of the report from the host is as follows:
  <table>
    <tr><th>   Byte</th><th>       0</th><th>    1</th></tr>
    <tr><th>Content</th><td>reg_addr</td><td>value</td></tr>
  </table>
  if reg_addr > 0x80, then an immediate command is executed.\n
  The device sends back:
  <table>
    <tr><th>   Byte</th><th>0</th></tr>
    <tr><th>Content</th><td>0</td></tr>
  </table>

  returns ERR_NONE if operation was successful.
 */
u8 cmdWriteReg (u16 rxSize, const u8 * rxData, u16 * txSize, u8 * txData)
{
    //LOG("applWriteReg: addr:%hhx, val:%hhx, rxsize:%hhx, txsize:%hhx\n", rxData[0], rxData[1], rxSize, *txSize);
    if (rxSize < WRITE_REG_RX_SIZE)
        return ERR_PARAM;

    return writeRegister(rxData[0], rxData[1], txSize, txData);
}

u8 applWriteReg( u16 rxSize, const u8 * rxData, u16 * txSize, u8 * txData )
{
    return cmdWriteReg(rxSize, rxData, txSize, txData);
}

#if RUN_ON_AS3994 || __PIC24FJ256GB110__    // check for CPU: fix nightly build
/* TODO: AS3994 does not support bootloader yet. */
void enableBootloader()
{

}
#endif



void tick (void)
{
    incrementaContadorDePerformance();
    //LED_A3(1);
    //sel_led(4,1);
    //OperacoesParaRtcEmTick();   
    operacoesEmTickParaEmpilhadeira();//Teste Gilson 06/06/17
    //OperacoesParaTickGprs();//Teste Gilson 31/08/17
    //operacoesEmTickParaZigBee();//Teste Gilson 06/09/17
    //operacacoesEmTickParaGps();//Teste Gilson 11/10/17
    //logicaDeRemocaoDeTabelaDeExclusao();
    //lidaComExpiracaoDoBufferDeRecepcaoDoZigBee();
    //sel_led(4,0);
    //OperacoesParaTickGprs();
    
    //ContadorParaEnviarArrayXbee++;
    //if (ContadorParaEnviarArrayXbee == 1000)
    //{
    //    ContadorParaEnviarArrayXbee = 0;
    //   //envia_meu_operador();
    //    atualizaHoraEData();
        //logicaDeRemocaoDeTabelaDeExclusao();
    //}
    
    //ContadorParaRemocaoDeTabelaDeExclusao = ContadorParaRemocaoDeTabelaDeExclusao + 1;
    //if (ContadorParaRemocaoDeTabelaDeExclusao == 10000){
    
    //if (ContadorParaRemocaoDeTabelaDeExclusao == 100){
    //    ContadorParaRemocaoDeTabelaDeExclusao = 0;
        //logicaDeRemocaoDeTabelaDeExclusao();
        
    //}
    //logicaDeRemocaoDeTabelaDeExclusao();
    
    //decrementaContadorDeEstouroDeTempoDaRecepcaoDeDadosDaUartDaTabelaDeExclusao();
    //LED_A3(0);   
}