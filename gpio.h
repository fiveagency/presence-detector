#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x_gpio.h"

#define LED1 GPIO_Pin_3
#define LED2 GPIO_Pin_4
#define LED3 GPIO_Pin_5
#define LED4 GPIO_Pin_6

void BOARD_GPIO_Init(void);
void LED_ON(int i);
void LED_OFF(int i);
char GET_SENSOR_STATUS(void);

#endif
