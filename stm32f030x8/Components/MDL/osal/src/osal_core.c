/**
 **************************************************************************************************
 * @file        osal_core.c
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "osal.h"
#include "osal_cfg.h"
#include "osal_cpu.h"
#include "osal_core.h"
#include "osal_clock.h"
#include "osal_timeout.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    osal_core_Modules 
 * @{  
 */

/**
 * @defgroup      osal_core_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_core_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_core_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
void osalRun(void);
/**
 * @}
 */

/**
 * @defgroup      osal_core_Functions 
 * @brief         
 * @{  
 */
void OS_Init(void)
{
    OS_Msg_Init();
    OS_Timer_Init();
    OS_Task_Init();
}


void OS_Start(void)
{
    for(;;)
    {
        osalRun();
    }
}

static void osalTimeUpdate(void)
{
    static uint32_t prev_ms = 0;
    uint32_t elapsedms = OS_Clock_GetSystemClock() - prev_ms;
    if (elapsedms > 1)
    {
        prev_ms = OS_Clock_GetSystemClock();
    }
}

static void osalRun(void)
{
    uint8_t idx=0;

    osalTimeUpdate();
    
    do
    {
        if (g_TasksEvents[idx])
        {
            break;
        }
    }while(++idx < OSAL_TASK_COUNT);
    
    if (idx < OSAL_TASK_COUNT)
    {
        osal_event_t events;
        OSAL_CPU_SR cpu_sr;
        OSAL_ENTER_CRITICAL(cpu_sr);
        events = g_TasksEvents[idx];
        g_TasksEvents[idx] = 0;
        OSAL_EXIT_CRITICAL(cpu_sr);
        
        events = g_TasksFnArr[idx](idx,events);
        
        OSAL_ENTER_CRITICAL(cpu_sr);
        g_TasksEvents[idx] |= events;
        OSAL_EXIT_CRITICAL(cpu_sr);
    }
}

void OS_Events_Set(uint8_t taskid,osal_event_t event_flag)
{
    if (taskid < OSAL_TASK_COUNT)
    {
        OSAL_CPU_SR cpu_sr; 
        OSAL_ENTER_CRITICAL(cpu_sr);
        g_TasksEvents[taskid] |= event_flag;
        OSAL_EXIT_CRITICAL(cpu_sr);
    }
}

void OS_Events_Clear(uint8_t taskid,osal_event_t event_flag)
{
    if (taskid < OSAL_TASK_COUNT)
    {
        OSAL_CPU_SR cpu_sr;
        OSAL_ENTER_CRITICAL(cpu_sr);
        g_TasksEvents[taskid] &= ~(event_flag);
        OSAL_EXIT_CRITICAL(cpu_sr);
    }
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

