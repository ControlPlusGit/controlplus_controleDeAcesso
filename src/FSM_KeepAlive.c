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
#include "system.h"
#include "FSM_TabelaDeEstacionamento.h"

#define NAO 0
#define SIM 1
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: controlar o tempo de execução de cada estado da máquina, aplicando um delay.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #define TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE 100 // MILISEGUNDOS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: controlar o tempo em que a maquina fica aguardando um ACK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    //#define TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE 300000ULL  // MILISEGUNDOS
    #define TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE 2000  // MILISEGUNDOS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_ENTRE_KEEP_ALIVE
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: controlar o tempo em que o keep alive eh enviado ao sistema
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    //#define TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE 300000ULL  // MILISEGUNDOS
    #define TEMPO_ENTRE_KEEP_ALIVE 1  // MINUTOS

enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        INICIA_CONEXAO_TCP_CLIENT,
        AGUARDANDO_INICIA_CONEXAO_TCP_CLIENT,
        INICIA_ENVIO_DE_DADOS_PARA_SERVER,
        AGUARDANDO_INICIA_ENVIO_DE_DADO_PARA_SERVER,
        ENVIAR_KEEP_ALIVE,        
        AGUARDANDO_KEEP_ALIVE,
        FINALIZA_CONEXAO_TCP,
        AGUARDANDO_FINALIZA_CONEXAO_TCP,
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
    
    
    extern char ESP8266_inicializado;
    
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
            //obtemIdDoLeitor();
            //retornaIdDoLeitor(idLeitor_KeepAlive);
        }
        habilitaMaquinaDeEstados_KeepAlive();
    }
    
    void incrementaContadorExecucao_FSM_KeepAlive(void){
        delayExecucao_KeepAlive++;
    }
    
    void zeraContadorExecucao_FSM_KeepAlive(void){
        delayExecucao_KeepAlive = 0;
    }
    
    uint8_t minuto_atual = 0;
    
    void executaMaquinaDeEstados_KeepAlive(void){     
       
        char* msgStartPosition;
        int msgPosition;
        int numMaiorQueZeroEncontrado;
        
        if(minuto_atual == 0 && maquinaDeEstadosLiberada_KeepAlive == NAO){
            minuto_atual = tick_getTimerCounter_min();
        }
        else{
            if(minuto_atual + TEMPO_ENTRE_KEEP_ALIVE <= tick_getTimerCounter_min() && maquinaDeEstadosLiberada_KeepAlive == NAO){
                minuto_atual = 0;
                habilitaMaquinaDeEstados_KeepAlive();
            }
        }
        
        incrementaContadorExecucao_FSM_KeepAlive();
        
        switch(estadoAtual_KeepAlive)
        {
            case AGUARDANDO_TAREFA:   
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){  
                    zeraContadorExecucao_FSM_KeepAlive();                    
                              
                    if(maquinaDeEstadosLiberada_KeepAlive){     
                        //wifiBusy = SIM;
                        estadoAtual_KeepAlive = ENVIAR_KEEP_ALIVE;
                        estadoAnterior_KeepAlive = AGUARDANDO_TAREFA;   
                    }                           
                }
            break;

            case INICIA_CONEXAO_TCP_CLIENT:
                               
            break;
            case AGUARDANDO_INICIA_CONEXAO_TCP_CLIENT:
                
            break;
                
            case INICIA_ENVIO_DE_DADOS_PARA_SERVER:
                               
            break;
            case AGUARDANDO_INICIA_ENVIO_DE_DADO_PARA_SERVER:
                               
            break;
                        
            case ENVIAR_KEEP_ALIVE:  
                
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){
                    zeraContadorExecucao_FSM_KeepAlive();                                  
                    
                    if(maquinaDeEstadosLiberada_KeepAlive){  
                        sprintf(stringSolicitacaoKeepAlive,"GET /tag/php/apifd.php?parametro=[FD;%c%c%c%c%c%c;A0] HTTP/1.1\r\nHost: www.portarianota10.com.br\r\n\r\n",
                                idDoLeitor[0],
                                idDoLeitor[1],
                                idDoLeitor[2],
                                idDoLeitor[3],
                                idDoLeitor[4],
                                idDoLeitor[5]); 
                        escreverMensagemWifi(stringSolicitacaoKeepAlive);
                        
                        estadoAtual_KeepAlive=AGUARDANDO_KEEP_ALIVE;
                        estadoAnterior_KeepAlive=ENVIAR_KEEP_ALIVE; 
                
                    } 
                }
                
            break;
            case AGUARDANDO_KEEP_ALIVE:
                
                if(delayExecucao_KeepAlive < TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE){
                    
                    if(maquinaDeEstadosLiberada_KeepAlive){
                        msgStartPosition = strstr(bufferInterrupcaoUART4,"[FD;OK;");    
                        
                        if(msgStartPosition != 0){
                            msgPosition = (int) (msgStartPosition - bufferInterrupcaoUART4);                                
                            numMaiorQueZeroEncontrado = NAO;  
                
                            if(*(msgStartPosition+7) == 'S'){
                                inicializaMaquinaDeEstados_TabelaDeEstacionamento();
                            }
                                             
                            resetarErrosDeTimeoutNoWifi(); 
                            limpaBufferNaMaquinaDeEstados_KeepAlive(); 
                            estadoAtual_KeepAlive = FIM_CICLO;
                            estadoAnterior_KeepAlive = AGUARDANDO_KEEP_ALIVE;                             
                        }
                        else{ // SE NAO RECEBER MENSAGEM OK
                            //ESP8266_inicializado = NAO; //MARCOS - REINICIA MODULO WIFI
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
            
            case FINALIZA_CONEXAO_TCP:
                               
            break;
            case AGUARDANDO_FINALIZA_CONEXAO_TCP:
                               
            break;
            
            case FIM_CICLO: 
                //TESTE DA BIBLIOTECA DE BUSCA DA TABELA DE EXCLUSAO
                               
                if(delayExecucao_KeepAlive > TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE){
                    if(maquinaDeEstadosLiberada_KeepAlive){
                        zeraContadorExecucao_FSM_KeepAlive();

                        //sprintf(mensagemParaDebug,"FSM_KeepAlive finalizando...\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);
                        bloqueiaMaquinaDeEstados_KeepAlive();
                        estadoAtual_KeepAlive=AGUARDANDO_TAREFA;
                        estadoAnterior_KeepAlive=FIM_CICLO;
                        //wifiBusy = NAO;
                    }      
                }                
            break;        
            default:
            break;
        }
    }

