/*
 * h_exti.c
 *
 * Created: 31/05/2023 21:30:03
 *  Author: 20101
 */ 


#include "h_exti.h"

Std_ReturnType H_EXTI_init(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx)
{
	EXT_vINTERRUPT_Init(EXT_INTx);
}

Std_ReturnType H_EXTI_deinit(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx)
{
	EXT_vINTERRUPT_Denit(EXT_INTx);
}