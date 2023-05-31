/*
 * sos_config.h
 *
 * Created: 5/29/2023 8:24:51 PM
 *  Author: sharb
 */ 


#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_


#define  TIMER_PRESCALLER     8

typedef enum 
{
	TIMER_ZERO,
	TIMER_ONE,
	TIMER_TWO,
}enu_sos_timer_select_t;

typedef struct
{
	void (*ptr_timer_init)                 (void*);
	void (*ptr_timer_deinit)               (void);
	void (*ptr_timer_start)                (Uint16_t);
	void (*ptr_timer_stop)                 (void);
	void (*ptr_timer_set_Tick_time)        (Uint16_t);
	void (*ptr_timer_setCallBack)          (void*);
	
}str_sos_timer_functions_t;


typedef struct  
{
	enu_sos_timer_select_t enu_sos_timer_select;
	str_sos_timer_functions_t str_sos_timer_functions;
}str_sos_configs_t;
#endif /* SOS_CONFIG_H_ */