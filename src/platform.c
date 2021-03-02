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
/** @file
  * @brief Implementation of serial interface communication with AS3993.
  *
  * The file provides functions to initialize the uController and the board
  * for SPI communication with AS3993. The function writeReadAS3993() provides
  * communication functionality. The function writeReadAS3993Isr() reads 
  * interrupt status register and is only called from the ISR.
  * (no reentrant function necessary).
  * \n
  * For porting to another uController/board the functions in this file have to be
  * adapted.
  * \n\n
  *
  * @author Ulrich Herrmann
  * @author Bernhard Breinbauer
  */

#include "as3993_config.h"
#include "platform.h"
#include "delay.h"
#include "PPS.h"
#include "spi1.h"

/*------------------------------------------------------------------------- */
/** This function initialising the external interrupt for comunication with the
  * AS3993. \n
  * This function does not take or return a parameter.
  */
static void initExtInterrupt(void )
{
    u8 a;
    // initialize IRQ interrupt
    // source for interrupt is set up in board-corresponding initXXX function

    _INT1EP  = 0;       // on positive edge
    _INT1IP  = 6;       // high priority
    _INT1IF  = 0;       // clear pending interrupts
    for (a = 100; a; a--);  // delay
    _INT1IE = 1;
}

static void initFermi(void)
{
    //TRISA = 0xFFE5;
    //_TRISB4 = 1;    //MISO
    //_TRISB5 = 0;    //MOSI
    _TRISC12 = 1;   //OSCI
    _TRISC15 = 0;   //OSCO
 
     //TRISB = 0x5CC7;
    _TRISB0 = 1;    //debugger
    _TRISB1 = 1;    //debugger
    _TRISA3 = 1;    //CLSYS
    _TRISD8 = 0;    //CLK
    
    
    _TRISB7 = 1;    //UART1RX
    _TRISB8 = 0;    //UART1TX
    
    _TRISG2 = 1;    //USB D+
    _TRISG3 = 1;    //USB D-
    _TRISB2 = 0;    //EN
    _TRISB14 = 1;   //IRQ
    _TRISF8 = 0;    //NCS

    //TRISC = 0x00;

    _TRISG8 = 1;    //entrada AD

    _TRISD11 = 0;     //saida RS
    _LATD11 = 0;     

    _TRISD0 = 0;      //saida ELCD
    _LATD0 = 0;

    _TRISD6 = 0;     //SAIDA BD4
    _LATD6 = 0;

    _TRISD7 = 0;     //SAIDA BD5
    _LATD7 = 0;

    _TRISD13 = 0;     //saida BD6
    _LATD13 = 0;

    _TRISD12 = 0;     //saida BD7
    _LATD12 = 0;

    _TRISF12 = 0;
    _TRISD15 = 0;

    _TRISF4 = 0;
    _TRISD14 = 0;

    _ANSG7 = 0;       //OPTO1 ANALOG DISABLE
    _ANSG6 = 0;       //OPTO2 ANALOG DISABLE
    _TRISG6 = 1;      //OPTO1 INPUT
    _TRISG7 = 1;      //OPTO2 INPUT

    _TRISG13 = 0;     //saida DIR

    _TRISB10 = 0;     //SAIDA SEL_BBA
   
    _TRISB12 = 0;     //SAIDA SEL B5-8
    _TRISC3 = 0;      //SAIDA SAI_4

    _TRISB15 = 0;     //SAIDA SEL A3-4
    _TRISC1 = 0;      //SAIDA SAI_6

    _TRISE0 = 0;      //SAIDA LED_A1
    _LATE0 = 0;      //SAIDA LED_A1
    //
    _TRISE1 = 0;    //LED A2
    _LATE1 = 0;      //SAIDA LED_A2
    
    _TRISE2 = 0;      //SAIDA LED_A3
    _LATE2 = 0;      //SAIDA LED_A3
    //
    _TRISE3 = 0;    //LED A4
    _LATE3 = 0;      //SAIDA LED_A4
    //
    _TRISE4 = 0;      //SAIDA LED_A5
    _LATE4 = 0;      //SAIDA LED_A5
    //
    _TRISE5 = 0;      //SAIDA LED_A6
    _LATE5 = 0;      //SAIDA LED_A6
    //

    _TRISA1 = 0;      //SAIDA LED_A7
    _LATA1 = 0;      //SAIDA LED_A7
    //
    _TRISA6 = 0;      //SAIDA LED_A8
    _LATA6 = 0;      //SAIDA LED_A8

    _TRISE8 = 0;      //SAIDA LED_TAG
    _LATE8 = 0;      //SAIDA LED_TAG
    //
    _TRISE9 = 0;      //SAIDA LIGA_PA
    _LATE9 = 0;      //SAIDA LIGA_PA

    _LATB10 = 0;     //SAIDA SEL_BBA
    
    _LATB12 = 0;     //SAIDA SEL B5-8
    _LATC3 = 0;      //SAIDA SAI_4

    _LATB15 = 0;     //SAIDA SEL A3-4
    _LATC1 = 0;      //SAIDA SAI_6

    _TRISB11 = 0;     //SAIDA SEL A1-4
    _TRISC4 = 0;      //SAIDA SAI_3
   
    _TRISF13 = 0;     //SAIDA SEL B5-6
    _TRISE9 = 0;      //SAIDA LIGA_PA

    _LATB11 = 0;     //SAIDA SEL A1-4
    _LATC4 = 0;      //SAIDA SAI_3

    _LATF13 = 0;     //SAIDA SEL B5-6    

    //--------PIC24FJ256DA210------------
    _TRISB13 = 0;    //SAIDA SEL_A1-2

    _TRISG15 = 0;    //SAIDA SAI_1
    _TRISB3 = 0;     //SAIDA SAI_2
    _TRISC2 = 0;     //SAIDA SAI_4
    _TRISF5 = 0;     //SAIDA GP0
    _TRISF3 = 0;     //SAIDA GP1
    _TRISF2 = 0;     //SAIDA GP2
    _TRISA4 = 0;     //SAIDA GP3
    _TRISA5 = 0;     //SAIDA GP4
    _TRISA2 = 0;     //SAIDA GP5
    _TRISG12 = 0;    //SAIDA GP6
    _TRISA9 = 0;     //SAIDA GP7
    _TRISA0 = 0;     //SAIDA GP8
    _TRISC14 = 0;    //SAIDA GP9
    _TRISF0 = 0;     //SAIDA GP10
    _TRISF1 = 0;     //SAIDA GP11
    _TRISA1 = 0;     //SAIDA GP12
    _TRISD10 = 0;    //SAIDA GP13
    _TRISA6 = 0;     //SAIDA GP14
    _TRISA7 = 0;     //SAIDA GP15

    _TRISA10 = 0;    //SAIDA LED_ZIG
    _TRISG14 = 0;    //SAIDA RIO4
    _TRISG0 = 0;     //SAIDA LED0
    _TRISG1 = 0;     //SAIDA LED1

    _TRISG9 = 1;     //ENTRADA RX0
    _TRISB9 = 0;     //SAIDA TX0
    _TRISD9 = 1;     //ENTRADA RX2
    _TRISD5 = 0;     //SAIDA TX2
    _TRISD1 = 1;     //ENTRADA RX3
    _TRISD4 = 0;     //SAIDA TX3
  
 //configure SPI
    
    _TRISF8 = 0;//NCS
    _TRISC13 = 1;// O NET GP1 esta nesse pino tambem e o deixo como entrada para nao influenciar na operacao
    _TRISB4 = 0;//                          ALTERAR!!!!
    _TRISB5 = 0;
    _TRISB2 = 0;
    _TRISB6 = 0;
    _TRISB14 = 1;// IRQ

    _TRISD8 = 0;//CLK

    _TRISF3 = 0;//MOSI
    _LATF3 = 0; // MOSI LOW

    _TRISF5 = 1;//MISO
    //_LATF5 = 1; // MISO high

    OUT_PIN_PPS_RP2 = OUT_FN_PPS_SCK1OUT;   // CLK
    OUT_PIN_PPS_RP16 = OUT_FN_PPS_SDO1;     //MOSI
    IN_FN_PPS_SDI1 = IN_PIN_PPS_RP17;       //MISO

    // setup external interrupt source
    IN_FN_PPS_INT1 = IN_PIN_PPS_RP14;   // RP14 (RB14) for source INT1

    // setup UART pin for debugging
    OUT_PIN_PPS_RP8 = OUT_FN_PPS_U1TX;  // connect function U1TX to RP8
    _TRISB8 = 0;

    OUT_PIN_PPS_RP20 = OUT_FN_PPS_U2TX;  // connect function U2TX to RP8
    _TRISD5 = 0;


    OUT_PIN_PPS_RP25 = OUT_FN_PPS_U3TX;  // connect function U3TX to RP8
    _TRISD4 = 0;


    OUT_PIN_PPS_RP9 = OUT_FN_PPS_U4TX;  // connect function U0TX to RP8
    _TRISB9 = 0;
    IN_FN_PPS_U4RX = IN_PIN_PPS_RP27;
    
    _TRISG9 = 1;
    _TRISB7 = 1;
    _TRISD1 = 1;
    _TRISD9 = 1;
    _TRISG9 = 1;

    RPINR18 = 0x1F07;//TX1
    RPINR19 = 0x0004;//TX2
    RPINR17 = 0x1800;//TX3
    RPINR27 = 0x001B;//TX0

}

