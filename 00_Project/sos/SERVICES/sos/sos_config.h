/*
 * sos_config.h
 *
 * Created: 5/29/2023 8:24:51 PM
 *  Author: sharb
 */ 


#ifndef SOS_CONFIG_H_
#define SOS_CONFIG_H_




typedef struct
{
	void (*ptr_timer_init)                 (void*);
	void (*ptr_timer_deinit)               (void);
	void (*ptr_timer_start)                (void);
	void (*ptr_timer_stop)                 (void);
	void (*ptr_timer_set_Tick_time)        (Uint16_t);
	void (*ptr_timer_setCallBack)          (void*);
	
}str_sos_timer_functions_t;


typedef struct  
{
	str_sos_timer_functions_t str_sos_timer_functions;
}str_sos_helpers_t;
#endif /* SOS_CONFIG_H_ */