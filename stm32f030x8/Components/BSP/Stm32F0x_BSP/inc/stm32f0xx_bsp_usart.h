/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_usart.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F0XX_BSP_USART_H_
#define _STM32F0XX_BSP_USART_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f0xx_bsp_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Macros 
 * @{  
 */
#if defined (STM32F10X_HD) || defined (STM32F10X_CL)     
    #define BSP_USARTCOUNT 5
#elif defined (STM32F10X_MD)
    #define BSP_USARTCOUNT 3
#elif defined (STM32F10X_LD)
    #define BSP_USARTCOUNT 2
#else
    #error "Please select first the target STM32F10x device used in your application (in stm32f10x.h file)"
#endif

#define BSP_USART1      0
#define BSP_USART2      1
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_MD)
#define BSP_USART3      2
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_CL)     
#define BSP_USART4      3
#define BSP_USART5      4
#endif

#define BSP_USART_MODE_DMA      0
#define BSP_USART_MODE_IRQ      1
#define BSP_USART_MODE_QUERY    2

#define BSP_USART_DMA_TRANSFERMODE_PACKET   0
#define BSP_USART_DMA_TRANSFERMODE_FLOW     1
/* */
#define USART_CMD_GETRXCOUNT    0
#define USART_CMD_TXFLUSH       1
#define USART_CMD_RXFLUSH       2
#define USART_CMD_RXENABLE      3
#define USART_CMD_RXDISABLE     4
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Functions 
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
