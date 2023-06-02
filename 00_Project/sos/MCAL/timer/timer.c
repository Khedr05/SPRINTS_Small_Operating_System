/*
* TMR_Program.c
*
*     Created on: Apr 11, 2023
*         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
*    Description: This file contains all TMRs (TMR) functions' implementation, and ISR functions' prototypes and implementation.
*		MCU Datasheet: AVR ATmega32
*                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
*/
/*************************************************************************************************/
#include "timer_private.h"
#include "timer_config.h"
#include "timer_interface.h"
#include <math.h>
/* ***********************************************************************************************/
/* Declaration and Initialization */

Uint8_t u8_g_timeOut = 0;
Uint8_t u8_l_mode = POLLING;

Uint16_t u16_g_TMR1Overflow = 0;
Uint16_t u16_g_overflowNumbers = 0;
Uint16_t u16_g_overflowTicks = 0;
Uint16_t u16_g_tcnt0InitialVal = 0;

Uint16_t u16_g_overflow2Ticks = 0;
Uint16_t u16_g_overflow2Numbers = 0;
Uint16_t u16_g_tcnt2InitialVal = 0;
Uint16_t u16_g_prescaler = 256;

Uint8_t * u8_g_TMRShutdownFlag = PTR_NULL;

void (*void_g_pfOvfInterruptAction)(void) = PTR_NULL;

/*************************************************************************************************/

/**
* @brief Initializes TMR2 at normal mode
*
* This function initializes/selects the TMR_2 normal mode for the TMR, and enable the ISR for this TMR.
* @param[in] EN_TMR_INTERRPUT_T en_a_interrputEnable value to set the interrupt bit for TMR_2 in the TIMSK reg.
* @param[in] **u8_a_shutdownFlag double pointer, acts as a main switch for TMR 2 operations.
*
* @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
*         (TMR_OK if the operation succeeded, TMR_ERROR otherwise)
*/
EN_TIMER_ERROR_T TIMER_TMR2NormalModeInit(EN_TIMER_INTERRPUT_T en_a_interrputEnable) {

	switch (en_a_interrputEnable) {
		case ENABLED:
		/* select the normal mode for the TMR, TMR is not start yet.*/
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM20_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM21_BIT);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(TMR_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for TMR0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE2_BIT);
		break;
		case DISABLED:
		/* select the normal mode for the TMR, TMR is not start yet.*/
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM20_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM21_BIT);
		break;
		default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}

/* ***********************************************************************************************/

/**
* @brief Creates a delay using TMR_2 in overflow mode
*
* This function Creates the desired delay on TMR_2 normal mode using inteerupt.
* @param[in] Uint16_t u16_a_interval value to set the desired delay.
*
* @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
*         (TMR_OK if the operation succeeded, TMR_ERROR otherwise)
*/
EN_TIMER_ERROR_T TMR_intDelay_ms(Uint16_t u16_a_interval) {
	if ( ( u16_a_interval / SECOND_OPERATOR ) > ( MAX_TIMER_DELAY ) ) {
		return TIMER_ERROR;
	}
	else {
		/* Clear the TCCR Register*/
		TMR_U8_TCCR2_REG = 0x00;
		/*Get the time in second*/
		float64_t d64_a_delay = (u16_a_interval / SECOND_OPERATOR);
		u16_g_overflow2Numbers = ceil(d64_a_delay / MAX_DELAY);
		TMR_U8_TCNT2_REG = (Uint8_t) ((MAX_COUNTS) - ((d64_a_delay - (MAX_DELAY * (u16_g_overflow2Numbers - 1.0))) /
		TICK_TIME)); // in decimal  (0 - 255)
		u16_g_tcnt2InitialVal = TMR_U8_TCNT2_REG;
		u16_g_overflow2Ticks = 0;
	}
	

	return TIMER_OK;
}

/* *************************************************************************************************/
/**
* @brief Start the TMR by setting the desired prescaler.
*
* This function set the prescaler for TMR_2.
* @param[in] Uint16_t u16_a_prescaler value to set the desired prescaler.
*
* @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
*         (TMR_OK if the operation succeeded, TMR_ERROR otherwise)
*/
EN_TIMER_ERROR_T TIMER_TMR2Start() {
	switch (u16_g_prescaler)
	{
		case 1:
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
		case 8:
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		break;
		case 32:
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		case 64:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		case 128:
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
		case 256:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		break;
		case 1024:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
		default:
		return TIMER_ERROR;
	}
	return TIMER_OK;

}
/* ************************************************************************************************/
/**
* @brief Stop the TMR by setting the prescaler to be 000--> TMR is stopped.
*
* This function Clear the prescaler for TMR_2.
* @param[in] void.
*
* @return void
*/
void TMR_TMR2Stop(void) {
	/* Stop the TMR by clearing the prescaler*/
	CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
	CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
	CLEAR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
}


/*********************************************************************************************************************/





void TIMER_tmr0deinit(void)
{
	TIMER_timer0Stop();
	//* Disable the interrupt for timer1 overflow.*//*
	CLEAR_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT);
}



void TIMER_tmr2deinit(void)
{
	TMR_TMR2Stop();
	//* Disable the interrupt for timer1 overflow.*//*
	CLEAR_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE2_BIT);
}





/**
* @brief Set callback function for TMR overflow interrupt
*
* @param void_a_pfOvfInterruptAction Pointer to the function to be called on TMR overflow interrupt
* @return EN_TMR_ERROR_T Returns TMR_OK if callback function is set successfully, else returns TMR_ERROR
*/
EN_TIMER_ERROR_T TMR_ovfSetCallback(void (*void_a_pfOvfInterruptAction)(void)) {
	// Check if the Pointer to Function is not equal to NULL
	if (void_a_pfOvfInterruptAction != PTR_NULL) {
		// Store the passed address of function ( in APP Layer ) through pointer to function ( OVFInterruptAction ) into Global Array of Pointers to Functions ( OVFInterruptsAction ) in the passed index ( TMRId ).
		void_g_pfOvfInterruptAction = void_a_pfOvfInterruptAction;
		return TIMER_OK;
		} else {
		return TIMER_ERROR;
	}
}

/**
* @brief Interrupt Service Routine for TMR Overflow.
*        This function is executed when TMR2 Overflows.
*        It increments u16_g_overflow2Ticks counter and checks whether
*        u16_g_overflow2Numbers is greater than u16_g_overflow2Ticks.
*        If true, it resets u16_g_overflow2Ticks and stops TMR2.
*        It then checks whether void_g_pfOvfInterruptAction is not null.
*        If true, it calls the function pointed to by void_g_pfOvfInterruptAction.
*
* @return void
*/
//__attribute__((optimize("O0")))
//ISR(TMR_ovfVect)

ISR(TIM2_OVF_INT)
{
	u16_g_overflow2Ticks++;
	if (u16_g_overflow2Ticks >= u16_g_overflow2Numbers )
	{
		TMR_U8_TCNT2_REG = u16_g_tcnt2InitialVal;
		u16_g_overflow2Ticks = 0;
		void_g_pfOvfInterruptAction();
	}
}
