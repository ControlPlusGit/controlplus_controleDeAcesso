/*
 *****************************************************************************
 * Copyright by ams AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */
/*
 *      PROJECT:   AS1130 MCU board firmware
 *      $Revision: $
 *      LANGUAGE:  ANSI C
 */

/*! \file
 *
 *  \author Wolfgang Reichart 
 *
 *  \brief uart driver implementation for PIC24FJ64
 *
 */
/*
******************************************************************************
* INCLUDES
******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "uart_driver.h"
#include <uart.h>
#include "string.h"
#include "delay.h"
//#include "FSM_DataHora.h"
#include "setup_usb.h"
#include "p24FJ256DA210.h"
#include <xc.h>
#include <p24Fxxxx.h>
/*
 *
 *
******************************************************************************
* LOCAL DEFINES
******************************************************************************
*/
int8_t uartRxNBytes( uint8_t *, uint16_t *);
int8_t uartRx2NBytes( uint8_t *, uint16_t *);
int8_t uartRx3NBytes( uint8_t *, uint16_t * numBytes);

extern char ComandoObtidoParaAEmpilhadeira;

extern volatile int operador_atual_outro;
extern int conta_recebe_operador;
extern void desliga_led_zig(void);
extern void  liga_led_zig(void);
void uart4Tx(uint8_t);
extern void poe_dado_XY(int,int,int);
extern uint8_t status_dir;
extern void desliga_dir();
extern void liga_dir();
extern void compararRespostaDoModemEmTempoReal(char *);

#ifdef UART_RECEIVE_ENABLED
//#define _U1RXInterrupt
#endif

extern unsigned char pacote_chegou[];
//extern unsigned char tags_entrou_corredor[];
//extern unsigned char tags_saiu_corredor[];
//extern unsigned char qt_tags_saiu;
//extern unsigned char qt_tags_entrou ;

extern unsigned char qt_pacote;
extern unsigned char cs_pacote;
extern unsigned char no_serie;
extern unsigned char pont_pac;
extern unsigned char qt_tags_portal;
extern unsigned char pacote_zerado;
extern unsigned char qt_pac_total;
extern uint8_t conta_tentativas_tx;
/*
******************************************************************************
* LOCAL VARIABLES
******************************************************************************
*/
#ifdef UART_RECEIVE_ENABLED
static uint8_t rxBuffer[UART_RX_BUFFER_SIZE];
uint8_t __attribute__((far)) rx2Buffer[UART_RX_BUFFER_SIZE];
uint8_t __attribute__((far)) rx3Buffer[UART_RX_BUFFER_SIZE];
uint8_t __attribute__((far)) rx4Buffer[UART_RX_BUFFER_SIZE];

static uint16_t rxCount;
static uint16_t rx2Count;
static uint16_t rx3Count;
static uint16_t rx4Count;

static uint8_t rxError;
/*
static uint8_t rx2Error;
static uint8_t rx3Error;
static uint8_t rx4Error;
 * */

extern struct EstruturaProtocolo Teste;

#endif


//******************************************************************************
//* GLOBAL FUNCTIONS
//******************************************************************************

char teste[20];
int contadorDeTeste;


int8_t uartTxInitialize (uint32_t sysclk, uint32_t baudrate, uint32_t* actbaudrate)
{
    uint32_t br1, br2;
    uint16_t breg;
    
    contadorDeTeste = 0;

    /* Disable UART for configuration */
    UART_WRITE_REG(MODE, 0x0);
    UART_WRITE_REG(STA, 0x0);

    /* Setup UART registers */
    /* equation according to the datasheet:
       (sysclk / (16 * baudrate)) - 1
     */
    breg = (sysclk / (16 * baudrate)) - 1;

    /* round up/down w/o using floating point maths */
    br1 = sysclk / (16 * (breg + 1));
    br2 = sysclk / (16 * (breg + 2));

    /* check which of the two values produce fewer error rate */
    if ((br1 - baudrate) > (baudrate - br2))
    {
        UART_WRITE_REG(BRG, breg + 1);
        if ( actbaudrate )
        {
            *actbaudrate = br2;
        }
    }
    else
    {
        UART_WRITE_REG(BRG, breg);
        if ( actbaudrate )
        {
            *actbaudrate = br1;
        }
    }

    //IEC4bits.U1ERIE = 1;//GILSON
    
    /* Enable UART */
    UART_WRITE_REG(MODE, UART_READ_REG(MODE) | 0x8100); 
    UART_WRITE_REG(STA, UART_READ_REG(STA) | 0x0400);
    
    IEC0bits.U1RXIE = 1;

    return 0;
}

