/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ256DA210
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


/**
    Section: Includes
*/

#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"
#include "../PPS.h"
#include "../delay.h"
#include "p24FJ256DA210.h"

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void){
    ANSA = 0;   // all I/O digital
    ANSB = 0;   // all I/O digital
    ANSC = 0;   // all I/O digital
    ANSD = 0;   // all I/O digital
    ANSE = 0;   // all I/O digital
    ANSF = 0;   // all I/O digital
    ANSG = 0;   // all I/O digital

    AS3993_EN_SetLow();
    NCS_DESELECT();

    delay_us(100);
    
    _TRISC12 = 1;   //OSCI
    _TRISC15 = 0;   //OSCO
     
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

    _ANSG7   = 0;      //OPTO1 ANALOG DISABLE
    _ANSG6   = 0;      //OPTO2 ANALOG DISABLE
    _ANSB5   = 0;      //OPTO3 ANALOG DISABLE
    _ANSC13  = 0;      //OPTO4 ANALOG DISABLE
    _TRISG6  = 1;      //OPTO1 INPUT - SENSOR PORTÃO 1
    _TRISG7  = 1;      //OPTO2 INPUT - SENSOR PORTÃO 2
    _TRISB5  = 1;      //OPTO3 INPUT GP16 - CALAR ALARME
    _TRISC13 = 0;      //OPTO4 INPUT GP1 - SENBSOR DE VEICULO    

    _TRISG13 = 0;     //saida DIR

    _TRISB10 = 0;     //SAIDA SEL_BBA
   
    _TRISB12 = 0;     //SAIDA SEL B5-8
    _TRISC3 = 0;      //SAIDA SAI_4

    _TRISB15 = 0;     //SAIDA SEL A3-4
    _TRISC1 = 0;      //SAIDA SAI_6

    _TRISE0 = 0;      //SAIDA LED_A1
    _LATE0 = 0;      //SAIDA LED_A1
  
    _TRISE1 = 0;    //LED A2
    _LATE1 = 0;      //SAIDA LED_A2
    
    _TRISE2 = 0;      //SAIDA LED_A3
    _LATE2 = 0;      //SAIDA LED_A3
  
    _TRISE3 = 0;    //LED A4
    _LATE3 = 0;      //SAIDA LED_A4
   
    _TRISE4 = 0;      //SAIDA LED_A5
    _LATE4 = 0;      //SAIDA LED_A5
   
    _TRISE5 = 0;      //SAIDA LED_A6
    _LATE5 = 0;      //SAIDA LED_A6
   
    _TRISA1 = 0;      //SAIDA LED_A7
    _LATA1 = 0;      //SAIDA LED_A7
   
    _TRISA6 = 0;      //SAIDA LED_A8
    _LATA6 = 0;      //SAIDA LED_A8

    _TRISE8 = 0;      //SAIDA LED_TAG
    _LATE8 = 0;      //SAIDA LED_TAG
  
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
    _TRISF2 = 0;     //SAIDA GP2 - RESET FISICO MODULO ETHERNET
    _TRISA4 = 0;     //SAIDA GP3
    _TRISA5 = 1;     //ENTRADA GP4 - SENSOR ULTRASON VEICULOS
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
    _TRISC13 = 0;// O NET GP1 esta nesse pino tambem e o deixo como entrada para nao influenciar na operacao
    _TRISB4 = 0;//                          ALTERAR!!!!
   // _TRISB5 = 0;
    _TRISB2 = 0;
    _TRISB6 = 1;    // GP15 - 
    _TRISB14 = 1;// IRQ

    _TRISD8 = 0;//CLK

    _TRISF3 = 0;//MOSI
    _LATF3 = 0; // MOSI LOW

    _TRISF5 = 1;//MISO

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

