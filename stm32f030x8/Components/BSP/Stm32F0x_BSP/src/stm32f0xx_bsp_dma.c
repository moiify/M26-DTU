/**
**************************************************************************************************
* @file        stm32f0xx_bsp_dma.c
* @author
* @version   v0.1.0
* @date        
* @brief
**************************************************************************************************
* @attention
*
**************************************************************************************************
*/
#include "stm32f0xx_bsp_dma.h"
#include "stm32f0xx_bsp_conf.h"
#include "gprs_cache.h"
/**
* @addtogroup    XXX 
* @{  
*/

/**
* @addtogroup    stm32f0xx_bsp_dma_Modules 
* @{  
*/

/**
* @defgroup      stm32f0xx_bsp_dma_IO_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Macros_Defines 
* @brief         
* @{  
*/

/**
* @}
*/
/**
* @defgroup      stm32f0xx_bsp_dma_Constants_Defines 
* @brief         
* @{  
*/
/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Private_Types
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Private_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Public_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Private_FunctionPrototypes 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_dma_Functions 
* @brief         
* @{  
*/
//void BSP_DMA_USART_StructInit(DMA_InitTypeDef *dma_init,BSP_DMA_USART_ConfigTypedef *config)
//{
//    dma_init->DMA_PeripheralBaseAddr = config->PeriphAddr;
//    dma_init->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//    dma_init->DMA_MemoryBaseAddr = config->MemAddr;
//    dma_init->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//    dma_init->DMA_DIR = config->Dir;
//    dma_init->DMA_BufferSize = config->BufSize;
//    dma_init->DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
//    dma_init->DMA_MemoryInc = DMA_MemoryInc_Enable;
//    dma_init->DMA_Priority = DMA_Priority_High;
//    dma_init->DMA_Mode = config->Mode;
//    dma_init->DMA_M2M = DMA_M2M_Disable;
//}

void  BSP_DMA_USART_StructInit(uint8_t BSP_USARTx)
{   
    uint8_t s_address[1];
    
    DMA_InitTypeDef dma_initstructure;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    if(BSP_USARTx==BSP_USART1)
    {
        dma_initstructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->TDR;
        dma_initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        dma_initstructure.DMA_MemoryBaseAddr = (uint32_t)g_AT_ReceiveBuf.Buf;
        dma_initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        dma_initstructure.DMA_DIR = DMA_DIR_PeripheralDST;
        dma_initstructure.DMA_BufferSize =0;
        dma_initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
        dma_initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        dma_initstructure.DMA_Priority = DMA_Priority_Low;
        dma_initstructure.DMA_Mode = DMA_Mode_Normal;
        dma_initstructure.DMA_M2M = DMA_M2M_Disable;
        
        DMA_Init(DMA1_Channel2,&dma_initstructure);    
        DMA_RemapConfig(DMA1, DMA1_CH2_USART1_TX);
    }
    //    dma_initstructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->RDR;
    //    dma_initstructure.DMA_MemoryBaseAddr = (uint32_t)g_AT_ReceiveBuf.Buf;
    //    dma_initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    //    dma_initstructure.DMA_BufferSize = sizeof(g_AT_ReceiveBuf.Buf) / sizeof(g_AT_ReceiveBuf.Buf[0]);
    //    dma_initstructure.DMA_Priority = DMA_Priority_High;
    //    
    //    DMA_Init(DMA1_Channel1,&dma_initstructure);
    //    DMA_RemapConfig(DMA1, DMA1_CH1_USART1_RX);
    if(BSP_USARTx==BSP_USART2)
    {
        dma_initstructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->TDR; 
        dma_initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        dma_initstructure.DMA_MemoryBaseAddr = (uint32_t)s_address;
        dma_initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        dma_initstructure.DMA_DIR = DMA_DIR_PeripheralDST;
        dma_initstructure.DMA_BufferSize =0;
        dma_initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
        dma_initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        dma_initstructure.DMA_Priority = DMA_Priority_Low;
        dma_initstructure.DMA_Mode = DMA_Mode_Normal;
        dma_initstructure.DMA_M2M = DMA_M2M_Disable;
        
        NVIC_InitStruct.NVIC_IRQChannel=DMA1_Channel4_5_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPriority=2;
        NVIC_Init(&NVIC_InitStruct);
        
       // DMA_ITConfig( DMA1_Channel4, DMA_IT_TC ,DISABLE); 
        DMA_Init(DMA1_Channel4,&dma_initstructure);    
        DMA_RemapConfig(DMA1, DMA1_CH4_USART2_TX);
        
        dma_initstructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->RDR;
        dma_initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        dma_initstructure.DMA_MemoryBaseAddr = (uint32_t)g_Machine_ReceiveBuf.pData;
        dma_initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        dma_initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        dma_initstructure.DMA_BufferSize =BSP_USART2_RXBUF_SIZE;
        dma_initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
        dma_initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        dma_initstructure.DMA_Priority = DMA_Priority_Low;
        dma_initstructure.DMA_Mode = DMA_Mode_Circular;
        dma_initstructure.DMA_M2M = DMA_M2M_Disable;

        DMA_Init(DMA1_Channel5,&dma_initstructure);    
        DMA_RemapConfig(DMA1, DMA1_CH5_USART2_RX);
        DMA_Cmd(DMA1_Channel5, ENABLE);
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

