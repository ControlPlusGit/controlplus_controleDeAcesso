#include "as3993_public.h"
#include "timer.h"
#include "i2c.h"
#include "as3993_public.h"
#include "uart_driver.h"
#include "as3993.h"
#include "platform.h"
#include "tuner.h"
#include <time.h>
#include "rtc.h"
#include "portal.h"
#include "perifericos.h"

extern u16 readerInitStatus;
extern Freq Frequencies;
extern void uart4Tx (u8 dado);

extern TunerConfiguration mainTuner;

TipoRegistroDeTagEmPortal RegistroDeTagEmPortal[MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL];

#define PARAMETRO_SETA_FREQUENCIA_ANATEL 0x55

char StringDeSaidaParaSerial[TAMANHO_MAXIMO_DE_STRING_DE_SAIDA];
char DadosParaASerial;
char SerialOcupada;
int ContadorDeTagMonitoradas;
int ContadorDeTagMovimentos;

int TagEmTratamento;
//int TagEmTratamentoEmTick;

int ModoDeOperacao;
int TempoParaInatividadeDeTagMonitorada;
char estadoSerialFrango;
unsigned char ComandoDaSerial;
unsigned char PrimeiroParametroDaSerial;
unsigned char SensibilidadeDaAntena;

int NumeroDeAntenasLidas;
int AtrasoParaDegradarLeitura;
int RepeticaoNaLeitura;
int ModoWieGand;
int Frequencia;
int PortaDePortalDeExclusao;
int InibeOperacaoEMesagensComOPC;
char IdDOLeitor[20] = "4035";

int PausaNasMensagensDeAvaliacao = 0;

int Beepar;
char Capacitores[3];

int ContadorParaEnviarTabelaDeTagsVisiveis;
int ContadorParaEnviarTabelaDeTagsInisiveis;
#define TEMPO_PARA_ENVIAR_TABELA 50//2


#define TEMPO_DO_ACIONAMENTO_DO_SINALEIRO 20//10
volatile int EstadoDoSinaleiro;
int ContadorDeTempoDoSinaleiro;

#define TEMPO_DE_SILENCIO_NA_485 20
int ContadorDeSilencioNa485;
int PodeEnviarTabelaDeInvisiveis;



void setaSensibilidade (unsigned char valor);


//struct EstruturaProtocolo EstruturaDeRecepcaoDoPC;
unsigned char CorpoDeComandoRecebidoDoPC[10];

int ContagemParaExpirarOsComandosDoPC;

#define TAMANHO_DA_LISTA 10
#define TAMANHO_DO_ITEM 10

unsigned char ListaDeSaida[TAMANHO_DA_LISTA][TAMANHO_DO_ITEM];
int ContadorDeReenvioDeDadosDaListaDeSaida;


void EnviaBytePara485 (unsigned char dado){
    /*
    //Para zigbee beta
    //while (_LATG13 != 0);
    _LATG13 = 1;
    
    U1TXREG = dado;
    while( (!U1STAbits.TRMT ) );
    _LATG13 = 0;
    */

    //Para zigbee normal
    //while (_LATG13 != 0);
    _LATG13 = 1;
    
    //U4TXREG = dado;
    //while( (!U4STAbits.TRMT ) );
    U1TXREG = dado;
    while( (!U1STAbits.TRMT ) );
    _LATG13 = 0;
    
    
}

void EnviaArrayDeBytesPara485 (char *dado, int tamanho){
    int contador;
    //while (_LATG13 != 0);
    _LATG13 = 1;
    
    for (contador = 0;contador < tamanho;contador = contador + 1){
        U1TXREG = *dado;
        //U4TXREG = *dado;
        dado = dado + 1;
        while( (!U1STAbits.TRMT ) );
        //while( (!U4STAbits.TRMT ) );
    }
    _LATG13 = 0;
}


void EnviaStringPara485 (char * dado){
    while (*dado != NULL){
        EnviaBytePara485(*dado);
        dado = dado + 1;
    }
}


void iniciaListaDeSaida(void){
    int Contador;
    
    for (Contador = 0;Contador < TAMANHO_DA_LISTA;Contador = Contador + 1){
        memset(ListaDeSaida[Contador], 0, TAMANHO_DO_ITEM);
    }
    ContadorDeReenvioDeDadosDaListaDeSaida = 0;
}

int procuraPosicaoLivreNaListaDeSaida(void){
    int Contador;
    for(Contador = 0;Contador < TAMANHO_DA_LISTA;Contador = Contador + 1){
        if (ListaDeSaida[Contador][0] == 0){
            return Contador;
        }
    }
    return -1;
}

int procuraPosicaoOcupadaNaListaDeSaida(void){
    int Contador;
    for(Contador = 0;Contador < TAMANHO_DA_LISTA;Contador = Contador + 1){
        if (ListaDeSaida[Contador][0] != 0){
            return Contador;
        }
    }
    return -1;
}


int adicionaItemNaListaDeSaida(unsigned char *Item){
    int Posicao;
    return 0;
    Posicao = procuraPosicaoLivreNaListaDeSaida();
    if (Posicao < 0)return -1;
    memcpy(ListaDeSaida[Posicao], Item, TAMANHO_DO_ITEM);
    ContadorDeReenvioDeDadosDaListaDeSaida = TEMPO_PARA_REENVIO_DA_LISTA_DE_SAIDA;
    return 0;
}

void realocaListaDeSaida(void){
    int Contador;
    for(Contador = 0;Contador < (TAMANHO_DA_LISTA - 1);Contador = Contador + 1){
        memcpy(ListaDeSaida[Contador], ListaDeSaida[Contador + 1], TAMANHO_DO_ITEM);
        memset(ListaDeSaida[Contador + 1], 0, TAMANHO_DO_ITEM);
    }
}

int recuperaERemoveItemDaListaDeSaida(unsigned char *Item){
    int Posicao;
    Posicao = procuraPosicaoOcupadaNaListaDeSaida();
    if (Posicao >= 0){
        memcpy(Item, ListaDeSaida[Posicao], TAMANHO_DO_ITEM);
        realocaListaDeSaida();
        return Posicao;
    }
    return -1;
}


int recuperaItemDaListaDeSaida(unsigned char *Item){
    int Posicao;
    Posicao = procuraPosicaoOcupadaNaListaDeSaida();
    if (Posicao >= 0){
        memcpy(Item, ListaDeSaida[Posicao], TAMANHO_DO_ITEM);
        return Posicao;
    }
    return -1;
}

void RemovePrimeiroItemDaListaDeSaida(void){
    //int Posicao;
    //Posicao = procuraPosicaoOcupadaNaListaDeSaida();
    realocaListaDeSaida();
}

void iniciaEstruturaDoProtocoloPC (void){
//    EstruturaDeRecepcaoDoPC.Comando = 0;
   // EstruturaDeRecepcaoDoPC.Estado = 0;
   // EstruturaDeRecepcaoDoPC.Tamanho = 0;
   // EstruturaDeRecepcaoDoPC.ContagemDoCorpo = 0;
    //ContadorParaExpirarOsDadosObtidosPorZigBee = 0;
}


