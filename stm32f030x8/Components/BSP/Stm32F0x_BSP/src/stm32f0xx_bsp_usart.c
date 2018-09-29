/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_usart.c
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
#if BSP_USART_MODULE_ENABLE == 1

/**
 * @addtogroup    stm32f0xx_bsp_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Private_Types
 * @brief         
 * @{  
 */
uint8_t USART1_Tx_Buf[BSP_USART1_TXBUF_SIZE];
uint8_t USART1_Rx_Buf[BSP_USART1_RXBUF_SIZE];
uint8_t USART2_Tx_Buf[BSP_USART2_TXBUF_SIZE];
uint8_t USART2_Rx_Buf[BSP_USART2_RXBUF_SIZE];
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_MD)
uint8_t USART3_Tx_Buf[BSP_USART3_TXBUF_SIZE];
uint8_t USART3_Rx_Buf[BSP_USART3_RXBUF_SIZE];
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) 
uint8_t USART4_Tx_Buf[BSP_USART4_TXBUF_SIZE];
uint8_t USART4_Rx_Buf[BSP_USART4_RXBUF_SIZE];
uint8_t USART5_Tx_Buf[BSP_USART5_TXBUF_SIZE];
uint8_t USART5_Rx_Buf[BSP_USART5_RXBUF_SIZE];
#endif 
#endif

static STM32F10xUSART_Instance_t stm32f10xUSART_Instance[BSP_USARTCOUNT] = 
{
    /* USART1 */
    {
        /* USART_TypeDef */
        .Instance = USART1,
        /* tx buf */
        .TxBuf.pData = USART1_Tx_Buf,
        .TxBuf.Size = sizeof(USART1_Tx_Buf) / sizeof(USART1_Tx_Buf[0]),
        .TxBuf.Count = 0,
        .TxBuf.In = 0,
        .TxBuf.Out = 0,
        /* rx buf */
        .RxBuf.pData = USART1_Rx_Buf,
        .RxBuf.Size = sizeof(USART1_Rx_Buf) / sizeof(USART1_Rx_Buf[0]),
        .RxBuf.Count = 0,
        .RxBuf.In = 0,
        .RxBuf.Out = 0,
    },
    /* USART2 */
    {
        /* USART_TypeDef */
        .Instance = USART2,
        /* tx buf */
        .TxBuf.pData = USART2_Tx_Buf,
        .TxBuf.Size = sizeof(USART2_Tx_Buf) / sizeof(USART2_Tx_Buf[0]),
        .TxBuf.Count = 0,
        .TxBuf.In = 0,
        .TxBuf.Out = 0,
        /* rx buf */
        .RxBuf.pData = USART2_Rx_Buf,
        .RxBuf.Size = sizeof(USART2_Rx_Buf) / sizeof(USART2_Rx_Buf[0]),
        .RxBuf.Count = 0,
        .RxBuf.In = 0,
        .RxBuf.Out = 0,
    },
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_MD)          
    /* USART3 */
    {
        /* USART_TypeDef */
        .Instance = USART3,
        /* tx buf */
        .TxBuf.pData = USART3_Tx_Buf,
        .TxBuf.Size = sizeof(USART3_Tx_Buf) / sizeof(USART3_Tx_Buf[0]),
        .TxBuf.Count = 0,
        .TxBuf.In = 0,
        .TxBuf.Out = 0,
        /* rx buf */
        .RxBuf.pData = USART3_Rx_Buf,
        .RxBuf.Size = sizeof(USART3_Rx_Buf) / sizeof(USART3_Rx_Buf[0]),
        .RxBuf.Count = 0,
        .RxBuf.In = 0,
        .RxBuf.Out = 0,
    },
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_CL)
    /* USART4 */
    {
        /* USART_TypeDef */
        .Instance = UART4,
        /* tx buf */
        .TxBuf.pData = USART4_Tx_Buf,
        .TxBuf.Size = sizeof(USART4_Tx_Buf) / sizeof(USART4_Tx_Buf[0]),
        .TxBuf.Count = 0,
        .TxBuf.In = 0,
        .TxBuf.Out = 0,
        /* rx buf */
        .RxBuf.pData = USART4_Rx_Buf,
        .RxBuf.Size = sizeof(USART4_Rx_Buf) / sizeof(USART4_Rx_Buf[0]),
        .RxBuf.Count = 0,
        .RxBuf.In = 0,
        .RxBuf.Out = 0,
    },
    /* USART5 */
    {
        /* USART_TypeDef */
        .Instance = UART5,
        /* tx buf */
        .TxBuf.pData = USART5_Tx_Buf,
        .TxBuf.Size = sizeof(USART5_Tx_Buf) / sizeof(USART5_Tx_Buf[0]),
        .TxBuf.Count = 0,
        .TxBuf.In = 0,
        .TxBuf.Out = 0,
        /* rx buf */
        .RxBuf.pData = USART5_Rx_Buf,
        .RxBuf.Size = sizeof(USART5_Rx_Buf) / sizeof(USART5_Rx_Buf[0]),
        .RxBuf.Count = 0,
        .RxBuf.In = 0,
        .RxBuf.Out = 0,
    },
#endif    
};
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Functions 
 * @brief         
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

