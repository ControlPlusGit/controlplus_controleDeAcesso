/*
 * File:   controleAcessoGaragem.c
 * Author: Marcos
 *
 * Created on 28 de Abril de 2021, 12:32
 */

#include "xc.h"
#include "p24FJ256DA210.h"
#include <stdio.h>
#include <string.h>
#include "controleAcessoGaragem.h"
#include "tabelaEstacionamento.h"
#include "delay.h"
#include "BSP/pin_manager.h"
#include "setup_usb.h"
#include "BSP/bsp.h"
#include "BSP/rfid_bsp.h"
#include "RFID/as3993.h"
#include"RFID/gen2.h"
#include "eventos.h"
#include "BSP/pin_manager.h"
#include "USR_TCP232.h"
#include "EEPROM/eeprom.h"



#define CMD_PORTAO1                 LATCbits.LATC2  //RELE 1
#define CMD_PORTAO2                 LATGbits.LATG15 //RELE 2
#define ALARME                      LATCbits.LATC1  //RELE 3
#define SENSOR_PORTAO1              PORTGbits.RG6   //OPTO 1
#define SENSOR_PORTAO2              PORTGbits.RG7   //OPTO 2
#define SENSOR_PASSAGEM_VEICULO     PORTAbits.RA5  //PORTCbits.RC13   //GPIO1  
#define BOTAO_CALAR_ALARME          PORTBbits.RB5   //GPIO16

EPC_Estacionamento epcLido;

unsigned char numeroDeTagsLidas = 0;
char numCarrosNaClausura = 0;
char contadorDeTagsQueEntraram = 0;
char contadorDeTagsQueSairam = 0;
char contadorDeCarrosQuePassaram = 0;
char flagAlarme = 0;

unsigned char tagCondominio[2] = {00,01};

/////////////////////////////////////////////
// Green list criada a partir de tabelaEstacionamento.h
/////////////////////////////////////////////
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;     // lista principal ordenada com as tags lidas
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberadosTest; // utilizada para check na gravacao de dados na flash
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Entrada; // lista desordenada com as tags em movimento
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Saida; // lista desordenada com as tags em movimento


unsigned char totalDeCarrosNaClaurura = 0;
unsigned char flagHabilitaLeituraDasAntenas = 0;


void ExecutaControleDeAcessoGaragem(void){
    unsigned char mensagem[50];
    unsigned int endereco;
    unsigned char dado;
    
    LATFbits.LATF2 = 1; // liga modulo ETH.
    inicializaModuloEthernet();
    
    //carregaListaDeVeiculosAutorizadosNaRAM();
    
//    sprintf(mensagem, "Carregando GreenList salva na EEPROM\r\n");
//    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
//    for(endereco = END_INICIAL_GREENLIST_EEPROM; endereco <= END_FINAL_GREENLIST_EEPROM; endereco = endereco + 1){
//        LerDadosDaEEprom(endereco, &dado);
//    }
//    sprintf(mensagem, "Tabela GreenList carregada com sucesso!\r\n");
//    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
       
    

    while(1){
        
        executaMaquinaDeEstadosUSRTCP232();
        
        numeroDeTagsLidas = realizaLeituraDeAntena(ANTENNA_1); //Antena de entrada
        if(numeroDeTagsLidas > 0 && tags_[0].tid.data_available_flag == 1){  // Se entrar, tid esta disponivel
            //CarregaEpcLido(0);
            if(tags_[0].epc[0] == 0x29 && tags_[0].epc[1] == 0x04 && tags_[0].epc[2] == 0x80){ //TAG é da ControlPlus?
                if(tags_[0].epc[3] == tagCondominio[0] && tags_[0].epc[4] == tagCondominio[1]){ //TAG é do Condominio?
                    epcLido.numVeiculo[0] = tags_[0].epc[6];
                    epcLido.numVeiculo[1] = tags_[0].epc[5];
                    if(buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epcLido)){ // Veiculo está autorizado a entrar?
                        sprintf(mensagem, "Veiculo querendo entrar\r\n");
                        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                        VeiculoQuerendoEntrar();
                    }else{
                        sprintf(mensagem, "Veículo não autorizado\r\n");
                        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                        delay_ms(500);
                    }
                }else{
                    sprintf(mensagem, "Veículo não pertence ao condominio\r\n");
                    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                    delay_ms(500);
                }
            }else{
                sprintf(mensagem, "Veículo não pertence ao sistema\r\n");
                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                delay_ms(500);
            }
        }
                
        numeroDeTagsLidas = realizaLeituraDeAntena(ANTENNA_2); //Antena de entrada
        if(numeroDeTagsLidas > 0){
            VeiculoQuerendoSair();
        }
        
        if(SENSOR_PORTAO1 == ABERTO && SENSOR_PORTAO2 == FECHADO){
            Portao1AbertoManualmente();
        }
        
        if(SENSOR_PORTAO1 == FECHADO && SENSOR_PORTAO2 == ABERTO){
            //não faz nada por enquanto
        }
    }  
    
}    

