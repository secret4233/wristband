#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"
#include "devGSM.h"
#include "string.h"
#include "usart.h"

#define GPIO_Pin_TX GPIO_Pin_2
#define GPIO_Pin_RX GPIO_Pin_3
#define USARTX USART2

void USARTX_init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStruct;   
	USART_InitTypeDef USART_InitStruct;   
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB1Periph_USART2,ENABLE);  
	
	USART_DeInit(USART2);  //复位串口3
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_TX;   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitStruct);   
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_RX;   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;   
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   
	GPIO_Init(GPIOA,&GPIO_InitStruct);   
	
	
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;   
	USART_InitStruct.USART_Parity=USART_Parity_No;   
	USART_InitStruct.USART_BaudRate=bound;   
	USART_InitStruct.USART_StopBits=USART_StopBits_1;   
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;   
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   
	USART_Init(USARTX,&USART_InitStruct);   
	
	USART_Cmd(USARTX, ENABLE);                    //使能串口 
	
	//使能接收中断
  USART_ITConfig(USARTX, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

}

void u2_printf(char* fmt,...)  
{  
	uint16_t i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	printf("%s\r\n",USART2_TX_BUF);
	for(j=0;j<i;j++)							//循环发送数据
	{
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)== RESET){  //循环发送,直到发送完毕  
		};  
	} 
}


