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
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;     // lista principal ordenada com as tags lidas
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberadosTest; // utilizada para check na gravacao de dados na flash
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Entrada; // lista desordenada com as tags em movimento
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Saida; // lista desordenada com as tags em movimento
    
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

void marsOne_init(void);
uint8_t realizaLeituraDeAntena(uint8_t antena);
int8_t obtemDadosDaMemoriaFLASH(void);

int8_t ler_antena_entrada(void);
int8_t verificaTagValida_entrada(uint8_t *tag);
int8_t ler_antena_durante_movimento_entrada(uint8_t movimento);
int8_t verificarTagValida_entrada(void);
int8_t verificarTagPresenteNaGreenList_entrada(void);
int8_t abrirPortao1DesligarPortao2_entrada(void);
int8_t aguardaFechamentoPortao1_entrada(void);
int8_t abrirPortao2DesligarPortao1_entrada(void);
int8_t aguardaFechamentoPortao2_entrada(void);
int8_t registraEventoEntrada_entrada(void);
int8_t registraEventoSaida_entrada(void);
int8_t fim_entrada(void);

int8_t ler_antena_saida(void);
int8_t verificaTagValida_saida(uint8_t *tag);
int8_t ler_antena_durante_movimento_saida(uint8_t movimento);
int8_t verificarTagValida_saida(void);
int8_t verificarTagPresenteNaGreenList_saida(void);
int8_t abrirPortao1DesligarPortao2_saida(void);
int8_t aguardaFechamentoPortao1_saida(void);
int8_t abrirPortao2DesligarPortao1_saida(void);
int8_t aguardaFechamentoPortao2_saida(void);
int8_t registraEventoEntrada_saida(void);
int8_t registraEventoSaida_saida(void);
int8_t fim_saida(void);
    
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
        for( i = 3; i < EPCLENGTH-1; i++){            
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

EPC_Estacionamento epcLido;

#define MOVIMENTO_SAIDA 0
#define MOVIMENTO_ENTRADA 1
#define MOVIMENTO_ENTRADA_SAIDA 2
#define MOVIMENTO_SAIDA_ENTRADA 3

#define SAIDA_PORTAO_ENTRADA RELAY_1
#define SAIDA_ALARME_PORTAO_ENTRADA RELAY_3
#define ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA INPUT_1
#define ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA INPUT_3

#define SAIDA_PORTAO_SAIDA RELAY_2
#define SAIDA_ALARME_PORTAO_SAIDA RELAY_4
#define ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA INPUT_2
#define ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA INPUT_4

uint8_t num_of_tags_entrada = 0; 
uint8_t num_of_tags_saida = 0; 

uint8_t numQuebrasBarreiraEntradaSaida = 0;
uint8_t bordaSubidaBarreiraEntradaSaida = 0;

uint8_t numQuebrasBarreiraSaidaEntrada = 0;
uint8_t bordaSubidaBarreiraSaidaEntrada = 0;

uint8_t numQuebrasBarreiraEntrada = 0;
uint8_t bordaSubidaBarreiraEntrada = 0;

uint8_t numQuebrasBarreiraSaida = 0;
uint8_t bordaSubidaBarreiraSaida = 0;

uint8_t alarmeEntradaAcionado = 0;
uint8_t alarmeSaidaAcionado = 0;

int8_t adicionaNovaTagNaLista(TabelaDeEpcDeEstacionamento *lista, EPC_Estacionamento tag){
    if(!buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(lista, tag)){
        adicionarRegistroNaTabelaDeEpcDeEstacionamento(lista, tag);
    }
    return 0;
}
int8_t ler_antena_durante_movimento(uint8_t movimento){    
    switch(movimento){
        case MOVIMENTO_ENTRADA:
                if(!ler_antena_entrada()){
                    if(!verificarTagValida_entrada()){
                        if(!verificarTagPresenteNaGreenList_entrada()){

                        }
                    }
                }   
            break;
        case MOVIMENTO_SAIDA:
                if(!ler_antena_saida()){
                    if(!verificarTagValida_saida()){

                    }
                }
            break;
    }
    return FLUXO_DE_SUCESSO;
}
int8_t detectar_quebra_de_barreira(uint8_t movimento){
    switch(movimento){
        case MOVIMENTO_ENTRADA:
                if(BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA) && !bordaSubidaBarreiraEntrada){
                    bordaSubidaBarreiraEntrada = 1;
                    numQuebrasBarreiraEntrada++;                                                
                }
                else{
                    if(!BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA) && bordaSubidaBarreiraEntrada){
                        bordaSubidaBarreiraEntrada = 0;
                    }
                }
            break;
        case MOVIMENTO_SAIDA:
                if(BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA) && !bordaSubidaBarreiraSaida){
                    bordaSubidaBarreiraSaida = 1;
                    numQuebrasBarreiraSaida++;                                                
                }
                else{
                    if(!BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA) && bordaSubidaBarreiraSaida){
                        bordaSubidaBarreiraSaida = 0;
                    }
                }
            break;
        case MOVIMENTO_ENTRADA_SAIDA:
                if(BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA) && !bordaSubidaBarreiraEntradaSaida){
                    bordaSubidaBarreiraEntradaSaida = 1;
                    numQuebrasBarreiraEntradaSaida++;                                                
                }
                else{
                    if(!BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA) && bordaSubidaBarreiraEntradaSaida){
                        bordaSubidaBarreiraEntradaSaida = 0;
                    }
                }
            break;
        case MOVIMENTO_SAIDA_ENTRADA:
                if(BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA) && !bordaSubidaBarreiraSaidaEntrada){
                    bordaSubidaBarreiraSaidaEntrada = 1;
                    numQuebrasBarreiraSaidaEntrada++;                                                
                }
                else{
                    if(!BSP_readDigitalInput(ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA) && bordaSubidaBarreiraSaidaEntrada){
                        bordaSubidaBarreiraSaidaEntrada = 0;
                    }
                }
            break;
    }
    return FLUXO_DE_SUCESSO;
}

