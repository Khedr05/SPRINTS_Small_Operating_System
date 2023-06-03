/*
 * app.c
 *
 * Created: 31/05/2023 16:19:04
 *  Author: sherif
 */ 


#include  "app.h"


void task1(void*ptr);
void task2(void*ptr);


str_tasks_t gl_str_task1_configs =
{
	.ptr_task_ref = task1,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 3, //times 100ms the tick time
};

str_tasks_t gl_str_task2_configs =
{
	.ptr_task_ref = task2,
	.ptr_task_arg = STR_NULL,
	.taskPeriodicity = 5, //times 100ms the tick time
};

enu_app_state_t gl_enu_app_state = APP_RUN_OS ;


void app_start(void)
{
	EN_PUSH_BTN_state_t loc_en_PUSH_BTN_state = PUSH_BTN_STATE_RELEASED;
	if(system_init() == SYSTEM_INIT_OK)
	{
		sos_create_task(PRIORITY_ONE,&gl_str_task1_configs);
		sos_create_task(PRIORITY_TWO,&gl_str_task2_configs);
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
					if(loc_en_PUSH_BTN_state == PUSH_BTN_STATE_RELEASED)
					{
						gl_enu_app_state = APP_RUN_OS;
					}
					break;
				}
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




