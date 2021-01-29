
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DELAY_H_
#define	_DELAY_H_

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
#include "global.h"
#include <libpic30.h>

#define delay_ms(x) __delay_ms(x)
#define delay_us(x) __delay_us(x)
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _DELAY_H_ */

