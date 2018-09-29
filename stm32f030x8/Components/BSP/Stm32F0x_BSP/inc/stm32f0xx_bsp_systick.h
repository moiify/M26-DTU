/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_systick.h
 * @author
 * @version     V2.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_BSP_SYSTICK_H_
#define _STM32F10X_BSP_SYSTICK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_systick_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Exported_Constants
 * @{  
 */
#define BSP_TICKS_PER_SEC   1000 
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Exported_Functions 
 * @{  
 */
void     BSP_SYSTICK_Open(void);
void     BSP_SYSTICK_IncTick(void);
uint32_t BSP_SYSTICK_GetTick(void);
void     BSP_SYSTICK_Delay(uint32_t ticks);
void     BSP_SYSTICK_Suspend(void);
void     BSP_SYSTICK_Resume(void);
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
