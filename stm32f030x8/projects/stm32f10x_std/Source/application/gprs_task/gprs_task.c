/**
 **************************************************************************************************
 * @file        gprs_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_task.h"
#include "gprs_process.h"
#include "self_def.h"
#include "osal.h"
#include "stm32_bsp_conf.h"
#include "system_info.h"
#include "cshell_port.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_task_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_GprsTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      gprs_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_task_Functions 
 * @brief         
 * @{  
 */
void GprsTask_Init(uint8_t taskId)
{
    g_GprsTask_Id = taskId;
    OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_RESET_EVENT,50);
    OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_LOOP_EVENT,200);
    OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_RSSI_EVENT,8000);
    OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_QISACK_EVENT,5000);
}
osal_event_t GprsTask_Process(uint8_t taskid,osal_event_t events)
{

    if (events & GPRS_TASK_ACK_EVENT)
    {   
        GPRS_ACK_Process();
        return events ^ GPRS_TASK_ACK_EVENT;
    }
    if (events & GPRS_TASK_LOOP_EVENT)
    {     
        GPRS_Loop_Process();
        OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_LOOP_EVENT,50);
        return events ^ GPRS_TASK_LOOP_EVENT;
    }
    if (events & GPRS_TASK_RSSI_EVENT)
    {   
        Gprs_UpdateRssi();
        OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_RSSI_EVENT,5000);
        return events ^ GPRS_TASK_RSSI_EVENT;
    }
    if (events & GPRS_TASK_QISACK_EVENT)
    {   
        Gprs_Cmd_QIACK();
        OS_Timer_Start(g_GprsTask_Id, GPRS_TASK_QISACK_EVENT,5000);
        return events ^ GPRS_TASK_QISACK_EVENT;
    }
    if (events & GPRS_TASK_RESET_EVENT)
    {   
        Gprs_Reset_Moudle();
        Gprs_Add_Sockets(g_SystemInfo.Socket_ListInfo[0]);
        Gprs_Add_Sockets(g_SystemInfo.Socket_ListInfo[1]);
        return events ^ GPRS_TASK_RESET_EVENT;
    }
    return 0;
}

void GprsTask_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_GprsTask_Id,events);
}

void GprsTask_Clear_Event(osal_event_t events)
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

