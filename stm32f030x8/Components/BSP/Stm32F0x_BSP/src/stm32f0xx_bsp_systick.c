/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_systick.c
 * @author
 * @version     V2.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f0xx_bsp_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f0xx_bsp_systick_Modules 
 * @{  
 */
#if BSP_SYSTICK_MODULE_ENABLE == 1
/**
 * @defgroup      stm32f0xx_bsp_systick_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       stm32f0xx_bsp_systick_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       stm32f0xx_bsp_systick_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Public_Variables 
 * @brief         
 * @{  
 */
uint32_t s_Systick_Ticks = 0;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_systick_Functions 
 * @brief         
 * @{  
 */
void BSP_SYSTICK_Open(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    RCC_GetClocksFreq(&rcc_clocks);
	SysTick_Config(rcc_clocks.HCLK_Frequency/BSP_TICKS_PER_SEC);
}

void BSP_SYSTICK_IncTick(void)
{
    s_Systick_Ticks++;
}

uint32_t BSP_SYSTICK_GetTick(void)
{
    return s_Systick_Ticks;
}

void BSP_SYSTICK_Delay(uint32_t ticks)
{
    uint32_t tickstart = 0;
    tickstart = BSP_SYSTICK_GetTick();
    while ((BSP_SYSTICK_GetTick() - tickstart) < ticks) 
    {
    }
}

void BSP_SYSTICK_Suspend(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  
}

void BSP_SYSTICK_Resume(void)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
/**
 * @}
 */
#endif // BSP_SYSTICK_MODULE_ENABLE
/**
 * @}
 */

/**
 * @}
 */