int8_t ler_antena_entrada(void){
            
    num_of_tags_entrada = realizaLeituraDeAntena(ANTENNA_1);   
    
    if(num_of_tags_entrada > 0){             
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }   
}
int8_t verificarTagValida_entrada(void){
    int i;
    uint8_t resultado = FLUXO_DE_INSUCESSO;
    uint8_t num_of_tags = 0;
    
    num_of_tags = num_of_tags_entrada;  
    
    for( i = 0; i < num_of_tags; i++){

        if( verificaTagValida( tags_[i].epc ) > 0 ){ // Tag veicular valida?
            epcLido.byte1 = tags_[i].epc[2];
            epcLido.byte2 = tags_[i].epc[1];
            adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Entrada,epcLido);
        
            resultado = FLUXO_DE_SUCESSO;
        }
        else{
            resultado = FLUXO_DE_INSUCESSO;
        }        
    }    
    return resultado;
}
int8_t verificarTagPresenteNaGreenList_entrada(void){
    
    if( buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epcLido)){ // Veiculo esta na lista?  
        adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Entrada,epcLido);        
        return FLUXO_DE_SUCESSO;    
    }
    else{      
        removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada,epcLido);          
        return FLUXO_DE_INSUCESSO;
    }
}
int8_t abrirPortao1DesligarPortao2_entrada(void){    
    int i;
    int quantTagsLidas = 0;
    
    BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, OFF);
    
    if(BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA) && 
       listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela > 0){    
        if(!BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA)){
            return FLUXO_DE_INSUCESSO;
        }
        if(timerSaida1 == 0){
            flagIniciarContadorTimerSaida1 = SIM;
            timerSaida1 = tick_getTimerCounter_ms() + 200;
        }
        if(flagDelayTimerSaida1Completo == NAO){
            BSP_setRelay(SAIDA_PORTAO_ENTRADA, ON);
            BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);     
        }
        else{
            timerSaida1 = 0;
            flagDelayTimerSaida1Completo = NAO;
        }        
    }
    else{
        BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
        BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
    }    
   
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao1_entrada(void){
    
    ler_antena_durante_movimento(MOVIMENTO_ENTRADA);    
    detectar_quebra_de_barreira(MOVIMENTO_ENTRADA);
   
    BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
    BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
   
    if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA)/* && numQuebrasBarreiraSaidaEntrada == numQuebrasBarreiraSaida*/){
        return FLUXO_DE_SUCESSO;
    }
    else{
        abrirPortao1DesligarPortao2_entrada();  
        return FLUXO_DE_INSUCESSO;
    }
}
int8_t abrirPortao2DesligarPortao1_entrada(void){
    int i;
    int quantTagsLidas = 0;    
    
    quantTagsLidas = listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela;
    if(numQuebrasBarreiraEntrada <= quantTagsLidas){
        if(numQuebrasBarreiraEntrada == quantTagsLidas){

        }
        else{
            for(i = numQuebrasBarreiraEntrada; i < quantTagsLidas; i++){
                listaDeVeiculosLidosDuranteMovimento_Entrada.epc[i].tag = 0; 
                listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela--;                    
            }  
            //listaDeVeiculosLidosDuranteMovimento.ponteiroTabela++; 
        }                     
    }
    else{
        BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, ON);
        alarmeEntradaAcionado = SIM;
        if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA) ){                
            return FLUXO_DE_INSUCESSO;
        }      
    }        
    
    BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, OFF);
    
    if(BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA) && 
      (listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela > 0 || listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela > 0)){    
        
        if(!BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA)){
            return FLUXO_DE_INSUCESSO;
        }
        if(timerSaida2 == 0){
            flagIniciarContadorTimerSaida2 = SIM;
            timerSaida2 = tick_getTimerCounter_ms() + 200;
        }
        if(flagDelayTimerSaida2Completo == NAO){
            BSP_setRelay(SAIDA_PORTAO_SAIDA, ON);
            BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
        }
        else{
            timerSaida2 = 0;
            flagDelayTimerSaida2Completo = NAO;
        }
    }
    else{
        BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
        BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
    }    
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao2_entrada(void){         
   
    detectar_quebra_de_barreira(MOVIMENTO_ENTRADA_SAIDA);
    
    BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
    BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);

    if(listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela < numQuebrasBarreiraEntrada &&
       !BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA) && 
       alarmeEntradaAcionado == SIM){
        numQuebrasBarreiraEntradaSaida = numQuebrasBarreiraEntrada;
    }

    if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA) && 
        numQuebrasBarreiraEntradaSaida == numQuebrasBarreiraEntrada){
        return FLUXO_DE_SUCESSO;
    }
    else{        
        abrirPortao2DesligarPortao1_entrada();        
        return FLUXO_DE_INSUCESSO;
    }
    
    return FLUXO_DE_SUCESSO;
}
int8_t registraEventoEntrada_entrada(void){
    return FLUXO_DE_SUCESSO;
}
int8_t fim_entrada(void){
    num_of_tags_entrada = 0; 
    removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
    numQuebrasBarreiraEntradaSaida = 0;
    numQuebrasBarreiraEntrada = 0;
    numQuebrasBarreiraSaida = 0;   
    alarmeEntradaAcionado = NAO;
    return FLUXO_DE_SUCESSO;
}

