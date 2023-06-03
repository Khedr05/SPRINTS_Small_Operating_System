/*
 * PB_prog.c
 *
 *  Created on: 6 Apr 2023
 *      Author: 20101
 */

#include"PB_interface.h"

Std_ReturnType PUSH_BTN_intialize(const ST_PUSH_BTN_t *btn)
{
	Std_ReturnType ret = E_NOT_OK;
	if(PTR_NULL == btn)
	{
		ret = E_NOT_OK;
	}
	else
	{
		DIO_initpin(btn->PUSH_BTN_pin,INFREE);
		ret = E_OK;
	}
	return ret;
}

Std_ReturnType PUSH_BTN_read_state(const ST_PUSH_BTN_t *btn , EN_PUSH_BTN_state_t *btn_state)
{
	Std_ReturnType ret = E_NOT_OK;
	if(PTR_NULL == btn || PTR_NULL == btn_state )
	{
		ret = E_NOT_OK;
	}
	else
	{
		EN_DIO_PinVoltage_type pin_logic_status = OUTPUT_LOW;
		DIO_readpin(btn->PUSH_BTN_pin,&pin_logic_status);
		if(PUSH_BTN_PULL_UP == btn->PUSH_BTN_connection)
		{
			if(OUTPUT_HIGH == pin_logic_status)
			{
				*btn_state = PUSH_BTN_STATE_RELEASED;
			}
			else
			{
				*btn_state = PUSH_BTN_STATE_PRESSED;
			}
		}
		else if(PUSH_BTN_PULL_DOWN == btn->PUSH_BTN_connection)
		{
			if(OUTPUT_LOW == pin_logic_status)
			{
				*btn_state = PUSH_BTN_STATE_PRESSED;
			}
			else
			{
				*btn_state = PUSH_BTN_STATE_RELEASED;
			}
		}
		else{/* nothing */}
		ret = E_OK;
	}

	return ret;
}
