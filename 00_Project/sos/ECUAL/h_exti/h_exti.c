/*
 * h_exti.c
 *
 * Created: 31/05/2023 21:30:03
 *  Author: 20101
 */ 


#include "h_exti.h"

void H_EXTI_init(void)
{
	EXT_vINTERRUPT_Init();
}

void H_EXTI_deinit(void)
{
	EXT_vINTERRUPT_Denit();
}