#ifdef UART_RECEIVE_ENABLED
int8_t uartRxInitialize ()
{
    rxCount = 0;
    rxError = 0;
    /* clear receive buffer */
    U1RX_Clear_Intr_Status_Bit;
    while ( DataRdyUART1() )
    {
        ReadUART1();
    }

    return 0;
}
#endif

/*
int8_t uartInitialize (uint32_t sysclk, uint32_t baudrate, uint32_t* actbaudrate)
{
    uint32_t actbaud;
    int8_t result = uartTxInitialize(sysclk, baudrate, &actbaud);
    *actbaudrate = actbaud;
#ifdef UART_RECEIVE_ENABLED
    if (result == ERR_NONE)
    {
        result = uartRxInitialize();
    }
#endif
    return result;
}
 * */


//int8_t uartTxDeinitialize ()
//{
//    /* disable UART */
//    UART_WRITE_REG(MODE, 0x0);
//    UART_WRITE_REG(STA, 0x0);
//    U1STA = 0;
//
//    return ERR_NONE;
//}


//int8_t uartDeinitialize ()
//{
//    return uartTxDeinitialize();
//}

int8_t uart2TxInitialize (uint32_t sysclk, uint32_t baudrate, uint32_t* actbaudrate)
{
    uint32_t br1, br2;
    uint16_t breg;

    /* Disable UART for configuration */
    UART2_WRITE_REG(MODE, 0x0);
    UART2_WRITE_REG(STA, 0x0);

    IPC7bits.U2RXIP = 7;
    /* Setup UART registers */
    /* equation according to the datasheet:
       (sysclk / (16 * baudrate)) - 1
     */
    breg = (sysclk / (16 * baudrate)) - 1;

    /* round up/down w/o using floating point maths */
    br1 = sysclk / (16 * (breg + 1));
    br2 = sysclk / (16 * (breg + 2));

    /* check which of the two values produce fewer error rate */
    if ((br1 - baudrate) > (baudrate - br2))
    {
        UART2_WRITE_REG(BRG, breg + 1);
        if ( actbaudrate )
        {
            *actbaudrate = br2;
        }
    }
    else
    {
        UART2_WRITE_REG(BRG, breg);
        if ( actbaudrate )
        {
            *actbaudrate = br1;
        }
    }
    
    //IEC4bits.U2ERIE = 1;//GILSON

    /* Enable UART */
    UART2_WRITE_REG(MODE, UART2_READ_REG(MODE) | 0x8100);
    //UART_WRITE_REG(MODE, UART_READ_REG(MODE) | 0x8100);
    //UART_WRITE_REG(STA, UART_READ_REG(STA) | 0x2400);
    UART2_WRITE_REG(STA, UART2_READ_REG(STA) | 0x0400);
    IEC1bits.U2RXIE = 1;

    return 0;
}