void VeiculoQuerendoEntrar(void){
    unsigned char mensagem[50];
    
    sprintf(mensagem, "Veiculo querendo entrar\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    if(SENSOR_PORTAO1 == FECHADO && SENSOR_PORTAO2 == FECHADO && numCarrosNaClausura == 0){
        if(comandoParaAbrirPortao1() == 1){
            sprintf(mensagem, "Portão externo aberto\r\n");
            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
        }
        contadorDeCarrosQuePassaram = 0;
        contadorDeTagsQueEntraram = 0;
        contadorDeTagsQueSairam = 0;
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida);
        while(SENSOR_PORTAO1 == ABERTO){
            lerFluxoDeEntrada();
            lerFluxoDeSaida();
            lerBarreiraDeUltrasom();
        }
        sprintf(mensagem, "Portão externo fechado\r\n");
        enviaDadosParaUSBserial(mensagem, strlen(mensagem)); 
        delay_ms(1000);            
        if(contadorDeTagsQueEntraram > 0 || contadorDeTagsQueSairam > 0) CadastraEventosDePassagem(&listaDeVeiculosLidosDuranteMovimento_Entrada, &listaDeVeiculosLidosDuranteMovimento_Saida);
        if(contadorDeCarrosQuePassaram > contadorDeTagsQueEntraram) flagAlarme = 1;
        if(contadorDeCarrosQuePassaram > 0) LiberaVeiculosNaClausura();
    }
    sprintf(mensagem, "Retoma leitura das antenas\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
}


void VeiculoQuerendoSair(void){
    unsigned char mensagem[50];
    
    sprintf(mensagem, "Veiculo querendo sair\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    if(SENSOR_PORTAO1 == FECHADO && SENSOR_PORTAO2 == FECHADO){
        if(comandoParaAbrirPortao1() == 1){
            sprintf(mensagem, "Portão externo aberto\r\n");
            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
        }
        contadorDeCarrosQuePassaram = 0;
        contadorDeTagsQueEntraram = 0;
        contadorDeTagsQueSairam = 0;
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida);
        while(SENSOR_PORTAO1 == ABERTO){
            lerFluxoDeEntrada();
            lerFluxoDeSaida();
            lerBarreiraDeUltrasom();
        }
        sprintf(mensagem, "Portão externo fechado\r\n");
        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
        delay_ms(1000);            
        if(contadorDeTagsQueEntraram > 0 || contadorDeTagsQueSairam > 0) CadastraEventosDePassagem(&listaDeVeiculosLidosDuranteMovimento_Entrada, &listaDeVeiculosLidosDuranteMovimento_Saida);
        if(contadorDeCarrosQuePassaram > contadorDeTagsQueEntraram) flagAlarme = 1;
        if(contadorDeCarrosQuePassaram > 0) LiberaVeiculosNaClausura();
    }
    sprintf(mensagem, "Retoma leitura das antenas\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
}


