#include "delay.h"
#include "system.h"
#include <libpic30.h>

void delay_ms(uint16_t ms_delay) {
    
    __delay_ms(ms_delay);
    
}

void delay_us(uint16_t us_delay) {
    
    __delay_us(us_delay);
    
}
