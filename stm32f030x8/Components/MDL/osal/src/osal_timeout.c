/**
 **************************************************************************************************
 * @file        osal_timeout.c
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
#include "osal_cpu.h"
#include "osal_cfg.h"
#include "osal_core.h"
#include "osal_timeout.h"


/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    osal_timeout_Modules 
 * @{  
 */

/**
 * @defgroup      osal_timeout_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_timeout_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_timeout_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Private_Variables 
 * @brief         
 * @{  
 */
static OSTimeout_t *s_osalTimeoutHead = NULL;
static uint32_t s_NextTimeout = 0;
/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Public_Variables 
 * @brief         
 * @{  
 */
extern uint8_t g_HalTask_Id;
/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Functions 
 * @brief         
 * @{  
 */
int8_t OS_Timeout_Init(OSTimeout_t *timeout,void (*callback)(void))
{
    OSTimeout_t *srch_timeout;

    timeout->Count = 0;
    timeout->ReloadValue = 0;
    timeout->Next = NULL;
    timeout->callback = callback;

    if (s_osalTimeoutHead == NULL)
    {
        s_osalTimeoutHead = timeout;
    }
    else
    {
        srch_timeout = s_osalTimeoutHead;

        while (srch_timeout->Next)
        {
            srch_timeout = srch_timeout->Next;
        }

        srch_timeout->Next = timeout;
    }

    return OSAL_ERR_NONE;
}

void OS_Timeout_Start(OSTimeout_t *timeout)
{
    uint32_t next_timeout = 0;
    OSAL_CPU_SR cpu_sr;

    OSAL_ENTER_CRITICAL(cpu_sr);
    timeout->Count = timeout->ReloadValue;
    OSAL_EXIT_CRITICAL(cpu_sr);
    next_timeout = OS_Timeout_GetNextTimeout();
    if (next_timeout > 0)
    {
        OS_Timer_Start(g_HalTask_Id, OSAL_TIMEOUT_EVENT, next_timeout);
        OSAL_ENTER_CRITICAL(cpu_sr);
        s_NextTimeout = next_timeout;
        OSAL_EXIT_CRITICAL(cpu_sr);
    }
}

void OS_Timeout_Stop(OSTimeout_t *timeout)
{
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    timeout->Count = 0;
    OSAL_EXIT_CRITICAL(cpu_sr);
}

void OS_Timeout_SetValue(OSTimeout_t *timeout,uint32_t value)
{
    timeout->ReloadValue = value;
}

uint32_t OS_Timeout_GetTimeout(OSTimeout_t *timeout)
{
    return timeout->Count;
}

uint32_t OS_Timeout_GetNextTimeout(void)
{
    uint32_t next_timeout = 0xFFFFFFFF;
    OSTimeout_t *srch_timeout = s_osalTimeoutHead;

    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    while (srch_timeout != NULL)
    {
        if ( srch_timeout->Count > 0 &&
             srch_timeout->Count < next_timeout)
        {
            next_timeout = srch_timeout->Count;
        }

        srch_timeout = srch_timeout->Next;
    }
   
    if (next_timeout == 0xFFFFFFFF)
    {
        next_timeout = 0;
    }
    OSAL_EXIT_CRITICAL(cpu_sr);

    return next_timeout;
}

void OS_Timeout_Update()
{
    uint32_t next_timeout = 0;
    OSTimeout_t *srch_timeout;
    OSAL_CPU_SR cpu_sr;
    
    srch_timeout = s_osalTimeoutHead;

    while (srch_timeout)
    {
        OSAL_ENTER_CRITICAL(cpu_sr);
        if (srch_timeout->Count)
        {
            if (srch_timeout->Count > s_NextTimeout)
            {
                srch_timeout->Count -= s_NextTimeout;
                OSAL_EXIT_CRITICAL(cpu_sr);
            }
            else
            {
                srch_timeout->Count = 0;
                OSAL_EXIT_CRITICAL(cpu_sr);
                if (srch_timeout->callback != NULL)
                {
                    srch_timeout->callback();
                }

            }
        }
        else
        {
            OSAL_EXIT_CRITICAL(cpu_sr);
        }
        srch_timeout = srch_timeout->Next;
    }
    
    next_timeout = OS_Timeout_GetNextTimeout();
    if (next_timeout > 0)
    {
        OS_Timer_Start(g_HalTask_Id, OSAL_TIMEOUT_EVENT, next_timeout);
        OSAL_ENTER_CRITICAL(cpu_sr);
        s_NextTimeout = next_timeout;
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

