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
#include "FSM_EventosDeParada.h"
#include "uart_driver.h"
#include <stdint.h>
#include "empilhadeira.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include "empilhadeira.h"
#include <stdlib.h> 

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
// VARIAVEL: maquinaDeEstadosLiberada_EventosDeParada
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: saber quando a maquina de estado está liberada para executar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char maquinaDeEstadosLiberada_EventosDeParada  = NAO;   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: delay
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: causar um delay no envio de mensagens no estadoAtual = ENVIAR_MENSAGEM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int delay = 0;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eepromInicializada
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazenar se a eeprom foi inicializada. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char eepromInicializada = NAO;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: leitorAcabouDeLigar
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena se o leitor acabou de ser ligado. 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    unsigned char leitorAcabouDeLigar = SIM;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAtual
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena o estado atual da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAtual = AGUARDANDO_TAREFA;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: estadoAnterior
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena o estado anterior da maquina de estado
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char estadoAnterior = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: idLeitor
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena id do leitor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned char idLeitor[20];
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eventosDeParadaArmazenados
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDeParada, executaMaquinaDeEstados_EventosDeParada e criarEventoDeParadaDeEmpilhadeira
// FUNÇÃO: armazena o valor de quantos eventos foram armazenados até o momento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int eventosDeParadaArmazenados = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: eventosDeParadaEnviados
// UTILIZADA EM: inicializaMaquinaDeEstados_EventosDeParada e executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena o valor de quantos eventos foram enviados para o servidor até o momento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int eventosDeParadaEnviados = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: stringMensagemEvento
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada
// FUNÇÃO: armazena a string do evento que é enviado pela serial
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char stringMensagemEvento[300];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIAVEL: novoEventoDeParada
// UTILIZADA EM: executaMaquinaDeEstado_EventosDeParada
// FUNÇÃO: armazena os eventos lidos da EEPROM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    eventoParadaEmpilhadeira novoEventoDeParada;
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      FUNÇÕES      /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    void incrementaContadorExecucao_EventosDeParada(void){
        delay++;
    }
    
    void zeraContadorExecucao_EventosDeParada(void){
        delay = 0;
    }
    
    void habilitaMaquinaDeEstados_EventosDeParada(void){
            //enviarMensagem = ENVIAR_MENSAGEM;
            maquinaDeEstadosLiberada_EventosDeParada = SIM;
        }

    void bloqueiaMaquinaDeEstados_EventosDeParada(void){
            maquinaDeEstadosLiberada_EventosDeParada = NAO;
        }

    void limpaBufferNaMaquinaDeEstados_EventosDeParada(void)  {
            int i=0;
            for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
                bufferInterrupcaoUART4[i]=0;
            }
        }

    void inicializaMaquinaDeEstados_EventosDeParada(void){
        unsigned char temp=0;
        
        if(eepromInicializada != VALOR_FLAG_INICIALIZACAO_EEPROM){
            LerDadosDaEEprom(ENDERECO_FLAG_INICIALIZACAO_EEPROM,&eepromInicializada);
            if(eepromInicializada != VALOR_FLAG_INICIALIZACAO_EEPROM){
                EscreverNaEEprom(ENDERECO_FLAG_INICIALIZACAO_EEPROM,VALOR_FLAG_INICIALIZACAO_EEPROM);
                EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS,0);
                EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS,eventosDeParadaArmazenados);
                EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS,0);
                EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS,eventosDeParadaEnviados);
            }
        }

        if(leitorAcabouDeLigar){           
            
            leitorAcabouDeLigar=0;

            LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS, &temp);
            eventosDeParadaArmazenados = (unsigned int)temp << 8;
            LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS, &temp);
            eventosDeParadaArmazenados |= (unsigned int)temp;

            LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS, &temp);
            eventosDeParadaEnviados = (unsigned int)temp << 8;
            LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS, &temp);
            eventosDeParadaEnviados |= (unsigned int)temp;

            retornaIdDoLeitor(idLeitor);
        }       
    }

    void criarEventoDeParadaDeEmpilhadeira(eventoParadaEmpilhadeira *_novoEventoDeParada){
        unsigned int endereco = (eventosDeParadaArmazenados * TAMANHO_EVENTO_DE_PARADA_EM_BYTES) + ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS;
        unsigned char temp=0;

        EscreverNaEEprom(endereco,_novoEventoDeParada->EPC_operador[0]);
        EscreverNaEEprom(endereco+1,_novoEventoDeParada->EPC_operador[1]);
        EscreverNaEEprom(endereco+2,_novoEventoDeParada->EPC_operador[2]);
        EscreverNaEEprom(endereco+3,_novoEventoDeParada->EPC_operador[3]);
        EscreverNaEEprom(endereco+4,_novoEventoDeParada->EPC_operador[4]);
        EscreverNaEEprom(endereco+5,_novoEventoDeParada->EPC_operador[5]);
        EscreverNaEEprom(endereco+6,_novoEventoDeParada->EPC_operador[6]);
        EscreverNaEEprom(endereco+7,_novoEventoDeParada->EPC_operador[7]);
        EscreverNaEEprom(endereco+8,_novoEventoDeParada->EPC_pedestre[0]);
        EscreverNaEEprom(endereco+9,_novoEventoDeParada->EPC_pedestre[1]);
        EscreverNaEEprom(endereco+10,_novoEventoDeParada->EPC_pedestre[2]);
        EscreverNaEEprom(endereco+11,_novoEventoDeParada->EPC_pedestre[3]);
        EscreverNaEEprom(endereco+12,_novoEventoDeParada->EPC_pedestre[4]);
        EscreverNaEEprom(endereco+13,_novoEventoDeParada->EPC_pedestre[5]);
        EscreverNaEEprom(endereco+14,_novoEventoDeParada->EPC_pedestre[6]);
        EscreverNaEEprom(endereco+15,_novoEventoDeParada->EPC_pedestre[7]);
        EscreverNaEEprom(endereco+16,_novoEventoDeParada->dia);
        EscreverNaEEprom(endereco+17,_novoEventoDeParada->mes);
        EscreverNaEEprom(endereco+18,_novoEventoDeParada->ano);
        EscreverNaEEprom(endereco+19,_novoEventoDeParada->hora);
        EscreverNaEEprom(endereco+20,_novoEventoDeParada->minuto);
        EscreverNaEEprom(endereco+21,_novoEventoDeParada->segundo);
        EscreverNaEEprom(endereco+22,_novoEventoDeParada->EPC_area[0]);
        EscreverNaEEprom(endereco+23,_novoEventoDeParada->EPC_area[1]);
        EscreverNaEEprom(endereco+24,_novoEventoDeParada->EPC_area[2]);
        EscreverNaEEprom(endereco+25,_novoEventoDeParada->EPC_area[3]);
        EscreverNaEEprom(endereco+26,_novoEventoDeParada->EPC_area[4]);
        EscreverNaEEprom(endereco+27,_novoEventoDeParada->EPC_area[5]);
        EscreverNaEEprom(endereco+28,_novoEventoDeParada->EPC_area[6]);
        EscreverNaEEprom(endereco+29,_novoEventoDeParada->EPC_area[7]);

        eventosDeParadaArmazenados++;

        temp = (unsigned char)(eventosDeParadaArmazenados>>8);
        EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS,temp);
        temp = (unsigned char)eventosDeParadaArmazenados & 0x00FF;
        EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS,temp);  
    }

    void executaMaquinaDeEstados_EventosDeParada(void){     
        unsigned char temp=0;

        incrementaContadorExecucao_EventosDeParada();
        
        switch(estadoAtual)
        {
            case AGUARDANDO_TAREFA:      
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA){ 
                    zeraContadorExecucao_EventosDeParada();
                    
                    if(maquinaDeEstadosLiberada_EventosDeParada){   
                        estadoAtual=LER_VARS_EEPROM;
                        estadoAnterior=AGUARDANDO_TAREFA;   
                    }      
                }
            break;
            case LER_VARS_EEPROM: 
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA){  
                    zeraContadorExecucao_EventosDeParada();
                    if(maquinaDeEstadosLiberada_EventosDeParada){                

                        if(eventosDeParadaArmazenados >= NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS){
                            eventosDeParadaArmazenados = 0;
                        }                               

                        if(eventosDeParadaEnviados >= NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS){ 
                            eventosDeParadaEnviados = 0;
                        }

                        if(eventosDeParadaEnviados != eventosDeParadaArmazenados){ 
                            estadoAtual=LER_MENSAGEM_NA_EEPROM;
                            estadoAnterior=LER_VARS_EEPROM; 
                        }                             
                    }    
                }
            break;
            case LER_MENSAGEM_NA_EEPROM:   
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA){  
                    zeraContadorExecucao_EventosDeParada();
                    if(maquinaDeEstadosLiberada_EventosDeParada){                
                        //WriteUART2('T');    

                        lerEventoDeParadaDeEmpilhadeiraNaEEPROM(&novoEventoDeParada,(ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS+(eventosDeParadaEnviados*TAMANHO_EVENTO_DE_PARADA_EM_BYTES)));

                        estadoAtual=ENVIAR_MENSAGEM;
                        estadoAnterior=LER_MENSAGEM_NA_EEPROM; 
                    }                       
                }
            break;
            case ENVIAR_MENSAGEM:   
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA){  
                    zeraContadorExecucao_EventosDeParada();
                    if(maquinaDeEstadosLiberada_EventosDeParada){  
                        //delay++;
                        //if(delay>INTERVALO_ENTRE_TENTATIVAS){
                            sprintf(stringMensagemEvento,"<E1;%c%c%c%c;%c%c%c%c%c%c%c%c;%c%c%c%c%c%c%c%c;%c%c%c%c%c%c%c%c;%02d%02d%02d;%02d%02d%02d>",
                                    idLeitor[0],idLeitor[1],idLeitor[2],idLeitor[3], 
                                    novoEventoDeParada.EPC_area[0],novoEventoDeParada.EPC_area[1],novoEventoDeParada.EPC_area[2],novoEventoDeParada.EPC_area[3],
                                    novoEventoDeParada.EPC_area[4],novoEventoDeParada.EPC_area[5],novoEventoDeParada.EPC_area[6],novoEventoDeParada.EPC_area[7],
                                    novoEventoDeParada.EPC_operador[0],novoEventoDeParada.EPC_operador[1],novoEventoDeParada.EPC_operador[2],novoEventoDeParada.EPC_operador[3],
                                    novoEventoDeParada.EPC_operador[4],novoEventoDeParada.EPC_operador[5],novoEventoDeParada.EPC_operador[6],novoEventoDeParada.EPC_operador[7],
                                    novoEventoDeParada.EPC_pedestre[0],novoEventoDeParada.EPC_pedestre[1],novoEventoDeParada.EPC_pedestre[2],novoEventoDeParada.EPC_pedestre[3],
                                    novoEventoDeParada.EPC_pedestre[4],novoEventoDeParada.EPC_pedestre[5],novoEventoDeParada.EPC_pedestre[6],novoEventoDeParada.EPC_pedestre[7],
                                    novoEventoDeParada.dia,novoEventoDeParada.mes,novoEventoDeParada.ano,
                                    novoEventoDeParada.hora,novoEventoDeParada.minuto,novoEventoDeParada.segundo);

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
                if(delay < TEMPO_AGUARDANDO_ACK_EVENTOS_DE_PARADA){  
                    if(maquinaDeEstadosLiberada_EventosDeParada){
                        if(bufferInterrupcaoUART4[0] == '<' &&
                            bufferInterrupcaoUART4[1] == 'E' &&
                            bufferInterrupcaoUART4[2] == '1' &&
                            bufferInterrupcaoUART4[3] == ';' &&
                            bufferInterrupcaoUART4[4] == 'O' &&
                            bufferInterrupcaoUART4[5] == 'K' &&
                            bufferInterrupcaoUART4[6] == '>'){   
                            zeraContadorExecucao_EventosDeParada();
                           
                            limpaBufferNaMaquinaDeEstados_EventosDeParada();
                            estadoAtual = FIM_CICLO;
                            estadoAnterior = AGUARDANDO_ACK;                          
                        }     
                        else{
                            if(bufferInterrupcaoUART4[0] == '<' &&
                                bufferInterrupcaoUART4[1] == 'E' &&
                                bufferInterrupcaoUART4[2] == '1' &&
                                bufferInterrupcaoUART4[3] == ';' &&
                                bufferInterrupcaoUART4[4] == 'N' &&
                                bufferInterrupcaoUART4[5] == 'O' &&
                                bufferInterrupcaoUART4[6] == 'K' &&
                                bufferInterrupcaoUART4[7] == ';'){                                   
                         
                                limpaBufferNaMaquinaDeEstados_EventosDeParada();
                                estadoAtual = FIM_CICLO;
                                estadoAnterior = AGUARDANDO_ACK;                          
                            }   
                        }
                    }                    
                }
                else{
                    zeraContadorExecucao_EventosDeParada();
                    estadoAtual=ENVIAR_MENSAGEM;
                    estadoAnterior=AGUARDANDO_ACK; 
                }
            break;
            case FIM_CICLO:    
                if(delay > TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA){
                    zeraContadorExecucao_EventosDeParada();
                    if(maquinaDeEstadosLiberada_EventosDeParada){
                        eventosDeParadaEnviados++;
                        temp = (unsigned char)(eventosDeParadaEnviados>>8);
                        EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS,temp);
                        temp = (unsigned char)eventosDeParadaEnviados & 0x00FF;
                        EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS,temp);                
                        estadoAtual=LER_VARS_EEPROM;
                        estadoAnterior=FIM_CICLO;
                    }                    
                }
            break;        
            default:
            break;
        }
    }

    void lerEventoDeParadaDeEmpilhadeiraNaEEPROM(eventoParadaEmpilhadeira *evento,int endereco){      
            // LER EPC DO OPERADOR QUE ESTAVA OPERANDO O VEICULO DURANTE O EVENTO
            LerDadosDaEEprom(endereco, &evento->EPC_operador[0]);
            LerDadosDaEEprom(endereco+1, &evento->EPC_operador[1]);
            LerDadosDaEEprom(endereco+2, &evento->EPC_operador[2]);
            LerDadosDaEEprom(endereco+3, &evento->EPC_operador[3]);
            LerDadosDaEEprom(endereco+4, &evento->EPC_operador[4]);
            LerDadosDaEEprom(endereco+5, &evento->EPC_operador[5]);
            LerDadosDaEEprom(endereco+6, &evento->EPC_operador[6]);
            LerDadosDaEEprom(endereco+7, &evento->EPC_operador[7]);
            // LER EPC DO PEDESTRE/OPERADOR/VEICULO PARA O QUAL GEROU O EVENTO
            LerDadosDaEEprom(endereco+8, &evento->EPC_pedestre[0]);
            LerDadosDaEEprom(endereco+9, &evento->EPC_pedestre[1]);
            LerDadosDaEEprom(endereco+10, &evento->EPC_pedestre[2]);
            LerDadosDaEEprom(endereco+11, &evento->EPC_pedestre[3]);
            LerDadosDaEEprom(endereco+12, &evento->EPC_pedestre[4]);
            LerDadosDaEEprom(endereco+13, &evento->EPC_pedestre[5]);
            LerDadosDaEEprom(endereco+14, &evento->EPC_pedestre[6]);
            LerDadosDaEEprom(endereco+15, &evento->EPC_pedestre[7]);
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
            LerDadosDaEEprom(endereco+22, &evento->EPC_area[0]);
            LerDadosDaEEprom(endereco+23, &evento->EPC_area[1]);
            LerDadosDaEEprom(endereco+24, &evento->EPC_area[2]);
            LerDadosDaEEprom(endereco+25, &evento->EPC_area[3]);
            LerDadosDaEEprom(endereco+26, &evento->EPC_area[4]);
            LerDadosDaEEprom(endereco+27, &evento->EPC_area[5]);
            LerDadosDaEEprom(endereco+28, &evento->EPC_area[6]);
            LerDadosDaEEprom(endereco+29, &evento->EPC_area[7]);
    }

