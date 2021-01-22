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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/tags.c src/tuner.c src/portal.c src/empilhadeira.c src/platform.c src/perifericos.c src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_EventosDeParada.c src/FSM_TabelaDeExclusao.c src/setup_usb.c src/rtc.c src/spi_driver.c src/timer.c src/i2c.c src/config_i2c3.c src/mem_i2c_24LC256.c src/uart_driver.c src/usb_device.c src/usb_descriptors.c src/usb_function_generic.c src/usb_hid_stream_driver.c src/usb_hal_pic24.c src/usb_function_hid.c src/appl_commands.c src/appl_commands_table.c src/as3993.c src/gen2.c src/global.c src/main.c src/tabelaDeExclusao.c src/bootloadable.c src/stream_dispatcher.c src/weak_stream_functions.c src/spi1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/tags.o ${OBJECTDIR}/src/tuner.o ${OBJECTDIR}/src/portal.o ${OBJECTDIR}/src/empilhadeira.o ${OBJECTDIR}/src/platform.o ${OBJECTDIR}/src/perifericos.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_EventosDeParada.o ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/rtc.o ${OBJECTDIR}/src/spi_driver.o ${OBJECTDIR}/src/timer.o ${OBJECTDIR}/src/i2c.o ${OBJECTDIR}/src/config_i2c3.o ${OBJECTDIR}/src/mem_i2c_24LC256.o ${OBJECTDIR}/src/uart_driver.o ${OBJECTDIR}/src/usb_device.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/usb_function_generic.o ${OBJECTDIR}/src/usb_hid_stream_driver.o ${OBJECTDIR}/src/usb_hal_pic24.o ${OBJECTDIR}/src/usb_function_hid.o ${OBJECTDIR}/src/appl_commands.o ${OBJECTDIR}/src/appl_commands_table.o ${OBJECTDIR}/src/as3993.o ${OBJECTDIR}/src/gen2.o ${OBJECTDIR}/src/global.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/tabelaDeExclusao.o ${OBJECTDIR}/src/bootloadable.o ${OBJECTDIR}/src/stream_dispatcher.o ${OBJECTDIR}/src/weak_stream_functions.o ${OBJECTDIR}/src/spi1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/tags.o.d ${OBJECTDIR}/src/tuner.o.d ${OBJECTDIR}/src/portal.o.d ${OBJECTDIR}/src/empilhadeira.o.d ${OBJECTDIR}/src/platform.o.d ${OBJECTDIR}/src/perifericos.o.d ${OBJECTDIR}/src/FSM_DataHora.o.d ${OBJECTDIR}/src/FSM_ESP8266.o.d ${OBJECTDIR}/src/FSM_Ethernet.o.d ${OBJECTDIR}/src/FSM_EventosDeParada.o.d ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d ${OBJECTDIR}/src/setup_usb.o.d ${OBJECTDIR}/src/rtc.o.d ${OBJECTDIR}/src/spi_driver.o.d ${OBJECTDIR}/src/timer.o.d ${OBJECTDIR}/src/i2c.o.d ${OBJECTDIR}/src/config_i2c3.o.d ${OBJECTDIR}/src/mem_i2c_24LC256.o.d ${OBJECTDIR}/src/uart_driver.o.d ${OBJECTDIR}/src/usb_device.o.d ${OBJECTDIR}/src/usb_descriptors.o.d ${OBJECTDIR}/src/usb_function_generic.o.d ${OBJECTDIR}/src/usb_hid_stream_driver.o.d ${OBJECTDIR}/src/usb_hal_pic24.o.d ${OBJECTDIR}/src/usb_function_hid.o.d ${OBJECTDIR}/src/appl_commands.o.d ${OBJECTDIR}/src/appl_commands_table.o.d ${OBJECTDIR}/src/as3993.o.d ${OBJECTDIR}/src/gen2.o.d ${OBJECTDIR}/src/global.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/tabelaDeExclusao.o.d ${OBJECTDIR}/src/bootloadable.o.d ${OBJECTDIR}/src/stream_dispatcher.o.d ${OBJECTDIR}/src/weak_stream_functions.o.d ${OBJECTDIR}/src/spi1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/tags.o ${OBJECTDIR}/src/tuner.o ${OBJECTDIR}/src/portal.o ${OBJECTDIR}/src/empilhadeira.o ${OBJECTDIR}/src/platform.o ${OBJECTDIR}/src/perifericos.o ${OBJECTDIR}/src/FSM_DataHora.o ${OBJECTDIR}/src/FSM_ESP8266.o ${OBJECTDIR}/src/FSM_Ethernet.o ${OBJECTDIR}/src/FSM_EventosDeParada.o ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/rtc.o ${OBJECTDIR}/src/spi_driver.o ${OBJECTDIR}/src/timer.o ${OBJECTDIR}/src/i2c.o ${OBJECTDIR}/src/config_i2c3.o ${OBJECTDIR}/src/mem_i2c_24LC256.o ${OBJECTDIR}/src/uart_driver.o ${OBJECTDIR}/src/usb_device.o ${OBJECTDIR}/src/usb_descriptors.o ${OBJECTDIR}/src/usb_function_generic.o ${OBJECTDIR}/src/usb_hid_stream_driver.o ${OBJECTDIR}/src/usb_hal_pic24.o ${OBJECTDIR}/src/usb_function_hid.o ${OBJECTDIR}/src/appl_commands.o ${OBJECTDIR}/src/appl_commands_table.o ${OBJECTDIR}/src/as3993.o ${OBJECTDIR}/src/gen2.o ${OBJECTDIR}/src/global.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/tabelaDeExclusao.o ${OBJECTDIR}/src/bootloadable.o ${OBJECTDIR}/src/stream_dispatcher.o ${OBJECTDIR}/src/weak_stream_functions.o ${OBJECTDIR}/src/spi1.o

