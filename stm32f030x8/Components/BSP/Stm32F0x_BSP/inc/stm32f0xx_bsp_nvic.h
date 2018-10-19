/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_nvic.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F0XX_BSP_NVIC_H_
#define _STM32F0XX_BSP_NVIC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_nvic_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Exported_Macros 
 * @{  
 */
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Exported_Functions 
 * @{  
 */
void BSP_NVIC_Config(uint8_t IRQChannel,uint8_t Priority,FunctionalState NewState);
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
