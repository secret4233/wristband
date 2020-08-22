#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
#include "stdio.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //����GPIO�ṹ�����
	EXTI_InitTypeDef EXTI_InitStruct;	//�����ⲿ�жϽṹ�����
	NVIC_InitTypeDef NVIC_InitStruct;	//�����ж����ȼ��ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);   //ʹ��GPIOB��ʱ�Ӳ���������ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;   //����GPIO��12����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;   //����GPIOΪ��������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   //����GPIO����
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //GPIO��ʼ������
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);   //PB12�ж���ӳ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;   //�ⲿ�ж�ģʽ
	EXTI_InitStruct.EXTI_Line=EXTI_Line12;   //�ж���12
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //�½��ش���
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;   //�ж���ʹ��
	EXTI_Init(&EXTI_InitStruct);   //�ⲿ�жϳ�ʼ������
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;   //�����ⲿ�ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   //������ռ���ȼ�Ϊ0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   //���������ȼ�Ϊ1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);   //�ж����ȼ���ʼ������
}

void KEY_Scan(void)
{
	if(USER_KEY == 0)   //�жϰ����Ƿ���
	{
		Delay_ms(10);   //��ʱ����
		if(USER_KEY == 0)   //�ٴ��жϰ����Ƿ���
		{
			printf("The USER_KEY has been pressed!\r\n");  //����Զ˴����������������Ϣ
		}
	}
}