void Portao1AbertoManualmente(void){
    unsigned char mensagem[50];
    
    sprintf(mensagem, "!*Portao externo aberto manualmente*!\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    contadorDeCarrosQuePassaram = 0;
    contadorDeTagsQueEntraram = 0;
    contadorDeTagsQueSairam = 0;
    while(SENSOR_PORTAO1 == ABERTO){
        lerFluxoDeEntrada();
        lerFluxoDeSaida();
        lerBarreiraDeUltrasom();
    }
    sprintf(mensagem, "Portão externo fechado\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));    
    delay_ms(1000);            
    if(contadorDeTagsQueEntraram > 0 || contadorDeTagsQueSairam > 0) CadastraEventosDePassagem(&listaDeVeiculosLidosDuranteMovimento_Entrada, &listaDeVeiculosLidosDuranteMovimento_Saida);
    if(contadorDeCarrosQuePassaram > contadorDeTagsQueEntraram) flagAlarme = 1;
    if(contadorDeCarrosQuePassaram > 0) LiberaVeiculosNaClausura();
    
    sprintf(mensagem, "Retoma leitura das antenas\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
}


void CadastraEventosDePassagem(TabelaDeEpcDeEstacionamento *tabelaEntrada, TabelaDeEpcDeEstacionamento *tabelaSaida){
    unsigned int i;
    unsigned int numEventosValidos;
    
    if(contadorDeCarrosQuePassaram <= contadorDeTagsQueEntraram){
        numEventosValidos = contadorDeCarrosQuePassaram;
    }else{
        numEventosValidos = contadorDeTagsQueEntraram;
    }
    for(i = 0; i < numEventosValidos; i++){
        cadastrarNovoEvento(tabelaEntrada->epc[i].tag, MOVIMENTO_ENTRADA);
    }
    for(i = 0; i < contadorDeTagsQueSairam; i++){
        cadastrarNovoEvento(tabelaSaida->epc[i].tag, MOVIMENTO_SAIDA);
    }
}



void exibirListaDeVeiculosLiberados(void){
    unsigned char mensagem[50];
    unsigned int i;
    unsigned int contador = 0;
    
    sprintf(mensagem, "\r\n\r\nLISTA DE VEICULOS AUTORIZADOS\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    for(i = 0; i < listaDeVeiculosLiberados.ponteiroTabela; i = i + 1){
        contador = contador + 1;
        sprintf(mensagem, "Tag %04d: %04x\r\n", contador, (listaDeVeiculosLiberados.epc[i]).tag);
        enviaDadosParaUSBserial(mensagem, strlen(mensagem));
        
    }
}

char comandoParaAbrirPortao1(void){
    unsigned char mensagem[50];
    char numTentativas;
    
    numTentativas = 0;
    while(SENSOR_PORTAO1 == FECHADO && SENSOR_PORTAO2 == FECHADO && numTentativas < 3){
        numTentativas = numTentativas + 1;
        CMD_PORTAO1 = 1;
        delay_ms(500);
        CMD_PORTAO1 = 0;
        delay_ms(3000);      
    }
    if(SENSOR_PORTAO1 == ABERTO){
        return 1;
    }
    return 0;
}



void lerFluxoDeEntrada(void){
    unsigned char i;
    unsigned char mensagem[50];

    numeroDeTagsLidas = realizaLeituraDeAntena(ANTENNA_1); //Antena de entrada
    if(numeroDeTagsLidas > 0){
        for(i = 0; i < MAXTAG; i++){           
            if(tags_[i].epclen > 0){
                if((tags_[i].epc[0] == 0x29) && (tags_[i].epc[1] == 0x04) && (tags_[i].epc[2] == 0x80)){ //verifica se a tag é de controle de acesso controlplus
                    if(tags_[i].epc[3] == tagCondominio[0] && tags_[i].epc[4] == tagCondominio[1]){ //verifica se a tag é do condomínio
                        epcLido.numVeiculo[0] = tags_[i].epc[6];
                        epcLido.numVeiculo[1] = tags_[i].epc[5];
                        if(buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido) == 0){ //Veiculo já inserido no fluxo de entrada?
                            if(buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(&listaDeVeiculosLiberados, epcLido)){ // Veiculo presenta na greenlist?  
                                adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido);
                                //novoEvento.id_veiculo[0] = epcLido.byte2;
                                //novoEvento.id_veiculo[1] = epcLido.byte1;
                                //novoEvento.tipoMovimento = MOVIMENTO_ENTRADA; 
                                //cadastrarNovoEvento(epcLido, MOVIMENTO_ENTRADA);
                                contadorDeTagsQueEntraram = contadorDeTagsQueEntraram + 1;
                                sprintf(mensagem, "-> Evento Entrada de Veiculo: %02x%02x\r\n", epcLido.numVeiculo[1], epcLido.numVeiculo[0]);
                                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                            }else{
                                //removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido);
                                sprintf(mensagem, "Veiculo %02d%02d não autorizado!!!\r\n", epcLido.numVeiculo[1], epcLido.numVeiculo[0]);
                                enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                            }
                        }
                    }                   
                }
            }
        }
    }
}

void lerFluxoDeSaida(void){
    unsigned char i;
    unsigned char mensagem[50];
    
    numeroDeTagsLidas = realizaLeituraDeAntena(ANTENNA_2); //Antena de entrada
    if(numeroDeTagsLidas > 0){
        for(i = 0; i < MAXTAG; i++){
            if(tags_[i].epclen > 0){
                if((tags_[i].epc[0] == 0x29) && (tags_[i].epc[1] == 0x04) && (tags_[i].epc[2] == 0x80)){ //if (verificaTagValida(tags_[i].epc) > 0) { // Tag veicular valida?
                    if(tags_[i].epc[3] == tagCondominio[0] && tags_[i].epc[4] == tagCondominio[1]){ //verifica se a tag é do condomínio
                        epcLido.numVeiculo[0] = tags_[i].epc[6];
                        epcLido.numVeiculo[1] = tags_[i].epc[5];
                        if(buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido) == 0){ // Veiculo esta na lista?  
                            adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido);

                            //EventoPassagem novoEvento;
                            //novoEvento.id_veiculo[0] = epcLido.byte2;
                            //novoEvento.id_veiculo[1] = epcLido.byte1;
                            //novoEvento.tipoMovimento = MOVIMENTO_SAIDA; 
                            //cadastrarNovoEvento(epcLido, MOVIMENTO_SAIDA);
                            contadorDeTagsQueSairam = contadorDeTagsQueSairam + 1;
                            sprintf(mensagem, "<- Evento Saida de Veiculo: %02x%02x\r\n", epcLido.numVeiculo[1], epcLido.numVeiculo[0]);
                            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
                        }else{
                            //removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido);                              
                        }
                    }
                }
            }
        }
    }
}