int trataRecepcaoDoProcoloNoPortal (unsigned char Dado, int *Estado, unsigned char *Comando, unsigned int *Tamanho, unsigned char *Corpo,int *ContadorDoCorpo, unsigned int /*char*/ *CheckSum){
    /*unsigned char Rascunho;
    //zeraAContagemDeSilencioNoZigBee();
    ContagemParaExpirarOsComandosDoPC = 3;
	*CheckSum = *CheckSum + Dado;
	*Tamanho = *Tamanho - 1;
	switch (*Estado){
		case ESPERANDO_CABECA:
            //Rascunho = Dado & 0xF0;
            Rascunho = Dado;
            if (//(Rascunho == 0xF0) ||
                (Rascunho == 0xF5) ||
                (Rascunho == 0xF6) 
#ifdef INTERFACE_DE_AJUSTES
                ||
                (Rascunho == 0xF6) ||
                (Rascunho == 0xFE) ||
                (Rascunho == 0xFD) ||
                (Rascunho == 0x55) ||
                (Rascunho == 0xAA) ||
                (Rascunho == 0xAB) ||
                (Rascunho == 0x80) ||
                (Rascunho == 0x7F) ||
                (Rascunho == 0x89) ||
                (Rascunho == 0x8A) ||
                (Rascunho == 0x8B) ||
                (Rascunho == 0x8C) ||
                (Rascunho == 0x8D) ||
                (Rascunho == 0x8E) ||
                (Rascunho == 0x8F) ||
                (Rascunho == 0x90) ||
                (Rascunho == 0x91) ||
                (Rascunho == 0x92)
#endif
                    ){
                *Estado = ESPERANDO_TAMANHO_MSB;
                *CheckSum = Dado;
                //printf("Obtem cabeca = %02X\n", Dado);
                *Comando = Dado;
                *ContadorDoCorpo = 0;
            }
			break;
		case ESPERANDO_TAMANHO_MSB:
			*Estado = PEGANDO_O_CORPO;
			//printf("Obtem tamanho = %d\n", Dado);
			*Tamanho = Dado - 2;//2
            if (*Tamanho > 16){
                *Estado = ESPERANDO_CABECA;
                *Tamanho = 0;
            }
			break;
		case PEGANDO_O_CORPO:
			if (*Tamanho != 0){
				*Corpo = Dado;
				//printf("Obtem corpo = %c\n", Dado);
				*ContadorDoCorpo = *ContadorDoCorpo + 1;
			} else {
				*CheckSum = *CheckSum - Dado;
				//printf("CheckSum CG = %d e DD %d\n", *CheckSum, Dado);

				*Estado = ESPERANDO_CABECA;
                *CheckSum = *CheckSum & 0x00FF;
				if (Dado == *CheckSum){
                    *CheckSum = 0;
					return 1;
                    *CheckSum = 0;
				} else {
					return -1;
				}
			}
			break;
		default:
			*Estado = ESPERANDO_CABECA;
			break;
	}*/
	return 0;
}


void testeSinaleiro (void){
    while(1){
        liga_rele2(); // amarelo
        desliga_rele3();
        desliga_rele4();
        delay_ms(2000);
        liga_rele3(); //verde
        desliga_rele2();
        desliga_rele4();
        delay_ms(2000);
        liga_rele4(); //vermelho
        desliga_rele2();
        desliga_rele3();
        delay_ms(2000);
    }
}

void setaSinaleiro (int estado){
    if (EstadoDoSinaleiro != SINALEIRO_VERDE){
        ContadorDeTempoDoSinaleiro = TEMPO_DO_ACIONAMENTO_DO_SINALEIRO;
        if (EstadoDoSinaleiro != estado){
            EstadoDoSinaleiro = estado;
            /*
            desliga_rele2();
            desliga_rele3();
            desliga_rele4();
            */
        }
    }
    
    /*
    if (EstadoDoSinaleiro == SINALEIRO_VERMELHO){
        ContadorDeTempoDoSinaleiro = TEMPO_DO_ACIONAMENTO_DO_SINALEIRO;
        EstadoDoSinaleiro = estado;
    }
    */
}

int TempoDeAcionamentoDoBuzzerDeCancelamento;

void acionaBeepDeCancelamento(void){
    TempoDeAcionamentoDoBuzzerDeCancelamento = 25;
}

void atulizaBeepDeCancelamento(void){
    if (TempoDeAcionamentoDoBuzzerDeCancelamento > 15){
        TempoDeAcionamentoDoBuzzerDeCancelamento = TempoDeAcionamentoDoBuzzerDeCancelamento - 1;
        liga_rele1();
    } else {
        if (TempoDeAcionamentoDoBuzzerDeCancelamento > 10){
            TempoDeAcionamentoDoBuzzerDeCancelamento = TempoDeAcionamentoDoBuzzerDeCancelamento - 1;
            desliga_rele1();
        } else {
            if (TempoDeAcionamentoDoBuzzerDeCancelamento > 0){
                TempoDeAcionamentoDoBuzzerDeCancelamento = TempoDeAcionamentoDoBuzzerDeCancelamento - 1;
                liga_rele1();
            } else {
                TempoDeAcionamentoDoBuzzerDeCancelamento = 0;
                desliga_rele1();
            }
                
        }

    }
    
    if (TempoDeAcionamentoDoBuzzerDeCancelamento < 0){
        TempoDeAcionamentoDoBuzzerDeCancelamento = 0;
    }
            

    
    /*
    if (TempoDeAcionamentoDoBuzzerDeCancelamento > 0){
        TempoDeAcionamentoDoBuzzerDeCancelamento = TempoDeAcionamentoDoBuzzerDeCancelamento - 1;
        liga_rele1();
    } else {
        TempoDeAcionamentoDoBuzzerDeCancelamento = 0;
        desliga_rele1();
    }
    */
}

