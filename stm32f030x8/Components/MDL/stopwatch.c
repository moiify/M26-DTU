/**
 **************************************************************************************************
 * @file        stopwatch.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "selftypedef.h"
#include "stopwatch.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stopwatch_Modules 
 * @{  
 */

/**
 * @defgroup      stopwatch_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Macros_Defines 
 * @brief         
 * @{  
 */
#define Stopwatch_State_Stop    0
#define Stopwatch_State_Start   1
#define Stopwatch_State_Pause   2
/**
 * @}
 */

/**
 * @defgroup      stopwatch_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Private_Types
 * @brief         
 * @{  
 */
static Stopwatch *s_StopwatchHead = NULL;
/**
 * @}
 */

/**
 * @defgroup      stopwatch_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Functions 
 * @brief         
 * @{  
 */
int8_t Stopwatch_Create(Stopwatch *stopwatch)
{
    Stopwatch *newStopwatch;

    stopwatch->Next = NULL;
    stopwatch->Rdy = FALSE;
    stopwatch->State = Stopwatch_State_Stop;
    stopwatch->TickCount = 0;

    if (s_StopwatchHead == NULL)
    {
        s_StopwatchHead = stopwatch;
    }
    else
    {
        newStopwatch = s_StopwatchHead;

        while (newStopwatch->Next)
        {
            newStopwatch = newStopwatch->Next;
        }

        newStopwatch->Next = stopwatch;
    }

    return 0;
}

void Stopwatch_StartOnce(Stopwatch* stopwatch,uint32_t initialVal)
{
    if (stopwatch->State != Stopwatch_State_Start)
    {
        stopwatch->TickCount = initialVal;
        stopwatch->State = Stopwatch_State_Start;
    }
}

void Stopwatch_Restart(Stopwatch* stopwatch,uint32_t initialVal)
{
    stopwatch->TickCount = initialVal;
    stopwatch->State = Stopwatch_State_Start;
}

void Stopwatch_Stop(Stopwatch* stopwatch)
{
    stopwatch->State = Stopwatch_State_Stop;
    stopwatch->Rdy = FALSE;
}

void Stopwatch_Pause(Stopwatch* stopwatch)
{
    stopwatch->State = Stopwatch_State_Pause;
}

void Stopwatch_Resume(Stopwatch* stopwatch)
{
    stopwatch->State = Stopwatch_State_Start;
}

uint32_t Stopwatch_GetTickCount(Stopwatch* stopwatch)
{
    uint32_t tmp;
    tmp = stopwatch->TickCount;
    return tmp;
}

BOOL Stopwatch_GetRdyState(Stopwatch* stopwatch)
{
    if (stopwatch->Rdy == TRUE)
    {
        stopwatch->Rdy = FALSE;
        return TRUE;
    }
    return FALSE;
}

void Stopwatch_Service(void)
{
    Stopwatch* srchStopwatch;

    srchStopwatch = s_StopwatchHead;

    while (srchStopwatch)
    {
        if (srchStopwatch->State == Stopwatch_State_Start)
        {
            srchStopwatch->TickCount--;
            if (srchStopwatch->TickCount == 0)
            {
                srchStopwatch->Rdy = TRUE;
                srchStopwatch->State = Stopwatch_State_Stop;
            }
        }
        srchStopwatch = srchStopwatch->Next;
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

