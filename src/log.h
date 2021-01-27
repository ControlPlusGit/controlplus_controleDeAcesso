/* 
 * File:   debug.h
 * Author: Vitor
 *
 * Created on 27 de Janeiro de 2021, 10:20
 */

#ifndef _LOG_H_
#define _LOG_H_

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    void loadLogCallbackFunction( void* pointer );

    void logMsg( const char* msg );

#ifdef	__cplusplus
}
#endif

#endif	/* _LOG_H_ */

