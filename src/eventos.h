/* 
 * File:   eventos.h
 * Author: Vitor
 *
 * Created on 6 de Abril de 2021, 14:44
 */

#ifndef EVENTOS_H
#define	EVENTOS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include "RTC/rtc.h"  
#include "tabelaEstacionamento.h"
    
    
    
    
    
    
#define SIM 1

//#define TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM 1
//#define TEMPO_AGUARDANDO_ACK_EVENTOS_DE_PASSAGEM 2000
#define TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES 10
//#define NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS 900
//#define VALOR_FLAG_INICIALIZACAO_EEPROM 0xA4 // Para resetar a eeprom basta mudar esse valor e gravar o firmware novamente.
//#define ENDERECO_FLAG_INICIALIZACAO_EEPROM 1995
#define MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS 1996
#define LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS 1997
#define MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS 1998
#define LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS 1999
#define ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS 2000

       
#define NUM_MAX_EVENTOS_CADASTRADOS 100
#define MOVIMENTO_ENTRADA   1
#define MOVIMENTO_SAIDA     0
    
    
typedef struct{ 
    unsigned char flagDeRegistro;
    unsigned char EPC_veiculo[2];
    unsigned char tipoMovimento;
    unsigned char dia;
    unsigned char mes;
    unsigned char ano;
    unsigned char hora;
    unsigned char minuto;
    unsigned char segundo;
}eventoPassagem;

    
//typedef struct{
//        uint8_t id_veiculo[2];
//        uint8_t tipoMovimento;
//        Calendar dataEvento;
//    }EventoPassagem;    

    
//typedef struct{
//        EventoPassagem eventos[NUM_MAX_EVENTOS_CADASTRADOS];
//        uint16_t numEventos;
//    }PilhaEventos;
    
    

void lerEventoDePassagemNaEEPROM(eventoPassagem *evento,int endereco);
//void criarEventoDePassagem(eventoPassagem *novoEventoDePassagem);
void inicializaEventosDePassagem(void);
//void habilitaMaquinaDeEstados_EventosDePassagem(void);
//void executaMaquinaDeEstados_EventosDePassagem(void);
//void bloqueiaMaquinaDeEstados_EventosDePassagem(void);
//void limpaBufferNaMaquinaDeEstados_EventosDePassagem(void);
 
//unsigned char cadastrarNovoEvento(EPC_Estacionamento veiculo, char movimento);
unsigned char cadastrarNovoEvento(unsigned int veiculo, char movimento);
unsigned char enviarEventoParaOServidor(void);
//unsigned char buscarEvento(PilhaEventos *pilhaEventos, EventoPassagem evento);

unsigned char VerificaSeHaEventosParaSeremEnviados(void);
void IncrementaContadorDeEventosEnviados(void);
void ReiniciaPonteiroDeMemoriaDosEventosNaEeprom(void);
void limpaEventosArmazenadosNaEeprom(void);
    
 



    
    
#ifdef	__cplusplus
}
#endif

#endif	/* EVENTOS_H */