/*
void atualizarSinaleiro (void){
    if (ContadorDeTempoDoSinaleiro > (TEMPO_DO_ACIONAMENTO_DO_SINALEIRO - 1)){
        ContadorDeTempoDoSinaleiro = ContadorDeTempoDoSinaleiro - 1;
    } else {

        if (ContadorDeTempoDoSinaleiro > 0){
            ContadorDeTempoDoSinaleiro = ContadorDeTempoDoSinaleiro - 1;
        }


        if ((ContadorDeTempoDoSinaleiro == 0) && (EstadoDoSinaleiro != SINALEIRO_VERMELHO)){
            ContadorDeTempoDoSinaleiro = -1;
            EstadoDoSinaleiro = SINALEIRO_VERMELHO;
            desliga_rele2();
            //liga_rele2(); // amarelo
            desliga_rele3();
            //desliga_rele4();
            liga_rele4(); //vermelho
        } else {
        
            switch(EstadoDoSinaleiro){
                case SINALEIRO_VERMELHO:
                    liga_rele4(); //vermelho
                    desliga_rele2();
                    desliga_rele3();
                    break;
                case SINALEIRO_AMARELO:
                    liga_rele2(); // amarelo
                    desliga_rele3();
                    desliga_rele4();
                    break;
                case SINALEIRO_VERDE:
                    liga_rele3(); //verde
                    desliga_rele2();
                    desliga_rele4();
                    break;
                
                //case SINALEIRO_CANCELADO:
                    //desliga_rele3();
                    //liga_rele2(); // amarelo
                    //liga_rele4(); //vermelho
                    //break;
                //
                default:
                    EstadoDoSinaleiro = SINALEIRO_VERMELHO;
                    ContadorDeTempoDoSinaleiro = 2;
                    break;
            }
        }
    }
}
*/
void atualizarSinaleiro (void){
    if (ContadorDeTempoDoSinaleiro > (TEMPO_DO_ACIONAMENTO_DO_SINALEIRO - 1)){
        ContadorDeTempoDoSinaleiro = ContadorDeTempoDoSinaleiro - 1;
    } else {

        if (ContadorDeTempoDoSinaleiro > 0){
            ContadorDeTempoDoSinaleiro = ContadorDeTempoDoSinaleiro - 1;
        }


        if ((ContadorDeTempoDoSinaleiro == 0) && (EstadoDoSinaleiro != SINALEIRO_VERMELHO)){
            ContadorDeTempoDoSinaleiro = -1;
            EstadoDoSinaleiro = SINALEIRO_VERMELHO;
            desliga_rele2();
            //liga_rele2(); // amarelo
            desliga_rele3();
            //desliga_rele4();
            liga_rele4(); //vermelho
        } 
    }
        
    switch(EstadoDoSinaleiro){
        case SINALEIRO_VERMELHO:
            liga_rele4(); //vermelho
            desliga_rele2();
            desliga_rele3();
            break;
        case SINALEIRO_AMARELO:
            liga_rele2(); // amarelo
            desliga_rele3();
            desliga_rele4();
            break;
        case SINALEIRO_VERDE:
            liga_rele3(); //verde
            desliga_rele2();
            desliga_rele4();
            break;

        //case SINALEIRO_CANCELADO:
            //desliga_rele3();
            //liga_rele2(); // amarelo
            //liga_rele4(); //vermelho
            //break;
        //
        default:
            EstadoDoSinaleiro = SINALEIRO_VERMELHO;
            ContadorDeTempoDoSinaleiro = 2;
            break;
    }
        

   
}

void acionaBeepDeComandoFrango(int quantia){
    Beepar = quantia;
}

void ligarBuzzer(void){
    _LATC4 = 1;
}

void desligarBuzzer(void){
    _LATC4 = 0;
}


void realizaBeepDeComandoFrango (void){
    while (Beepar !=0){
        Beepar = Beepar - 1;
        //liga_buzzer();
        ligarBuzzer();
        delay_ms(100);
        //desliga_buzzer();
        desligarBuzzer();
        delay_ms(100);
    }
}




void aguradaSilencioNa485(void){
    while(ContadorDeSilencioNa485);
}




void enviaMovimentoParaWiegand(unsigned char *Dado, int Movimento, unsigned char Antena){
    unsigned char Dados[3];
    unsigned char Rascunho;

    if (ModoWieGand == WIEGAND_PARA_PORTAL){
        Dados[0] = Antena;
        Dados[0] = Dados[0] - 1;
        Dados[0] = Dados[0] << 5;
        Movimento = Movimento << 4;
        Dados[0] = Dados[0] | Movimento;
        Rascunho = *Dado & 0x0F;
        Dados[0] = Dados[0] | Rascunho;
        Dado = Dado + 1;
        Dados[1] = *Dado;
        Dado = Dado + 1;
        Dados[2] = *Dado;
        //enviaWiegand(Dados, 3);
    }
}


void enviaTAgParaAvaliacaoParaWiegand(unsigned char *Dado, unsigned char Antena){
    unsigned char Dados[3];
    unsigned char Rascunho;

    if (ModoWieGand == WIEGAND_PARA_AVALIACAO){
        Dados[0] = Antena;
        Dados[0] = Dados[0] - 1;
        Dados[0] = Dados[0] << 5;
        Rascunho = *Dado & 0x1F;
        Dados[0] = Dados[0] | Rascunho;
        Dado = Dado + 1;
        Dados[1] = *Dado;
        Dado = Dado + 1;
        Dados[2] = *Dado;
        //enviaWiegand(Dados, 3);
    }
}

void resetaParametrosFrango (void){
    
}


void salvaParametrosFrango (void){
//int EscreverNaEEprom (int endereco, unsigned char dado){
    EscreverNaEEprom(0, (unsigned char)ModoDeOperacao);
    EscreverNaEEprom(1, (unsigned char)AtrasoParaDegradarLeitura);
    EscreverNaEEprom(2, (unsigned char)RepeticaoNaLeitura);
    EscreverNaEEprom(3, (unsigned char)SensibilidadeDaAntena);
    EscreverNaEEprom(4, (unsigned char)TempoParaInatividadeDeTagMonitorada);
    EscreverNaEEprom(5, (unsigned char)NumeroDeAntenasLidas);
    EscreverNaEEprom(6, (unsigned char)ModoWieGand);
    EscreverNaEEprom(7, (unsigned char)Frequencia);
    EscreverNaEEprom(8, (unsigned char)PortaDePortalDeExclusao);
    EscreverNaEEprom(9, (unsigned char)Capacitores[0]);
    EscreverNaEEprom(10, (unsigned char)Capacitores[1]);
    EscreverNaEEprom(11, (unsigned char)Capacitores[2]);
    EscreverNaEEprom(12, (unsigned char)InibeOperacaoEMesagensComOPC);
}


void SetaFrequencias800(void){
    unsigned long rascunho;
    if (Frequencia < 100){
        rascunho = Frequencia;
        rascunho = rascunho + 800;
        rascunho = rascunho * 1000;
        Frequencies.freq[0] = rascunho;
        //Frequencies.numFreqs=1;
        Frequencies.numFreqs = 0;
    }

    if (Frequencia == PARAMETRO_SETA_FREQUENCIA_ANATEL){
        //lista_freq_anatel();
    }

    //readerInitStatus = as3993Initialize(Frequencies.freq[0]);
    //tunerInit(&mainTuner);
}


void SetaFrequencias(void){
    unsigned long rascunho;
    if (Frequencia < 33){
        rascunho = Frequencia;
        rascunho = rascunho + 900;
        rascunho = rascunho * 1000;
        Frequencies.freq[0] = rascunho;
        Frequencies.freq[1] = rascunho;
        Frequencies.numFreqs=1;
    }

    if (Frequencia == PARAMETRO_SETA_FREQUENCIA_ANATEL){
        //lista_freq_anatel();
    }

    //readerInitStatus = as3993Initialize(Frequencies.freq[0]);
    //tunerInit(&mainTuner);
}

