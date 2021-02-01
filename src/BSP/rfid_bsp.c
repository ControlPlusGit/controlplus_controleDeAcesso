
#include <stdint.h>
#include <xc.h>
#include "pin_manager.h"
#include "rfid_bsp.h"

#define SEL_BBA(x) if(x){SEL_BBA_SetHigh();}else{SEL_BBA_SetLow();}

#define SEL_A1_4(x) if(x){SEL_A1_4_SetHigh();}else{SEL_A1_4_SetLow();}
#define SEL_A1_2(x) if(x){SEL_A1_2_SetHigh();}else{SEL_A1_2_SetLow();}
#define SEL_A3_4(x) if(x){SEL_A3_4_SetHigh();}else{SEL_A3_4_SetLow();}

#define SEL_B5_8(x) if(x){SEL_B5_8_SetHigh();}else{SEL_B5_8_SetLow();}
#define SEL_B5_6(x) if(x){SEL_B5_6_SetHigh();}else{SEL_B5_6_SetLow();}
#define SEL_B7_8(x) if(x){SEL_B7_8_SetHigh();}else{SEL_B7_8_SetLow();}

BSP_RFID_Status BSP_RFID_status;

BSP_RFID_OnboardDigitalCapacitors OnboardDigitalCapacitors;

static void BSP_RFID_selectDigitalCapacitor(uint8_t num_capacitor){
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
    switch(num_capacitor){
        case DIGITAL_CAPACITOR_1: // Cin            
            TUNE_CAP_1_SetHigh();
            TUNE_CAP_2_SetLow();
            TUNE_CAP_3_SetLow();
            break;
        case DIGITAL_CAPACITOR_2: // Cout          
            TUNE_CAP_1_SetLow();
            TUNE_CAP_2_SetHigh();
            TUNE_CAP_3_SetLow();           
            break;
        case DIGITAL_CAPACITOR_3: // Clen
            TUNE_CAP_1_SetLow();
            TUNE_CAP_2_SetLow(); 
            TUNE_CAP_3_SetHigh();
            break;
    }
}

BSP_RFID_Status BSP_RFID_selectAntenna(uint8_t num_antenna){
    switch (num_antenna)
    {
            case 1:                         //Seleciona a antena 1
                SEL_BBA(1);                 //sel. grupo 1-4
                SEL_A1_4(1);                //sel. 1-2
                SEL_A1_2(1);                //sel. A1
            break;
            case 2:                         //Seleciona a antena 2
                SEL_BBA(1);                 //sel. grupo 1-4
                SEL_A1_4(1);                //sel. 1-2
                SEL_A1_2(0);                //sel. A2
            break;
            case 3:                         //Seleciona a antena 3
                SEL_BBA(1);                 //sel. grupo 1-4
                SEL_A1_4(0);                //sel. 3-4
                SEL_A3_4(1);                //sel. A3
            break;
            case 4:                         //Seleciona a antena 4
                SEL_BBA(1);                 //sel. grupo 1-4
                SEL_A1_4(0);                //sel. 3-4
                SEL_A3_4(0);                //sel. A4
            break;
            case 5:                         //Seleciona a antena 5
                SEL_BBA(0);                 //sel. grupo 5-8
                SEL_B5_8(1);                //sel. 5-6
                SEL_B5_6(1);                //sel. A5
            break;
            case 6:                         //Seleciona a antena 6
                SEL_BBA(0);                 //sel. grupo 5-8
                SEL_B5_8(1);                //sel. 5-6
                SEL_B5_6(0);                //sel. A6
            break;
            case 7:                         //Seleciona a antena 7
                SEL_BBA(0);                 //sel. grupo 5-8
                SEL_B5_8(0);                //sel. 7-8
                SEL_B7_8(1);                //sel. A7
            break;
            case 8:                         //Seleciona a antena 8
                SEL_BBA(0);                 //sel. grupo 5-8
                SEL_B5_8(0);                //sel. 7-8
                SEL_B7_8(0);                //sel. A8
            break;
            default:     
                return BSP_RFID_ERROR;
                break;
    }
    return BSP_RFID_OK;
}

void BSP_RFID_selectDigitalCapacitor_Cin(void){
    BSP_RFID_selectDigitalCapacitor(DIGITAL_CAPACITOR_1);
}

void BSP_RFID_selectDigitalCapacitor_Clen(void){
    BSP_RFID_selectDigitalCapacitor(DIGITAL_CAPACITOR_3);
}

void BSP_RFID_selectDigitalCapacitor_Cout(void){
    BSP_RFID_selectDigitalCapacitor(DIGITAL_CAPACITOR_2);
}



