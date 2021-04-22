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
#include "FSM_EventosDePassagem.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "EEPROM/eeprom.h"
#include "uart_driver.h"
#include "eventos.h"


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
    unsigned char idLeitor[20];
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eventosDePassagemArmazenados
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDePassagem, executaMaquinaDeEstados_EventosDePassagem e criarEventoDePassagem
// FUNÇÃO: armazena o valor de quantos eventos foram armazenados até o momento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int eventosDePassagemArmazenados = 0;

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

    void inicializaMaquinaDeEstados_EventosDePassagem(void){
        unsigned char temp=0;
        
        if(eepromInicializada != VALOR_FLAG_INICIALIZACAO_EEPROM){
            LerDadosDaEEprom(ENDERECO_FLAG_INICIALIZACAO_EEPROM,&eepromInicializada);
            if(eepromInicializada != VALOR_FLAG_INICIALIZACAO_EEPROM){
                EscreverNaEEprom(ENDERECO_FLAG_INICIALIZACAO_EEPROM,VALOR_FLAG_INICIALIZACAO_EEPROM);
                EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,0);
                EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,eventosDePassagemArmazenados);
                EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS,0);
                EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS,eventosDePassagemEnviados);
            }
        }

        if(leitorAcabouDeLigar){           
            
            leitorAcabouDeLigar=0;

            LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, &temp);
            eventosDePassagemArmazenados = (unsigned int)temp << 8;
            LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, &temp);
            eventosDePassagemArmazenados |= (unsigned int)temp;

            LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, &temp);
            eventosDePassagemEnviados = (unsigned int)temp << 8;
            LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, &temp);
            eventosDePassagemEnviados |= (unsigned int)temp;

            retornaIdDoLeitor(idLeitor);
        }       
        habilitaMaquinaDeEstados_EventosDePassagem();
    }

    void criarEventoDePassagem(eventoPassagem *_novoEventoDePassagem){
        unsigned int endereco = (eventosDePassagemArmazenados * TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES) + ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS;
        unsigned char temp=0;

        bloqueiaMaquinaDeEstados_EventosDePassagem();
        
        EscreverNaEEprom(endereco,_novoEventoDePassagem->EPC_naoUsado[0]);
        EscreverNaEEprom(endereco+1,_novoEventoDePassagem->EPC_naoUsado[1]);
        EscreverNaEEprom(endereco+2,_novoEventoDePassagem->EPC_naoUsado[2]);
        EscreverNaEEprom(endereco+3,_novoEventoDePassagem->EPC_naoUsado[3]);
        EscreverNaEEprom(endereco+4,_novoEventoDePassagem->EPC_naoUsado[4]);
        EscreverNaEEprom(endereco+5,_novoEventoDePassagem->EPC_naoUsado[5]);
        EscreverNaEEprom(endereco+6,_novoEventoDePassagem->EPC_naoUsado[6]);
        EscreverNaEEprom(endereco+7,_novoEventoDePassagem->EPC_naoUsado[7]);
        EscreverNaEEprom(endereco+8,_novoEventoDePassagem->EPC_veiculo[0]);
        EscreverNaEEprom(endereco+9,_novoEventoDePassagem->EPC_veiculo[1]);
        EscreverNaEEprom(endereco+10,_novoEventoDePassagem->EPC_veiculo[2]);
        EscreverNaEEprom(endereco+11,_novoEventoDePassagem->EPC_veiculo[3]);
        EscreverNaEEprom(endereco+12,_novoEventoDePassagem->EPC_veiculo[4]);
        EscreverNaEEprom(endereco+13,_novoEventoDePassagem->EPC_veiculo[5]);
        EscreverNaEEprom(endereco+14,_novoEventoDePassagem->EPC_veiculo[6]);
        EscreverNaEEprom(endereco+15,_novoEventoDePassagem->EPC_veiculo[7]);
        EscreverNaEEprom(endereco+16,_novoEventoDePassagem->dia);
        EscreverNaEEprom(endereco+17,_novoEventoDePassagem->mes);
        EscreverNaEEprom(endereco+18,_novoEventoDePassagem->ano);
        EscreverNaEEprom(endereco+19,_novoEventoDePassagem->hora);
        EscreverNaEEprom(endereco+20,_novoEventoDePassagem->minuto);
        EscreverNaEEprom(endereco+21,_novoEventoDePassagem->segundo);
        EscreverNaEEprom(endereco+22,_novoEventoDePassagem->tipoMovimento[0]);
        EscreverNaEEprom(endereco+23,_novoEventoDePassagem->tipoMovimento[1]);
        EscreverNaEEprom(endereco+24,_novoEventoDePassagem->tipoMovimento[2]);
        EscreverNaEEprom(endereco+25,_novoEventoDePassagem->tipoMovimento[3]);
        EscreverNaEEprom(endereco+26,_novoEventoDePassagem->tipoMovimento[4]);
        EscreverNaEEprom(endereco+27,_novoEventoDePassagem->tipoMovimento[5]);
        EscreverNaEEprom(endereco+28,_novoEventoDePassagem->tipoMovimento[6]);
        EscreverNaEEprom(endereco+29,_novoEventoDePassagem->tipoMovimento[7]);

        eventosDePassagemArmazenados++;

        temp = (unsigned char)(eventosDePassagemArmazenados>>8);
        EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,temp);
        temp = (unsigned char)eventosDePassagemArmazenados & 0x00FF;
        EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,temp);  
        
        habilitaMaquinaDeEstados_EventosDePassagem();
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
                        //delay++;
                        //if(delay>INTERVALO_ENTRE_TENTATIVAS){
                            sprintf(stringMensagemEvento,"GET /tag/php/apiff.php?parametro=[FF;%c%c%c%c%c%c;%c;%c%c%c%c;%02d%02d%02d;%02d%02d%02d] HTTP/1.1\r\nHost: www.portarianota10.com.br\r\n\r\n",
                                    idLeitor[0],idLeitor[1],idLeitor[2],idLeitor[3],idDoLeitor[4],idDoLeitor[5],
                                    (novoEventoDePassagem.tipoMovimento[0]==MOVIMENTO_ENTRADA ? 'E':'S'),
                                    novoEventoDePassagem.EPC_veiculo[0],novoEventoDePassagem.EPC_veiculo[1],novoEventoDePassagem.EPC_veiculo[2],novoEventoDePassagem.EPC_veiculo[3],
                                    novoEventoDePassagem.dia,novoEventoDePassagem.mes,novoEventoDePassagem.ano,
                                    novoEventoDePassagem.hora,novoEventoDePassagem.minuto,novoEventoDePassagem.segundo);

                            //escreverMensagemEthernet(stringMensagemEvento); 
                            escreverMensagemWifi(stringMensagemEvento); 
                            //escreverMensagemUSB(stringMensagemEvento);
                            
                            estadoAtual=AGUARDANDO_ACK;
                            estadoAnterior=ENVIAR_MENSAGEM;
                            //delay = 0;
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

    void lerEventoDePassagemNaEEPROM(eventoPassagem *evento,int endereco){      
            // LER EPC DO OPERADOR QUE ESTAVA OPERANDO O VEICULO DURANTE O EVENTO
            LerDadosDaEEprom(endereco, &evento->EPC_naoUsado[0]);
            LerDadosDaEEprom(endereco+1, &evento->EPC_naoUsado[1]);
            LerDadosDaEEprom(endereco+2, &evento->EPC_naoUsado[2]);
            LerDadosDaEEprom(endereco+3, &evento->EPC_naoUsado[3]);
            LerDadosDaEEprom(endereco+4, &evento->EPC_naoUsado[4]);
            LerDadosDaEEprom(endereco+5, &evento->EPC_naoUsado[5]);
            LerDadosDaEEprom(endereco+6, &evento->EPC_naoUsado[6]);
            LerDadosDaEEprom(endereco+7, &evento->EPC_naoUsado[7]);
            // LER EPC DO PEDESTRE/OPERADOR/VEICULO PARA O QUAL GEROU O EVENTO
            LerDadosDaEEprom(endereco+8, &evento->EPC_veiculo[0]);
            LerDadosDaEEprom(endereco+9, &evento->EPC_veiculo[1]);
            LerDadosDaEEprom(endereco+10, &evento->EPC_veiculo[2]);
            LerDadosDaEEprom(endereco+11, &evento->EPC_veiculo[3]);
            LerDadosDaEEprom(endereco+12, &evento->EPC_veiculo[4]);
            LerDadosDaEEprom(endereco+13, &evento->EPC_veiculo[5]);
            LerDadosDaEEprom(endereco+14, &evento->EPC_veiculo[6]);
            LerDadosDaEEprom(endereco+15, &evento->EPC_veiculo[7]);
            // LER DIA QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+16, &evento->dia);
            // LER MES QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+17, &evento->mes);
            // LER ANO QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+18, &evento->ano);
            // LER HORA QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+19, &evento->hora);
            // LER MINUTO QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+20, &evento->minuto);
            // LER SEGUNDO QUANDO OCORREU O EVENTO
            LerDadosDaEEprom(endereco+21, &evento->segundo);     
            LerDadosDaEEprom(endereco+22, &evento->tipoMovimento[0]);
            LerDadosDaEEprom(endereco+23, &evento->tipoMovimento[1]);
            LerDadosDaEEprom(endereco+24, &evento->tipoMovimento[2]);
            LerDadosDaEEprom(endereco+25, &evento->tipoMovimento[3]);
            LerDadosDaEEprom(endereco+26, &evento->tipoMovimento[4]);
            LerDadosDaEEprom(endereco+27, &evento->tipoMovimento[5]);
            LerDadosDaEEprom(endereco+28, &evento->tipoMovimento[6]);
            LerDadosDaEEprom(endereco+29, &evento->tipoMovimento[7]);
    }