void obtemParamentrosSalvosFrango (void){
//int LerDadosDaEEprom (int endereco, unsigned char *dado){
    unsigned char rascunho;

    LerDadosDaEEprom(0, &rascunho);
    ModoDeOperacao = rascunho;

    if ((ModoDeOperacao != OPERACAO_COM_LEITURA_UNICA) &&
            (ModoDeOperacao != OPERACAO_COM_MULTIPLAS_LEITURAS)){
        ModoDeOperacao = OPERACAO_COM_MULTIPLAS_LEITURAS;
    }

    LerDadosDaEEprom(1, &rascunho);
    AtrasoParaDegradarLeitura = rascunho;
    if (AtrasoParaDegradarLeitura > (LIMITE_PARA_ATRASO_PARA_DEGRADAR_LEITURA - 1)){
        AtrasoParaDegradarLeitura = 0;
    }

    LerDadosDaEEprom(2, &rascunho);
    RepeticaoNaLeitura = rascunho;
    if (RepeticaoNaLeitura > (LIMITE_DE_REPETICAO_EM_ANTENAS - 1)){
        RepeticaoNaLeitura = 1;
    }

    LerDadosDaEEprom(3, &rascunho);
    SensibilidadeDaAntena = rascunho;
    if (SensibilidadeDaAntena > (LIMITE_DA_SENSIBILIDADE - 1)){
        SensibilidadeDaAntena = LIMITE_DA_SENSIBILIDADE;
    }

    LerDadosDaEEprom(4, &rascunho);
    TempoParaInatividadeDeTagMonitorada = rascunho;
    if (TempoParaInatividadeDeTagMonitorada > TEMPO_LIMITE_PARA_INATIVIDADE_DE_TAG_MONITORADA){
        TempoParaInatividadeDeTagMonitorada = TEMPO_LIMITE_PARA_INATIVIDADE_DE_TAG_MONITORADA;
    }
    
    

    LerDadosDaEEprom(5, &rascunho);
    NumeroDeAntenasLidas = rascunho;
    if (NumeroDeAntenasLidas > (LIMITE_DE_ANTENAS_FRANGO - 1)){
        NumeroDeAntenasLidas = LIMITE_DE_ANTENAS_FRANGO;
    }

    LerDadosDaEEprom(6, &rascunho);
    if (rascunho < FINAL_WIEGAND){
        ModoWieGand = rascunho;
    }

    LerDadosDaEEprom(7, &rascunho);
    Frequencia = rascunho;
    SetaFrequencias();

    LerDadosDaEEprom(8, &rascunho);
    PortaDePortalDeExclusao = rascunho;

    LerDadosDaEEprom(9, &rascunho);
    Capacitores[0] = rascunho;

    LerDadosDaEEprom(10, &rascunho);
    Capacitores[1] = rascunho;

    LerDadosDaEEprom(11, &rascunho);
    Capacitores[2] = rascunho;
    
    LerDadosDaEEprom(12, &rascunho);
    InibeOperacaoEMesagensComOPC = rascunho;
    
    //ModoDeOperacao = OPERACAO_COM_LEITURA_UNICA;
    ModoDeOperacao = OPERACAO_COM_MULTIPLAS_LEITURAS;
    
    // *************************************************************************
    //  Ajustes de antenas para Portais de Juiz de fora em frequencia de 890Mhz
    //  As pontes rolantes usam todo o espectro Brasileiro do RFID e com isso
    //terei de realizar uma nova calibracao em todos os portais.
    // Vou ter como objetivo ter duas calibracoes:
    // -Para duas antenas
    // -Para 4 antenas.
    // Porem eu sei que havera mais valores
    // *************************************************************************

    
    // *************************************************************************
    // Duas antenas em 890Mhz
    // *************************************************************************
    
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(125);
    NumeroDeAntenasLidas = 4;
    //Frequencia = 90;//Para chegar em 890Mhz
    //SetaFrequencias();
    //SetaFrequencias800();
    //Frequencia = -20;//Para chegar em 890Mhz
    //Frequencia = 20;//Para chegar em 890Mhz
    Frequencia = 18;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    //Capacitores[0] = 1; 
    //Capacitores[1] = 4;
    //Capacitores[2] = 4;
    
    //Capacitores[0] = 0; 
    //Capacitores[1] = 9;
    //Capacitores[2] = 5;
    
    //Ajuste 1
    //Capacitores[0] = 1; 
    //Capacitores[1] = 4;
    //Capacitores[2] = 4;

    //Ajuste 2
    Capacitores[0] = 0; 
    Capacitores[1] = 4;
    Capacitores[2] = 3;

    //Ajuste 3
    //Capacitores[0] = 0; 
    //Capacitores[1] = 9;
    //Capacitores[2] = 7;

     
    
    RepeticaoNaLeitura = 2;

    
    // *************************************************************************

    
    // *************************************************************************
    // Quatro antenas em 890Mhz
    // *************************************************************************
    /*
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(125);
    NumeroDeAntenasLidas = 4;
    //NumeroDeAntenasLidas = 2;
    //Frequencia = 80;
    //SetaFrequencias800();
    Frequencia = 20;//Para chegar em 890Mhz
    //Frequencia = 23;//Para chegar em 890Mhz
    //Frequencia = 15;//Para chegar em 890Mhz
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 10;//14;//7;//5;
    PortaDePortalDeExclusao = 1;

    //Ajuste padrao
    //Capacitores[0] = 0; 
    //Capacitores[1] = 9;
    //Capacitores[2] = 5;


    //Ajuste 1
    //Capacitores[0] = 1; 
    //Capacitores[1] = 4;
    //Capacitores[2] = 4;

    
    //Ajuste 2
    Capacitores[0] = 0; 
    Capacitores[1] = 4;
    Capacitores[2] = 3;

    //Ajuste 3
    //Capacitores[0] = 0; 
    //Capacitores[1] = 9;
    //Capacitores[2] = 7;


    RepeticaoNaLeitura = 2;
    //RepeticaoNaLeitura = 1;
    */
    // *************************************************************************
    

    
    //Ajustes para antena Pixys Air Para Saint Gobain
    /*
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(125);
    NumeroDeAntenasLidas = 4;//Normalmente com 2 antenas
    Frequencia = 23;
    RepeticaoNaLeitura = 4;
    SetaFrequencias();
    //Frequencies.numFreqs = 0;
    TempoParaInatividadeDeTagMonitorada = 7;//7;
    PortaDePortalDeExclusao = 1;
    Capacitores[0] = 1; 
    Capacitores[1] = 4;
    Capacitores[2] = 4;
    */
    
    //Ajustes para a antena de Pixys Air
    /*
    AtrasoParaDegradarLeitura = 100;
    setaSensibilidade(5);
    NumeroDeAntenasLidas = 2;
    Frequencia = 15;
    RepeticaoNaLeitura = 1;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//7;
    PortaDePortalDeExclusao = 1;
    */
    
    //Ajustes para antena de vidro
    /*
    AtrasoParaDegradarLeitura = 5;
    setaSensibilidade(125);
    NumeroDeAntenasLidas = 4;
    Frequencia = 30;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    */
    
    /*
    AtrasoParaDegradarLeitura = 5;
    setaSensibilidade(125);
    NumeroDeAntenasLidas = 2;
    Frequencia = 30;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
l    */

    //O, N, M, G, E, C
    // Usando com 4 antenas no portal largo de juiz de fora e no da saida do patio de bobinas
    //AtrasoParaDegradarLeitura = 100;
    /*
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(5);
    NumeroDeAntenasLidas = 4;//4 antenas para o portal largo de juiz de fora
    Frequencia = 15;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    
    Capacitores[0] = 0; 
    Capacitores[1] = 9;
    Capacitores[2] = 5;
    RepeticaoNaLeitura = 2;
    */
    
    //Ajustado em campo
    //O, N, M, E    AtrasoParaDegradarLeitura = 0;
    // *********************************************************
    //SERVIU PARA QUASE TODOS OS PORTAIS DE JUIZ DE FORA
    // *********************************************************
    /*
    setaSensibilidade(150);
    NumeroDeAntenasLidas = 2;
    //Frequencia = 25;
    Frequencia = 11;//I JF
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    ModoDeOperacao = OPERACAO_COM_MULTIPLAS_LEITURAS;
    
    Capacitores[0] = 0; 
    Capacitores[1] = 4;
    Capacitores[2] = 3;
    RepeticaoNaLeitura = 2;
    //RepeticaoNaLeitura = 4;//i jf
    */
    
    //Ajustado em campo pra placa C
    /*
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(150);
    NumeroDeAntenasLidas = 2;
    Frequencia = 25;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    ModoDeOperacao = OPERACAO_COM_MULTIPLAS_LEITURAS;
    
    Capacitores[0] = 0; 
    Capacitores[1] = 9;
    Capacitores[2] = 5;
    RepeticaoNaLeitura = 2;
    */
    
    
    //H, I, J, K, L, D
    //Muito bom para um dos portais de Juiz de Fora em 30/08/18
    /*
    //AtrasoParaDegradarLeitura = 100;
    AtrasoParaDegradarLeitura = 0;
    setaSensibilidade(141);//k
    //setaSensibilidade(219);
    NumeroDeAntenasLidas = 2;
    //Frequencia = 15;
    //Frequencia = 4;//k
    Frequencia = 19;//G jf
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    
    Capacitores[0] = 0; 
    Capacitores[1] = 9;
    Capacitores[2] = 7;
    //RepeticaoNaLeitura = 4;//k
    RepeticaoNaLeitura = 2;//G
    */
    
    //B
    /*
    AtrasoParaDegradarLeitura = 100;
    setaSensibilidade(5);
    NumeroDeAntenasLidas = 2;
    Frequencia = 15;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;


    Capacitores[0] = 0; 
    Capacitores[1] = 9;
    Capacitores[2] = 7;
    RepeticaoNaLeitura = 4;
    */
/*
    AtrasoParaDegradarLeitura = 100;
    setaSensibilidade(5);
    NumeroDeAntenasLidas = 2;
    Frequencia = 15;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;

    Capacitores[0] = 0; 
    Capacitores[1] = 9;
    Capacitores[2] = 5;
    RepeticaoNaLeitura = 4;
    */
    //A
    /*
    AtrasoParaDegradarLeitura = 100;
    setaSensibilidade(4);
    NumeroDeAntenasLidas = 2;
    Frequencia = 15;
    SetaFrequencias();
    TempoParaInatividadeDeTagMonitorada = 7;//5;    
    PortaDePortalDeExclusao = 1;
    
    Capacitores[0] = 0; 
    Capacitores[1] = 4;
    Capacitores[2] = 3;
    RepeticaoNaLeitura = 4;
    */
    
    
    
    
    
}

