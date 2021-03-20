

// <editor-fold defaultstate="collapsed" desc="INCLUDES">
#include "clp.h"
#include <stdint.h>
#include "system.h"
#include "declara_clp.h"

#include "BSP/bsp.h"
#include "BSP/rfid_bsp.h"
#include "RFID/as3993.h"
#include "RFID/gen2.h"
#include "tabelaEstacionamento.h"

#include "main.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="DECLARACAO DE VARIAVEIS">
uint8_t ELC = 0;

VetorTemporizador temporizadores;
VetorVariavel entradasDigitais;
VetorVariavel saidasDigitais;

uint8_t i_temporizadores = 0;

uint8_t clpLiberado = 0;

uint8_t inicializacaoConcluida = 0; 
// </editor-fold>

uint8_t registraTemporizador(Temporizador *temporizador) {
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

void CLP_liberaExecucao(void){
    if(!clpLiberado){
        clpLiberado = 1;
    }
}

void CLP_executa(void){    
    if(clpLiberado){
        if(!inicializacaoConcluida){
            CLP_inicializaTemporizadores();
            inicializacaoConcluida = 1;
        }
        CLP_atualizaEntradas();
    
        CLP_executaLogica();

        CLP_atualizaSaidas();

        verificarTemporizadores();
    }    
}

void CLP_inicializaTemporizadores(void){
    CADASTRAR_TEMPORIZADOR(tmpLeituraAntenasPortaoRua)
    CADASTRAR_TEMPORIZADOR(tmpAguardaPortaoRuaAbrir)
    CADASTRAR_TEMPORIZADOR(tmpAguardaPortaoInternoAbrir)
}

void CLP_atualizaEntradas(void){
    leitorMarsOne_INPUT1 = BSP_readDigitalInput(INPUT_1);
    leitorMarsOne_INPUT2 = BSP_readDigitalInput(INPUT_2);
    leitorMarsOne_INPUT3 = BSP_readDigitalInput(INPUT_3);
    leitorMarsOne_INPUT4 = BSP_readDigitalInput(INPUT_4);
    
    entradaSensorPortaoRuaAberto  =   leitorMarsOne_INPUT1 & 1;
    entradaSensorPortaoRuaFechado = ~(leitorMarsOne_INPUT1 & 1);
    
    entradaSensorPortaoInternoAberto     =   leitorMarsOne_INPUT2 & 1;
    sensorFechamentoPortaoInternoFechado = ~(leitorMarsOne_INPUT2 & 1);
    
    entradaSensorBarreiraPortaoRuaAberto  =   leitorMarsOne_INPUT3 & 1;
    entradaSensorBarreiraPortaoRuaFechado = ~(leitorMarsOne_INPUT3 & 1);
    
    entradaSensorBarreiraPortaoInternoAberto  =   leitorMarsOne_INPUT4 & 1;
    entradaSensorBarreiraPortaoInternoFechado = ~(leitorMarsOne_INPUT4 & 1);
}

void CLP_executaLogica(void){    
    
    // <editor-fold defaultstate="collapsed" desc="LOGICA DO PROGRAMA">
    
        SED(autoLerAntenasPortaoRua)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        EN(autoAcionaAberturaPortaoRua)
        EN(autoVerificaSensorPortaoRuaAberto)
        EN(autoVerificaSensorBarreiraPortaoRua)
        EN(autoVerificaSensorPortaoRuaFechado)
        EN(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        EN(autoVerificaSensorBarreiraPortaoInterno_1)
        EN(autoAcionaAberturaPortaoInterno)
        EN(autoVerificaSensorPortaoInternoAberto)
        EN(autoVerificaSensorBarreiraPortaoInterno_2)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        EN(autoRegistraEventoEntradaVeiculo)
        MEMO(autoAguardaInicioLogica)

        SEL(autoAguardaInicioLogica)
        E(iniciarPrograma)
        OU(autoLerAntenasPortaoRua)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        MEMO(autoLerAntenasPortaoRua)

        SEL(autoLerAntenasPortaoRua)
        E(fim_tmpLeituraAntenasPortaoRua)
        OU(autoVerificaSeTagValidaFoiEncontrada)
        EN(autoAcionaAberturaPortaoRua)
        MEMO(autoVerificaSeTagValidaFoiEncontrada)

        SEL(autoVerificaSeTagValidaFoiEncontrada)
        E(tagEncontradaNaRua)
        OU(autoAcionaAberturaPortaoRua)
        EN(autoVerificaSensorPortaoRuaAberto)
        MEMO(autoAcionaAberturaPortaoRua)

        SEL(autoAcionaAberturaPortaoRua)
        E(fim_tmpAguardaPortaoRuaAbrir)
        OU(autoVerificaSensorPortaoRuaAberto)
        EN(autoVerificaSensorBarreiraPortaoRua)
        MEMO(autoVerificaSensorPortaoRuaAberto)

        SEL(autoVerificaSensorPortaoRuaAberto)
        E(entradaSensorPortaoRuaAberto)
        OU(autoVerificaSensorBarreiraPortaoRua)
        EN(autoVerificaSensorPortaoRuaFechado)
        MEMO(autoVerificaSensorBarreiraPortaoRua)

        SEL(autoVerificaSensorBarreiraPortaoRua)
        E(entradaSensorBarreiraPortaoRuaAberto)
        OU(autoVerificaSensorPortaoRuaFechado)
        EN(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        MEMO(autoVerificaSensorPortaoRuaFechado)

        SEL(autoVerificaSensorPortaoRuaFechado)
        E(entradaSensorPortaoRuaFechado)
        OU(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        EN(autoVerificaSensorBarreiraPortaoInterno_1)
        MEMO(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)

        SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        E(entradaVeiculosRuaLiberada)
        OU(autoVerificaSensorBarreiraPortaoInterno_1)
        EN(autoAcionaAberturaPortaoInterno)
        MEMO(autoVerificaSensorBarreiraPortaoInterno_1)

        SEL(autoVerificaSensorBarreiraPortaoInterno_1)
        E(entradaSensorBarreiraPortaoInternoAberto)
        OU(autoAcionaAberturaPortaoInterno)
        EN(autoVerificaSensorPortaoInternoAberto)
        MEMO(autoAcionaAberturaPortaoInterno)

        SEL(autoAcionaAberturaPortaoInterno)
        E(fim_tmpAguardaPortaoInternoAbrir)
        OU(autoVerificaSensorPortaoInternoAberto)
        EN(autoVerificaSensorBarreiraPortaoInterno_2)
        MEMO(autoVerificaSensorPortaoInternoAberto)

        SEL(autoVerificaSensorPortaoInternoAberto)
        E(entradaSensorPortaoInternoAberto)
        OU(autoVerificaSensorBarreiraPortaoInterno_2)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        MEMO(autoVerificaSensorBarreiraPortaoInterno_2)

        SEL(autoVerificaSensorBarreiraPortaoInterno_2)
        E(entradaSensorBarreiraPortaoInternoAberto)
        OU(autoVerificaSensorFechamentoPortaoInternoFechado)
        EN(autoRegistraEventoEntradaVeiculo)
        MEMO(autoVerificaSensorFechamentoPortaoInternoFechado)

        SEL(autoVerificaSensorFechamentoPortaoInternoFechado)
        E(sensorFechamentoPortaoInternoFechado)
        MEMO(autoRegistraEventoEntradaVeiculo)
        
    // </editor-fold>    
    
    // <editor-fold defaultstate="collapsed" desc="DISPARO DOS TEMPORIZADORES">

        // <editor-fold defaultstate="collapsed" desc="timer_tmpLeituraAntenasPortaoRua">
        //TEMPORIZADOR DE LEITURA DAS ANTENAS DA RUA
        SEL(autoLerAntenasPortaoRua)
        SUBIDA
        OU(dsp_tmpLeituraAntenasPortaoRua)
        EN(fim_tmpLeituraAntenasPortaoRua)
        MEMO(dsp_tmpLeituraAntenasPortaoRua)
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAguardaPortaoRuaAbrir">
        //TEMPORIZADOR DE ESPERA PARA PORTAO ABRIR
        SEL(autoAcionaAberturaPortaoRua)
        SUBIDA
        OU(dsp_tmpAguardaPortaoRuaAbrir)
        EN(fim_tmpAguardaPortaoRuaAbrir)
        MEMO(dsp_tmpAguardaPortaoRuaAbrir)
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAguardaPortaoInternoAbrir">
        //TEMPORIZADOR DE ESPERA PARA PORTAO ABRIR
        SEL(autoAcionaAberturaPortaoInterno)
        SUBIDA
        OU(dsp_tmpAguardaPortaoInternoAbrir)
        EN(fim_tmpAguardaPortaoInternoAbrir)
        MEMO(dsp_tmpAguardaPortaoInternoAbrir)
        // </editor-fold>
    
    // </editor-fold>
    
    // <editor-fold defaultstate="collapsed" desc="DISPARO DOS ALARMES">
    
    
    
    // </editor-fold>
       
    // <editor-fold defaultstate="collapsed" desc="FUNCOES CONFORME PASSO">
    
    // <editor-fold defaultstate="collapsed" desc="autoAguardaInicioLogica">

    SEL(autoAguardaInicioLogica)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoLerAntenasPortaoRua">

    SEL(autoLerAntenasPortaoRua)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSeTagValidaFoiEncontrada">

    SEL(autoVerificaSeTagValidaFoiEncontrada)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoRua">    

    SEL(autoAcionaAberturaPortaoRua)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoRuaAberto">    

    SEL(autoVerificaSensorPortaoRuaAberto)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoRua">    

    SEL(autoVerificaSensorBarreiraPortaoRua)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoRuaFechado">    

    SEL(autoVerificaSensorPortaoRuaFechado)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira">    

    SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoInterno_1">    

    SEL(autoVerificaSensorBarreiraPortaoInterno_1)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoInterno">    

    SEL(autoAcionaAberturaPortaoInterno)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoInternoAberto">    

    SEL(autoVerificaSensorPortaoInternoAberto)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoInterno_2">    

    SEL(autoVerificaSensorBarreiraPortaoInterno_2)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorFechamentoPortaoInternoFechado">    

    SEL(autoVerificaSensorFechamentoPortaoInternoFechado)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoRegistraEventoEntradaVeiculo">    

    SEL(autoRegistraEventoEntradaVeiculo)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>      
    
    // </editor-fold> 
    
}

void CLP_atualizaSaidas(void){
    SEL(solicSaidaAbrirPortaoRua) 
    ENTAO_EXECUTA_BLOCO{
        BSP_setRelay(RELAY_1,leitorMarsOne_Rele1 & 1);
    }
    
    SEL(solicSaidaAbrirPortaoInterno) 
    ENTAO_EXECUTA_BLOCO{
        BSP_setRelay(RELAY_2,leitorMarsOne_Rele2 & 1);
    }
    
    SEL(solicSaidaAlarme) 
    ENTAO_EXECUTA_BLOCO{
        BSP_setRelay(RELAY_3,leitorMarsOne_Rele3 & 1);
    }
    
    SEL(0) //SAIDA LIVRE
    ENTAO_EXECUTA_BLOCO{
        BSP_setRelay(RELAY_4,leitorMarsOne_Rele4 & 1);
    }    
}




