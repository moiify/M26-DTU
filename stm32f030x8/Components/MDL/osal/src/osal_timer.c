/**
 **************************************************************************************************
 * @file        osal_timer.c
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
#include "osal_timer.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    osal_timer_Modules 
 * @{  
 */

/**
 * @defgroup      osal_timer_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_timer_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timer_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_timer_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t IsUsed;
    OSTimer_t Timer;
}osalTimerMem_t;
/**
 * @}
 */

/**
 * @defgroup      osal_timer_Private_Variables 
 * @brief         
 * @{  
 */
static OSTimer_t *s_osalTimerHead = NULL;
static osalTimerMem_t s_osalTimerMemHeap[OSAL_TIMER_HEAP_SIZE];
/**
 * @}
 */

/**
 * @defgroup      osal_timer_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timer_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timer_Functions 
 * @brief         
 * @{  
 */
void OS_Timer_Init(void)
{
    uint8_t i=0;
    for (i=0; i<OSAL_TIMER_HEAP_SIZE; i++)
    {
        s_osalTimerMemHeap[i].IsUsed = 0;
    }
}

OSTimer_t *osalTimerAlloc(void)
{
    OSTimer_t *new_timer = NULL;
    uint8_t i=0;

    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    
    for (i=0; i<OSAL_TIMER_HEAP_SIZE; i++)
    {
        if (s_osalTimerMemHeap[i].IsUsed == 0)
        {
            s_osalTimerMemHeap[i].IsUsed = 1;
            s_osalTimerMemHeap[i].Timer.IsRunning = 0;
            new_timer = &s_osalTimerMemHeap[i].Timer;
            break;
        }
    }

    OSAL_EXIT_CRITICAL(cpu_sr);
    return new_timer;
}

void osalTimerFree(OSTimer_t *timer)
{
    uint8_t i;
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    for (i=0; i<OSAL_TIMER_HEAP_SIZE; i++)
    {
        if (&s_osalTimerMemHeap[i].Timer == timer)
        {
            s_osalTimerMemHeap[i].IsUsed = 0;
            break;
        }
    }
    OSAL_EXIT_CRITICAL(cpu_sr);
}

OSTimer_t *osalTimerFind(uint8_t taskid,osal_event_t event_flag)
{
    OSTimer_t *srch_timer;
    OSAL_CPU_SR cpu_sr;
    
    OSAL_ENTER_CRITICAL(cpu_sr);
    srch_timer = s_osalTimerHead;
    while (srch_timer)
    {
        if ( (srch_timer->TaskId == taskid) &&
             (srch_timer->EventsFlag == event_flag))
        {
            break;
        }
        srch_timer = srch_timer->Next;
    }
    OSAL_EXIT_CRITICAL(cpu_sr);
    return srch_timer;
}

OSTimer_t *osalTimerAdd(uint8_t taskid,osal_event_t event_flag,uint32_t timeout)
{
    OSTimer_t *new_timer;
    OSTimer_t *srch_timer;
    
    new_timer = osalTimerFind(taskid,event_flag);
    
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    if (new_timer)
    {
        new_timer->Timeout = timeout;
        new_timer->IsRunning = 1;
        OSAL_EXIT_CRITICAL(cpu_sr);
        return new_timer;
    }
    else
    {
        new_timer = osalTimerAlloc();

        if (new_timer)
        {
            new_timer->EventsFlag = event_flag;
            new_timer->TaskId = taskid;
            new_timer->Timeout = timeout;
            new_timer->IsRunning = 1;
            
            if (s_osalTimerHead == NULL)
            {
                s_osalTimerHead = new_timer;
            }
            else
            {
                srch_timer = s_osalTimerHead;

                while (srch_timer->Next)
                {
                    srch_timer = srch_timer->Next;
                }

                srch_timer->Next = new_timer;
            }
            OSAL_EXIT_CRITICAL(cpu_sr);
            return new_timer;
        }
        else
        {
            OSAL_EXIT_CRITICAL(cpu_sr);
            return NULL;
        }
    }
}

uint8_t OS_Timer_Start(uint8_t taskid,osal_event_t event_flag,uint32_t timeout)
{
  OSTimer_t *newTimer;

  // Add timer
  newTimer = osalTimerAdd( taskid, event_flag, timeout );

  return ( (newTimer != NULL) ? 1 : 0 );
}

uint8_t OS_Timer_Stop(uint8_t taskid,uint32_t event_flag)
{
    OSTimer_t *found_timer = NULL;

    found_timer = osalTimerFind(taskid,event_flag);

    if (found_timer)
    {
        found_timer->IsRunning = 0;
    }
    
    return OSAL_ERR_NONE;
}

uint8_t OS_Timer_Delete(uint8_t taskid,uint32_t event_flag)
{
    OSTimer_t *srch_timer;
    OSTimer_t *prev_timer = NULL;

    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    
    srch_timer = s_osalTimerHead;

    while (srch_timer)
    {
        if ( (srch_timer->TaskId == taskid) &&
             (srch_timer->EventsFlag == event_flag))
        {
            if (prev_timer == NULL)
            {
                s_osalTimerHead = srch_timer->Next;
            }
            else
            {
                prev_timer->Next = srch_timer->Next;
            }

            osalTimerFree(srch_timer);
            break;
        }
        prev_timer = srch_timer;
        srch_timer = srch_timer->Next;
    }
    OSAL_EXIT_CRITICAL(cpu_sr);
    return OSAL_ERR_NONE;
}

void OS_Timer_Update(uint8_t updateTime)
{
    OSTimer_t *srch_timer;
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    if (s_osalTimerHead != NULL)
    {
        srch_timer = s_osalTimerHead;

        while (srch_timer)
        {
            if (srch_timer->IsRunning > 0)
            {
                if (srch_timer->Timeout > updateTime)
                {
                    srch_timer->Timeout -= updateTime;
                }
                else
                {
                    srch_timer->Timeout = 0;
                }

                if ( (srch_timer->EventsFlag) && (srch_timer->Timeout == 0))
                {
                    srch_timer->IsRunning = 0;
                    OS_Events_Set(srch_timer->TaskId,srch_timer->EventsFlag);
                }
            }
            srch_timer = srch_timer->Next;
            OSAL_EXIT_CRITICAL(cpu_sr);
        }
    }
    else
    {
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

