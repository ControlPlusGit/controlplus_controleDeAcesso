/*
 * 
 * Arquivo: i2c3_driver.h
 * 
 * Control Plus - Controles e Sistemas
 * 
 * Autor: Eng. Vitor Alho
 * Data: Dezembro de 2020
 * 
 * As funções utilizadas nesta biblioteca são as listadas abaixo. 
 * 
 * /!\ Demais funções com interrupção precisam ser testadas antes!!!
 * 
 *   I2C1_Status_Message i2c1_driver_init(uint32_t i2c_baudRate);
 * 
 *   I2C1_Status_Message i2c1_driver_start(uint8_t timeout);
 *     
 *   I2C1_Status_Message i2c1_driver_TXData(uint8_t dado, uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_restart(uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_sendAck(int16_t timeout)
 * 
 *   I2C1_Status_Message i2c1_driver_getRXData(uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_stop(uint8_t timeout);
 * 
*/

#ifndef __I2C1_DRIVER_H
#define __I2C1_DRIVER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "../system.h"

#ifndef FCY
#define FCY _XTAL_FREQ/2
#endif

#include <libpic30.h>

#define INLINE  inline 

typedef enum{    
    I2C1_TIMEOUT = -1,   
    I2C1_OK,    
    I2C1_ERROR              
} I2C1_Status_Message;
        
typedef void (*I2C1_interruptHandler)(void);

/* Interrupt interfaces */
INLINE void i2c1_enableIRQ(void);
INLINE bool i2c1_IRQisEnabled(void);
INLINE void i2c1_disableIRQ(void);
INLINE void i2c1_clearIRQ(void);
INLINE void i2c1_setIRQ(void);
INLINE void i2c1_waitForEvent(uint16_t*);

/* I2C interfaces */
I2C1_Status_Message i2c1_driver_init(uint32_t i2c_baudRate);
I2C1_Status_Message i2c1_driver_start(int16_t timeout);
I2C1_Status_Message i2c1_driver_restart(int16_t timeout);
I2C1_Status_Message i2c1_driver_stop(int16_t timeout);
I2C1_Status_Message i2c1_driver_sendAck(int16_t timeout);
I2C1_Status_Message i2c1_driver_getRXData(uint8_t *data, int16_t timeout);
I2C1_Status_Message i2c1_driver_TXData(uint8_t data, int16_t timeout);
/* arbitration interface */
void i2c1_driver_close(void);
void i2c1_driver_resetBus(void);

INLINE bool i2c1_driver_isNACK(void);
INLINE void i2c1_driver_sendNACK(void);
INLINE void i2c1_driver_clearBusCollision(void);

I2C1_Status_Message  i2c1_driver_initSlaveHardware(void);
INLINE void i2c1_driver_releaseClock(void);
INLINE bool i2c1_driver_isBuferFull(void);
INLINE bool i2c1_driver_isStart(void);
INLINE bool i2c1_driver_isStop(void);
INLINE bool i2c1_driver_isAddress(void);
INLINE bool i2c1_driver_isData(void);
INLINE bool i2c1_driver_isRead(void);
INLINE void i2c1_driver_enableStartIRQ(void);
INLINE void i2c1_driver_disableStartIRQ(void);
INLINE void i2c1_driver_enableStopIRQ(void);
INLINE void i2c1_driver_disableStopIRQ(void);

INLINE void i2c1_driver_setBusCollisionISR(I2C1_interruptHandler handler);
INLINE void i2c1_driver_setMasterI2cISR(I2C1_interruptHandler handler);
INLINE void i2c1_driver_setSlaveI2cISR(I2C1_interruptHandler handler);

#endif // __I2C1_DRIVER_H
