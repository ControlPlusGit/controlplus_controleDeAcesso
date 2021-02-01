/*
 * 
 * Control Plus - Controles e Sistemas
 * 
 * Autor: Eng. Vitor Alho
 * Data: Dezembro de 2020
 * 
 * Arquivo gerado com o uso do MCC (Microchip Code Configurator) e personalizado em seguida.
 * 
 * As funções utilizadas nesta biblioteca são as listadas abaixo. 
 * 
 * /!\ Demais funções precisam ser testadas antes!!!
 *  
 *   I2C1_Status_Message i2c1_driver_init(void);
 * 
 *   I2C1_Status_Message i2c1_driver_start(uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_restart(uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_stop(uint8_t timeout);
 *     
 *   I2C1_Status_Message i2c1_driver_TXData(uint8_t dado, uint8_t timeout);
 * 
 *   I2C1_Status_Message i2c1_driver_getRXData(uint8_t timeout);
 * 
 *   void i2c1_driver_close(void);
 * 
*/

#include "../system.h"
#include "i2c1_driver.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../delay.h"

#ifndef FCY
#define FCY _XTAL_FREQ/2
#endif
    
#include <libpic30.h>

void (*i2c1_driver_busCollisionISR)( void );
void (*i2c1_driver_Masteri2cISR)( void );
void (*i2c1_driver_Slavei2cISR)( void );

I2C1_Status_Message i2c1_driver_init( uint32_t i2c_baudRate ) {
    
    if(!I2C1CONbits.I2CEN)
    {
        
///////////////////////////////////////////////////////////     
//                   REGISTRADOR I2C1STAT
///////////////////////////////////////////////////////////
//      Esse registrador contém todos os status de operações de envio e recebimento.
//        
//      Limpamos ele para iniciar o periférico
        
        I2C1STAT = 0x0;
        
///////////////////////////////////////////////////////////     
//                   REGISTRADOR I2C1CON
///////////////////////////////////////////////////////////
//
//        bit 15 I2CEN: I2Cx Enable bit
//              1 = Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins
//              0 = Disables the I2Cx module. All I2C? pins are controlled by port functions
//        
//        bit 14 Unimplemented: Read as ?0?
//       
//        bit 13 I2CSIDL: Stop in Idle Mode bit
//              1 = Discontinues module operation when device enters an Idle mode
//              0 = Continues module operation in Idle mode
//       
//        bit 12 SCLREL: SCLx Release Control bit (when operating as I2C slave)
//              1 = Releases SCLx clock
//              0 = Holds SCLx clock low (clock stretch)
//              If STREN = 1:
//              Bit is R/W (i.e., software may write ?0? to initiate stretch and write ?1? to release clock). Hardware is clear
//              at the beginning of slave transmission. Hardware is clear at the end of slave reception.
//              If STREN = 0:
//              Bit is R/S (i.e., software may only write ?1? to release clock). Hardware clear at beginning of slave
//              transmission.
//       
//        bit 11 IPMIEN: Intelligent Platform Management Interface (IPMI) Enable bit
//              1 = IPMI Support mode is enabled; all addresses are Acknowledged
//              0 = IPMI mode is disabled
//       
//        bit 10 A10M: 10-Bit Slave Addressing bit
//              1 = I2CxADD is a 10-bit slave address
//              0 = I2CxADD is a 7-bit slave address
//       
//        bit 9 DISSLW: Disable Slew Rate Control bit
//              1 = Slew rate control disabled
//              0 = Slew rate control enabled
//       
//        bit 8 SMEN: SMBus Input Levels bit
//              1 = Enables I/O pin thresholds compliant with SMBus specifications
//              0 = Disables the SMBus input thresholds
//       
//        bit 7 GCEN: General Call Enable bit (when operating as I2C slave)
//              1 = Enables interrupt when a general call address is received in the I2CxRSR (module is enabled for
//              reception)
//              0 = General call address disabled
//       
//        bit 6 STREN: SCLx Clock Stretch Enable bit (when operating as I2C slave)
//              Used in conjunction with the SCLREL bit.
//              1 = Enables software or receive clock stretching
//              0 = Disables software or receive clock stretching
//
//        bit 5 ACKDT: Acknowledge Data bit (when operating as I2C master. Applicable during master receive.)
//              Value that will be transmitted when the software initiates an Acknowledge sequence.
//              1 = Sends NACK during Acknowledge
//              0 = Sends ACK during Acknowledge
//       
//        bit 4 ACKEN: Acknowledge Sequence Enable bit (when operating as I2C master. Applicable during master
//        receive.)
//              1 = Initiates Acknowledge sequence on SDAx and SCLx pins and transmits the ACKDT data bit.
//              Hardware is clear at the end of the master Acknowledge sequence.
//              0 = Acknowledge sequence is not in progress
//       
//        bit 3 RCEN: Receive Enable bit (when operating as I2C master)
//              1 = Enables Receive mode for I2C. Hardware is clear at the end of the eighth bit of the master receive
//              data byte.
//              0 = Receive sequence is not in progress
//      
//        bit 2 PEN: Stop Condition Enable bit (when operating as I2C master)
//              1 = Initiates Stop condition on the SDAx and SCLx pins. Hardware is clear at the end of the master
//              Stop sequence.
//              0 = Stop condition is not in progress
//      
//        bit 1 RSEN: Repeated Start Condition Enabled bit (when operating as I2C master)
//              1 = Initiates Repeated Start condition on the SDAx and SCLx pins. Hardware is clear at the end of the
//              master Repeated Start sequence
//              0 = Repeated Start condition is not in progress
//       
//        bit 0 SEN: Start Condition Enabled bit (when operating as I2C master)
//              1 = Initiates Start condition on SDAx and SCLx pins. Hardware is clear at end of the master Start
//              sequence.
//              0 = Start condition is not in progress        
        
        I2C1CON = 0x8000; // Setamos o bit I2CEN, habilitando o módulo I2C
        
///////////////////////////////////////////////////////////     
//         CALCULO DO BAUDRATE DO BARRAMENTO I2C
///////////////////////////////////////////////////////////
//        
//      Usando o MCC para gerar um clock de 100 KHz, obtive o valor 78 com base no calculo abaixo:
//
//      I2CxBRG = ( FCY / FSCL ) - ( FCY / 10000 ) - 1
//
//      Sendo: 
//
//      FCY = Fosc / 2 
//
//      FSCL = 100 KHz -> Frequência desejada no I2C
//
//      Substituindo os valores na equação, para um clock de 100 KHz no barramento I2C, obtemos o valor 78,2
//
//      Então:
//
//      I2C1BRG = 78;
//        
//      Ao testar na prática, o resultado dá 79, resultando em um clock de 99 KHz
//        
//      Por isso, coloquei um -1 no final da equação para corrigir os erros de arredondamento
//        
//      Comparei com os valores do datasheet e analisei o resultado do cálculo para todos os valores de frequência 
//      do barramento I2C com o oscilador em 8MHz.
//                
//            |     I2C     |      FCY      |       I2CxBRG     |
//            |   100 kHz   |    8000000    |          78       |
//            |   400 kHz   |    8000000    |          18       |
//            |     1 MHz   |    8000000    |          06       |
                
        I2C1BRG = ( ( FCY / i2c_baudRate ) - ( FCY / 10000000UL ) - 1 ) -1;
        
        return I2C1_OK;
        
    }
    else
        
        return I2C1_ERROR;
    
}