/*------------------------------------------------------------------------- */
void platformInit(void)
{
    // configure ports
    //AD1PCFG = 0xFFFF;   // all I/O digital
      // configure ports
    //AD1PCFGH = 0xFFFF;   // all I/O digital
    //AD1PCFGL = 0xFFFF;   // all I/O digital
    ANSA = 0;   // all I/O digital
    ANSB = 0;   // all I/O digital
    ANSC = 0;   // all I/O digital
    ANSD = 0;   // all I/O digital
    ANSE = 0;   // all I/O digital
    ANSF = 0;   // all I/O digital
    ANSG = 0;   // all I/O digital

    initFermi();

    EN(LOW);
    NCS_DESELECT();

    // Init external interrupt
    _INT1EP  = 0;       // on positive edge
    _INT1IP  = 6;       // high priority
    _INT1IF  = 0;       // clear pending interrupts    
    _INT1IE = 1;

    delay_us(100);
}

/*------------------------------------------------------------------------- */
void spiInit(void)
{
//    spiConfig_t spiconf;
//
//    // setup spi configuration
//    spiconf.frequency = 2000000ULL;
//    spiconf.instance = SPI1;
//    spiconf.clockPhase = 0;
//    spiconf.clockPolarity = 0;
//    spiconf.deviceId = 0;
////#if  FEMTO2 ||FEMTO2_1 //Gabriel
//    spiconf.frequency = 4000000ULL; // on FEMTO 4MHz are possible.
////#endif
//    spiInitialize(SYSCLK, &spiconf, 0);
}