void salvaCapacitores(int Cin, int Cen, int Cout){
  
}

void enviarID(void){
   
}

void enviaParaSerialOsParametrosAJustados(void){
    
}

void iniciaPortalFrango(void){
    
}


void reiniciaPortalFrango(void){
    
}

unsigned char gerarCheckSum (char *Dados, int Tamanho){
    unsigned char Resultado=0;
  
    return Resultado;
}

void enviaTagLidaParaAvaliacao(u8 *data, int Tamanho, int Antena, char Estado){
    
}


int procuraPosicaoLivreNosRegistrosDeTag (void){
    return 0;
}

int tagJaPresenteNosRegistros (unsigned char * Tag, int Tamanho){
    return 0;
}

int AtualizaEstadoDaTag(int Posicao, int Antena){
    return 0;
}


void registraTagDePortal (unsigned char *Tag, int Posicao, int Antena, int AntenaReal){
    
}

void registraAUltimaAntenaQueATagFoiLida(int Posicao, int Antena, int AntenaReal){

}

void eliminaRegistroDeTag(int Posicao){
    
}

extern char NomeDoPortal[2];

void enviaStringDoRegistroDeMovimento (TipoRegistroDeTagEmPortal Tag){
  
}

void geraStringDoRegistroDeMovimento (TipoRegistroDeTagEmPortal Tag){
   /* int Contador;
    char rascunho[30];
    memset(rascunho, 0, 30);
    int GerouEvento;
    GerouEvento = 0;
    
    if ((Tag.AntenaDaPrimeiraLeitura ==  ANTENA_DE_ENTRADA) &&
            (Tag.AntenaDaUltimaLeitura == ANTENA_DE_SAIDA)){
        Tag.estado = PORTAL_SAIU;
        enviaStringDoRegistroDeMovimento(Tag);
        GerouEvento = 1;
    } else {
        if ((Tag.AntenaDaPrimeiraLeitura ==  ANTENA_DE_ENTRADA) &&
                (Tag.estado == PORTAL_SAINDO)){
            Tag.estado = PORTAL_SAIU;
            enviaStringDoRegistroDeMovimento(Tag);
            GerouEvento = 1;
        }
    }

    if ((Tag.AntenaDaPrimeiraLeitura ==  ANTENA_DE_SAIDA) &&
            (Tag.AntenaDaUltimaLeitura == ANTENA_DE_ENTRADA)){
        Tag.estado = PORTAL_ENTROU;
        enviaStringDoRegistroDeMovimento(Tag);
        GerouEvento = 1;
    } else {
        if ((Tag.AntenaDaPrimeiraLeitura ==  ANTENA_DE_SAIDA) &&
                (Tag.estado == PORTAL_ENTRANDO)){
            Tag.estado = PORTAL_ENTROU;
            enviaStringDoRegistroDeMovimento(Tag);
            GerouEvento = 1;
        }
    }

    
    rascunho[POSICAO_DO_ESTADO_PARA_MOVIMENTO_PIC_PC_FRANGO] = Tag.estado;

    switch(Tag.AntenaDaUltimaLeitura){
        ContadorDeTagMovimentos = ContadorDeTagMovimentos + 1;
        case ANTENA_DE_ENTRADA:
            if (Tag.AntenaDaPrimeiraLeitura == ANTENA_DE_SAIDA){
                rascunho[POSICAO_DA_ANTENA_DA_ULTIMA_LEITURA_PIC_PC_FRANGO] = 1;
            }
            break;
        case ANTENA_DE_SAIDA:
            if (Tag.AntenaDaPrimeiraLeitura == ANTENA_DE_ENTRADA){
                rascunho[POSICAO_DA_ANTENA_DA_ULTIMA_LEITURA_PIC_PC_FRANGO] = 2;
            }
            break;
        default:
            //(void)sprintf(StringFinal, "Tag,%s,Foi e lida e ocorreu algum erro\n",(char *)SubStringDeEPC);
            break;
    }
    */
    
    //if (rascunho[POSICAO_DO_TAMANHO_TOTAL_PARA_MOVIMENTO_PIC_PC_FRANGO] == 0){
    /*if (GerouEvento == 0){
        rascunho[POSICAO_DO_COMANDO_PIC_PC_FRANGO] = TAG_DE_MOVIMENTO_CANCELADO;
        rascunho[POSICAO_DA_ANTENA_DA_LEITURA_PIC_PC_FRANGO] = 0xFF;
        rascunho[POSICAO_DO_TAMANHO_DA_CARGA_PIC_PC_FRANGO] = Tag.TamanhoDoEpc + 2;
        for (Contador = 0;Contador < TAMANHO_DE_EPC_EM_PORTAL_FRANGO;Contador = Contador + 1){
            rascunho[POSICAO_DO_EPC_EM_MOVIMENTO_PIC_PC_FRANGO + Contador] = Tag.Epc[Contador];
        }
        rascunho[POSICAO_DO_ESTADO_PARA_MOVIMENTO_PIC_PC_FRANGO] = 0;
        rascunho[POSICAO_DO_CHECKSUM_PARA_MOVIMENTO_PIC_PC_FRANGO] =
                gerarCheckSum(rascunho, POSICAO_DO_CHECKSUM_PARA_MOVIMENTO_PIC_PC_FRANGO);
        if (PausaNasMensagensDeAvaliacao == 0){
            if (InibeOperacaoEMesagensComOPC == 0){
                EnviaArrayDeBytesPara485(rascunho, POSICAO_DO_TAMANHO_TOTAL_PARA_MOVIMENTO_PIC_PC_FRANGO);
            }
        }
        enviaMovimentoParaWiegand(Tag.Epc, Tag.estado, Tag.AntenaDaUltimaLeitura);
        
        setaSinaleiro(SINALEIRO_VERMELHO);
        //setaSinaleiro(SINALEIRO_CANCELADO);
        
        
        if (Tag.LeuOutroAntena != SEM_REGISTRO_DE_ANTENA){
            acionaBeepDeCancelamento();
        }
        
        //acionaBeepDeCancelamento();
        
    }*/
}

