#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void USART1_Init(void)
{
	USART_InitTypeDef  USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable SPI1 and GPIOA clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	/* Configure USART1 pins: USART1_TX*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART1 pins: USART1_RX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1 configuration */ 
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    	USART_Init(USART1, &USART_InitStructure);
    	USART_Cmd(USART1, ENABLE);
}


void USART1_Write_Char(char data){
  	/* Transmit this character using USART */
  	USART_SendData(USART1, (char) data);
  
  	/* Wait until the transmit is done */
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}  

void USART1_Write_String(char *data){
    	int   i = 0;

    	while(data[i] != 0) {
        	USART1_Write_Char(data[i++]);
    	}
} 


unsigned char USART1_Read_Char(void){
    	/* Wait until the data is ready to be received. */
    	while (USART_GetFlagStatus(USART1, USART_SR_RXNE) == RESET);
   	 
  	/* Receive char from USART */
  	return USART_ReceiveData(USART1);	
} 