# Source Files
SOURCEFILES=src/tags.c src/tuner.c src/portal.c src/empilhadeira.c src/platform.c src/perifericos.c src/FSM_DataHora.c src/FSM_ESP8266.c src/FSM_Ethernet.c src/FSM_EventosDeParada.c src/FSM_TabelaDeExclusao.c src/setup_usb.c src/rtc.c src/spi_driver.c src/timer.c src/i2c.c src/config_i2c3.c src/mem_i2c_24LC256.c src/uart_driver.c src/usb_device.c src/usb_descriptors.c src/usb_function_generic.c src/usb_hid_stream_driver.c src/usb_hal_pic24.c src/usb_function_hid.c src/appl_commands.c src/appl_commands_table.c src/as3993.c src/gen2.c src/global.c src/main.c src/tabelaDeExclusao.c src/bootloadable.c src/stream_dispatcher.c src/weak_stream_functions.c src/spi1.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA210
MP_LINKER_FILE_OPTION=,--script="src\p24FJ256DA210.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/tags.o: src/tags.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tags.o.d 
	@${RM} ${OBJECTDIR}/src/tags.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tags.c  -o ${OBJECTDIR}/src/tags.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tags.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tags.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tuner.o: src/tuner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tuner.o.d 
	@${RM} ${OBJECTDIR}/src/tuner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tuner.c  -o ${OBJECTDIR}/src/tuner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tuner.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tuner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/portal.o: src/portal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/portal.o.d 
	@${RM} ${OBJECTDIR}/src/portal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/portal.c  -o ${OBJECTDIR}/src/portal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/portal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/portal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/empilhadeira.o: src/empilhadeira.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/empilhadeira.o.d 
	@${RM} ${OBJECTDIR}/src/empilhadeira.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/empilhadeira.c  -o ${OBJECTDIR}/src/empilhadeira.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/empilhadeira.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/empilhadeira.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/platform.o: src/platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/platform.o.d 
	@${RM} ${OBJECTDIR}/src/platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/platform.c  -o ${OBJECTDIR}/src/platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/platform.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/platform.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/perifericos.o: src/perifericos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/perifericos.o.d 
	@${RM} ${OBJECTDIR}/src/perifericos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/perifericos.c  -o ${OBJECTDIR}/src/perifericos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/perifericos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/perifericos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_DataHora.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_ESP8266.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_Ethernet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_EventosDeParada.o: src/FSM_EventosDeParada.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDeParada.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDeParada.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_EventosDeParada.c  -o ${OBJECTDIR}/src/FSM_EventosDeParada.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_EventosDeParada.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_EventosDeParada.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_TabelaDeExclusao.o: src/FSM_TabelaDeExclusao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeExclusao.c  -o ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/rtc.o: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/rtc.c  -o ${OBJECTDIR}/src/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi_driver.o: src/spi_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/src/spi_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi_driver.c  -o ${OBJECTDIR}/src/spi_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/timer.o: src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timer.o.d 
	@${RM} ${OBJECTDIR}/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/timer.c  -o ${OBJECTDIR}/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/i2c.o: src/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/i2c.c  -o ${OBJECTDIR}/src/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/config_i2c3.o: src/config_i2c3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o.d 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/config_i2c3.c  -o ${OBJECTDIR}/src/config_i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/config_i2c3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/config_i2c3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/mem_i2c_24LC256.o: src/mem_i2c_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/mem_i2c_24LC256.c  -o ${OBJECTDIR}/src/mem_i2c_24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/mem_i2c_24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/mem_i2c_24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_device.o: src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_device.o.d 
	@${RM} ${OBJECTDIR}/src/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_device.c  -o ${OBJECTDIR}/src/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_descriptors.c  -o ${OBJECTDIR}/src/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_function_generic.o: src/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_function_generic.o.d 
	@${RM} ${OBJECTDIR}/src/usb_function_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_function_generic.c  -o ${OBJECTDIR}/src/usb_function_generic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_function_generic.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_function_generic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_hid_stream_driver.o: src/usb_hid_stream_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_hid_stream_driver.o.d 
	@${RM} ${OBJECTDIR}/src/usb_hid_stream_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_hid_stream_driver.c  -o ${OBJECTDIR}/src/usb_hid_stream_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_hid_stream_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_hid_stream_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_hal_pic24.o: src/usb_hal_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/src/usb_hal_pic24.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_hal_pic24.c  -o ${OBJECTDIR}/src/usb_hal_pic24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_hal_pic24.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_hal_pic24.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_function_hid.o: src/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/src/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_function_hid.c  -o ${OBJECTDIR}/src/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_function_hid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands.o: src/appl_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands.c  -o ${OBJECTDIR}/src/appl_commands.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands_table.o: src/appl_commands_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands_table.c  -o ${OBJECTDIR}/src/appl_commands_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands_table.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands_table.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/as3993.o: src/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/as3993.c  -o ${OBJECTDIR}/src/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/as3993.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gen2.o: src/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gen2.c  -o ${OBJECTDIR}/src/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gen2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global.o: src/global.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/global.o.d 
	@${RM} ${OBJECTDIR}/src/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global.c  -o ${OBJECTDIR}/src/global.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/global.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaDeExclusao.o: src/tabelaDeExclusao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaDeExclusao.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaDeExclusao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaDeExclusao.c  -o ${OBJECTDIR}/src/tabelaDeExclusao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaDeExclusao.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaDeExclusao.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/bootloadable.o: src/bootloadable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/bootloadable.o.d 
	@${RM} ${OBJECTDIR}/src/bootloadable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/bootloadable.c  -o ${OBJECTDIR}/src/bootloadable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/bootloadable.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/bootloadable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/stream_dispatcher.o: src/stream_dispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/stream_dispatcher.o.d 
	@${RM} ${OBJECTDIR}/src/stream_dispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/stream_dispatcher.c  -o ${OBJECTDIR}/src/stream_dispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/stream_dispatcher.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/stream_dispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/weak_stream_functions.o: src/weak_stream_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/weak_stream_functions.o.d 
	@${RM} ${OBJECTDIR}/src/weak_stream_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/weak_stream_functions.c  -o ${OBJECTDIR}/src/weak_stream_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/weak_stream_functions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/weak_stream_functions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/tags.o: src/tags.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tags.o.d 
	@${RM} ${OBJECTDIR}/src/tags.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tags.c  -o ${OBJECTDIR}/src/tags.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tags.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tags.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tuner.o: src/tuner.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tuner.o.d 
	@${RM} ${OBJECTDIR}/src/tuner.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tuner.c  -o ${OBJECTDIR}/src/tuner.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tuner.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tuner.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/portal.o: src/portal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/portal.o.d 
	@${RM} ${OBJECTDIR}/src/portal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/portal.c  -o ${OBJECTDIR}/src/portal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/portal.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/portal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/empilhadeira.o: src/empilhadeira.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/empilhadeira.o.d 
	@${RM} ${OBJECTDIR}/src/empilhadeira.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/empilhadeira.c  -o ${OBJECTDIR}/src/empilhadeira.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/empilhadeira.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/empilhadeira.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/platform.o: src/platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/platform.o.d 
	@${RM} ${OBJECTDIR}/src/platform.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/platform.c  -o ${OBJECTDIR}/src/platform.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/platform.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/platform.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/perifericos.o: src/perifericos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/perifericos.o.d 
	@${RM} ${OBJECTDIR}/src/perifericos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/perifericos.c  -o ${OBJECTDIR}/src/perifericos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/perifericos.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/perifericos.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_DataHora.o: src/FSM_DataHora.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_DataHora.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_DataHora.c  -o ${OBJECTDIR}/src/FSM_DataHora.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_DataHora.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_DataHora.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_ESP8266.o: src/FSM_ESP8266.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_ESP8266.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_ESP8266.c  -o ${OBJECTDIR}/src/FSM_ESP8266.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_ESP8266.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_ESP8266.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_Ethernet.o: src/FSM_Ethernet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_Ethernet.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_Ethernet.c  -o ${OBJECTDIR}/src/FSM_Ethernet.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_Ethernet.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_Ethernet.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_EventosDeParada.o: src/FSM_EventosDeParada.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDeParada.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_EventosDeParada.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_EventosDeParada.c  -o ${OBJECTDIR}/src/FSM_EventosDeParada.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_EventosDeParada.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_EventosDeParada.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/FSM_TabelaDeExclusao.o: src/FSM_TabelaDeExclusao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d 
	@${RM} ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/FSM_TabelaDeExclusao.c  -o ${OBJECTDIR}/src/FSM_TabelaDeExclusao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/FSM_TabelaDeExclusao.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/setup_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/rtc.o: src/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/rtc.c  -o ${OBJECTDIR}/src/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/rtc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/rtc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi_driver.o: src/spi_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/src/spi_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi_driver.c  -o ${OBJECTDIR}/src/spi_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/timer.o: src/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/timer.o.d 
	@${RM} ${OBJECTDIR}/src/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/timer.c  -o ${OBJECTDIR}/src/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/timer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/i2c.o: src/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/i2c.o.d 
	@${RM} ${OBJECTDIR}/src/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/i2c.c  -o ${OBJECTDIR}/src/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/i2c.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/config_i2c3.o: src/config_i2c3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o.d 
	@${RM} ${OBJECTDIR}/src/config_i2c3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/config_i2c3.c  -o ${OBJECTDIR}/src/config_i2c3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/config_i2c3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/config_i2c3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/mem_i2c_24LC256.o: src/mem_i2c_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/mem_i2c_24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/mem_i2c_24LC256.c  -o ${OBJECTDIR}/src/mem_i2c_24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/mem_i2c_24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/mem_i2c_24LC256.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/uart_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_device.o: src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_device.o.d 
	@${RM} ${OBJECTDIR}/src/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_device.c  -o ${OBJECTDIR}/src/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_descriptors.o: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_descriptors.c  -o ${OBJECTDIR}/src/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_function_generic.o: src/usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_function_generic.o.d 
	@${RM} ${OBJECTDIR}/src/usb_function_generic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_function_generic.c  -o ${OBJECTDIR}/src/usb_function_generic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_function_generic.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_function_generic.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_hid_stream_driver.o: src/usb_hid_stream_driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_hid_stream_driver.o.d 
	@${RM} ${OBJECTDIR}/src/usb_hid_stream_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_hid_stream_driver.c  -o ${OBJECTDIR}/src/usb_hid_stream_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_hid_stream_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_hid_stream_driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_hal_pic24.o: src/usb_hal_pic24.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/src/usb_hal_pic24.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_hal_pic24.c  -o ${OBJECTDIR}/src/usb_hal_pic24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_hal_pic24.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_hal_pic24.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/usb_function_hid.o: src/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/src/usb_function_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/usb_function_hid.c  -o ${OBJECTDIR}/src/usb_function_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/usb_function_hid.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/usb_function_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands.o: src/appl_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands.c  -o ${OBJECTDIR}/src/appl_commands.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/appl_commands_table.o: src/appl_commands_table.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o.d 
	@${RM} ${OBJECTDIR}/src/appl_commands_table.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/appl_commands_table.c  -o ${OBJECTDIR}/src/appl_commands_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/appl_commands_table.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/appl_commands_table.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/as3993.o: src/as3993.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/as3993.c  -o ${OBJECTDIR}/src/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/as3993.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/as3993.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gen2.o: src/gen2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gen2.c  -o ${OBJECTDIR}/src/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gen2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/gen2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/global.o: src/global.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/global.o.d 
	@${RM} ${OBJECTDIR}/src/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/global.c  -o ${OBJECTDIR}/src/global.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/global.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/global.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/tabelaDeExclusao.o: src/tabelaDeExclusao.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaDeExclusao.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaDeExclusao.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaDeExclusao.c  -o ${OBJECTDIR}/src/tabelaDeExclusao.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/tabelaDeExclusao.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/tabelaDeExclusao.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/bootloadable.o: src/bootloadable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/bootloadable.o.d 
	@${RM} ${OBJECTDIR}/src/bootloadable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/bootloadable.c  -o ${OBJECTDIR}/src/bootloadable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/bootloadable.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/bootloadable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/stream_dispatcher.o: src/stream_dispatcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/stream_dispatcher.o.d 
	@${RM} ${OBJECTDIR}/src/stream_dispatcher.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/stream_dispatcher.c  -o ${OBJECTDIR}/src/stream_dispatcher.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/stream_dispatcher.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/stream_dispatcher.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/weak_stream_functions.o: src/weak_stream_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/weak_stream_functions.o.d 
	@${RM} ${OBJECTDIR}/src/weak_stream_functions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/weak_stream_functions.c  -o ${OBJECTDIR}/src/weak_stream_functions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/weak_stream_functions.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/weak_stream_functions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -fno-short-double -mlarge-code -mlarge-data -mlarge-scalar -mconst-in-data -menable-large-arrays -O0 -I"src" -DUSER_LOGGER -msmart-io=1 -Wall -msfr-warn=off   
	@${FIXDEPS} "${OBJECTDIR}/src/spi1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    src/p24FJ256DA210.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=100,--no-check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   src/p24FJ256DA210.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=100,--no-check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/controleDeAcesso.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
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