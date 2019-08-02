#include "beep.h"
#include "delay.h"

void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				       //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOB.5
 GPIO_ResetBits(GPIOA,GPIO_Pin_9);						             //PB.12 �����
}
 void BEEP_Flashing(int number ,int delay_time)
{
    int i = 0;
	  for(i = 0;i<number;i++)
	  {
	    GPIO_SetBits(GPIOA,GPIO_Pin_9);						             //PB.12 �����
			delay_xms(delay_time);
			GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			delay_xms(delay_time);
	  }
 
}
 void BEEP_OnOff(int isOnOff)
{
	  if(isOnOff == 1)
		   GPIO_SetBits(GPIOA,GPIO_Pin_9);						             //PA.9�����
	  else
			GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}





