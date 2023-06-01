/*
 * h_exti.h
 *
 * Created: 31/05/2023 21:29:49
 *  Author: 20101
 */ 


#ifndef H_EXTI_H_
#define H_EXTI_H_

#include "../../MCAL/exti/exti_Interface.h"


Std_ReturnType H_EXTI_init(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx);

Std_ReturnType H_EXTI_deinit(const  ST_EXT_INTERRUPTS_CFG *EXT_INTx);


#endif /* H_EXTI_H_ */