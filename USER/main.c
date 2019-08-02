#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "FreeRTOS.h"
#include "task.h"

#include "led.h"
#include "beep.h"
#include "esc.h"
#include "battery.h"
#include "key.h"
/************************************************
 ALIENTEK 战舰STM32F103开发板 FreeRTOS实验2-1
 FreeRTOS移植实验-库函数版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define ADC_TASK_PRIO		2
//任务堆栈大小	
#define ADC_STK_SIZE 		50  
//任务句柄
TaskHandle_t ADCTask_Handler;
//任务函数
void adc_task(void *pvParameters);

//任务优先级
#define LED_TASK_PRIO		3
//任务堆栈大小	
#define LED_STK_SIZE 		50  
//任务句柄
TaskHandle_t LEDTask_Handler;
//任务函数
void led_task(void *pvParameters);

//任务优先级
#define ESC_TASK_PRIO		4
//任务堆栈大小	
#define ESC_STK_SIZE 		50  
//任务句柄
TaskHandle_t ESCTask_Handler;
//任务函数
void esc_task(void *pvParameters);

//任务优先级
#define KEY_TASK_PRIO		5
//任务堆栈大小	
#define KEY_STK_SIZE 		50  
//任务句柄
TaskHandle_t KEYTask_Handler;
//任务函数
void key_task(void *pvParameters);

float base_bat;
float base_input;
int get_base_gear =0;
int base_gear = 2;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);					//初始化串口
	LED_Init();		  					//初始化LED
	BEEP_Init(); 
	BEEP_Flashing(2,100);
	Battery_Init();
	ESC_Init(19999,71);
	KEY_Init();
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建ADC任务
    xTaskCreate((TaskFunction_t )adc_task,     	
                (const char*    )"adc_task",   	
                (uint16_t       )ADC_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ADC_TASK_PRIO,	
                (TaskHandle_t*  )&ADCTask_Handler);   
    //创建LED任务
    xTaskCreate((TaskFunction_t )led_task,     
                (const char*    )"led_task",   
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);   
    //创建ESC任务
    xTaskCreate((TaskFunction_t )esc_task,     
                (const char*    )"esc_task",   
                (uint16_t       )ESC_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )ESC_TASK_PRIO,
                (TaskHandle_t*  )&ESCTask_Handler); 	
    //创建KEY任务
    xTaskCreate((TaskFunction_t )key_task,     
                (const char*    )"key_task",   
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KEYTask_Handler); 								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//ADC任务函数 
void adc_task(void *pvParameters)
{
    while(1)
    {
      base_bat = BatGetVolt();
			delay_xms(10);
			base_input = AdcGetVolt() ;
      vTaskDelay(1);
    }
}   

//LED任务函数
void led_task(void *pvParameters)
{
    while(1)
    {
        LEDG=0;
        vTaskDelay(200);
        LEDG=1;
        vTaskDelay(200);
    }
}
//ESC任务函数
void esc_task(void *pvParameters)
{
    while(1)
    {
        ESC_Spin(1526);
			  vTaskDelay(1);
    }
}
//KEY任务函数
void key_task(void *pvParameters)
{
    while(1)
    {
        get_base_gear =  KEY_Scan(0);
			  if(get_base_gear == 1)
					base_gear = 1;
				if(get_base_gear == 2)
					base_gear = 3;
				else 
					base_gear = 2;
			  vTaskDelay(1);
    }

}


