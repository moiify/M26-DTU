/**
 **************************************************************************************************
 * @file        cshell_port.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32_bsp_conf.h"
#include "cshell_port.h"
#include "segger_rtt.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    cshell_port_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cshell_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cshell_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Functions 
 * @brief         
 * @{  
 */
uint16_t CShell_ReadBytes(uint8_t *pBuf,uint16_t count)
{
    //return BSP_USART_ReadBytes(BSP_USART1,pBuf,count);
    return SEGGER_RTT_ReadNoLock(0,pBuf,(int)count);
}

void CShell_WriteBytes(uint8_t *pBuf,uint16_t count)
{
    //BSP_USART_WriteBytes(BSP_USART1,pBuf,count);
    SEGGER_RTT_Write(0,pBuf,count);
}

uint32_t CShell_GetTicks(void)
{
    return 0;
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

