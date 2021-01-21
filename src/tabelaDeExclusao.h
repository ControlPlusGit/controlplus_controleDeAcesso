/* 
 * File:   tabelaDeExclusao.h
 * Author: Vitor
 *
 * Created on 17 de Fevereiro de 2020, 10:52
 */

#ifndef TABELADEEXCLUSAO_H
#define	TABELADEEXCLUSAO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SIM 1
#define NAO 0
    
#define NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_EXCLUSAO 500
    
#define TAMANHO_EPC_REGISTRADO_NA_TABELA 4 //BYTES 
    
#define NUMERO_DE_CARACTERES_GERAIS_QUE_COMPOE_A_MENSAGEM_RECEBIDA 12 //BYTES
   
#define NUMERO_DE_CARACTERES_QUE_O_EPC_OCUPA_NA_MENSAGEM_RECEBIDA 9 //BYTES   8 CARACTERES + 1 PONTO E VIRGULA
        
    typedef union {
        long tag;
        struct{
            char byte1:8;
            char byte2:8;
            char byte3:8;
            char byte4:8;  
        };
    }EPC;
    
    typedef struct{        
        EPC epc[NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_EXCLUSAO];        
    }TabelaDeExclusao;
       
    int binarySearch(TabelaDeExclusao arr, int l, int r, long _epc);
    void adicionarRegistroNaTabelaDeExclusao(EPC _epc);
    void removerTabelaDeExclusao(void);
    int buscarRegistroNaTabelaDeExclusao(EPC _epc);
    void zeraPointeiroDaTabelaDeExclusao(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TABELADEEXCLUSAO_H */

