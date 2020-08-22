#include "stm32f10x.h"
#include "stm32f10x_it.h"

#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "tim.h"
#include "usart.h"
#include "devGSM.h"
#include "usart2.h"
#include "dev_GSM.h"


int main(void)
{
	E_GSMstatus status;
	uint8_t flag_success;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //设置NVIC中断分组为2
	LED_Init();   //LED初始化
	Delay_Init();   //延时初始化
	USART_init(115200);
	USARTX_init(115200);
	TIM3_Int_Init(99,7199);		//10ms中断
	USART2_RX_STA=0;		//清零
	TIM_Cmd(TIM3,DISABLE);			//关闭定时器7
//	KEY_Init();   //按键初始化
	printf("This is ready\r\n");  

	
	
	
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay_ms(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay_ms(500);
		
		status = devGSMStatus();
		printf("status: %d\r\n",status);
		if (status == 1) {
			flag_success = devGSMSendMessage("17513123446","czpnb");
			printf("is success? %d\r\n",flag_success);
			break;
		}
	}
}

