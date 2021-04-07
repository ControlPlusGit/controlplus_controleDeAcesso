#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/clp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/setup_usb.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/clp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/tabelaEstacionamento.o.d ${OBJECTDIR}/src/eventos.o.d ${OBJECTDIR}/src/BSP/bsp.o.d ${OBJECTDIR}/src/BSP/pin_manager.o.d ${OBJECTDIR}/src/BSP/rfid_bsp.o.d ${OBJECTDIR}/src/clp.o.d ${OBJECTDIR}/src/delay.o.d ${OBJECTDIR}/src/EEPROM/24LC256.o.d ${OBJECTDIR}/src/EEPROM/eeprom.o.d ${OBJECTDIR}/src/EXT_INT/ext_int.o.d ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d ${OBJECTDIR}/src/FLASH/flash.o.d ${OBJECTDIR}/src/FSM_DataHora.o.d ${OBJECTDIR}/src/FSM_ESP8266.o.d ${OBJECTDIR}/src/FSM_Ethernet.o.d ${OBJECTDIR}/src/FSM_KeepAlive.o.d ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d ${OBJECTDIR}/src/setup_usb.o.d ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d ${OBJECTDIR}/src/log.o.d ${OBJECTDIR}/src/RFID/as3993.o.d ${OBJECTDIR}/src/RFID/gen2.o.d ${OBJECTDIR}/src/RTC/DS1307.o.d ${OBJECTDIR}/src/RTC/rtc.o.d ${OBJECTDIR}/src/spi1.o.d ${OBJECTDIR}/src/tmr2.o.d ${OBJECTDIR}/src/uart_driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/clp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o

# Source Files
SOURCEFILES=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/clp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/setup_usb.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA210
MP_LINKER_FILE_OPTION=,--script=p24FJ256DA210.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/eventos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/rfid_bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/clp.o: src/clp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clp.o.d 
	@${RM} ${OBJECTDIR}/src/clp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/clp.c  -o ${OBJECTDIR}/src/clp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/clp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/clp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/delay.o: src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_INT/ext_int.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_DataHora.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_ESP8266.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_Ethernet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_KeepAlive.o: src/FSM_KeepAlive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_KeepAlive.c  -o ${OBJECTDIR}/src/FSM_KeepAlive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_KeepAlive.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_KeepAlive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o: src/FSM_TabelaDeEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeEstacionamento.c  -o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/log.o: src/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RFID/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RFID/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/DS1307.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tmr2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/eventos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/BSP/rfid_bsp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/clp.o: src/clp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clp.o.d 
	@${RM} ${OBJECTDIR}/src/clp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/clp.c  -o ${OBJECTDIR}/src/clp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/clp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/clp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/delay.o: src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_INT/ext_int.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_DataHora.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_ESP8266.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_Ethernet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_KeepAlive.o: src/FSM_KeepAlive.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_KeepAlive.c  -o ${OBJECTDIR}/src/FSM_KeepAlive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_KeepAlive.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_KeepAlive.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o: src/FSM_TabelaDeEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeEstacionamento.c  -o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/log.o: src/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/log.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RFID/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RFID/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/DS1307.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tmr2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FLASH" 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o.d 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/FLASH/flash.s  -o ${OBJECTDIR}/src/FLASH/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/FLASH/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST) 
	@${FIXDEPS} "${OBJECTDIR}/src/FLASH/flash.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FLASH" 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o.d 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/FLASH/flash.s  -o ${OBJECTDIR}/src/FLASH/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/FLASH/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST) 
	@${FIXDEPS} "${OBJECTDIR}/src/FLASH/flash.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
