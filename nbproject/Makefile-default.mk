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
SOURCEFILES_QUOTED_IF_SPACED=src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/EEPROM/24LC256.c src/FLASH/flash.s src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/RTC/DS1307.c src/appl_commands.c src/appl_commands_table.c src/as3993.c src/bootloadable.c src/config_i2c3.c src/flash_access.c src/gen2.c src/global.c src/i2c.c src/log.c src/main.c src/mem_i2c_24LC256.c src/perifericos.c src/platform.c src/rtc.c src/setup_usb.c src/system_clock.c src/tabelaEstacionamento.c src/tuner.c src/uart_driver.c src/delay.c src/system.c src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/spi1.c src/tmr2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/appl_commands.o ${OBJECTDIR}/src/appl_commands_table.o ${OBJECTDIR}/src/as3993.o ${OBJECTDIR}/src/bootloadable.o ${OBJECTDIR}/src/config_i2c3.o ${OBJECTDIR}/src/flash_access.o ${OBJECTDIR}/src/gen2.o ${OBJECTDIR}/src/global.o ${OBJECTDIR}/src/i2c.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/mem_i2c_24LC256.o ${OBJECTDIR}/src/perifericos.o ${OBJECTDIR}/src/platform.o ${OBJECTDIR}/src/rtc.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/system_clock.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/tuner.o ${OBJECTDIR}/src/uart_driver.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/BSP/bsp.o.d ${OBJECTDIR}/src/BSP/pin_manager.o.d ${OBJECTDIR}/src/BSP/rfid_bsp.o.d ${OBJECTDIR}/src/EEPROM/24LC256.o.d ${OBJECTDIR}/src/FLASH/flash.o.d ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d ${OBJECTDIR}/src/RTC/DS1307.o.d ${OBJECTDIR}/src/appl_commands.o.d ${OBJECTDIR}/src/appl_commands_table.o.d ${OBJECTDIR}/src/as3993.o.d ${OBJECTDIR}/src/bootloadable.o.d ${OBJECTDIR}/src/config_i2c3.o.d ${OBJECTDIR}/src/flash_access.o.d ${OBJECTDIR}/src/gen2.o.d ${OBJECTDIR}/src/global.o.d ${OBJECTDIR}/src/i2c.o.d ${OBJECTDIR}/src/log.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/mem_i2c_24LC256.o.d ${OBJECTDIR}/src/perifericos.o.d ${OBJECTDIR}/src/platform.o.d ${OBJECTDIR}/src/rtc.o.d ${OBJECTDIR}/src/setup_usb.o.d ${OBJECTDIR}/src/system_clock.o.d ${OBJECTDIR}/src/tabelaEstacionamento.o.d ${OBJECTDIR}/src/tuner.o.d ${OBJECTDIR}/src/uart_driver.o.d ${OBJECTDIR}/src/delay.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/FSM_DataHora.o.d ${OBJECTDIR}/src/FSM_ESP8266.o.d ${OBJECTDIR}/src/FSM_Ethernet.o.d ${OBJECTDIR}/src/FSM_KeepAlive.o.d ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d ${OBJECTDIR}/src/spi1.o.d ${OBJECTDIR}/src/tmr2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/appl_commands.o ${OBJECTDIR}/src/appl_commands_table.o ${OBJECTDIR}/src/as3993.o ${OBJECTDIR}/src/bootloadable.o ${OBJECTDIR}/src/config_i2c3.o ${OBJECTDIR}/src/flash_access.o ${OBJECTDIR}/src/gen2.o ${OBJECTDIR}/src/global.o ${OBJECTDIR}/src/i2c.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/mem_i2c_24LC256.o ${OBJECTDIR}/src/perifericos.o ${OBJECTDIR}/src/platform.o ${OBJECTDIR}/src/rtc.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/system_clock.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/tuner.o ${OBJECTDIR}/src/uart_driver.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o

