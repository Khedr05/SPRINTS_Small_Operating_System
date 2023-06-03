/*
 * system.h
 *
 * Created: 02/06/2023 17:09:23
 *  Author: sherif
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "std_types.h"
#include "../SERVICES/sos/sos_interface.h"
#include "../ECUAL/h_exti/h_exti.h"
#include "../ECUAL/led/led_interface.h"
#include "../ECUAL/push_button/PB_interface.h"

typedef enum
{
	SYSTEM_INIT_OK = 0,
	SYSTEM_INIT_NOK
}enu_system_init_status_t;


enu_system_init_status_t system_init(void);


#endif /* SYSTEM_H_ */