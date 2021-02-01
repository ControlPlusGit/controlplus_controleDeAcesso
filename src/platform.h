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
/*! \file
 *
 *  \author Bernhard Breinbauer
 *
 *   \brief This file provides platform (board) specific macros and declarations
 *
 *   Contains configuration macros which are used throughout the code base,
 *   to enable/disable board specific features.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/
//#include <p24Fxxxx.h>
#include "p24FJ256DA210.h"
#include "Compiler.h"
#include "global.h"
#include "as3993_config.h"


/*
******************************************************************************
* DEFINES
******************************************************************************
*/
/** define for stopMode parameter of writeReadAS3993() */
#define STOP_NONE               0
/** define for stopMode parameter of writeReadAS3993() */
#define STOP_SGL                1
/** define for stopMode parameter of writeReadAS3993() */
#define STOP_CONT               2

/** map as3993Isr to _INT1Interrupt */
#define as3993Isr _INT1Interrupt

/*! map timer2Isr to _T3Interrupt */
#define timer3Isr _T3Interrupt
#define timer2Isr _T2Interrupt


/** Macro for enable external IRQ */
#define ENEXTIRQ()                _INT1IE = 1;

/** Macro for disable external IRQ */
#define DISEXTIRQ()               _INT1IE = 0

/** Macro for clearing external IRQ flag*/
#define CLREXTIRQ()               _INT1IF = 0



/** Macro for setting enable pin */
#define EN(x)                     ENABLE=(x)

/** Macro for setting DCDC on/off */
#define DCDC(x)                   DCDCPIN=(x)

/** Macro for setting PA on/off */
//#define EN_PA(x)                  EN_PAPIN(x)

/** Macro for setting NCS pin, serial enable line */
#define NCS(x)                    NCSPIN=(x)
/** Macro for activating AS3993 for SPI communication */
#define NCS_SELECT()              NCS(0)
/** Macro for deactivating AS3993 for SPI communication */
#define NCS_DESELECT()            NCS(1)

#ifdef TUNER
#define SEN_TUNER_CIN(x)          //SEN_CINPIN(x)
#define SEN_TUNER_CLEN(x)         //SEN_CLENPIN(x)
#define SEN_TUNER_COUT(x)         //SEN_COUTPIN(x)
#endif

/** Definition for the MCU Status LED */
//#define MCULED(x)                 MCULEDPIN(x)

/** Definition of the general status LEDs */
#define NUMLEDS                   BOARD_NUMLEDS
//#define LED1(x)                   LED1PIN(x)
//#define LED2(x)                   LED2PIN(x)
//#define LED3(x)                   LED3PIN(x)
//#define LED4(x)                   LED4PIN(x)

#define LEDON                     0
#define LEDOFF                    1

/*
//definition of test points for debugging
#if EVALBOARD
#define TP1(x)  _LATB10=(x);
#elif FERMI
#define TP1(x)  _LATB4=(x);
#elif  FEMTO2 || FEMTO2_1
#define TP1(x)  _LATB4=(x);
#elif MEGA
#define TP1(x)  _LATF1=(x);
#elif RADON
// not available :#define TP1(x)  _LATF1=(x);
#endif
*/

/*
******************************************************************************
* GLOBAL FUNCTIONS
******************************************************************************
*/
/*------------------------------------------------------------------------- */
/** This function initializes uController I/O ports for the configured board
  *
  * This function does not take or return a parameter.
  */
void platformInit(void);

/*------------------------------------------------------------------------- */
/** This function initializes SPI communication.
  *
  * This function does not take or return a parameter.
  */
void spiInit(void);

/*------------------------------------------------------------------------- */
/** This function talks with the AS3993 chip.
  */
void writeReadAS3993( const u8* wbuf, u8 wlen, u8* rbuf, u8 rlen, u8 stopMode, u8 doStart );

/** This function talks with the AS3993 chip from ISR.
  */
void writeReadAS3993Isr( const u8 *wbuf, u8 wlen, u8* rbuf, u8 rlen );

/*------------------------------------------------------------------------- */
/** \attention Do not use, not implemented.
  *  This function sets the interface to the AS3993 for accessing it via
  * direct mode. 
  */
void setPortDirect();

/*------------------------------------------------------------------------- */
/** \attention Do not use, not implemented.
  *  This function sets the interface to the AS3993 for accessing it via
  * normal SPI mode using writeReadAS3993()
  */
void setPortNormal();

//marte
void sel_antena (int);
void sel_cap_cin(int);
void sel_cap_cout(int);
void sel_cap_clen(int);
void desliga_saida_pa (void);
void liga_saida_pa (void);
void ld_pa (int);
void antena_ok (unsigned char);
void auto_sintonia (void);

/*
******************************************************************************
* INTERNAL DEFINES
* Not to be used directly, use the macros at the top of this file
******************************************************************************
*/

#ifdef FERMI
/** Definition for the serial enable pin */
#define NCSPIN                    _LATF8 //_LATB15
/** Definition for the Direct data mode Pin*/

/** Definition for the enable pin */
#define ENABLE                    _LATB2 //_LATB13
/** Definition for the PA enable Pin, this is a dummy pin as the
 * fermi reader pa is always enabled  */

