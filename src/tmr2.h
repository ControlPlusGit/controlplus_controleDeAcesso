
#ifndef _TMR2_H_
#define	_TMR2_H_

#include <xc.h> 
#include "log.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void TMR2_Initialize(void);

void TMR2_LoadInterruptCallback(void* handler);

void test_TMR2_OverflowInterrupt_should_Execute(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _TMR2_H_ */

