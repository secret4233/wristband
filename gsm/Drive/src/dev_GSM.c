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
	return 0;
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
			printf("send message success\r\n");
			return 0;
		}
	}else {
		printf("set describer--->error\r\n");
		return 1;
	}
	return 1;
}


uint8_t devGSMDeinitialize(void){
	return 0;
}
