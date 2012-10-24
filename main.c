#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "core_cm3.h"

int history[15] = {};
static int currentHistory = 0;
int reset_counter = 0;


char is_somebody_present(){
    	int i = 0;
    	for (i = 0; i < 15; ++i) {
        	if (history[i]) {
            	return 1;
        	}
    	}
    	return 0;
}

void report_input(int input) {
    	history[currentHistory++] = input;
    	if (currentHistory >= 15) {
        	currentHistory = 0;
    	}
}


void TIM2_IRQHandler(void) {
	if  (TIM_GetITStatus(TIM2,  TIM_IT_CC1)  !=  RESET){
		TIM_ClearITPendingBit(TIM2,  TIM_IT_CC1);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		report_input(GET_SENSOR_STATUS());
		int room_status = is_somebody_present();
		if(room_status == 1){
			LED_ON(LED4);
			USART1_Write_String("\nStatus: 1\n");
		}
		else{
			LED_OFF(LED4);
			USART1_Write_String("\nStatus: 0\n");
		}
	}
	reset_counter+= 1;
	if (reset_counter >= 60 * 5 ){
	    USART1_Write_String("\n\n\nReset.\n\n\n");
        NVIC_SystemReset();
	}
}

int main(void) 
{
	BOARD_GPIO_Init();
	USART1_Init();
	SPI1_Init();
	TIM2_Init();
	USART1_Write_String("\n\n\nInit.\n\n\n");
	LED_ON(LED1);
	simple_server();
	LED_ON(LED2);
	
	while(1){
		 USART1_Write_String("...\n");
		 LED_ON(LED1);
		 LED_ON(LED2);
		 LED_ON(LED3);
		 
	}
}