int8_t ler_antena_saida(void){ 
            
    num_of_tags_saida = realizaLeituraDeAntena(ANTENNA_2);   
    
    if(num_of_tags_saida > 0){
        return FLUXO_DE_SUCESSO;
    }
    else{
        return FLUXO_DE_INSUCESSO;
    }   
}
int8_t verificarTagValida_saida(void){
    int i;
    uint8_t resultado = FLUXO_DE_INSUCESSO;
    uint8_t num_of_tags = 0;
        
    num_of_tags = num_of_tags_saida;
  
    for( i = 0; i < num_of_tags; i++){

        if( verificaTagValida( tags_[i].epc ) > 0 ){ // Tag veicular valida?
            epcLido.byte1 = tags_[i].epc[2];
            epcLido.byte2 = tags_[i].epc[1];
            adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Saida,epcLido);
            resultado = FLUXO_DE_SUCESSO;
        }
        else{
            resultado = FLUXO_DE_INSUCESSO;
        }        
    }    
    return resultado;
}
int8_t abrirPortao1DesligarPortao2_saida(void){    
    int i;
    int quantTagsLidas = 0;
    
//    if(logicaSaidaExecutando){
//        if(movimentoSendoRealizado_Saida){
//            quantTagsLidas = listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela;
//            if(numQuebrasBarreiraSaida <= quantTagsLidas){
//                if(numQuebrasBarreiraSaida == quantTagsLidas){
//
//                }
//                else{
//                    for(i = numQuebrasBarreiraSaida; i < quantTagsLidas; i++){
//                        listaDeVeiculosLidosDuranteMovimento_Saida.epc[i].tag = 0; 
//                        listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela--;                    
//                    }                      
//                }                     
//            }
//            else{
//                BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, ON);
//
//                if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA) ){                
//                    return FLUXO_DE_INSUCESSO;
//                }      
//            }
//        }
//    }
    
    BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, OFF);
    
    if(BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA) && 
       listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela > 0){    
        if(!BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA)){
            return FLUXO_DE_INSUCESSO;
        }
        if(timerSaida1 == 0){
            flagIniciarContadorTimerSaida1 = SIM;
        }
        if(flagDelayTimerSaida1Completo == NAO){
            BSP_setRelay(SAIDA_PORTAO_ENTRADA, ON);
            BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);     
        }
        else{
            timerSaida1 = 0;
            flagIniciarContadorTimerSaida1 = NAO;
        }        
    }
    else{
        BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
        BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
    }    
   
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao1_saida(void){
    
//    if(logicaSaidaExecutando){
//        detectar_quebra_de_barreira(MOVIMENTO_SAIDA_ENTRADA);
//    }
    
    BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
    BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
    
//    if(logicaSaidaExecutando){
//        if(listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela < numQuebrasBarreiraSaida && !BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA)){
//            numQuebrasBarreiraSaidaEntrada = numQuebrasBarreiraSaida;
//        }
//    }
    
    if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA)/* && numQuebrasBarreiraSaidaEntrada == numQuebrasBarreiraSaida*/){
        return FLUXO_DE_SUCESSO;
    }
    else{
        abrirPortao1DesligarPortao2_saida();  
        return FLUXO_DE_INSUCESSO;
    }
}
int8_t abrirPortao2DesligarPortao1_saida(void){
    int i;
    int quantTagsLidas = 0;
    
    BSP_setRelay(SAIDA_ALARME_PORTAO_ENTRADA, OFF);
    
    if(BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA) && 
      (listaDeVeiculosLidosDuranteMovimento_Saida.ponteiroTabela > 0)){    
        
        if(!BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA)){
            return FLUXO_DE_INSUCESSO;
        }
        if(timerSaida2 == 0){
            flagIniciarContadorTimerSaida2 = SIM;
        }
        if(flagDelayTimerSaida2Completo == NAO){
            BSP_setRelay(SAIDA_PORTAO_SAIDA, ON);
            BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
        }
        else{
            timerSaida2 = 0;
            flagIniciarContadorTimerSaida2 = NAO;
        }
    }
    else{
        BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
        BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);
    }
    
    return FLUXO_DE_SUCESSO;
}
int8_t aguardaFechamentoPortao2_saida(void){
               
    ler_antena_durante_movimento(MOVIMENTO_SAIDA);    
    detectar_quebra_de_barreira(MOVIMENTO_SAIDA);
   
    BSP_setRelay(SAIDA_PORTAO_SAIDA, OFF);
    BSP_setRelay(SAIDA_PORTAO_ENTRADA, OFF);   
    
    if( BSP_readDigitalInput(ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA)/* && numQuebrasBarreiraEntradaSaida == numQuebrasBarreiraEntrada*/ ){
        return FLUXO_DE_SUCESSO;
    }
    else{        
        abrirPortao2DesligarPortao1_saida();        
        return FLUXO_DE_INSUCESSO;
    }
    
    return FLUXO_DE_SUCESSO;
}
int8_t registraEventoSaida_saida(void){
    return FLUXO_DE_SUCESSO;
}
int8_t fim_saida(void){
       
    num_of_tags_saida = 0; 
    removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida);    
    numQuebrasBarreiraSaidaEntrada = 0;
     
    return FLUXO_DE_SUCESSO;
}