int DadosASeremEnviadosPelaSerialDoPortalFrango(void){
    return DadosParaASerial;
}

void DadosDaSerialDoPortalTratadosFrango(void){
    DadosParaASerial = 0;
}

int DadosEstaoSendoEnviadosAoPC(void){
    return SerialOcupada;
}

void ComecouAEnviarDadosAoPC(void){
    SerialOcupada = 1;
}

void ParouDeEnviarDadosAoPC(void){
    SerialOcupada = 0;
}


void LidaComEstadosDaTagEmTick(void){
    if (RegistroDeTagEmPortal[TagEmTratamento].TempoParaInatividade == 0){
        if (RegistroDeTagEmPortal[TagEmTratamento].estado == PORTAL_SAINDO){
            RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_SAIU;
        }
    }

    if (RegistroDeTagEmPortal[TagEmTratamento].TempoParaInatividade == 0){
        if (RegistroDeTagEmPortal[TagEmTratamento].estado == PORTAL_ENTRANDO){
            RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_ENTROU;
        }
    }

    /*
    if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeEntrada == 0){
        if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeSaida != 0){
            RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_SAIDA;
        }
    }

    if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeEntrada <
            RegistroDeTagEmPortal[TagEmTratamento].ContagemDeSaida){
        RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_SAINDO;
    }

    if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeSaida == 0){
        if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeEntrada != 0){
            RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_ENTRADA;
        }
    }

    if (RegistroDeTagEmPortal[TagEmTratamento].ContagemDeEntrada >
            RegistroDeTagEmPortal[TagEmTratamento].ContagemDeSaida){
        RegistroDeTagEmPortal[TagEmTratamento].estado = PORTAL_ENTRANDO;
    }
    */
}

void acoesEmCodigoCorrentePortalFrango(void){
    /*
    TagEmTratamento = TagEmTratamento + 1;
    if (TagEmTratamento > (MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL - 1)){
        TagEmTratamento = 0;
    }
    */
    
    
    for (TagEmTratamento = 0;TagEmTratamento < MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL;TagEmTratamento = TagEmTratamento + 1){
    //if (TagEmTratamento < MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL){
        //TagEmTratamento = TagEmTratamento + 1;
        LidaComEstadosDaTagEmTick();

        if (RegistroDeTagEmPortal[TagEmTratamento].TempoParaInatividade == 0){
            //*********************************************************8
            //Nesse ponto eh aonde o desempenho eh degradado
            //geraStringDoRegistroDeMovimento(RegistroDeTagEmPortal[TagEmTratamento], StringDeSaidaParaSerial);
            geraStringDoRegistroDeMovimento(RegistroDeTagEmPortal[TagEmTratamento]);
            //*********************************************************8

            DadosParaASerial = 1;
            if (RegistroDeTagEmPortal[TagEmTratamento].Epc[0] != 0){
                eliminaRegistroDeTag(TagEmTratamento);
            }
            
        }
    } 
     //else {
        //TagEmTratamento = 0;
    
}


void acoesEmTickParaPortalFrango(void){
//    int TempoDeSilencioAtualNoZigBee=0;
    if (ContadorDeSilencioNa485){
        ContadorDeSilencioNa485 =  ContadorDeSilencioNa485 - 1;
    }
    
    //TempoDeSilencioAtualNoZigBee = tempoDeSilencioNoZigBee();
//    if (TempoDeSilencioAtualNoZigBee >= (TEMPO_MAXIMO_DE_SILENCIO_DO_ZIGBEE - 1)){
   //     PodeEnviarTabelaDeInvisiveis = 1;
   // }

    /*
    TagEmTratamentoEmTick = TagEmTratamentoEmTick + 1;
    if (TagEmTratamentoEmTick >= MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL){
        TagEmTratamentoEmTick = 0;
    }

    if (RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade > 0){
        RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade = RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade - 1;
    }
    */

    /*
    int Posicao;
    for(Posicao = 0;Posicao < MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL;Posicao = Posicao + 1){
        if (RegistroDeTagEmPortal[Posicao].TempoParaInatividade > 0){
            RegistroDeTagEmPortal[Posicao].TempoParaInatividade = RegistroDeTagEmPortal[Posicao].TempoParaInatividade - 1;
        }
    }
    */
    
    //acoesEmCodigoCorrentePortalFrango();
}

void acoesEmTickACadaSegundoParaPortalFrango(void){

    /*
    TagEmTratamentoEmTick = TagEmTratamentoEmTick + 1;
    if (TagEmTratamentoEmTick >= MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL){
        TagEmTratamentoEmTick = 0;
    }

    if (RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade > 0){
        RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade = RegistroDeTagEmPortal[TagEmTratamentoEmTick].TempoParaInatividade - 1;
    }
    */

    if (PausaNasMensagensDeAvaliacao != 0){
        if (InibeOperacaoEMesagensComOPC == 0){
            PausaNasMensagensDeAvaliacao = PausaNasMensagensDeAvaliacao - 1;
        }
    }

    int Posicao;
    for(Posicao = 0;Posicao < MAXIMO_DE_TAGS_MONITORASDAS_EM_PORTAL;Posicao = Posicao + 1){
        if (RegistroDeTagEmPortal[Posicao].TempoParaInatividade > 0){
            RegistroDeTagEmPortal[Posicao].TempoParaInatividade = RegistroDeTagEmPortal[Posicao].TempoParaInatividade - 1;
        }
    }

    
    if (PortaDePortalDeExclusao != 0){
        atualizarSinaleiro();
        atulizaBeepDeCancelamento();
    }
    
    //operacoesEmTickParaEnviarTabelasDeInvisiveisEVisiveis();
    //acoesEmCodigoCorrentePortalFrango();
    
    if (ContagemParaExpirarOsComandosDoPC > 0){
        ContagemParaExpirarOsComandosDoPC = ContagemParaExpirarOsComandosDoPC - 1;
        if (ContagemParaExpirarOsComandosDoPC == 1){
            //iniciaEstruturaDoProtocoloPC();
        }
    }

}

