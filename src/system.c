#include <stdint.h>

#include "system.h"
#include "platform.h"
#include "spi1.h"
#include "tmr2.h"
#include "config_i2c3.h"
#include "uart_driver.h"
#include "delay.h"

#include "I2C1/i2c1_driver.h"
#include "I2C3/i2c3_driver.h"

#include "RTC/DS1307.h"
#include "EEPROM/24LC256.h"

#include "FSM_ESP8266.h"
#include "FSM_TabelaDeEstacionamento.h"
#include "setup_usb.h"
#include "FSM_DataHora.h"
#include "FSM_KeepAlive.h"

uint16_t globalCounter_ms = 0;

volatile void tick ( void ){   
    
    globalCounter_ms++;
        
    executaMaquinaDeEstados_ESP8266();    
    executaMaquinaDeEstados_TabelaDeEstacionamento();
    commandHandlerPortaUSB();
    executaMaquinaDeEstados_DataHora();
    executaMaquinaDeEstados_KeepAlive();
}

uint16_t tick_getTimerCounter(void){
    return globalCounter_ms;
}

void SYSTEM_Initialize(void){
    uint32_t baudrate, realrate;
    
    CNPU1bits.CN15PUE = 1; 
    CNPU2bits.CN16PUE = 1;
    CNPU2bits.CN19PUE = 1;
    CNPU4bits.CN49PUE = 1;
    CNPU4bits.CN56PUE = 1;
    CNPU4bits.CN57PUE = 1;
    CNPU2bits.CN28PUE = 1;
    
    platformInit();
    
    SPI1_Initialize();
    
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes
    
    TMR2_LoadInterruptCallback(tick);
    
    TMR2_Initialize();
   
    i2c1_driver_init(100000); // Inicializa o RTC com 100KHz
    
    RTC_DS1307_load_callbacks(  i2c1_driver_start,
                                i2c1_driver_restart,
                                i2c1_driver_stop,
                                i2c1_driver_TXData,
                                i2c1_driver_getRXData,
                                i2c1_driver_sendAck,                                
                                delay_ms);
    
    RTC_DS1307_I2C_config();
    
    i2c3_driver_init(100000); // Inicializa a EEPROM com 100 KHz
    
    EEPROM_24LC256_load_callbacks(i2c3_driver_start,
                                  i2c3_driver_restart,
                                  i2c3_driver_stop,
                                  i2c3_driver_TXData,
                                  i2c3_driver_getRXData,
                                  i2c3_driver_sendAck,
                                  delay_ms);
    
    baudrate = 115200ULL;   
    
    uartTxInitialize(SYSCLK, baudrate, &realrate); 
    
    uart2TxInitialize(SYSCLK, baudrate, &realrate); // ethernet
    
    uart3TxInitialize(SYSCLK, baudrate, &realrate); // usb
    
    uart4TxInitialize(SYSCLK, baudrate, &realrate); // wifi 
}
