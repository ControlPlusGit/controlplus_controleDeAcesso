/* 
 * File:   FSM_Ethernet.c
 * Author: Vitor
 *
 * Created on 11 de Fevereiro de 2020, 14:29
 */

#include <uart.h>
#include "delay.h"
#include "FSM_Ethernet.h"
#include "uart_driver.h"
#include <string.h>
#include <stdio.h>
#include <libpic30.h>
#include "FSM_ESP8266.h"
#include "setup_usb.h"

#define SIM 1
#define NAO 0

unsigned long long contadorDePerformance=0;

void incrementaContadorDePerformance(void){
    contadorDePerformance++;
}

unsigned long long retornaValorContadorDePerformance(void){
    return contadorDePerformance;
}

void escreverMensagemEthernet(char *data){  
    int pointerAddress = (int) data;
    while(*data != '\0'){
        uart2Tx(*data);
        data++; 
    }
    data = (char*) pointerAddress;
}
/*
    teste de presença
    envia "AT<CR><LF>"
    recebe "OK<CR><LF>"

    ENVIAR MENSAGEM
    envia "AT+CIPSTART="TCP","104.154.47.107",8000<CR><LF>"
    recebe "CONNECT<CR><LF>" 
    recebe "OK<CR><LF>"
    envia "AT+CIPSEND=40<CR><LF>"
    recebe "OK<CR><LF>"
    recebe "SEND OK<CR><LF>"
 */

char interfaceWifiJaFoiConfigurada = NAO;

char mensagemESP8266[100];

void limpaMensagemESP8266(void){
    int i=0;
    for(i=0;i<sizeof(mensagemESP8266);i++){
        mensagemESP8266[i]=0;
    }
}

void escreveMensagemESP8266(char *data){ 
    int pointerAddress = (int) data;
    
    if(debugInterfaceWifi_Silent){
        escreverMensagemUSB(data);
    }  
    
    //data = pointerAddress;
    
    while(*data != '\0'){
        uart4Tx(*data);     
        data++;
    }
    
    data = (char*) pointerAddress;
}

char jaInicializeiESP8266 = NAO;

void iniciaESP8266(void){
    if(!jaInicializeiESP8266){
        jaInicializeiESP8266 = SIM;
        /*
         MENSAGEM
            AT+CWMODE_CUR=MODE\r\n
         ESP8266 MODES
         1 - STATION MODE
         2 - SOFT AP MODE
         3 - STATION / SOFT AP MODE 
        */
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"AT+CWMODE_CUR=1\r\n");
        escreveMensagemESP8266(mensagemESP8266);   
        delay_ms(5000);
        /*
         CONECTAR NA REDE WIFI
        */   
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"AT+CWJAP_CUR=\"LenovoEngenharia\",\"lenovoEngenharia\"\r\n");
        escreveMensagemESP8266(mensagemESP8266);  
        delay_ms(8000);
        /*
         ESTABELECER CONEXÃO COM O SERVIDOR
        */
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"AT+CIPSTART=\"TCP\",\"104.154.47.107\",8000\r\n");
        escreveMensagemESP8266(mensagemESP8266);
        delay_ms(2000);
        
        /*
         DESLIGAR ECHO DE MENSAGENS 
        */
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"ATE0\r\n");
        escreveMensagemESP8266(mensagemESP8266);
        delay_ms(100);
        
        /*
         ENTRA EM MODO TRANSPARENTE
         1 - modo transparente - passthrough
         0 - modo normal
        */        
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"AT+CIPMODE=1\r\n");
        escreveMensagemESP8266(mensagemESP8266);
        delay_ms(100);
        
        /*
         ENVIAR MENSAGEM PARA O SERVIDOR SEM TAMANHO DEFINIDO
         * isso faz com que tudo que seja mandado pela uart
         * seja enviado para o servidor, o mesmo acontece com 
         * as informações vindas do servidor.
        */
        limpaMensagemESP8266(); 
        sprintf(mensagemESP8266,"AT+CIPSEND\r\n");
        escreveMensagemESP8266(mensagemESP8266);
        delay_ms(100);
    }
}

extern unsigned int wifiLiberadoParaUso;

void escreverMensagemWifi(char *data){ 
    int pointerAddress = (int) data;
    if(wifiLiberadoParaUso){
        if(ESP8266_jaFoiInicializado()){
            escreveMensagemESP8266(data);
        }
    }
    data = (char*) pointerAddress;
}

void escreverMensagemUSB(char *data){ 
    int pointerAddress = (int) data;
    
    while(*data != '\0'){
        uart3Tx(*data);
        data++; 
    }    
    data = (char*) pointerAddress;
}