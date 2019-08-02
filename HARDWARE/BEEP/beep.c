#include "beep.h"
#include "delay.h"

void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				       //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					         //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOA,GPIO_Pin_9);						             //PB.12 输出高
}
 void BEEP_Flashing(int number ,int delay_time)
{
    int i = 0;
	  for(i = 0;i<number;i++)
	  {
	    GPIO_SetBits(GPIOA,GPIO_Pin_9);						             //PB.12 输出高
			delay_xms(delay_time);
			GPIO_ResetBits(GPIOA,GPIO_Pin_9);
			delay_xms(delay_time);
	  }
 
}
 void BEEP_OnOff(int isOnOff)
{
	  if(isOnOff == 1)
		   GPIO_SetBits(GPIOA,GPIO_Pin_9);						             //PA.9输出高
	  else
			GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}





