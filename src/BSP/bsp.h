/*
 * 
 * Arquivo: i2c3_driver.h
 * 
 * Control Plus - Controles e Sistemas
 * 
 * Autor: Eng. Vitor Alho
 * Data: Janeiro de 2021
 * 
 * Abaixo segue um exemplo de main.c, utilizando as funções da biblioteca para
 * acionamento dos dispositivos na placa de CPU

    //    Section: Included Files

    #include "mcc_generated_files/system.h"
    #include <libpic30.h>
    #include "bsp.h"
    #include "rfid_bsp.h"
    #include "mcc_generated_files/pin_manager.h"



    //    Main application 

    void test_IO_should_TurnOnAndOffEachOutput(void);

    void test_IO_should_CheckIfInputIsTurningOn(void);

    void test_IO_should_CheckIfBspLibIsWorking(void);

    int main(void)
    {
        // initialize the device
        SYSTEM_Initialize();

        while (1)
        {     
            //test_IO_should_TurnOnAndOffEachOutput();  
            //test_IO_should_CheckIfInputIsTurningOn();
            test_IO_should_CheckIfBspLibIsWorking();        
        }

        return 1;
    }

    void test_IO_should_TurnOnAndOffEachOutput(void) {
        // 
        // Saídas digitais para acionamento dos periféricos
        // 
        SAI_1_SetHigh();   // Controla RL2 - ligado = 1 / desligado = 0
        __delay_ms(200);
        SAI_1_SetLow();

        SAI_2_SetHigh();   // Aciona RL4 - ligado = 1 / desligado = 0
        __delay_ms(200);
        SAI_2_SetLow();

        SAI_3_SetHigh();   // Aciona o buzzer BZ1 - ligado = 1 / desligado = 0
        __delay_ms(200);
        SAI_3_SetLow();

        SAI_4_SetHigh();   // Sinal digital disponível no conector P1, pino 4
        __delay_ms(200);
        SAI_4_SetLow();

        SAI_5_SetHigh();   // Aciona RL1 - ligado = 1 / desligado = 0
        __delay_ms(200);
        SAI_5_SetLow();

        SAI_6_SetHigh();   // Aciona RL3 - ligado = 1 / desligado = 0
        __delay_ms(200);
        SAI_6_SetLow();

        SAI_7_SetHigh();   // Sinal digital disponível no conector P1, pino 7
        __delay_ms(200);
        SAI_7_SetLow();

        LED1_SetHigh();    // Aciona LED D9 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED1_SetLow();

        LED2_SetHigh();    // Aciona LED D10 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED2_SetLow();

        LED_A1_SetHigh();  // Aciona LED D5 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A1_SetLow();

        LED_A2_SetHigh();  // Aciona LED D6 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A2_SetLow();

        LED_A3_SetHigh();  // Aciona LED D7 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A3_SetLow();

        LED_A4_SetHigh();  // Aciona LED D8 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A4_SetLow();

        LED_A5_SetHigh();  // Aciona LED D1 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A5_SetLow();

        LED_A6_SetHigh();  // Aciona LED D2 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A6_SetLow();

        LED_A7_SetHigh();  // Aciona LED D3 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A7_SetLow();

        LED_A8_SetHigh();  // Aciona LED D4 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_A8_SetLow();

        LED_ZIG_SetHigh(); // Aciona LED D16 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LED_ZIG_SetLow();

        LED_TAG_SetHigh(); // Aciona LED D13 - ligado = 1 / desligado = 0
        __delay_ms(200); 
        LED_TAG_SetLow();

        RIO4_SetHigh();    // Aciona LED D11 - ligado = 1 / desligado = 0
        __delay_ms(200);
        RIO4_SetLow();

        LIGA_PA_SetHigh(); // Aciona LED D12 - ligado = 1 / desligado = 0
        __delay_ms(200);
        LIGA_PA_SetLow();

        //
        // Aqui são os sinais da placa de RFID, preciso verificar os sinais
        // de ON e OFF de cada periférico.
        //

        SEL_BBA_SetHigh(); // Ativa a seleção do MUX para grupos de antenas
                           // BBA = 1 -> Seleciona grupo de antenas de 1 a 4
                           // BBA = 0 -> Seleciona grupo de antenas de 5 a 8
        __delay_ms(200);

        SEL_A1_4_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // A1_4 = 1 -> Seleciona grupo de antenas de 1 a 2
                           // A1_4 = 0 -> Seleciona grupo de antenas de 3 a 4
        __delay_ms(200);

        SEL_A1_2_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // A1_2 = 1 -> Seleciona a antena 1
                           // A1_2 = 0 -> Seleciona a antena 2
        __delay_ms(200);

        SEL_A3_4_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // A3_4 = 1 -> Seleciona a antena 3
                           // A3_4 = 0 -> Seleciona a antena 4
        __delay_ms(200);

        SEL_B5_8_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // B5_8 = 1 -> Seleciona grupo de antenas de 5 a 6
                           // B5_8 = 0 -> Seleciona grupo de antenas de 7 a 8
        __delay_ms(200);

        SEL_B5_6_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // B5_6 = 1 -> Seleciona a antena 5
                           // B5_6 = 0 -> Seleciona a antena 6
        __delay_ms(200);

        SEL_B7_8_SetHigh();// Ativa a seleção do MUX para grupos de antenas
                           // B7_8 = 1 -> Seleciona a antena 7
                           // B7_8 = 0 -> Seleciona a antena 8
        __delay_ms(200);

        // 
        // Capacitores digitais para casar a impedância do circuito
        //
        //                         .--- L ---.
        //                         |         |
        //  in ----.----.----- L --.--C_len--.--.-----.-----.----- out
        //         |    |                       |     |     |
        //        C_in  L                     C_out   L     R
        //         |    |                       |     |     |
        //        ___  ___                     ___   ___   ___
        //         -    -                       -     -     -
        //         '    '                       '     '     '

        TUNE_CAP_1_SetHigh();// Ativa o enable do capacitor digital 1 (Cin)
                             // 1 -> capacitor selecionado
                             // 0 -> capacitor não selecionado
        __delay_ms(200);

        TUNE_CAP_2_SetHigh();// Ativa o enable do capacitor digital 2 (Cout)
                             // 1 -> capacitor selecionado
                             // 0 -> capacitor não selecionado
        __delay_ms(200);

        TUNE_CAP_3_SetHigh();// Ativa o enable do capacitor digital 3 (Clen)
                             // 1 -> capacitor selecionado
                             // 0 -> capacitor não selecionado
        __delay_ms(200);
    }

    void test_IO_should_CheckIfInputIsTurningOn(void){

        uint8_t aux = 0;

        if(!OPTO1_GetValue()){
            aux = 1;  // Set a breakpoint here.
        }
        else{
            if(!OPTO2_GetValue()){
                aux = 2;  // Set a breakpoint here.
            }
        }
    }

    void test_IO_should_CheckIfBspLibIsWorking(void){
        uint8_t aux=0;

        BSP_setRelay(RELAY_1,ON);    __delay_ms(200);
        BSP_setRelay(RELAY_1,OFF);

        BSP_setRelay(RELAY_2,ON);    __delay_ms(200);
        BSP_setRelay(RELAY_2,OFF);

        BSP_setRelay(RELAY_3,ON);    __delay_ms(200);
        BSP_setRelay(RELAY_3,OFF);

        BSP_setRelay(RELAY_4,ON);    __delay_ms(200);
        BSP_setRelay(RELAY_4,OFF);

        BSP_setBuzzer(ON);           __delay_ms(200);
        BSP_setBuzzer(OFF); 

        BSP_setLed(LED_D1,ON);  __delay_ms(200);
        BSP_setLed(LED_D1,OFF);

        BSP_setLed(LED_D2,ON);  __delay_ms(200);
        BSP_setLed(LED_D2,OFF);

        BSP_setLed(LED_D3,ON);  __delay_ms(200);
        BSP_setLed(LED_D3,OFF);

        BSP_setLed(LED_D4,ON);  __delay_ms(200);
        BSP_setLed(LED_D4,OFF);

        BSP_setLed(LED_D5,ON);  __delay_ms(200);
        BSP_setLed(LED_D5,OFF);

        BSP_setLed(LED_D6,ON);  __delay_ms(200);
        BSP_setLed(LED_D6,OFF);

        BSP_setLed(LED_D7,ON);  __delay_ms(200);
        BSP_setLed(LED_D7,OFF);

        BSP_setLed(LED_D8,ON);  __delay_ms(200);
        BSP_setLed(LED_D8,OFF);

        BSP_setLed(LED_D9,ON);  __delay_ms(200);
        BSP_setLed(LED_D9,OFF);

        BSP_setLed(LED_D10,ON); __delay_ms(200);
        BSP_setLed(LED_D10,OFF);

        BSP_setLed(LED_D11,ON); __delay_ms(200);
        BSP_setLed(LED_D11,OFF);

        BSP_setLed(LED_D12,ON); __delay_ms(200);
        BSP_setLed(LED_D12,OFF);

        BSP_setLed(LED_D13,ON); __delay_ms(200);
        BSP_setLed(LED_D13,OFF);

        BSP_setLed(LED_D16,ON); __delay_ms(200);
        BSP_setLed(LED_D16,OFF);

        if(!BSP_readDigitalInput(INPUT_1)){
            aux=1;
        }
        if(!BSP_readDigitalInput(INPUT_2)){
            aux=2;
        }
    }

    
//     End of File
    
 * 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __BSP_H__
#define	__BSP_H__

#include <stdint.h>
#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
    extern "C" {
#endif /* __cplusplus */
    
    #ifndef ON
        #define ON  1
    #endif

    #ifndef OFF
        #define OFF 0
    #endif
        
    typedef enum {
        LED_D1 = 1,
        LED_D2,
        LED_D3,
        LED_D4,
        LED_D5,
        LED_D6,
        LED_D7,
        LED_D8,
        LED_D9,
        LED_D10,
        LED_D11,
        LED_D12,
        LED_D13,
        LED_D16,
        NUM_MAX_LEDS
    }BSP_OnboardLeds;

    typedef enum {
    INPUT_1 = 1,
    INPUT_2,
    INPUT_3,
    INPUT_4,
    NUM_MAX_INPUTS
    }BSP_OnboardDigitalInputs;

    typedef enum {
    RELAY_1 = 1,
    RELAY_2,
    RELAY_3,
    RELAY_4,
    NUM_MAX_RELAYS
    }BSP_OnboardRelays;

    typedef enum {
    RS485_INPUT = 0,
    RS485_OUTPUT
    }BSP_RS485_Direction;

    extern BSP_OnboardLeds OnboardLeds;

    extern BSP_OnboardDigitalInputs OnboardDigitalInputs;

    extern BSP_OnboardRelays OnboardRelays;
        
    void BSP_setRelay(uint8_t num_relay, uint8_t state);
    
    void BSP_setBuzzer(uint8_t state);

    void BSP_setLed(uint8_t numLed, uint8_t state);
    
    void BSP_RS485_setDirection(uint8_t direction);
    
    uint8_t BSP_readDigitalInput(uint8_t num_input);
    
#ifdef	__cplusplus
    }
#endif /* __cplusplus */

#endif /* __BSP_H__ */

