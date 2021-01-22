#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P24FJ256DA210.h"
#include "appl_commands.h"
#include "empilhadeira.h"
#include "perifericos.h"
#include "as3993_public.h"
#include "global.h"
#include "uart_driver.h"
#include "timer.h"
#include <math.h>
#include "tuner.h"
#include "tags.h"
#include "mem_i2c_24LC256.h"
#include "uart_driver.h"
#include "rtc.h"
#include "tuner.h"
#include "FSM_EventosDeParada.h"
#include "FSM_DataHora.h"
#include "FSM_TabelaDeExclusao.h"
#include "tabelaDeExclusao.h"
#include "FSM_ESP8266.h"
#include "FSM_Ethernet.h"
#include "setup_usb.h"

EPC areaDoVeiculo;

//Parametros para nova programacao de Empilhadeira
int obterPedestres(int Antena);

struct tm *dataHora;

extern TunerConfiguration mainTuner;
//extern __eds__ struct EstruturaTabelaDeExclusao TabelaDeExclusao;
//extern struct EstruturaTabelaDeExclusao TabelaDeExclusao;
extern char num_serie[20];

int ContagemParaEnviarOMeuOperadorParaAsOutrasEmpilhadeiras;

#define TAMANHO_DO_NOME_DA_EMPILHADEIRA 5
char NomeDaEmpilhadeira[TAMANHO_DO_NOME_DA_EMPILHADEIRA];


extern int pode_operar;
extern int tem_ze_na_area;
extern int total_parcial;

extern Tag __attribute__((far)) tags_[MAXTAG];


int ContagemDeTicksParaFazerALogicaDeOperadores;

int AntenaASerLida;
int DirecaoDaEmpilhadeira;
char ComandoObtidoParaAEmpilhadeira;



char ComandoParaEmpilhadeira[TAMANHO_BUFFER_DE_COMANDO_PARA_EMPILHADEIRA];

Pedestre ListaDePedestres[LIMITE_DE_PEDESTRES];
//Operador ListaDePedestresNoPortalDeExclusao[LIMITE_DE_PEDESTRES];
Operador ListaDeOperadores[QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA];
Operador MeuOperador;

int ZonaDeExclusaoDetectada;
int ContadorDeTempoDeValidadeDaZonaDeExclusao[6];
int DbmDaZonaDeExclusao[6];

int TempoDeBloqueioParaMaquinaLind;

#define TEMPO_DE_VALIDADE_DA_ZONA_DE_EXCLUSAO 2000


char CintoVirtual;
char DirecaoVirtual;

#define POSICAO_DO_MEU_OPERADOR 0

int ContadorDePausaEmCasoDePossivelAcidente;

int OperadorSentado;
int DirecaoDaMaquinaAnterior;

int JaSintonizado = 0;

extern int id_byte_um;

int TempoParaTrocarAntenaNaVarreduraFrontal;

//Prototipos

void setarAntenaASerLida(int Direcao);
void logicaDeOperadores (void);
int ehOMomentoDeFazerTesteAutomaticoDoSistema(void);
extern u8 inventoryGen2(void);
void enviarOperadorPorZigBee(void);
extern void uart4Tx (u8 dado);
int operadorJaCadastrado (unsigned char *Operador);
int ehEpcDeOperador(char * Epc);
int ehEpcDeDepestre(char * Epc);
int ehZonaDeExclusao(char * Epc);
int ehEpcDeOeradorParaFeira(unsigned char * Epc);
int ehEpcDePedestreParaFeira(unsigned char * Epc);
int ehPedestreValidoParaFeira (unsigned char *Epc);
int ehOEpcDoMeuOperador (unsigned char * Epc);

int ContadorDeDebonceDoCinto;
int NivelDoCinto;
int ContadorDeDebonceDoOperadorPresente;
int NivelDoOperadorPresente;
int OperadorPresente;
int ehEpcDeZonaDeExclusao(unsigned char * Epc);
void inverteBytesParaZonaDeExclusao (unsigned char *Epc);
int operadorValido(void);
int ehEpcDeOperador(char * Epc);
int retornaADirecaoDaZonaDeExclusaoEmFuncaoDaAntena(int Antena);
int trataReducaoDeVelocidadeDeJuizDeFora(unsigned char *Epc);
void logicaDePortalDeExclusao (void);
void iniciaVelocidadeDeJuizDeFora(void);
void trataComandoDaEmpilhadeira (void);

void apagarEsseEpcDaListaDePedestres (char *Etiqueta);
int confereSeTodosOsNiblesTemApenasNumeros(u8 *Epc, int Tamanho);
int confereSeOsByteNaoUsadosDoEpcEstaoEmZero(u8 *Epc, int Tamanho);

int AntenaAntiga;

//char IdDOLeitor[20];

unsigned char EpcTagEmpilhadeira[2];

#define LIMITE_DE_DEBOUNCE_BAIXO 10
#define LIMITE_DE_DEBOUNCE_ALTO 240

//Rotinas


void retornaIdDoLeitor(unsigned char*id){
    *id = idDoLeitor[0];
    id++;
    *id = idDoLeitor[1];
    id++;
    *id = idDoLeitor[2];
    id++;
    *id = idDoLeitor[3];    
}


int obterPotenciaDoRssi(unsigned char Rssi){
	int Q, I;
	int Resultado;
	Q = Rssi >> 4;
    Q = Q & 0x0F;
	I = Rssi & 0x0F;
	Resultado = sqrt((Q*Q) + (I*I));
	return Resultado;
}

signed int calculaRSSI(unsigned int indice)
{
    signed int rssi;
    signed int rssiI, rssiQ;

    rssiI = tags_[indice].rssi & 0x0F;           // pegamos a parte real do RSSI
    rssiQ = (tags_[indice].rssi >> 4) & 0x0F;    // pegamos a parte imaginaria do RSSI
    //rssi = (signed int)sqrt((rssiI*rssiI) + (rssiQ*rssiQ));   // calculo do modulo do RSSI
    rssi = (signed int)((rssiI*rssiI) + (rssiQ*rssiQ));         // calculo do modulo do RSSI sem extrair a raiz quadrada
    
    return(rssi);
}

unsigned int verifSeEhZonaExclusao(unsigned int indice)
{
    if((tags_[indice].epc[11] == 1) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 0) //&&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       //(tags_[indice].epc[2] == 0)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 0)
            )   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }
    if(//(tags_[indice].epc[11] == 0) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 0) &&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       (tags_[indice].epc[2] == 0)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 1))   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }

    if((tags_[indice].epc[11] == 30) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 1) //&&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       //(tags_[indice].epc[2] == 0)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 1)
            )   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }

    if(//(tags_[indice].epc[11] == 0) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 0) &&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       (tags_[indice].epc[2] == 1)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 30))   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }

    if((tags_[indice].epc[11] == 0x30) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 1) //&&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       //(tags_[indice].epc[2] == 0)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 1)
            )   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }

    if(//(tags_[indice].epc[11] == 0) && (tags_[indice].epc[10] == 0) && (tags_[indice].epc[9] == 0) &&
       //(tags_[indice].epc[8] == 0)  && (tags_[indice].epc[7] == 0)  && (tags_[indice].epc[6] == 0) &&
       //(tags_[indice].epc[5] == 0)  && (tags_[indice].epc[4] == 0)  && (tags_[indice].epc[3] == 0) &&
       (tags_[indice].epc[2] == 1)  && (tags_[indice].epc[1] == 0)  && (tags_[indice].epc[0] == 0x30))   // eh uma TAG da zona de exclusao
    {
        return(1);                      // se sim, retorna 1
    }
    

    return(0);                          // caso contrario, retorna 0
}



int adicinarOMeuOperador(char * Operador){//Apenas para testes
	memcpy(MeuOperador.Epc, Operador, TAMANHO_EPC_PARA_EMPILHADEIRA);
	MeuOperador.TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
    return 0;
}

int procurarPosicaoLivreNaListaDePedestres(void){
	int Contador;
	
	for(Contador = 0;Contador < LIMITE_DE_PEDESTRES;Contador = Contador + 1){
		if (ListaDePedestres[Contador].Epc[0] == 0){
			return Contador;
		}
	}
	return -1;
}

int pedestreJaPresente (unsigned char *Pedestre){
    int Contador;
    for (Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
        if (memcmp(&ListaDePedestres[Contador].Epc[0], Pedestre, TAMANHO_EPC_PARA_EMPILHADEIRA) == 0)
            return Contador;
    }
    return -1;
}
 
int adicionarPedestre(unsigned char *Pedestre, int Antena, int Rssi, int Indice){
	int Posicao;
	Posicao = procurarPosicaoLivreNaListaDePedestres();
	if (Posicao < 0){
		return Posicao;
	}
    
    /*
    if (pedestreJaPresente(Pedestre) >= 0){
        return -1;
    }
    */
    
    //Fazer rotina para impedir que item ja presente seja duplicado
	memcpy(ListaDePedestres[Posicao].Epc, Pedestre, TAMANHO_EPC_PARA_EMPILHADEIRA);
	ListaDePedestres[Posicao].Antena = Antena;
	ListaDePedestres[Posicao].Dbm = obterPotenciaDoRssi(Rssi);
    //ListaDePedestres[Posicao].TempoDeValidade = TEMPO_PARA_EXPIRAR_TAG_DA_TABELA_DE_EXCLUSAO;
    //ListaDePedestres[Posicao].Dbm = calculaRSSI(Indice);
    
	return Posicao;
}

