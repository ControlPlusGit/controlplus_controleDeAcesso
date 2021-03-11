
#include <stdint.h>
#include <xc.h>
#include "bsp.h"
#include "pin_manager.h" // include all pin macros
#include "../delay.h"

BSP_OnboardLeds OnboardLeds;

BSP_OnboardDigitalInputs OnboardDigitalInputs;

BSP_OnboardRelays OnboardRelays;

BSP_RS485_Direction OnboardRs485Direction;
    
void BSP_setRelay(uint8_t num_relay, uint8_t state){
    
    switch(num_relay){
        case RELAY_1:
            if(state){
                SAI_5_SetHigh();
            }
            else{
                SAI_5_SetLow();
            } 
            break;
        case RELAY_2:
            if(state){
                SAI_1_SetHigh();
            }
            else{
                SAI_1_SetLow();
            } 
            break;
        case RELAY_3:
            if(state){
                SAI_6_SetHigh();
            }
            else{
                SAI_6_SetLow();
            }  
            break;
        case RELAY_4:
            if(state){
                SAI_2_SetHigh();
            }
            else{
                SAI_2_SetLow();
            }    
            break;
        case NUM_MAX_RELAYS:
            state ? SAI_5_SetHigh(): SAI_5_SetLow();
            state ? SAI_1_SetHigh(): SAI_1_SetLow();
            state ? SAI_6_SetHigh(): SAI_6_SetLow();
            state ? SAI_2_SetHigh(): SAI_2_SetLow();
            break;
    }
       
}

void BSP_setBuzzer(uint8_t state){
    if(state){
        SAI_3_SetHigh();
    }
    else{
        SAI_3_SetLow();
    }
}

void BSP_setLed(uint8_t numLed, uint8_t state){
    switch(numLed){
        case LED_D1:
            if(state){
                LED_A5_SetHigh();
            }
            else{
                LED_A5_SetLow();
            }
            break;
        case LED_D2:
            if(state){
                LED_A6_SetHigh();
            }
            else{
                LED_A6_SetLow();
            }
            break;
        case LED_D3:
            if(state){
                LED_A7_SetHigh();
            }
            else{
                LED_A7_SetLow();
            }
            break;
        case LED_D4:
            if(state){
                LED_A8_SetHigh();
            }
            else{
                LED_A8_SetLow();
            }
            break;
        case LED_D5:
            if(state){
                LED_A1_SetHigh();
            }
            else{
                LED_A1_SetLow();
            }
            break;
        case LED_D6:if(state){
                LED_A2_SetHigh();
            }
            else{
                LED_A2_SetLow();
            }
            
            break;
        case LED_D7:
            if(state){
                LED_A3_SetHigh();
            }
            else{
                LED_A3_SetLow();
            }
            break;
        case LED_D8:
            if(state){
                LED_A4_SetHigh();
            }
            else{
                LED_A4_SetLow();
            }
            break;
        case LED_D9:
            if(state){
                LED1_SetHigh();
            }
            else{
                LED1_SetLow();
            }
            break;
        case LED_D10:
            if(state){
                LED2_SetHigh();
            }
            else{
                LED2_SetLow();
            }
            break;
        case LED_D11:
            if(state){
                RIO4_SetHigh();
            }
            else{
                RIO4_SetLow();
            }
            break;
        case LED_D12:
            if(state){
                LIGA_PA_SetHigh();
            }
            else{
                LIGA_PA_SetLow();
            }
            break;
        case LED_D13:
            if(state){
                LED_TAG_SetHigh();
            }
            else{
                LED_TAG_SetLow();
            }
            break;
        case LED_D16:
            if(state){
                LED_ZIG_SetHigh();
            }
            else{
                LED_ZIG_SetLow();
            }
            break;   
        case NUM_MAX_LEDS:
            state ? LED_A5_SetHigh():LED_A5_SetLow();
            state ? LED_A6_SetHigh():LED_A6_SetLow();
            state ? LED_A7_SetHigh():LED_A7_SetLow();
            state ? LED_A8_SetHigh():LED_A8_SetLow();
            state ? LED_A1_SetHigh():LED_A1_SetLow();
            state ? LED_A2_SetHigh():LED_A2_SetLow();
            state ? LED_A3_SetHigh():LED_A3_SetLow();
            state ? LED_A4_SetHigh():LED_A4_SetLow();
            state ? LED1_SetHigh():LED1_SetLow();
            state ? LED2_SetHigh():LED2_SetLow();
            state ? RIO4_SetHigh():RIO4_SetLow();
            state ? LIGA_PA_SetHigh():LIGA_PA_SetLow();
            state ? LED_TAG_SetHigh():LED_TAG_SetLow();
            state ? LED_ZIG_SetHigh():LED_ZIG_SetLow();
            
            break;
    }
}

uint8_t BSP_readDigitalInput(uint8_t num_input){
    switch(num_input){
        case INPUT_1:
            if(OPTO1_GetValue()){
                delay_ms(100);
                if(OPTO1_GetValue()){
                    return OPTO1_GetValue();
                }
            }                
            break;
        case INPUT_2:
            if(OPTO2_GetValue()){
                delay_ms(100);
                if(OPTO2_GetValue()){
                    return OPTO2_GetValue();
                }
            }  
            break;
        default:
            return 0;
            break;
    }
    return 0;
}

void BSP_RS485_setDirection(uint8_t direction) {
    switch(direction){
        case RS485_INPUT:
            RS485_DIRECTION_SetLow();
            break;
        case RS485_OUTPUT:
            RS485_DIRECTION_SetHigh();
            break;
    }
}
 
