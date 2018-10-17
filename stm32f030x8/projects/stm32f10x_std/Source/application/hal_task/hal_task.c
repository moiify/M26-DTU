/**
 **************************************************************************************************
 * @file        hal_task.c
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
#include "osal.h"
#include "bsp_led.h"
#include "hal_task.h"
#include "stm32_bsp_conf.h"
#include "cshell_port.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_HalTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Functions 
 * @brief         
 * @{  
 */
void HalTask_Init(uint8_t taskId)
{
    g_HalTask_Id = taskId;
     
    OS_Events_Set(g_HalTask_Id, HAL_TASK_LED_OPEN_EVENT);
    OS_Events_Set(g_HalTask_Id, HAL_TASK_LED_TOGGLE_EVENT);
    
}

osal_event_t HalTask_Process(uint8_t taskid,osal_event_t events)
{   
    if (events & HAL_TASK_LED_OPEN_EVENT)
    {
 //       BSP_LED_Open(BSP_LEDRUN);
//        BSP_LED_Open(BSP_LEDM26);
        GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
        GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET);
        return events ^ HAL_TASK_LED_OPEN_EVENT;
    }
    if (events & HAL_TASK_LED_TOGGLE_EVENT)
    {   
        BSP_LED_Toggle(BSP_LEDRUN);
        OS_Timer_Start(g_HalTask_Id,HAL_TASK_LED_TOGGLE_EVENT,500);
        return events ^ HAL_TASK_LED_TOGGLE_EVENT;       
    }
    return 0;
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

