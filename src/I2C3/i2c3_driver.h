/*
 * 
 * Control Plus - Controles e Sistemas
 * 
 * Autor: Eng. Vitor Alho
 * Data: Dezembro de 2020
 * 
 * As funções utilizadas nesta biblioteca são as listadas abaixo. 
 * 
 * /!\ Demais funções precisam ser testadas antes!!!
 *  
 *   I2C3_Status_Message  i2c3_driver_init(uint32_t i2c_baudRate);
 * 
 *   I2C3_Status_Message i2c3_driver_start(uint8_t timeout);
 *     
 *   I2C3_Status_Message i2c3_driver_TXData(uint8_t dado, uint8_t timeout);
 * 
 *   I2C3_Status_Message i2c3_driver_restart(uint8_t timeout);
 * 
 *   I2C3_Status_Message i2c3_driver_sendAck(int16_t timeout)
 * 
 *   I2C3_Status_Message i2c3_driver_getRXData(uint8_t timeout);
 * 
 *   I2C3_Status_Message i2c3_driver_stop(uint8_t timeout);
 * 
*/

#ifndef __I2C3_DRIVER_H
#define __I2C3_DRIVER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define INLINE  inline 

typedef enum{    
    I2C3_TIMEOUT = -1,   
    I2C3_OK,    
    I2C3_ERROR              
} I2C3_Status_Message;
        
typedef void (*I2C3_interruptHandler)(void);

/* Interrupt interfaces */
INLINE void i2c3_enableIRQ(void);
INLINE bool i2c3_IRQisEnabled(void);
INLINE void i2c3_disableIRQ(void);
INLINE void i2c3_clearIRQ(void);
INLINE void i2c3_setIRQ(void);
INLINE void i2c3_waitForEvent(uint16_t*);

/* I2C interfaces */
I2C3_Status_Message  i2c3_driver_init(uint32_t i2c_baudRate);
I2C3_Status_Message i2c3_driver_start(int16_t timeout);
I2C3_Status_Message i2c3_driver_restart(int16_t timeout);
I2C3_Status_Message i2c3_driver_stop(int16_t timeout);
I2C3_Status_Message i2c3_driver_sendAck(int16_t timeout);
I2C3_Status_Message i2c3_driver_getRXData(uint8_t *data, int16_t timeout);
I2C3_Status_Message i2c3_driver_TXData(uint8_t data, int16_t timeout);
/* arbitration interface */
void i2c3_driver_close(void);
void i2c3_driver_resetBus(void);

INLINE bool i2c3_driver_isNACK(void);
INLINE void i2c3_driver_sendNACK(void);
INLINE void i2c3_driver_clearBusCollision(void);

I2C3_Status_Message  i2c3_driver_initSlaveHardware(void);
INLINE void i2c3_driver_releaseClock(void);
INLINE bool i2c3_driver_isBuferFull(void);
INLINE bool i2c3_driver_isStart(void);
INLINE bool i2c3_driver_isStop(void);
INLINE bool i2c3_driver_isAddress(void);
INLINE bool i2c3_driver_isData(void);
INLINE bool i2c3_driver_isRead(void);
INLINE void i2c3_driver_enableStartIRQ(void);
INLINE void i2c3_driver_disableStartIRQ(void);
INLINE void i2c3_driver_enableStopIRQ(void);
INLINE void i2c3_driver_disableStopIRQ(void);

INLINE void i2c3_driver_setBusCollisionISR(I2C3_interruptHandler handler);
INLINE void i2c3_driver_setMasterI2cISR(I2C3_interruptHandler handler);
INLINE void i2c3_driver_setSlaveI2cISR(I2C3_interruptHandler handler);

#endif // __I2C3_DRIVER_H
