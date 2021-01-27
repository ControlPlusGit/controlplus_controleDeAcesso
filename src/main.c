#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "i2c.h"
#include "rtc.h"
#include "spi1.h"
#include "timer.h"
#include "platform.h"
#include "perifericos.h"
#include "uart_driver.h"
#include "uart.h"
#include "errno.h"
#include "as3993_public.h"
#include "as3993_config.h"
#include "as3993.h"
#include "gen2.h"
#include "appl_commands.h"
#include "global.h"
#include "uart_driver.h"
#include "tuner.h"
#include "config_i2c3.h"
#include "mem_i2c_24LC256.h"
#include "tags.h"
#include "FSM_DataHora.h"
#include "FSM_Ethernet.h"
#include "FSM_ESP8266.h"
#include "setup_usb.h"

#include "tabelaEstacionamento.h"
#include "tmr2.h"
#include "FSM_TabelaDeEstacionamento.h"
#include "log.h"

#ifdef __PIC24FJ256DA210__
_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_ON & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV3 & IESO_OFF)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_LPSOSC & WUTSEL_LEG & ALTPMP_ALPMPDIS & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)

#endif     

TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;

uint16_t globalCounter_ms = 0;

void tick(void);

void systemInit(void);

void testAppResources(void);

int main(void){
        
    systemInit();    
 
    obtemParametrosDaMemoria();
    
    inicializaMaquinaDeEstados_ESP8266();   
    
    testAppResources();
    
    while(1){
        
    }
    
    return 0;
}

void tick ( void ){   
    
    globalCounter_ms++;
    
    executaMaquinaDeEstados_TabelaDeEstacionamento();
    executaMaquinaDeEstados_ESP8266();
    commandHandlerPortaUSB();
}

uint16_t tick_getTimerCounter(void){
    return globalCounter_ms;
}

void systemInit(void){

    u32 baudrate, realrate;
    
    u16 readerInitStatus;
    
    CNPU1bits.CN15PUE = 1; 
    CNPU2bits.CN16PUE = 1;
    CNPU2bits.CN19PUE = 1;
    CNPU4bits.CN49PUE = 1;
    CNPU4bits.CN56PUE = 1;
    CNPU4bits.CN57PUE = 1;
    CNPU2bits.CN28PUE = 1;
    
    platformInit();
    
    SPI1_Initialize();
    
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes
    
    TMR2_LoadInterruptCallback(tick);
    
    TMR2_Initialize();
   
    IniciaRTC(); // Inicializa o RTC no periferico I2C1
    
    inicializa_i2c3(); // Inicializa a EEPROM 
    
    baudrate = BAUDRATE;   
    
    uartTxInitialize(SYSCLK, baudrate, &realrate); 
    
    uart2TxInitialize(SYSCLK, baudrate, &realrate); // ethernet
    
    uart3TxInitialize(SYSCLK, baudrate, &realrate); // usb
    
    uart4TxInitialize(SYSCLK, baudrate, &realrate); // wifi 
    
    readerInitStatus = as3993Initialize(BAUDRATE);
    
    initCommands(); 
       
    delay_ms(10);

    if(readerInitStatus){
        readerInitStatus = as3993Initialize(BAUDRATE);
    }
    
    as3993SetSensitivity(125);
    
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

void testAppResources(void){
    
    loadLogCallbackFunction(uart3Tx);
    
    ////////////////////////////
    // Green list tests
    ////////////////////////////
    testTabelaDeEPC_should_IncludeSearchExclude();
    
    ////////////////////////////
    // TMR2 overflow interrupt
    ////////////////////////////
    test_TMR2_OverflowInterrupt_should_Execute();
    
    TMR2_LoadInterruptCallback(tick);
    
    ////////////////////////////
    // Async delay with TMR2 interrupt
    ////////////////////////////
    logMsg("///////////////////////////////////////////////\n\rTESTE - DELAY ASSINCRONO COM TIMER2\n\r///////////////////////////////////////////////\n\n\r");
    
    uint8_t async_delay_ok = 0;
    char mensagem[300];      
    uint16_t time_now = tick_getTimerCounter(); 
    uint16_t delay = 5000 + time_now;
    uint16_t inicial, final, diferenca;
    
    inicial = time_now;
    
    sprintf(mensagem,"mili segundos inicial: %u\n\n\r",inicial);
    logMsg(mensagem);
    
    while(!async_delay_ok){
        if( tick_getTimerCounter() == delay ) {
            async_delay_ok = 1;            
        }         
    }
    
    final = tick_getTimerCounter();
    
    sprintf(mensagem,"mili segundos final: %u\n\n\r",final);
    logMsg(mensagem);
    
    diferenca = final-inicial;
    
    sprintf(mensagem,"diferenca: %u\n\n\r",diferenca);
    logMsg(mensagem);
    
    logMsg("Delay assincrono executado com sucesso!\n\n\r");
    
    ////////////////////////////
    // Receive green list and mount table
    ////////////////////////////
    
    inicializaMaquinaDeEstados_TabelaDeEstacionamento();
            
    inicializaMaquinaDeEstados_ESP8266();
    
}