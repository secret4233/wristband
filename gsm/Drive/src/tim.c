#include "stm32f10x.h"
#include "tim.h"
void TIM3_Int_Init(uint16_t per, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //���嶨ʱ���ṹ�����
	NVIC_InitTypeDef NVIC_InitStruct;   //�����ж����ȼ��ṹ�����
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ��TIM3��ʱ��
	
	TIM_TimeBaseInitStruct.TIM_Period=per;   //�����Զ���װ�ص�����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //����Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;   //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);   //��ʱ����ʼ������
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //TIM3�ж�ʹ��
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;   //TIM3�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;   //��ռ���ȼ�0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;   //�����ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //ʹ��TIM3�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);   //�ж����ȼ���ʼ������
	
	TIM_Cmd(TIM3,ENABLE);   //TIM3ʹ��
}

//void TIM_Init(uint16_t per, uint16_t psc)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;   //����GPIO�ṹ�����
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //���嶨ʱ���ṹ�����
//	TIM_OCInitTypeDef TIM_OCInitStruct;   //��������ȽϽṹ�����
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);   //GPIOAʱ��ʹ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ��TIM3��ʱ��
//	
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;   //����GPIO��6����
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   //����GPIOΪ�����������
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   //����GPIO����
//	GPIO_Init(GPIOA,&GPIO_InitStruct);   //GPIO��ʼ������
//	
//	TIM_TimeBaseInitStruct.TIM_Period=per;   //�����Զ���װ�ص�����ֵ
//	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //����Ԥ��Ƶֵ
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���ģʽ
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;   //����ʱ�ӷָ�
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);   //��ʱ����ʼ������
//	
//	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWMģʽ1
//	TIM_OCInitStruct.TIM_Pulse=0;   //��ʼ��ռ�ձ�Ϊ0
//	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;   //����Ƚϼ��Ե�
//	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   //�Ƚ����ʹ��
//	TIM_OC1Init(TIM3,&TIM_OCInitStruct);   //�Ƚ������ʼ������
//	
//	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);   //����Ƚ�1Ԥװ�ؼĴ���ʹ��
//	
//	TIM_Cmd(TIM3,ENABLE);   //TIM3ʹ��
//}

