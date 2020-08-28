#include "stm32f10x.h"
#include "dev_GSM.h"
#include "devGSM.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
#include "usart2.h"

char send_describer[200];

uint8_t devGSMInitialize(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  			
	USARTX_Init(115200);       	//115200:Baud rate
	TIM3_Int_Init(99,7199);		//99:TIM_Period,7199:TIM_Prescaler	
	USARTX_RX_STA=0;			//flag of accept message
	TIM_Cmd(TIM3,DISABLE);
	if (devGSMStatus == DEV_GSM_OFF)	return 1
	else								return 0;
}


E_GSMstatus devGSMStatus(void){
	if(!sim900a_send_cmd("AT","OK",200) == 0){
		return DEV_GSM_OFF;
	}else if (sim900a_send_cmd("AT+CPIN?","+CPIN: READY",200) != 0){
		return DEV_GSM_NOSIM;
	}else if(sim900a_send_cmd("AT+COPS?","CHINA MOBILE",500) == 0){ 
		return DEV_GSM_READY;
	}else if (sim900a_send_cmd("AT+CSQ","+CSQ: 0,0",200) == 0){
		return DEV_GSM_NONETWORK;
	}else{
		return DEV_GSM_EXCEPTION;
	}
}


uint8_t devGSMSendMessage(char * describer, char * message){
	if(sim900a_send_cmd("AT+CSCS=\"GSM\"","OK",200)){
		printf("AT+CSCS=\"GSM\"--->error\r\n");
		return 1;
	}
	if(sim900a_send_cmd("AT+CMGF=1","OK",200)){
		printf("AT+CMGF=1--->error\r\n");
		return 1;
	}
	sprintf(send_describer,"AT+CMGS=\"%s\"",describer);
	printf(send_describer);//logInfo
	if(sim900a_send_cmd((u8*)send_describer,">",200) == 0){
		u2_printf("%s",message);
		if(sim900a_send_cmd((u8*)0X1A,"+CMGS:",1000)==0){
			printf("send message success\r\n");//logInfo
			return 0;
		}
	}else {
		printf("set describer--->error\r\n");//logInfo
		return 1;
	}
	return 1;
}


uint8_t devGSMDeinitialize(void){
	USART_Cmd(USARTX, ENABLE);
	if (devGSMStatus != DEV_GSM_OFF)	return 1
	else								return 0;
	return 0;
}
