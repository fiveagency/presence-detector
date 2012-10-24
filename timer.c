#include "stm32f10x_rcc.h"
#include "misc.h"
#include "timer.h"

void TIM2_Init(void){
	/*  Enable  the  TIM2  gloabal  Interrupt  */
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel  =  TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority  =  1;
	NVIC_InitStructure.NVIC_IRQChannelCmd  =  ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*  Configure and enable  TIM2 timer */
	
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode  = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler  = 7999;
	TIM_TimeBaseStructure.TIM_Period  =  1000;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* Output Compare Timing Mode configuration: Channel1 */
	/* Frozen - The comparison between the output compare register TIMx_CCR1 and the
	counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing
	base).  */
	TIM_OCInitTypeDef    TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	/* OC1 signal is output on the corrisponding output pin */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse  =  0;
	/*  OC1  active  high  */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2,  &TIM_OCInitStructure);
	/* TIMx_CCR1 can be written at anytime, the new value is taken in account immediately */
	TIM_OC1PreloadConfig(TIM2,  TIM_OCPreload_Disable);
	TIM_ITConfig(TIM2,  TIM_IT_CC1,  ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}
