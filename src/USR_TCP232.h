#ifndef ETH_H
#define ETH_H

#define TAMANHO_BUFFER_RX_ETHERNET  100
#define IP_REMOTO_PRINCIPAL         1
#define IP_REMOTO_SECUNDARIO        2
#define CONNECTED                   1
#define NOT_CONNECTED               0

#define RESET_ETH                   LATFbits.LATF2;

#define TEMPO_LIMITE_DE_RESPOSTA_COMANDO_ETH 500
#define ENDERECO_INICIAL_PARA_ARMAZENAR_VEICULOS_NA_EEPROM 30000



void enviaDadosParaEthernet(char dados[TAMANHO_BUFFER_RX_ETHERNET], int Tamanho);
void operacoesEmTickParaEthernet(void);

void solicitaDataHoraPelaEthernet(void);
void enviaKeepAliveParaEthernet(char status);

char solicitaStatusDeConexaoTCP(void);
void CommandHandleModuloEthernet(void);
void setaStatusDoLedDeEthernet(void);

void defineIPRemotoInicial(void);
void limpaBufferRxEthernet(void);
//void aguardoPrimeiraConexaoTCP(void);
void enviaDadosParaEthernet(char dados[TAMANHO_BUFFER_RX_ETHERNET], int Tamanho);

char entraEmModoAt(void);
char saiDoModoAt(void);
char resetModuloETH(void);
char restartModuloEth(void);

char enviaURLDataHora(void);
char enviaURLKeepAlive(void);
char enviaURLGreenList(void);
char enviaURLEnvioDeEventos(void);

char setaURLDataHora(void);
char setaURLKeepAlive(void);
char setaURLGreenList(void);
char setaURLEnvioDeEventos(void);

void enviaSolicitacaoDataHoraPelaEthernet(void);
void enviaKeepAlivePelaEthernet(void);
void enviaSolicitacaoGreenListPelaEthernet(void);
void enviaEventosDeEntradaEhSaidaPelaEthernet(void);

void atualizaDataHoraNoRTC(void);
void executaMaquinaDeEstadosUSRTCP232(void);

void inicializaModuloEthernet(void);

unsigned int obtemNumeroDeTagsRecebidasNaGreenListRequest(void);
void salvaGreenListNaEEPROM(unsigned int numRegistros);
char VerificaIntegridadeDaGreenList(unsigned int numRegistros);
void exibeListaDeTagsRecebidasDoServer(void);
void limpaListaDeTagsRecebidasDoServer(void);
void carregaListaDeVeiculosAutorizadosNaRAM(void);

void setaStatusDoLedDeEthernet(void);

//extern char bufferRxEthernet[TAMANHO_BUFFER_RX_ETHERNET];
extern unsigned char statusDeConexaoTCP;



#endif
