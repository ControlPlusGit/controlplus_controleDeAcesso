
#include <xc.h>
#include <stdio.h>

#include "tmr2.h"
#include "global.h"
#include <libpic30.h>

void (*TMR2_IntCallback)(void);

volatile void TMR2_test_overflowFunction(void);

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt (void)    // interrupt handler for Timer2
{
    (*TMR2_IntCallback)();
    _T2IF = 0;
}

void TMR2_LoadInterruptCallback(void* handler){
    TMR2_IntCallback = (void (*)(void)) handler;
}

//void ligaTimer2 (void){
void TMR2_Initialize(void){

    T2CONbits.TON = 0;
    //T2CON = 0x0000;
    PR2 = 16000;
    TMR2 = 0;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;
}

int i=0;
char mensagem[100];

void test_TMR2_OverflowInterrupt_should_Execute(void){
    
    TMR2_LoadInterruptCallback(TMR2_test_overflowFunction);
    
    __delay_ms(100);
    
    if(i > 2){
        sprintf(mensagem,"Interrupcao ocorrendo conforme esperado");
    }
    
}

volatile void TMR2_test_overflowFunction(void){
    i++;
}



