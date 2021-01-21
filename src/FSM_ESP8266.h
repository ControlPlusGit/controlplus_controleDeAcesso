/* 
 * File:   FSM_ESP8266.h
 * Author: Vitor
 *
 * Created on 25 de Fevereiro de 2020, 18:27
 */

#ifndef FSM_ESP8266_H
#define	FSM_ESP8266_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define NAO 0
    #define SIM 1

    #define LIGADO 1
    #define DESLIGADO 0

    #define CONECTADO 1
    #define DESCONECTADO 0

    #define NUM_MAX_ERROS_TIMEOUT 4

    #define NUM_MAX_ERROS_MAQUINA_TIMEOUT 2

    #define TEMPO_ENTRE_ESTADOS_FSM_ESP8266 100

    #define TEMPO_AGUARDANDO_ACK_ESP8266 500

    #define TEMPO_AGUARDANDO_ACK_MSG_WIFI_ESP8266 20000

    extern unsigned int wifiLiberadoParaUso;
    
    char ESP8266_jaFoiInicializado(void);
    
    void habilitaMaquinaDeEstados_ESP8266(void);

    void bloqueiaMaquinaDeEstados_ESP8266(void);

    void limpaBufferNaMaquinaDeEstados_ESP8266(void);

    void inicializaMaquinaDeEstados_ESP8266(void);
    
    void incrementaContadorExecucao_FSM_ESP8266(void);
    
    void zeraContadorExecucao_FSM_ESP8266(void);
       
    void executaMaquinaDeEstados_ESP8266(void);
    
    void trocarIpDeServidor(char servidor);
    
    void resetarErrosDeTimeoutNoWifi(void);
    
    void ocorreuErroDeTimeoutNoWifi(void);


#ifdef	__cplusplus
}
#endif

#endif	/* FSM_ESP8266_H */

