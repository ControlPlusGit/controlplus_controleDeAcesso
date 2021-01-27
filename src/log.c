
#include <stdint.h>

#include "log.h"

void ( *log_wrapper_function )( uint8_t data );

void loadLogCallbackFunction( void* pointer ) {
    
    log_wrapper_function = ( void (*)( uint8_t ) ) pointer;
    
}

void logMsg( const char* msg ) {
    
    while( *msg != 0 ) {
        
        ( *log_wrapper_function )( *msg );
        
        msg++;
    }
    
}