int removerPedestrePorEpc(unsigned char *Epc){
	int Posicao;
	Posicao = operadorJaCadastrado(Epc);
	memset(ListaDePedestres[Posicao].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
	ListaDePedestres[Posicao].Dbm = 0;
	ListaDePedestres[Posicao].Antena = 0;
    return 0;
}

int removerPedestre(int Posicao){
	memset(ListaDePedestres[Posicao].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
	ListaDePedestres[Posicao].Dbm = 0;
	ListaDePedestres[Posicao].Antena = 0;
    return 0;
}

void enviaOcorrenciaDeEventoPorZigBee (unsigned char *EpcPedestre, unsigned char *EpcOperador){
    unsigned char Rascunho[10];
    memcpy(&Rascunho[0], EpcPedestre, TAMANHO_EPC_PARA_EMPILHADEIRA);
    memcpy(&Rascunho[TAMANHO_EPC_PARA_EMPILHADEIRA], EpcOperador, TAMANHO_EPC_PARA_EMPILHADEIRA);
    //enviaMensagemBinariaAoMonitorPorZigBee((char *)Rascunho, 6, COMANDO_EVENTO_ZIG_BEE);
}

void removerTodosOsPedestre(void){
	int Contador;
	for(Contador = 0;Contador < LIMITE_DE_PEDESTRES;Contador = Contador + 1){
		memset(ListaDePedestres[Contador].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
		ListaDePedestres[Contador].Dbm = 0;
		ListaDePedestres[Contador].Antena = 0;
	}


    /*
	for(Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
		memset(tags_[Contador].epc, 0, EPCLENGTH);
		memset(tags_[Contador].rn16, 0, 2);
        memset(tags_[Contador].handle, 0, 2);
		memset(tags_[Contador].pc, 0, 2);
        tags_[Contador].epclen = 0;
        tags_[Contador].rssi = 0;
        tags_[Contador].rssi = 0;
        tags_[Contador].agc = 0;
	}
    */
}

int removerOMeuOperador(void){
	memset(MeuOperador.Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
	MeuOperador.TempoDeValidade = 0;
	return 0;
}

void logicaDoMeuOperador (void){
    if (MeuOperador.TempoDeValidade > 0){
        MeuOperador.TempoDeValidade = MeuOperador.TempoDeValidade - 1;
    }

    if (MeuOperador.TempoDeValidade == 0){
        (void)removerOMeuOperador();
        MeuOperador.TempoDeValidade = -1;
    }
}

void lidaComDebounceDoCinto(void){
    if (_RG7 == 0){//Sankyu
    //if (_RG7){
        if (ContadorDeDebonceDoCinto >= LIMITE_DE_DEBOUNCE_ALTO){
            NivelDoCinto = 1;
            ContadorDeDebonceDoCinto = LIMITE_DE_DEBOUNCE_ALTO;
        } else {
            ContadorDeDebonceDoCinto = ContadorDeDebonceDoCinto + 1;
        }
    } else {
        if (ContadorDeDebonceDoCinto <= LIMITE_DE_DEBOUNCE_BAIXO){
            NivelDoCinto = 0;
            ContadorDeDebonceDoCinto = LIMITE_DE_DEBOUNCE_BAIXO;
        } else {
            ContadorDeDebonceDoCinto = ContadorDeDebonceDoCinto - 1;
        }
    }
}

void lidaComDebounceDaPresencaDoOperador(void){
    if (MeuOperador.TempoDeValidade == 0){
        NivelDoOperadorPresente = NAO;
    } else {
        if (OperadorPresente == SIM){
            if (ContadorDeDebonceDoOperadorPresente >= LIMITE_DE_DEBOUNCE_ALTO){
                NivelDoOperadorPresente = SIM;
                ContadorDeDebonceDoOperadorPresente = LIMITE_DE_DEBOUNCE_ALTO;
            } else {
                ContadorDeDebonceDoOperadorPresente = ContadorDeDebonceDoOperadorPresente + 5;
            }
        } else {
            if (ContadorDeDebonceDoOperadorPresente <= LIMITE_DE_DEBOUNCE_BAIXO){
                NivelDoOperadorPresente = NAO;
                ContadorDeDebonceDoOperadorPresente = LIMITE_DE_DEBOUNCE_BAIXO;
            } else {
                ContadorDeDebonceDoOperadorPresente = ContadorDeDebonceDoOperadorPresente - 1;
            }
        }
    }
}

void apagaZonaDeExclusao (int Indice){
    ContadorDeTempoDeValidadeDaZonaDeExclusao[Indice] = -1;
    DbmDaZonaDeExclusao[Indice] = 0;
}

int timerCounter = 0;

void operacoesEmTickParaEmpilhadeira(void){
       
    if (TempoParaTrocarAntenaNaVarreduraFrontal > 0){
        TempoParaTrocarAntenaNaVarreduraFrontal = TempoParaTrocarAntenaNaVarreduraFrontal - 1;
    }
       
    if (TempoDeBloqueioParaMaquinaLind > 0){
        TempoDeBloqueioParaMaquinaLind = TempoDeBloqueioParaMaquinaLind - 1;
    }
      
    timerCounter++;
    if(timerCounter>1000){
        timerCounter=0;
        atualizaHoraEData();
    }
    
    commandHandlerPortaUSB();
    
    executaMaquinaDeEstados_ESP8266(); //Wifi
    executaMaquinaDeEstados_DataHora();
    executaMaquinaDeEstados_EventosDeParada();
    executaMaquinaDeEstados_TabelaDeExclusao();    
}

int operadorJaCadastrado (unsigned char *Operador){
    int Contador;
    if (*Operador != 0x50){
        return -1;
    }
    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        if (memcmp(ListaDeOperadores[Contador].Epc, Operador, TAMANHO_EPC_PARA_EMPILHADEIRA)== 0)
            return Contador;
    }
    return -1;
}

int procuraPosicaoDeOperadorLivre(void){
    int Contador;
    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        if (ListaDeOperadores[Contador].Epc[0] == 0)
            return Contador;
    }
    return -1;
}

int pedestresPresentes (void){
    int Contador;
    int Resultado;

    Resultado = 0;
    for (Contador = 0;Contador < LIMITE_DE_PEDESTRES;Contador = Contador + 1){
        if (ListaDePedestres[Contador].Epc[0] != 0){
            Resultado = Resultado + 1;
            return Resultado;
        }
    }
    //return Resultado;
    return 0;
}

int retornaAoMenosUmPedestrePresente (void){
    int Contador;
    int Resultado;

    Resultado = 0;
    for (Contador = 0;Contador < LIMITE_DE_PEDESTRES;Contador = Contador + 1){
        if (ListaDePedestres[Contador].Epc[0] != 0)
            return Contador;
    }
    return -1;
}


int enviaPedestresQuePararamAEmpilhadeira (void){
 //   int Contador;
//    char Raschunho[50];
/*
    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        if (ListaDePedestres[Contador].Epc[0] != 0){
            (void)sprintf(Raschunho, "Bloqueio com %02X%02X%02X e operado por %02X%02X%02X R %02d A %d\n", 
                    ListaDePedestres[Contador].Epc[0], ListaDePedestres[Contador].Epc[1], ListaDePedestres[Contador].Epc[2],
                    MeuOperador.Epc[0], MeuOperador.Epc[1], MeuOperador.Epc[2],
                    ListaDePedestres[Contador].Dbm, ListaDePedestres[Contador].Antena);
            enviaMensagemPor485(Raschunho);
            delay_ms(100);
            return 0;
        }
    }*/
    return 0;
}

int cadastrarOperador(unsigned char *Operador){
    int Posicao;
    
    Posicao = operadorJaCadastrado(Operador);
    if (Posicao >= 0){
        ListaDeOperadores[Posicao].TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
        return -1;
    }
    
    Posicao = procuraPosicaoDeOperadorLivre();

    if (Posicao < 0)
        return -1;


    ListaDeOperadores[Posicao].TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
    (void)memcpy(ListaDeOperadores[Posicao].Epc, Operador, TAMANHO_EPC_PARA_EMPILHADEIRA);

    return 0;
}

int removeOperador (int Posicao){
    if (Posicao > QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA)
        return -1;
    memset(ListaDeOperadores[Posicao].Epc, 0 , TAMANHO_EPC_PARA_EMPILHADEIRA);
    return 0;
}

/*
int pedestreJaCadastradoNaListaDePortalDeExclusao (unsigned char *Operador){
    int Contador;

    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        if (memcmp(ListaDePedestresNoPortalDeExclusao[Contador].Epc, Operador, TAMANHO_EPC_PARA_EMPILHADEIRA)== 0)
            return Contador;
    }
    return -1;
}
 */

/*
int procuraPosicaoLivreNaListaDePortalDeExclusao (void){
    int Contador;

    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        if (ListaDePedestresNoPortalDeExclusao[Contador].Epc[0] == 0)
        return Contador;
    }
    return -1;
}
*/

/*
int cadastrarPedestreAListaDoPortalDeExclusao (unsigned char *Pedestre){
    int Posicao;

    Posicao = pedestreJaCadastradoNaListaDePortalDeExclusao(Pedestre);
    if (Posicao >= 0){
        ListaDeOperadores[Posicao].TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
        return -1;
    }

    Posicao = procuraPosicaoLivreNaListaDePortalDeExclusao();

    if (Posicao < 0)
        return -1;
    
    
    memcpy(ListaDePedestresNoPortalDeExclusao[Posicao].Epc, Pedestre, TAMANHO_EPC_PARA_EMPILHADEIRA);
    ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
    return 0;
}
*/

/*
int removePedestreDaListaDoPortalDeExclusaoPorEpc (unsigned char *Pedestre){
    int Posicao;
    
    Posicao = pedestreJaCadastradoNaListaDePortalDeExclusao(Pedestre);
    if (Posicao < 0){
        return -1;
    }
    memset(ListaDePedestresNoPortalDeExclusao[Posicao].Epc, 0 , TAMANHO_EPC_PARA_EMPILHADEIRA);
    //ListaDeOperadores[Posicao].TempoDeValidade = 0;
    ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade = 0;
    return 0;
}
*/

/*
int removePedestreDaListaDoPortalDeExclusao (int Posicao){
    if (Posicao > QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA)
        return -1;
    memset(ListaDePedestresNoPortalDeExclusao[Posicao].Epc, 0 , TAMANHO_EPC_PARA_EMPILHADEIRA);
    ListaDeOperadores[Posicao].TempoDeValidade = 0;
    return 0;
}
*/

/*
void logicaDePortalDeExclusao (void){
	int Posicao;
	
	for (Posicao = 0;Posicao < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA; Posicao = Posicao + 1){
        if (ListaDePedestresNoPortalDeExclusao[Posicao].Epc[0] != 0){
            if (ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade > 0){
                ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade 
                        = ListaDeOperadores[Posicao].TempoDeValidade - 1;
                if (ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade <= 0){
                    removePedestreDaListaDoPortalDeExclusao(Posicao);
                    ListaDePedestresNoPortalDeExclusao[Posicao].TempoDeValidade = 0;
                }

            }
        }
	}
}
*/



void limpaListaDePedestres(void){
    int Contador;
    for (Contador = 0;Contador < LIMITE_DE_PEDESTRES;Contador = Contador + 1){
        memset(ListaDePedestres[Contador].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
        ListaDePedestres[Contador].Antena = 0;
        ListaDePedestres[Contador].Dbm = 0;
    }
    
}

void limpaListaDeOperadores(void){
    int Contador;
    for (Contador = 0;Contador < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;Contador = Contador + 1){
        memset(ListaDeOperadores[Contador].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
        ListaDeOperadores[Contador].TempoDeValidade = 0;
    }
}

void limpaBufferInternoDasLeituras (int Tamanho){
    int Contador;
    for (Contador = 0;Contador < Tamanho;Contador = Contador + 1){
        memset(tags_[Contador].epc, 0, EPCLENGTH);//TAMANHO_EPC_PARA_EMPILHADEIRA);
        memset(tags_[Contador].rn16, 0, 2);
        memset(tags_[Contador].pc, 0, 2);
        tags_[Contador].epclen = 0;
        memset(tags_[Contador].handle, 0, 2);
        //tags_[Contador].handle[2];
        tags_[Contador].rssi = 0;
        tags_[Contador].agc = 0;                                
        //ListaDeOperadores[Contador].TempoDeValidade = 0;
    }
}


/*
void EnviaBytePara485 (char dado){
    //while (_LATG13 != 0);
    _LATG13 = 1;

    U1TXREG = dado;
    while( (!U1STAbits.TRMT ) );
    _LATG13 = 0;
}

void EnviaStringPara485 (char * dado){
    while (*dado != NULL){
        EnviaBytePara485(*dado);
        dado = dado + 1;
    }
}
*/

/*
int obterPosicaoDeEventoEmE2PROM(void){
    int Posicao;
    unsigned char Rascunho;
    Posicao = 0;
    
    //mem_leDados_24LC256(98, &Rascunho, 1);
    //EnviaBytePara485(Rascunho);
    //Posicao = Rascunho;
    //Posicao = Posicao << 8;

    mem_leDados_24LC256(99, &Rascunho, 1);
    //EnviaBytePara485(Rascunho);
    Posicao = Posicao | Rascunho;
    return Posicao;
}
*/

/*
int eventosArmazenadosEmE2PROM(void){
    unsigned int Rascunho;

    Rascunho = obterPosicaoDeEventoEmE2PROM();
    if (Rascunho > 100){
        //mem_escreve_24LC256(98, 0);
        mem_escreve_24LC256(99, 0);
        return 0;
    }

    return Rascunho;
}
*/

/*
int incrementaContadorDeEventosEmE2PROM(int Endereco){
    int Rascunho;
    char Dado;

    Endereco = Endereco + 1;
    Rascunho = Endereco;

    if (Endereco > 100){
        return 100;
    }

    
    //Rascunho = Rascunho & 0x00FF;
    //Dado = (char)Rascunho;
    //mem_escreve_24LC256(98, Dado);


    //Rascunho = Rascunho >> 8;
    Dado = (char)Rascunho;
    //mem_escreve_24LC256(99, Dado);
    return Endereco;
}
*/

/*
void adicionaUmEventoAE2PROM (char *Epc){
//void adicionaUmEventoAE2PROM (unsigned char *Mensagem){

    unsigned int Endereco;
    int Posicao;
    
    //char Rascunho[100];

    //memset(Rascunho, 0, 100);
    //sprintf(Rascunho, "%s,%02X%02X%02X,%s,%s,%s\n",num_serie,
    //        meu_operador[2], meu_operador[1],
    //        meu_operador[0], Epc, stringHora, stringData);
    

    Endereco = obterPosicaoDeEventoEmE2PROM();
    Endereco = Endereco + 1;
    Posicao = Endereco;
    Endereco = Endereco * 100;
    mem_escreveDados_24LC256(Endereco, (unsigned char *)Epc, 100);
    //mem_escreveDados_24LC256(Endereco, Rascunho, 100);
    //Endereco = incrementaContadorDeEventosEmE2PROM(Posicao);
    mem_escreve_24LC256(99, (char)Posicao);
}
*/

/*
void enviaEventosArmazenadosEmE2PROMParaAvaliacao(void){
    char Rascunho[100];
    unsigned int Endereco;
    int Contador;
    int Limite;

    Limite = eventosArmazenadosEmE2PROM();
    Endereco = 100;

    for(Contador = 0;Contador < Limite;Contador = Contador + 1){
        mem_leDados_24LC256(Endereco, (unsigned char *)Rascunho, 100);
        EnviaStringPara485(Rascunho);
        Endereco = Endereco + 100;
    }


}
*/

/*
void apagaTodosOsEventosArmazenasEmE2PROM (void){
    //char Rascunho[100];
    unsigned char Rascunho;
    unsigned int Endereco;

    //memset(Rascunho, 0, 100);
    for(Endereco = 100;Endereco < 10000;Endereco = Endereco + 100){
        mem_escreveDados_24LC256(Endereco, &Rascunho, 1);
    }

    //mem_escreve_24LC256(98, 0);
    mem_escreve_24LC256(99, 0);
    EnviaStringPara485("Apagado\n");
}
*/

/*
void trataRecepcaoDeDadosParaAvalicaoDeEmpilhadeira(char *Mensagem){
    //unsigned char Rascunho;
    if (memcmp(Mensagem, "HaDados?", 7) == 0){
        if (eventosArmazenadosEmE2PROM() > 0){
            EnviaStringPara485("Sim\n");
        } else {
            EnviaStringPara485("Nao\n");
        }

    }

    if (memcmp(Mensagem, "enviarDados", 11) == 0){
        enviaEventosArmazenadosEmE2PROMParaAvaliacao();
    }

    if (memcmp(Mensagem, "ApagarDados", 10) == 0){
        apagaTodosOsEventosArmazenasEmE2PROM();
    }
}
*/

/*
void enviaMensagemDeQuemParouAMaquina(void){
    int Processou = 0;
    char rascunhoDeString[100];

    //if ((meu_operador[0] != tags_[0].epc[2])
//           || (meu_operador[1] != tags_[0].epc[1])
//           || (meu_operador[2] != tags_[0].epc[0])
//           ){
//       int x;


    if ((MeuOperador.Epc[0] != tags_[0].epc[2])
           || (MeuOperador.Epc[1] != tags_[0].epc[1])
           || (MeuOperador.Epc[2] != tags_[0].epc[0])
           ){

       int x;

    
    //sprintf(Rascunho, "%02X%02X%02X,%s,%s,%s",meu_operador[2], meu_operador[1],
            //meu_operador[0], Epc, stringHora, stringData);

       for (x = 0;x < MAXTAG;x = x + 1){
           if (ListaDePedestres[x].Epc[0] != 0){
               sprintf(rascunhoDeString,
                    "Maquina operada por:%02X%02X%02X e parada pelo o pedestre:%02X%02X%02X e foram lidas %d tags as %s %s\n",
                    MeuOperador.Epc[0], MeuOperador.Epc[1],MeuOperador.Epc[2],
                    //tags_[x].epc[0], tags_[x].epc[1], tags_[x].epc[2], total_parcial,
                       ListaDePedestres[x].Epc[0], ListaDePedestres[x].Epc[1], ListaDePedestres[x].Epc[2], total_parcial,
                       //ListaDePedestres
                    stringHora, stringData);
               EnviaStringPara485(rascunhoDeString);
                memset(rascunhoDeString, 0, 50);
                sprintf(rascunhoDeString,"%02X%02X%02X,%02X%02X%02X,%02X%02X%02X,%s,%s\n",
                        IdDOLeitor[9],IdDOLeitor[10],IdDOLeitor[11],
                        MeuOperador.Epc[2], MeuOperador.Epc[1],MeuOperador.Epc[0],
                        tags_[x].epc[0], tags_[x].epc[1], tags_[x].epc[2],
                        stringHora, stringData);
                adicionaUmEventoAE2PROM(rascunhoDeString);
               Processou = 1;
           }
       }
    }
    if (Processou == 0){
        sprintf(rascunhoDeString, "Maquina foi parada e nao conseguir saber por qual epc\n");
        EnviaStringPara485(rascunhoDeString);
    }
}
*/

int obterPosicaoDeEventoEmE2PROM(void){
    int Posicao;
    unsigned char Rascunho;
    Posicao = 0;
    /*
    mem_leDados_24LC256(98, &Rascunho, 1);
    //EnviaBytePara485(Rascunho);
    Posicao = Rascunho;
    Posicao = Posicao << 8;
    */
    mem_leDados_24LC256(99, &Rascunho, 1);
    //EnviaBytePara485(Rascunho);
    Posicao = Posicao | Rascunho;
    return Posicao;
}

int eventosArmazenadosEmE2PROM(void){
    unsigned int Rascunho;
    
    Rascunho = obterPosicaoDeEventoEmE2PROM();
    if (Rascunho > 100){
        //mem_escreve_24LC256(98, 0);
        mem_escreve_24LC256(99, 0);
        return 0;
    }
  
    return Rascunho;
}

int incrementaContadorDeEventosEmE2PROM(int Endereco){
    int Rascunho;
    char Dado;
    
    Endereco = Endereco + 1;
    Rascunho = Endereco;

    if (Endereco > 100){
        //return 100;
        return 0;
    }
    
    /*
    Rascunho = Rascunho & 0x00FF;
    Dado = (char)Rascunho;
    mem_escreve_24LC256(98, Dado);
    */

    //Rascunho = Rascunho >> 8;
    Dado = (char)Rascunho;
    //mem_escreve_24LC256(99, Dado);
    return Endereco;
}

void adicionaUmEventoAE2PROM (unsigned char *Epc){
//void adicionaUmEventoAE2PROM (unsigned char *Mensagem){
    
    unsigned int Endereco;
    int Posicao;
    /*
    char Rascunho[100];

    memset(Rascunho, 0, 100);
    sprintf(Rascunho, "%s,%02X%02X%02X,%s,%s,%s\n",num_serie,
            meu_operador[2], meu_operador[1],
            meu_operador[0], Epc, stringHora, stringData);
    */

    Endereco = obterPosicaoDeEventoEmE2PROM();
    Endereco = Endereco + 1;
    Posicao = Endereco;
    Endereco = Endereco * 100;
    mem_escreveDados_24LC256(Endereco, Epc, 100);
    //mem_escreveDados_24LC256(Endereco, Rascunho, 100);
    //Endereco = incrementaContadorDeEventosEmE2PROM(Posicao);
    mem_escreve_24LC256(99, (char)Posicao);
}

void enviaEventosArmazenadosEmE2PROMParaAvaliacao(void){
    char Rascunho[100];
    unsigned int Endereco;
    int Contador;
    //int SubContadorParaGerarCRC;
    int Limite;
    //unsigned int CRC = 0x5555;
    //unsigned char Dado;
    
    Limite = eventosArmazenadosEmE2PROM();
    Endereco = 100;
    
    for(Contador = 0;Contador < Limite;Contador = Contador + 1){
        mem_leDados_24LC256(Endereco,(unsigned char *) Rascunho, 100);
        if ((unsigned char)Rascunho[0] != 0xFF){
//            EnviaStringPara485(Rascunho);
            Endereco = Endereco + 100;
        }
        
        /*
        for(SubContadorParaGerarCRC = 0;SubContadorParaGerarCRC < Limite; SubContadorParaGerarCRC = SubContadorParaGerarCRC + 1){
            if (Rascunho[SubContadorParaGerarCRC] == 0)break;
            CRC = CRC ^ Rascunho[SubContadorParaGerarCRC];
        }
        */
    }
    
    /*
    Dado = (unsigned char)(CRC >> 8);
    EnviaStringPara485(Dado);

    Dado = (unsigned char)(CRC & 0x00FF);
    EnviaStringPara485(Dado);
    */
    
}

void apagaTodosOsEventosArmazenasEmE2PROM (void){
    //char Rascunho[100];
    unsigned char Rascunho = 0;
    unsigned int Endereco;
    
    //memset(Rascunho, 0, 100);
    for(Endereco = 100;Endereco < 10000;Endereco = Endereco + 100){
        mem_escreveDados_24LC256(Endereco, &Rascunho, 1);
    }
    
    //mem_escreve_24LC256(98, 0);
    mem_escreve_24LC256(99, 0);
//    EnviaStringPara485("Apagado\n");
}

void filtraOperadorDeMensagemRecebidaDeOutraEmpilhadeira(unsigned char *Mensagem){
    Mensagem = Mensagem + 14;
    cadastrarOperador(Mensagem);
    Mensagem = Mensagem - 14;
}

void trataRecepcaoDeDadosParaAvalicaoDeEmpilhadeira(char *Mensagem){
    //unsigned char Rascunho;
    int Contador;
    char rascunhoDeString[100];
    
    

    (void)sprintf(rascunhoDeString, "Operador=");
    if (memcmp(Mensagem, rascunhoDeString, strlen(rascunhoDeString)) == 0){
        Contador = strlen(Mensagem);
        if (Contador == 17){
            filtraOperadorDeMensagemRecebidaDeOutraEmpilhadeira((unsigned char *)Mensagem);
        }
    }

    
    
    //if (memcmp(Mensagem, "HaDados?", 7) == 0){
    //(void)sprintf(rascunhoDeString, "%c%c%c%c-HaDados?", num_serie[8],num_serie[9],num_serie[10],num_serie[11]);
    (void)sprintf(rascunhoDeString, "%c%c%c%c-HaDados?", num_serie[0],num_serie[1],num_serie[2],num_serie[3]);
    if (memcmp(Mensagem, rascunhoDeString, strlen(rascunhoDeString)) == 0){
        if (eventosArmazenadosEmE2PROM() > 0){
//            EnviaStringPara485("Sim\n");
        } else {
      //      EnviaStringPara485("Nao\n");
        }
        
    }

    
    //if (memcmp(Mensagem, "enviarDados", 11) == 0){
    //(void)sprintf(rascunhoDeString, "%c%c%c%c-enviarDados", num_serie[8],num_serie[9],num_serie[10],num_serie[11]);
    (void)sprintf(rascunhoDeString, "%c%c%c%c-enviarDados", num_serie[0],num_serie[1],num_serie[2],num_serie[3]);
    
    if (memcmp(Mensagem, rascunhoDeString, strlen(rascunhoDeString)) == 0){
        enviaEventosArmazenadosEmE2PROMParaAvaliacao();
    }

    
    //if (memcmp(Mensagem, "ApagarDados", 10) == 0){
    //(void)sprintf(rascunhoDeString, "%c%c%c%c-ApagarDados", num_serie[8],num_serie[9],num_serie[10],num_serie[11]);
    (void)sprintf(rascunhoDeString, "%c%c%c%c-ApagarDados", num_serie[0],num_serie[1],num_serie[2],num_serie[3]);
    if (memcmp(Mensagem, rascunhoDeString, strlen(rascunhoDeString)) == 0){
        apagaTodosOsEventosArmazenasEmE2PROM();
    }

    if (memcmp(Mensagem, "Epoch=", 6) == 0){
        Mensagem = Mensagem + 6;
        SetaTempoComEpoch(atol(Mensagem));
    }
    
    if (memcmp(Mensagem, "Hora?", 5) == 0){
        sprintf(rascunhoDeString, "Hora do Leitor = %s %s\n", stringHora, stringData);
//        EnviaStringPara485(rascunhoDeString);
    }

}



void enviaMensagemDeQuemParouAMaquina(void){
   /* int Processou = 0;
    char meu_operador[3];
    char rascunhoDeString[100];
    int x;
    
    meu_operador[0] = MeuOperador.Epc[2];
    meu_operador[1] = MeuOperador.Epc[1];
    meu_operador[2] = MeuOperador.Epc[0];
    */
    /*
    if ((meu_operador[0] != tags_[0].epc[2])
           || (meu_operador[1] != tags_[0].epc[1])
           || (meu_operador[2] != tags_[0].epc[0])
           ){
    */
       
       
    //sprintf(Rascunho, "%02X%02X%02X,%s,%s,%s",meu_operador[2], meu_operador[1],
            //meu_operador[0], Epc, stringHora, stringData);
      /* 
       for (x = 0;x < MAXTAG;x = x + 1){
           if (ListaDePedestres[x].Epc[0] != 0){
                sprintf(rascunhoDeString, 
                    "Maquina operada por:%02X%02X%02X e parada pelo o pedestre:%02X%02X%02X e foram lidas %d tags as %s %s\n",  
                    meu_operador[2], meu_operador[1],meu_operador[0],
                    ListaDePedestres[x].Epc[0], ListaDePedestres[x].Epc[1], ListaDePedestres[x].Epc[2], total_parcial,
                    stringHora, stringData);
                //EnviaStringPara485(rascunhoDeString);
                memset(rascunhoDeString, 0, 50);
                
                sprintf(rascunhoDeString,"%02X%02X%02X,%02X%02X%02X,%02X%02X%02X,%s,%s\n", 
                        num_serie[9],num_serie[10],num_serie[11],
                        meu_operador[2], meu_operador[1],meu_operador[0],
                        ListaDePedestres[x].Epc[0], ListaDePedestres[x].Epc[1], ListaDePedestres[x].Epc[2],
                        stringHora, stringData);
                
                sprintf(rascunhoDeString,"00%c%c%c%c,%02X%02X%02X,%02X%02X%02X,%s,%s\n", 
                        num_serie[0],num_serie[1],num_serie[2],num_serie[3],
                        meu_operador[2], meu_operador[1],meu_operador[0],
                        ListaDePedestres[x].Epc[0], ListaDePedestres[x].Epc[1], ListaDePedestres[x].Epc[2],
                        stringHora, stringData);
                adicionaUmEventoAE2PROM((unsigned char *)rascunhoDeString);
                Processou = 1;
           }
       }
    //}
    if (Processou == 0){
        //sprintf(rascunhoDeString, "Maquina foi parada e nao conseguir saber por qual epc\n");
        //EnviaStringPara485(rascunhoDeString);
    }*/
}

/*
void filtraEpcQueNaoFazemParteDoSistema (int Tamanho){
    int Contador;
    
    for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
        if ((tags_[Contador].epc[0] != 0x30) && (tags_[Contador].epc[0] != 0x50)){
            memset(tags_[Contador].epc, 0, EPCLENGTH);
            
            //tags_[Contador].epclen = 0;
        }
        
        if ((meu_operador[0] == tags_[Contador].epc[2]) 
                && (meu_operador[1] == tags_[Contador].epc[1])
                && (meu_operador[2] == tags_[Contador].epc[0])
                ){
            memset(tags_[Contador].epc, 0, EPCLENGTH);
            tags_[Contador].epclen = 0;
        }
    }
}
*/

/*
void filtraEpcQueNaoFazemParteDoSistema (int Tamanho){
    int Contador;

    for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
        if ((tags_[Contador].epc[0] != 0x30) && (tags_[Contador].epc[0] != 0x50)){
            memset(tags_[Contador].epc, 0, EPCLENGTH);

            //tags_[Contador].epclen = 0;
        }

        if ((meu_operador[0] == tags_[Contador].epc[2])
                && (meu_operador[1] == tags_[Contador].epc[1])
                && (meu_operador[2] == tags_[Contador].epc[0])
                ){
            memset(tags_[Contador].epc, 0, EPCLENGTH);
            tags_[Contador].epclen = 0;
        }
    }
}
*/

void iniciaLogicaDeEmpilhadeira (void){
    //int Contador;
    //signed char x;

    //enviaTextoDeLogDaOperacao("\nInicia Operacao da empilhaderia\n");
    
//    ObtemID(IdDOLeitor);

    ContagemDeTicksParaFazerALogicaDeOperadores = TICKS_PARA_UM_SEGUNDO;

    //(void)sprintf(NomeDaEmpilhadeira, "nulo");

    limpaListaDeOperadores();
    limpaListaDePedestres();
  
    //iniciaEstruturaDoProtocolo();
    CintoVirtual = 0;
    OperadorSentado = NAO;
    DirecaoDaEmpilhadeira = DIRECAO_NULA;
    DirecaoDaMaquinaAnterior = DIRECAO_NULA;
    
    //iniciaVelocidadeGps();
    ZonaDeExclusaoDetectada = 0;
    //as3993SetSensitivity(125);
    
    //iniciaVelocidadeDeJuizDeFora();
}

void logicaDeOperadores (void){
	//Inteirar os operadores e remover quanto o tempo expirar
	int Posicao;
	
    /*
	if (MeuOperador.TempoDeValidade != 0){
		MeuOperador.TempoDeValidade = MeuOperador.TempoDeValidade - 1;
	}
    */
	
	for (Posicao = 0;Posicao < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA; Posicao = Posicao + 1){
		if (ListaDeOperadores[Posicao].TempoDeValidade > 0){
			ListaDeOperadores[Posicao].TempoDeValidade = ListaDeOperadores[Posicao].TempoDeValidade - 1;
			if (ListaDeOperadores[Posicao].TempoDeValidade == 0){
                removeOperador(Posicao);
				//printf("eliminacao na posicao %d\n",Posicao);
			}
		} /*else {
            if (ListaDeOperadores[Posicao].Epc[0] != 0){
                removeOperador(Posicao);
            }
        }*/
	}
}

void desabilitaEmpilhadeira (void){
    //Logica inversa
#ifdef SANKYU_SAO_PAULO_EMPILHADEIRA_2_5_TONS
    desliga_rele1();
    desliga_rele3();
    
#elif ARCELOR_JUIZ_DE_FORA_EMPILHADEIRA_TRADMAQ_3_5_TONS
    liga_rele1();
    liga_rele3();
    
#elif BRUNAUER_JOAO_MONLEVADE_EMPILHADEIRA_2_5_TONS
    desliga_rele1();
    desliga_rele3();
    
#elif SANKYU_JOAO_MONLEVADE_EMPILHADEIRA_7_5_TONS
    desliga_rele1();
    desliga_rele3();

#endif    
    
    
    //Ligoca normal, JUIZ DE FORA
    //liga_rele1();
    //liga_rele3();
    //Ligoca normal, MONLEVAD
    //desliga_rele1();
    //desliga_rele3();


    
}

void habilitarEmpilhadeira (void){
#ifdef SANKYU_SAO_PAULO_EMPILHADEIRA_2_5_TONS 
    //Logica inversa
    //Ligoca normal, JUIZ DE FORA
    liga_rele1();
    liga_rele3();
    
#elif ARCELOR_JUIZ_DE_FORA_EMPILHADEIRA_TRADMAQ_3_5_TONS
    desliga_rele1();
    desliga_rele3();
    
#elif BRUNAUER_JOAO_MONLEVADE_EMPILHADEIRA_2_5_TONS
    liga_rele1();
    liga_rele3();
    
#elif SANKYU_JOAO_MONLEVADE_EMPILHADEIRA_7_5_TONS
    liga_rele1();
    liga_rele3();
    
#endif    
    
    //Ligoca normal
    //Ligoca normal, JUIZ DE FORA
    //desliga_rele1();
    //desliga_rele3();
    //Ligoca normal, MONLEVAD
    //liga_rele1();
    //liga_rele3();
    

}

void acionaFitaDeLedsDaEmpilhadeira (void){
    liga_rele4();
}

void desacionaFitaDeLedsDaEmpilhadeira (void){
    desliga_rele4();
}

void acionaSireneDaEmpilhadeira (void){
    liga_rele2();
}

void desacionaSireneDaEmpilhadeira (void){
    desliga_rele2();
}

int operadorPresente(void){
    int TempoDeValidadeDOOperador;
    int Contador;
    
    // *************************************************************************
    //Para debugar quando, nao tenho operador disponivel
#ifdef SEM_OPERADOR
    const char OPERADOR_PARA_TESTE [3] = {0x50, 0x09, 0x99 };
    memcpy(MeuOperador.Epc, OPERADOR_PARA_TESTE, TAMANHO_EPC_PARA_EMPILHADEIRA);
    MeuOperador.TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
    return SIM;
#endif
    // *************************************************************************
    
    
    sel_led(0,0);//Apaga leds
    setarAntenaASerLida(ANTENA_PARA_LER_O_OPERADOR);
    setarAntenaASerLida(1);
    comecaInvetorio();
    TempoDeValidadeDOOperador = MeuOperador.TempoDeValidade;
    //if (TempoDeValidadeDOOperador > TEMPO_PARA_PROCURAR_O_OPERADOR){
    if (TempoDeValidadeDOOperador != 0){
        if (ehEpcDeOperador((char *)MeuOperador.Epc) == SIM){
            return SIM;
        }
    }
    
    sel_led(ANTENA_PARA_LER_O_OPERADOR,1);
    //if (inventorioSimplificado()){
    limpaBufferInternoDasLeituras(MAXTAG);
    if (inventorioSimplificado()){        
        for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
            //liga_led_tag();
            //limpaBufferInternoDasLeituras();

            sel_led(ANTENA_PARA_LER_O_OPERADOR,0);//Apaga leds
            sel_led(0,0);//Apaga leds
            desliga_led_tag();
            
            if (confereSeTodosOsNiblesTemApenasNumeros(tags_[Contador].epc, TAMANHO_EPC_PARA_EMPILHADEIRA)){
                memset(tags_[Contador].epc, 0, EPCLENGTH);
            }

            if (confereSeOsByteNaoUsadosDoEpcEstaoEmZero(&tags_[Contador].epc[TAMANHO_EPC_PARA_EMPILHADEIRA], (EPCLENGTH - TAMANHO_EPC_PARA_EMPILHADEIRA))){
                memset(tags_[Contador].epc, 0, EPCLENGTH);
            }
            

            //if (ehEpcDeOperador(MeuOperador.Epc) == 0){
            if (ehEpcDeOperador((char *)tags_[Contador].epc) == 0){
                return NAO;
            }

            //if (OperadorEstaNaTabelaDeExclusao((char *)tags_[Contador].epc) == SIM){
            /*
            if (elementroPresenteNaTabelaDeExclusao((char *)tags_[Contador].epc) < 0){
                return NAO;
            }
            */

            //liga_led_tag();
            memcpy(MeuOperador.Epc, tags_[Contador].epc, TAMANHO_EPC_PARA_EMPILHADEIRA);
            MeuOperador.TempoDeValidade = TEMPO_DE_VALIDADE_DE_OPERADOR;
            limpaBufferInternoDasLeituras(MAXTAG);
            desliga_led_tag();
            return SIM;
        }
    };
    sel_led(0,0);//Apaga leds
    return NAO;
}


int subRotinaCintoColocado(void){
    if (CintoVirtual){
        return SIM;
    }
    
    if (NivelDoCinto){
      return NAO;
    }
    return SIM;
}



int subRotinaCintoColocadoInvertido(void){
    if (CintoVirtual){
        return SIM;
    }
    
    if (NivelDoCinto){
      return SIM;
    }
    return NAO;
}


int cintoColocado(void){
#ifdef ARCELOR_JUIZ_DE_FORA_EMPILHADEIRA_TRADMAQ_3_5_TONS
    return SIM;
    
#elif BRUNAUER_JOAO_MONLEVADE_EMPILHADEIRA_2_5_TONS
    return SIM;
    
#elif SANKYU_SAO_PAULO_EMPILHADEIRA_2_5_TONS
    return subRotinaCintoColocado();
    
#elif SANKYU_JOAO_MONLEVADE_EMPILHADEIRA_7_5_TONS
    return subRotinaCintoColocadoInvertido();
    
#endif
    
    
    /*
    if (CintoVirtual){
        return SIM;
    }
    
    if (NivelDoCinto){
      return NAO;
    }
    */
    return SIM;
    
}

extern char stringHora[20];

int ehOMomentoDeFazerTesteAutomaticoDoSistema(void){
    if ((strstr(stringHora,"00:00:")) || (strstr(stringHora,"08:00:")) || (strstr(stringHora,"16:00:")))
        return SIM;
    return NAO;
}

int testeAutomaticoDoSistema(void){
    return 0;
}

int obterDirecaoDaMovimentacaoDaEmpilhadeira(void){
    /*
    if (DirecaoVirtual == 1){
        return FRENTE;
    }

    if (DirecaoVirtual == 2){
        return TRAS;
    }
    * */

    if (_RG6){
        return FRENTE;
    } else {
        return TRAS;
    }
}

void setarAntenaASerLida(int Antena){
    sel_antena(Antena);
}

unsigned char RepeticaoDeLeitura;

int setarAntenaEmFuncaoDaDirecao(int Direcao, int AtenaQueFoiLida){
    int Antena = 0;
    sel_led(0, 0);
    if (Direcao == FRENTE){
      //tunerInitFrenteSankyu(&mainTuner);
      if (AtenaQueFoiLida == 1)
        Antena = 2;
      else
        Antena = 1;
      //sel_led(Antena, 1);
    } else {
    //if(Direcao == TRAS){
    //Antena = 3;
        //tunerInitTraseiraSankyu(&mainTuner);
        if (AtenaQueFoiLida == 3){
            //Antena = 5; retiramos pois nao faz sentido ler a antena 3
            Antena = 3;
        } else {
            Antena = 3;
            //sel_led(Antena, 1);
        }
    }
    //sel_antena(Antena);
    //sel_led(Antena, 1);
    return Antena;
}

/*
unsigned int setaONumeroDeRepeticaoDeLeiturasEmFuncaoDaAntena(int Antena){
    if (Antena == 1)
        //return 3;
        return 60000;//3;
        
    if (Antena == 2)
        //return 3;
        return 60000;//3;
    if (Antena == 3)
        //return 60000;//12;//3 //6
        return 30000;//12;//3 //6
    if (Antena == 4)
        return 3;//6
    if (Antena == 6)
        return 1;
    return 1;
}
*/

unsigned int setaONumeroDeRepeticaoDeLeiturasEmFuncaoDaAntena(int Antena){
    if (Antena == 1){
        //return 3;
        TempoParaTrocarAntenaNaVarreduraFrontal = TEMPO_PARA_VARREDURA_EM_ANTENA; 
        return 60000;//3;
    }
    if (Antena == 2){
        //return 3;
        TempoParaTrocarAntenaNaVarreduraFrontal = TEMPO_PARA_VARREDURA_EM_ANTENA;
        return 60000;//3;
    }
    if (Antena == 3){
        TempoParaTrocarAntenaNaVarreduraFrontal = TEMPO_PARA_VARREDURA_EM_ANTENA;
        //return 60000;//12;//3 //6
        return 30000;//12;//3 //6
    }
    if (Antena == 4){
        return 3;//6
    }
    if (Antena == 6){
        return 1;
    }
    
    TempoParaTrocarAntenaNaVarreduraFrontal = TEMPO_PARA_VARREDURA_EM_ANTENA; //Em mili segundo
    return 1;
}


int fazAjusteDeRssiParaZonaDeExclusao(int rssi){
    //rssi += FATOR_CORRECAO_TAG;         // soma o fator
     if(rssi <= 2)                               // se rssi menor que 2 (extremamente fraco)
         rssi += (FATOR_CORRECAO_TAG - ((FATOR_CORRECAO_TAG >> 2)+(FATOR_CORRECAO_TAG >> 3)));   // entao soma o fator-((fator/4)+(fator/8)) (faixa de 25 ~ 27)
     else if((rssi > 2) && (rssi <= 10))         // se rssi entre 2 e 10 (muito fraco)
         rssi += (FATOR_CORRECAO_TAG >> 1);      // entao soma 1/2 do fator (faixa de 22 ~ 30)
     else if((rssi > 10) && (rssi <= 30))        // se rssi entre 10 e 30 (fraco)
         rssi += (FATOR_CORRECAO_TAG >> 2);      // entao soma 1/4 do fator (faixa de 20 ~ 40)
     else if((rssi > 30) && (rssi <= 40))        // se rssi entre 30 e 40 (medio)
         rssi += (FATOR_CORRECAO_TAG >> 3);      // entao soma 1/8 do fator (faixa de 35 ~ 45)
     else if((rssi > 40) && (rssi <= 45))        // se rssi entre 40 e 45 (forte)
         rssi += (FATOR_CORRECAO_TAG >> 4);      // entao soma 1/16 do fator (faixa de 42 ~ 47)
     else if((rssi > 45) && (rssi <= 47))        // se rssi entre 45 e 47 (muito forte)
         rssi += (FATOR_CORRECAO_TAG >> 5);      // entao soma 1/32 do fator (faixa de 46 ~ 48)
     else if(rssi > 47)                          // se rssi maior que 47
         ;                                       // nao soma nada
     return rssi;
}


int confereSeOsByteNaoUsadosDoEpcEstaoEmZero(u8 *Epc, int Tamanho){
    int Contador;
    char Resultado;
    Resultado = 0;
    for (Contador = 0;Contador < Tamanho;Contador = Contador + 1){
        Resultado = Resultado | *Epc;
        Epc = Epc + 1;
    }
    return Resultado;
}

int confereSeTodosOsNiblesTemApenasNumeros(u8 *Epc, int Tamanho){
    int Contador;
    char Resultado;
    char Nible;
    Resultado = 0;
    for (Contador = 0;Contador < Tamanho;Contador = Contador + 1){
        Nible = *Epc;
        Nible = Nible >> 4;
        if (Nible > 9)Resultado = Resultado | 1;
     
        Nible = *Epc;
        Nible = Nible & 0x0F;
        if (Nible > 9)Resultado = Resultado | 1;
        
        Epc = Epc + 1;
    }
    return Resultado;    
}


int obterPedestres(int Antena){
    int TagsObtidas;
    int Contador;
    int Resultado;
    int Rascunho;
    int SelecaoDaZonaDeExclusao;
    
    //TagsObtidas = 0;
   
    TagsObtidas = inventorioSimplificado();
    //TagsObtidas = inventoryGen2();
    
    if (TagsObtidas == 0){
        return 0;
    }
    
    liga_led_tag();
    
    if (TagsObtidas >= (MAXTAG + 1)){
        TagsObtidas = 0;
        return TagsObtidas;
    }
    
    //for (Contador = 0;Contador < TagsObtidas;Contador = Contador + 1){
    //ZonaDeExclusaoDetectada = ZonaDeExclusaoDetectada - 1;
    //for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
    for (Contador = 0;Contador < TagsObtidas;Contador = Contador + 1){
        //liga_led_tag();
        Resultado = 0;
        
        //Resultado = Resultado + ehEpcDeOeradorParaFeira(tags_[Contador].epc);
        //Resultado = Resultado + ehEpcDePedestreParaFeira(tags_[Contador].epc);
        Resultado = Resultado + ehEpcDeOperador((char *)tags_[Contador].epc);
        Resultado = Resultado + ehEpcDeDepestre((char *)tags_[Contador].epc);
        Resultado = Resultado + ehEpcDeEmpilhadeira((char *)tags_[Contador].epc);
        Resultado = Resultado + (tags_[Contador].epc[0] == 0x40 ? 1:0); // TAG DE AREA
        Rascunho = trataReducaoDeVelocidadeDeJuizDeFora(tags_[Contador].epc);
        if (Rascunho != 0){
            memset(tags_[Contador].epc, 0, EPCLENGTH);//3
        }
        
        if (confereSeTodosOsNiblesTemApenasNumeros(tags_[Contador].epc, TAMANHO_EPC_PARA_EMPILHADEIRA)){
            memset(tags_[Contador].epc, 0, EPCLENGTH);
        }

        if (confereSeOsByteNaoUsadosDoEpcEstaoEmZero(&tags_[Contador].epc[TAMANHO_EPC_PARA_EMPILHADEIRA], (EPCLENGTH - TAMANHO_EPC_PARA_EMPILHADEIRA))){
            memset(tags_[Contador].epc, 0, EPCLENGTH);
        }

        
        /*
        if  ((ehEpcDeDepestre((char *)tags_[Contador].epc) == 0  && ehEpcDeOperador((char *)tags_[Contador].epc) == 0)){
         * 
            memset(tags_[Contador].epc, 0, EPCLENGTH);//3
        }
        */
                
        //if (ehEpcDeZonaDeExclusao(tags_[Contador].epc)){
        
        if (verifSeEhZonaExclusao(Contador)){
            //Resultado = Resultado + 1;
            //Rascunho = calculaRSSI(Contador);
            SelecaoDaZonaDeExclusao = retornaADirecaoDaZonaDeExclusaoEmFuncaoDaAntena(Antena);
            //if (DbmDaZonaDeExclusao[Antena] < Rascunho){
            //    DbmDaZonaDeExclusao[Antena] = Rascunho;
            //}
            
            //sel_led(7,1);
            Rascunho = obterPotenciaDoRssi(tags_[Contador].rssi);            
            //Rascunho = fazAjusteDeRssiParaZonaDeExclusao(Rascunho);
            if (DbmDaZonaDeExclusao[SelecaoDaZonaDeExclusao] < Rascunho){
                DbmDaZonaDeExclusao[SelecaoDaZonaDeExclusao] = Rascunho;
            }
            
            //inverteBytesParaZonaDeExclusao(tags_[Contador].epc);
            //ZonaDeExclusaoDetectada = 10;
            //ContadorDeTempoDeValidadeDaZonaDeExclusao[Antena] = TEMPO_DE_VALIDADE_DA_ZONA_DE_EXCLUSAO;
            ContadorDeTempoDeValidadeDaZonaDeExclusao[SelecaoDaZonaDeExclusao] = TEMPO_DE_VALIDADE_DA_ZONA_DE_EXCLUSAO;
        }       
        
        if(tags_[Contador].epc[0] == 0x40){ // TAG DE AREA
            
            areaDoVeiculo.byte4 = tags_[Contador].epc[0];
            areaDoVeiculo.byte3 = tags_[Contador].epc[1];
            areaDoVeiculo.byte2 = tags_[Contador].epc[2];
            areaDoVeiculo.byte1 = tags_[Contador].epc[3]; 
            
            memset(tags_[Contador].epc, 0, EPCLENGTH);
            
            Resultado = 0;
        }
        
        if (ehOEpcDoMeuOperador(tags_[Contador].epc) == 1){
            Resultado = 0;
            memset(tags_[Contador].epc, 0, EPCLENGTH);//TAMANHO_EPC_PARA_EMPILHADEIRA);
        }
        
        if ((operadorValido()) == 0 && (Antena != ANTENA_PARA_LER_O_OPERADOR)){
            Resultado = 0;
        }
        
        if(Resultado > 0){// == 1
            //liga_led_tag();
            (void)adicionarPedestre((unsigned char *)tags_[Contador].epc, Antena, tags_[Contador].rssi, Contador);
            //if (ehPedestreValidoParaFeira((unsigned char *)tags_[Contador].epc)){
            //    (void)adicionarPedestre((unsigned char *)tags_[Contador].epc, Antena, tags_[Contador].rssi);
            //}
            //TagsObtidas = TagsObtidas | 1;
        }
    }   
    
    //limpaBufferInternoDasLeituras();
    limpaBufferInternoDasLeituras(TagsObtidas);
    return TagsObtidas;
}


int AtualizarPontenciaDeRFIDEmFuncaoDaVelocidadeDaMaquina(void){
    /*
    signed char Sensibilidade;
    //desliga_buzzer();
    
    atualizaLedGps();
    if ((EstadoLedGps != ESTADO_LED_PISCANDO__ACESSO_GPS) && (EstadoLedGps != ESTADO_LED_PISCANDO__APAGADO_GPS)){
        return 0;
    }
    if (VelocidadeFinal > LIMITE_DE_VELOCIDADE_GPS){
        Sensibilidade = as3993GetSensitivity();
        if (Sensibilidade != 125){
            as3993SetSensitivity(125);

            //liga_buzzer();
            //desliga_led_gps();
            EstadoLedGps = ESTADO_LED_LIGADO_GPS;;
        }
    } else {
        
        Sensibilidade = as3993GetSensitivity();
        if (Sensibilidade != -80){
            as3993SetSensitivity(-80);
            //liga_buzzer();
            //liga_led_gps();
            EstadoLedGps = ESTADO_LED_DESLIGADO_GPS;
        }
        
    }
    */
    return 0;
}

int ehPedestreValidoParaFeira (unsigned char *Epc){
    if ((*Epc != 0x10) && (*Epc != 0x20))
        return 0;
    Epc = Epc + 1;
    if (*Epc != 0x00)
        return 0;
    Epc = Epc + 1;
    if ((*Epc >= 0x01) && (*Epc <= 0x03))
        return 1;
    return 0;
}


int operadorValido(void){
    if (MeuOperador.Epc[0] == 0){
        return 0;
    }
    return 1;
}
int ehOEpcDoMeuOperador (unsigned char * Epc){
    if (memcmp (MeuOperador.Epc, Epc, TAMANHO_EPC_PARA_EMPILHADEIRA) == 0)return 1;
    return 0;
}

int sePedestreLidoForOMeuOPeradorEliminoDaLidaDePedestre(void){
    return 0;
}

int sePedestreForOperadorEliminarDaListaDePedestresLidos(void){
  int InteradorDaListaDePedestres;
  int IntetadorDaListaDeOperadores;
  int Resultado;
  int PedestresLidos;
  PedestresLidos = 0;
  
  for(InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
    for(IntetadorDaListaDeOperadores = 0;IntetadorDaListaDeOperadores < QUANTIA_MAXIMA_DE_OPERADORES_NO_SISTEMA;IntetadorDaListaDeOperadores = IntetadorDaListaDeOperadores + 1){
      Resultado = memcmp(ListaDePedestres[InteradorDaListaDePedestres].Epc, ListaDeOperadores[IntetadorDaListaDeOperadores].Epc, TAMANHO_EPC_PARA_EMPILHADEIRA);
      if (ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0){
	    if (Resultado == 0){
            removerPedestre(InteradorDaListaDePedestres);
	    }
	  }
    }
  }
  return 0;
}

int oPedestreEhUmaZonaDeExclusao(unsigned char *Epc){
	int Contador;
	Contador = 0;
	if (*Epc == 1){
		Contador = Contador + 1;
	}
	Epc = Epc + 1;
	if (*Epc == 0){
		Contador = Contador + 1;
	}
	Epc = Epc + 1;
	if (*Epc == 0){
		Contador = Contador + 1;
	}
	if (Contador == 3)	{
		return 1;
	}
	return 0;
}

int setaNovoValorDeDbmDaZOnaDeExclusao (int Valor, int Antena){
    DbmDaZonaDeExclusao[Antena] = Valor;
    /*
	if (DbmDaZonaDeExclusao[Antena] < Valor){
		DbmDaZonaDeExclusao[Antena] = Valor;
	}
    */
	//printf("Novo valor para a ZE = %d\n", DbmDaZonaDeExclusao);
    return 0;
}

int retornaADirecaoDaZonaDeExclusaoEmFuncaoDaAntena(int Antena){
    if (Antena == 1 || Antena == 2){
        return FRENTE;
    } else {
        return TRAS;
    }
}

void filtaTagsPorRSSI(){
    int i=0;
    char limpaPedestre=0;
    
    for(i=0;i<LIMITE_DE_PEDESTRES;i++){
        switch(ListaDePedestres[i].Antena){
            case 1:
                if(ListaDePedestres[i].Dbm < rssiMinAntena1){
                    limpaPedestre = 1;
                }
                break;
            case 2:
                if(ListaDePedestres[i].Dbm < rssiMinAntena2){
                    limpaPedestre = 1;
                }
                break;
            case 3:
                if(ListaDePedestres[i].Dbm < rssiMinAntena3){
                    limpaPedestre = 1;
                }
                break;
            case 4: 
                if(ListaDePedestres[i].Dbm < rssiMinAntena4){
                    limpaPedestre = 1;
                }
                break;
            case 5:
                if(ListaDePedestres[i].Dbm < rssiMinAntena5){
                    limpaPedestre = 1;
                }
                break;
            case 6: 
                if(ListaDePedestres[i].Dbm < rssiMinAntena6){
                    limpaPedestre = 1;
                }
                break;
            case 7: 
                if(ListaDePedestres[i].Dbm < rssiMinAntena7){
                    limpaPedestre = 1;
                }
                break;
            case 8: 
                if(ListaDePedestres[i].Dbm < rssiMinAntena8){
                    limpaPedestre = 1;
                }
                break;
            
        }
        if(limpaPedestre){
            limpaPedestre=0;
            ListaDePedestres[i].Epc[0] = 0;
            ListaDePedestres[i].Epc[0] = 0;
            ListaDePedestres[i].Epc[0] = 0;
            ListaDePedestres[i].Dbm = 0;
            ListaDePedestres[i].Antena = 0;        
        }
    }
}

void sePedestreForLidoComZonaDeExclusaoProximaEliminaloDaLista(int Antena){
	int InteradorDaListaDePedestres;
    int SelecaoDaZonaDeExclusao;
    
    SelecaoDaZonaDeExclusao = retornaADirecaoDaZonaDeExclusaoEmFuncaoDaAntena(Antena);    

	for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
		if ((ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0) && (ContadorDeTempoDeValidadeDaZonaDeExclusao > 0)){
			//if (DbmDaZonaDeExclusao[Antena] >= ListaDePedestres[InteradorDaListaDePedestres].Dbm){
            if (DbmDaZonaDeExclusao[SelecaoDaZonaDeExclusao] >= ListaDePedestres[InteradorDaListaDePedestres].Dbm){
				//printf("Um elemento eliminado por zona de exclusao! Dmb da ZE = %d e da Tag = %d\n", DbmDaZonaDeExclusao,  ListaDePedestres[InteradorDaListaDePedestres].Dbm);
				//memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, 3);
                ListaDePedestres[InteradorDaListaDePedestres].Epc[0] = 0;
                ListaDePedestres[InteradorDaListaDePedestres].Epc[1] = 0;
                ListaDePedestres[InteradorDaListaDePedestres].Epc[2] = 0;
				ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
				ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
			}
		}
	}

    
    /*
	for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
		if (ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0){
			if (DbmDaZonaDeExclusao > ListaDePedestres[InteradorDaListaDePedestres].Dbm){
				//printf("Um elemento eliminado por zona de exclusao! Dmb da ZE = %d e da Tag = %d\n", DbmDaZonaDeExclusao,  ListaDePedestres[InteradorDaListaDePedestres].Dbm);
				memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, 1);
				ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
				ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
			}
		}
	}
    */
}

void sePedestreEstiverNaListaDeOperadoresEliminaDaLista(void){
    int InteradorDaListaDePedestres;
    int InteradorDaListaDeOperadores;
    int Contador;
    char Resultado;
    
    for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
        if (ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0){
            for (InteradorDaListaDeOperadores = 0;InteradorDaListaDeOperadores < LIMITE_DE_PEDESTRES;InteradorDaListaDeOperadores = InteradorDaListaDeOperadores + 1){
                Resultado = 0;
                if (ListaDeOperadores[InteradorDaListaDeOperadores].Epc[0] != 0){
                    for(Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
                        if (ListaDePedestres[InteradorDaListaDePedestres].Epc[Contador] != ListaDeOperadores[InteradorDaListaDeOperadores].Epc[Contador]){
                            Resultado = Resultado | 1;
                        }
                    }
                    if(Resultado == 0){
                        memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
                        //ListaDePedestres[InteradorDaListaDePedestres].Epc[0] = 0;
                        ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
                        ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
                    }
                }
            }
        }
    }   
}

void SePedestreEstiverNaTabelaDePortalDeExclusaoEliminaloDaLista (void){
   
    /*
    int InteradorDaListaDePedestres;
    int InteradorDaListaDoPortalDeExclusao;
    int Contador;
    char Resultado;
    for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
        if (ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0){
            //for (InteradorDaListaDoPortalDeExclusao = 0;InteradorDaListaDoPortalDeExclusao < LIMITE_DE_PEDESTRES;InteradorDaListaDoPortalDeExclusao = InteradorDaListaDoPortalDeExclusao + 1){
            for (InteradorDaListaDoPortalDeExclusao = 0;InteradorDaListaDoPortalDeExclusao < QUANTIA_DE_ELEMENTOS;InteradorDaListaDoPortalDeExclusao = InteradorDaListaDoPortalDeExclusao + 1){
                Resultado = 0;
                if (TabelaDeExclusao.Elementos[InteradorDaListaDoPortalDeExclusao][0] != 0){
                    //if (TabelaDeExclusao.Excluido == ENTROU_NA_AREA_SEGURA){
                    for(Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
                        if (ListaDePedestres[InteradorDaListaDePedestres].Epc[Contador] != TabelaDeExclusao.Elementos[InteradorDaListaDoPortalDeExclusao][Contador]){
                            Resultado = Resultado | 1;
                        }
                    }
                    //if (memcmp(ListaDePedestres[InteradorDaListaDePedestres].Epc, ListaDePedestresNoPortalDeExclusao[InteradorDaListaDoPortalDeExclusao].Epc,  TAMANHO_EPC_PARA_EMPILHADEIRA) == 0){
                    if(Resultado == 0){
                        if (TabelaDeExclusao.Excluido[InteradorDaListaDoPortalDeExclusao] == ENTROU_NA_AREA_SEGURA){
                            memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
                            //ListaDePedestres[InteradorDaListaDePedestres].Epc[0] = 0;
                            ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
                            ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
                        }
                    }
                    //}
                }
            }
        }
    }*/
    int i=0;
    EPC tempEpc;
    
    bloqueiaMaquinaDeEstados_TabelaDeExclusao();
            
    for(i=0;i<LIMITE_DE_PEDESTRES;i++){
        if (ListaDePedestres[i].Epc[0] != 0){
            tempEpc.byte4 = ListaDePedestres[i].Epc[0];
            tempEpc.byte3 = ListaDePedestres[i].Epc[1];
            tempEpc.byte2 = ListaDePedestres[i].Epc[2];
            tempEpc.byte1 = 0x00;
            
            if(buscarRegistroNaTabelaDeExclusao(tempEpc)){
                ListaDePedestres[i].Epc[0] = 0;
                ListaDePedestres[i].Epc[1] = 0;
                ListaDePedestres[i].Epc[2] = 0;
                ListaDePedestres[i].Dbm = 0;
                ListaDePedestres[i].Antena = 0;
            }
        }
    }
    
    habilitaMaquinaDeEstados_TabelaDeExclusao();
}

void SePedestreForOMeuOperadorEliminoDaLista (void){
    int InteradorDaListaDePedestres;
    //int Contador;
    //char Resultado;
    for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
        if (ListaDePedestres[InteradorDaListaDePedestres].Epc[0] != 0){
            if (memcmp(&ListaDePedestres[InteradorDaListaDePedestres].Epc[0], &MeuOperador.Epc[0], TAMANHO_EPC_PARA_EMPILHADEIRA) == 0){
                memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, 1);
                ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
                ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
            }
                
            /*
            for(Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
                if (ListaDePedestres[InteradorDaListaDePedestres].Epc[Contador] != MeuOperador.Epc[Contador]){
                    Resultado = Resultado | 1;
                }
            }
            //if (memcmp(ListaDePedestres[InteradorDaListaDePedestres].Epc, ListaDePedestresNoPortalDeExclusao[InteradorDaListaDoPortalDeExclusao].Epc,  TAMANHO_EPC_PARA_EMPILHADEIRA) == 0){
            if(Resultado == 0){
                memset(&ListaDePedestres[InteradorDaListaDePedestres], 0, 1);
                //ListaDePedestres[InteradorDaListaDePedestres].Epc[0] = 0;
                ListaDePedestres[InteradorDaListaDePedestres].Dbm = 0;
                ListaDePedestres[InteradorDaListaDePedestres].Antena = 0;
            }
            */
        }
    }
}


