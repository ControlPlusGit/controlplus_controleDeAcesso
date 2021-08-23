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
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/controleAcessoGaragem.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/setup_usb.c src/USR_TCP232.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/controleAcessoGaragem.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/USR_TCP232.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/tabelaEstacionamento.o.d ${OBJECTDIR}/src/eventos.o.d ${OBJECTDIR}/src/controleAcessoGaragem.o.d ${OBJECTDIR}/src/BSP/bsp.o.d ${OBJECTDIR}/src/BSP/pin_manager.o.d ${OBJECTDIR}/src/BSP/rfid_bsp.o.d ${OBJECTDIR}/src/delay.o.d ${OBJECTDIR}/src/EEPROM/24LC256.o.d ${OBJECTDIR}/src/EEPROM/eeprom.o.d ${OBJECTDIR}/src/EXT_INT/ext_int.o.d ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d ${OBJECTDIR}/src/FLASH/flash.o.d ${OBJECTDIR}/src/setup_usb.o.d ${OBJECTDIR}/src/USR_TCP232.o.d ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d ${OBJECTDIR}/src/log.o.d ${OBJECTDIR}/src/RFID/as3993.o.d ${OBJECTDIR}/src/RFID/gen2.o.d ${OBJECTDIR}/src/RTC/DS1307.o.d ${OBJECTDIR}/src/RTC/rtc.o.d ${OBJECTDIR}/src/spi1.o.d ${OBJECTDIR}/src/tmr2.o.d ${OBJECTDIR}/src/uart_driver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/tabelaEstacionamento.o ${OBJECTDIR}/src/eventos.o ${OBJECTDIR}/src/controleAcessoGaragem.o ${OBJECTDIR}/src/BSP/bsp.o ${OBJECTDIR}/src/BSP/pin_manager.o ${OBJECTDIR}/src/BSP/rfid_bsp.o ${OBJECTDIR}/src/delay.o ${OBJECTDIR}/src/EEPROM/24LC256.o ${OBJECTDIR}/src/EEPROM/eeprom.o ${OBJECTDIR}/src/EXT_INT/ext_int.o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o ${OBJECTDIR}/src/FLASH/flash.o ${OBJECTDIR}/src/setup_usb.o ${OBJECTDIR}/src/USR_TCP232.o ${OBJECTDIR}/src/I2C1/i2c1_driver.o ${OBJECTDIR}/src/I2C3/i2c3_driver.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/RFID/as3993.o ${OBJECTDIR}/src/RFID/gen2.o ${OBJECTDIR}/src/RTC/DS1307.o ${OBJECTDIR}/src/RTC/rtc.o ${OBJECTDIR}/src/spi1.o ${OBJECTDIR}/src/tmr2.o ${OBJECTDIR}/src/uart_driver.o

