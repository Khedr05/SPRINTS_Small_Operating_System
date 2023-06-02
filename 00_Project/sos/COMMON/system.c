/*
 * system.c
 *
 * Created: 02/06/2023 17:06:18
 *  Author: 20101
 */ 

#include "system.h"

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
	.PUSH_BTN_connection = PUSH_BTN_PULL_DOWN,
	.PUSH_BTN_state = PUSH_BTN_STATE_RELEASED
};
ST_EXT_INTERRUPTS_CFG  gl_str_HEXT_Stop_os =
{
	.EXTERNAL_INTERRUPRT_Number = EXT2_INTERRUPTS,
	.EXTERNAL_INTERRUPRT_Sense_Control = RISING_EDGE_SENSE_CONTROL,
	.INTERRUPT_EXTERNAL_HANDLER = stop_call_back
};




enu_system_init_status_t system_init(void)
{
	enu_system_init_status_t ret = SYSTEM_INIT_NOK;
	if(LED_initialize(&gl_str_led_task1) == E_OK && LED_initialize(&gl_str_led_task2) == E_OK)
	{
		if(PUSH_BTN_intialize(&gl_str_start_button) == E_OK)
		{
			if(H_EXTI_init(&gl_str_HEXT_Stop_os) == E_OK)
			{
					if(sos_init() == SOS_STATUS_SUCCESS)
					{
						ret = SYSTEM_INIT_OK;
					}	
			}		
		}	
	}
	return ret;
}