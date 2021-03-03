/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __RFID_BSP_H__
#define	__RFID_BSP_H__

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
        DIGITAL_CAPACITOR_1 = 1,
        DIGITAL_CAPACITOR_2,
        DIGITAL_CAPACITOR_3
    }BSP_RFID_OnboardDigitalCapacitors;
    
    typedef enum {
        BSP_RFID_OK = 0,
        BSP_RFID_ERROR
    }BSP_RFID_Status;
    
    extern BSP_RFID_Status BSP_RFID_status;

    extern BSP_RFID_OnboardDigitalCapacitors OnboardDigitalCapacitors;

    BSP_RFID_Status BSP_RFID_selectAntenna(uint8_t num_antenna);    

    void BSP_RFID_selectDigitalCapacitor_Cin(void);

    void BSP_RFID_selectDigitalCapacitor_Clen(void);

    void BSP_RFID_selectDigitalCapacitor_Cout(void);
    
    void BSP_RFID_setAS3993_enablePin(uint8_t val);

    uint8_t BSP_RFID_AS3993_isEnabled(void);

    void BSP_RFID_setAS3993_SPI_enablePin(uint8_t val);
    
    //static void BSP_RFID_selectDigitalCapacitor(uint8_t num_capacitor);
        
#ifdef	__cplusplus
    }
#endif /* __cplusplus */

#endif	/* __RFID_BSP_H__ */

