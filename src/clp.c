

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
    
    SED(leitorMarsOne_INPUT1)
    MEMO(entradaSensorPortaoRuaAberto)    
    SEL(leitorMarsOne_INPUT1)
    MEMO(entradaSensorPortaoRuaFechado)
    
    SED(leitorMarsOne_INPUT2)
    MEMO(entradaSensorPortaoInternoAberto)    
    SEL(leitorMarsOne_INPUT2)
    MEMO(entradaSensorPortaoInternoFechado)
            
    SEL(leitorMarsOne_INPUT3)
    MEMO(entradaSensorBarreiraPortaoRuaAberto)    
    SED(leitorMarsOne_INPUT3)
    MEMO(entradaSensorBarreiraPortaoRuaFechado)
            
    SEL(leitorMarsOne_INPUT4)
    MEMO(entradaSensorBarreiraPortaoInternoAberto)    
    SED(leitorMarsOne_INPUT4)
    MEMO(entradaSensorBarreiraPortaoInternoFechado)
}

uint8_t numQuebrasBarreiraPortaoRua = 0, numQuebrasBarreiraPortaoInterno = 0;

void CLP_executaLogica(void){    
    
    // <editor-fold defaultstate="collapsed" desc="LOGICA DO PROGRAMA">
    
        SED(autoLerAntenasPortaoRua)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        EN(autoAcionaAberturaPortaoRua)
        EN(autoVerificaSensorPortaoRuaAberto)
        EN(autoVerificaSensorBarreiraPortaoRua)
        EN(autoVerificaSensorPortaoRuaFechado)
        EN(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        EN(autoVerificaSensorBarreiraPortaoInterno)
        EN(autoAcionaAberturaPortaoInterno)
        EN(autoVerificaSensorPortaoInternoAberto)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        EN(autoRegistraEventoEntradaVeiculo)
        MEMO(autoAguardaInicioLogica)

        SEL(autoAguardaInicioLogica)
        E(iniciarPrograma)        
        OU(autoLerAntenasPortaoRua)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        MEMO(autoLerAntenasPortaoRua)

        SEL(autoLerAntenasPortaoRua)
        E(fim_tmpLeituraAntenasPortaoRua)
        OU(autoVerificaSeTagValidaFoiEncontrada)  
        EN(autoReiniciaEntrada)
        EN(autoAcionaAberturaPortaoRua)
        MEMO(autoVerificaSeTagValidaFoiEncontrada)

        SEL(autoVerificaSeTagValidaFoiEncontrada)
        E(tagEncontradaNaRua)        
        OU(autoAcionaAberturaPortaoRua)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorPortaoRuaAberto)
        MEMO(autoAcionaAberturaPortaoRua)

        SEL(autoAcionaAberturaPortaoRua)
        E(fim_tmpAguardaPortaoRuaAbrir)        
        OU(autoVerificaSensorPortaoRuaAberto)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorBarreiraPortaoRua)
        MEMO(autoVerificaSensorPortaoRuaAberto)

        SEL(autoVerificaSensorPortaoRuaAberto)
        E(entradaSensorPortaoRuaAberto)             
        OU(aberturaManualPortao1Detectada)
        OU(autoVerificaSensorBarreiraPortaoRua)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorPortaoRuaFechado)
        MEMO(autoVerificaSensorBarreiraPortaoRua)

        SEL(autoVerificaSensorBarreiraPortaoRua)
        E(entradaSensorBarreiraPortaoRuaAberto)        
        OU(autoVerificaSensorPortaoRuaFechado)
        EN(autoReiniciaEntrada)
        EN(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        MEMO(autoVerificaSensorPortaoRuaFechado)

        SEL(autoVerificaSensorPortaoRuaFechado)
        E(entradaSensorPortaoRuaFechado)        
        OU(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorBarreiraPortaoInterno)
        MEMO(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)

        SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        E(entradaVeiculosRuaLiberada)         
        OU(aberturaManualPortao2Detectada)
        EN(veiculoPresoNaClausura)
        OU(autoVerificaSensorBarreiraPortaoInterno)
        EN(autoReiniciaEntrada)
        EN(autoAcionaAberturaPortaoInterno)
        MEMO(autoVerificaSensorBarreiraPortaoInterno)

        SEL(autoVerificaSensorBarreiraPortaoInterno)
        E(entradaSensorBarreiraPortaoInternoAberto)        
        OU(autoAcionaAberturaPortaoInterno)
        OU(veiculoPresoNaClausura)
        EN(autoReiniciaEntrada)
        EN(solicSaidaAlarme)
        EN(autoVerificaSensorPortaoInternoAberto)
        MEMO(autoAcionaAberturaPortaoInterno)

        SEL(autoAcionaAberturaPortaoInterno)
        E(fim_tmpAguardaPortaoInternoAbrir)        
        OU(autoVerificaSensorPortaoInternoAberto)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        MEMO(autoVerificaSensorPortaoInternoAberto)

        SEL(autoVerificaSensorPortaoInternoAberto)
        E(entradaSensorPortaoInternoAberto)        
        OU(autoVerificaSensorFechamentoPortaoInternoFechado)
        EN(autoReiniciaEntrada)
        EN(autoRegistraEventoEntradaVeiculo)
        MEMO(autoVerificaSensorFechamentoPortaoInternoFechado)

        SEL(autoVerificaSensorFechamentoPortaoInternoFechado)
        E(entradaSensorPortaoInternoFechado)
        EN(autoReiniciaEntrada)
        MEMO(autoRegistraEventoEntradaVeiculo)
        
        
        //LOGICA PARA SINAIS AUXILIARES DO SEQUENCIADOR
        
        //CASO NAO ENCONTRE NINGUEM NA ANTENA DA RUA
        SEL(autoVerificaSeTagValidaFoiEncontrada)
        EN(tagEncontradaNaRua)
        MEMO(autoReiniciaEntrada)        
        
        //DETECCAO DE ABERTURA MANUAL DE PORTAO DA RUA
        SED(solicSaidaAbrirPortaoRua)
        EN(autoAcionaAberturaPortaoRua)
        EN(autoVerificaSensorPortaoRuaAberto)
        E(entradaSensorPortaoRuaAberto)
        MEMO(aberturaManualPortao1Detectada)
        
        //DETECCAO DE ABERTURA MANUAL DE PORTAO INTERNO
        SED(solicSaidaAbrirPortaoInterno)
        EN(autoAcionaAberturaPortaoInterno)
        EN(autoVerificaSensorPortaoInternoAberto)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        E(entradaSensorPortaoInternoAberto)
        MEMO(aberturaManualPortao2Detectada)
        
        //DETECCAO DE VEICULO PRESO NA CLAUSURA
        SEL(entradaSensorPortaoRuaFechado)
        E(entradaSensorPortaoInternoFechado)
        E(entradaSensorBarreiraPortaoInternoAberto)
        EN(autoAcionaAberturaPortaoInterno)
        MEMO(veiculoPresoNaClausura)
        
        
    // </editor-fold>    
    
    // <editor-fold defaultstate="collapsed" desc="DISPARO DOS TEMPORIZADORES">

        // <editor-fold defaultstate="collapsed" desc="timer_tmpLeituraAntenasPortaoRua">
        //TEMPORIZADOR DE LEITURA DAS ANTENAS DA RUA
        SEL(autoLerAntenasPortaoRua)        
        OU(dsp_tmpLeituraAntenasPortaoRua)
        EN(fim_tmpLeituraAntenasPortaoRua)
        MEMO(dsp_tmpLeituraAntenasPortaoRua)
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAguardaPortaoRuaAbrir">
        //TEMPORIZADOR DE ESPERA PARA PORTAO ABRIR
        SEL(autoAcionaAberturaPortaoRua)        
        OU(dsp_tmpAguardaPortaoRuaAbrir)
        EN(fim_tmpAguardaPortaoRuaAbrir)
        MEMO(dsp_tmpAguardaPortaoRuaAbrir)
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAguardaPortaoInternoAbrir">
        //TEMPORIZADOR DE ESPERA PARA PORTAO ABRIR
        SEL(autoAcionaAberturaPortaoInterno)        
        OU(dsp_tmpAguardaPortaoInternoAbrir)
        EN(fim_tmpAguardaPortaoInternoAbrir)
        MEMO(dsp_tmpAguardaPortaoInternoAbrir)
        // </editor-fold>
    
    // </editor-fold>    
           
    SEL(entradaSensorBarreiraPortaoRuaAberto)
    SUBIDA
    ENTAO_EXECUTA_BLOCO{
        numQuebrasBarreiraPortaoRua++;
    }
        
    SEL(entradaSensorBarreiraPortaoInternoAberto)
    SUBIDA
    ENTAO_EXECUTA_BLOCO{
        numQuebrasBarreiraPortaoInterno++;
    }
    
    SEL(autoAguardaInicioLogica)
    SUBIDA
    ENTAO_EXECUTA_BLOCO{
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
        numQuebrasBarreiraPortaoRua = 0;
        numQuebrasBarreiraPortaoInterno = 0;
    }
       
    // <editor-fold defaultstate="collapsed" desc="FUNCOES CONFORME PASSO">
    
    // <editor-fold defaultstate="collapsed" desc="autoAguardaInicioLogica">

    SEL(autoAguardaInicioLogica)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoLerAntenasPortaoRua">

    SEL(autoLerAntenasPortaoRua)
    OU(autoAcionaAberturaPortaoRua)
    OU(autoVerificaSensorPortaoRuaAberto)
    OU(autoVerificaSensorBarreiraPortaoRua) 
    EN(entradaSensorPortaoInternoAberto)
    ENTAO_EXECUTA_BLOCO {
        uint8_t i;
        uint8_t resultado = 0;
        EPC_Estacionamento epcLido;
        
        #ifndef DEBUG
            //realizaLeituraDeAntena(ANTENNA_1);  
        #else
            EPC_Estacionamento epc;
            
            tags_[0].epc[0] = 0x30;
            tags_[0].epc[1] = 0x00;
            tags_[0].epc[2] = 0x04;
           
            epc.byte1 = tags_[0].epc[2];
            epc.byte2 = tags_[0].epc[1];           
            
            adicionaNovaTagNaLista(&listaDeVeiculosLiberados,epc);
                        
        #endif
                    
        for( i = 0; i < MAXTAG; i++){

            if( verificaTagValida( tags_[i].epc ) > 0 ){ // Tag veicular valida?
                epcLido.byte1 = tags_[i].epc[2];
                epcLido.byte2 = tags_[i].epc[1];
                if( buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epcLido)){ // Veiculo esta na lista?  
                    adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Entrada,epcLido);        
                    resultado = 1;    
                }
                else{      
                    removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada,epcLido);          
                    resultado = 0;
                }
            }
            else{
                resultado = 0;
            }        
        }    
        tagEncontradaNaRua = resultado;
    }
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSeTagValidaFoiEncontrada">

    SEL(autoVerificaSeTagValidaFoiEncontrada)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {
        
    }
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoRua">    

    SEL(autoAcionaAberturaPortaoRua)
    E(entradaSensorPortaoRuaFechado)
    EN(entradaSensorPortaoInternoAberto)
    SUBIDA
    MEMO(solicSaidaAbrirPortaoRua)
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoRuaAberto">    

    // ESSE PASSO NAO FAZ NADA, APENAS VERIFICA SE O PORTAO ABRIU, NO PROPRIO SEQUENCIADOR
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoRua">    

    // ESSE PASSO NAO FAZ NADA, APENAS VERIFICA SE O PORTAO ABRIU, NO PROPRIO SEQUENCIADOR
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoRuaFechado">    

    // ESSE PASSO NAO FAZ NADA, APENAS VERIFICA SE O PORTAO ABRIU, NO PROPRIO SEQUENCIADOR
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira">    

    SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)    
    E(numQuebrasBarreiraPortaoRua == listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela)    
    MEMO(entradaVeiculosRuaLiberada)
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoInterno">    

    SEL(autoVerificaSensorBarreiraPortaoInterno)
    SUBIDA
    ENTAO_EXECUTA_BLOCO {

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoInterno">    

    SEL(autoAcionaAberturaPortaoInterno)
    EN(entradaSensorPortaoRuaAberto)    
    MEMO(solicSaidaAbrirPortaoInterno)
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorPortaoInternoAberto">    

    SEL(autoVerificaSensorPortaoInternoAberto)
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
    
    // <editor-fold defaultstate="collapsed" desc="DISPARO DOS ALARMES">
    
    // ALARME VEICULO SEM TAG DENTRO DA CLAUSURA
    SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
    EN(entradaVeiculosRuaLiberada)
    OU(solicSaidaAlarme)
    EN(entradaSensorPortaoInternoAberto)
    MEMO(solicSaidaAlarme)
    
    // </editor-fold>
    
}

void CLP_atualizaSaidas(void){
    
    SEL(solicSaidaAbrirPortaoRua) 
    MEMO(leitorMarsOne_Rele1)
    
    SEL(solicSaidaAbrirPortaoInterno) 
    MEMO(leitorMarsOne_Rele2)
    
    SEL(solicSaidaAlarme) 
    MEMO(leitorMarsOne_Rele3)
    
    SEL(0) //SAIDA LIVRE
    MEMO(leitorMarsOne_Rele4)   
    
    BSP_setRelay(RELAY_1,leitorMarsOne_Rele1 & 1);
    BSP_setRelay(RELAY_2,leitorMarsOne_Rele2 & 1);
    BSP_setRelay(RELAY_3,leitorMarsOne_Rele3 & 1);
    BSP_setRelay(RELAY_4,leitorMarsOne_Rele4 & 1);
}