Maquina maqMovimentoEntrada[20] = {
                                    [LER_ANTENA]                            = { (uint16_t*)ler_antena_entrada,                      10,  {VERIFICAR_TAG_VALIDA,FIM}                                 },
                                    [VERIFICAR_TAG_VALIDA]                  = { (uint16_t*)verificarTagValida_entrada,              200, {VERIFICAR_TAG_PRESENTE_NA_GREENLIST,FIM}                  },
                                    [VERIFICAR_TAG_PRESENTE_NA_GREENLIST]   = { (uint16_t*)verificarTagPresenteNaGreenList_entrada, 200, {ABRIR_PORTAO1_DESLIGA_PORTAO2,FIM}                        },
                                    [ABRIR_PORTAO1_DESLIGA_PORTAO2]         = { (uint16_t*)abrirPortao1DesligarPortao2_entrada,     5000,{AGUARDA_FECHAMENTO_PORTAO1,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO1]            = { (uint16_t*)aguardaFechamentoPortao1_entrada,        200, {ABRIR_PORTAO2_DESLIGA_PORTAO1,AGUARDA_FECHAMENTO_PORTAO1} },
                                    [ABRIR_PORTAO2_DESLIGA_PORTAO1]         = { (uint16_t*)abrirPortao2DesligarPortao1_entrada,     5000,{AGUARDA_FECHAMENTO_PORTAO2,ABRIR_PORTAO2_DESLIGA_PORTAO1} },
                                    [AGUARDA_FECHAMENTO_PORTAO2]            = { (uint16_t*)aguardaFechamentoPortao2_entrada,        200, {REGISTRA_EVENTO,AGUARDA_FECHAMENTO_PORTAO2}               },
                                    [REGISTRA_EVENTO]                       = { (uint16_t*)registraEventoEntrada_entrada,           200, {LER_ANTENA,FIM}                                           }, 
                                    [FIM]                                   = { (uint16_t*)fim_entrada,                             200, {LER_ANTENA,LER_ANTENA}                                    },
                                  };

Maquina maqMovimentoSaida[20] = {
                                    [LER_ANTENA]                            = { (uint16_t*)ler_antena_saida,                      10,  {VERIFICAR_TAG_VALIDA,FIM}                                 },
                                    [VERIFICAR_TAG_VALIDA]                  = { (uint16_t*)verificarTagValida_saida,              200, {ABRIR_PORTAO2_DESLIGA_PORTAO1,FIM}                        },
                                    [VERIFICAR_TAG_PRESENTE_NA_GREENLIST]   = { 0, 0, {0,0}                                                                                                       },
                                    [ABRIR_PORTAO1_DESLIGA_PORTAO2]         = { (uint16_t*)abrirPortao1DesligarPortao2_saida,     5000,{AGUARDA_FECHAMENTO_PORTAO1,ABRIR_PORTAO1_DESLIGA_PORTAO2} },
                                    [AGUARDA_FECHAMENTO_PORTAO1]            = { (uint16_t*)aguardaFechamentoPortao1_saida,        200, {REGISTRA_EVENTO,AGUARDA_FECHAMENTO_PORTAO1}               },
                                    [ABRIR_PORTAO2_DESLIGA_PORTAO1]         = { (uint16_t*)abrirPortao2DesligarPortao1_saida,     5000,{AGUARDA_FECHAMENTO_PORTAO2,FIM}                           },
                                    [AGUARDA_FECHAMENTO_PORTAO2]            = { (uint16_t*)aguardaFechamentoPortao2_saida,        200, {ABRIR_PORTAO1_DESLIGA_PORTAO2,AGUARDA_FECHAMENTO_PORTAO2} },
                                    [REGISTRA_EVENTO]                       = { (uint16_t*)registraEventoSaida_saida,             200, {LER_ANTENA,FIM}                                           }, 
                                    [FIM]                                   = { (uint16_t*)fim_saida,                             200, {LER_ANTENA,LER_ANTENA}                                    },
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
        
//        if(movimentoSendoRealizado_Saida == NAO){
//            logicaDeMovimentoDeEntrada();
//        }
//        if(movimentoSendoRealizado_Entrada == NAO){
//            logicaDeMovimentoDeSaida();
//        };                
        logicaDeMovimentoDeEntrada();

        logicaDeMovimentoDeSaida();
    }
    
    return 0;
}

