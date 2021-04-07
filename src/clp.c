

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
#include "eventos.h"

#include "main.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="DECLARACAO DE VARIAVEIS">

PilhaEventos eventosDePassagem;

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
            E    ( tick_getTimerCounter_ms() >= temporizadores.temp[i_temporizadores]->contagem )   
            MEMO ( (*temporizadores.temp[i_temporizadores]->var_fim) )
                    
            SEL( tick_getTimerCounter_ms() < temporizadores.temp[i_temporizadores]->contagem - (*temporizadores.temp[i_temporizadores]->tempoProgramado) )
            ENTAO_EXECUTA_BLOCO{
                temporizadores.temp[i_temporizadores]->contagem = (*temporizadores.temp[i_temporizadores]->tempoProgramado) + tick_getTimerCounter_ms();
            }           
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
    
#ifndef DEBUG //definido em clp.h
    iniciarPrograma = 1;
#else
    iniciarPrograma = 0;
#endif
    
    if(clpLiberado){
        if(!inicializacaoConcluida){
            CLP_inicializaTemporizadores();
            inicializacaoConcluida = 1;
        }
        
        verificarTemporizadores();
        
        CLP_atualizaEntradas();
    
        CLP_executaLogica();

        CLP_atualizaSaidas();

        
    }    
}

void CLP_inicializaTemporizadores(void){
    CADASTRAR_TEMPORIZADOR(tmpLeituraAntenasPortaoRua)
    CADASTRAR_TEMPORIZADOR(tmpAguardaPortaoRuaAbrir)
    CADASTRAR_TEMPORIZADOR(tmpAguardaPortaoInternoAbrir)
    CADASTRAR_TEMPORIZADOR(tmpAcionaSinalAberturaPortaoRua)
    CADASTRAR_TEMPORIZADOR(tmpDesligaSinalAberturaPortaoRua)
    CADASTRAR_TEMPORIZADOR(tmpAcionaSinalAberturaPortaoInterno)
    CADASTRAR_TEMPORIZADOR(tmpDesligaSinalAberturaPortaoInterno)
}

#ifdef DEBUG //definido em clp.h
    uint8_t entradaDigitalVirtual1 = 1;
    uint8_t entradaDigitalVirtual2 = 1;
    uint8_t entradaDigitalVirtual3 = 0;
    uint8_t entradaDigitalVirtual4 = 0;
#endif

