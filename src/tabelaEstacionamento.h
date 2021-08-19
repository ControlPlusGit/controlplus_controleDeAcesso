/* 
 * File:   tabela.h
 * Author: Vitor
 *
 * Created on 17 de Fevereiro de 2020, 10:52
 */

#ifndef TABELA_H
#define	TABELA_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
     

#define NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO 1000
#define TAMANHO_EPC_REGISTRADO_NA_TABELA 2 //BYTES 
  
    
typedef union {
    unsigned int tag;
    struct{
        unsigned char numVeiculo[2];
    };
}EPC_Estacionamento;


typedef struct{        
    EPC_Estacionamento epc[NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO];   
    int ponteiroTabela;
}TabelaDeEpcDeEstacionamento;


int binarySearchNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *arr, int l, int r, long _epc);
void adicionarRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc);
void removerTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela);
int buscarRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc);
int buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc);
int removerRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc);
void zeraPointeiroDaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela);
void testTabelaDeEPC_should_IncludeSearchExclude(void);
unsigned char gravarListaDeVeiculosLiberados(void);

//int8_t listaDeVeiculosLiberados(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TABELADEEXCLUSAO_H */

