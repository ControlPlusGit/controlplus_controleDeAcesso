/* 
 * File:   FSM_EventosDeParada.h
 * Author: Vitor
 *
 * Created on 30 de Janeiro de 2020, 17:18
 */

#ifndef EVENTOS_DE_PARADA_H
#define	EVENTOS_DE_PARADA_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define NAO 0
#define SIM 1
    
//#define INTERVALO_ENTRE_TENTATIVAS 500
    
#define TEMPO_ENTRE_ESTADOS_FSM_EVENTOS_DE_PARADA 1
    
#define TEMPO_AGUARDANDO_ACK_EVENTOS_DE_PARADA 2000
    
#define ENDERECO_INICIAL_PARA_ARMAZENAR_EVENTOS 2000
    
#define TAMANHO_EVENTO_DE_PARADA_EM_BYTES 30
    
#define NUMERO_MAXIMO_DE_EVENTOS_ARMAZENADOS 900
    
#define VALOR_FLAG_INICIALIZACAO_EEPROM 0xA3 // Para resetar a eeprom basta mudar esse valor e gravar o firmware novamente.
    
#define ENDERECO_FLAG_INICIALIZACAO_EEPROM 1995
    
#define MSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS 1996
#define LSB_ENDERECO_EVENTOS_DE_PARADA_ARMAZENADOS 1997

#define MSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS 1998
#define LSB_ENDERECO_EVENTOS_DE_PARADA_ENVIADOS 1999
        
typedef struct{    
    unsigned char EPC_area[8];
    unsigned char EPC_operador[8];
    unsigned char EPC_pedestre[8];
    unsigned char dia;
    unsigned char mes;
    unsigned char ano;
    unsigned char hora;
    unsigned char minuto;
    unsigned char segundo;
}eventoParadaEmpilhadeira;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: lerEventoDeParadaDeEmpilhadeiraNaEEPROM
// PARÂMETROS: eventoParadaEmpilhadeira *evento, int endereco
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParadas
// FUNÇÃO: realiza a leitura de um evento de parada na eeprom para dentro de evento
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void lerEventoDeParadaDeEmpilhadeiraNaEEPROM(eventoParadaEmpilhadeira *evento,int endereco);
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: criarEventoDeParadaDeEmpilhadeira
// PARÂMETROS: eventoParadaEmpilhadeira *novoEventoDeParada
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: realiza a escrita de um novo evento de parada dentro da eeprom
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void criarEventoDeParadaDeEmpilhadeira(eventoParadaEmpilhadeira *novoEventoDeParada);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: inicializaMaquinaDeEstados_EventosDeParada
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: inicializa as variáveis necessárias para o funcionamento da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void inicializaMaquinaDeEstados_EventosDeParada(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: habilitaMaquinaDeEstados_EventosDeParada
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: libera a máquina de estados para execução
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void habilitaMaquinaDeEstados_EventosDeParada(void);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: executaMaquinaDeEstados_EventosDeParada
// PARÂMETROS: nenhum
// UTILIZADA EM: tick
// FUNÇÃO: executa a máquina de estados. Essa função é executada com interrupção de timer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void executaMaquinaDeEstados_EventosDeParada(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: bloqueiaMaquinaDeEstados_EventosDeParada
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: bloqueia a execução da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void bloqueiaMaquinaDeEstados_EventosDeParada(void);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: limpaBufferNaMaquinaDeEstados_EventosDeParada
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParadas
// FUNÇÃO: limpa o buffer de mensagens recebidas da UART2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void limpaBufferNaMaquinaDeEstados_EventosDeParada(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TESTEMAQUINAESTADO_H */

