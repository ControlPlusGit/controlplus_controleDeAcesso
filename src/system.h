/* 
 * File:   system.h
 * Author: Vitor
 *
 * Created on 1 de Fevereiro de 2021, 13:51
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ  16000000UL
#endif

#ifndef FCY
#define FCY _XTAL_FREQ/2
#endif

#ifndef SYSCLK
#define SYSCLK _XTAL_FREQ
#endif

#include "xc.h"
#include "stdint.h"
#include <libpic30.h>

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */

extern uint16_t delayLogicaDeSaida;
extern uint8_t flagIniciarContadorDelayEntrada;
extern uint8_t flagIniciarContadorDelaySaida;

extern uint16_t delayLogicaDeEntrada;
extern uint8_t flagDelayEntradaCompleto;
extern uint8_t flagDelaySaidaCompleto;

extern uint16_t timerSaida1;
extern uint8_t flagIniciarContadorTimerSaida1;
extern uint8_t flagDelayTimerSaida1Completo;

extern uint16_t timerSaida2;
extern uint8_t flagIniciarContadorTimerSaida2;
extern uint8_t flagDelayTimerSaida2Completo;

void SYSTEM_Initialize(void);

uint16_t tick_getTimerCounter_ms(void);

uint16_t tick_getTimerCounter_seg(void);

uint16_t tick_getTimerCounter_min(void);

#endif	/* SYSTEM_H */
/**
 End of File
*/