void setaSensibilidade (unsigned char valor){
    //signed char sensibilidadeAtual, resultado;
    signed char rascunho = 0;
    SensibilidadeDaAntena = valor;
    rascunho = rascunho - valor;
    //sensibilidadeAtual = as3993GetSensitivity();
    //if (sensibilidadeAtual != rascunho){
      //resultado = as3993SetSensitivity(rascunho);
    //}
    as3993SetSensitivity(rascunho);
}

void setaNumeroDeAntenas (int valor){
    if ((valor > 0) && (valor < 8)){
        NumeroDeAntenasLidas = valor;
    }
}

void setaAtrasoNaLeitura (int valor){
    AtrasoParaDegradarLeitura = valor;
}

void setaRepeticaoDaLeitura (int valor){
    RepeticaoNaLeitura = valor;
}

extern int EuSouOAlphaDosPortais;



void repetirOComando(void){
    /*
    if (EuSouOAlphaDosPortais == 1){
        //Pede para quem enviou o movimento o fazer novamente
        _LATG13 = 1;
        delay_us(10);
        uart1Tx(0xFE);
        //delay_us (120);
        //delay_ms (4);
        uart1Tx(0x04);
        //delay_us (120);
        //delay_ms (4);
        uart1Tx(0x55);
        //delay_us (120);
        //delay_ms (4);
        uart1Tx(0x58);
        //delay_us (120);
        //delay_ms (4);

        _LATG13 = 0;            
    }
    */
}

void comandoRecebidoNa485(void){
    /*
    if (EuSouOAlphaDosPortais == 1){
        //Pede para quem enviou o movimento o fazer novamente
        _LATG13 = 1;
        uart1Tx(0xFD);
        //delay_ms (4);
        //delay_us (500);
        uart1Tx(0x04);
        //delay_ms (4);
        //delay_us (500);
        uart1Tx(0xAA);
        //delay_ms (4);
        //delay_us (500);
        uart1Tx(0xAC);
        //delay_ms (4);
        //delay_us (500);

        _LATG13 = 0;            
    }
    */
}

void reenvioDeItemDaListaDeSaida(void){
    /*
    unsigned char Saida[10];
    int Contador;
    
    if (recuperaItemDaListaDeSaida(Saida) >= 0){
        
        aguradaSilencioNa485();

        _LATG13 = 1;
        delay_us(10);
        for (Contador = 0;Contador < 8; Contador = Contador + 1){
            uart1Tx(Saida[Contador]);
            //delay_us (120);
            //delay_ms (4);
            //delay_us (500);
        }
        _LATG13 = 0; 
        
    }
    */
}


void reenvioDeItemDaListaDeSaidaPorEstouDeTempo(void){
    /*
    unsigned char Saida[10];
    int Contador;
    
    if (ContadorDeReenvioDeDadosDaListaDeSaida == 0){
        ContadorDeReenvioDeDadosDaListaDeSaida = TEMPO_PARA_REENVIO_DA_LISTA_DE_SAIDA;
        if (recuperaItemDaListaDeSaida(Saida) >= 0){
            _LATG13 = 1;
            for (Contador = 0;Contador < 8; Contador = Contador + 1){
                uart1Tx(Saida[Contador]);
                //delay_us (120);
                //delay_ms (4);
                //delay_us (500);
            }
            _LATG13 = 0; 
        }
    }
    */
}


