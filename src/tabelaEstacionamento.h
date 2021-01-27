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

#define SIM 1
#define NAO 0
    
#define NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO 1000
    
#define TAMANHO_EPC_REGISTRADO_NA_TABELA 2 //BYTES 
      
    typedef union {
        uint16_t tag;
        struct{
            uint8_t byte1:8;
            uint8_t byte2:8; 
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
    
    void zeraPointeiroDaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela);
    
    void testTabelaDeEPC_should_IncludeSearchExclude(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TABELADEEXCLUSAO_H */

