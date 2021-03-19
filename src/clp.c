#include "clp.h"
#include <stdint.h>
#include "system.h"

uint8_t ELC = 0;

VetorTemporizador temporizadores;
VetorVariavel entradasDigitais;
VetorVariavel saidasDigitais;

uint8_t i_temporizadores = 0;

uint8_t registraTemporizador(Temporizador *temporizador){
    temporizadores.temp[temporizadores.numTempFinal++] = temporizador;
    return 0;
}

int8_t verificarTemporizadores(void){
    if(temporizadores.numTempFinal > 0){
        for( i_temporizadores = 0; i_temporizadores < temporizadores.numTempFinal; i_temporizadores++ ){

            SEL( (*temporizadores.temp[i_temporizadores]->var_disparo) )
            SUBIDA
            ENTAO_EXECUTA_BLOCO
            {
                temporizadores.temp[i_temporizadores]->contagem = (*temporizadores.temp[i_temporizadores]->tempoProgramado) + tick_getTimerCounter_ms();
            }

            SEL  ( (*temporizadores.temp[i_temporizadores]->var_disparo) )
            E    ( tick_getTimerCounter_ms() == temporizadores.temp[i_temporizadores]->contagem )
            EN   ( (*temporizadores.temp[i_temporizadores]->var_fim) )
            MEMO ( (*temporizadores.temp[i_temporizadores]->var_fim) )
        }
    }
    return 0;
}
