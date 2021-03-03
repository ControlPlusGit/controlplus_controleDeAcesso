#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "FSM_DataHora.h"
#include "FSM_Ethernet.h"
#include "FSM_ESP8266.h"
#include "FSM_TabelaDeEstacionamento.h"
#include "FSM_KeepAlive.h"
#include "setup_usb.h"

#include "system.h"
#include "BSP/pin_manager.h"
#include "BSP/bsp.h"
#include "BSP/rfid_bsp.h"

#include "tabelaEstacionamento.h"
#include "tmr2.h"
#include "log.h"
#include "delay.h"

#include "RTC/DS1307.h"  
#include "EEPROM/24LC256.h"
#include "FLASH/flash.h"

#ifdef __PIC24FJ256DA210__
_CONFIG1(WDTPS_PS1 & FWPSA_PR32 & ALTVREF_ALTVREDIS & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_ON & JTAGEN_OFF)
_CONFIG2(POSCMOD_HS & IOL1WAY_OFF & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV3 & IESO_OFF)
_CONFIG3(WPFP_WPFP0 & SOSCSEL_LPSOSC & WUTSEL_LEG & ALTPMP_ALPMPDIS & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
#endif 

/////////////////////////////////////////////
// Green list criada a partir de tabelaEstacionamento.h
/////////////////////////////////////////////
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberadosTest;
/////////////////////////////////////////////
// RTC DS1307 library variables
/////////////////////////////////////////////
    Calendar calendar;
    RTC_DS1307_stats RTC_DS1307_status;
    // Quando precisar ler o calendario do RTC, usar a linha abaixo:
    // status = RTC_DS1307_I2C_read_calendar( &calendar ); 

/////////////////////////////////////////////
// RTC DS1307 library variables
/////////////////////////////////////////////
    EEPROM_24LC256_stats EEPROM_24LC256_status;
    // Para leitura e escrita na eeprom, usar linhas abaixo  
    //EEPROM_24LC256_I2C_write_uchar(0,200,0x55);
    //EEPROM_24LC256_I2C_read_uchar(0,200,&var);
   
void marsOne_init(void){
        
    ////////////////////////////////////////////////////////
    // Rotina de inicializacao visual do leitor
    ////////////////////////////////////////////////////////
    
    BSP_setBuzzer(OFF);
    BSP_setLed(NUM_MAX_LEDS,OFF);
    BSP_setRelay(NUM_MAX_RELAYS,OFF);
    
    BSP_setBuzzer(ON);
    BSP_setLed(NUM_MAX_LEDS,ON);

    delay_ms (1000);

    BSP_setBuzzer(OFF);
    BSP_setLed(NUM_MAX_LEDS,OFF);
    
    BSP_RS485_setDirection(RS485_INPUT);        
}


int8_t obtemDadosDaMemoriaFLASH(void){
    obtemListaDeVeiculosLiberados();
    return 0;
}

uint8_t num_of_tags;

int main(void){
   
    SYSTEM_Initialize();
    
    marsOne_init();         
     
    obtemDadosDaMemoriaFLASH();
    
    obtemParametrosDaMemoriaEEPROM();
    
    inicializaMaquinaDeEstados_ESP8266();   
    
    inicializaMaquinaDeEstados_TabelaDeEstacionamento();
    
    inicializaMaquinaDeEstados_DataHora();
    
    inicializaMaquinaDeEstados_KeepAlive(); 
            
    // Seleciona a antena 1
    SEL_BBA_SetHigh();
    SEL_A1_4_SetHigh();
    SEL_A1_2_SetHigh();
    SEL_A3_4_SetLow();
    
    while(1){
        LIGA_PA_SetHigh();
        num_of_tags = inventoryGen2();
        if(num_of_tags>=1){
            int i=0;
            LED_TAG_SetHigh();
            i=1;
        }
        LIGA_PA_SetLow();
        delay_ms(100);
        LED_TAG_SetLow();
    }
    
    return 0;
}




