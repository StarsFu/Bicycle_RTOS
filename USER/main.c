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
 ALIENTEK ս��STM32F103������ FreeRTOSʵ��2-1
 FreeRTOS��ֲʵ��-�⺯���汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define ADC_TASK_PRIO		2
//�����ջ��С	
#define ADC_STK_SIZE 		50  
//������
TaskHandle_t ADCTask_Handler;
//������
void adc_task(void *pvParameters);

//�������ȼ�
#define LED_TASK_PRIO		3
//�����ջ��С	
#define LED_STK_SIZE 		50  
//������
TaskHandle_t LEDTask_Handler;
//������
void led_task(void *pvParameters);

//�������ȼ�
#define ESC_TASK_PRIO		4
//�����ջ��С	
#define ESC_STK_SIZE 		50  
//������
TaskHandle_t ESCTask_Handler;
//������
void esc_task(void *pvParameters);

//�������ȼ�
#define KEY_TASK_PRIO		5
//�����ջ��С	
#define KEY_STK_SIZE 		50  
//������
TaskHandle_t KEYTask_Handler;
//������
void key_task(void *pvParameters);

float base_bat;
float base_input;
int get_base_gear =0;
int base_gear = 2;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);					//��ʼ������
	LED_Init();		  					//��ʼ��LED
	BEEP_Init(); 
	BEEP_Flashing(2,100);
	Battery_Init();
	ESC_Init(19999,71);
	KEY_Init();
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����ADC����
    xTaskCreate((TaskFunction_t )adc_task,     	
                (const char*    )"adc_task",   	
                (uint16_t       )ADC_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ADC_TASK_PRIO,	
                (TaskHandle_t*  )&ADCTask_Handler);   
    //����LED����
    xTaskCreate((TaskFunction_t )led_task,     
                (const char*    )"led_task",   
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);   
    //����ESC����
    xTaskCreate((TaskFunction_t )esc_task,     
                (const char*    )"esc_task",   
                (uint16_t       )ESC_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )ESC_TASK_PRIO,
                (TaskHandle_t*  )&ESCTask_Handler); 	
    //����KEY����
    xTaskCreate((TaskFunction_t )key_task,     
                (const char*    )"key_task",   
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KEYTask_Handler); 								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//ADC������ 
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

//LED������
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
//ESC������
void esc_task(void *pvParameters)
{
    while(1)
    {
        ESC_Spin(1526);
			  vTaskDelay(1);
    }
}
//KEY������
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


