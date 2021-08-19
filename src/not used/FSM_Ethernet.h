/* 
 * File:   FSM_Ethernet.h
 * Author: Vitor
 *
 * Created on 11 de Fevereiro de 2020, 14:29
 */

#ifndef FSM_ETHERNET_H
#define	FSM_ETHERNET_H

#ifdef	__cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUN��O: escreverMensagemEthernet
// PAR�METROS: char *data
// UTILIZADA EM: executaMaquinaDeEstados_EventosDeParada e executaMaquinaDeEstados_DataHora
// FUN��O: escreve uma string na porta serial 2 at� que encontre o caractere nulo '\0'
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void escreverMensagemEthernet(char *data);
    
    void escreverMensagemUSB(char *data);
    
    void escreverMensagemWifi(char *data);
    
    void recebeDadosESP8266(int lenght);
    
    void iniciaESP8266(void);
        
    void incrementaContadorDePerformance(void);
    
    void escreveMensagemESP8266(char *data);

    unsigned long long retornaValorContadorDePerformance(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FSM_ETHERNET_H */

