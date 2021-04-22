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
MKDIR=mkdir -p
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
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/clp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/setup_usb.c src/FSM_EventosDePassagem.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/clp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/FSM_EventosDePassagem.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/tabelaEstacionamento.o.d ${OBJECTDIR}/src/eventos.o.d ${OBJECTDIR}/src/BSP/bsp.o.d ${OBJECTDIR}/src/BSP/pin_manager.o.d ${OBJECTDIR}/src/BSP/rfid_bsp.o.d ${OBJECTDIR}/src/clp.o.d ${OBJECTDIR}/src/delay.o.d ${OBJECTDIR}/src/EEPROM/24LC256.o.d ${OBJECTDIR}/src/EEPROM/eeprom.o.d ${OBJECTDIR}/src/EXT_INT/ext_int.o.d ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d ${OBJECTDIR}/src/FLASH/flash.o.d ${OBJECTDIR}/src/FSM_DataHora.o.d ${OBJECTDIR}/src/FSM_ESP8266.o.d ${OBJECTDIR}/src/FSM_Ethernet.o.d ${OBJECTDIR}/src/FSM_KeepAlive.o.d ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d ${OBJECTDIR}/src/setup_usb.o.d ${OBJECTDIR}/src/FSM_EventosDePassagem.o.d ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d ${OBJECTDIR}/src/log.o.d ${OBJECTDIR}/src/RFID/as3993.o.d ${OBJECTDIR}/src/RFID/gen2.o.d ${OBJECTDIR}/src/RTC/DS1307.o.d ${OBJECTDIR}/src/RTC/rtc.o.d ${OBJECTDIR}/src/spi1.o.d ${OBJECTDIR}/src/tmr2.o.d ${OBJECTDIR}/src/uart_driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/clp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_KeepAlive.o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/FSM_EventosDePassagem.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o