# Source Files
SOURCEFILES=src/main.c src/system.c src/tabelaEstacionamento.c src/eventos.c src/controleAcessoGaragem.c src/BSP/bsp.c src/BSP/pin_manager.c src/BSP/rfid_bsp.c src/delay.c src/EEPROM/24LC256.c src/EEPROM/eeprom.c src/EXT_INT/ext_int.c src/EXT_INT/interrupt_manager.c src/FLASH/flash.s src/setup_usb.c src/USR_TCP232.c src/I2C1/i2c1_driver.c src/I2C3/i2c3_driver.c src/log.c src/RFID/as3993.c src/RFID/gen2.c src/RTC/DS1307.c src/RTC/rtc.c src/spi1.c src/tmr2.c src/uart_driver.c



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
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/bac400658b487dd2b3627494c16ad7e64b84be2c .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/default/4453dd613277178a3f6f1a15a4f79eab90f338d4 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  .generated_files/flags/default/a8546fcf76467aa150930b95272ce396f2cea8ef .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  .generated_files/flags/default/2d01152f6791d459952f2784bd8999c8e400ed2c .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/controleAcessoGaragem.o: src/controleAcessoGaragem.c  .generated_files/flags/default/c87421ba0511a96434296b2e383e64c8bd521d4c .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/controleAcessoGaragem.o.d 
	@${RM} ${OBJECTDIR}/src/controleAcessoGaragem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/controleAcessoGaragem.c  -o ${OBJECTDIR}/src/controleAcessoGaragem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/controleAcessoGaragem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  .generated_files/flags/default/e9fb35adeee6a9dcc182cd83188ad6d3806b742b .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  .generated_files/flags/default/e366b59ce6df0c9fb471bf779b5797425879d998 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  .generated_files/flags/default/48ebbf5d792dd2c877f3beac5c80fc8a465ee45a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/delay.o: src/delay.c  .generated_files/flags/default/e9643e9c697da7b4d89defd9da53cb98eda659f0 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  .generated_files/flags/default/b5206f588dcdc01ebbc14896fb3e6430e5f07f56 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  .generated_files/flags/default/2ed439574e68b2f6f208deb69c06b0ed684c247a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  .generated_files/flags/default/ff3f9eddb584177676d8da713524eba182a6228b .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  .generated_files/flags/default/67691891d94be843d6baeb3c37e76ae7d1a725ea .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  .generated_files/flags/default/1f793a24b893e8d04becfcd4eff8c2710493d954 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/USR_TCP232.o: src/USR_TCP232.c  .generated_files/flags/default/7d8f6f44014251507181854eca6f815d7708856a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/USR_TCP232.o.d 
	@${RM} ${OBJECTDIR}/src/USR_TCP232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USR_TCP232.c  -o ${OBJECTDIR}/src/USR_TCP232.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/USR_TCP232.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  .generated_files/flags/default/a030eda6f299b514c41eec32f64caa3c9ba85dfb .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  .generated_files/flags/default/416ba3c16b2f9d0dae661f44f360c6d9874a849a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/default/f122a1a36843bb170de19cb3dda4a2a5165a67c0 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  .generated_files/flags/default/67729a520956ad18a38b92b470a6e2067c73ed09 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  .generated_files/flags/default/a52bafe93ecef08af27e83d5d2622e7380810da5 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  .generated_files/flags/default/4322ed1eca9af0c8d64d1f3d093ed7e81504c57b .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  .generated_files/flags/default/967a2852b49b2c3b17e9decc68e0cc63c56b1b5f .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  .generated_files/flags/default/a1941c3b5235f87fbd20db03a2d03aa9dbd7334f .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  .generated_files/flags/default/f2b14500bf102d228c5087166e07ba6c86f2dd51 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  .generated_files/flags/default/813d16dca9b0744a1aac051e28e6a758a371b87 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/2d2859d43d3cc37176686d42aae1b90ce6176f1e .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/default/53b28ce131189a2d2393e9eeb6e8130f2a5c605f .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/system.c  -o ${OBJECTDIR}/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tabelaEstacionamento.o: src/tabelaEstacionamento.c  .generated_files/flags/default/b559b7407a2e9c06b2da5f0abe640c78bf43fc5a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o.d 
	@${RM} ${OBJECTDIR}/src/tabelaEstacionamento.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tabelaEstacionamento.c  -o ${OBJECTDIR}/src/tabelaEstacionamento.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tabelaEstacionamento.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/eventos.o: src/eventos.c  .generated_files/flags/default/58c17840a6f47e668235bc8fc387b11c0919aeba .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/eventos.o.d 
	@${RM} ${OBJECTDIR}/src/eventos.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/eventos.c  -o ${OBJECTDIR}/src/eventos.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/eventos.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/controleAcessoGaragem.o: src/controleAcessoGaragem.c  .generated_files/flags/default/383990d36218c1a532f786f0383a024d7861d45a .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/controleAcessoGaragem.o.d 
	@${RM} ${OBJECTDIR}/src/controleAcessoGaragem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/controleAcessoGaragem.c  -o ${OBJECTDIR}/src/controleAcessoGaragem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/controleAcessoGaragem.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/bsp.o: src/BSP/bsp.c  .generated_files/flags/default/d6f3888a98cc3ef72c6bb0f531f451e556a7127e .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/bsp.c  -o ${OBJECTDIR}/src/BSP/bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/pin_manager.o: src/BSP/pin_manager.c  .generated_files/flags/default/5956abb4900a5550071f38b9f3ea128ed308c297 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/pin_manager.c  -o ${OBJECTDIR}/src/BSP/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/BSP/rfid_bsp.o: src/BSP/rfid_bsp.c  .generated_files/flags/default/fa397e896d95018564f2ee194e5ffed601a00b47 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/BSP" 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o.d 
	@${RM} ${OBJECTDIR}/src/BSP/rfid_bsp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/BSP/rfid_bsp.c  -o ${OBJECTDIR}/src/BSP/rfid_bsp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/BSP/rfid_bsp.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/delay.o: src/delay.c  .generated_files/flags/default/7705c8848aad9a38f68bd91a1790e92cb3eee072 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/delay.o.d 
	@${RM} ${OBJECTDIR}/src/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/delay.c  -o ${OBJECTDIR}/src/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/24LC256.o: src/EEPROM/24LC256.c  .generated_files/flags/default/b1ec4b64c8944a890af1bfe47022e0b14a8cc55e .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/24LC256.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/24LC256.c  -o ${OBJECTDIR}/src/EEPROM/24LC256.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/24LC256.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EEPROM/eeprom.o: src/EEPROM/eeprom.c  .generated_files/flags/default/58369a15cb8b5bfcba5cdbca0eac9dd5ec94e947 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EEPROM" 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/EEPROM/eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EEPROM/eeprom.c  -o ${OBJECTDIR}/src/EEPROM/eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EEPROM/eeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/ext_int.o: src/EXT_INT/ext_int.c  .generated_files/flags/default/b73e77c363c237244a876950f5a7cad848205a06 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/ext_int.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/ext_int.c  -o ${OBJECTDIR}/src/EXT_INT/ext_int.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/ext_int.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/EXT_INT/interrupt_manager.o: src/EXT_INT/interrupt_manager.c  .generated_files/flags/default/3dc06a9a19661f747ec2ba4502f09329d6704f3c .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/EXT_INT" 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/EXT_INT/interrupt_manager.c  -o ${OBJECTDIR}/src/EXT_INT/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/EXT_INT/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/setup_usb.o: src/setup_usb.c  .generated_files/flags/default/be43d725dce0b9ceef644931ce3240a5e3889cee .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/setup_usb.o.d 
	@${RM} ${OBJECTDIR}/src/setup_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/setup_usb.c  -o ${OBJECTDIR}/src/setup_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/setup_usb.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/USR_TCP232.o: src/USR_TCP232.c  .generated_files/flags/default/7b234feffcde073fab96714a6bf12dca1627f297 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/USR_TCP232.o.d 
	@${RM} ${OBJECTDIR}/src/USR_TCP232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/USR_TCP232.c  -o ${OBJECTDIR}/src/USR_TCP232.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/USR_TCP232.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C1/i2c1_driver.o: src/I2C1/i2c1_driver.c  .generated_files/flags/default/3aed09b2cbc4dcaceed92cec5e5b9f6412eeb5a6 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/I2C1" 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C1/i2c1_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C1/i2c1_driver.c  -o ${OBJECTDIR}/src/I2C1/i2c1_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C1/i2c1_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/I2C3/i2c3_driver.o: src/I2C3/i2c3_driver.c  .generated_files/flags/default/b085440cedddb03f408698ceb3aaa8806857297b .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/I2C3" 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o.d 
	@${RM} ${OBJECTDIR}/src/I2C3/i2c3_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/I2C3/i2c3_driver.c  -o ${OBJECTDIR}/src/I2C3/i2c3_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/I2C3/i2c3_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/default/e874494732f7253b78d1478277771f7c556af35c .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/log.c  -o ${OBJECTDIR}/src/log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/log.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/as3993.o: src/RFID/as3993.c  .generated_files/flags/default/5a5a166805d2884b01130758f3378e2e0e2d27e0 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/as3993.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/as3993.c  -o ${OBJECTDIR}/src/RFID/as3993.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/as3993.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RFID/gen2.o: src/RFID/gen2.c  .generated_files/flags/default/a47d879bf74163d9ce141866ad8120d8561e41f2 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RFID" 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o.d 
	@${RM} ${OBJECTDIR}/src/RFID/gen2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RFID/gen2.c  -o ${OBJECTDIR}/src/RFID/gen2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RFID/gen2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/DS1307.o: src/RTC/DS1307.c  .generated_files/flags/default/6f631d00d9836d33022732c17dea0a362c35753 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/DS1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/DS1307.c  -o ${OBJECTDIR}/src/RTC/DS1307.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/DS1307.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/RTC/rtc.o: src/RTC/rtc.c  .generated_files/flags/default/78c0e61132998c3a53e1cc96dfd9d0aef489ca0f .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/RTC" 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/RTC/rtc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/RTC/rtc.c  -o ${OBJECTDIR}/src/RTC/rtc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/RTC/rtc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/spi1.o: src/spi1.c  .generated_files/flags/default/ee08edf75984fd1b5f44938dcd68b8299901a07b .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/spi1.o.d 
	@${RM} ${OBJECTDIR}/src/spi1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/spi1.c  -o ${OBJECTDIR}/src/spi1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/spi1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/tmr2.o: src/tmr2.c  .generated_files/flags/default/f5e6a3e338bdf3263effdb826be290e18b1c6503 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/tmr2.o.d 
	@${RM} ${OBJECTDIR}/src/tmr2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/tmr2.c  -o ${OBJECTDIR}/src/tmr2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/tmr2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/src/uart_driver.o: src/uart_driver.c  .generated_files/flags/default/8012cee553feab5ca2d3a27dade626c211121ce8 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/uart_driver.o.d 
	@${RM} ${OBJECTDIR}/src/uart_driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart_driver.c  -o ${OBJECTDIR}/src/uart_driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/src/uart_driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  .generated_files/flags/default/8d380bb30a2a70c36ba5c8f6b73a72ace00ab557 .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
	@${MKDIR} "${OBJECTDIR}/src/FLASH" 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o.d 
	@${RM} ${OBJECTDIR}/src/FLASH/flash.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  src/FLASH/flash.s  -o ${OBJECTDIR}/src/FLASH/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/src/FLASH/flash.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST) 
	
else
${OBJECTDIR}/src/FLASH/flash.o: src/FLASH/flash.s  .generated_files/flags/default/7c6ae02cbe5968019a67223b14c02c10c068eadd .generated_files/flags/default/51030ad5fcde18c86bd57d8db34c66a7d14e9a57
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
