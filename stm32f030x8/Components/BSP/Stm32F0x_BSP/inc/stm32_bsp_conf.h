/**
 **************************************************************************************************
 * @file        stm32_bsp_conf.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32_BSP_CONF_H_
#define _STM32_BSP_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32_bsp_conf_Modules 
 * @{  
 */

/**
 * @defgroup      stm32_bsp_conf_Exported_Macros 
 * @{  
 */
#define STM32F0_FAMILY  0
#define STM32F1_FAMILY  1
#define STM32F2_FAMILY  2
#define STM32F3_FAMILY  3
#define STM32F4_FAMILY  4
#define STM32L0_FAMILY  5
#define STM32L1_FAMILY  6
#define STM32L4_FAMILY  7

#define STM32_BSP_PLATFORM  STM32F0_FAMILY

#if STM32_BSP_PLATFORM == STM32F0_FAMILY
  #include "stm32f0xx_bsp_conf.h"
#elif STM32_BSP_PLATFORM == STM32F1_FAMILY
  #include "stm32f10x_bsp_conf.h"
#endif
/**
 * @}
 */

/**
 * @defgroup      stm32_bsp_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32_bsp_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32_bsp_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32_bsp_conf_Exported_Functions 
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
