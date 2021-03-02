///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINE - MÁQUINA DE ESTADOS FINITOS PARA TABELA DE EXCLUSÃO
// EMPRESA: CONTROL + PLUS
// AUTOR: Vitor M. dos S. Alho
// DATA: 13/02/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FSM_Ethernet.h"
#include "timer.h"
#include "FSM_KeepAlive.h"
#include "uart_driver.h"
#include <stdint.h>
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
//#include "rtc.h"
#include <time.h>
#include "FSM_ESP8266.h"

enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        ENVIAR_KEEP_ALIVE,        
        AGUARDANDO_KEEP_ALIVE,        
        FIM_CICLO
}estados_KeepAlive;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: maquinaDeEstadosLiberada_KeepAlive
// UTILIZADA EM: inicializaMaquinaDeEstados_KeepAlive
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_KeepAlive  = NAO;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlive, incrementaContadorExecucao_FSM_KeepAlive e zeraContadorExecucao_FSM_KeepAlive
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_KEEP_ALIVE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint32_t delayExecucao_KeepAlive = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar_KeepAlive
// UTILIZADA EM: inicializaMaquinaDeEstados_KeepAlive
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar_KeepAlive = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlive
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual_KeepAlive = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlive
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior_KeepAlive = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringSolicitacaoKeepAlive
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlive
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringSolicitacaoKeepAlive[300];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: idLeitor_KeepAlive
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlive
// FUNÇÃO: armazenar o ID do leitor para uso da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char idLeitor_KeepAlive[20];   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNCOES     /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void habilitaMaquinaDeEstados_KeepAlive(void){
            //enviarMensagem = ENVIAR_KEEP_ALIVE;
            maquinaDeEstadosLiberada_KeepAlive = SIM;
        }

    void bloqueiaMaquinaDeEstados_KeepAlive(void){
            maquinaDeEstadosLiberada_KeepAlive = NAO;
        }

    void limpaBufferNaMaquinaDeEstados_KeepAlive(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }

    void inicializaMaquinaDeEstados_KeepAlive(void){    
        if(leitorAcabouDeLigar_KeepAlive){
            leitorAcabouDeLigar_KeepAlive = NAO;
            retornaIdDoLeitor(idLeitor_KeepAlive);
        }
        habilitaMaquinaDeEstados_KeepAlive();
    }
    
    void incrementaContadorExecucao_FSM_KeepAlive(void){
        delayExecucao_KeepAlive++;
    }
    
    void zeraContadorExecucao_FSM_KeepAlive(void){
        delayExecucao_KeepAlive = 0;
    }
    void executaMaquinaDeEstados_KeepAlive(void){     
       
        char* msgStartPosition;
        int msgPosition;
        int numMaiorQueZeroEncontrado;
            
        incrementaContadorExecucao_FSM_KeepAlive();
        
        switch(estadoAtual_KeepAlive)
        {
            case AGUARDANDO_TAREFA:   
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){  
                    zeraContadorExecucao_FSM_KeepAlive();                    
                              
                    if(maquinaDeEstadosLiberada_KeepAlive){     
                        
                        estadoAtual_KeepAlive = ENVIAR_KEEP_ALIVE;
                        estadoAnterior_KeepAlive = AGUARDANDO_TAREFA;   
                    }                           
                }
            break;            
            case ENVIAR_KEEP_ALIVE:  
                
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){
                    zeraContadorExecucao_FSM_KeepAlive();                                  
                    
                    if(maquinaDeEstadosLiberada_KeepAlive){  
                      
                        sprintf(stringSolicitacaoKeepAlive,"GET /tag/php/apifd.php?parametro=[FD;000001;A0] HTTP/1.1\r\nHost: www.portarianota10.com.br\r\n\r\n");
                        
                        escreverMensagemWifi(stringSolicitacaoKeepAlive);
                        
                        estadoAtual_KeepAlive=AGUARDANDO_KEEP_ALIVE;
                        estadoAnterior_KeepAlive=ENVIAR_KEEP_ALIVE; 
                
                    } 
                }
                
            break;
            case AGUARDANDO_KEEP_ALIVE:
                
                if(delayExecucao_KeepAlive < TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE){
                    
                    if(maquinaDeEstadosLiberada_KeepAlive){
                        
                        msgStartPosition = strstr(bufferInterrupcaoUART4,"[FD;OK");                                              
                        
                        if(msgStartPosition != 0){
                            
                            msgPosition = (int) (msgStartPosition - bufferInterrupcaoUART4);                                
                           
                            numMaiorQueZeroEncontrado = NAO;    
                                                        
                            resetarErrosDeTimeoutNoWifi();
                                      
                            limpaBufferNaMaquinaDeEstados_KeepAlive(); 
                            estadoAtual_KeepAlive = FIM_CICLO;
                            estadoAnterior_KeepAlive = AGUARDANDO_KEEP_ALIVE;                             
                        }
                       else{ // SE NAO RECEBER MENSAGEM OK
                            
                       }
                    }  
                }
                else{
                    ocorreuErroDeTimeoutNoWifi();
                    //removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados);
                    zeraContadorExecucao_FSM_KeepAlive();
                    estadoAtual_KeepAlive=ENVIAR_KEEP_ALIVE;
                    estadoAnterior_KeepAlive=AGUARDANDO_KEEP_ALIVE;                                          
                }
            break;
            case FIM_CICLO: 
                //TESTE DA BIBLIOTECA DE BUSCA DA TABELA DE EXCLUSAO
                               
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){
                    if(maquinaDeEstadosLiberada_KeepAlive){
                        zeraContadorExecucao_FSM_KeepAlive();

                        //sprintf(mensagemParaDebug,"FSM_KeepAlive finalizando...\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        estadoAtual_KeepAlive=AGUARDANDO_TAREFA;
                        estadoAnterior_KeepAlive=FIM_CICLO;
                        
                    }      
                }                
            break;        
            default:
            break;
        }
    }

