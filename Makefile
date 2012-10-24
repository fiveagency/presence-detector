#stm32 project makefile

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OB = arm-none-eabi-objcopy

.PHONY: all clean

CFLAGS := -c -nostartfiles -mcpu=cortex-m3 -mthumb
 
LIB_DEF       = -D STM32F10X_HD
LIB_DEF      += -D USE_STDPERIPH_DRIVER
 
LIB_INC       = -I ./Libraries/CMSIS/CM3/CoreSupport
LIB_INC      += -I ./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
LIB_INC      += -I ./Libraries/STM32F10x_StdPeriph_Driver/inc

#LIB_OBJ     = ./Libraries/CMSIS/CM3/CoreSupport/core_cm3.o
#LIB_OBJ     += ./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/misc.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.o
LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.o
#LIB_OBJ     += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.o 



WORK_OBJ = startup_stm32f10x_hd.o main.o  gpio.o spi.o usart.o enc28j60.o simple_server.o ip_arp_udp_tcp.o timer.o


all: presence_detector.bin

%.o : %.c
	$(CC) $(CFLAGS) $(LIB_INC) $(LIB_DEF) -o $@ -c $<
	
%.o : %.s
	$(AS) -mcpu=cortex-m3 -mthumb -o $@ -c $<
	
presence_detector.out: $(WORK_OBJ) stm32f103vet6.ld
	$(LD) -T stm32f103vet6.ld -o presence_detector.out $(LIB_OBJ) $(WORK_OBJ)

presence_detector.bin: presence_detector.out
	$(OB) -O binary presence_detector.out presence_detector.bin

clean:
	rm -f *.o *.out *.bin