# Source Files
SOURCEFILES=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/clp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_KeepAlive.c src/FSM_TabelaDeEstacionamento.c src/setup_usb.c src/FSM_EventosDePassagem.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c



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
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/ad6dcac92068b31437cf793bd1006e46a7f6453e.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/5648bd6b640376f60471967579ece699be6190d2.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  .generated_files/ee86943cd77b9e188268a5e94151df2c3f41ea40.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  .generated_files/ce68872e2ca0cc484e754bb8c681f45231a440e0.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  .generated_files/c651fb0aaf967c72a9fb895b196e115f2a47244c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  .generated_files/617c33dcb0da306d7a0eded3e5d8033836274eca.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  .generated_files/dd953c6f1c4eba0e51dbd7cd63bef71acc9b981f.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/clp.o: src/clp.c  .generated_files/dc1de2a6c25d9c1a742441fff808044810b39d0c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clp.o.d 
	@${RM} ${OBJECTDIR}/src/clp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/clp.c  -o ${OBJECTDIR}/src/clp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/clp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/delay.o: src/delay.c  .generated_files/9bdc46d0456537b94bb2ec1f4eef17656404bddc.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  .generated_files/7309b3b1cec7d261d6c92c981becbf695280c58.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  .generated_files/9962e43005f9601eff44d5d50b03ebdc1ce29fc9.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  .generated_files/c61f07a8dbc668dc3b25cb1b5d0d7e4f5ba55a9c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  .generated_files/f9e9ef9f6b357aedbcdede7c070fff03aa1716a3.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  .generated_files/8211ee451c26262b5c1d891b3b7eb85931c34ebd.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  .generated_files/2e15778a7566e5a88600dcf6b9565d719d921044.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  .generated_files/3df829a08c355db7181485fcf83a604b45073be2.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_KeepAlive.o: src/FSM_KeepAlive.c  .generated_files/379ea180b4b8e13e19088963491fe16a485102f5.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_KeepAlive.c  -o ${OBJECTDIR}/src/FSM_KeepAlive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_KeepAlive.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o: src/FSM_TabelaDeEstacionamento.c  .generated_files/c1c7dbe3e792af10ae04b725bcf8872359814dc3.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeEstacionamento.c  -o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  .generated_files/987d9985bbf1b0cd0c84faca3891459362b39147.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_EventosDePassagem.o: src/FSM_EventosDePassagem.c  .generated_files/fb76c737a556f66b23e9a7e93b56b78464cfe27e.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDePassagem.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDePassagem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_EventosDePassagem.c  -o ${OBJECTDIR}/src/FSM_EventosDePassagem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_EventosDePassagem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  .generated_files/16b01c552ebc03776a7da3fe71b26230f0ff2205.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  .generated_files/1ea692d8df90872ba65056be155ef51d810c21c2.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/679299d9e471bb966786845c7c1ac7e10bf760df.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  .generated_files/c68f5ce2677a12308f1870189cd2981f4f9a2b7b.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  .generated_files/52246e92a2d94a14f34df25edc65976b0b6a338.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  .generated_files/a8e69a7d03551873d67d53a480228055cc0cafd7.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  .generated_files/6bc9c0d025d107c8bb324cf0a30503b8bc203a1c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  .generated_files/118c2913a1bb7a0a08abc44aeaf21ec629f558fb.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  .generated_files/10ee2836006bbded2aa55888ffaeedaa2c6df1a.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  .generated_files/d805d7547aae97b8f6065e979f614dea3450f4f4.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/b04d27a55249a2844dbc90661cfa78d100c83a82.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/e4c410dfa370f592d1f4f0e26164d46b3d9e09b4.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  .generated_files/aaa3f7dd692fe61729d65d851defb6e6378d6098.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  .generated_files/fdbbcc80f8f11e6cc579395be10eec5bada7fb74.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  .generated_files/e0da3e02a2a7f5d434ac058764074a855f45a55d.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  .generated_files/627cda388d1c413df0da230017f73c67a31be7c4.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  .generated_files/9dcee2e509a527109dbec07da300b9fc63575c8e.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/clp.o: src/clp.c  .generated_files/48cdb434172ef61758a3dc9b95b6fa24f1a4fbd3.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/clp.o.d 
	@${RM} ${OBJECTDIR}/src/clp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/clp.c  -o ${OBJECTDIR}/src/clp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/clp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/delay.o: src/delay.c  .generated_files/e6ea5d7f06b204f5a9faa1c567e89e640fba8033.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  .generated_files/a7225367decd8ce2749e707bf1ca6a7e1bf198a8.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  .generated_files/87dacc8f9b91537727a594fd9cacaf2db8df20b9.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  .generated_files/2d4655e0f036ad181855ad993d1c879ad2a1c8a.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  .generated_files/60adda73dd6da41c0905bf189533473fc83b6566.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  .generated_files/9992ea72ccf8642bba3f7b343c534ffe31a70a27.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  .generated_files/ab959ae021f52afa5b9650587ecae9cf78a0b2c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  .generated_files/a06329c9ab2b0cc742aafde7124213d8f93f06bc.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_KeepAlive.o: src/FSM_KeepAlive.c  .generated_files/2261a36fae9a93686151f5a6e1f8ec3122709242.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_KeepAlive.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_KeepAlive.c  -o ${OBJECTDIR}/src/FSM_KeepAlive.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_KeepAlive.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o: src/FSM_TabelaDeEstacionamento.c  .generated_files/a380ae8c651c2ab538ae376ac0f902670910b44d.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeEstacionamento.c  -o ${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  .generated_files/3513da0880b9c3ff85325e3680b71da040735bf7.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/FSM_EventosDePassagem.o: src/FSM_EventosDePassagem.c  .generated_files/38a041fa82d57f4e8d39eb6600f4d9c47b7efde7.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDePassagem.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDePassagem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_EventosDePassagem.c  -o ${OBJECTDIR}/src/FSM_EventosDePassagem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/FSM_EventosDePassagem.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  .generated_files/c81786b465d6a89d3cb8e50345aa9529a0110420.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  .generated_files/24f1abd3313edf18b19335f81f95d8b9db850e3.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/240e59564b8ed4a66589843be65aaf39782350cb.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/log.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  .generated_files/65ced120b4d745a00854e5ec33069af8d746595d.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  .generated_files/ec94c55a3cf53d89469e6d3eacf2024deafa644d.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  .generated_files/44d02f1203a346d053e27d43801ff97bd34dd6a3.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  .generated_files/a2593cebdd8a0d74f28644e24e82d1aa14ffdbc0.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  .generated_files/f9d48a67729310265293897eb92f86b52f3075eb.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  .generated_files/9f78434ab109e64bafa60bd27769b713a67cb29c.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  .generated_files/8b79af9f8209e80d44328f30e60db5f6a1382549.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  .generated_files/5c06d0043fd1e6004336b5795eac7d8182255194.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/FLASH" 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o.d 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/FLASH/flash.s  -o ${OBJECTDIR}/src/FLASH/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/FLASH/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST) 
	
else
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  .generated_files/26c27d50d5a076403588f1e9a92eebc50822eb88.flag .generated_files/de07652b9ea526867b20bd2ebbcfe40482de27df.flag
	@${MKDIR} "${OBJECTDIR}/src/FLASH" 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o.d 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/FLASH/flash.s  -o ${OBJECTDIR}/src/FLASH/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/FLASH/flash.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST) 
	
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
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/controlplus_controleDeAcesso.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
