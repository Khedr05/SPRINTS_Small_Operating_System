/*
 * system.h
 *
 * Created: 02/06/2023 17:09:23
 *  Author: 20101
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "std_types.h"
#include "sos_interface.h"
#include "h_exti.h"
#include "led_interface.h"
#include "PB_interface.h"

typedef enum
{
	SYSTEM_INIT_OK = 0,
	SYSTEM_INIT_NOK
}enu_system_init_status_t;


enu_system_init_status_t system_init(void);


#endif /* SYSTEM_H_ */