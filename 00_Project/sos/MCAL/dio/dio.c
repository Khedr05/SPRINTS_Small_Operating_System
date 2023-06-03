/*
 * Dio.c
 *
 * Created: 5/15/2023 5:42:04 PM
 *    Author: momen hassan
 */ 
#include "dio.h"

void  DIO_initpin(EN_DIO_Pin_type pin,EN_DIO_PinStatus_type status)
{
	EN_DIO_Port_type port = pin/8 ;
	Uint8_t pin_num =pin % 8;
	
	if (pin_num < 8)
	{

		switch(status)
		{
			case OUTPUT:
			switch(port)
			{
				case PORT_A:
				SET_BIT( DIO_PORTA_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTA_PORT_REG,pin_num);
				break;
				case PORT_B:
				SET_BIT( DIO_PORTB_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTB_PORT_REG,pin_num);
				break;
				case PORT_C:
				SET_BIT( DIO_PORTC_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTC_PORT_REG,pin_num);
				break;
				case PORT_D:
				SET_BIT( DIO_PORTD_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTD_PORT_REG,pin_num);
				break;
				default:
				break;
			}
			break;
			case INFREE:
			switch(port)
			{
				case PORT_A:
				CLEAR_BIT(DIO_PORTA_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTA_PORT_REG,pin_num);
				break;
				case PORT_B:
				CLEAR_BIT(DIO_PORTB_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTB_PORT_REG,pin_num);
				break;
				case PORT_C:
				CLEAR_BIT(DIO_PORTC_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTC_PORT_REG,pin_num);
				break;
				case PORT_D:
				CLEAR_BIT(DIO_PORTD_DDR_REG,pin_num);
				CLEAR_BIT(DIO_PORTD_PORT_REG,pin_num);
				break;
				default:
				break;
			}
			break;

			case INPULL:
			switch(port)
			{
				case PORT_A:
				CLEAR_BIT(DIO_PORTA_DDR_REG,pin_num);
				SET_BIT(DIO_PORTA_PORT_REG,pin_num);
				break;
				case PORT_B:
				CLEAR_BIT(DIO_PORTB_DDR_REG,pin_num);
				SET_BIT(DIO_PORTB_PORT_REG,pin_num);
				break;
				case PORT_C:
				CLEAR_BIT(DIO_PORTC_DDR_REG,pin_num);
				SET_BIT(DIO_PORTC_PORT_REG,pin_num);
				break;
				case PORT_D:
				CLEAR_BIT(DIO_PORTD_DDR_REG,pin_num);
				SET_BIT(DIO_PORTD_PORT_REG,pin_num);
				break;
				default:
				break;
			}
			break;
			default:
			break;
		}
	}
	else
	{
	}

}

void  DIO_writepin(EN_DIO_Pin_type pin,EN_DIO_PinVoltage_type volt)
{
	EN_DIO_Port_type port = pin/8 ;
	Uint8_t pin_num =pin % 8;
	if (pin_num<8)
	{
		switch (volt)
		{
			case OUTPUT_HIGH:

			switch(port)
			{
				case PORT_A:

				SET_BIT(DIO_PORTA_PORT_REG,pin_num);
				break;
				case PORT_B:

				SET_BIT(DIO_PORTB_PORT_REG,pin_num);
				break;
				case PORT_C:

				SET_BIT(DIO_PORTC_PORT_REG,pin_num);
				break;
				case PORT_D:

				SET_BIT(DIO_PORTD_PORT_REG,pin_num);
				break;
				default:
				break;
			}
			break;

			case OUTPUT_LOW:

			switch(port)
			{
				case PORT_A:

				CLEAR_BIT(DIO_PORTA_PORT_REG,pin_num);
				break;
				case PORT_B:

				CLEAR_BIT(DIO_PORTB_PORT_REG,pin_num);
				break;
				case PORT_C:

				CLEAR_BIT(DIO_PORTC_PORT_REG,pin_num);
				break;
				case PORT_D:

				CLEAR_BIT(DIO_PORTD_PORT_REG,pin_num);
				break;
				default:
				break;
			}

			break;

			default:
			break;

		}
	}
	else
	{
	}

}
void  DIO_readpin(EN_DIO_Pin_type pin,EN_DIO_PinVoltage_type *volt)
{
	EN_DIO_Port_type port = pin/8 ;
	Uint8_t pin_num =pin % 8;
	if (pin_num < 8)
	{

		switch(port)
		{
			case PORT_A:

			*volt=GET_BIT(DIO_PORTA_PIN_REG,pin_num);
			break;
			case PORT_B:

			*volt=GET_BIT(DIO_PORTB_PIN_REG,pin_num);
			break;
			case PORT_C:

			*volt=GET_BIT(DIO_PORTC_PIN_REG,pin_num);
			break;
			case PORT_D:

			*volt=GET_BIT(DIO_PORTD_PIN_REG,pin_num);
			break;
			default:
			break;
		}

	}
	else
	{
	}
}
void  DIO_togglepin(EN_DIO_Pin_type pin)
{
	EN_DIO_Port_type port = pin/8 ;
	Uint8_t pin_num =pin % 8;
	if (pin_num< 8)
	{
		switch(port)
		{
			case PORT_A:
			TOGGLE_BIT(DIO_PORTA_PORT_REG,pin_num);
			break;
			case PORT_B:
			TOGGLE_BIT(DIO_PORTB_PORT_REG,pin_num);
			break;
			case PORT_C:
			TOGGLE_BIT(DIO_PORTC_PORT_REG,pin_num);
			break;
			case PORT_D:
			TOGGLE_BIT(DIO_PORTD_PORT_REG,pin_num);
			break;
			default:
			break;
		}
	}
	else
	{
	}
}


