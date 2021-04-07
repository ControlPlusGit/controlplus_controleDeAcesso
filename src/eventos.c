#include "eventos.h"
#include <stdint.h>
#include "clp.h"
#include "log.h"

uint8_t string[100];

int8_t cadastrarNovoEvento(PilhaEventos *pilhaEventos, EventoPassagem evento){
   
    if(!buscarEvento(pilhaEventos, evento)){
        pilhaEventos->eventos[pilhaEventos->numEventos++] = evento;        
        
        #ifdef LOG_EVENTOS //definido em clp.h
        sprintf(string,"Veiculo %02x%02x fez um movimento de %s",evento.id_veiculo[0],evento.id_veiculo[1],(evento.tipoMovimento == MOVIMENTO_ENTRADA ? "SAIDA":"ENTRADA"));
        logMsg(string);
        #endif
        
        return 1;
        
    }
    else{
        return 0;
    }        
    
}

int8_t buscarEvento(PilhaEventos *pilhaEventos, EventoPassagem evento){
    
    uint16_t i=0;
    
    for(i = 0; i < pilhaEventos->numEventos; i++){
        if(pilhaEventos->eventos[i].id_veiculo[0] == evento.id_veiculo[0] &&
           pilhaEventos->eventos[i].id_veiculo[1] == evento.id_veiculo[1] &&
           pilhaEventos->eventos[i].tipoMovimento == evento.tipoMovimento){
            return 1;
        }        
    }
    return 0;    
}

int8_t removerEvento(PilhaEventos *pilhaEventos, EventoPassagem evento){
    uint16_t i = 0;
    uint16_t j = 0;
    
    for(i = 0; i < pilhaEventos->numEventos; i++){
        if(pilhaEventos->eventos[i].id_veiculo == evento.id_veiculo &&
           pilhaEventos->eventos[i].tipoMovimento == evento.tipoMovimento){
            
            pilhaEventos->eventos[i].id_veiculo[0] = 0;
            pilhaEventos->eventos[i].id_veiculo[1] = 0;
            pilhaEventos->eventos[i].tipoMovimento = 0;
            pilhaEventos->eventos[i].dataEvento;
            
            for(j = i; j < pilhaEventos->numEventos-1; j++){
                pilhaEventos->eventos[j] = pilhaEventos->eventos[j+1];
            }
            return 1;
        }        
    }
    return 0;   
}
