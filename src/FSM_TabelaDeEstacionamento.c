///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINE - MÁQUINA DE ESTADOS FINITOS PARA TABELA DE EXCLUSÃO
// EMPRESA: CONTROL + PLUS
// AUTOR: Vitor M. dos S. Alho
// DATA: 13/02/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FSM_Ethernet.h"
#include "timer.h"
#include "FSM_TabelaDeEstacionamento.h"
#include "uart_driver.h"
#include <stdint.h>
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
//#include "rtc.h"
#include <time.h>
#include "tabelaEstacionamento.h"
#include "FSM_ESP8266.h"
#include "FLASH/flash.h"

#define NAO 0
#define SIM 1
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamentos
// FUNÇÃO: controlar o tempo de execução de cada estado da máquina, aplicando um delay.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #define TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_ESTACIONAMENTO 10 // MILISEGUNDOS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_AGUARDANDO_ACK
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamentos
// FUNÇÃO: controlar o tempo em que a maquina fica aguardando um ACK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    //#define TEMPO_AGUARDANDO_TABELA_DE_EXCLUSAO_FSM_TABELA_DE_ESTACIONAMENTO 300000ULL  // MILISEGUNDOS
    #define TEMPO_AGUARDANDO_TABELA_DE_EXCLUSAO_FSM_TABELA_DE_ESTACIONAMENTO 10000  // MILISEGUNDOS    

extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;

enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        ENVIAR_SOLICITACAO_DE_TABELA_DE_ESTACIONAMENTO,        
        AGUARDANDO_TABELA_DE_ESTACIONAMENTO,        
        FIM_CICLO
}estados_TabelaDeEstacionamento;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: maquinaDeEstadosLiberada_TabelaDeEstacionamento
// UTILIZADA EM: inicializaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_TabelaDeEstacionamento  = NAO;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamento, incrementaContadorExecucao_FSM_TabelaDeEstacionamento e zeraContadorExecucao_FSM_TabelaDeEstacionamento
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    uint32_t delayExecucao_TabelaDeEstacionamento = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar_TabelaDeEstacionamento
// UTILIZADA EM: inicializaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar_TabelaDeEstacionamento = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual_TabelaDeEstacionamento = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior_TabelaDeEstacionamento = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringSolicitacaoTabelaDeEstacionamento
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringSolicitacaoTabelaDeEstacionamento[300];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: idLeitor_TabelaDeEstacionamento
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeEstacionamento
// FUNÇÃO: armazenar o ID do leitor para uso da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char idLeitor_TabelaDeEstacionamento[20];   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNCOES     /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void habilitaMaquinaDeEstados_TabelaDeEstacionamento(void){
            //enviarMensagem = ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO;
            maquinaDeEstadosLiberada_TabelaDeEstacionamento = SIM;
        }

    void bloqueiaMaquinaDeEstados_TabelaDeEstacionamento(void){
            maquinaDeEstadosLiberada_TabelaDeEstacionamento = NAO;
        }

    void limpaBufferNaMaquinaDeEstados_TabelaDeEstacionamento(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }

    void inicializaMaquinaDeEstados_TabelaDeEstacionamento(void){    
        if(leitorAcabouDeLigar_TabelaDeEstacionamento){
            leitorAcabouDeLigar_TabelaDeEstacionamento = NAO;
            retornaIdDoLeitor(idLeitor_TabelaDeEstacionamento);
        }
        habilitaMaquinaDeEstados_TabelaDeEstacionamento();
    }
    
    void incrementaContadorExecucao_FSM_TabelaDeEstacionamento(void){
        delayExecucao_TabelaDeEstacionamento++;
    }
    
    void zeraContadorExecucao_FSM_TabelaDeEstacionamento(void){
        delayExecucao_TabelaDeEstacionamento = 0;
    }
    void executaMaquinaDeEstados_TabelaDeEstacionamento(void){     
        
        int i=0,j=0,k=0,numDigitos=0,multiplicarPor10=1; 
        int bufferOperacoesMatematicas[10];
        int numRegistrosTabelaDeEstacionamento = 0;
        int numeroDeRegistrosProcessados=0;
        
        char* msgStartPosition;
        int msgPosition;
        int numMaiorQueZeroEncontrado;
            
        EPC_Estacionamento novoEPC;
        char epcTemp[20];
      
        incrementaContadorExecucao_FSM_TabelaDeEstacionamento();
        
        switch(estadoAtual_TabelaDeEstacionamento)
        {
            case AGUARDANDO_TAREFA:   
                if(delayExecucao_TabelaDeEstacionamento > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_ESTACIONAMENTO){  
                    zeraContadorExecucao_FSM_TabelaDeEstacionamento();                    
                              
                    if(maquinaDeEstadosLiberada_TabelaDeEstacionamento){     
                        
                        estadoAtual_TabelaDeEstacionamento = ENVIAR_SOLICITACAO_DE_TABELA_DE_ESTACIONAMENTO;
                        estadoAnterior_TabelaDeEstacionamento = AGUARDANDO_TAREFA;   
                    }                           
                }
            break;            
            case ENVIAR_SOLICITACAO_DE_TABELA_DE_ESTACIONAMENTO:  
                
                if(delayExecucao_TabelaDeEstacionamento > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_ESTACIONAMENTO){
                    zeraContadorExecucao_FSM_TabelaDeEstacionamento();                                  
                    
                    if(maquinaDeEstadosLiberada_TabelaDeEstacionamento){  
                      
                        sprintf(stringSolicitacaoTabelaDeEstacionamento,"GET /tag/php/apifb.php?parametro=[FB;%c%c%c%c%c%c] HTTP/1.1\r\nHost: www.portarianota10.com.br\r\n\r\n",
                                idDoLeitor[0],
                                idDoLeitor[1],
                                idDoLeitor[2],
                                idDoLeitor[3],
                                idDoLeitor[4],
                                idDoLeitor[5]);
                       
                        escreverMensagemWifi(stringSolicitacaoTabelaDeEstacionamento);
                        
                        estadoAtual_TabelaDeEstacionamento=AGUARDANDO_TABELA_DE_ESTACIONAMENTO;
                        estadoAnterior_TabelaDeEstacionamento=ENVIAR_SOLICITACAO_DE_TABELA_DE_ESTACIONAMENTO; 
                
                    } 
                }
                
            break;
            case AGUARDANDO_TABELA_DE_ESTACIONAMENTO:
                
                if(delayExecucao_TabelaDeEstacionamento < TEMPO_AGUARDANDO_TABELA_DE_EXCLUSAO_FSM_TABELA_DE_ESTACIONAMENTO){
                    
                    if(maquinaDeEstadosLiberada_TabelaDeEstacionamento){
                        
                        msgStartPosition = strstr(bufferInterrupcaoUART4,"[FB;OK;");                                              
                        
                        if(msgStartPosition != 0){
                            
                            msgPosition = (int) (msgStartPosition - bufferInterrupcaoUART4);                                
                           
                            numMaiorQueZeroEncontrado = NAO;    
                            
                            k = 0;
                            
                            resetarErrosDeTimeoutNoWifi();
                                                                
                            if( bufferInterrupcaoUART4[msgPosition] != '0' ) {
                                
                                // <E2;OK;2;XXXXXXXX;XXXXXXXX>
                                i= msgPosition + 7; // PRIMEIRA POSIÇÃO ONDE COMEÇA O NÚMERO DE REGISTROS
                                while( bufferInterrupcaoUART4[i] != ';' && bufferInterrupcaoUART4[i] != ']' ) {                                
                                    
                                    if( bufferInterrupcaoUART4[i] == '0' && numMaiorQueZeroEncontrado == NAO ) {
                                        
                                    }
                                    else{    
                                        if(!numMaiorQueZeroEncontrado){
                                            numMaiorQueZeroEncontrado = SIM;
                                        }
                                        numDigitos++;
                                        bufferOperacoesMatematicas[k++] = bufferInterrupcaoUART4[i];                                 
                                        if( numDigitos > 1 ){
                                            multiplicarPor10 *= 10;
                                        }                                        
                                    }
                                    i++;
                                }   
                                for(i=0;i<numDigitos;i++){
                                   numRegistrosTabelaDeEstacionamento += (bufferOperacoesMatematicas[i]-'0') * multiplicarPor10;
                                   multiplicarPor10 /= 10;
                                }          
                                // <E2;OK;1000
                                i= msgPosition + 7 + 4;//numDigitos; // POSIÇÃO DO PRIMEIRO PONTO E VÍRGULA ANTES DOS EPCS NO VETOR bufferInterrupcaoUART4
                                zeraPointeiroDaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados);
                                while(numeroDeRegistrosProcessados < numRegistrosTabelaDeEstacionamento){  
                                    j=0;            // POSICAO DO VETOR epcPedestre
                                    while(bufferInterrupcaoUART4[i-1] != ';' && bufferInterrupcaoUART4[i-1] != ']'){                                
                                        i+=2;
                                        //tabelaDeExclusao[k][j] = ((bufferInterrupcaoUART4[i-1]-'0') << 4) + (bufferInterrupcaoUART4[i]-'0');   
                                        epcTemp[j] = ((bufferInterrupcaoUART4[i-1]-'0') << 4) + (bufferInterrupcaoUART4[i]-'0');   
                                        j++;                                    
                                    } 
                                    novoEPC.tag = 0;
                                    novoEPC.byte2 = epcTemp[0];
                                    novoEPC.byte1 = epcTemp[1];                                
                                    
                                    adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, novoEPC);                                
                                    i--;    
                                    epcTemp[0]=0;
                                    epcTemp[1]=0;
                                    epcTemp[2]=0;
                                    epcTemp[3]=0;  
                                    numeroDeRegistrosProcessados++;
                                }                                 
                            }
                            else{
                                //removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados); Nao removo porque a tabela deve persistir no leitor o tempo todo
                            }
                            limpaBufferNaMaquinaDeEstados_TabelaDeEstacionamento(); 
                            estadoAtual_TabelaDeEstacionamento = FIM_CICLO;
                            estadoAnterior_TabelaDeEstacionamento = AGUARDANDO_TABELA_DE_ESTACIONAMENTO;                             
                        }
                       else{ // SE NAO RECEBER MENSAGEM OK
                            /* Nao fazemos nada pois devemos usar a tabela interna para permitir
                             o acesso dos veiculos */
//                            msgStartPosition = strstr(bufferInterrupcaoUART4,"[FB;NOK;");  
//                            if(msgStartPosition != 0){ 
//                                   limpaBufferNaMaquinaDeEstados_TabelaDeEstacionamento(); 
//                                   resetarErrosDeTimeoutNoWifi();
//                                   removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados);
//                            }
                       }
                    }  
                }
                else{
                    ocorreuErroDeTimeoutNoWifi();
                    //removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados);
                    zeraContadorExecucao_FSM_TabelaDeEstacionamento();
                    estadoAtual_TabelaDeEstacionamento=ENVIAR_SOLICITACAO_DE_TABELA_DE_ESTACIONAMENTO;
                    estadoAnterior_TabelaDeEstacionamento=AGUARDANDO_TABELA_DE_ESTACIONAMENTO;                                          
                }
            break;
            case FIM_CICLO: 
                //TESTE DA BIBLIOTECA DE BUSCA DA TABELA DE EXCLUSAO
                               
                if(delayExecucao_TabelaDeEstacionamento > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_ESTACIONAMENTO){
                    if(maquinaDeEstadosLiberada_TabelaDeEstacionamento){
                        zeraContadorExecucao_FSM_TabelaDeEstacionamento();
                        
                        gravarListaDeVeiculosLiberados(); // Grava informa��es na tabela flash
                        bloqueiaMaquinaDeEstados_TabelaDeEstacionamento();
                        //sprintf(mensagemParaDebug,"FSM_TabelaDeEstacionamento finalizando...\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        estadoAtual_TabelaDeEstacionamento=AGUARDANDO_TAREFA;
                        estadoAnterior_TabelaDeEstacionamento=FIM_CICLO;
                        
                    }      
                }                
            break;        
            default:
            break;
        }
    }

