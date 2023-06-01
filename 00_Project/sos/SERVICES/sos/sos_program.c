/*
 * sos_program.c
 *
 * Created: 5/29/2023 9:40:45 PM
 *  Author: sharpel
 */ 

#include "../../COMMON/std_types.h"
#include "../../MCAL/timer/timer_interface.h"
#include "sos_config.h"
#include "sos_interface.h"
#include "../../MCAL/dio/dio.h"

// sos config struct (contain selected timer data)
extern const str_sos_configs_t gl_str_sos_configs ;

// array of pointers to tasks
static str_tasks_config_t *gl_tasks_db[MAX_TASKS];

// this global variable indicates if sos is initialized or not
Uint8_t gl_is_init = FALSE;

// this global variable becomes true when system tick happens
Uint8_t gl_system_tick = FALSE;

// this global counter counts the ticks of system
Uint64_t gl_ticks_counter = FALSE ;

// this global indicates the status of running
enu_run_state_t gl_running_state = RUNNING_DISABLED;

//call back prototype
static void is_tick_done(void);

// this function executed inside timer ISR
static void is_tick_done(void)
{
	gl_system_tick = TRUE;
	gl_ticks_counter++;
	
	if(gl_ticks_counter == MAX_TICK_COUNTS)
	{
		gl_ticks_counter = FALSE ;
	}
}
enu_system_status_t sos_init(void)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	Uint8_t uint8_loc_counter = FALSE;
	if(gl_is_init == FALSE)
	{
		// initialize timer with system tick desired time and callback
		gl_str_sos_configs.str_sos_timer_functions.ptr_timer_init(ENABLED);
		gl_str_sos_configs.str_sos_timer_functions.ptr_timer_set_Tick_time(100);
		gl_str_sos_configs.str_sos_timer_functions.ptr_timer_setCallBack(is_tick_done);
		
		// means this module is initialized
		gl_is_init = TRUE;
		
		// initialize database with Nulls
		while(uint8_loc_counter < MAX_TASKS)
		{
			gl_tasks_db[uint8_loc_counter] = PTR_NULL;
			uint8_loc_counter ++;
		}
	}
	else
	{
		// case of duplicated initialization 
		enu_system_status_retval = SOS_STATUS_INVALID_STATE;
	}
	
	return enu_system_status_retval;
}


enu_system_status_t sos_deinit(void)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	Uint8_t uint8_loc_counter = FALSE;
	
	// check if module is initialized
	if(gl_is_init == TRUE)
	{
		
		// clear database
		while(uint8_loc_counter < MAX_TASKS)
		{
			gl_tasks_db[uint8_loc_counter] = PTR_NULL;
			uint8_loc_counter ++;
		}
		
		//clear is init-flag and system-tick and ticks-counter
		gl_is_init       = FALSE;
		gl_system_tick   = FALSE;
		gl_ticks_counter = FALSE ;
		
		// (to be done SM) de init timer
	}
	else
	{
		// case of duplicated de-initialization or not initialized module 
		enu_system_status_retval = SOS_STATUS_INVALID_STATE;
	}
	
	return enu_system_status_retval;
}

enu_system_status_t sos_create_task(enu_task_priority_id_t enu_task_priority_id,str_tasks_config_t *str_tasks_config)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;	
	
	// check on args null pointers
	if((str_tasks_config == PTR_NULL) || (str_tasks_config->ptr_task_ref ==PTR_NULL) )
	{
	   enu_system_status_retval = SOS_NULL_ARGS;
	}
	else 
	{
		// check on unknown periodicity
		if(str_tasks_config->taskPeriodicity == STR_NULL)
		{
			enu_system_status_retval = SOS_TASK_PERIODICITY_UNKNOWN;
		}
		else
		{
			// check on duplicated priority it's value must be less than PRIORITY_TOTAL
			if((gl_tasks_db[enu_task_priority_id] == PTR_NULL) && (enu_task_priority_id < PRIORITY_TOTAL))
			{
				// store address of task struct in db with chosen priority (priority here will be task index in db )
				 gl_tasks_db[enu_task_priority_id]  = str_tasks_config;
			}
			
			else
			{
				//(it doesn't support duplicated priority)
				enu_system_status_retval = SOS_TASK_DUBLICATED_PIRIORITY;
			}
		}
	}
	
	return enu_system_status_retval;
}


