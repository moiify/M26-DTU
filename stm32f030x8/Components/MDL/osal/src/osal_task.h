/**
 **************************************************************************************************
 * @file        osal_task.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_TASK_H_
#define _OSAL_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_task_Modules 
 * @{  
 */

/**
 * @defgroup      osal_task_Exported_Macros 
 * @{  
 */
#define OSAL_TASK_COUNT      3
/**
 * @}
 */

/**
 * @defgroup      osal_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_task_Exported_Types 
 * @{  
 */
typedef osal_event_t (*pTaskEventHandlerFn)(uint8_t task_id, osal_event_t events);
/**
 * @}
 */

/**
 * @defgroup      osal_task_Exported_Variables 
 * @{  
 */
extern const pTaskEventHandlerFn g_TasksFnArr[OSAL_TASK_COUNT];
extern osal_event_t g_TasksEvents[];
/**
 * @}
 */

/**
 * @defgroup      osal_task_Exported_Functions 
 * @{  
 */
void   OS_Task_Init(void);
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