# Source Files
SOURCEFILES=src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/EEPROM/24LC256.c src/FLASH/flash.s src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/RTC/DS1307.c src/appl_commands.c src/appl_commands_table.c src/as3993.c src/bootloadable.c src/config_i2c3.c src/flash_access.c src/gen2.c src/global.c src/i2c.c src/log.c src/main.c src/mem_i2c_24LC256.c src/perifericos.c src/platform.c src/rtc.c src/setup_usb.c src/system_clock.c src/tabelaEstacionamento.c src/tuner.c src/uart_driver.c src/delay.c src/system.c src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/spi1.c src/tmr2.c



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
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/DS1307.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands.o: src/appl_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands.c  -o ${OBJECTDIR}/src/appl_commands.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands_table.o: src/appl_commands_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands_table.c  -o ${OBJECTDIR}/src/appl_commands_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands_table.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands_table.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/as3993.o: src/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/as3993.c  -o ${OBJECTDIR}/src/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/as3993.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/bootloadable.o: src/bootloadable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/bootloadable.o.d 
	@${RM} ${OBJECTDIR}/src/bootloadable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/bootloadable.c  -o ${OBJECTDIR}/src/bootloadable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/bootloadable.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/bootloadable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/config_i2c3.o: src/config_i2c3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o.d 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/config_i2c3.c  -o ${OBJECTDIR}/src/config_i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/config_i2c3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/config_i2c3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/flash_access.o: src/flash_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/flash_access.o.d 
	@${RM} ${OBJECTDIR}/src/flash_access.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/flash_access.c  -o ${OBJECTDIR}/src/flash_access.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/flash_access.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/flash_access.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gen2.o: src/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gen2.c  -o ${OBJECTDIR}/src/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gen2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global.o: src/global.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/global.o.d 
	@${RM} ${OBJECTDIR}/src/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global.c  -o ${OBJECTDIR}/src/global.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/global.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/i2c.o: src/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/i2c.c  -o ${OBJECTDIR}/src/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/log.o: src/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/mem_i2c_24LC256.o: src/mem_i2c_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/mem_i2c_24LC256.c  -o ${OBJECTDIR}/src/mem_i2c_24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/mem_i2c_24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/mem_i2c_24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/perifericos.o: src/perifericos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/perifericos.o.d 
	@${RM} ${OBJECTDIR}/src/perifericos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/perifericos.c  -o ${OBJECTDIR}/src/perifericos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/perifericos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/perifericos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/platform.o: src/platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/platform.o.d 
	@${RM} ${OBJECTDIR}/src/platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/platform.c  -o ${OBJECTDIR}/src/platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/platform.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/platform.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/rtc.o: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/rtc.c  -o ${OBJECTDIR}/src/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system_clock.o: src/system_clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system_clock.o.d 
	@${RM} ${OBJECTDIR}/src/system_clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system_clock.c  -o ${OBJECTDIR}/src/system_clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system_clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system_clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tuner.o: src/tuner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tuner.o.d 
	@${RM} ${OBJECTDIR}/src/tuner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tuner.c  -o ${OBJECTDIR}/src/tuner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tuner.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tuner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/delay.o: src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	
else
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
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/EEPROM/24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/RTC/DS1307.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands.o: src/appl_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands.c  -o ${OBJECTDIR}/src/appl_commands.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands_table.o: src/appl_commands_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands_table.c  -o ${OBJECTDIR}/src/appl_commands_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands_table.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands_table.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/as3993.o: src/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/as3993.c  -o ${OBJECTDIR}/src/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/as3993.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/bootloadable.o: src/bootloadable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/bootloadable.o.d 
	@${RM} ${OBJECTDIR}/src/bootloadable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/bootloadable.c  -o ${OBJECTDIR}/src/bootloadable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/bootloadable.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/bootloadable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/config_i2c3.o: src/config_i2c3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o.d 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/config_i2c3.c  -o ${OBJECTDIR}/src/config_i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/config_i2c3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/config_i2c3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/flash_access.o: src/flash_access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/flash_access.o.d 
	@${RM} ${OBJECTDIR}/src/flash_access.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/flash_access.c  -o ${OBJECTDIR}/src/flash_access.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/flash_access.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/flash_access.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gen2.o: src/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gen2.c  -o ${OBJECTDIR}/src/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gen2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global.o: src/global.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/global.o.d 
	@${RM} ${OBJECTDIR}/src/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global.c  -o ${OBJECTDIR}/src/global.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/global.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/i2c.o: src/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/i2c.c  -o ${OBJECTDIR}/src/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/i2c.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/log.o: src/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/log.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/mem_i2c_24LC256.o: src/mem_i2c_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/mem_i2c_24LC256.c  -o ${OBJECTDIR}/src/mem_i2c_24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/mem_i2c_24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/mem_i2c_24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/perifericos.o: src/perifericos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/perifericos.o.d 
	@${RM} ${OBJECTDIR}/src/perifericos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/perifericos.c  -o ${OBJECTDIR}/src/perifericos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/perifericos.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/perifericos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/platform.o: src/platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/platform.o.d 
	@${RM} ${OBJECTDIR}/src/platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/platform.c  -o ${OBJECTDIR}/src/platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/platform.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/platform.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/rtc.o: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/rtc.c  -o ${OBJECTDIR}/src/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/rtc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system_clock.o: src/system_clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system_clock.o.d 
	@${RM} ${OBJECTDIR}/src/system_clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system_clock.c  -o ${OBJECTDIR}/src/system_clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system_clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system_clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaEstacionamento.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tuner.o: src/tuner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tuner.o.d 
	@${RM} ${OBJECTDIR}/src/tuner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tuner.c  -o ${OBJECTDIR}/src/tuner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tuner.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tuner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/delay.o: src/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/system.o: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
