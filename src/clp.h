/* 
 * File:   clp.h
 * Author: vitor
 *
 * Created on March 19, 2021, 2:29 AM
 */

#ifndef CLP_H
#define	CLP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
#define NUM_MAX_VARIAVEIS 100
#define NUM_MAX_TEMPORIZADORES 20
#define NUM_MAX_ENTRADAS_DIGITAIS 4
#define NUM_MAX_SAIDAS_DIGITAIS 4
    
typedef struct{
    uint8_t *var;
}Variavel;

typedef struct{
    int16_t numVarFinal;
    Variavel *var[NUM_MAX_VARIAVEIS];    
}VetorVariavel;

typedef struct{
    uint8_t *var_disparo;
    uint8_t *var_fim;
    uint32_t *tempoProgramado;
    uint32_t contagem;
}Temporizador;

typedef struct{
    Temporizador *temp[NUM_MAX_TEMPORIZADORES];
    uint16_t numTempFinal;
}VetorTemporizador;

uint8_t registraTemporizador(Temporizador *temp);
int8_t verificarTemporizadores(void);
void CLP_inicializaTemporizadores(void);
void CLP_executa(void);
void CLP_liberaExecucao(void);
void CLP_atualizaEntradas(void);
void CLP_executaLogica(void);
void CLP_atualizaSaidas(void);

#define TEMPORIZADOR(x,y) uint8_t dsp_##x; uint8_t fim_##x; Temporizador timer_##x = {&dsp_##x,&fim_##x,&y,0};
#define CADASTRAR_TEMPORIZADOR(x) registraTemporizador(&timer_##x);
#define ENTRADA_DIGITAL(x) uint8_t x;
#define SAIDA_DIGITAL(x) uint8_t x;
#define SINAL_DIGITAL(x) uint8_t x;

extern uint8_t ELC; //Estado logico corrente

#define LDT(x)  ELC=x;
#define LDF(x)  ELC=~x;
#define SEL(x)  ELC=x;    
#define SED(x)  ELC=~x;    
#define E(x)    ELC&=x;
#define EN(x)   ELC&=~x;
#define OU(x)   ELC|=x;
#define OUN(x)  ELC|=~x;
#define SUBIDA  ELC=(ELC&3)==1?1:0;
#define DESCIDA ELC=(ELC&3)==2?1:0;
#define MEMO(x) x=x<<1|(ELC&1);
#define NAO     ELC=~ELC;
#define IF1     if (ELC&1)
#define ENTAO_EXECUTA_BLOCO if (ELC&1)    
#define SET(x)  if (ELC&1) x=x<<1|(ELC&1);
#define RESET(x)if (ELC&1) x=x<<1;


//#define DEBUG 

#ifdef	__cplusplus
}
#endif

#endif	/* CLP_H */

