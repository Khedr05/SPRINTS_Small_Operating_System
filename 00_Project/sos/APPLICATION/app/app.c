/*
 * app.c
 *
 * Created: 31/05/2023 16:19:04
 *  Author: 20101
 */ 

#include "../../COMMON/std_types.h"
#include "../../SERVICES/sos/sos_interface.h"
#include "../../ECUAL/h_exti/h_exti.h"
#include "../../ECUAL/led/led_interface.h"
#include  "app.h"


void task1(void*ptr);
void task2(void*ptr);
void stop_call_back(void);
ST_led_t gl_str_led_task1 =
{
	.DIO_Pin_type = PINB6,
	.led_status   = LED_STATUS_OFF
};

ST_led_t gl_str_led_task2 =
{
	.DIO_Pin_type = PINB5,
	.led_status   = LED_STATUS_OFF
};

ST_EXT_INTERRUPTS_CFG  gl_str_HEXT_Stop_os = 
{
	.EXTERNAL_INTERRUPRT_Number = EXT2_INTERRUPTS,
	.EXTERNAL_INTERRUPRT_Sense_Control = RISING_EDGE_SENSE_CONTROL,
	.INTERRUPT_EXTERNAL_HANDLER = stop_call_back
};

enu_app_state_t gl_enu_app_state = APP_RUN_OS ; 

str_tasks_config_t gl_str_task1_configs = 
{
	.ptr_task_ref = task1,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 300,
};

str_tasks_config_t gl_str_task2_configs =
{
	.ptr_task_ref = task2,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 500,
};
void app_init(void)
{
  LED_initialize(&gl_str_led_task1);
  LED_initialize(&gl_str_led_task2);
  H_EXTI_init   (&gl_str_HEXT_Stop_os);
  sos_init();
  sos_create_task(PRIORITY_ONE,&gl_str_task1_configs);
  sos_create_task(PRIORITY_TWO,&gl_str_task2_configs);
}
void app_start(void)
{
	while (1)
	{
		switch(gl_enu_app_state)
		{
			case APP_RUN_OS : 
			{
				sos_run();
				break;
			}
			
			case APP_STOP_OS :
			{
				/*READ START BUTTON*/
				break;
			}
		}
	}
}

void task1(void*ptr)
{
	LED_toggle(&gl_str_led_task1);
}


void task2(void*ptr)
{
	LED_toggle(&gl_str_led_task2);
}

void stop_call_back(void)
{
	sos_disable();
	gl_enu_app_state =  APP_STOP_OS ;
}