/*------------------------------------------------------------------------- */
void writeReadAS3993( const u8* wbuf, u8 wlen, u8* rbuf, u8 rlen, u8 stopMode, u8 doStart )
{
#if AS3993DEBUG
    if (!ENABLE)
        LOG("******* attempting SPI with EN low! ******\n");
#endif
    if (doStart) NCS_SELECT();

    //spiTxRx(wbuf, 0, wlen);
    SPI1_Exchange8bitBuffer((uint8_t *)wbuf,(uint16_t)wlen,0);
    if (rlen)
        //spiTxRx(0, rbuf, rlen);
        SPI1_Exchange8bitBuffer(0,(uint16_t)rlen,rbuf);

    if (stopMode != STOP_NONE) NCS_DESELECT();
}

/*------------------------------------------------------------------------- */
void writeReadAS3993Isr( const u8* wbuf, u8 wlen, u8* rbuf, u8 rlen )
{
#if AS3993DEBUG
    if (!ENABLE)
        LOG("******* attempting SPI with EN low (ISR)! ******\n");
#endif

    NCS_SELECT();

    //spiTxRx(wbuf, 0, wlen);
    //spiTxRx(0, rbuf, rlen);
    SPI1_Exchange8bitBuffer((uint8_t *)wbuf,(uint16_t)wlen,0);
    SPI1_Exchange8bitBuffer(0,(uint16_t)rlen,rbuf);

    NCS_DESELECT();
}


void setPortDirect()
{
}

void setPortNormal()
{
}
