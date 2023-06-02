/*
 * LED_prog.c
 *
 *  Created on: 6 Apr 2023
 *      Author: 20101
 */



#include "LED_interface.h"

Std_ReturnType LED_initialize(const ST_led_t *led)
{
	Std_ReturnType ret = E_OK;
	if(PTR_NULL == led)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
		DIO_initpin(led->DIO_Pin_type,OUTPUT);
	}
	return ret;
}
Std_ReturnType LED_turn_on(const ST_led_t *led)
{
	Std_ReturnType ret = E_OK;
	if(PTR_NULL == led)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
		DIO_writepin(led->DIO_Pin_type, OUTPUT_HIGH);
	}
	return ret;
}
Std_ReturnType LED_turn_off(const ST_led_t *led)
{
	Std_ReturnType ret = E_OK;
	if(PTR_NULL == led)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
		DIO_writepin(led->DIO_Pin_type, OUTPUT_LOW);
	}
	return ret;
}
Std_ReturnType LED_toggle(const ST_led_t *led)
{
	Std_ReturnType ret = E_OK;
	if(PTR_NULL == led)
	{
		ret = E_NOT_OK;
	}
	else
	{
	   DIO_togglepin(led->DIO_Pin_type);
	}
	return ret;
}
