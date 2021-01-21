///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINE - MÁQUINA DE ESTADOS FINITOS PARA EVENTOS DE EMPILHADEIRA
// EMPRESA: CONTROL + PLUS
// AUTOR: Vitor M. dos S. Alho
// DATA: 07/02/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <uart.h>
//#include "../../../../../../../../Program Files (x86)/Microchip/xc16/v1.24/support/peripheral_24F/uart.h"
#include "FSM_Ethernet.h"
#include "timer.h"
#include "FSM_ESP8266.h"
#include "FSM_DataHora.h"
#include "uart_driver.h"
#include <stdint.h>
#include "empilhadeira.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "rtc.h"
#include <time.h>

enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        VERIFICA_SE_JA_ATUALIZOU_O_RELOGIO,
        ENVIAR_SOLICITACAO_DATA_HORA,
        AGUARDANDO_ACK,        
        FIM_CICLO
}estados_DataHora;

struct tm objetoDataHora;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: maquinaDeEstadosLiberada_DataHora
// UTILIZADA EM: inicializaMaquinaDeEstados_DataHora
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_DataHora  = NAO;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_DataHora
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_SOLICITACAO_DATA_HORA
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int delayExecucao_DataHora = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar_DataHora
// UTILIZADA EM: inicializaMaquinaDeEstados_DataHora
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar_DataHora = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_DataHora
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual_DataHora = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_DataHora
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior_DataHora = -1;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringSolicitacaoDataHora
// UTILIZADA EM: executaMaquinaDeEstados_DataHora
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringSolicitacaoDataHora[300];
    
    static unsigned char idLeitor_DataHora[20];
    
    
    char horarioFoiAtualizado = NAO;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNÇÕES      /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void habilitaMaquinaDeEstados_DataHora(void){
            //enviarMensagem = ENVIAR_SOLICITACAO_DATA_HORA;
            maquinaDeEstadosLiberada_DataHora = SIM;
        }

    void bloqueiaMaquinaDeEstados_DataHora(void){
            maquinaDeEstadosLiberada_DataHora = NAO;
        }

    void limpaBufferNaMaquinaDeEstados_DataHora(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }

    void inicializaMaquinaDeEstados_DataHora(void){    
        if(leitorAcabouDeLigar_DataHora){
            leitorAcabouDeLigar_DataHora = NAO;
            retornaIdDoLeitor(idLeitor_DataHora);
        }
    }
    
    void incrementaContadorExecucao_FSM_DataHora(void){
        delayExecucao_DataHora++;
    }
    
    void zeraContadorExecucao_FSM_DataHora(void){
        delayExecucao_DataHora = 0;
    }
    
    char funcao_atualizaDataHoraNoRTC_FSM_DataHora_jaExecutou = NAO;
    
    void atualizaDataHoraNoRTC_FSM_DataHora(void){ // isso não pôde ser executado na máquina pois demorava muito.
        if(horarioFoiAtualizado){
            if(!funcao_atualizaDataHoraNoRTC_FSM_DataHora_jaExecutou){  
                funcao_atualizaDataHoraNoRTC_FSM_DataHora_jaExecutou = SIM;
                /*
                SetarHoraRTC(objetoDataHora.tm_sec,
                     objetoDataHora.tm_min,
                     objetoDataHora.tm_hour,
                     objetoDataHora.tm_mday,
                     objetoDataHora.tm_mon,
                     objetoDataHora.tm_year);   */             
            }           
        }        
    }  
        
    void executaMaquinaDeEstados_DataHora(void){     
//        int temp=0;
        char mensagemParaDebug[200];
     
        incrementaContadorExecucao_FSM_DataHora();
        
        switch(estadoAtual_DataHora)
        {
            case AGUARDANDO_TAREFA:   
                if(delayExecucao_DataHora > TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA){  
                    zeraContadorExecucao_FSM_DataHora();
                    
                    sprintf(mensagemParaDebug,"FSM_DataHora aguardando\n\r");
                    //escreverMensagemUSB(mensagemParaDebug);
                                
                    if(maquinaDeEstadosLiberada_DataHora){     
                       
                        //inicializaMaquinaDeEstados_DataHora();

                        sprintf(mensagemParaDebug,"FSM_DataHora liberada\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        estadoAtual_DataHora = VERIFICA_SE_JA_ATUALIZOU_O_RELOGIO;
                        estadoAnterior_DataHora = AGUARDANDO_TAREFA;   
                    }                           
                }
            break;
            case VERIFICA_SE_JA_ATUALIZOU_O_RELOGIO: 

                if(delayExecucao_DataHora > TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA){
                    zeraContadorExecucao_FSM_DataHora();
                    
                    sprintf(mensagemParaDebug,"FSM_DataHora verifica relogio\n\r");
                    //escreverMensagemUSB(mensagemParaDebug);                
                    
                    if(maquinaDeEstadosLiberada_DataHora){  
                        
                        if(!horarioFoiAtualizado){
                            estadoAtual_DataHora = ENVIAR_SOLICITACAO_DATA_HORA;
                            estadoAnterior_DataHora = VERIFICA_SE_JA_ATUALIZOU_O_RELOGIO; 
                        }                              
                    }   
                }
            break;         
            case ENVIAR_SOLICITACAO_DATA_HORA:  
                
                if(delayExecucao_DataHora > TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA){
                    zeraContadorExecucao_FSM_DataHora();
                    sprintf(mensagemParaDebug,"FSM_DataHora enviando solicitacao\n\r");
                    //escreverMensagemUSB(mensagemParaDebug);                
                    
                    if(maquinaDeEstadosLiberada_DataHora){  
                       
                        //if(delayExecucao_DataHora>500){
                        
                        sprintf(stringSolicitacaoDataHora,"<FE;%c%c%c%c>",idLeitor_DataHora[0],idLeitor_DataHora[1],idLeitor_DataHora[2],idLeitor_DataHora[3]);
                        //sprintf(stringSolicitacaoDataHora,"<FE;1302>\n\r");

                        //escreverMensagemEthernet(stringSolicitacaoDataHora);                     
                        escreverMensagemWifi(stringSolicitacaoDataHora);                    
                        //escreverMensagemUSB(stringSolicitacaoDataHora); // para debug da comunicação
                        estadoAtual_DataHora=AGUARDANDO_ACK;
                        estadoAnterior_DataHora=ENVIAR_SOLICITACAO_DATA_HORA; 
                        //}
                    } 
                }
                
            break;
            case AGUARDANDO_ACK:                    
                if(delayExecucao_DataHora < TEMPO_AGUARDANDO_ACK){
                    if(maquinaDeEstadosLiberada_DataHora){
                       if(   bufferInterrupcaoUART4[0]  == '<' && // <OK;20092020;101520>
                             bufferInterrupcaoUART4[1]  == 'F' &&
                             bufferInterrupcaoUART4[2]  == 'E' &&
                             bufferInterrupcaoUART4[3]  == ';' &&
                             bufferInterrupcaoUART4[4]  == 'O' &&
                             bufferInterrupcaoUART4[5]  == 'K' &&
                             bufferInterrupcaoUART4[6]  == ';' &&
                             bufferInterrupcaoUART4[15] == ';' &&
                             bufferInterrupcaoUART4[22] == '>'){         

                             sprintf(mensagemParaDebug,"FSM_DataHora confirmacao recebida\n\r");
                             //escreverMensagemUSB(mensagemParaDebug);
                             objetoDataHora.tm_mday = (bufferInterrupcaoUART4[7]  - '0') * 10 + (bufferInterrupcaoUART4[8]  - '0');  
                             objetoDataHora.tm_mon  = ((bufferInterrupcaoUART4[9]  - '0') * 10 + (bufferInterrupcaoUART4[10]  - '0'));
                             objetoDataHora.tm_year = ((bufferInterrupcaoUART4[13] - '0') * 10 + (bufferInterrupcaoUART4[14] - '0'));
                             objetoDataHora.tm_hour = ((bufferInterrupcaoUART4[16] - '0') * 10 + (bufferInterrupcaoUART4[17] - '0'));
                             objetoDataHora.tm_min  = ((bufferInterrupcaoUART4[18] - '0') * 10 + (bufferInterrupcaoUART4[19] - '0'));
                             objetoDataHora.tm_sec  = ((bufferInterrupcaoUART4[20] - '0') * 10 + (bufferInterrupcaoUART4[21] - '0'));
                                                                                     
                             limpaBufferNaMaquinaDeEstados_DataHora(); 
                             estadoAtual_DataHora = FIM_CICLO;
                             estadoAnterior_DataHora = AGUARDANDO_ACK; 
                             resetarErrosDeTimeoutNoWifi();
                         }                       
                    }  
                }
                else{
                    ocorreuErroDeTimeoutNoWifi();
                    zeraContadorExecucao_FSM_DataHora();
                    estadoAtual_DataHora=ENVIAR_SOLICITACAO_DATA_HORA;
                    estadoAnterior_DataHora=AGUARDANDO_ACK;                                          
                }
            break;
            case FIM_CICLO: 
                if(delayExecucao_DataHora > TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA){
                    if(maquinaDeEstadosLiberada_DataHora){
                        zeraContadorExecucao_FSM_DataHora();

                        sprintf(mensagemParaDebug,"FSM_DataHora finalizando...\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        horarioFoiAtualizado = SIM;
                        
                        //SetarHoraRTC (int segundo, int minuto, int hora, int dia, int mes, int ano)                        
                        //Epoch = mktime(objetoDataHora);
                        //SetaTempoComEpoch(Epoch);
                        //operacoesParaRtcEmCodigoCorrente();
                        SetarHoraRTC(objetoDataHora.tm_sec,objetoDataHora.tm_min,objetoDataHora.tm_hour,objetoDataHora.tm_mday,objetoDataHora.tm_mon,objetoDataHora.tm_year);   
                        
                        //SetarHoraRTC(10,10,10,10,10,10); 
                        bloqueiaMaquinaDeEstados_DataHora();

                        estadoAtual_DataHora=AGUARDANDO_TAREFA;
                        estadoAnterior_DataHora=FIM_CICLO;
                    }      
                }                
            break;        
            default:
            break;
        }
    }

