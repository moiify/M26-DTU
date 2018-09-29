/**
 **************************************************************************************************
 * @file        osal_timer.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_TIMER_H_
#define _OSAL_TIMER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_timer_Modules 
 * @{  
 */

/**
 * @defgroup      osal_timer_Exported_Macros 
 * @{  
 */
#define OSAL_TIMER_HEAP_SIZE    10
/**
 * @}
 */

/**
 * @defgroup      osal_timer_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timer_Exported_Types 
 * @{  
 */
typedef struct osal_timer
{
    struct osal_timer *Next;
    uint8_t IsRunning;
    uint32_t Timeout;
    uint8_t TaskId;
    uint32_t EventsFlag;
}OSTimer_t;
/**
 * @}
 */

/**
 * @defgroup      osal_timer_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timer_Exported_Functions 
 * @{  
 */
void    OS_Timer_Init(void);
uint8_t OS_Timer_Start(uint8_t taskid,osal_event_t event_flag,uint32_t timeout);
uint8_t OS_Timer_Stop(uint8_t taskid,osal_event_t event_flag);
uint8_t OS_Timer_Delete(uint8_t taskid,osal_event_t event_flag);
void    OS_Timer_Update(uint8_t updateTime);
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
