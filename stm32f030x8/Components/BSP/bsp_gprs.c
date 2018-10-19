/**
 **************************************************************************************************
 * @file        bsp_gprs.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_gprs.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_gprs_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_gprs_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_gprs_Functions 
 * @brief         
 * @{  
 */

void BSP_GPRS_PowerOff(void)
{
   GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);   //µÙµÁ 
}
void BSP_GPRS_PowerOn(void)
{
   GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);   //…œµÁ 
}
void BSP_GPRS_PowerKeyHigh(void)
{
  GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_RESET); 
}
void BSP_GPRS_PowerKeyLow(void)
{
  GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET);  
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