enu_system_status_t sos_delete_task(enu_task_priority_id_t enu_task_priority_id)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	
	// check on priority it's value must be less than PRIORITY_TOTAL
	if((enu_task_priority_id >= PRIORITY_TOTAL))
	{
		// means that priority exceeded the max
		enu_system_status_retval = SOS_TASK_PRIRORITY_ERROR;
	}
	else
	{
			// check on desired task in db
			if(gl_tasks_db[enu_task_priority_id] != PTR_NULL)
			{
				gl_tasks_db[enu_task_priority_id] = PTR_NULL;
			}
			
			else
			{
				// means that this task is not in db
				enu_system_status_retval = SOS_TASK_NOT_FOUND;
			}
		
	}
	
	return enu_system_status_retval;

}
enu_system_status_t sos_modify_task(enu_task_priority_id_t enu_task_priority_id,str_tasks_config_t *str_tasks_config)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	
	// check on args null pointers
	if((str_tasks_config == PTR_NULL) || (str_tasks_config->ptr_task_ref ==PTR_NULL) )
	{
		enu_system_status_retval = SOS_NULL_ARGS;
	}
	else
	{
		// check on unknown periodicity
		if(str_tasks_config->taskPeriodicity == STR_NULL)
		{
			enu_system_status_retval = SOS_TASK_PERIODICITY_UNKNOWN;
		}
		else
		{
			// check that desired task is not null and make sure that it's value is less than PRIORITY_TOTAL
			if((gl_tasks_db[enu_task_priority_id] != PTR_NULL) && (enu_task_priority_id < PRIORITY_TOTAL))
			{
				gl_tasks_db[enu_task_priority_id]   = str_tasks_config;
			}
			
			else
			{
				// means that this task is not in db
				enu_system_status_retval = SOS_TASK_NOT_FOUND;
			}
		}
	}
	
	return enu_system_status_retval;
}


enu_system_status_t sos_run(void)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	Uint8_t uint8_loc_counter = FALSE;
	
	// check if database is not empty
	for(uint8_loc_counter = FALSE; uint8_loc_counter < MAX_TASKS ; uint8_loc_counter++)
	{
		if(gl_tasks_db[uint8_loc_counter] != PTR_NULL)
		{
			break;
		}
	}
	
	// in case of empty db
	if(uint8_loc_counter == MAX_TASKS)
	{
		enu_system_status_retval =  SOS_NO_TASKS_TO_RUN;
	}
	else
	{
		// run state is idle
		gl_running_state = IDLE;
		// start the timer
		gl_str_sos_configs.str_sos_timer_functions.ptr_timer_start(TIMER_PRESCALLER);

		while(1)
		{
			// check on running state
			if(gl_running_state == RUNNING_DISABLED)
			{
				enu_system_status_retval = SOS_RUNNING_DISABLED;
				break;// break while loop
			}
			switch(gl_running_state)
			{
				
				case IDLE:
				{
					//wait for system tick
					if(gl_system_tick == TRUE)
					{
						gl_running_state = RUNNING;
					}
					break;
				}
				
				case RUNNING:
				{
					
					for(uint8_loc_counter = FALSE; uint8_loc_counter < MAX_TASKS ; uint8_loc_counter++)
					{
						//check if there's a task. if it ready it will execute
						if(gl_tasks_db[uint8_loc_counter] != PTR_NULL && (gl_ticks_counter % gl_tasks_db[uint8_loc_counter]->taskPeriodicity == FALSE ))
						{
							gl_tasks_db[uint8_loc_counter]->ptr_task_ref(gl_tasks_db[uint8_loc_counter]->ptr_task_arg);
						}
					}
					
					//wait for the next tick
					gl_system_tick = FALSE;
					gl_running_state = IDLE;
					
					break;
				}
				case RUNNING_DISABLED:
				{
					break;
				}
			}//end switch
		}//end while
	
	}//end else
		
	return enu_system_status_retval;
}
enu_system_status_t sos_disable(void)
{
	enu_system_status_t enu_system_status_retval = SOS_STATUS_SUCCESS;
	if(gl_running_state != RUNNING_DISABLED)
	{
		gl_running_state = RUNNING_DISABLED;
		gl_system_tick   = FALSE;
		gl_ticks_counter = FALSE;
		gl_str_sos_configs.str_sos_timer_functions.ptr_timer_stop();
	}
	else
	{
		// case of duplicated disable calling or sos is not running
		enu_system_status_retval = SOS_STATUS_INVALID_STATE;
	}
	
	return enu_system_status_retval;
}