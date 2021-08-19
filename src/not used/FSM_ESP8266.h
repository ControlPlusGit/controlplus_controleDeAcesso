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

