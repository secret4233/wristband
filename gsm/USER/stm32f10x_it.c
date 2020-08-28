#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"

#define USART2_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.

u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 USARTX_RX_STA=0;  
#define TIMX TIM3  	
void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USARTX, USART_IT_RXNE) != RESET){	 
		res = USART_ReceiveData(USARTX);		 
		if((USARTX_RX_STA&(1<<15))==0){ 
			if(USARTX_RX_STA<USART2_MAX_RECV_LEN){
				TIM_SetCounter(TIMX,0);
				if(USARTX_RX_STA==0){
					TIM_Cmd(TIMX,ENABLE);
				}
				USARTX_RX_BUF[USARTX_RX_STA++]=res;	
			}else {
				USARTX_RX_STA|=1<<15;				
			} 
		}
	}  				 											 
}  

void TIM3_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIMX, TIM_IT_Update) != RESET)
	{	 			   
		USARTX_RX_STA|=1<<15;	
		TIM_ClearITPendingBit(TIMX, TIM_IT_Update  );     
		TIM_Cmd(TIMX, DISABLE);  
	}	    
}

