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
void SYSTEM_Initialize(void);

uint16_t tick_getTimerCounter(void);

#endif	/* SYSTEM_H */
/**
 End of File
*/

