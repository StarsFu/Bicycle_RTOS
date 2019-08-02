#ifndef __BATTERY_H
#define __BATTERY_H	 
#include "sys.h"

#define ADC1_DR_ADDRESS             ((u32)0x4001244C)//ADC1外设的基地址0x40012400 + ADC_DR 0x4c

void Battery_Init(void);
float AdcGetVolt(void);
float BatGetVolt(void);
extern u16 ADC_ConvertedValue[2];		 				    
#endif




