/*
 * app.h
 *
 * Created: 31/05/2023 16:19:17
 *  Author: 20101
 */ 


#ifndef APP_H_
#define APP_H_



typedef enum
{
	APP_RUN_OS,
	APP_STOP_OS
}enu_app_state_t;

void app_init(void);
void app_start(void);


#endif /* APP_H_ */