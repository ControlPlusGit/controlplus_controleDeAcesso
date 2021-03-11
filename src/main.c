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
#include "RFID/as3993.h"
#include "RFID/gen2.h"

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

uint8_t realizaLeituraDeAntena(uint8_t antena){
    BSP_RFID_selectAntenna(antena);        
    return BSP_RFID_searchForTags();
}

int8_t verificaTagValida(uint8_t *tag){
    uint8_t i;
    uint8_t *p = tag;
    
    if( *tag == 0x30 ){
        tag += 3;
        for( i = 3; i < MAXTAG-1; i++){            
            if( *tag != 0x00 )
            {
                return -1;
            }
            else{
                tag++;
            }
        }
    }
    else{
        return -1;
    }
    
    tag = p;
    
    return 1;
}

#define FLUXO_DE_SUCESSO 0
#define FLUXO_DE_INSUCESSO 1

int8_t (*functionPointerEntrada)(void);
int8_t (*functionPointerSaida)(void);
typedef struct{
    uint16_t *action;
    uint16_t wait_ms;
    uint16_t next[2];
}State;

typedef State Maquina;

enum{
    LER_ANTENA = 0,
    VERIFICAR_TAG_VALIDA,
    VERIFICAR_TAG_PRESENTE_NA_GREENLIST,
    ABRIR_PORTAO1_DESLIGA_PORTAO2,
    AGUARDA_FECHAMENTO_PORTAO1,
    ABRIR_PORTAO2_DESLIGA_PORTAO1,
    AGUARDA_FECHAMENTO_PORTAO2,
    REGISTRA_EVENTO,
    FIM,
}app_states;

EPC_Estacionamento epcEntrada;
EPC_Estacionamento epcSaida;

uint8_t movimentoSendoRealizado_Entrada = NAO;
uint8_t movimentoSendoRealizado_Saida = NAO;

int8_t ler_antena(void){
    
    uint8_t num_of_tags = 0;    
            
    num_of_tags = realizaLeituraDeAntena(ANTENNA_1);   
    
    if(num_of_tags > 0){
        movimentoSendoRealizado_Entrada = SIM;
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }   
}

int8_t ler_antena_saida(void){
    
    uint8_t num_of_tags = 0;    
            
    num_of_tags = realizaLeituraDeAntena(ANTENNA_2);   
    
    if(num_of_tags > 0){
        movimentoSendoRealizado_Saida = SIM;
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }   
}