int8_t uart3TxInitialize (uint32_t sysclk, uint32_t baudrate, uint32_t* actbaudrate)
{
    uint32_t br1, br2;
    uint16_t breg;

    /* Disable UART for configuration */
    UART3_WRITE_REG(MODE, 0x0);
    UART3_WRITE_REG(STA, 0x0);

    /* Setup UART registers */
    /* equation according to the datasheet:
       (sysclk / (16 * baudrate)) - 1
     */
    breg = (sysclk / (16 * baudrate)) - 1;

    /* round up/down w/o using floating point maths */
    br1 = sysclk / (16 * (breg + 1));
    br2 = sysclk / (16 * (breg + 2));

    /* check which of the two values produce fewer error rate */
    if ((br1 - baudrate) > (baudrate - br2))
    {
        UART3_WRITE_REG(BRG, breg + 1);
        if ( actbaudrate )
        {
            *actbaudrate = br2;
        }
    }
    else
    {
        UART3_WRITE_REG(BRG, breg);
        if ( actbaudrate )
        {
            *actbaudrate = br1;
        }
    }

    //IEC5bits.U3ERIE = 1;//GILSON

    /* Enable UART */
    UART3_WRITE_REG(MODE, UART3_READ_REG(MODE) | 0x8100);
    //UART_WRITE_REG(MODE, UART_READ_REG(MODE) | 0x8100);
    //UART_WRITE_REG(STA, UART_READ_REG(STA) | 0x2400);
    UART3_WRITE_REG(STA, UART3_READ_REG(STA) | 0x0400);
    IEC5bits.U3RXIE = 1;

    return 0;
}

int8_t uart4TxInitialize (uint32_t sysclk, uint32_t baudrate, uint32_t* actbaudrate)
{
    uint32_t br1, br2;
    uint16_t breg;

    /* Disable UART for configuration */
    UART4_WRITE_REG(MODE, 0x0);
    UART4_WRITE_REG(STA, 0x0);

    IPC22bits.U4TXIP = 7;
    /* Setup UART registers */
    /* equation according to the datasheet:
       (sysclk / (16 * baudrate)) - 1
     */
    breg = (sysclk / (16 * baudrate)) - 1;

    /* round up/down w/o using floating point maths */
    br1 = sysclk / (16 * (breg + 1));
    br2 = sysclk / (16 * (breg + 2));

    /* check which of the two values produce fewer error rate */
    if ((br1 - baudrate) > (baudrate - br2))
    {
        UART4_WRITE_REG(BRG, breg + 1);
        if ( actbaudrate )
        {
            *actbaudrate = br2;
        }
    }
    else
    {
        UART4_WRITE_REG(BRG, breg);
        if ( actbaudrate )
        {
            *actbaudrate = br1;
        }
    }
    /* Enable UART */
    UART4_WRITE_REG(MODE, UART4_READ_REG(MODE) | 0x8000);//8100
    //UART_WRITE_REG(MODE, UART_READ_REG(MODE) | 0x8100);
    //UART_WRITE_REG(STA, UART_READ_REG(STA) | 0x2400);
    UART4_WRITE_REG(STA, UART4_READ_REG(STA) | 0x0400);
    //UART4_WRITE_REG(STA, UART4_READ_REG(STA) | 0x0400);
    //IEC0bits.U1RXIE = 1;
    IEC5bits.U4RXIE = 1;

    return 0;
}

void uart1Tx (uint8_t dado){
    U1TXREG = dado;
    //while( (U1STA & 0x0100) );
    while( (U1STA & 0x0100) == 0);
}

void uart2Tx (uint8_t dado){
    U2TXREG = dado;
    //while( (U2STA & 0x0100) );
    while( (U2STA & 0x0200) );
}


void uart3Tx (uint8_t dado){
    U3TXREG = dado;
    //while( (U3STA & 0x0100) );
    while( (U3STA & 0x0200) );
}

void uart4Tx (uint8_t dado){
    U4TXREG = dado;
    //while( (U4STA & 0x0100) ){
    while( (U4STA & 0x0200) ){

    };
}


uint16_t uartRx2NumBytesAvailable ()
{
    uint16_t num;
    DisableIntU2RX;
    num = rx2Count;
    EnableIntU2RX;
    return num;
}


uint16_t uartRx3NumBytesAvailable ()
{
    uint16_t num;
    DisableIntU3RX;
    num = rx3Count;
    EnableIntU3RX;
    return num;
}

uint16_t uartRx4NumBytesAvailable ()
{
    uint16_t num;
    DisableIntU4RX;
    num = rx4Count;
    EnableIntU4RX;
    return num;
}