void lerBarreiraDeUltrasom(void){
    static char barreiraInterrompida = 0;
    unsigned char mensagem[50];
    
    if(SENSOR_PASSAGEM_VEICULO == 1){
        BSP_setLedAntena(4,1);
        if(barreiraInterrompida == 0){
            contadorDeCarrosQuePassaram = contadorDeCarrosQuePassaram + 1;
            barreiraInterrompida = 1;
            sprintf(mensagem, "Carros que passaram: %d\r\n", contadorDeCarrosQuePassaram);
            enviaDadosParaUSBserial(mensagem, strlen(mensagem));
        }
    }else{
        barreiraInterrompida = 0;
        BSP_setLedAntena(4,0);
    }
}

void LiberaVeiculosNaClausura(void){
    unsigned char mensagem[100];
    
    sprintf(mensagem, "Veículos na clausura! Aguardando abrir portão interno...\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));    
    while(SENSOR_PORTAO2 == FECHADO){
        if(BOTAO_CALAR_ALARME == 0){
            flagAlarme = 0;
        }
    }
    
    sprintf(mensagem, "Portão interno aberto! Aguardando fechar...\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    while(SENSOR_PORTAO2 == ABERTO){
        flagAlarme = 0;
    }
    sprintf(mensagem, "Portão interno fechado...\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    
}


void trataAlarmeDoPortaoDeGaragem(void){
    if(flagAlarme == 1){
        ALARME = !ALARME;
    }else{
        ALARME = 0;
    }
}


//void CarregaEpcLido(unsigned char index){
        
//    epcLido.numProprietario[0] = tags_[index].epc[0];
//    epcLido.numProprietario[1] = tags_[index].epc[1];
//    epcLido.numProprietario[2] = tags_[index].epc[2];
//    epcLido.numCondominio[0] = tags_[index].epc[3];
//    epcLido.numCondominio[1] = tags_[index].epc[4];
//    epcLido.numVeiculo[0] = tags_[index].epc[5];
//    epcLido.numVeiculo[1] = tags_[index].epc[6];
//}


