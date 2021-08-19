#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "USR_TCP232.h"
#include "uart_driver.h"
#include "time.h"
#include "setup_usb.h"
#include "BSP/bsp.h"
#include "BSP/pin_manager.h"
#include "RTC/DS1307.h"
#include "delay.h"
#include "tabelaEstacionamento.h"
#include "EEPROM/eeprom.h"
#include "eventos.h"
#include "main.h"


enum estadoDaMaquina{
    IDLE_ETH=0,
    CMD_SOLICITA_DATA_E_HORA,
    ACK_SOLICITA_DATA_E_HORA,
    CMD_KEEP_ALIVE,
    ACK_KEEP_ALIVE,
    CMD_SOLICITA_GREEN_LIST,
    ACK_SOLICITA_GREEN_LIST,
    CMD_ENVIA_EVENTOS_ETH,
    ACK_ENVIA_EVENTOS_ETH
}estados_USRTCP232;

enum estadosSetadosDaURL{
    URL_NENHUM=0,
    URL_DATA_E_HORA,
    URL_KEEP_ALIVE,
    URL_GREEN_LIST,
    URL_ENVIO_DE_EVENTOS
};

struct tm dataHora;

unsigned char listaDeTagsRecebidasDoServer[1000][2];

eventoPassagem eventoCadastradoParaEnvio; 

extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;
extern char __attribute__((far)) bufferRxEthernet[TAMANHO_BUFFER_ISR_UART2];

extern unsigned int eventosDePassagemEnviados;
extern unsigned int eventosDePassagemCadastrados;

//int timeoutRespostaKeepAlive;

unsigned char statusDeConexaoTCP = NOT_CONNECTED;

char alarmeFaltaDeRedeEthernet;

//extern struct tm *dataHora;

char estadoUSRTCP232;
unsigned int contadorExecucaoMaquinaEstadosUSRTCP232 = 0;


extern unsigned int contatorTempoParaRequisitarDataHoraEth = 0;
extern unsigned int contadorTempoParaEnviarKeepAlive = 0;

char flagEnviarKeepAlive = 0;
char flagRequisitarDataHora = 0;

extern unsigned char idLeitor[20];

char estadoHttpdURL = URL_NENHUM;

char flagDataHoraJaAtualizada = 0;


