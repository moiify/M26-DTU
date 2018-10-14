/**
 **************************************************************************************************
 * @file        USER_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "stm32_bsp_conf.h"
#include "osal.h"
#include "clog.h"
#include "cshell.h"
#include "user_task.h"
#include "gprs_process.h"


/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    USER_task_Modules 
 * @{  
 */

/**
 * @defgroup      USER_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_UserTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      USER_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      USER_task_Functions 
 * @brief         
 * @{  
 */
void UserTask_Init(uint8_t taskId)
{
    g_UserTask_Id = taskId;
    OS_Timer_Start(g_UserTask_Id, USER_TASK_LOOP_EVENT,20);
}

osal_event_t UserTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & USER_TASK_KEY_PROCESS_EVENT)
    {
        return events ^ USER_TASK_KEY_PROCESS_EVENT;
    }
    if (events & USER_TASK_LOOP_EVENT)
    {   
        GPRS_WriteBytes("hello123",8);
        GPRS_WriteBytes("hello",5);
        
        OS_Timer_Start(g_UserTask_Id, USER_TASK_LOOP_EVENT,500);
        return events ^ USER_TASK_LOOP_EVENT;
    }
    
    if (events & USER_TASK_SHELL_EVENT)
    {   
        return events ^ USER_TASK_SHELL_EVENT;
    }

    if (events & USER_TASK_OPEN_CMD_EVENT)
    {   
        OS_Timer_Start(taskid,USER_TASK_CLOSE_CMD_EVENT,1000);
        return events ^ USER_TASK_OPEN_CMD_EVENT;
    }

    if (events & USER_TASK_CLOSE_CMD_EVENT)
    {
        return events ^ USER_TASK_CLOSE_CMD_EVENT;
    }
    return 0;
}

void UserTask_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_UserTask_Id,events);
}

void UserTask_Clear_Event(osal_event_t events)
{

}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

