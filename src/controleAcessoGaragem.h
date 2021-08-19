
#include <xc.h>
#include "p24FJ256DA210.h"
#include "tabelaEstacionamento.h"
#include <stdio.h>


#define END_INICIAL_GREENLIST_EEPROM    30000
#define END_FINAL_GREENLIST_EEPROM    32000


#define SAIDA       0
#define ENTRADA     1
#define FECHADO     0
#define ABERTO      1


void ExecutaControleDeAcessoGaragem(void);
void exibirListaDeVeiculosLiberados(void);
char comandoParaAbrirPortao1(void);
void LiberaVeiculosNaClausura(void);
void trataAlarmeDoPortaoDeGaragem(void);
void lerBarreiraDeUltrasom(void);
void lerFluxoDeEntrada(void);
void lerFluxoDeSaida(void);
void VeiculoQuerendoEntrar(void);
void VeiculoQuerendoSair(void);
void Portao1AbertoManualmente(void);
void CadastraEventosDePassagem(TabelaDeEpcDeEstacionamento *tabelaEntrada, TabelaDeEpcDeEstacionamento *tabelaSaida);

//void CarregaEpcLido(unsigned char index);