void apagarEsseEpcDaListaDePedestres (char *Etiqueta){
    int InteradorDaListaDePedestres;
    int Contador;
    char Epc[TAMANHO_EPC_PARA_EMPILHADEIRA];
    
    
    for (Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
        Epc[Contador] = *Etiqueta;
        Etiqueta = Etiqueta + 1;
    }
    
    for (InteradorDaListaDePedestres = 0;InteradorDaListaDePedestres < LIMITE_DE_PEDESTRES;InteradorDaListaDePedestres = InteradorDaListaDePedestres + 1){
        for (Contador = 0;Contador < TAMANHO_EPC_PARA_EMPILHADEIRA;Contador = Contador + 1){
            if (ListaDePedestres[InteradorDaListaDePedestres].Epc[Contador] != Epc[Contador]) break;
            if (Contador == (TAMANHO_EPC_PARA_EMPILHADEIRA - 1)){
                memset(ListaDePedestres[InteradorDaListaDePedestres].Epc, 0, TAMANHO_EPC_PARA_EMPILHADEIRA);
            }
        }
    }    
}



/*
int OperadorEstaNaTabelaDeExclusao (char *Operador){
    int InteradorDaListaDoPortalDeExclusao;
    for (InteradorDaListaDoPortalDeExclusao = 0;InteradorDaListaDoPortalDeExclusao 
            < LIMITE_DE_PEDESTRES;InteradorDaListaDoPortalDeExclusao = InteradorDaListaDoPortalDeExclusao + 1){
        if (memcmp(Operador, ListaDePedestresNoPortalDeExclusao[InteradorDaListaDoPortalDeExclusao].Epc,  TAMANHO_EPC_PARA_EMPILHADEIRA) == 0){
            return SIM;
        }
    }
    return NAO;
}
*/