void lidaComComandoDOPC(unsigned char dado){
   /* int rascunho;
    int Resultado;
    //int Contador;
    //unsigned char Saida[TAMANHO_DO_ITEM];
    
    //Resultado = trataRecepcaoNoProcolo (dado, &EstruturaDeRecepcaoDoPC.Estado, &EstruturaDeRecepcaoDoPC.Comando, &EstruturaDeRecepcaoDoPC.Tamanho, &CorpoDeComandoRecebidoDoPC[EstruturaDeRecepcaoDoPC.ContagemDoCorpo], &EstruturaDeRecepcaoDoPC.ContagemDoCorpo, &EstruturaDeRecepcaoDoPC.CheckSum);
    Resultado = trataRecepcaoDoProcoloNoPortal (dado, &EstruturaDeRecepcaoDoPC.Estado, &EstruturaDeRecepcaoDoPC.Comando, &EstruturaDeRecepcaoDoPC.Tamanho, &CorpoDeComandoRecebidoDoPC[EstruturaDeRecepcaoDoPC.ContagemDoCorpo], &EstruturaDeRecepcaoDoPC.ContagemDoCorpo, &EstruturaDeRecepcaoDoPC.CheckSum);
    //int contador;
    
    //if (Resultado == 1){
    
    if (Resultado == -1){
        if (EuSouOAlphaDosPortais == 1){
            //Pede para quem enviou o movimento o fazer novamente
            
            _LATG13 = 1;
            delay_us(10);
            uart1Tx(0xFE);
            //delay_us (120);
            //delay_ms (4);
            uart1Tx(0x05);
            //delay_us (120);
            //delay_ms (4);
            uart1Tx(0x55);
            //delay_us (120);
            //delay_ms (4);
            uart1Tx(0x58);
            //delay_us (120);
            //delay_ms (4);
            
            _LATG13 = 0;            
             * */
        /*} else {
            
            if (recuperaItemDaListaDeSaida(Saida) >= 0){
                _LATG13 = 1;
                delay_us(10);
                for (Contador = 0;Contador < 8; Contador = Contador + 1){
                    uart1Tx(Saida[Contador]);
                    //delay_us (120);
                    //delay_ms (4);
                    //delay_us (500);
                }
                _LATG13 = 0; 
            }
            */
    /*    }
    }
    if (Resultado != 0){//Puro desespero
        switch(EstruturaDeRecepcaoDoPC.Comando){
            case 0xF0:
                TempoParaInatividadeDeTagMonitorada = CorpoDeComandoRecebidoDoPC[0];
                salvaParametrosFrango();
                break;
            case 0x55:
                reiniciaPortalFrango();
                break;
            case 0xAA:
                enviarID();
                break;
                
            case 0xAB:
                PausaNasMensagensDeAvaliacao = 2;
                break;
            case 0x7F:
                PortaDePortalDeExclusao = PrimeiroParametroDaSerial;
                salvaParametrosFrango();
                acionaBeepDeComandoFrango(1);
                break;
                
            case 0x80:
                rascunho = CorpoDeComandoRecebidoDoPC[0];
                if (rascunho < 9){
                    NumeroDeAntenasLidas = rascunho;
                    salvaParametrosFrango();
                    acionaBeepDeComandoFrango(1);
                }
                break;
            case 0x89:
                setaSensibilidade(dado);
                salvaParametrosFrango();

                acionaBeepDeComandoFrango(1);
                estadoSerialFrango = ESPERANDO_COMANDO_SERIAL_FRANGO;
                break;
            case 0x8A:
                if (dado == 0){
                    ModoDeOperacao = OPERACAO_COM_LEITURA_UNICA;
                }

                if (dado == 1){
                    ModoDeOperacao = OPERACAO_COM_MULTIPLAS_LEITURAS;
                }
                
                if (dado == 2){
                    ModoDeOperacao = OPERACAO_LEITURAS_INITERRUPTAS;
                }

                salvaParametrosFrango();
                acionaBeepDeComandoFrango(1);
                break;
            case 0x8B:
                setaAtrasoNaLeitura(CorpoDeComandoRecebidoDoPC[0]);
                salvaParametrosFrango();
                acionaBeepDeComandoFrango(1);
                break;
            case 0x8C:
                setaRepeticaoDaLeitura(CorpoDeComandoRecebidoDoPC[0]);
                salvaParametrosFrango();
                acionaBeepDeComandoFrango(1);
                break;
            case 0x8D:
                enviaParaSerialOsParametrosAJustados();
                acionaBeepDeComandoFrango(1);
                break;
            case 0x8E:
                if (CorpoDeComandoRecebidoDoPC[0] < FINAL_WIEGAND){
                    ModoWieGand = CorpoDeComandoRecebidoDoPC[0];
                    salvaParametrosFrango();
                    acionaBeepDeComandoFrango(1);
                }
                break;
            case 0x8F:
                if ((CorpoDeComandoRecebidoDoPC[0] < 28) || (CorpoDeComandoRecebidoDoPC[0] == PARAMETRO_SETA_FREQUENCIA_ANATEL)){
                    Frequencia = CorpoDeComandoRecebidoDoPC[0];
                    salvaParametrosFrango();
                    SetaFrequencias();
                    acionaBeepDeComandoFrango(1);
                }
                break;
            case 0x90:
                CorpoDeComandoRecebidoDoPC[0] = CorpoDeComandoRecebidoDoPC[0] & 0x03;
                CorpoDeComandoRecebidoDoPC[0] = CorpoDeComandoRecebidoDoPC[0] << 2;
                as3993SingleWrite(AS3993_REG_RFOUTPUTCONTROL, CorpoDeComandoRecebidoDoPC[0]);
                acionaBeepDeComandoFrango(1);
                break;
            case 0x91:
                estadoSerialFrango = ESPERANDO_COMANDO_SERIAL_FRANGO;
                sintonizaCapacitores(&mainTuner, CorpoDeComandoRecebidoDoPC[0], CorpoDeComandoRecebidoDoPC[1], CorpoDeComandoRecebidoDoPC[2]);
                Capacitores[0] = CorpoDeComandoRecebidoDoPC[0];
                Capacitores[1] = CorpoDeComandoRecebidoDoPC[1];
                Capacitores[2] = CorpoDeComandoRecebidoDoPC[2];
                salvaParametrosFrango();
                acionaBeepDeComandoFrango(1);
                break;
            case 0x92:
                salvaParametrosFrango();
                InibeOperacaoEMesagensComOPC = CorpoDeComandoRecebidoDoPC[0];
                acionaBeepDeComandoFrango(1);
                break;
                
            case 0xF5:
                ContadorDeSilencioNa485 = TEMPO_DE_SILENCIO_NA_485;
                //adicionaItemNaTabelaDeInvisiveis(CorpoDeComandoRecebidoDoPC);
                //(void)adicionaElementoDaTabelaDeExclusao (CorpoDeComandoRecebidoDoPC, ENTROU_NA_AREA_SEGURA);
                (void)adicionaElementoDaTabelaDeExclusao (CorpoDeComandoRecebidoDoPC,CorpoDeComandoRecebidoDoPC[3],CorpoDeComandoRecebidoDoPC[4], ENTROU_NA_AREA_SEGURA);
                comandoRecebidoNa485();
                break;
                
            case 0xF6:
                ContadorDeSilencioNa485 = TEMPO_DE_SILENCIO_NA_485;
                //adicionaItemNaTabelaDeVisiveis(CorpoDeComandoRecebidoDoPC);
                //(void)adicionaElementoDaTabelaDeExclusao (CorpoDeComandoRecebidoDoPC, SAIU_NA_AREA_SEGURA);
                (void)adicionaElementoDaTabelaDeExclusao (CorpoDeComandoRecebidoDoPC,CorpoDeComandoRecebidoDoPC[3],CorpoDeComandoRecebidoDoPC[4], SAIU_NA_AREA_SEGURA);
                comandoRecebidoNa485();
                break;
            case 0xFD:
                RemovePrimeiroItemDaListaDeSaida();
                break;
            case 0xFE:
                reenvioDeItemDaListaDeSaida();
                
                if (recuperaItemDaListaDeSaida(Saida) >= 0){
                    _LATG13 = 1;
                    for (Contador = 0;Contador < 8; Contador = Contador + 1){
                        uart1Tx(Saida[Contador]);
                        //delay_us (120);
                        delay_ms (4);
                        delay_us (500);
                    }
                    _LATG13 = 0; 
                }
                */
                          
        /*}
        iniciaEstruturaDoProtocoloPC();
    }*/
    
}

void testaEnvio(void){
    (void)sprintf((char *)RegistroDeTagEmPortal[0].Epc, "123");


    RegistroDeTagEmPortal[0].TamanhoDoEpc = TAMANHO_DE_EPC_EM_PORTAL_FRANGO;
    RegistroDeTagEmPortal[0].AntenaDaPrimeiraLeitura = ANTENA_DE_ENTRADA;
    //RegistroDeTagEmPortal[0].AntenaDaPrimeiraLeitura = ANTENA_DE_SAIDA;
    RegistroDeTagEmPortal[0].AntenaDaUltimaLeitura = ANTENA_DE_SAIDA;
    //RegistroDeTagEmPortal[0].AntenaDaUltimaLeitura = ANTENA_DE_ENTRADA;
    RegistroDeTagEmPortal[0].TempoParaInatividade = 0;
    RegistroDeTagEmPortal[0].MarcaDePosicaoOcupada = 0;
    RegistroDeTagEmPortal[0].ContagemDeEntrada = 0;
    RegistroDeTagEmPortal[0].ContagemDeSaida = 0;
    RegistroDeTagEmPortal[0].estado = 0;
    //geraStringDoRegistroDeMovimento(RegistroDeTagEmPortal[0], Rascunho);
    geraStringDoRegistroDeMovimento(RegistroDeTagEmPortal[0]);



    //void enviaTagLidaParaAvaliacao(u8 *data, int Tamanho, int Antena, char Estado){
    //enviaTagLidaParaAvaliacao(RegistroDeTagEmPortal[0].Epc,3,1,0);

}
