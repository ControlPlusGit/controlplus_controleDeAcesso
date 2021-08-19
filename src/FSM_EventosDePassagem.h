/* 
 * File:   FSM_EventosDePassagem.h
 * Author: Vitor
 *
 * Created on 30 de Janeiro de 2020, 17:18
 */

#ifndef EVENTOS_DE_PASSAGEM_H
#define	EVENTOS_DE_PASSAGEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define SIM 1
    
//#define INTERVALO_ENTRE_TENTATIVAS 500
    
#define TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PASSAGEM 1
    
#define TEMPO_AGUARDANDO_ACK_EVENTOS_DE_PASSAGEM 2000
    

    
#define TAMANHO_EVENTO_DE_PASSAGEM_EM_BYTES 10
    
#define NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS 900
    
#define VALOR_FLAG_INICIALIZACAO_EEPROM 0xA4 // Para resetar a eeprom basta mudar esse valor e gravar o firmware novamente.
    
#define ENDERECO_FLAG_INICIALIZACAO_EEPROM 1995
    
#define MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS 1996
#define LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ARMAZENADOS 1997

#define MSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS 1998
#define LSB_ENDERECO_EVENTOS_DE_PASSAGEM_ENVIADOS 1999
    
#define ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS 2000
        
    
typedef struct{ 
    unsigned char flagDeRegistro;
    unsigned char EPC_veiculo[2];
    unsigned char tipoMovimento;
    unsigned char dia;
    unsigned char mes;
    unsigned char ano;
    unsigned char hora;
    unsigned char minuto;
    unsigned char segundo;
}eventoPassagem;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: lerEventoDePassagemDeNaEEPROM
// PARÂMETROS: eventoPassagem *evento, int endereco
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagems
// FUNÇÃO: realiza a leitura de um evento de parada na eeprom para dentro de evento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: criarEventoDePassagemDe
// PARÂMETROS: eventoPassagem *novoEventoDePassagem
// UTILIZADA EM: logicaDeV2
// FUNÇÃO: realiza a escrita de um novo evento de passagem dentro da eeprom
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void criarEventoDePassagem(eventoPassagem *novoEventoDePassagem);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: inicializaMaquinaDeEstados_EventosDePassagem
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeV2
// FUNÇÃO: inicializa as variáveis necessárias para o funcionamento da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void inicializaMaquinaDeEstados_EventosDePassagem(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: habilitaMaquinaDeEstados_EventosDePassagem
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeV2
// FUNÇÃO: libera a máquina de estados para execução
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void habilitaMaquinaDeEstados_EventosDePassagem(void);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: executaMaquinaDeEstados_EventosDePassagem
// PARÂMETROS: nenhum
// UTILIZADA EM: tick
// FUNÇÃO: executa a máquina de estados. Essa função é executada com interrupção de timer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void executaMaquinaDeEstados_EventosDePassagem(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: bloqueiaMaquinaDeEstados_EventosDePassagem
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeV2
// FUNÇÃO: bloqueia a execução da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void bloqueiaMaquinaDeEstados_EventosDePassagem(void);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: limpaBufferNaMaquinaDeEstados_EventosDePassagem
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_EventosDePassagems
// FUNÇÃO: limpa o buffer de mensagens recebidas da UART2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void limpaBufferNaMaquinaDeEstados_EventosDePassagem(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TESTEMAQUINAESTADO_H */