// ENTRADA
//1 - 1 Veiculo ameaça de entrar, é lido e vai embora.
//Resultado: OK
//2 - 1 veículo entra na clausura e acessa o condominio
//Resultado: OK
//3 - 1 veículo entra na clausura e não sai a tempo do portão fechar. Então, o portão abre novamente até que ele saia.
//Resultado: OK
//4 - 2 veiculos entram na clausura e ambos tem tag.
//Resultado: OK
//5 - 2 veiculos entram na clausura, ambos tem tag e pelo menos um não sai. O portão abre novamente até todos sairem.
//Resultado: OK
//6 - 2 veiculos entram na clausura e pelo menos um não possui tag (carona)
//Resultado: OK - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.
//7 - 2 veiculos entram na clausura, pelo menos um não possui tag e ambos não saem.
//Resultado: OK - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.
//8 - 2 veiculos entram na clausura, pelo menos um não possui tag e pelo menos um veiculo entra no condominio.
//Resultado: OK - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.

// SAIDA
//1 - 1 Veiculo ameaça de entrar, é lido e vai embora.
//Resultado: OK
//2 - 1 veículo entra na clausura e acessa o condominio
//Resultado: OK
//3 - 1 veículo entra na clausura e não sai a tempo do portão fechar. Então, o portão abre novamente até que ele saia.
//Resultado: OK
//4 - 2 veiculos entram na clausura e ambos tem tag.
//Resultado: OK
//5 - 2 veiculos entram na clausura, ambos tem tag e pelo menos um não sai. O portão abre novamente até todos sairem.
//Resultado: OK
//6 - 2 veiculos entram na clausura e pelo menos um não possui tag (carona)
//Resultado: - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.
//7 - 2 veiculos entram na clausura, pelo menos um não possui tag e ambos não saem.
//Resultado:  - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.
//8 - 2 veiculos entram na clausura, pelo menos um não possui tag e pelo menos um veiculo entra no condominio.
//Resultado:  - A partir do momento que a portaria é notificada, o leitor não mais controla os veículos, até que o portão2 feche.


