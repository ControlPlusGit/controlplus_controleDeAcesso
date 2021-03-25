/* 
 * File:   main.h
 * Author: vitor
 *
 * Created on March 20, 2021, 3:27 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MOVIMENTO_SAIDA 0
#define MOVIMENTO_ENTRADA 1
#define MOVIMENTO_ENTRADA_SAIDA 2
#define MOVIMENTO_SAIDA_ENTRADA 3

#define SAIDA_PORTAO_ENTRADA RELAY_1
#define SAIDA_ALARME_PORTAO_ENTRADA RELAY_3
#define ENTRADA_SENSOR_FECHAMENTO_PORTAO_ENTRADA INPUT_1
#define ENTRADA_SENSOR_BARREIRA_PORTAO_ENTRADA INPUT_3

#define SAIDA_PORTAO_SAIDA RELAY_2
#define SAIDA_ALARME_PORTAO_SAIDA RELAY_4
#define ENTRADA_SENSOR_FECHAMENTO_PORTAO_SAIDA INPUT_2
#define ENTRADA_SENSOR_BARREIRA_PORTAO_SAIDA INPUT_4

/////////////////////////////////////////////
// Green list criada a partir de tabelaEstacionamento.h
/////////////////////////////////////////////
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;     // lista principal ordenada com as tags lidas
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberadosTest; // utilizada para check na gravacao de dados na flash
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Entrada; // lista desordenada com as tags em movimento
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLidosDuranteMovimento_Saida; // lista desordenada com as tags em movimento
    
void marsOne_init(void);
uint8_t realizaLeituraDeAntena(uint8_t antena);
int8_t obtemDadosDaMemoriaFLASH(void);

int8_t adicionaNovaTagNaLista(TabelaDeEpcDeEstacionamento *lista, EPC_Estacionamento tag);
uint8_t realizaLeituraDeAntena(uint8_t antena);
int8_t verificaTagValida(uint8_t *tag);
int8_t ler_antena_entrada(void);
int8_t verificarTagValida_entrada(void);

extern uint8_t flagRealizaLeituraAntenaEntrada;

#define DEBUG

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

