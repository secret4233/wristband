#ifndef   _KEY_H
#define   _KEY_H

#define   USER_KEY     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)   //��PB12�ܽź궨��


void KEY_Init(void);   //������ʼ��
void KEY_Scan(void);   //����ɨ��

#endif

