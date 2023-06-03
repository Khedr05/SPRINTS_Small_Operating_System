/*
 * dio_linking_config.h
 *
 * Created: 5/14/2023 10:30:00 AM
 *  Author: momen
 */ 

#ifndef DIO_LINKING_CONFIG_H
#define DIO_LINKING_CONFIG_H
#include "dio_private.h"

typedef enum{
	PORT_A=0,
	PORT_B,
	PORT_C,
	PORT_D
}EN_DIO_Port_type;

typedef enum{
	OUTPUT,
	INFREE,
	INPULL
}EN_DIO_PinStatus_type;

typedef enum{
	OUTPUT_LOW=0,
	OUTPUT_HIGH,
}EN_DIO_PinVoltage_type;


typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}EN_DIO_Pin_type;

#endif /* DIO_LINKING_CONFIG_H */