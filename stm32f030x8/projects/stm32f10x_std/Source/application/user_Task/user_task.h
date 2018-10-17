/**
 **************************************************************************************************
 * @file        USER_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _USER_TASK_H_
#define _USER_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "osal.h"
/**
 * @addtogroup    USER_task_Modules 
 * @{  
 */

/**
 * @defgroup      USER_task_Exported_Macros 
 * @{  
 */
#define USER_TASK_KEY_PROCESS_EVENT     0x0001
#define USER_TASK_LOOP_EVENT            0x0002
#define USER_TASK_SHELL_EVENT           0x0004
#define USER_TASK_OPEN_CMD_EVENT        0x0008
#define USER_TASK_CLOSE_CMD_EVENT       0x0010
/**
 * @}
 */

/**
 * @defgroup      USER_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Exported_Functions 
 * @{  
 */
void UserTask_Init(uint8_t taskId);
osal_event_t UserTask_Process(uint8_t taskid,osal_event_t events);
void UserTask_Send_Event(osal_event_t events);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
