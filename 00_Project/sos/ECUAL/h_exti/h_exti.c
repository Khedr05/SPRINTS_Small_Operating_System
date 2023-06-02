/*
 * h_exti.c
 *
 * Created: 31/05/2023 21:30:03
 *  Author: 20101
 */ 


#include "h_exti.h"

Std_ReturnType H_EXTI_init(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx)
{
	if(EXT_vINTERRUPT_Init(EXT_INTx) == E_OK)
	{
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}

Std_ReturnType H_EXTI_deinit(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx)
{
	if(EXT_vINTERRUPT_Denit(EXT_INTx) == E_OK)
	{
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}