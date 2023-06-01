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
#include "../../ECUAL/push_button/PB_interface.h"
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

ST_PUSH_BTN_t gl_str_start_button = 
{
	.PUSH_BTN_pin = PINC4,
	.PUSH_BTN_connection = PUSH_BTN_PULL_UP,
	.PUSH_BTN_state = PUSH_BTN_STATE_RELEASED
};
ST_EXT_INTERRUPTS_CFG  gl_str_HEXT_Stop_os = 
{
	.EXTERNAL_INTERRUPRT_Number = EXT2_INTERRUPTS,
	.EXTERNAL_INTERRUPRT_Sense_Control = FALLING_EDGE_SENSE_CONTROL,
	.INTERRUPT_EXTERNAL_HANDLER = stop_call_back
};

enu_app_state_t gl_enu_app_state = APP_RUN_OS ; 

str_tasks_config_t gl_str_task1_configs = 
{
	.ptr_task_ref = task1,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 3, //times 100ms the tick time
};

str_tasks_config_t gl_str_task2_configs =
{
	.ptr_task_ref = task2,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 5, //times 100ms the tick time
};
void app_init(void)
{
  LED_initialize(&gl_str_led_task1);
  LED_initialize(&gl_str_led_task2);
  PUSH_BTN_intialize(&gl_str_start_button);
  H_EXTI_init   (&gl_str_HEXT_Stop_os);
  sos_init();
  sos_create_task(PRIORITY_ONE,&gl_str_task1_configs);
  sos_create_task(PRIORITY_TWO,&gl_str_task2_configs);
}
void app_start(void)
{
	EN_PUSH_BTN_state_t loc_en_PUSH_BTN_state = PUSH_BTN_STATE_RELEASED;
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
				PUSH_BTN_read_state(&gl_str_start_button,&loc_en_PUSH_BTN_state);
				if(loc_en_PUSH_BTN_state == PUSH_BTN_STATE_PRESSED)
				{
					gl_enu_app_state = APP_RUN_OS;
				}
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




