/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_timer.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F0XX_BSP_TIMER_H_
#define _STM32F0XX_BSP_TIMER_H_
#include "stm32f0xx_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_timer_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_timer_Exported_Macros 
 * @{  
 */
#define BSP_TIM3  3 
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_timer_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_timer_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_timer_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_timer_Exported_Functions 
 * @{  
 */
void BSP_Timer_Init(void);
void BSP_TIMER_IRQHandler(uint8_t BSP_TIMx);
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