I2C1_Status_Message i2c1_driver_start(int16_t timeout) {
    I2C1CONbits.SEN = 1;
    
    while( I2C1CONbits.SEN && timeout > 0 ) {
        
        timeout--;
        
    }    
    
    if( timeout < 0 ) {
    
        return I2C1_TIMEOUT;
    
    }
    
    return I2C1_OK;
    
}

I2C1_Status_Message i2c1_driver_sendAck( int16_t timeout ) {
    
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.ACKEN = 1;
    
    while( I2C1CONbits.ACKEN && timeout > 0) {
        
        timeout--;
        
    }
    
    if( timeout < 0 ) {
    
        return I2C1_TIMEOUT;
    
    }
    
    return I2C1_OK;
    
}

I2C1_Status_Message i2c1_driver_restart(int16_t timeout) {
    I2C1CONbits.RSEN = 1;
    
    while( I2C1CONbits.RSEN && timeout > 0 ) {
        
        timeout--;
        
    }   
    
    if( timeout < 0 ) {
    
        return I2C1_TIMEOUT;
    
    }
    
    return I2C1_OK;
    
}

I2C1_Status_Message i2c1_driver_stop(int16_t timeout) {
    I2C1CONbits.PEN = 1;
    
    while( I2C1CONbits.PEN && timeout > 0 ) {
        
        timeout--;
        
    }
    
    if( timeout < 0 ) {
    
        return I2C1_TIMEOUT;
    
    }
    
    return I2C1_OK;
    
}

I2C1_Status_Message i2c1_driver_getRXData(uint8_t *data, int16_t timeout) {
    
    I2C1CONbits.RCEN = 1;
    
    while( !I2C1STATbits.RBF && timeout >= 0) {
        
        timeout--;
        
    }
    
    if( timeout < 0 ) {
        return I2C1_TIMEOUT;
    }
    
    *data = I2C1RCV;
    
    return I2C1_OK;
}

