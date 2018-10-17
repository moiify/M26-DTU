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
#include "stm32f0xx_bsp_conf.h"
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

#define BSP_USART1      0
#define BSP_USART2      1
     
#define USART1_Tx_Buf_MAX_SIZE 200
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
typedef struct
{
   uint32_t Baudrate;
}GPRS_USARTParams_t;

typedef struct
{
	uint8_t Buf[250];
	uint8_t Len;
}receive_buf_t;

typedef struct 
{ 
  receive_buf_t Buf[5];
  uint8_t In;	
  uint8_t Out;
  uint8_t Count;
  uint8_t Size;  
}Receive_Cache_t;


typedef struct 
{ 
  receive_buf_t Buf[8];
  uint8_t In;	
  uint8_t Out;
  uint8_t Count;
  uint8_t Size;  
}Transmit_Cache_t;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Variables 
 * @{  
 */
extern uint8_t g_USART1_ReceiveCompleteFlag;
extern Receive_Cache_t g_AT_ReceiveBuf ;
extern Transmit_Cache_t g_Machine_TransmitBuf;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_usart_Exported_Functions 
 * @{  
 */
void     BSP_USART_Open(uint8_t BSP_USARTx, GPRS_USARTParams_t *GPRSparams);
//void     BSP_USART_Close(uint8_t BSP_USARTx);

void     BSP_USART_WriteBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length);
//uint16_t BSP_USART_ReadBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length);

//int16_t  BSP_USART_Control(uint8_t BSP_USARTx,uint8_t cmd,void *arg);
//void     BSP_USART_ITConfig(uint8_t BSP_USARTx,uint16_t USART_IT,FunctionalState NewState);

//void     BSP_USART_IRQHandler(uint8_t BSP_USARTx);
void     BSP_USART_TxDMA_IRQHandler(uint8_t BSP_USARTx);
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
