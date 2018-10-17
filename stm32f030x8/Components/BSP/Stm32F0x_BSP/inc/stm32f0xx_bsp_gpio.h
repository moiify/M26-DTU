/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_gpio.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F0XX_BSP_GPIO_H_
#define _STM32F0XX_BSP_GPIO_H_

#include "stm32f0xx.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_gpio_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_gpio_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_gpio_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_gpio_Exported_Types 
 * @{  
 */
typedef struct
{
    uint32_t            Clock;
    GPIO_TypeDef*       GPIOx;
    GPIO_InitTypeDef    Init;
    GPIO_InitTypeDef    DeInit;
}GPIO_InstanceTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_gpio_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_gpio_Exported_Functions 
 * @{  
 */

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
