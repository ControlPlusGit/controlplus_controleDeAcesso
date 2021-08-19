///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINE - MÁQUINA DE ESTADOS FINITOS PARA EVENTOS DE EMPILHADEIRA
// EMPRESA: CONTROL + PLUS
// AUTOR: Vitor M. dos S. Alho
// DATA: 07/02/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <uart.h>
//#include "../../../../../../../../Program Files (x86)/Microchip/xc16/v1.24/support/peripheral_24F/uart.h"
//#include "FSM_Ethernet.h"
#include "timer.h"
#include "FSM_EventosDePassagem.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "EEPROM/eeprom.h"
#include "uart_driver.h"
#include "eventos.h"
#include "USR_TCP232.h"


enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        ENVIAR_MENSAGEM,
        AGUARDANDO_ACK,
        ESCOLHER_SERVIDOR_01_COMO_DESTINATARIO,
        ESCOLHER_SERVIDOR_02_COMO_DESTINATARIO,
        LER_MENSAGEM_NA_EEPROM,
        ESCREVER_NA_EEPROM,
        LER_VARS_EEPROM,
        FIM_CICLO
}estados;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: maquinaDeEstadosLiberada_EventosDePassagem
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_EventosDePassagem  = 0;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_MENSAGEM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int delay = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eepromInicializada
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazenar se a eeprom foi inicializada. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char eepromInicializada = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: idLeitor
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena id do leitor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eventosDePassagemArmazenados
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem, executaMaquinaDeEstados_EventosDePassagem e criarEventoDePassagem
// FUNÇÃO: armazena o valor de quantos eventos foram armazenados até o momento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //unsigned int eventosDePassagemArmazenados = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eventosDePassagemEnviados
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem e executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena o valor de quantos eventos foram enviados para o servidor até o momento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int eventosDePassagemEnviados = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringMensagemEvento
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagem
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringMensagemEvento[300];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: novoEventoDePassagem
// UTILIZADA EM: executaMaquinaDeEstado_EventosDePassagem
// FUNÇÃO: armazena os eventos lidos da EEPROM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    eventoPassagem novoEventoDePassagem;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNÇÕES      /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void incrementaContadorExecucao_EventosDePassagem(void){
        delay++;
    }
    
    void zeraContadorExecucao_EventosDePassagem(void){
        delay = 0;
    }
    
    void habilitaMaquinaDeEstados_EventosDePassagem(void){
            //enviarMensagem = ENVIAR_MENSAGEM;
            maquinaDeEstadosLiberada_EventosDePassagem = SIM;
        }

    void bloqueiaMaquinaDeEstados_EventosDePassagem(void){
            maquinaDeEstadosLiberada_EventosDePassagem = 0;
        }

    void limpaBufferNaMaquinaDeEstados_EventosDePassagem(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }



 

    void executaMaquinaDeEstados_EventosDePassagem(void){     
        unsigned char temp=0;
        
        char* msgStartPosition;
        int msgPosition;

        incrementaContadorExecucao_EventosDePassagem();
        
        switch(estadoAtual)
        {
            case AGUARDANDO_TAREFA:      
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM){ 
                    zeraContadorExecucao_EventosDePassagem();
                    
                    if(maquinaDeEstadosLiberada_EventosDePassagem){   
                        estadoAtual=LER_VARS_EEPROM;
                        estadoAnterior=AGUARDANDO_TAREFA;   
                    }      
                }
            break;
            case LER_VARS_EEPROM: 
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM){  
                    zeraContadorExecucao_EventosDePassagem();
                    if(maquinaDeEstadosLiberada_EventosDePassagem){                

                        if(eventosDePassagemArmazenados >= NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS){
                            eventosDePassagemArmazenados = 0;
                        }                               

                        if(eventosDePassagemEnviados >= NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS){ 
                            eventosDePassagemEnviados = 0;
                        }

                        if(eventosDePassagemEnviados != eventosDePassagemArmazenados){ 
                            estadoAtual=LER_MENSAGEM_NA_EEPROM;
                            estadoAnterior=LER_VARS_EEPROM; 
                        }                             
                    }    
                }
            break;
            case LER_MENSAGEM_NA_EEPROM:   
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM){  
                    zeraContadorExecucao_EventosDePassagem();
                    if(maquinaDeEstadosLiberada_EventosDePassagem){                
                        //WriteUART2('T');    

                        lerEventoDePassagemNaEEPROM(&novoEventoDePassagem,(ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS+(eventosDePassagemEnviados*TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES)));

                        estadoAtual=ENVIAR_MENSAGEM;
                        estadoAnterior=LER_MENSAGEM_NA_EEPROM; 
                    }                       
                }
            break;
            case ENVIAR_MENSAGEM:   
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM){  
                    zeraContadorExecucao_EventosDePassagem();
                    if(maquinaDeEstadosLiberada_EventosDePassagem){  
                            
                        //if(setaURLEnvioDeEventos()){
                            sprintf(stringMensagemEvento,"parametro=[FF;%c%c%c%c%c%c;%c;%c%c%c%c;%02d%02d%02d;%02d%02d%02d]",
                                    idLeitor[0],idLeitor[1],idLeitor[2],idLeitor[3],idDoLeitor[4],idDoLeitor[5],
                                    (novoEventoDePassagem.tipoMovimento == MOVIMENTO_ENTRADA ? 'E':'S'),
                                    novoEventoDePassagem.EPC_veiculo[0],novoEventoDePassagem.EPC_veiculo[1],novoEventoDePassagem.EPC_veiculo[2],novoEventoDePassagem.EPC_veiculo[3],
                                    novoEventoDePassagem.dia,novoEventoDePassagem.mes,novoEventoDePassagem.ano,
                                    novoEventoDePassagem.hora,novoEventoDePassagem.minuto,novoEventoDePassagem.segundo);

                            escreverMensagemEthernet(stringMensagemEvento); 
                            //escreverMensagemWifi(stringMensagemEvento); 
                            //escreverMensagemUSB(stringMensagemEvento);
                            
                            estadoAtual=AGUARDANDO_ACK;
                            estadoAnterior=ENVIAR_MENSAGEM;
                        //}     
                    }    
                }
            break;
            case AGUARDANDO_ACK:   
                if(delay < TEMPO_AGUARDANDO_ACK_EVENTOS_DE_PASSAGEM){  
                    if(maquinaDeEstadosLiberada_EventosDePassagem){
                        
                        msgStartPosition = strstr(bufferInterrupcaoUART4,"[FF;OK]");                                              
                        
                        if(msgStartPosition != 0){
                            
                            msgPosition = (int) (msgStartPosition - bufferInterrupcaoUART4);         
                            
                            zeraContadorExecucao_EventosDePassagem();
                           
                            limpaBufferNaMaquinaDeEstados_EventosDePassagem();
                            estadoAtual = FIM_CICLO;
                            estadoAnterior = AGUARDANDO_ACK; 
                        }          
                        else{
                            msgStartPosition = strstr(bufferInterrupcaoUART4,"[FF;NOK]");                                              
                        
                            if(msgStartPosition != 0){
                                limpaBufferNaMaquinaDeEstados_EventosDePassagem();
                                estadoAtual = FIM_CICLO;
                                estadoAnterior = AGUARDANDO_ACK;  
                            }
                        }
                    }                    
                }
                else{
                    zeraContadorExecucao_EventosDePassagem();
                    estadoAtual=ENVIAR_MENSAGEM;
                    estadoAnterior=AGUARDANDO_ACK; 
                }
            break;
            case FIM_CICLO:    
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM){
                    zeraContadorExecucao_EventosDePassagem();
                    if(maquinaDeEstadosLiberada_EventosDePassagem){
                        eventosDePassagemEnviados++;
                        temp = (unsigned char)(eventosDePassagemEnviados>>8);
                        EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS,temp);
                        temp = (unsigned char)eventosDePassagemEnviados & 0x00FF;
                        EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS,temp);                
                        estadoAtual=LER_VARS_EEPROM;
                        estadoAnterior=FIM_CICLO;
                    }                    
                }
            break;        
            default:
            break;
        }
    }

    