void pausaNaOperacaoPorDeteccaoDePedestre(void){
    ContadorDePausaEmCasoDePossivelAcidente = TEMPO_DE_PAUSA_EM_POSSIVEL_ACIDENTE;
    while(ContadorDePausaEmCasoDePossivelAcidente != 0){
        delay_ms(1000);
    }
}

void gerarRegistroDePossivelAcidente(void){
    //enviaTextoDeLogDaOperacao("Empilhadeira foi bloqueada\n");
}

void geraRegistroDeOperadorEntrouNaEmpilhadeira(void){
    //enviaTextoDeLogDaOperacao("Operador entrou na maquina\n");
}

void geraRegistroDeOperadorSaiuDaEmpilhadeira(void){
    //enviaTextoDeLogDaOperacao("Operadro saiu da maquina\n");
}

void enviaMensagemPor485 (char *Mensagem){
    int Contador;
    liga_led_zig();
    _LATG13 = 1;
    for(Contador = 0;*Mensagem != 0;Contador = Contador + 1){
        U1TXREG = *Mensagem;
        while( (!U1STAbits.TRMT ) );
        Mensagem = Mensagem + 1;
    }
    _LATG13 = 0;
    desliga_led_zig();    
}

int ehEpcDeOperador(char * Epc){
    char Resultado;
    Resultado = *Epc & 0xF0;
    if (Resultado == 0x50)
        return 1;
    return 0;
}

