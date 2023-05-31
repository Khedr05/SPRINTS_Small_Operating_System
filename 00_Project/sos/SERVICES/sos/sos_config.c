/*
 * sos_config.c
 *
 * Created: 5/29/2023 8:37:19 PM
 *  Author: sharpel
 */ 


#include "../../COMMON/std_types.h"
#include "sos_config.h"
#include "../../MCAL/timer/timer_interface.h"


const str_sos_configs_t gl_str_sos_configs =
{
   .enu_sos_timer_select                               = TIMER_TWO,
   .str_sos_timer_functions.ptr_timer_init             = TIMER_TMR2NormalModeInit,
   .str_sos_timer_functions.ptr_timer_deinit           = TIMER_tmr2deinit,
   .str_sos_timer_functions.ptr_timer_start            = TIMER_TMR2Start,
   .str_sos_timer_functions.ptr_timer_stop             = TIMER_timer2Stop,
   .str_sos_timer_functions.ptr_timer_set_Tick_time    = TMR_intDelay_ms,
   .str_sos_timer_functions.ptr_timer_setCallBack      = TMR_ovfSetCallback
};