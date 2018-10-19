#include "stm32f0xx_bsp_usart.h"
  
Receive_Cache_t g_AT_ReceiveBuf =
{   
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(g_AT_ReceiveBuf.Buf)/sizeof(g_AT_ReceiveBuf.Buf[0]),
};

Receive_Cache_t g_Server_ReceiveBuf =
{
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(g_Server_ReceiveBuf.Buf)/sizeof(g_Server_ReceiveBuf.Buf[0]),
};
Socket_Cache_t g_Machine_TransmitBuf=
{   
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(g_Machine_TransmitBuf.Buf)/sizeof(g_Machine_TransmitBuf.Buf[0]),
};    

uint8_t g_USART1_ReceiveCompleteFlag=0;

void BSP_USART_Open(uint8_t BSP_USARTx, GPRS_USARTParams_t *GPRSparams)
{
  
    USART_InitTypeDef usart_initstructure;
    GPIO_InitTypeDef  gpio_initstructure;
    NVIC_InitTypeDef  nvic_initstructure;
//    if (GPRSparams != NULL)
//    { 
//        baudrate = GPRSparams->Baudrate;
//    }
    if (BSP_USARTx == BSP_USART1)
    {     
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
             
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); 
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);    
              
        gpio_initstructure.GPIO_Pin=GPIO_Pin_9;
        gpio_initstructure.GPIO_Mode=GPIO_Mode_AF;
        gpio_initstructure.GPIO_Speed=GPIO_Speed_50MHz;
        gpio_initstructure.GPIO_OType=GPIO_OType_PP;
        gpio_initstructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &gpio_initstructure);
        
        gpio_initstructure.GPIO_Pin=GPIO_Pin_10;
        gpio_initstructure.GPIO_Mode=GPIO_Mode_AF;
        gpio_initstructure.GPIO_Speed=GPIO_Speed_50MHz;
        gpio_initstructure.GPIO_OType=GPIO_OType_PP;
        gpio_initstructure.GPIO_PuPd=GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &gpio_initstructure);
        
        
        nvic_initstructure.NVIC_IRQChannel = USART1_IRQn;
        nvic_initstructure.NVIC_IRQChannelPriority =2;
        nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&nvic_initstructure);

        usart_initstructure.USART_BaudRate=115200;        
        usart_initstructure.USART_WordLength = USART_WordLength_8b,
        usart_initstructure.USART_StopBits = USART_StopBits_1,
        usart_initstructure.USART_Parity = USART_Parity_No,
        usart_initstructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx,
        usart_initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        USART_Init(USART1,&usart_initstructure);
        USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
        USART_Cmd(USART1, ENABLE);
                
        BSP_DMA_USART1_StructInit();        
        USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE); 
        DMA_Cmd(DMA1_Channel2, DISABLE);
        DMA_Cmd(DMA1_Channel1, ENABLE); 
   
    }
}
void  BSP_USART_WriteBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t length)
{      
    if(BSP_USARTx==BSP_USART1)
    {         
            DMA_Cmd(DMA1_Channel2,DISABLE);
            DMA1_Channel2->CMAR = (uint32_t)pBuf;
            DMA1_Channel2->CNDTR = length;
            DMA_Cmd(DMA1_Channel2,ENABLE);
    }
}



//void BSP_USART_TxDMA_IRQHandler(uint8_t BSP_USARTx)
//{
//    
//    if (DMA_GetITStatus(DMA1_IT_TC4) != RESET)
//    {
//        DMA_ClearITPendingBit(DMA1_IT_TC4);
//        BSP_USART_WriteBytesDMAISR(BSP_USARTx);
//    }   
//
//}