//----------------------- novo -----------------------------------------
    #define SAIDA_RS(x)                 _LATD11=(x)     //SAIDA RS
    #define SAIDA_ELCD(x)               _LATD0=(x)      //SAIDA ELCD
    #define SAIDA_BD4(x)                _LATD6=(x)      //SAIDA BD4
    #define SAIDA_BD5(x)                _LATD7=(x)      //SAIDA BD5
    #define SAIDA_BD6(x)                _LATD13=(x)     //SAIDA BD6
    #define SAIDA_BD7(x)                _LATD12=(x)     //SAIDA BD7
    #define SAIDA_DIR(x)                _LATG13=(x)     //SAIDA DIR

    #define LED_A1(x)                   _LATE0=(x)      //SAIDA LED_A1
    #define LED_A2(x)                   _LATE1=(x)      //SAIDA LED A2
    #define LED_A3(x)                   _LATE2=(x)      //SAIDA LED A3
    #define LED_A4(x)                   _LATE3=(x)      //SAIDA LED_A4
    #define LED_A5(x)                   _LATE4=(x)      //SAIDA LED A5
    #define LED_A6(x)                   _LATE5=(x)      //SAIDA LED A6

    #define LED_A7(x)                   _LATA1=(x)      //SAIDA LED A7
    #define LED_A8(x)                   _LATA6=(x)      //SAIDA LED A8
    //Definicoes para placas anterioes a 7.15
    //#define LED_A7(x)                   _LATD3=(x)      //SAIDA LED A7
    //#define LED_A8(x)                   _LATD2=(x)      //SAIDA LED A8

    #define LED_TAG(x)                  _LATE8=(x)      //SAIDA LED TAG
    #define LIGA_PA(x)                  _LATE9=(x)      //SAIDA LIGA PA

    #define SEL_BBA(x)                  _LATB10=(x)     //SAIDA SEL_BBA
    #define SEL_A1_4(x)                 _LATB11=(x)     //SAIDA SEL_A1-4
    #define SEL_B5_8(x)                 _LATB12=(x)     //SAIDA SEL_B5-8
    #define SEL_A1_2(x)                 _LATB13=(x)     //SAIDA SEL_A1-2
    #define SEL_A3_4(x)                 _LATB15=(x)     //SAIDA SEL_A3-4
    #define SEL_B5_6(x)                 _LATF13=(x)     //SAIDA SEL_B5-6
    #define SEL_B7_8(x)                 _LATF12=(x)     //SAIDA SEL_B7-8
    #define TUNE_CAP3(x)                _LATF4=(x)      //SAIDA TUNE_CAP3

    #define SAI_1(x)                    _LATG15=(x)     //SAIDA SAI_1
    #define SAI_2(x)                    _LATB3=(x)      //SAIDA SAI_2
    #define SAI_3(x)                    _LATC4=(x)      //SAIDA SAI_3
    #define SAI_4(x)                    _LATC3=(x)      //SAIDA SAI_4
    #define SAI_5(x)                    _LATC2=(x)      //SAIDA SAI_5
    #define SAI_6(x)                    _LATC1=(x)      //SAIDA SAI_6
    #define SAI_7(x)                    _LATB6=(x)      //SAIDA SAI_6
    #define TUNE_CAP1(x)                _LATD15=(x)     //SAIDA TUNE_CAP1
    #define TUNE_CAP2(x)                _LATD14=(x)     //SAIDA TUNE_CAP2

    #define GP_0(x)                     _LATB4=(x)      //SAIDA GP_0
    #define GP_1(x)                     _LATC13=(x)      //SAIDA GP_1
    #define GP_2(x)                     _LATF2=(x)      //SAIDA GP_2
    #define GP_3(x)                     _LATA4=(x)      //SAIDA GP_3
    #define GP_4(x)                     _LATA5=(x)      //SAIDA GP_4
    #define GP_5(x)                     _LATA2=(x)      //SAIDA GP_5
    #define GP_6(x)                     _LATG12=(x)      //SAIDA GP_6
    #define GP_7(x)                     _LATA9=(x)      //SAIDA GP_7
    #define GP_8(x)                     _LATA0=(x)      //SAIDA GP_8
    #define GP_9(x)                     _LATC14=(x)      //SAIDA GP_9
    #define GP_10(x)                     _LATF0=(x)      //SAIDA GP_10
    #define GP_11(x)                     _LATF1=(x)      //SAIDA GP_11
    #define GP_12(x)                     _LATA1=(x)      //SAIDA GP_12
    #define GP_13(x)                     _LATD10=(x)      //SAIDA GP_13
    #define GP_14(x)                     _LATA6=(x)      //SAIDA GP_14
    #define GP_15(x)                     _LATA7=(x)      //SAIDA GP_15
    #define GP_16(x)                     _LATB5=(x)      //SAIDA GP_16

    #define LED_ZIG(x)                   _LATA10=(x)     //SAIDA LED_ZIG
    #define LED_WIFI                     _LATA10
    #define LED_WF(x)                    _LATG1=(x)//_LATG14=(x)     //SAIDA RIO4
    #define LED_3G(x)                    _LATG14=(x)//_LATG0=(x)      //SAIDA LED0
    #define LED_GPS(x)                   _LATG0=(x)//_LATG1=(x)      //SAIDA LED1

//----------------------------------------------------------------------


#define PA_ON                     HIGH
#define PA_OFF                    LOW

#endif


#endif /* PLATFORM_H_ */