int8_t uartRxNBytes ( uint8_t * buffer, uint16_t * numBytes )
{
    uint16_t maxCopy = *numBytes;
    DisableIntU4RX;
    if ( rxCount <= maxCopy )
    { /* copy whole received data into buffer */
	*numBytes = rxCount;
	memcpy( buffer, rxBuffer, rxCount );
	rxCount = 0; /* reset receive buffer */
    }
    else /* copy only the first *numBytes to buffer  */
    {
	memcpy( buffer, rxBuffer, maxCopy );
	rxCount -= maxCopy; /* remove the copied bytes from internal buffer */
	memmove( rxBuffer, rxBuffer + maxCopy, rxCount );
    }
    EnableIntU4RX;
    return 0;
}

int8_t uartRx2NBytes ( uint8_t * buffer, uint16_t * numBytes )
{
    uint16_t maxCopy = *numBytes;
    DisableIntU2RX;
    if ( rx2Count <= maxCopy )
    { /* copy whole received data into buffer */
	*numBytes = rx2Count;
	//memcpy( buffer, rx2Buffer, rx2Count );
	rx2Count = 0; /* reset receive buffer */
    }
    else /* copy only the first *numBytes to buffer  */
    {
	//memcpy( buffer, rx2Buffer, maxCopy );
	rx2Count -= maxCopy; /* remove the copied bytes from internal buffer */
	//memmove( rx2Buffer, rx2Buffer + maxCopy, rx2Count );
    }
    EnableIntU2RX;
    return 0;
}

void LimpaBufferRX3 (void){
    //DisableIntU3RX;
    memset(rx3Buffer, 0, UART_RX_BUFFER_SIZE);
    rx3Count = 0; /* reset receive buffer */
    //EnableIntU3RX;

}

int8_t uartRx3NBytes ( uint8_t * buffer, uint16_t * numBytes )
{
    uint16_t maxCopy = *numBytes;
    DisableIntU3RX;
    if ( rx3Count <= maxCopy )
    { /* copy whole received data into buffer */
	*numBytes = rx3Count;
	memcpy( buffer, rx3Buffer, rx3Count );
	rx3Count = 0; /* reset receive buffer */
    }
    else /* copy only the first *numBytes to buffer  */
    {
	memcpy( buffer, rx3Buffer, maxCopy );
	rx3Count -= maxCopy; /* remove the copied bytes from internal buffer */
	memmove( rx3Buffer, rx3Buffer + maxCopy, rx3Count );
    }
    EnableIntU3RX;
    //IEC5bits.U3ERIE = 1;
    return 0;
}

int8_t uartRx4NBytes ( uint8_t * buffer, uint16_t * numBytes )
{
    uint16_t maxCopy = *numBytes;
    DisableIntU4RX;
    if ( rx4Count <= maxCopy )
    { /* copy whole received data into buffer */
	*numBytes = rx4Count;
	memcpy( buffer, rx4Buffer, rx4Count );
	rx4Count = 0; /* reset receive buffer */
    }
    else /* copy only the first *numBytes to buffer  */
    {
	memcpy( buffer, rx4Buffer, maxCopy );
	rx4Count -= maxCopy; /* remove the copied bytes from internal buffer */
	memmove( rx4Buffer, rx4Buffer + maxCopy, rx4Count );
    }
    EnableIntU4RX;
    return 0;
}




/*
int8_t uartTxByte ( uint8_t dat )
{
    uartTx( dat );
    return ERR_NONE;
}
*/
/*
int8_t uartTxString ( const char * text )
{
    while ( *text != '\0' )
    {
        uartTx( *text );
        ++text;
    }
    return ERR_NONE;
}
*/
/*
int8_t uartTxNBytes ( const uint8_t * buffer, uint16_t length )
{
    while ( length-- )
    {
        uartTx( *buffer );
        ++buffer;
    }

    return ERR_NONE;
}
 * */


//#define UART_RECEIVE_ENABLED
#ifdef UART_RECEIVE_ENABLED

uint16_t uartRxNumBytesAvailable ()
{
    uint16_t num;
    DisableIntU4RX;//1
    num = rxCount;
    EnableIntU4RX;//1
    return num;
}