int ehEpcDeDepestre(char * Epc){
    char Resultado;
    Resultado = *Epc & 0xF0;
    if (Resultado == 0x30)
        return 1;
    return 0;
}

int ehOEpcDessaEmpilhadeira(char * Epc){
    char Rascunho;
    Epc = Epc + 1;
    Rascunho = *Epc;
    Epc = Epc + 1;
    if (EpcTagEmpilhadeira[0] == Rascunho && EpcTagEmpilhadeira[1] == *Epc)
        return 1;
    else
        return 0;
}

int ehEpcDeEmpilhadeira(char * Epc){
    char Resultado;
    Resultado = *Epc & 0xF0;
    if (Resultado == 0x60){
        if (ehOEpcDessaEmpilhadeira(Epc)) return 0;
        else return 1;
    }
    return 0;
}


int ehEpcDeOeradorParaFeira(unsigned char * Epc){
    char Resultado;
    Resultado = *Epc & 0xF0;
    if (Resultado == 0x20)
        return 1;
    return 0;
}


int ehEpcDeZonaDeExclusao(unsigned char * Epc){
    char Resultado;
    Resultado = *Epc | 0x00;
    Epc = Epc + 1;
    Resultado = *Epc | 0x00;
    Epc = Epc + 1;
    Resultado = *Epc | 0x00;
    
    if (Resultado != 0){
        return 0;
    }
    
    Epc = Epc - 2;
    Epc = Epc + 9;//Conferir se eh 12 bytes mesmo o tamanho do Epc
    
    if (*Epc != 0) return 0;
    Epc = Epc + 1;
    if (*Epc != 0) return 0;
    Epc = Epc + 1;
    if (*Epc != 1) return 0;
    return 1;
}

