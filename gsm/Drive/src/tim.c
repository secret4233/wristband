#include "stm32f10x.h"
#include "tim.h"
void TIM3_Int_Init(uint16_t per, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct; 
	NVIC_InitTypeDef NVIC_InitStruct; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  
	
	TIM_TimeBaseInitStruct.TIM_Period=per;   
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);   
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;  
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;  
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;   
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStruct);   
	
	TIM_Cmd(TIM3,ENABLE);   
}