/*
int8_t uartRxNBytes ( uint8_t * buffer, uint16_t * numBytes )
{
    uint16_t maxCopy = *numBytes;
    DisableIntU1RX;
    if ( rxCount <= maxCopy )
    {  copy whole received data into buffer
	*numBytes = rxCount;
	memcpy( buffer, rxBuffer, rxCount );
	rxCount = 0;  reset receive buffer 
    }
    else  copy only the first *numBytes to buffer 
    {
	memcpy( buffer, rxBuffer, maxCopy ); 
	rxCount -= maxCopy;  remove the copied bytes from internal buffer 
	memmove( rxBuffer, rxBuffer + maxCopy, rxCount );
    }
    EnableIntU1RX;
    return ERR_NONE;
}
*/

/*
void _U4RXInterrupt (void)
{
    U1RX_Clear_Intr_Status_Bit;

    while(DataRdyUART1())
    {
        if (rxCount >= UART_RX_BUFFER_SIZE || U1STAbits.OERR)
        {
            rxError = ERR_NOMEM;
            U1STAbits.OERR = 0;
            break;
        }
        contadorRX
        rxBuffer[rxCount] = ReadUART1();
        rxCount++;
        contadorParaEnviarArrayXbee = 0;
    }
}

 * */
#endif

void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt (void){
    //int data;     //LUCIANO: Variavel declarada e nao utilizada. Eliminei um warning.

    IFS4bits.U1ERIF = 0;

    if (U1STAbits.OERR)
        U1STAbits.OERR = 0;

    if (U1STAbits.FERR)
        U1STAbits.FERR = 0;

    if (U1STAbits.PERR)
        U1STAbits.PERR = 0;


    //data = ReadUART1();// leio para tentar tratar os erros.

}


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void){    
    
    U1RX_Clear_Intr_Status_Bit;
    
    int EsperaChegadaDeDados = 500;    
    while(EsperaChegadaDeDados != 0){
        EsperaChegadaDeDados = EsperaChegadaDeDados - 1;
    
        if (U1STAbits.OERR || U1STAbits.FERR){
                if (U1STAbits.OERR)
                    U1STAbits.OERR = 0;

                if (U1STAbits.FERR)
                    U1STAbits.FERR = 0;
        } 
        else {
            while(DataRdyUART1()){

                char Dado;    
                Dado = ReadUART1();
                EsperaChegadaDeDados = 500;                
                //uart3Tx(Dado);                                                
            }
        }
    }    
}
//char bufferRxEthernet[TAMANHO_BUFFER_ISR_UART2];

char __attribute__((far)) bufferRxEthernet[TAMANHO_BUFFER_ISR_UART2];

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt (void){ // Porta usada para receber dados de ETH
 
    //U2RX_Clear_Intr_Status_Bit;
    //IFS1bits.U2RXIF = 0;
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes
    IFS1bits.U2RXIF = 0;
    IEC1bits.U2RXIE = 0;
    
    IEC0bits.T1IE = 0;
    IEC0bits.T2IE = 0;
    IEC0bits.T3IE = 0;
    
    IEC3bits.RTCIE = 0;
    U2STAbits.OERR = 0;
    U2STAbits.FERR = 0;
    U2STAbits.PERR = 0;
    
    
    unsigned int posicao = 0;
    unsigned int esperaChegadaDeDados = 0;
    unsigned char dado;
    
    esperaChegadaDeDados = 0;
    while(esperaChegadaDeDados < 500){
        esperaChegadaDeDados = esperaChegadaDeDados + 1;
        while(U2STAbits.URXDA == 1){ // enquanto houver dados disponiveis
            U2STAbits.URXDA = 0;
            dado = U2RXREG;
            bufferRxEthernet[posicao] = dado;
            posicao = posicao + 1;
            esperaChegadaDeDados = 0;
        }    
    }
    
    IEC0bits.T1IE = 1;
    IEC0bits.T2IE = 1;
    IEC0bits.T3IE = 1;
    
    IEC1bits.U2RXIE = 1;
    
}

