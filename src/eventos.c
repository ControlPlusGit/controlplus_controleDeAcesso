#include "eventos.h"
#include <stdint.h>
#include <string.h>
#include "clp.h"
#include "log.h"
#include "RTC/rtc.h"
#include "tabelaEstacionamento.h"
#include "EEPROM/eeprom.h"
#include "EEPROM/24LC256.h"
#include "setup_usb.h"
#include "USR_TCP232.h"
//#include "FSM_EventosDePassagem.h"

uint8_t string[100];
unsigned int eventosDePassagemCadastrados = 0;
unsigned int eventosDePassagemEnviados = 0;


unsigned char idLeitor[20];

//extern eventoPassagem novoEventoDePassagem;

//unsigned char cadastrarNovoEvento(EPC_Estacionamento veiculo, char movimento){
unsigned char cadastrarNovoEvento(unsigned int veiculo, char movimento){
    
    unsigned int endereco;
    unsigned char temp = 0;
    unsigned char numVeiculo[2];
    Calendar dataHora;
    
    endereco = ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS + (eventosDePassagemCadastrados * TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES);
    RTC_calendarRequest(&dataHora); 

    numVeiculo[0] =  veiculo & 0x00FF;
    numVeiculo[1] =  veiculo >> 8 & 0x00FF;
    
    EscreverNaEEprom(endereco, 0xAA);
    EscreverNaEEprom(endereco+1, numVeiculo[0]); //EscreverNaEEprom(endereco+1, veiculo.numVeiculo[0]);
    EscreverNaEEprom(endereco+2, numVeiculo[1]); //EscreverNaEEprom(endereco+2, veiculo.numVeiculo[1]);
    EscreverNaEEprom(endereco+3, movimento);
    EscreverNaEEprom(endereco+4, dataHora.tm_mday);
    EscreverNaEEprom(endereco+5, dataHora.tm_mon);
    EscreverNaEEprom(endereco+6, dataHora.tm_year);
    EscreverNaEEprom(endereco+7, dataHora.tm_hour);
    EscreverNaEEprom(endereco+8, dataHora.tm_min);
    EscreverNaEEprom(endereco+9, dataHora.tm_sec);

    eventosDePassagemCadastrados = eventosDePassagemCadastrados + 1;
    if(eventosDePassagemCadastrados > NUM_MAX_EVENTOS_CADASTRADOS){
        eventosDePassagemCadastrados = 0;
    }

    temp = (unsigned char)(eventosDePassagemCadastrados >> 8);
    EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,temp);
    temp = (unsigned char)eventosDePassagemCadastrados & 0x00FF;
    EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS,temp); 
    return 1;    
}



void inicializaEventosDePassagem(void){
    unsigned int temp = 0;

    //Carrega ultima posição de eventos de passagem armazenados na eeprom
    LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, &temp);
    eventosDePassagemCadastrados = (unsigned int)temp << 8;
    LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, &temp);
    eventosDePassagemCadastrados |= (unsigned int)temp;

    //Carrega ultima posição de eventos de passagem enviados para o server
    LerDadosDaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, &temp);
    eventosDePassagemEnviados = (unsigned int)temp << 8;
    LerDadosDaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, &temp);
    eventosDePassagemEnviados |= (unsigned int)temp;

    retornaIdDoLeitor(idLeitor);
}


void lerEventoDePassagemNaEEPROM(eventoPassagem *evento,int endereco){      
        
    LerDadosDaEEprom(endereco, &evento->flagDeRegistro);
    LerDadosDaEEprom(endereco+1, &evento->EPC_veiculo[0]);
    LerDadosDaEEprom(endereco+2, &evento->EPC_veiculo[1]);
    LerDadosDaEEprom(endereco+3, &evento->tipoMovimento);
    LerDadosDaEEprom(endereco+4, &evento->dia);
    LerDadosDaEEprom(endereco+5, &evento->mes);
    LerDadosDaEEprom(endereco+6, &evento->ano);
    LerDadosDaEEprom(endereco+7, &evento->hora);
    LerDadosDaEEprom(endereco+8, &evento->minuto);
    LerDadosDaEEprom(endereco+9, &evento->segundo);

}


unsigned char VerificaSeHaEventosParaSeremEnviados(void){
    if(eventosDePassagemCadastrados != eventosDePassagemEnviados){
        return 1;
    }
    return 0;
}


void IncrementaContadorDeEventosEnviados(void){
    unsigned char temp = 0;
    
    eventosDePassagemEnviados++;
    temp = (unsigned char)(eventosDePassagemEnviados >> 8);
    EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, temp);
    temp = (unsigned char)eventosDePassagemEnviados & 0x00FF;
    EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, temp);  
}

void ReiniciaPonteiroDeMemoriaDosEventosNaEeprom(void){
    EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, 0);
    EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS, 0);
    EscreverNaEEprom(MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, 0);
    EscreverNaEEprom(LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS, 0);
    eventosDePassagemCadastrados = 0;
    eventosDePassagemEnviados = 0;
}


void limpaEventosArmazenadosNaEeprom(void){
    unsigned int i;
    unsigned int posicaoInicialDoRegistro;
    unsigned char mensagem[50];
    
    sprintf(mensagem, "limpando memoria de eventos\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
    
    for(i = 0; i < NUM_MAX_EVENTOS_CADASTRADOS; i++){
        posicaoInicialDoRegistro = ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS + (i * TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES);
        EscreverNaEEprom(posicaoInicialDoRegistro, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+1, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+2, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+3, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+4, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+5, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+6, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+7, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+8, 0);
        EscreverNaEEprom(posicaoInicialDoRegistro+9, 0);
    }   
    ReiniciaPonteiroDeMemoriaDosEventosNaEeprom();
    sprintf(mensagem, "memoria reiniciada com sucesso!\r\n");
    enviaDadosParaUSBserial(mensagem, strlen(mensagem));
}