void inverteBytesParaZonaDeExclusao (unsigned char *Epc){
    unsigned char Rascunho[3];
    Epc = Epc + 9;
    Rascunho[0] = *Epc;
    Epc = Epc + 1;
    Rascunho[1] = *Epc;
    Epc = Epc + 1;
    Rascunho[2] = *Epc;
    
    Epc = Epc - 11;
    
    *Epc = Rascunho[0];
    Epc = Epc + 1;
    *Epc = Rascunho[1];
    Epc = Epc + 1;
    *Epc = Rascunho[2];    
    
}

int ehEpcDePedestreParaFeira(unsigned char * Epc){
    char Resultado;
    Resultado = *Epc & 0xF0;
    if (Resultado == 0x10)
        return 1;
    return 0;
}

void obterNomeDaMaquinaDeTag(void){
    //TAMANHO_DO_NOME_DA_EMPILHADEIRA
    //NomeDaEmpilhadeira[TAMANHO_DO_NOME_DA_EMPILHADEIRA];
    memset(NomeDaEmpilhadeira, 0, TAMANHO_DO_NOME_DA_EMPILHADEIRA);
    
}

int ehUmaTagDeReducaoDeVelocidade(unsigned char *Epc){
    if (*Epc == 0x60){
        Epc = Epc + 1;
        if (*Epc == 0x00){
            Epc = Epc + 1;
            if (*Epc == 0x00){
                return 1;
            }
        }
    }
    return 0;
}

