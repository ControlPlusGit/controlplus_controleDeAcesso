
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DELAY_H_
#define	_DELAY_H_

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
#include "system.h"
    
#ifndef FCY
#define FCY _XTAL_FREQ/2
#endif
    
#include <libpic30.h>
    
void delay_ms(uint16_t ms_delay);

void delay_us(uint16_t us_delay);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _DELAY_H_ */

