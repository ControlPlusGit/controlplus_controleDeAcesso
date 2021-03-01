/* 
 * File:   FSM_KeepAlive.h
 * Author: Vitor
 *
 * Created on 13 de Fevereiro de 2020, 12:03
 */

#ifndef FSM_KEEPALIVE_H
#define	FSM_KEEPALIVE_H

#ifdef	__cplusplus
extern "C" {
#endif
        
#define NAO 0
#define SIM 1
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_ENTRE_ESTADOS_FSM_DATA_HORA
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: controlar o tempo de execução de cada estado da máquina, aplicando um delay.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #define TEMPO_ENTRE_ESTADOS_FSM_KEEP_ALIVE 100 // MILISEGUNDOS

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEFINE: TEMPO_AGUARDANDO_ACK
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: controlar o tempo em que a maquina fica aguardando um ACK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    //#define TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE 300000ULL  // MILISEGUNDOS
    #define TEMPO_AGUARDANDO_KEEP_ALIVE_FSM_KEEP_ALIVE 2000  // MILISEGUNDOS
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: inicializaMaquinaDeEstados_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: inicializa as variáveis necessárias para o funcionamento da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void inicializaMaquinaDeEstados_KeepAlive(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: habilitaMaquinaDeEstados_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: logicaDeEmpilhadeiraV2
// FUNÇÃO: libera a máquina de estados para execução
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void habilitaMaquinaDeEstados_KeepAlive(void);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: executaMaquinaDeEstados_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: tick
// FUNÇÃO: executa a máquina de estados. Essa função é executada com interrupção de timer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void executaMaquinaDeEstados_KeepAlive(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: bloqueiaMaquinaDeEstados_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: bloqueia a execução da máquina de estados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void bloqueiaMaquinaDeEstados_KeepAlive(void);
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: limpaBufferNaMaquinaDeEstados_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: limpa o buffer de mensagens recebidas da UART2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void limpaBufferNaMaquinaDeEstados_KeepAlive(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: incrementaContadorExecucao_FSM_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: incrementa a variavel delayExecucao_KeepAlive
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    void incrementaContadorExecucao_FSM_KeepAlive(void);    

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNÇÃO: zeraContadorExecucao_FSM_KeepAlive
// PARÂMETROS: nenhum
// UTILIZADA EM: executaMaquinaDeEstados_KeepAlives
// FUNÇÃO: zera a variável delayExecucao_KeepAlive
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    void zeraContadorExecucao_FSM_KeepAlive(void);   
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* FSM_KEEPALIVE_H */