void CLP_atualizaEntradas(void){

#ifndef DEBUG //definido em clp.h
    leitorMarsOne_INPUT1 = BSP_readDigitalInput(INPUT_1);
    leitorMarsOne_INPUT2 = BSP_readDigitalInput(INPUT_2);
    leitorMarsOne_INPUT3 = BSP_readDigitalInput(INPUT_3);
    leitorMarsOne_INPUT4 = BSP_readDigitalInput(INPUT_4);
#else    
    leitorMarsOne_INPUT1 = entradaDigitalVirtual1;
    leitorMarsOne_INPUT2 = entradaDigitalVirtual2;
    leitorMarsOne_INPUT3 = entradaDigitalVirtual3;
    leitorMarsOne_INPUT4 = entradaDigitalVirtual4;
#endif    
    
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
    
    // <editor-fold defaultstate="collapsed" desc="LOGICA DE ENTRADA/SAIDA DE VEICULOS">
    
        // <editor-fold defaultstate="collapsed" desc="LOGICA DO PROGRAMA">

        SED(autoLerAntenasPortaoRua)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        EN(autoAcionaAberturaPortaoRua)
        EN(autoVerificaSensorPortaoRuaAberto)
        EN(autoVerificaSensorBarreiraPortaoRua)
        EN(autoVerificaSensorPortaoRuaFechado)
        EN(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        //        EN(autoVerificaSensorBarreiraPortaoInterno)
        //        EN(autoAcionaAberturaPortaoInterno)
        EN(autoVerificaSensorPortaoInternoAberto)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        EN(autoRegistraEventoEntradaVeiculo)
        EN(aberturaManualPortao1Detectada)
        MEMO(autoAguardaInicioLogica)

        SEL(autoAguardaInicioLogica)
        E(iniciarPrograma)
        OU(autoLerAntenasPortaoRua)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSeTagValidaFoiEncontrada)
        EN(aberturaManualPortao1Detectada)
        MEMO(autoLerAntenasPortaoRua)

        SEL(autoLerAntenasPortaoRua)
        E(fim_tmpLeituraAntenasPortaoRua)
        OU(autoVerificaSeTagValidaFoiEncontrada)
        EN(autoReiniciaEntrada)
        EN(autoAcionaAberturaPortaoRua)
        EN(aberturaManualPortao1Detectada)
        MEMO(autoVerificaSeTagValidaFoiEncontrada)

        SEL(autoVerificaSeTagValidaFoiEncontrada)
        E(tagEncontradaNaRua)
        OU(autoAcionaAberturaPortaoRua)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorPortaoRuaAberto)
        EN(aberturaManualPortao1Detectada)
        MEMO(autoAcionaAberturaPortaoRua)

        SEL(autoAcionaAberturaPortaoRua)
        E(fim_tmpAguardaPortaoRuaAbrir)
        OU(autoVerificaSensorPortaoRuaAberto)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorBarreiraPortaoRua)
        EN(aberturaManualPortao1Detectada)
        MEMO(autoVerificaSensorPortaoRuaAberto)

        SEL(aberturaManualPortao1Detectada)
        SUBIDA
        OU(autoVerificaSensorPortaoRuaAberto)
        E(entradaSensorPortaoRuaAberto)        
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
        EN(autoVerificaSensorPortaoInternoAberto)
        MEMO(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)

        SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        E(entradaVeiculosRuaLiberada)
        OU(aberturaManualPortao2Detectada)
        EN(veiculoPresoNaClausura)
        OU(autoVerificaSensorPortaoInternoAberto)
        EN(autoReiniciaEntrada)
        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        MEMO(autoVerificaSensorPortaoInternoAberto)

        //        SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        //        E(entradaVeiculosRuaLiberada)         
        //        OU(aberturaManualPortao2Detectada)
        //        EN(veiculoPresoNaClausura)
        //        OU(autoVerificaSensorBarreiraPortaoInterno)
        //        EN(autoReiniciaEntrada)
        //        EN(autoAcionaAberturaPortaoInterno)
        //        MEMO(autoVerificaSensorBarreiraPortaoInterno)
        //
        //        SEL(autoVerificaSensorBarreiraPortaoInterno)
        //        E(entradaSensorBarreiraPortaoInternoAberto)        
        //        OU(autoAcionaAberturaPortaoInterno)
        //        OU(veiculoPresoNaClausura)
        //        EN(autoReiniciaEntrada)
        //        EN(solicSaidaAlarme)
        //        EN(autoVerificaSensorPortaoInternoAberto)
        //        MEMO(autoAcionaAberturaPortaoInterno)
        //
        //        SEL(autoAcionaAberturaPortaoInterno)
        //        E(fim_tmpAguardaPortaoInternoAbrir)        
        //        OU(autoVerificaSensorPortaoInternoAberto)
        //        EN(autoReiniciaEntrada)
        //        EN(autoVerificaSensorFechamentoPortaoInternoFechado)
        //        MEMO(autoVerificaSensorPortaoInternoAberto)

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
        OU(flagTodosVeiculosSairamPelaEntradaPorAlarme)
        OU(flagNenhumVeiculoEntrou)
        MEMO(autoReiniciaEntrada)

        SEL(solicSaidaAlarme)
        E(aberturaManualPortao1Detectada)
        E(numQuebrasBarreiraPortaoRua == 0)
        EN(autoReiniciaEntrada)
        MEMO(flagTodosVeiculosSairamPelaEntradaPorAlarme)

        //DETECCAO DE ABERTURA MANUAL DE PORTAO DA RUA
