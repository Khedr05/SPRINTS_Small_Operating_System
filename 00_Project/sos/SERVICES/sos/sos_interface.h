/*
 * sos_interface.h
 *
 * Created: 5/29/2023 7:44:00 PM
 *  Author: sharpel
 */ 


#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

#define MAX_TASKS  10

// assuming that lower the priority number having higher priority 
typedef enum
{
  PRIORITY_ONE,
  PRIORITY_TWO,
  PRIORITY_THREE,
  PRIORITY_FOUR,
  PRIORITY_FIVE,
  PRIORITY_SIX,
  PRIORITY_SEVEN,
  PRIORITY_EIGHT,
  PRIORITY_NINE,
  PRIORITY_TEN,
  PRIORITY_TOTAL,	
}enu_task_priority_id_t; 
typedef struct  
{
	Uint16_t taskPeriodicity;
	void (*ptr_task_ref)(void*);
	void *ptr_task_arg;
	
}str_tasks_config_t;


typedef enum
{
	SOS_STATUS_SUCCESS,
	SOS_STATUS_INVALID_STATE,
	SOS_NULL_ARGS,
	SOS_TASK_PERIODICITY_UNKNOWN,
	SOS_TASK_DUBLICATED_PIRIORITY,
	SOS_TASK_NOT_FOUND,
	SOS_TASK_PRIRORITY_ERROR,
	SOS_NO_TASKS_TO_RUN,
	SOS_RUNNING_DISABLED
}enu_system_status_t;

typedef enum
{
	IDLE,
	RUNNING,
	RUNNING_DISABLED,
}enu_run_state_t;



/**
 * @brief                                               :   Function Used to Initialize sos
 * @name                                                :   sos_init
 * @param[in,out]                                       :   None
 * @param[in]                                           :   None   
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_STATUS_INVALID_STATE                :   In case of re-initialization    
 *             
 */
enu_system_status_t sos_init(void);

/**
 * @brief                                               :   Function Used to Initialize sos
 * @name                                                :   sos_init
 * @param[in,out]                                       :   None
 * @param[in]                                           :   None   
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_STATUS_INVALID_STATE                :   In case of re-initialization    
 *             
 */
enu_system_status_t sos_deinit(void);


/**
 * @brief                                               :   Function Used to Create task and store it in database 
 * @name                                                :   sos_create_task
 * @param[in,out]                                       :   None
 * @param[in]                                           :   enu_task_priority_id_t
                                                            str_tasks_config_t  
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_NULL_ARGS                           :   In case of Null pointer arguments
                SOS_TASK_PERIODICITY_UNKNOWN            :   In case of undefined periodicity
                SOS_TASK_DUBLICATED_PIRIORITY           :   In case of duplicated priority
 *             
 */
enu_system_status_t sos_create_task(enu_task_priority_id_t enu_task_priority_id , str_tasks_config_t *str_tasks_config);

/**
 * @brief                                               :   Function Used to Modify specific task in database 
 * @name                                                :   sos_modify_task
 * @param[in,out]                                       :   None
 * @param[in]                                           :   enu_task_priority_id_t
                                                            str_tasks_config_t  
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_NULL_ARGS                           :   In case of Null pointer arguments
                SOS_TASK_PERIODICITY_UNKNOWN            :   In case of undefined periodicity
                SOS_TASK_NOT_FOUND                      :   In case of not found task 
 *             
 */
enu_system_status_t sos_modify_task(enu_task_priority_id_t enu_task_priority_id ,str_tasks_config_t *str_tasks_config);

/**
 * @brief                                               :   Function Used to delete specific task in database 
 * @name                                                :   sos_delete_task
 * @param[in,out]                                       :   None
 * @param[in]                                           :   enu_task_priority_id_t
                                                              
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_TASK_PRIRORITY_ERROR                :   In case of priority greater than max
                SOS_TASK_NOT_FOUND                      :   In case of not found task 
 *             
 */
enu_system_status_t sos_delete_task(enu_task_priority_id_t enu_task_priority_id);
/**
 * @brief                                               :   Function Used to run scheduler 
 * @name                                                :   sos_run
 * @param[in,out]                                       :   None
 * @param[in]                                           :   None                                                 
 * @return      SOS_NO_TASKS_TO_RUN                     :   In case of Empty Database     
 *              SOS_RUNNING_DISABLED                    :   In case of disable scheduler
 *             
 */
enu_system_status_t sos_run(void);

/**
 * @brief                                               :   Function Used to disable sos
 * @name                                                :   sos_disable
 * @param[in,out]                                       :   None
 * @param[in]                                           :   None   
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              SOS_STATUS_INVALID_STATE                :   In case of re-disable scheduler or the scheduler is already not run
 *             
 */
enu_system_status_t sos_disable(void);
#endif /* SOS_INTERFACE_H_ */