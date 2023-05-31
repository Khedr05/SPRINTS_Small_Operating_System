/*
 * LED_config.h
 *
 *  Created on: 6 Apr 2023
 *      Author: 20101
 */

#ifndef ECU_LED_LED_CONFIG_H_
#define ECU_LED_LED_CONFIG_H_

#include "../../COMMON/std_types.h"

typedef enum
{
    LED_STATUS_OFF = 0,
    LED_STATUS_ON,
}EN_led_status_t;

typedef struct
{
    EN_DIO_Pin_type DIO_Pin_type;
    Uint8_t led_status;
}ST_led_t;



#endif /* ECU_LED_LED_CONFIG_H_ */
