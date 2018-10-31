/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_flash.c
 * @author
 * @version   v0.1.0
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
 * @addtogroup    stm32f0xx_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Macros_Defines 
 * @brief         
 * @{  
 */
#define FLASH_START_ADDR    0x8000000
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_flash_Functions 
 * @brief         
 * @{  
 */
void BSP_FLASH_EraseSector(uint32_t addr)
{
    FLASH_Unlock();
    FLASH_ErasePage(addr+FLASH_START_ADDR);
    FLASH_Lock();
}

void BSP_FLASH_WriteBytes(uint32_t addr,uint8_t *pBuf,uint16_t count)
{
    uint16_t data;
    volatile FLASH_Status status;
    uint16_t loop = (count+1)/2;
    addr += FLASH_START_ADDR;
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR);
    while (loop--)
    {
        data = *(uint16_t*)pBuf;
        status = FLASH_ProgramHalfWord(addr,data);
        addr += 2;  
        pBuf += 2;
    }
    FLASH_Lock();
}

void BSP_FLASH_ReadBytes(uint32_t addr,uint8_t *pBuf,uint16_t count)
{
    addr += FLASH_START_ADDR;
    while (count--)
    {
        *pBuf = *(uint8_t*)addr;
        pBuf++;
        addr++;
    }
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

