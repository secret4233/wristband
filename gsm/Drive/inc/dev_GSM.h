#ifndef DEV_GSM_DRIVER
#define DEV_GSM_DRIVER

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"  //Colck Config Library
#include "stm32f10x_tim.h"  //timer Library
#include "stm32f10x_usart.h"//USART Library
#include "stm32f10x_gpio.h" //GPIO Peripheral Library
#include "string.h"  //Used to deal with strings
#include "stdarg.h"  //Used to receive variable parameters

//GSM drivers, and this group of driver function names are started by 'devGSM'

//the Status enum
typedef enum ENUMGSMSTATUS{
	DEV_GSM_OFF,
	DEV_GSM_READY,
	DEV_GSM_NOSIM,
	DEV_GSM_NONETWORK,
	DEV_GSM_EXCEPTION
}E_GSMstatus;

/*
this function initializes the USART and timer of the STM32 used by GSM and power on GSM.
this function returns:
0 == successfully initializing GSM.
1 == fail.
*/
uint8_t devGSMInitialize(void);

/*
this function returns the status of the GSM module.
this function returns:
DEV_GSM_OFF       ==  GSM is not turned on or there is a problem with the USART serial port
DEV_GSM_READY     ==  GSM module can send SMS
DEV_GSM_NOSIM     ==  The GSM module is not inserted into the sim card
DEV_GSM_NONETWORK ==  GSM module is not connected to the network
DEV_GSM_EXCEPTION ==  Used to handle the situation where the GSM module has been inserted into the sim card 
                      and connected to the network, but cannot send SMS
*/
E_GSMstatus devGSMStatus(void);


/*
this function send the message to the target describer and returns the sending result
this function input:
describer == The describer is a char array with a fixed length of 12, 
             including 11 bits phone numbe.
message ==   The message prepate to send.

a example to use:
devGSMSendMessage("18933193265","czpnb")

this function returns:
0 == successfully sending message. 
1 == fail.
*/
uint8_t devGSMSendMessage(char * describer, char * message);

/*
this function power off GSM module.

this function returns:
0 == successfully powered off GSM moudle. 
1 == fail.
*/
uint8_t devGSMDeinitialize(void);


#endif
