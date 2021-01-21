///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINE - MÁQUINA DE ESTADOS FINITOS PARA TABELA DE EXCLUSÃO
// EMPRESA: CONTROL + PLUS
// AUTOR: Vitor M. dos S. Alho
// DATA: 13/02/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <uart.h>
#include "FSM_Ethernet.h"
#include "timer.h"
#include "FSM_TabelaDeExclusao.h"
#include "uart_driver.h"
#include <stdint.h>
#include "empilhadeira.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "rtc.h"
#include <time.h>
#include "tabelaDeExclusao.h"
#include "FSM_ESP8266.h"

enum estadosDaMaquina{
        AGUARDANDO_TAREFA=0,
        ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO,        
        AGUARDANDO_TABELA_DE_EXCLUSAO,        
        FIM_CICLO
}estados_TabelaDeExclusao;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: maquinaDeEstadosLiberada_TabelaDeExclusao
// UTILIZADA EM: inicializaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_TabelaDeExclusao  = NAO;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeExclusao, incrementaContadorExecucao_FSM_TabelaDeExclusao e zeraContadorExecucao_FSM_TabelaDeExclusao
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int delayExecucao_TabelaDeExclusao = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar_TabelaDeExclusao
// UTILIZADA EM: inicializaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar_TabelaDeExclusao = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual_TabelaDeExclusao = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior_TabelaDeExclusao = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringSolicitacaoTabelaDeExclusao
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringSolicitacaoTabelaDeExclusao[300];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: idLeitor_TabelaDeExclusao
// UTILIZADA EM: executaMaquinaDeEstados_TabelaDeExclusao
// FUNÇÃO: armazenar o ID do leitor para uso da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char idLeitor_TabelaDeExclusao[20];   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNÇÕES      /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void habilitaMaquinaDeEstados_TabelaDeExclusao(void){
            //enviarMensagem = ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO;
            maquinaDeEstadosLiberada_TabelaDeExclusao = SIM;
        }

    void bloqueiaMaquinaDeEstados_TabelaDeExclusao(void){
            maquinaDeEstadosLiberada_TabelaDeExclusao = NAO;
        }

    void limpaBufferNaMaquinaDeEstados_TabelaDeExclusao(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }

    void inicializaMaquinaDeEstados_TabelaDeExclusao(void){    
        if(leitorAcabouDeLigar_TabelaDeExclusao){
            leitorAcabouDeLigar_TabelaDeExclusao = NAO;
            retornaIdDoLeitor(idLeitor_TabelaDeExclusao);
        }
    }
    
    void incrementaContadorExecucao_FSM_TabelaDeExclusao(void){
        delayExecucao_TabelaDeExclusao++;
    }
    
    void zeraContadorExecucao_FSM_TabelaDeExclusao(void){
        delayExecucao_TabelaDeExclusao = 0;
    }
    void executaMaquinaDeEstados_TabelaDeExclusao(void){     
        //int temp=0;
//        char mensagemParaDebug[300];
        // variáveis utilizadas na aritmética para tratar a tabela de exclusão
        int i=0,j=0,numDigitos=0,multiplicarPor10=1; 
        int bufferOperacoesMatematicas[10];
        int numRegistrosTabelaDeExclusao = 0;
        int numeroDeRegistrosProcessados=0;
        
        //char tabelaDeExclusao[800][4];
        //char epcPedestre[8];        
        EPC novoEPC;
        char epcTemp[20];
      
        incrementaContadorExecucao_FSM_TabelaDeExclusao();
        
        switch(estadoAtual_TabelaDeExclusao)
        {
            case AGUARDANDO_TAREFA:   
                if(delayExecucao_TabelaDeExclusao > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_EXCLUSAO){  
                    zeraContadorExecucao_FSM_TabelaDeExclusao();                    
                            
                    //sprintf(mensagemParaDebug,"FSM_TabelaDeExclusao aguardando\n\r");
                    //escreverMensagemUSB(mensagemParaDebug);
                                
                    if(maquinaDeEstadosLiberada_TabelaDeExclusao){     
                                               
                        //inicializaMaquinaDeEstados_TabelaDeExclusao();

                        //sprintf(mensagemParaDebug,"FSM_TabelaDeExclusao liberada\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        estadoAtual_TabelaDeExclusao = ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO;
                        estadoAnterior_TabelaDeExclusao = AGUARDANDO_TAREFA;   
                    }                           
                }
            break;            
            case ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO:  
                
                if(delayExecucao_TabelaDeExclusao > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_EXCLUSAO){
                    zeraContadorExecucao_FSM_TabelaDeExclusao();
                    
                    //sprintf(mensagemParaDebug,"FSM_TabelaDeExclusao enviando solicitacao\n\r");
                    //escreverMensagemUSB(mensagemParaDebug);                
                    
                    if(maquinaDeEstadosLiberada_TabelaDeExclusao){  
                       
                        //if(delayExecucao_TabelaDeExclusao>500){
                        
                        sprintf(stringSolicitacaoTabelaDeExclusao,"<E2;%c%c%c%c;%c%c%c%c%c%c%c%c>",
                                idLeitor_TabelaDeExclusao[0],idLeitor_TabelaDeExclusao[1],
                                idLeitor_TabelaDeExclusao[2],idLeitor_TabelaDeExclusao[3],
                                ((areaDoVeiculo.byte4>>4)+'0'),((areaDoVeiculo.byte4&0x0f)+'0'),((areaDoVeiculo.byte3>>4)+'0'),((areaDoVeiculo.byte3&0x0f)+'0'),((areaDoVeiculo.byte2>>4)+'0'),((areaDoVeiculo.byte2&0x0f)+'0'),((areaDoVeiculo.byte1>>4)+'0'),((areaDoVeiculo.byte1&0x0f)+'0'));
                        //sprintf(stringSolicitacaoTabelaDeExclusao,"<FE;1302>\n\r");
                        
                        //escreverMensagemUSB(stringSolicitacaoTabelaDeExclusao); // para debug da comunicação
                        //escreverMensagemEthernet(stringSolicitacaoTabelaDeExclusao);
                        escreverMensagemWifi(stringSolicitacaoTabelaDeExclusao);
                        
                        estadoAtual_TabelaDeExclusao=AGUARDANDO_TABELA_DE_EXCLUSAO;
                        estadoAnterior_TabelaDeExclusao=ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO; 
                        //}
                    } 
                }
                
            break;
            case AGUARDANDO_TABELA_DE_EXCLUSAO: 
                
                if(delayExecucao_TabelaDeExclusao < TEMPO_AGUARDANDO_TABELA_DE_EXCLUSAO_FSM_TABELA_DE_EXCLUSAO){
                    if(maquinaDeEstadosLiberada_TabelaDeExclusao){
                       if(  bufferInterrupcaoUART4[0]  == '<' && // <E2;OK;1;30000100>
                            bufferInterrupcaoUART4[1]  == 'E' &&
                            bufferInterrupcaoUART4[2]  == '2' &&
                            bufferInterrupcaoUART4[3]  == ';' &&
                            bufferInterrupcaoUART4[4]  == 'O' &&
                            bufferInterrupcaoUART4[5]  == 'K' &&
                            bufferInterrupcaoUART4[6]  == ';'){         
                           
                            resetarErrosDeTimeoutNoWifi();
                            
                            //escreverMensagemUSB(bufferInterrupcaoUART4);
                            //sprintf(mensagemParaDebug,"FSM_TabelaDeExclusao confirmacao recebida\n\r");
                            //escreverMensagemUSB(mensagemParaDebug);                             
                            //sprintf(bufferInterrupcaoUART4,"<E2;OK;500;30000100;30006000;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30001000;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100;30000100>");
                            //sprintf(bufferInterrupcaoUART4,"<E2;3;30000100;30000100;30000100>");
                            //sprintf(bufferInterrupcaoUART4,"<E2;OK;2;30004000;30006000>");
                                    
                            if(bufferInterrupcaoUART4[7] != '0'){
                                
                                // <E2;OK;2;XXXXXXXX;XXXXXXXX>
                                i=7; // PRIMEIRA POSIÇÃO ONDE COMEÇA O NÚMERO DE REGISTROS
                                while(bufferInterrupcaoUART4[i] != ';' && bufferInterrupcaoUART4[i] != '>'){                                
                                    numDigitos++;
                                    bufferOperacoesMatematicas[i-7] = bufferInterrupcaoUART4[i];                                 
                                    if(i>=8){
                                        multiplicarPor10 *= 10;
                                    }
                                    i++;
                                }     
                                for(i=0;i<numDigitos;i++){
                                   numRegistrosTabelaDeExclusao += (bufferOperacoesMatematicas[i]-'0') * multiplicarPor10;
                                   multiplicarPor10 /= 10;
                                }          

                                i=7+numDigitos; // POSIÇÃO DO PRIMEIRO PONTO E VÍRGULA ANTES DOS EPCS NO VETOR bufferInterrupcaoUART4
                                zeraPointeiroDaTabelaDeExclusao();
                                while(numeroDeRegistrosProcessados < numRegistrosTabelaDeExclusao){  
                                    j=0;            // POSICAO DO VETOR epcPedestre
                                    while(bufferInterrupcaoUART4[i-1] != ';' && bufferInterrupcaoUART4[i-1] != '>'){                                
                                        i+=2;
                                        //tabelaDeExclusao[k][j] = ((bufferInterrupcaoUART4[i-1]-'0') << 4) + (bufferInterrupcaoUART4[i]-'0');   
                                        epcTemp[j] = ((bufferInterrupcaoUART4[i-1]-'0') << 4) + (bufferInterrupcaoUART4[i]-'0');   
                                        j++;                                    
                                    } 
                                    novoEPC.byte4 = epcTemp[0];
                                    novoEPC.byte3 = epcTemp[1];
                                    novoEPC.byte2 = epcTemp[2];
                                    novoEPC.byte1 = epcTemp[3];                                
                                    
                                    adicionarRegistroNaTabelaDeExclusao(novoEPC);                                
                                    i--;    
                                    epcTemp[0]=0;
                                    epcTemp[1]=0;
                                    epcTemp[2]=0;
                                    epcTemp[3]=0;  
                                    numeroDeRegistrosProcessados++;
                                }                                 
                            }
                            else{
                                removerTabelaDeExclusao();
                            }
                            limpaBufferNaMaquinaDeEstados_TabelaDeExclusao(); 
                            estadoAtual_TabelaDeExclusao = FIM_CICLO;
                            estadoAnterior_TabelaDeExclusao = AGUARDANDO_TABELA_DE_EXCLUSAO;                             
                        }
                       else{ // SE NAO RECEBER MENSAGEM OK
                           if(  bufferInterrupcaoUART4[0]  == '<' && // <E2;OK;1;30000100>
                                bufferInterrupcaoUART4[1]  == 'E' &&
                                bufferInterrupcaoUART4[2]  == '2' &&
                                bufferInterrupcaoUART4[3]  == ';' &&
                                bufferInterrupcaoUART4[4]  == 'N' &&
                                bufferInterrupcaoUART4[5]  == 'O' &&
                                bufferInterrupcaoUART4[6]  == 'K' &&
                                bufferInterrupcaoUART4[7]  == ';'){   
                                   limpaBufferNaMaquinaDeEstados_TabelaDeExclusao(); 
                                   resetarErrosDeTimeoutNoWifi();
                                   removerTabelaDeExclusao();
                            }
                       }
                    }  
                }
                else{
                    ocorreuErroDeTimeoutNoWifi();
                    removerTabelaDeExclusao();
                    zeraContadorExecucao_FSM_TabelaDeExclusao();
                    estadoAtual_TabelaDeExclusao=ENVIAR_SOLICITACAO_DE_TABELA_DE_EXCLUSAO;
                    estadoAnterior_TabelaDeExclusao=AGUARDANDO_TABELA_DE_EXCLUSAO;                                          
                }
            break;
            case FIM_CICLO: 
                //TESTE DA BIBLIOTECA DE BUSCA DA TABELA DE EXCLUSAO
                               
                if(delayExecucao_TabelaDeExclusao > TEMPO_ENTRE_ESTADOS_FSM_TABELA_DE_EXCLUSAO){
                    if(maquinaDeEstadosLiberada_TabelaDeExclusao){
                        zeraContadorExecucao_FSM_TabelaDeExclusao();

                        //sprintf(mensagemParaDebug,"FSM_TabelaDeExclusao finalizando...\n\r");
                        //escreverMensagemUSB(mensagemParaDebug);

                        estadoAtual_TabelaDeExclusao=AGUARDANDO_TAREFA;
                        estadoAnterior_TabelaDeExclusao=FIM_CICLO;
                        
                    }      
                }                
            break;        
            default:
            break;
        }
    }

