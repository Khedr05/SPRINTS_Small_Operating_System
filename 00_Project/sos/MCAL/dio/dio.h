/*
 *  dio.h
 *  Created: 5/15/2023 6:36:12 PM
 *  Author: Momen Hassan 
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "../../COMMON/STD_Types.h"
#include "../../COMMON/BIT_Math.h"
#include "dio_cfg.h"
#include "dio_private.h"
#include "dio_linking_config.h"

void DIO_initpin  (EN_DIO_Pin_type pin,EN_DIO_PinStatus_type status);
void DIO_writepin (EN_DIO_Pin_type pin,EN_DIO_PinVoltage_type volt);
void DIO_readpin(EN_DIO_Pin_type pin,EN_DIO_PinVoltage_type *volt);
void DIO_togglepin(EN_DIO_Pin_type pin);

#endif /* DIO_H_ */