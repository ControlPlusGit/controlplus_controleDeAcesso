/* 
 * File:   declara_clp.h
 * Author: vitor
 *
 * Created on March 19, 2021, 1:22 PM
 */

#ifndef DECLARA_CLP_H
#define	DECLARA_CLP_H

#ifdef	__cplusplus
extern "C" {
#endif
 
#include "clp.h"
#include <stdint.h>
////////////////////////////////////////////
//TEMPORIZADORES
////////////////////////////////////////////

uint32_t durTmpLeituraAntenasPortaoRua = 2;
TEMPORIZADOR(tmpLeituraAntenasPortaoRua,durTmpLeituraAntenasPortaoRua)

uint32_t durTmpAguardaPortaoRuaAbrir = 2;
TEMPORIZADOR(tmpAguardaPortaoRuaAbrir,durTmpAguardaPortaoRuaAbrir)

uint32_t durTmpAguardaPortaoInternoAbrir = 2;
TEMPORIZADOR(tmpAguardaPortaoInternoAbrir,durTmpAguardaPortaoInternoAbrir)

////////////////////////////////////////////
//ENTRADAS DIGITAIS
////////////////////////////////////////////
        
ENTRADA_DIGITAL(leitorMarsOne_INPUT1)
ENTRADA_DIGITAL(leitorMarsOne_INPUT2)
ENTRADA_DIGITAL(leitorMarsOne_INPUT3)
ENTRADA_DIGITAL(leitorMarsOne_INPUT4)

////////////////////////////////////////////
//SAIDAS DIGITAIS
////////////////////////////////////////////
       
SAIDA_DIGITAL(leitorMarsOne_Rele1)
SAIDA_DIGITAL(leitorMarsOne_Rele2)
SAIDA_DIGITAL(leitorMarsOne_Rele3)
SAIDA_DIGITAL(leitorMarsOne_Rele4)

////////////////////////////////////////////
//SINAIS DIGITAIS
////////////////////////////////////////////
        
SINAL_DIGITAL(autoAguardaInicioLogica)
SINAL_DIGITAL(autoLerAntenasPortaoRua)
SINAL_DIGITAL(autoVerificaSeTagValidaFoiEncontrada)
SINAL_DIGITAL(autoAcionaAberturaPortaoRua)
SINAL_DIGITAL(autoVerificaSensorPortaoRuaAberto)
SINAL_DIGITAL(autoVerificaSensorBarreiraPortaoRua)
SINAL_DIGITAL(autoVerificaSensorPortaoRuaFechado)
SINAL_DIGITAL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
SINAL_DIGITAL(autoVerificaSensorBarreiraPortaoInterno)
SINAL_DIGITAL(autoAcionaAberturaPortaoInterno)
SINAL_DIGITAL(autoVerificaSensorPortaoInternoAberto)
SINAL_DIGITAL(autoVerificaSensorFechamentoPortaoInternoFechado)
SINAL_DIGITAL(autoRegistraEventoEntradaVeiculo)

SINAL_DIGITAL(iniciarPrograma);
SINAL_DIGITAL(tagEncontradaNaRua);
SINAL_DIGITAL(entradaSensorPortaoRuaAberto);
SINAL_DIGITAL(sensorBarreiraPortaoRuaAcionado);
SINAL_DIGITAL(entradaSensorPortaoRuaFechado);
SINAL_DIGITAL(entradaVeiculosRuaLiberada);
SINAL_DIGITAL(entradaSensorPortaoInternoAberto);
SINAL_DIGITAL(sensorFechamentoPortaoInternoFechado);
SINAL_DIGITAL(eventoEntradaVeiculoRegistrado);

SINAL_DIGITAL(entradaSensorBarreiraPortaoRuaAberto)
SINAL_DIGITAL(entradaSensorBarreiraPortaoRuaFechado)

SINAL_DIGITAL(entradaSensorBarreiraPortaoInternoAberto)
SINAL_DIGITAL(entradaSensorBarreiraPortaoInternoFechado)
        
SINAL_DIGITAL(saidaSinalVeiculoSemTagNaEntrada)
SINAL_DIGITAL(saidaAcionaAberturaPortaoRua)
SINAL_DIGITAL(saidaAcionaAberturaPortaoInterno)
        
SINAL_DIGITAL(solicSaidaAbrirPortaoRua)
SINAL_DIGITAL(solicSaidaAbrirPortaoInterno)
SINAL_DIGITAL(solicSaidaAlarme)

#ifdef	__cplusplus
}
#endif

#endif	/* DECLARA_CLP_H */

