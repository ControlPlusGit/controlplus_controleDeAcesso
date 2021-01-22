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
#include "spi1.h"

#ifdef __PIC24FJ256DA210__
_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_ON & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV3 & IESO_OFF)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_LPSOSC & WUTSEL_LEG & ALTPMP_ALPMPDIS & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)

#endif

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

int ContadorParaUmSegundo;
char ContadorParaUmCentessimo;

int ContadorParaEnviarArrayXbee;
int ContadorParaRemocaoDeTabelaDeExclusao;

void systemInit(void);

int main(void){
    
    systemInit();    
 
    readerInitStatus = as3993Initialize(915000ULL);
    
    initCommands(); 
    
    desliga_saida_pa();
    
    desliga_led_tag ();
   
    ligaTimer2();
    
   
    IniciaRTC(); // Inicializa o RTC no periferico I2C1
    inicializa_i2c3(); // Inicializa a EEPROM 
       
    obtemParametrosDaMemoria();
    
    inicializaMaquinaDeEstados_ESP8266();  
    
    num_serie[0] = idDoLeitor[0];
    num_serie[1] = idDoLeitor[1];
    num_serie[2] = idDoLeitor[2];
    num_serie[3] = idDoLeitor[3];
       
    delay_ms(1000);

    if(readerInitStatus){
        readerInitStatus = as3993Initialize(915000ULL);
    }
    
    iniciaLogicaDeEmpilhadeira();
    
    as3993SetSensitivity(125);
    
    logicaDeEmpilhadeiraV2();

    return 0;
}

void systemInit(void){

    u32 baudrate, realrate;
    
    CNPU1bits.CN15PUE = 1; 
    CNPU2bits.CN16PUE = 1;
    CNPU2bits.CN19PUE = 1;
    CNPU4bits.CN49PUE = 1;
    CNPU4bits.CN56PUE = 1;
    CNPU4bits.CN57PUE = 1;
    CNPU2bits.CN28PUE = 1;
    
    //systemInit();
    timerInit();
    platformInit();
    SPI1_Initialize();
    
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes
    
    baudrate = BAUDRATE;
   
    
    uartTxInitialize(SYSCLK, baudrate, &realrate); 
    
    uart2TxInitialize(SYSCLK, baudrate, &realrate); // ethernet
    
    uart3TxInitialize(SYSCLK, baudrate, &realrate); // usb
    
    uart4TxInitialize(SYSCLK, baudrate, &realrate); // wifi 
    
    ////////////////////////////////////////////////////////
    // Rotina de inicializacao visual do leitor
    ////////////////////////////////////////////////////////
    
    desliga_saida_pa();    
    
    ld_saidas (0,0); // Desliga todas as saidas
    sel_led (0,0);   // Desliga todos os leds
    
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
    
}

void tick ( void ){
    incrementaContadorDePerformance();    
    operacoesEmTickParaEmpilhadeira();
}