/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_flash.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F0XX_BSP_FLASH_H_
#define _STM32F0XX_BSP_FLASH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Exported_Functions 
 * @{  
 */
void BSP_FLASH_ReadBytes(uint32_t addr,uint8_t *pBuf,uint16_t count);
void BSP_FLASH_WriteBytes(uint32_t addr,uint8_t *pBuf,uint16_t count);
void BSP_FLASH_EraseSector(uint32_t addr);
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
