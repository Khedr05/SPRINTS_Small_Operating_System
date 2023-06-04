/*
 * app.h
 *
 * Created: 31/05/2023 16:19:17
 *  Author: 20101
 */ 


#ifndef APP_H_
#define APP_H_

#include "system.h"


extern ST_led_t gl_str_led_task1;
extern ST_led_t gl_str_led_task2;
extern ST_PUSH_BTN_t gl_str_start_button;
extern ST_EXT_INTERRUPTS_CFG  gl_str_HEXT_Stop_os;
extern void stop_call_back(void);

typedef enum
{
	APP_RUN_OS,
	APP_STOP_OS
}enu_app_state_t;

void app_init(void);
void app_start(void);


#endif /* APP_H_ */