int ehUmaTagDeAceleracaoDeVelocidade(unsigned char *Epc){
    if (*Epc == 0x60){
        Epc = Epc + 1;
        if (*Epc == 0x00){
            Epc = Epc + 1;
            if (*Epc == 0x01){
                return 1;
            }
        }
    }
    return 0;
}

void colocaAEmpilhadeiraEmVelocidadeNormal(void){
    desliga_rele3();
}

void colocaAEmpilhadeiraEmVelocidadeReduzida(void){
    liga_rele3();
}

void salvaEstadoDaVelocidadeDaEmpilhadeira(int Nivel){
    mem_escreve_24LC256(ENDERECO_DA_VELOCIDADE_JUIZ_DE_FORA, Nivel);
}

int retornaEstadoDaVelocidadeDaEmpilhadeira(void){
    unsigned char Nivel;
    mem_leDados_24LC256(ENDERECO_DA_VELOCIDADE_JUIZ_DE_FORA, &Nivel, 1);
    return Nivel;
}

void iniciaVelocidadeDeJuizDeFora(void){
    int Resultado;
    
    Resultado = retornaEstadoDaVelocidadeDaEmpilhadeira();
    if (Resultado){
        colocaAEmpilhadeiraEmVelocidadeReduzida();
    } else {
        colocaAEmpilhadeiraEmVelocidadeNormal();
    }
    
}
int trataReducaoDeVelocidadeDeJuizDeFora(unsigned char *Epc){
    if (ehUmaTagDeReducaoDeVelocidade(Epc)){
        colocaAEmpilhadeiraEmVelocidadeReduzida();
        salvaEstadoDaVelocidadeDaEmpilhadeira(1);
        return 1;
    }



    if (ehUmaTagDeAceleracaoDeVelocidade(Epc)){
        colocaAEmpilhadeiraEmVelocidadeNormal();
        salvaEstadoDaVelocidadeDaEmpilhadeira(0);
        return 1;
    }
    
    return 0;
}


void trataRecepcaoDeTabelaDeExclusaoEmCodigoCorrente(void){
    //#define TAMANHO_BUFFER_REPOSTA 128
    u8 Resposta[UART_RX_BUFFER_SIZE];
    //u8 Resposta[256];
    u16 Tamanho;

    Tamanho = uartRxNumBytesAvailable();
    //if (Tamanho != 0){
    while (Tamanho != 0){
        uartRxNBytes(Resposta, &Tamanho);

        //uart4Tx('=');
        //uart4Tx((u8)Tamanho);
        //uart4Tx('=');
        
        int Contador;
        //for (Contador = Tamanho;Contador > -1;Contador = Contador - 1){
        for (Contador = 0;Contador < Tamanho;Contador = Contador + 1){
            //ResetaTempoParaExpirarOBufferDoZigBee();
            //TrataRecepcaoDeDadosDeZigBee(Resposta[Contador]);
            //uart4Tx(Resposta[Contador]);
        }
        Tamanho = uartRxNumBytesAvailable();
    }
}

/*
void TesteParaLeituraMaximaNaAntena1(void){
    int Contador;
    int Resultado = 0;
    int Antena;
    Contador = 0;
    comecaInvetorio();
    
    if (_RG6){
        tunerInit(&mainTuner);
    } else {
        tunerInitTraseiraJuizDeFora(&mainTuner);
    }    
    
    tunerInit(&mainTuner);
    //callAutoTuner
    
    //as3993SetSensitivity(125);

    //sel_led(1, 1);
    //sel_antena(1);
    //while(1){

   
    
    while(1){
        for(Antena = 1;Antena < 3;Antena = Antena + 1){
            sel_led(Antena, 1);
            sel_antena(Antena);

            asm("CLRWDT");
            if (inventorioSimplificado()){
                for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
                    if (tags_[Contador].epc[0] =! 0){
                        Resultado = 50;
                        memset(tags_[Contador].epc, 0, 12);
                    }
                }
                //Contador = 50;
            } else {
                //desliga_buzzer();
            }
            if (Resultado){
                liga_buzzer();
                Resultado = Resultado - 1;
            } else {
                desliga_buzzer();
            }


            sel_led(Antena, 0);
        }

    }        
            
    TerminaInvetorio();
}
*/

void bloqueiaEmpilhadeira(int TempoDeBloqueio){
    acionaFitaDeLedsDaEmpilhadeira();
    //liga_rele1();
    //liga_rele3();
    //desliga_rele1();
    //desliga_rele3();
    desabilitaEmpilhadeira();
    delay_ms(TempoDeBloqueio);
}

void liberaEmpilhadeira (void){
    desacionaFitaDeLedsDaEmpilhadeira();
    
    //desliga_rele1();
    //desliga_rele3();
    //liga_rele1();
    
    //liga_rele1();
    //liga_rele3();
    habilitarEmpilhadeira();
}

int filtraOsPedestresObtidos(void){
    int QuantidadeDePedestresResultante;
//    char Epc[3];
    //sePedestreForOperadorEliminarDaListaDePedestresLidos();
#ifndef ARCELOR_JUIZ_DE_FORA_EMPILHADEIRA_TRADMAQ_3_5_TONS
    sePedestreEstiverNaListaDeOperadoresEliminaDaLista();
#endif
    filtaTagsPorRSSI();
    
    sePedestreForLidoComZonaDeExclusaoProximaEliminaloDaLista(AntenaASerLida);
    //sePedestreForLidoComZonaDeExclusaoProximaEliminaloDaLista();
#ifdef TABELA_DE_EXCLUSAO
    SePedestreEstiverNaTabelaDePortalDeExclusaoEliminaloDaLista();
    SePedestreForOMeuOperadorEliminoDaLista();
#endif 
    
    //Epc[0] = 0x30;
    //Epc[1] = 0x19;
    //Epc[2] = 0x95;
    //apagarEsseEpcDaListaDePedestres(Epc);
    QuantidadeDePedestresResultante = pedestresPresentes();
    
    return QuantidadeDePedestresResultante;
}

int operadorSentado(void){
#ifdef BARBACENA
    if (OperadorPresente == SIM){
        return SIM;
    }
#endif
    
    OperadorPresente = operadorPresente();
    if ((OperadorPresente == SIM) && (cintoColocado() == SIM)){
        return SIM;
    }
    
    return NAO;
}

/*
void sintoniaAntena(int Direcao){
    static int sintonizadoParaADirecao = FRENTE;
    
    if (sintonizadoParaADirecao != Direcao){
        if (Direcao == FRENTE){
            //enviaTextoDeLogDaOperacao("Maquina indo para frente\n");
            tunerInit(&mainTuner);
        } else {
            //enviaTextoDeLogDaOperacao("Maquina indo para tras\n");
            tunerInitTraseiraJuizDeFora(&mainTuner);
        }
        sintonizadoParaADirecao = Direcao;
    }
}
 */

int setaAntenaASerLida(int DirecaoDaEmpilhadeira){
    static int AntenaASerLida = 1;
    AntenaASerLida = setarAntenaEmFuncaoDaDirecao(DirecaoDaEmpilhadeira, AntenaASerLida);
    //RepeticaoDeLeitura = setaONumeroDeRepeticaoDeLeiturasEmFuncaoDaAntena(AntenaASerLida);
    sel_led(AntenaASerLida, 1);
    sel_antena(AntenaASerLida);
    return AntenaASerLida;
}


void ajustaSintoniaEmFuncaoDaDirecao(int Direcao){
    
    if (Direcao == FRENTE){
        if(AntenaASerLida==1){
            tunerInit_A1(&mainTuner);                
        }
        else{            
            tunerInit_A2(&mainTuner);
        }       
    } 
    else {
        tunerInit_A3(&mainTuner);
    }
}

void enviarOMeuOperadorParaAsOutrosEmpilhadeiras (void){
    char Rascunho[30];
    (void)sprintf(Rascunho, "Operador=%c%c%c%c-%c%c%c\n", num_serie[0], num_serie[1], num_serie[2], num_serie[3], MeuOperador.Epc[0], MeuOperador.Epc[1], MeuOperador.Epc[2]);
//    EnviaStringPara485(Rascunho);
}

int ehEtiquetaDeBatismo(char *Epc){
    if (*Epc == 0x60){
        return SIM;
    } else {
        return NAO;
    }
}

