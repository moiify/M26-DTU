/**
 **************************************************************************************************
 * @file        BSP_Init.c
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "stm32_bsp_conf.h"
#include "cshell_port.h"
#include "clog.h"
#include "bsp_init.h"
#include "bsp_led.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    BSP_Init_Modules 
 * @{  
 */

/**
 * @defgroup      BSP_Init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_Init_Functions 
 * @brief         
 * @{  
 */
void Board_Init()
{
    SystemInit();
}

void BSP_Init(void)
{   
    CLog_Init(CLogAppender_RTT);
    BSP_LED_Init(); 
    BSP_Timer_Init();
    BSP_USART_Open(BSP_USART1, NULL);
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