I2C1_Status_Message i2c1_driver_TXData(uint8_t data, int16_t timeout) {
    
    I2C1TRN = data;
    
    while( I2C1STATbits.TRSTAT && ( timeout >= 0 ) ) {
        
        timeout--;
        
    }
    
    if( timeout < 0 ) {
    
        return I2C1_TIMEOUT;
    
    }
    
    return I2C1_OK;
    
}

void i2c1_driver_close( void ) {
    I2C1CONbits.I2CEN = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// FIM DAS FUNÇÕES TESTADAS /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/* Interrupt Control */
inline void i2c1_enableIRQ( void ) {
    IEC1bits.MI2C1IE = 1;
    IEC1bits.SI2C1IE = 1;
}

inline bool i2c1_IRQisEnabled(void) {
    return IEC1bits.MI2C1IE || IEC1bits.SI2C1IE;
}

inline void i2c1_disableIRQ(void) {
    IEC1bits.MI2C1IE = 0;
    IEC1bits.SI2C1IE = 0;
}

inline void i2c1_clearIRQ(void) {
    IFS1bits.MI2C1IF = 0;
    IFS1bits.SI2C1IF = 0;
}

inline void i2c1_setIRQ(void) {
    IFS1bits.MI2C1IF = 1;
    IFS1bits.SI2C1IF = 1;
}

inline void i2c1_waitForEvent(uint16_t *timeout) {
    //uint16_t to = (timeout!=NULL)?*timeout:100;
    //to <<= 8;
    if((IFS1bits.MI2C1IF == 0) && (IFS1bits.SI2C1IF == 0))
    {
        while(1)// to--)
        {
            if(IFS1bits.MI2C1IF || IFS1bits.SI2C1IF) break;
            delay_us(100);
        }
    }
}

I2C1_Status_Message i2c1_driver_initSlaveHardware(void) {
    if(!I2C1CONbits.I2CEN)
    {

    /* NOTE on SEN:
     * SEN will be set enabling clock stretching.  This is because we don't know how
     * long the user will take to process data bytes in their callbacks.  If they are fast,
     * we may not need to stretch the clock.  If they are slow, we need to stretch the clock.
     * If we ALWAYS stretch the clock, we will release the clock when the ISR is complete.
     */

    /* NOTE on PCIE:
     * PCIE will be set to enable interrupts on STOP.  This will allow us know when
     * the master is finished
     */

    /* NOTE on SCIE:
     * SCIE will be set to enable interrupts on START.  This will allow us to detect
     * both a START and a RESTART event and prepare to restart communications.
     */
        
        I2C1CONbits.STREN = 1;
        
        I2C1CONbits.I2CEN = 1;
        return I2C1_OK;
    }
    return I2C1_ERROR;
}

inline void i2c1_driver_resetBus(void) {
    
}

inline bool i2c1_driver_isNACK(void) {
    return I2C1STATbits.ACKSTAT;
}

inline void i2c1_driver_sendNACK(void) {
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ACKEN = 1; // start the ACK/NACK
}

inline void i2c1_driver_releaseClock(void) {
    I2C1CONbits.SCLREL = 1;
}

inline bool i2c1_driver_isBuferFull(void) {
    return I2C1STATbits.RBF || I2C1STATbits.TBF;
}

inline bool i2c1_driver_isStart(void) {
    return I2C1STATbits.S;
}

inline bool i2c1_driver_isAddress(void) {
    return !I2C1STATbits.D_A;
}

inline bool i2c1_driver_isStop(void) {
    return I2C1STATbits.P;
}

inline bool i2c1_driver_isData(void) {
    return I2C1STATbits.D_A;
}

inline bool i2c1_driver_isRead(void) {
    return I2C1STATbits.R_W;
}

inline void i2c1_driver_clearBusCollision(void) {
    I2C1STATbits.BCL = 0; // clear the bus collision.
}

inline void i2c1_driver_enableStartIRQ(void) {
    
}

inline void i2c1_driver_disableStartIRQ(void) {
    
}

inline void i2c1_driver_enableStopIRQ(void) {
    
}

inline void i2c1_driver_disableStopIRQ(void) {
    
}

inline void i2c1_driver_setBusCollisionISR(I2C1_interruptHandler handler){
    i2c1_driver_busCollisionISR = handler;
}

inline void i2c1_driver_setMasterI2cISR(I2C1_interruptHandler handler){
    i2c1_driver_Masteri2cISR = handler;
}

inline void i2c1_driver_setSlaveI2cISR(I2C1_interruptHandler handler){
    i2c1_driver_Slavei2cISR = handler;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C1Interrupt ( void ) {
    (*i2c1_driver_Masteri2cISR)();
}
void __attribute__ ( ( interrupt, no_auto_psv ) ) _SI2C1Interrupt ( void ) {
    (*i2c1_driver_Slavei2cISR)();
}
