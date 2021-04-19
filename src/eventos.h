/* 
 * File:   eventos.h
 * Author: Vitor
 *
 * Created on 6 de Abril de 2021, 14:44
 */

#ifndef EVENTOS_H
#define	EVENTOS_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include <stdint.h>
    #include "RTC/rtc.h"
    
    #define NUM_MAX_EVENTOS 20
    
    typedef enum{
        MOVIMENTO_ENTRADA = 0,
        MOVIMENTO_SAIDA
    }TipoMovimento;
    
    typedef struct{
        uint8_t id_veiculo[2];
        uint8_t tipoMovimento;
        Calendar dataEvento;
    }EventoPassagem;
    
    typedef struct{
        EventoPassagem eventos[NUM_MAX_EVENTOS];
        uint16_t numEventos;
    }PilhaEventos;
    
    int8_t cadastrarNovoEvento(PilhaEventos *pilhaEventos, EventoPassagem evento);
    int8_t buscarEvento(PilhaEventos *pilhaEventos, EventoPassagem evento);
    int8_t removerEvento(PilhaEventos *pilhaEventos, EventoPassagem evento);
    
#ifdef	__cplusplus
}
#endif

#endif	/* EVENTOS_H */

