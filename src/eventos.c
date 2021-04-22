#include "eventos.h"
#include <stdint.h>
#include "clp.h"
#include "log.h"
#include "FSM_EventosDePassagem.h"
#include "RTC/rtc.h"

uint8_t string[100];

extern eventoPassagem novoEventoDePassagem;

int8_t cadastrarNovoEvento(PilhaEventos *pilhaEventos, EventoPassagem evento){
    
    Calendar dataHora;
    
    if(pilhaEventos->numEventos >= NUM_MAX_EVENTOS){
        pilhaEventos->numEventos = 0;
    }
    if(!buscarEvento(pilhaEventos, evento)){
        pilhaEventos->eventos[pilhaEventos->numEventos++] = evento;        
                
        //IMPLEMENTANDO GRAVACAO DE EVENTO NA EEPROM
        
        novoEventoDePassagem.EPC_naoUsado[0] = '0';
        novoEventoDePassagem.EPC_naoUsado[1] = '0';
        novoEventoDePassagem.EPC_naoUsado[2] = '0';
        novoEventoDePassagem.EPC_naoUsado[3] = '0';
        novoEventoDePassagem.EPC_naoUsado[4] = '0';
        novoEventoDePassagem.EPC_naoUsado[5] = '0';
        novoEventoDePassagem.EPC_naoUsado[6] = '0';
        novoEventoDePassagem.EPC_naoUsado[7] = '0';

        novoEventoDePassagem.tipoMovimento[0] = evento.tipoMovimento;
        novoEventoDePassagem.tipoMovimento[1] = '0';
        novoEventoDePassagem.tipoMovimento[2] = '0';
        novoEventoDePassagem.tipoMovimento[3] = '0';
        novoEventoDePassagem.tipoMovimento[4] = '0';
        novoEventoDePassagem.tipoMovimento[5] = '0';
        novoEventoDePassagem.tipoMovimento[6] = '0';
        novoEventoDePassagem.tipoMovimento[7] = '0';

        novoEventoDePassagem.EPC_veiculo[0] = (((unsigned char)evento.id_veiculo[0] >> 4) + '0');
        novoEventoDePassagem.EPC_veiculo[1] = (((unsigned char)evento.id_veiculo[0] & 0x0F) + '0');
        novoEventoDePassagem.EPC_veiculo[2] = (((unsigned char)evento.id_veiculo[1] >> 4) + '0');
        novoEventoDePassagem.EPC_veiculo[3] = (((unsigned char)evento.id_veiculo[1] & 0x0F) + '0');
        novoEventoDePassagem.EPC_veiculo[4] = '0';
        novoEventoDePassagem.EPC_veiculo[5] = '0';
        novoEventoDePassagem.EPC_veiculo[6] = '0';
        novoEventoDePassagem.EPC_veiculo[7] = '0';

        RTC_calendarRequest(&dataHora); 

        novoEventoDePassagem.dia = dataHora.tm_mday;
        novoEventoDePassagem.mes = dataHora.tm_mon+1;
        novoEventoDePassagem.ano = dataHora.tm_year-100;

        novoEventoDePassagem.hora = dataHora.tm_hour;
        novoEventoDePassagem.minuto = dataHora.tm_min;
        novoEventoDePassagem.segundo = dataHora.tm_sec;

        //inicializaMaquinaDeEstados_EventosDePassagem();                    

        criarEventoDePassagem(&novoEventoDePassagem);                    

        //bloqueiaMaquinaDeEstados_EventosDePassagem(); 
        
        //FIM DA GRAVACAO DE EVENTO NA EEPROM
        
        #ifdef LOG_EVENTOS //definido em clp.h
        sprintf(string,"\n\rVeiculo %02x%02x fez um movimento de %s",evento.id_veiculo[0],evento.id_veiculo[1],(evento.tipoMovimento == MOVIMENTO_ENTRADA ? "SAIDA":"ENTRADA"));
        logMsg(string);
        sprintf(string,"\n\rNum. Eventos: %d",pilhaEventos->numEventos);
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
            //pilhaEventos->eventos[i].dataEvento;
            
            for(j = i; j < pilhaEventos->numEventos-1; j++){
                pilhaEventos->eventos[j] = pilhaEventos->eventos[j+1];
            }
            return 1;
        }        
    }
    return 0;   
}
