#include "esc.h"
#include "stdlib.h"
void ESC_Init(int arr,int psc)
{
  TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_BaseInitStructure.TIM_Period                = arr;
	TIM_BaseInitStructure.TIM_Prescaler             = psc;
	TIM_BaseInitStructure.TIM_ClockDivision         = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode           = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter     = 0;

	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_Cmd(TIM1, ENABLE);  //使能TIM2
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void ESC_Spin(int value)
{
   TIM_SetCompare1(TIM1, abs(value));

}










