# ARM-MKD toolchain setup
# -------------------------------------------------------------------------------------------------
PREFIX := arm-none-eabi-
CFLAGS :=   -c -nostartfiles -mcpu=cortex-m3 -mthumb
 
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

# -------------------------------------------------------------------------------------------------
# CMSIS & Standard Firmware Library directories
# -------------------------------------------------------------------------------------------------
CMSIS_DIR     = ./CMSIS
STDPERIPH_DIR = ./STM32F10x_StdPeriph_Driver
# -------------------------------------------------------------------------------------------------
  
# Library setup
# -------------------------------------------------------------------------------------------------
LIB_DEF       = -D STM32F10X_MD
LIB_DEF      += -D USE_STDPERIPH_DRIVER
 
LIB_INC       = -I $(CMSIS_DIR)/CM3/CoreSupport
LIB_INC      += -I $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x
LIB_INC      += -I $(STDPERIPH_DIR)/inc
 
LIB_SRC       = $(CMSIS_DIR)/CM3/CoreSupport/core_cm3.c
LIB_SRC      += $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
LIB_SRC      += $(STDPERIPH_DIR)/src/misc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_adc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_bkp.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_can.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_cec.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_crc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_dac.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_dbgmcu.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_dma.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_exti.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_flash.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_fsmc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_gpio.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_i2c.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_iwdg.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_pwr.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_rcc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_rtc.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_sdio.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_spi.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_tim.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_usart.c
LIB_SRC      += $(STDPERIPH_DIR)/src/stm32f10x_wwdg.c
 
LIB_OBJ       = $(LIB_SRC:.c=.o)
# -------------------------------------------------------------------------------------------------
 

.PHONY : all libs
 
%.o : %.c
	$(CC) $(CFLAGS) $(LIB_INC) $(INCLUDES) $(LIB_DEF) -o $@ -c $<
 
libs : $(LIB_OBJ)
 
clean : 
	rm $(STDPERIPH_DIR)/src/*.o
	rm $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x/*.o	
	rm $(CMSIS_DIR)/CM3/CoreSupport/*.o 
	rm $(STARTUP_DIR)/*.o ./*.a