int batizadoComEtiqueta(void){
    int Contador;
    
    num_serie[0] = '1';
    num_serie[1] = '3';
    num_serie[2] = '1';
    num_serie[3] = '0';
    
    return SIM;
    
    sel_led(0,0);//Apaga leds
    setarAntenaASerLida(ANTENA_PARA_LER_O_OPERADOR);
    comecaInvetorio();
    
    sel_led(ANTENA_PARA_LER_O_OPERADOR,1);
    limpaBufferInternoDasLeituras(MAXTAG);
    if (inventorioSimplificado()){        

        sel_led(ANTENA_PARA_LER_O_OPERADOR,0);//Apaga leds
        sel_led(0,0);//Apaga leds
        desliga_led_tag();
        
        for (Contador = 0;Contador < MAXTAG;Contador = Contador + 1){
            if (ehEtiquetaDeBatismo((char *)tags_[Contador].epc) == SIM){
                liga_led_tag();
                memset(num_serie, 0, 20);
                (void)sprintf(num_serie, "%d%d%d%d", (tags_[Contador].epc[1] >> 4),
                        (tags_[Contador].epc[1] & 0x0F),
                        (tags_[Contador].epc[2] >> 4),
                        (tags_[Contador].epc[2]) & 0xF);
                limpaBufferInternoDasLeituras(MAXTAG);
                desliga_led_tag();
                return SIM;
            }
        }
    };
    sel_led(0,0);//Apaga leds
    return NAO;
    
}

void reiniciaTempoParaEnviarOMeuOperador (void){
    ContagemParaEnviarOMeuOperadorParaAsOutrasEmpilhadeiras = TEMPO_PARA_ENVIAR_O_OPERADOR_PARA_OUTRAS_MAQUINAS;    
}

int mudouADirecaoDaMaquina(void){
    int Direcao;
    Direcao = obterDirecaoDaMovimentacaoDaEmpilhadeira();
    if (DirecaoDaEmpilhadeira != Direcao){
        return 1;
    }
    return 0;
}

void trataComandoDaEmpilhadeira (void){
    if (ComandoObtidoParaAEmpilhadeira != 0){
        trataRecepcaoDeDadosParaAvalicaoDeEmpilhadeira(ComandoParaEmpilhadeira);
        memset(ComandoParaEmpilhadeira, 0, TAMANHO_BUFFER_DE_COMANDO_PARA_EMPILHADEIRA);
        ComandoObtidoParaAEmpilhadeira = 0;
    }
}

void bloqueiaOperacaoDoLeitorParaAMaquinaLind(void){
    TempoDeBloqueioParaMaquinaLind = 3000;   
        
    while(TempoDeBloqueioParaMaquinaLind != 0){
    } 
    
    liberaEmpilhadeira();    
    desacionaFitaDeLedsDaEmpilhadeira();
    desacionaSireneDaEmpilhadeira(); 
    __delay_ms(2000); // Delay para permitir que o operador tenha tempo de dar a ré e se movimentar, por exemplo.
                      // Sem isso, a detecção das antenas frontais impede que o operador acelere ou dê a ré.
}

unsigned char retonaComByteDeDoisCaracteresNumericos(char X, char Y){
    unsigned char Saida;
    unsigned char Rascunho;
    Rascunho = X - '0';
    Saida = Rascunho << 4;
    Rascunho = Y - '0';
    Saida = Saida | Rascunho;
    return Saida;
}

void ajustaFrequenciaEmFuncaoDaDirecao(int Direcao){
    static int FrequenciaAjustada = 0;
    extern Freq Frequencies;
    int Frequencia=0;
    int FrequenciaTraseira=0;
    unsigned long rascunho=0;
        
    if (Direcao == FRENTE){
        if (FrequenciaAjustada != Direcao){
            rascunho = Frequencia;
            rascunho = rascunho + 900;
            rascunho = rascunho * 1000;
            rascunho = 915000;
            rascunho = frequenciaDeOperacao*1000 + 900000;
            Frequencies.freq[0] = rascunho;
            Frequencies.freq[1] = rascunho;
            
            Frequencies.numFreqs = 1;
            TerminaInvetorio();
            comecaInvetorio();

            FrequenciaAjustada = Direcao;
        }
        
    } else {
        if (FrequenciaAjustada != Direcao){
            rascunho = FrequenciaTraseira;
            TerminaInvetorio();          
            comecaInvetorio();
            
            FrequenciaAjustada = Direcao;
        }
    }
}

void logicaDeEmpilhadeiraV2 (void){
    eventoParadaEmpilhadeira novoEventoDeParada;
    EPC epcLido;
    
    //variaveis do loop para encontrar pedestres
    int iPedestres=0;
    //////////////////////////////////////////////
    
//    char mensagem[1000];    
    int QuantiaDePedestresLidos;
    int Direcao;   
    int SintoniaParaOOperadorFeita; 
    
    // FIXEI ESSE VALOR POIS A ARCELORMITTAL NAO USA MAIS DE 1 AREA ATÉ 03/2020
    areaDoVeiculo.byte4 = 0x40;
    areaDoVeiculo.byte3 = 0x00;
    areaDoVeiculo.byte2 = 0x01;
    areaDoVeiculo.byte1 = 0x00;  
    
    //tunerInit(&mainTuner);   
    
    comecaInvetorio();
    
    desabilitaEmpilhadeira();
    
    while(batizadoComEtiqueta() == NAO);

    EpcTagEmpilhadeira[0] = retonaComByteDeDoisCaracteresNumericos(idDoLeitor[0], idDoLeitor[1]);
    EpcTagEmpilhadeira[1] = retonaComByteDeDoisCaracteresNumericos(idDoLeitor[2], idDoLeitor[3]);    
    
    while(1){    
        
        inicializaMaquinaDeEstados_DataHora();
        habilitaMaquinaDeEstados_DataHora();        
        inicializaMaquinaDeEstados_TabelaDeExclusao();
        habilitaMaquinaDeEstados_TabelaDeExclusao();
                
        while(operadorSentado() == NAO){
            bloqueiaEmpilhadeira(50);
            removerOMeuOperador();
          
            operacoesParaRtcEmCodigoCorrente();
            
            if (SintoniaParaOOperadorFeita == NAO){
                SintoniaParaOOperadorFeita = SIM;
                JaSintonizado = 0;
            }
        }
        
        SintoniaParaOOperadorFeita = NAO;
        
        liberaEmpilhadeira();
        
        operacoesParaRtcEmCodigoCorrente();
        Direcao = obterDirecaoDaMovimentacaoDaEmpilhadeira();
        AntenaASerLida = setaAntenaASerLida(Direcao);
       
        ajustaFrequenciaEmFuncaoDaDirecao(Direcao);
        ajustaSintoniaEmFuncaoDaDirecao(Direcao);
        desliga_led_tag();
         
        (void)setaONumeroDeRepeticaoDeLeiturasEmFuncaoDaAntena(AntenaASerLida);
        
        while(TempoParaTrocarAntenaNaVarreduraFrontal > 0){
            
            operacoesParaRtcEmCodigoCorrente();
            
            QuantiaDePedestresLidos = obterPedestres(AntenaASerLida);
            
            if (QuantiaDePedestresLidos > 0){
                
                
                QuantiaDePedestresLidos = filtraOsPedestresObtidos();
                
                if (QuantiaDePedestresLidos > 0){
                    
                    for(iPedestres=0;iPedestres<LIMITE_DE_PEDESTRES;iPedestres++){
                        if(ListaDePedestres[iPedestres].Epc[0]!=0){
                            epcLido.byte4 = ListaDePedestres[iPedestres].Epc[0];
                            epcLido.byte3 = ListaDePedestres[iPedestres].Epc[1];
                            epcLido.byte2 = ListaDePedestres[iPedestres].Epc[2];
                            epcLido.byte1 = 0x00;
                            
                            /*sprintf(mensagem,"\n\rAntena a ser lida: %02d\
                            \n\rObjeto pedestre: \
                            \n\rEPC:%02x%02x%02x00\
                            \n\rPotência: %02d Dbm\
                            \n\rAntena: %02d\n",
                           AntenaASerLida,
                           ListaDePedestres[iPedestres].Epc[0],ListaDePedestres[iPedestres].Epc[1],ListaDePedestres[iPedestres].Epc[2],
                           ListaDePedestres[iPedestres].Dbm,
                           ListaDePedestres[iPedestres].Antena);
                           escreverMensagemUSB(mensagem);*/
                        }
                    }                                        
                    
                    desabilitaEmpilhadeira();//Bloqueio inicial para melhorar a percepcao do operador
                    DirecaoDaEmpilhadeira = Direcao;
                    acionaFitaDeLedsDaEmpilhadeira();
                    acionaSireneDaEmpilhadeira ();

                    novoEventoDeParada.EPC_area[0] = ((areaDoVeiculo.byte4 >> 4) + '0');
                    novoEventoDeParada.EPC_area[1] = ((areaDoVeiculo.byte4 & 0x0F) + '0');
                    novoEventoDeParada.EPC_area[2] = ((areaDoVeiculo.byte3 >> 4) + '0');
                    novoEventoDeParada.EPC_area[3] = ((areaDoVeiculo.byte3 & 0x0F) + '0');
                    novoEventoDeParada.EPC_area[4] = ((areaDoVeiculo.byte2 >> 4) + '0');
                    novoEventoDeParada.EPC_area[5] = ((areaDoVeiculo.byte2 & 0x0F) + '0');
                    novoEventoDeParada.EPC_area[6] = ((areaDoVeiculo.byte1 >> 4) + '0');
                    novoEventoDeParada.EPC_area[7] = ((areaDoVeiculo.byte1 & 0x0F) + '0');
                            
                    novoEventoDeParada.EPC_operador[0] = (((unsigned char)MeuOperador.Epc[0] >> 4) + '0');
                    novoEventoDeParada.EPC_operador[1] = (((unsigned char)MeuOperador.Epc[0] & 0x0F) + '0');
                    novoEventoDeParada.EPC_operador[2] = (((unsigned char)MeuOperador.Epc[1] >> 4) + '0');
                    novoEventoDeParada.EPC_operador[3] = (((unsigned char)MeuOperador.Epc[1] & 0x0F) + '0');
                    novoEventoDeParada.EPC_operador[4] = (((unsigned char)MeuOperador.Epc[2] >> 4) + '0');
                    novoEventoDeParada.EPC_operador[5] = (((unsigned char)MeuOperador.Epc[2] & 0x0F) + '0');
                    novoEventoDeParada.EPC_operador[6] = '0';
                    novoEventoDeParada.EPC_operador[7] = '0';

                    novoEventoDeParada.EPC_pedestre[0] = (((unsigned char)epcLido.byte4 >> 4) + '0');
                    novoEventoDeParada.EPC_pedestre[1] = (((unsigned char)epcLido.byte4 & 0x0F) + '0');
                    novoEventoDeParada.EPC_pedestre[2] = (((unsigned char)epcLido.byte3 >> 4) + '0');
                    novoEventoDeParada.EPC_pedestre[3] = (((unsigned char)epcLido.byte3 & 0x0F) + '0');
                    novoEventoDeParada.EPC_pedestre[4] = (((unsigned char)epcLido.byte2 >> 4) + '0');
                    novoEventoDeParada.EPC_pedestre[5] = (((unsigned char)epcLido.byte2 & 0x0F) + '0');
                    novoEventoDeParada.EPC_pedestre[6] = (((unsigned char)epcLido.byte1 & 0x0F) + '0');
                    novoEventoDeParada.EPC_pedestre[7] = (((unsigned char)epcLido.byte1 & 0x0F) + '0');

                    dataHora = localtime (&Tempo); 

                    novoEventoDeParada.dia = dataHora->tm_mday;
                    novoEventoDeParada.mes = dataHora->tm_mon+1;
                    novoEventoDeParada.ano = dataHora->tm_year-100;

                    novoEventoDeParada.hora = dataHora->tm_hour;
                    novoEventoDeParada.minuto = dataHora->tm_min;
                    novoEventoDeParada.segundo = dataHora->tm_sec;


                    inicializaMaquinaDeEstados_EventosDeParada();                    

                    criarEventoDeParadaDeEmpilhadeira(&novoEventoDeParada);                    

                    habilitaMaquinaDeEstados_EventosDeParada();

                    bloqueiaOperacaoDoLeitorParaAMaquinaLind();

                    bloqueiaMaquinaDeEstados_EventosDeParada();                    
                }              
                removerTodosOsPedestre();
            }
        }        
    }
    TerminaInvetorio();
}