void __attribute__((interrupt, no_auto_psv)) _U3ErrInterrupt (void){
    int data;

    IFS5bits.U3ERIF = 0;

    if (U3STAbits.OERR)
        U3STAbits.OERR = 0;

    if (U3STAbits.FERR)
        U3STAbits.FERR = 0;

    if (U3STAbits.PERR)
        U3STAbits.PERR = 0;


    data = ReadUART3();// leio para tentar tratar os erros.

}

char bufferInterrupcaoUART3[TAMANHO_BUFFER_COMANDOS_USB];

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt (void){ //Porta usada para receber dados da USB
    
    U3RX_Clear_Intr_Status_Bit;
    int EsperaChegadaDeDados = 500;   
    int posicaoBufferUART3=0;    
     
    while(EsperaChegadaDeDados != 0){
        EsperaChegadaDeDados = EsperaChegadaDeDados - 1;
    
        if (U3STAbits.OERR || U3STAbits.FERR){
                if (U3STAbits.OERR)
                    U3STAbits.OERR = 0;

                if (U3STAbits.FERR)
                    U3STAbits.FERR = 0;

        } else {
            //if(DataRdyUART3()){
            while(DataRdyUART3()){

                char Dado;
   
                Dado = ReadUART3();
                EsperaChegadaDeDados = 500; 
                //if(Dado != 0){
                    if(posicaoBufferUART3 < TAMANHO_BUFFER_COMANDOS_USB-1){
                        bufferRxUSB[posicaoBufferUART3] = Dado;
                        posicaoBufferUART3++;
                    }
                    else{
                        posicaoBufferUART3 = 0;
                    }
                //}
            }
        }
    }
    bufferRxUSB[posicaoBufferUART3] = 0;
    posicaoBufferUART3 = 0;
}

extern int ResultadoProtocolo;

char __attribute__((far)) bufferInterrupcaoUART4[TAMANHO_BUFFER_ISR_UART4];



void __attribute__((interrupt, no_auto_psv)) _U4RXInterrupt (void){ // Wifi
    U4RX_Clear_Intr_Status_Bit;
    unsigned int EsperaChegadaDeDados;
    int posicaoBufferUART4=0;
    int i=0; 
    
    EsperaChegadaDeDados = 500;
    
    INTCON1bits.NSTDIS = 1; //habilita o aninhamento de interrupcoes   
    
    while(EsperaChegadaDeDados != 0){
        EsperaChegadaDeDados = EsperaChegadaDeDados - 1;
      
        while(DataRdyUART4()){
      
            unsigned char Dado;  //unsigned int Dado;
            if ((U4STAbits.OERR) || (U4STAbits.FERR)){
                if (U4STAbits.OERR)U4STAbits.OERR = 0;
                if (U4STAbits.FERR)U4STAbits.FERR = 0;
                Dado = ReadUART4();
                                
            } else {
                Dado = ReadUART4();
                EsperaChegadaDeDados = 500;
                if(Dado != 0){
                    if(posicaoBufferUART4 < TAMANHO_BUFFER_ISR_UART4-1){
                        bufferInterrupcaoUART4[posicaoBufferUART4] = Dado;
                        posicaoBufferUART4++;
                    }
                    else{
                        bufferInterrupcaoUART4[posicaoBufferUART4] = 0;
                    }      
                }
            }
        }     
    }
    
    bufferInterrupcaoUART4[posicaoBufferUART4] = 0;
    //posicaoBufferUART4=0;
    
    i=0;
    if(debugInterfaceWifi || debugInterfaceWifi_Silent){        
        while(bufferInterrupcaoUART4[i] != 0){
            uart3Tx(bufferInterrupcaoUART4[i]);
            //bufferInterrupcaoUART4[i] = 0;
            i++;
        }         
    }
}

void cleanRX4InterruptBuffer(void){
    int i=0;
    for(i=0;i<sizeof(bufferInterrupcaoUART4);i++){
        bufferInterrupcaoUART4[i] = 0;
    }
}


void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt (void){
    char Dado=0;
    //Dado = trabalhaNaInterrupcaoDeWifi();
    //uart4Tx(Dado);
    U4TXREG = Dado;
    __asm("NOP");
}

