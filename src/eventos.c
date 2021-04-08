#include "eventos.h"
#include <stdint.h>
#include "clp.h"
#include "log.h"

uint8_t string[100];

int8_t cadastrarNovoEvento(PilhaEventos *pilhaEventos, EventoPassagem evento){
    if(pilhaEventos->numEventos >= NUM_MAX_EVENTOS){
        pilhaEventos->numEventos = 0;
    }
    if(!buscarEvento(pilhaEventos, evento)){
        pilhaEventos->eventos[pilhaEventos->numEventos++] = evento;        
                
        //IMPLEMENTANDO GRAVACAO DE EVENTO NA EEPROM
        
//        novoEventoDeParada.EPC_area[0] = ((areaDoVeiculo.byte4 >> 4) + '0');
//        novoEventoDeParada.EPC_area[1] = ((areaDoVeiculo.byte4 & 0x0F) + '0');
//        novoEventoDeParada.EPC_area[2] = ((areaDoVeiculo.byte3 >> 4) + '0');
//        novoEventoDeParada.EPC_area[3] = ((areaDoVeiculo.byte3 & 0x0F) + '0');
//        novoEventoDeParada.EPC_area[4] = ((areaDoVeiculo.byte2 >> 4) + '0');
//        novoEventoDeParada.EPC_area[5] = ((areaDoVeiculo.byte2 & 0x0F) + '0');
//        novoEventoDeParada.EPC_area[6] = ((areaDoVeiculo.byte1 >> 4) + '0');
//        novoEventoDeParada.EPC_area[7] = ((areaDoVeiculo.byte1 & 0x0F) + '0');
//
//        novoEventoDeParada.EPC_operador[0] = (((unsigned char)MeuOperador.Epc[0] >> 4) + '0');
//        novoEventoDeParada.EPC_operador[1] = (((unsigned char)MeuOperador.Epc[0] & 0x0F) + '0');
//        novoEventoDeParada.EPC_operador[2] = (((unsigned char)MeuOperador.Epc[1] >> 4) + '0');
//        novoEventoDeParada.EPC_operador[3] = (((unsigned char)MeuOperador.Epc[1] & 0x0F) + '0');
//        novoEventoDeParada.EPC_operador[4] = (((unsigned char)MeuOperador.Epc[2] >> 4) + '0');
//        novoEventoDeParada.EPC_operador[5] = (((unsigned char)MeuOperador.Epc[2] & 0x0F) + '0');
//        novoEventoDeParada.EPC_operador[6] = '0';
//        novoEventoDeParada.EPC_operador[7] = '0';
//
//        novoEventoDeParada.EPC_pedestre[0] = (((unsigned char)epcLido.byte4 >> 4) + '0');
//        novoEventoDeParada.EPC_pedestre[1] = (((unsigned char)epcLido.byte4 & 0x0F) + '0');
//        novoEventoDeParada.EPC_pedestre[2] = (((unsigned char)epcLido.byte3 >> 4) + '0');
//        novoEventoDeParada.EPC_pedestre[3] = (((unsigned char)epcLido.byte3 & 0x0F) + '0');
//        novoEventoDeParada.EPC_pedestre[4] = (((unsigned char)epcLido.byte2 >> 4) + '0');
//        novoEventoDeParada.EPC_pedestre[5] = (((unsigned char)epcLido.byte2 & 0x0F) + '0');
//        novoEventoDeParada.EPC_pedestre[6] = (((unsigned char)epcLido.byte1 & 0x0F) + '0');
//        novoEventoDeParada.EPC_pedestre[7] = (((unsigned char)epcLido.byte1 & 0x0F) + '0');
//
//        dataHora = localtime (&Tempo); 
//
//        novoEventoDeParada.dia = dataHora->tm_mday;
//        novoEventoDeParada.mes = dataHora->tm_mon+1;
//        novoEventoDeParada.ano = dataHora->tm_year-100;
//
//        novoEventoDeParada.hora = dataHora->tm_hour;
//        novoEventoDeParada.minuto = dataHora->tm_min;
//        novoEventoDeParada.segundo = dataHora->tm_sec;
//
//        inicializaMaquinaDeEstados_EventosDeParada();                    
//
//        criarEventoDeParadaDeEmpilhadeira(&novoEventoDeParada);                    
//
//        habilitaMaquinaDeEstados_EventosDeParada();
//
//        bloqueiaOperacaoDoLeitorParaAMaquinaLind();
//
//        bloqueiaMaquinaDeEstados_EventosDeParada(); 
        
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
            pilhaEventos->eventos[i].dataEvento;
            
            for(j = i; j < pilhaEventos->numEventos-1; j++){
                pilhaEventos->eventos[j] = pilhaEventos->eventos[j+1];
            }
            return 1;
        }        
    }
    return 0;   
}