void executaMaquinaDeEstadosUSRTCP232(void){
        
    unsigned char mensagem[200];
    static int timeoutAsk;
    unsigned int ponteiroStartMsg;
    unsigned int numTagsNaGreenList;
    
    switch(estadoUSRTCP232){
        
        case IDLE_ETH:
            if(!flagDataHoraJaAtualizada && flagRequisitarDataHora){
                flagRequisitarDataHora = 0;
                estadoUSRTCP232 = CMD_SOLICITA_DATA_E_HORA;
            }else{
                contatorTempoParaRequisitarDataHoraEth++;
                if(contatorTempoParaRequisitarDataHoraEth > 20){ //30 seg
                    contatorTempoParaRequisitarDataHoraEth = 0;
                    flagRequisitarDataHora = 1;
                }
            }
            
            if(flagDataHoraJaAtualizada && flagEnviarKeepAlive){
                flagEnviarKeepAlive = 0;
                estadoUSRTCP232 = CMD_KEEP_ALIVE;
            }else{
                contadorTempoParaEnviarKeepAlive++;
                if(contadorTempoParaEnviarKeepAlive > 100){ //30 seg
                    contadorTempoParaEnviarKeepAlive = 0;
                    flagEnviarKeepAlive = 1;
                }
            }
            
        break;
        
        case CMD_SOLICITA_DATA_E_HORA:
            if(estadoHttpdURL != URL_DATA_E_HORA){
                sprintf(mensagem,"set url data hora\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                if(setaURLDataHora()){
                    estadoHttpdURL = URL_DATA_E_HORA;
                }else{
                    estadoUSRTCP232 = IDLE_ETH;
                }
            }else{
                sprintf(mensagem,"send cmd data hora\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                sprintf(mensagem, "parametro=[FE;%c%c%c%c%c%c]", idDoLeitor[0], idDoLeitor[1], idDoLeitor[2], idDoLeitor[3], idDoLeitor[4], idDoLeitor[5]);
                //sprintf(mensagem, "parametro=[FE;000027]");
                enviaDadosParaEthernet(mensagem, strlen(mensagem));
                estadoUSRTCP232 = ACK_SOLICITA_DATA_E_HORA;
                timeoutAsk = 0;
            }
        break;           
        case ACK_SOLICITA_DATA_E_HORA:
            if(strncmp(bufferRxEthernet, "\n\n[FE;OK;", 9) == 0){
                atualizaDataHoraNoRTC();
                flagDataHoraJaAtualizada = 1;
                estadoUSRTCP232 = IDLE_ETH;
                sprintf(mensagem,"data hora update successful\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
            }else{
                timeoutAsk = timeoutAsk + 1;
                if(timeoutAsk > 50){ // 10 seg
                    limpaBufferRxEthernet();
                    flagDataHoraJaAtualizada = 0;
                    estadoUSRTCP232 = IDLE_ETH;
                }
            }
        break;
  
        
        case CMD_KEEP_ALIVE:
            if(VerificaSeHaEventosParaSeremEnviados() == 1){
                estadoUSRTCP232 = CMD_ENVIA_EVENTOS_ETH;
                break;
            }
            if(estadoHttpdURL != URL_KEEP_ALIVE){
                sprintf(mensagem,"set url keep alive\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                if(setaURLKeepAlive()){
                    estadoHttpdURL = URL_KEEP_ALIVE;
                }else{
                    estadoUSRTCP232 = IDLE_ETH;
                }
            }else{
                sprintf(mensagem,"send cmd keep alive\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                sprintf(mensagem, "parametro=[FD;%c%c%c%c%c%c;A0]", idDoLeitor[0], idDoLeitor[1], idDoLeitor[2], idDoLeitor[3], idDoLeitor[4], idDoLeitor[5]);
                //sprintf(mensagem, "parametro=[FD;000027;A0]");
                enviaDadosParaEthernet(mensagem, strlen(mensagem));
                estadoUSRTCP232 = ACK_KEEP_ALIVE;
                timeoutAsk = 0;
            }
        break;        
        case ACK_KEEP_ALIVE:
            if(strstr(bufferRxEthernet, "[FD;OK;S]")){
                limpaBufferRxEthernet();
                estadoUSRTCP232 = CMD_SOLICITA_GREEN_LIST;
                break;
            }
            
            if(strstr(bufferRxEthernet, "[FD;OK;N]")){
                limpaBufferRxEthernet();
                sprintf(mensagem,"keep alive ok\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                estadoUSRTCP232 = IDLE_ETH;
                break;
            }
            
            timeoutAsk = timeoutAsk + 1;
            if(timeoutAsk > 20){
                limpaBufferRxEthernet();
                estadoUSRTCP232 = IDLE_ETH;
            }
            
        break;

        
        case CMD_SOLICITA_GREEN_LIST:
            if(estadoHttpdURL != URL_GREEN_LIST){
                sprintf(mensagem,"set url green list\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                if(setaURLGreenList()){
                    estadoHttpdURL = URL_GREEN_LIST;
                }else{
                    estadoUSRTCP232 = IDLE_ETH;
                }
            }else{
                sprintf(mensagem,"send cmd get green list\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                sprintf(mensagem, "parametro=[FB;%c%c%c%c%c%c]", idDoLeitor[0], idDoLeitor[1], idDoLeitor[2], idDoLeitor[3], idDoLeitor[4], idDoLeitor[5]);
                //sprintf(mensagem, "parametro=[FB;000027]");
                enviaDadosParaEthernet(mensagem, strlen(mensagem));
                estadoUSRTCP232 = ACK_SOLICITA_GREEN_LIST;
                timeoutAsk = 0;
            }
        break;        
        case ACK_SOLICITA_GREEN_LIST:
            if(strstr(bufferRxEthernet, "[FB;OK;")){
                if((bufferRxEthernet[2] = '[') && (bufferRxEthernet[13] = ';')){
                    numTagsNaGreenList = obtemNumeroDeTagsRecebidasNaGreenListRequest();
                    if(numTagsNaGreenList > 1000){
                        sprintf(mensagem,"green list very large > 1000 veicles\r\n");
                        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                    }else{
                        if(VerificaIntegridadeDaGreenList(numTagsNaGreenList)){
                            exibeListaDeTagsRecebidasDoServer();
                            sprintf(mensagem,"save list eeprom internal memory\r\n");
                            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                            salvaGreenListNaEEPROM(numTagsNaGreenList);
                            removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados);
                            carregaListaDeVeiculosAutorizadosNaRAM();   //atualiza lista de veículos autorizados;
                            exibirListaDeVeiculosLiberados();
                            estadoUSRTCP232 = IDLE_ETH;
                            sprintf(mensagem,"green list update successful\r\n");
                            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                        }else{
                            sprintf(mensagem,"green list corrupted\r\n");
                            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                        }
                    }
                } 
            }else{
                timeoutAsk = timeoutAsk + 1;
                if(timeoutAsk > 20){
                    limpaBufferRxEthernet();
                    estadoUSRTCP232 = IDLE_ETH;
                    sprintf(mensagem,"error receive green list\r\n");
                    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                }
            }
        break;
        
        case CMD_ENVIA_EVENTOS_ETH:                                   
            if(estadoHttpdURL != URL_ENVIO_DE_EVENTOS){
                sprintf(mensagem,"set url envio de eventos\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                if(setaURLEnvioDeEventos()){
                    estadoHttpdURL = URL_ENVIO_DE_EVENTOS;
                }else{
                    estadoUSRTCP232 = IDLE_ETH;
                }
            }else{
                lerEventoDePassagemNaEEPROM(&eventoCadastradoParaEnvio, (ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS+(eventosDePassagemEnviados*TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES)));
                sprintf(mensagem,"send cmd envio de eventos\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                //sprintf(mensagem, "parametro=[FF;000027;E;0001;010621;163600]");
                //enviaDadosParaEthernet(mensagem, strlen(mensagem));
                sprintf(mensagem, "parametro=[FF;%c%c%c%c%c%c;%c;%02x%02x;%02d%02d%02d;%02d%02d%02d]",
                        idDoLeitor[0],
                        idDoLeitor[1],
                        idDoLeitor[2],
                        idDoLeitor[3],
                        idDoLeitor[4],
                        idDoLeitor[5],       
                        (eventoCadastradoParaEnvio.tipoMovimento == MOVIMENTO_ENTRADA ? 'E':'S'),
                        eventoCadastradoParaEnvio.EPC_veiculo[1],
                        eventoCadastradoParaEnvio.EPC_veiculo[0],
                        //eventoCadastradoParaEnvio.EPC_veiculo[2],
                        //eventoCadastradoParaEnvio.EPC_veiculo[3],
                        eventoCadastradoParaEnvio.dia,
                        eventoCadastradoParaEnvio.mes,
                        eventoCadastradoParaEnvio.ano,
                        eventoCadastradoParaEnvio.hora,
                        eventoCadastradoParaEnvio.minuto,
                        eventoCadastradoParaEnvio.segundo);
                enviaDadosParaEthernet(mensagem, strlen(mensagem));
                estadoUSRTCP232 = ACK_ENVIA_EVENTOS_ETH;
                timeoutAsk = 0;        
            }
        break;
        case ACK_ENVIA_EVENTOS_ETH:
            if(strstr(bufferRxEthernet, "[FF;OK]")){
                sprintf(mensagem,"evento enviado com sucesso\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                limpaBufferRxEthernet();
                IncrementaContadorDeEventosEnviados();
                if(eventosDePassagemEnviados == eventosDePassagemCadastrados){
                    sprintf(mensagem,"todos os eventos foram enviados com sucesso!\r\n");
                    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                    ReiniciaPonteiroDeMemoriaDosEventosNaEeprom();
                    estadoUSRTCP232 = IDLE_ETH;
                }else{
                    estadoUSRTCP232 = CMD_ENVIA_EVENTOS_ETH;
                }
                break;
            }
            timeoutAsk = timeoutAsk + 1;
            if(timeoutAsk > 20){
                limpaBufferRxEthernet();
                estadoUSRTCP232 = IDLE_ETH;
            }
        break;
            
    }
    
}




char setaURLDataHora(void){
    if(entraEmModoAt()){
        delay_ms(100);
        if(enviaURLDataHora()){
            delay_ms(100);
            if(saiDoModoAt()){
                delay_ms(100);
                return 1;
            }
        }
    }
    //saiDoModoAt();
    //resetModuloETH(); 
    return 0;
}

char setaURLKeepAlive(void){
   
    if(entraEmModoAt()){
        delay_ms(100);
        if(enviaURLKeepAlive()){
            delay_ms(100);
            if(saiDoModoAt()){
                delay_ms(100);
                return 1;
            }    
        }
    }
    //resetModuloETH(); 
    return 0;
}

char setaURLGreenList(void){
   
    if(entraEmModoAt()){
        delay_ms(100);
        if(enviaURLGreenList()){
            delay_ms(100);
            if(saiDoModoAt()){
                delay_ms(100);
                return 1;
            }
        }
    }
    //restartModuloEth();
    return 0;
}

char setaURLEnvioDeEventos(void){
   
    if(entraEmModoAt()){
        delay_ms(100);
        if(enviaURLEnvioDeEventos()){
            delay_ms(100);
            if(saiDoModoAt()){
                delay_ms(100);
                return 1;
            }
        }
    }
    //restartModuloEth();
    return 0;
}
    
 
char enviaURLDataHora(void){
    
    unsigned long timeout;
    unsigned char comando[50];
    unsigned char mensagem[50];
    
    sprintf(comando, "AT+HTPURL=/tag/php/apife.php?\r");  
    enviaDadosParaEthernet(comando, strlen(comando));
    timeout = 0;
    for(timeout = 0; timeout < 500000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    }
    sprintf(mensagem, "Falha ao setar URL data hora\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    limpaBufferRxEthernet();
    return 0;
}

char enviaURLKeepAlive(void){
    
    unsigned int timeout;
    unsigned char comando[50];
    unsigned char mensagem[50];
    
    sprintf(comando, "AT+HTPURL=/tag/php/apifd.php?\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    timeout = 0;
    for(timeout = 0; timeout < 500000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    }
    sprintf(mensagem, "Falha ao setar URL keep alive\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    limpaBufferRxEthernet();
    return 0;
}

char enviaURLGreenList(void){
    
    unsigned int timeout;
    unsigned char comando[50];
    unsigned char mensagem[50];
    
    sprintf(comando, "AT+HTPURL=/tag/php/apifb.php?\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    timeout = 0;
    for(timeout = 0; timeout < 500000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    }
    sprintf(mensagem, "Falha ao setar URL green list\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    limpaBufferRxEthernet();
    return 0;
}

char enviaURLEnvioDeEventos(void){
    
    unsigned int timeout;
    unsigned char comando[50];
    unsigned char mensagem[50];
    
    sprintf(comando, "AT+HTPURL=/tag/php/apiff.php?\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    timeout = 0;
    for(timeout = 0; timeout < 500000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    }
    sprintf(mensagem, "Falha ao setar URL envio de eventos\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    limpaBufferRxEthernet();
    return 0;
}




char entraEmModoAt(void){
    char comando[20];
    unsigned char mensagem[50];
    unsigned int timeout;
        
    limpaBufferRxEthernet();
    sprintf(comando, "+++");
    enviaDadosParaEthernet(comando, strlen(comando));
    delay_ms(100);
    //for(timeout = 0; timeout < 5000; timeout = timeout + 1){
        if(bufferRxEthernet[0] == 'a') goto FASE_2;
    //}
    goto ERROR;
   
FASE_2:
    limpaBufferRxEthernet();
    sprintf(comando, "a");
    enviaDadosParaEthernet(comando, strlen(comando));
    delay_ms(100);
    //for(timeout = 0; timeout < 5000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+ok")){
            limpaBufferRxEthernet();
            return 1;
        }
    //}
    
ERROR:
    sprintf(mensagem, "Falha ao entrar em modo AT\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    return 0;
}


char saiDoModoAt(void){
    char comando[10];
    unsigned char mensagem[50];
    unsigned int timeout;
    
    limpaBufferRxEthernet();
    sprintf(comando, "AT+ENTM\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    for(timeout = 0; timeout < 500000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    }
    sprintf(mensagem, "Falha ao sair do modo AT\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    return 0;
    
}

char restartModuloEth(void){
    char comando[10];
    unsigned char mensagem[50];
    unsigned int timeout;
    
    limpaBufferRxEthernet();
    sprintf(comando, "AT+Z\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    delay_ms(100);
    //for(timeout = 0; timeout < 1000; timeout = timeout + 1){
        if(strstr(bufferRxEthernet, "+OK")){
            limpaBufferRxEthernet();
            return 1;
        }
    //}
    sprintf(mensagem, "Falha reiniciar modulo Ethernet\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    return 0;
}




char solicitaStatusDeConexaoTCP(void){
    char comando[50];
    char respostaEsperada[TAMANHO_BUFFER_RX_ETHERNET];
    char timeout = 0;
    
    entraEmModoAt();
    delay_ms(200);
    limpaBufferRxEthernet();
    sprintf(comando, "AT+SOCKLK\r");
    enviaDadosParaEthernet(comando, strlen(comando));
    delay_ms(100);
    strcpy(respostaEsperada, "\r\n+OK=connect\r\n");
    if(strncmp(bufferRxEthernet, respostaEsperada, 15) == 0){
        delay_ms(100);
        saiDoModoAt();
        delay_ms(100);
        return 1;
    }else{
        delay_ms(200);
        saiDoModoAt();
        delay_ms(100);
        return 0;
    } 
}


void atualizaDataHoraNoRTC(void){ // isso nao pode ser executado na maquina pois demorava muito.
  
        dataHora.tm_mday = (bufferRxEthernet[9]  - '0') * 10 + (bufferRxEthernet[10]  - '0');  
        dataHora.tm_mon  = (bufferRxEthernet[11]  - '0') * 10 + (bufferRxEthernet[12] - '0');
        dataHora.tm_year = (bufferRxEthernet[13] - '0') * 10 + (bufferRxEthernet[14] - '0');
        dataHora.tm_hour = (bufferRxEthernet[16] - '0') * 10 + (bufferRxEthernet[17] - '0');
        dataHora.tm_min  = (bufferRxEthernet[18] - '0') * 10 + (bufferRxEthernet[19] - '0');
        dataHora.tm_sec  = (bufferRxEthernet[20] - '0') * 10 + (bufferRxEthernet[21] - '0');
        SetarHoraRTC(dataHora.tm_sec, dataHora.tm_min, dataHora.tm_hour, dataHora.tm_mday, dataHora.tm_mon, dataHora.tm_year);
}

void salvaGreenListNaEEPROM(unsigned int numRegistros){
    unsigned char dado;
    unsigned int linha;
    unsigned char coluna;
    unsigned int vetorInicial;
    unsigned int enderecoEeprom;
    //char listaDeTagsRecebidasDoServer[1000][2];
    
    linha = 0;
    coluna = 0;
    vetorInicial = 13;
    enderecoEeprom = ENDERECO_INICIAL_PARA_ARMAZENAR_VEICULOS_NA_EEPROM;
    
    for(linha = 0; linha < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; linha++){
        dado = listaDeTagsRecebidasDoServer[linha][0];
        EscreverNaEEprom(enderecoEeprom, dado);
        dado = listaDeTagsRecebidasDoServer[linha][1];
        EscreverNaEEprom(enderecoEeprom + 1, dado);
        enderecoEeprom = enderecoEeprom + 2;
    }
}



char VerificaIntegridadeDaGreenList(unsigned int numRegistros){
    unsigned int i;
    unsigned int vetorDoBuffer;
    unsigned int posicao;
    unsigned char num[4] = {0,0,0,0};
    unsigned int numVeiculo;
    
    const char byte1 = 0;
    const char byte2 = 1;
    posicao = 0;
    //num = {0,0,0,0};
    numVeiculo = 0;
    limpaListaDeTagsRecebidasDoServer();
    vetorDoBuffer = 13;    
    
    for(i = 0; i < numRegistros; i++){
        if(bufferRxEthernet[vetorDoBuffer] == ';'){
            num[0] = bufferRxEthernet[vetorDoBuffer + 1];
            num[1] = bufferRxEthernet[vetorDoBuffer + 2];
            num[2] = bufferRxEthernet[vetorDoBuffer + 3];
            num[3] = bufferRxEthernet[vetorDoBuffer + 4];
            numVeiculo = (int)strtol(num, NULL, 16);
            listaDeTagsRecebidasDoServer[posicao][0] = (numVeiculo >> 8) & 0x00FF;
            listaDeTagsRecebidasDoServer[posicao][1] = numVeiculo & 0x00FF;
            posicao = posicao + 1;
            vetorDoBuffer = vetorDoBuffer + 5;
        }else{
            limpaBufferRxEthernet();
            return 0;
        }
    }
    limpaBufferRxEthernet();
    return 1;
}



unsigned int obtemNumeroDeTagsRecebidasNaGreenListRequest(void){
    unsigned char numTagsNaGreenList[4];
    
    numTagsNaGreenList[0] = bufferRxEthernet[9];
    numTagsNaGreenList[1] = bufferRxEthernet[10];
    numTagsNaGreenList[2] = bufferRxEthernet[11];
    numTagsNaGreenList[3] = bufferRxEthernet[12];
    return atoi(numTagsNaGreenList); 
}


void exibeListaDeTagsRecebidasDoServer(void){
    unsigned int posicao;
    unsigned char mensagem[50];
    
    sprintf(mensagem, "lista recebida e verificada\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    for(posicao = 0; posicao < 1000; posicao++){
        sprintf(mensagem, "%04d > %02x%02x\r\n", posicao, listaDeTagsRecebidasDoServer[posicao][0], listaDeTagsRecebidasDoServer[posicao][1]);
        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    }
    
}



void setaStatusDoLedDeEthernet(void){
    if(statusDeConexaoTCP == CONNECTED){
        LED1_SetHigh();
    }else{
        LED1_Toggle();
    }
}


void limpaBufferRxEthernet(void){
    memset(bufferRxEthernet, 0, TAMANHO_BUFFER_ISR_UART2 - 1);
}
  

void enviaDadosParaEthernet(char dados[TAMANHO_BUFFER_RX_ETHERNET], int Tamanho){
    int posicao;
    
    for (posicao = 0; posicao < Tamanho; posicao = posicao + 1){
        //uart3Tx(*Dados);//Porta USB
        //uart2Tx(*Dados);//Porta ETH
        uart2Tx(dados[posicao]);//Porta ETH
        //uart1Tx(*Dados);//ZigBee Beta
        //uart4Tx(Dado);//ZigBee Alfa
        //Dados = Dados + 1;
    }
}

char resetModuloETH(void){
    char mensagem[50];
    sprintf(mensagem, "Reset fisico modulo Ethernet\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    LATFbits.LATF2 = 0;
    delay_ms(300);
    LATFbits.LATF2 = 1;
    delay_ms(100);
}



void inicializaModuloEthernet(void){
    
    resetModuloETH();
    flagDataHoraJaAtualizada = 0;
    flagRequisitarDataHora = 0;
    estadoUSRTCP232 = IDLE_ETH;
    estadoHttpdURL = URL_NENHUM;
}

void limpaListaDeTagsRecebidasDoServer(void){
    unsigned int posicao;
    for(posicao = 0; posicao < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; posicao++){
        listaDeTagsRecebidasDoServer[posicao][0] = NULL;
        listaDeTagsRecebidasDoServer[posicao][1] = NULL;
    }
}

void carregaListaDeVeiculosAutorizadosNaRAM(void){
    unsigned int posicao;
    unsigned int endereco;
    unsigned char dado;
    unsigned int numTag;
    
    EPC_Estacionamento readEPC;

    endereco = ENDERECO_INICIAL_PARA_ARMAZENAR_VEICULOS_NA_EEPROM;
    dado = 0;
    
    for(posicao = 0; posicao < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; posicao++){

        LerDadosDaEEprom(endereco, &dado);
        numTag = dado;
        LerDadosDaEEprom(endereco + 1, &dado);
        numTag = ((numTag << 8) & 0xFF00) | dado;
        if(numTag > 0){
            readEPC.tag = numTag;
            adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, readEPC);
            endereco = endereco + 2;
        }else{
            break;
        }
        //tabela.epc[posicao].numVeiculo[0] = listaDeTagsRecebidasDoServer[posicao][0];
        //tabela.epc[posicao].numVeiculo[1] = listaDeTagsRecebidasDoServer[posicao][1];
        
    }
}