#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

BOARD_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable GPIOE and GPIOA clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* Configure GPIOE pins */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* Sensor bit */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_ON(int i){
	GPIO_SetBits(GPIOE, i);
}

void LED_OFF(int i){
	GPIO_ResetBits(GPIOE, i);
}

char GET_SENSOR_STATUS(void){
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
}	

		