//        SED(solicSaidaAbrirPortaoRua)
//        EN(autoAcionaAberturaPortaoRua)
//        EN(autoVerificaSensorPortaoRuaAberto)
//        E(entradaSensorPortaoRuaAberto)
//        MEMO(aberturaManualPortao1Detectada)
        SED(dsp_tmpAcionaSinalAberturaPortaoRua)
        EN(dsp_tmpDesligaSinalAberturaPortaoRua)
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
        //E(entradaSensorBarreiraPortaoInternoAberto)
        EN(autoAcionaAberturaPortaoInterno)
        MEMO(veiculoPresoNaClausura)

        //DETECTAR VEICULOS EXECUTANDO MOVIMENTO DE ENTRADA
        SEL(entradaSensorPortaoRuaFechado)
        E(entradaSensorPortaoInternoFechado)
        E(numQuebrasBarreiraPortaoRua > 0)
        MEMO(veiculoExecutandoMovimentoEntrada)

        //DETECTA QUE O PORTAO ABRIU MAS NENHUM VEICULO ENTROU
        SEL(autoVerificaSensorBarreiraPortaoRua)
        E(entradaSensorPortaoRuaFechado)
        E(numQuebrasBarreiraPortaoRua == 0)
        MEMO(flagNenhumVeiculoEntrou)

        //DETECTA QUEBRA DA BARREIRA DURANTE ENTRADA PARA CONTAR VEICULOS
        SEL(autoVerificaSensorBarreiraPortaoRua)
        OU(autoVerificaSensorPortaoRuaFechado)
        E(entradaSensorBarreiraPortaoRuaAberto)
        SUBIDA
        EN(solicSaidaAlarme)
        ENTAO_EXECUTA_BLOCO {
            numQuebrasBarreiraPortaoRua++;
        }

        //DETECTA QUEBRA DA BARREIRA DURANTE SAIDA PARA CONTAR VEICULOS

        SEL(entradaSensorBarreiraPortaoRuaFechado)
        SUBIDA
        E(solicSaidaAlarme)
        E(aberturaManualPortao1Detectada)
        ENTAO_EXECUTA_BLOCO {
            if (numQuebrasBarreiraPortaoRua > 0) {
                numQuebrasBarreiraPortaoRua--;
            }
        }

        //        SEL(autoVerificaSensorBarreiraPortaoInterno)
        //        E(entradaSensorBarreiraPortaoInternoAberto)
        //        SUBIDA
        //        EN(solicSaidaAlarme)
        //        ENTAO_EXECUTA_BLOCO{
        //            numQuebrasBarreiraPortaoInterno++;
        //        }

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

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAcionaSinalAberturaPortaoRua">
        //TEMPORIZADOR DE TEMPO ON PARA ACIONAR PORTAO RUA
        SEL(autoAcionaAberturaPortaoRua)
        OU(autoVerificaSensorPortaoRuaAberto)
        OU(tagEncontradaNaClausura)
        OU(dsp_tmpAcionaSinalAberturaPortaoRua)
        EN(fim_tmpAcionaSinalAberturaPortaoRua)
        EN(dsp_tmpDesligaSinalAberturaPortaoRua)
        MEMO(dsp_tmpAcionaSinalAberturaPortaoRua)
                
        //TEMPORIZADOR DE TEMPO OFF PARA ACIONAR PORTAO RUA
        SEL(autoAcionaAberturaPortaoRua)
        OU(autoVerificaSensorPortaoRuaAberto)
        OU(tagEncontradaNaClausura)
        E(fim_tmpAcionaSinalAberturaPortaoRua)
        OU(dsp_tmpDesligaSinalAberturaPortaoRua)
        EN(fim_tmpDesligaSinalAberturaPortaoRua)
        MEMO(dsp_tmpDesligaSinalAberturaPortaoRua)
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="timer_tmpAcionaSinalAberturaPortaoInterno">
        //        //TEMPORIZADOR DE TEMPO ON PARA ACIONAR PORTAO INTERNO
        //        SEL(autoAcionaAberturaPortaoInterno)
        //        OU(autoVerificaSensorPortaoInternoAberto)
        //        E(entradaSensorPortaoRuaFechado)    
        //        E(entradaSensorPortaoInternoFechado)
        //        OU(dsp_tmpAcionaSinalAberturaPortaoInterno)
        //        EN(fim_tmpAcionaSinalAberturaPortaoInterno)
        //        EN(dsp_tmpDesligaSinalAberturaPortaoInterno)
        //        MEMO(dsp_tmpAcionaSinalAberturaPortaoInterno)
        //        //TEMPORIZADOR DE TEMPO OFF PARA ACIONAR PORTAO INTERNO
        //        SEL(autoAcionaAberturaPortaoInterno)
        //        OU(autoVerificaSensorPortaoInternoAberto)
        //        E(entradaSensorPortaoRuaFechado)    
        //        E(entradaSensorPortaoInternoFechado)
        //        E(fim_tmpAcionaSinalAberturaPortaoInterno)
        //        OU(dsp_tmpDesligaSinalAberturaPortaoInterno)
        //        EN(fim_tmpDesligaSinalAberturaPortaoInterno)
        //        MEMO(dsp_tmpDesligaSinalAberturaPortaoInterno) 
        // </editor-fold>

        // </editor-fold>   

        // <editor-fold defaultstate="collapsed" desc="FUNCOES CONFORME PASSO">

        // <editor-fold defaultstate="collapsed" desc="autoAguardaInicioLogica">

        SEL(autoAguardaInicioLogica)        
        ENTAO_EXECUTA_BLOCO {
            tagEncontradaNaRua = 0;
            tagEncontradaNaClausura = 0;
            removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
            removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida);
        }// </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="autoLerAntenasPortaoRua">

        SEL(autoLerAntenasPortaoRua)
        OU(autoAcionaAberturaPortaoRua)
        OU(autoVerificaSensorPortaoRuaAberto)
        OU(autoVerificaSensorBarreiraPortaoRua)
        OU(entradaSensorPortaoRuaAberto)
        EN(entradaSensorPortaoInternoAberto)
        EN(veiculoExecutandoMovimentoEntrada)
        ENTAO_EXECUTA_BLOCO {
            uint8_t i;
            EPC_Estacionamento epcLido;
            uint8_t num_of_tags = 0;        

            #ifndef DEBUG //definido em clp.h
            num_of_tags = realizaLeituraDeAntena(ANTENNA_1);
            #else
            EPC_Estacionamento epc;

            tags_[0].epc[0] = 0x30;
            tags_[0].epc[1] = 0x00;
            tags_[0].epc[2] = 0x04;
            tags_[0].epclen = 1;

            epc.byte1 = tags_[0].epc[2];
            epc.byte2 = tags_[0].epc[1];

            listaDeVeiculosLiberados.ponteiroTabela = 0;

            adicionaNovaTagNaLista(&listaDeVeiculosLiberados, epc);

            #endif
            if(num_of_tags > 0){
                for (i = 0; i < MAXTAG; i++) {
                    if (tags_[i].epclen > 0) {
                        if (verificaTagValida(tags_[i].epc) > 0) { // Tag veicular valida?
                            epcLido.byte1 = tags_[i].epc[2];
                            epcLido.byte2 = tags_[i].epc[1];
                            if(!buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido)){
                                if (buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epcLido)) { // Veiculo esta na lista?  
                                    adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido);
                                    tagEncontradaNaRua = 1;
                                } else {
                                    removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido);
                                }
                            }
                        }
                    }
                }
            }
            else{
                tagEncontradaNaRua = 0;
            }
            #ifndef DEBUG //definido em clp.h
            num_of_tags = realizaLeituraDeAntena(ANTENNA_2);
            #endif

            if(num_of_tags > 0){
                for (i = 0; i < MAXTAG; i++) {
                    if (tags_[i].epclen > 0) {
                        if (verificaTagValida(tags_[i].epc) > 0) { // Tag veicular valida?
                            epcLido.byte1 = tags_[i].epc[2];
                            epcLido.byte2 = tags_[i].epc[1];
                            if (!buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada, epcLido)) { // Veiculo esta na lista?  
                                EventoPassagem novoEvento;
                                uint8_t i = 0;

                                adicionaNovaTagNaLista(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido);
                                tagEncontradaNaClausura = 1;

                                novoEvento.id_veiculo[0] = epcLido.byte2;
                                novoEvento.id_veiculo[1] = epcLido.byte1;
                                novoEvento.tipoMovimento = MOVIMENTO_SAIDA; 
                                cadastrarNovoEvento(&eventosDePassagem, novoEvento);

                            } else {
                                removerRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Saida, epcLido);                              
                            }
                        }
                    }
                }
            }
            else{
                tagEncontradaNaClausura = 0;
            }
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="autoVerificaSeTagValidaFoiEncontrada">

        SEL(autoVerificaSeTagValidaFoiEncontrada)
        SUBIDA
        ENTAO_EXECUTA_BLOCO {

        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoRua">    

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
        E(numQuebrasBarreiraPortaoRua <= listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela)
        MEMO(entradaVeiculosRuaLiberada)
        
        SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
        ENTAO_EXECUTA_BLOCO{
            EventoPassagem novoEvento;
            uint8_t i = 0;
            
            for( i = 0; i < listaDeVeiculosLidosDuranteMovimento_Entrada.ponteiroTabela; i++ ){
                novoEvento.id_veiculo[0] = listaDeVeiculosLidosDuranteMovimento_Entrada.epc[i].byte2;
                novoEvento.id_veiculo[1] = listaDeVeiculosLidosDuranteMovimento_Entrada.epc[i].byte1;
                novoEvento.tipoMovimento = MOVIMENTO_ENTRADA;     
                cadastrarNovoEvento(&eventosDePassagem, novoEvento);
            }            
        }

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="autoVerificaSensorBarreiraPortaoInterno">    

        SEL(autoVerificaSensorBarreiraPortaoInterno)
        SUBIDA
        ENTAO_EXECUTA_BLOCO {

        }// </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="autoAcionaAberturaPortaoInterno">    

        SEL(dsp_tmpAcionaSinalAberturaPortaoInterno)
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
            removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLidosDuranteMovimento_Entrada);
            numQuebrasBarreiraPortaoRua = 0;
            numQuebrasBarreiraPortaoInterno = 0;
            tagEncontradaNaRua = 0;
        }// </editor-fold>      

        // </editor-fold> 
    
    // </editor-fold>

    //SOLICITACAO DE SAIDA PARA ABERTURA DO PORTAO DA RUA
    SEL(dsp_tmpAcionaSinalAberturaPortaoRua) //DISPARO PERIODICO TEMPORIZADO    
    E(entradaSensorPortaoRuaFechado)
    E(entradaSensorPortaoInternoFechado)
    MEMO(solicSaidaAbrirPortaoRua)

    //SOLICITACAO DE SAIDA DE ALARME PARA VEICULO SEM TAG DENTRO DA CLAUSURA
    SEL(autoVerificaQuantidadeTagsLidasEQuebrasDeBarreira)
    EN(entradaVeiculosRuaLiberada)
    OU(solicSaidaAlarme)
    E(entradaSensorPortaoInternoFechado)
    EN(autoReiniciaEntrada)
    MEMO(solicSaidaAlarme)
    
}

void CLP_atualizaSaidas(void){
    
    SEL(solicSaidaAbrirPortaoRua) 
    MEMO(leitorMarsOne_Rele1)
    
//    SEL(solicSaidaAbrirPortaoInterno) 
//    MEMO(leitorMarsOne_Rele2)
    SEL(0) 
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