int8_t verificarTagValida(void){
    int i;

    for( i = 0; i < MAXTAG; i++){

        if( verificaTagValida( tags_[i].epc ) ){ // Tag veicular valida?
            epcEntrada.byte1 = tags_[i].epc[2];
            epcEntrada.byte2 = tags_[i].epc[1];
            return FLUXO_DE_SUCESSO;
        }
        else{
            return FLUXO_DE_INSUCESSO;
        }        
    }    
}
int8_t verificarTagPresenteNaGreenList(void){
    
    if( buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epcEntrada)){ // Veiculo esta na lista?    
        return FLUXO_DE_SUCESSO;    
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }
}
int8_t abrirPortao1DesligarPortao2(void){
    
    BSP_setRelay(RELAY_1, ON);
    BSP_setRelay(RELAY_2, OFF);
    
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao1(void){
    
    BSP_setRelay(RELAY_1, OFF);
    BSP_setRelay(RELAY_2, OFF);
    
    if( !BSP_readDigitalInput(INPUT_1) ){
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }
}
int8_t abrirPortao2DesligarPortao1(void){
    
    BSP_setRelay(RELAY_2, ON);
    BSP_setRelay(RELAY_1, OFF);
    
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao2(void){
    
    BSP_setRelay(RELAY_2, OFF);
    BSP_setRelay(RELAY_1, OFF);
    
    if( !BSP_readDigitalInput(INPUT_2) ){
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }
    
    return FLUXO_DE_SUCESSO;
}
int8_t registraEventoEntrada(void){return FLUXO_DE_SUCESSO;}
int8_t registraEventoSaida(void){return FLUXO_DE_SUCESSO;}
int8_t fim(void){movimentoSendoRealizado_Entrada = NAO; movimentoSendoRealizado_Saida = NAO; return FLUXO_DE_SUCESSO;}

Maquina maqMovimentoEntrada[20] = {
                                    [LER_ANTENA]                            = { (uint16_t*)ler_antena,                      10, {VERIFICAR_TAG_VALIDA,FIM}                                },
                                    [VERIFICAR_TAG_VALIDA]                  = { (uint16_t*)verificarTagValida,              200, {VERIFICAR_TAG_PRESENTE_NA_GREENLIST,FIM}                  },
                                    [VERIFICAR_TAG_PRESENTE_NA_GREENLIST]   = { (uint16_t*)verificarTagPresenteNaGreenList, 200, {ABRIR_PORTAO1_DESLIGA_PORTAO2,FIM}                        },
                                    [ABRIR_PORTAO1_DESLIGA_PORTAO2]         = { (uint16_t*)abrirPortao1DesligarPortao2,     2000,{AGUARDA_FECHAMENTO_PORTAO1,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO1]            = { (uint16_t*)aguardaFechamentoPortao1,        200, {ABRIR_PORTAO2_DESLIGA_PORTAO1,AGUARDA_FECHAMENTO_PORTAO1} },
                                    [ABRIR_PORTAO2_DESLIGA_PORTAO1]         = { (uint16_t*)abrirPortao2DesligarPortao1,     2000,{AGUARDA_FECHAMENTO_PORTAO2,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO2]            = { (uint16_t*)aguardaFechamentoPortao2,        200, {REGISTRA_EVENTO,AGUARDA_FECHAMENTO_PORTAO2}               },
                                    [REGISTRA_EVENTO]                       = { (uint16_t*)registraEventoEntrada,           200, {LER_ANTENA,FIM}                                           }, 
                                    [FIM]                                   = { (uint16_t*)fim,                             200, {LER_ANTENA,LER_ANTENA}                                    },
                                  };

Maquina maqMovimentoSaida[20] = {
                                    [LER_ANTENA]                            = { (uint16_t*)ler_antena_saida,                10, {VERIFICAR_TAG_VALIDA,FIM}                                },
                                    [VERIFICAR_TAG_VALIDA]                  = { (uint16_t*)verificarTagValida,              200,  {ABRIR_PORTAO2_DESLIGA_PORTAO1,FIM}                        },
                                    [VERIFICAR_TAG_PRESENTE_NA_GREENLIST]   = { (uint16_t*)verificarTagPresenteNaGreenList, 200,  {0,0}                                                      },
                                    [ABRIR_PORTAO1_DESLIGA_PORTAO2]         = { (uint16_t*)abrirPortao1DesligarPortao2,     2000,{AGUARDA_FECHAMENTO_PORTAO1,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO1]            = { (uint16_t*)aguardaFechamentoPortao1,        200, {REGISTRA_EVENTO,AGUARDA_FECHAMENTO_PORTAO1}               },
                                    [ABRIR_PORTAO2_DESLIGA_PORTAO1]         = { (uint16_t*)abrirPortao2DesligarPortao1,     2000,{AGUARDA_FECHAMENTO_PORTAO2,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO2]            = { (uint16_t*)aguardaFechamentoPortao2,        200, {ABRIR_PORTAO1_DESLIGA_PORTAO2,AGUARDA_FECHAMENTO_PORTAO2} },
                                    [REGISTRA_EVENTO]                       = { (uint16_t*)registraEventoSaida,             200, {LER_ANTENA,FIM}                                           }, 
                                    [FIM]                                   = { (uint16_t*)fim,                             200, {LER_ANTENA,LER_ANTENA}                                    },
                                  };

uint16_t estadoAtual = LER_ANTENA;
uint16_t fluxoMaqEntrada = FLUXO_DE_SUCESSO;

void logicaDeMovimentoDeEntrada(void){
        
    if( delayLogicaDeEntrada == 0){
        fluxoMaqEntrada = FLUXO_DE_INSUCESSO;   
        functionPointerEntrada = (int8_t(*)(void)) maqMovimentoEntrada[estadoAtual].action;
        delayLogicaDeEntrada = tick_getTimerCounter_ms() + maqMovimentoEntrada[estadoAtual].wait_ms;
        flagIniciarContadorDelayEntrada = SIM;
    }
    
    if( flagDelayEntradaCompleto == NAO )
    {
        fluxoMaqEntrada = (*functionPointerEntrada)();
    }
    else{
        delayLogicaDeEntrada = 0;
        estadoAtual = maqMovimentoEntrada[estadoAtual].next[fluxoMaqEntrada];
        flagDelayEntradaCompleto = NAO;
    }    
}

uint16_t estadoAtual_saida = LER_ANTENA;
uint16_t fluxoMaqSaida = FLUXO_DE_SUCESSO;

void logicaDeMovimentoDeSaida(void){
        
    if( delayLogicaDeSaida == 0){
        fluxoMaqSaida = FLUXO_DE_INSUCESSO;   
        functionPointerSaida = (int8_t(*)(void)) maqMovimentoSaida[estadoAtual_saida].action;
        delayLogicaDeSaida = tick_getTimerCounter_ms() + maqMovimentoSaida[estadoAtual_saida].wait_ms;
        flagIniciarContadorDelaySaida = SIM;
    }
    
    if( flagDelaySaidaCompleto == NAO )
    {
        fluxoMaqSaida = (*functionPointerSaida)();
    }
    else{
        delayLogicaDeSaida = 0;
        estadoAtual_saida = maqMovimentoSaida[estadoAtual_saida].next[fluxoMaqSaida];
         flagDelaySaidaCompleto = NAO;
    }    
}

int main(void){
            
    SYSTEM_Initialize();
    
    marsOne_init();         
     
    obtemDadosDaMemoriaFLASH();
    
    obtemParametrosDaMemoriaEEPROM();
    
    inicializaMaquinaDeEstados_ESP8266();   
    
    inicializaMaquinaDeEstados_TabelaDeEstacionamento();
    
    inicializaMaquinaDeEstados_DataHora();
    
    inicializaMaquinaDeEstados_KeepAlive(); 
                    
    while(1){
        
        // Logica implementada considerando uma gaiola com clausura
        
        if(movimentoSendoRealizado_Saida == NAO){
            logicaDeMovimentoDeEntrada();
        }
        if(movimentoSendoRealizado_Entrada == NAO){
            logicaDeMovimentoDeSaida();
        }
    }
    
    return 0;
}




