#include "stm32f0xx_bsp_usart.h"
#include "gprs_cache.h"
#include "user_task.h"
//static void Uart_DMA_Rx_Data(void);

static GPRS_USARTParams_t s_GPRS_USARTParams;

static uint16_t BSP_USART_ReadBytesDMA(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t count);
static void bsp_USART_ParameterRedistribution(uint8_t BSP_USARTx);

void BSP_USART_Open(uint8_t BSP_USARTx)
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
        
        USART_DeInit(USART1);
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
        usart_initstructure.USART_Parity=USART_Parity_No;
        usart_initstructure.USART_StopBits=USART_StopBits_1;
        usart_initstructure.USART_WordLength=USART_WordLength_8b;
        usart_initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
        usart_initstructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
        USART_Init(USART1,&usart_initstructure);
        USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
        USART_Cmd(USART1, ENABLE);
        
        
        BSP_DMA_USART_StructInit(BSP_USART1);        
        USART_DMACmd(USART1,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE); 
        DMA_Cmd(DMA1_Channel2, DISABLE);
        DMA_Cmd(DMA1_Channel1, ENABLE); 
        
    }
    if (BSP_USARTx == BSP_USART2)
    {   
        bsp_USART_ParameterRedistribution(BSP_USART2);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
        
        GPIO_PinAFConfig( GPIOA,  GPIO_PinSource2,  GPIO_AF_1);
        GPIO_PinAFConfig( GPIOA,  GPIO_PinSource3,  GPIO_AF_1); 
        
        gpio_initstructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
        gpio_initstructure.GPIO_Mode = GPIO_Mode_AF;
        gpio_initstructure.GPIO_OType=GPIO_OType_PP;
        gpio_initstructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
        gpio_initstructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &gpio_initstructure);
        
        USART_DeInit( USART2);
        usart_initstructure.USART_BaudRate=s_GPRS_USARTParams.Baudrate;     
        usart_initstructure.USART_WordLength = (uint32_t)s_GPRS_USARTParams.DataBits,
        usart_initstructure.USART_StopBits = (uint32_t)s_GPRS_USARTParams.StopBits,
        usart_initstructure.USART_Parity = (uint32_t)s_GPRS_USARTParams.Parity,
        usart_initstructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx,
        usart_initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
        usart_initstructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
        USART_Init( USART2, &usart_initstructure);   
        
        nvic_initstructure.NVIC_IRQChannel=USART2_IRQn;
        nvic_initstructure.NVIC_IRQChannelCmd=ENABLE;
        nvic_initstructure.NVIC_IRQChannelPriority=3;
        NVIC_Init(&nvic_initstructure);   
        USART_ClearITPendingBit( USART2, USART_IT_IDLE);
        USART_ITConfig( USART2, USART_IT_IDLE, ENABLE);
        
        BSP_DMA_USART_StructInit(BSP_USART2);
        USART_DMACmd(USART2,USART_DMAReq_Rx|USART_DMAReq_Tx,ENABLE); 
        
        USART_Cmd( USART2, ENABLE);
        
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
    if(BSP_USARTx==BSP_USART2)
    {         
        DMA_Cmd(DMA1_Channel4,DISABLE);
        DMA1_Channel4->CMAR = (uint32_t)pBuf;
        DMA1_Channel4->CNDTR = length;
        DMA_Cmd(DMA1_Channel4,ENABLE);
    }
}

void BSP_USART_IRQHandler(uint8_t BSP_USARTx)
{   
    if(BSP_USARTx==BSP_USART2)
    {
        if (USART_GetITStatus(USART2,USART_IT_IDLE) != RESET)
        {
            USART_ClearITPendingBit( USART2, USART_IT_IDLE);
            //Uart_DMA_Rx_Data();
            UserTask_Send_Event(USER_TASK_LOOP_EVENT);
            USART_ReceiveData(USART2);
        }
    }
}

static void bsp_USART_ParameterRedistribution(uint8_t BSP_USARTx)
{
    if(BSP_USARTx==BSP_USART2)
    {   
        s_GPRS_USARTParams.Baudrate=g_SystemInfo.Gprs_SerialPort_BaudRate;
        switch(g_SystemInfo.Gprs_SerialPort_Parity)
        {
            case 0:
            {
                s_GPRS_USARTParams.Parity=USART_Parity_No;
                break;
            }
            case 1:
            {
                s_GPRS_USARTParams.Parity=USART_Parity_Odd;
                break;
            }
            case 2:
            {
                s_GPRS_USARTParams.Parity=USART_Parity_Even;
                break;
            }
            default:
            {
            }
            break;
        }
        switch(g_SystemInfo.Gprs_SerialPort_DataBits)
        {
            case 0:
            {
                s_GPRS_USARTParams.DataBits=USART_WordLength_7b;
                break;
            }
            case 1:
            {
                s_GPRS_USARTParams.DataBits=USART_WordLength_8b;
                break;
            }
            case 2:
            {
                s_GPRS_USARTParams.DataBits=USART_WordLength_9b;
                break;
            }
            default:
            {
                 s_GPRS_USARTParams.DataBits=USART_WordLength_8b;
            }
            break;
        }
        switch(g_SystemInfo.Gprs_SerialPort_StopBits)
        {
            case 0:
            {
                s_GPRS_USARTParams.StopBits=USART_StopBits_1;
                break;
            }
            case 1:
            {
                s_GPRS_USARTParams.StopBits=USART_StopBits_1_5;
                break;
            }
            case 2:
            {
                s_GPRS_USARTParams.StopBits=USART_StopBits_2;
                break;
            }
            default:
            {
            }
            break;
        }
    }
}
//static void Uart_DMA_Rx_Data(void)
//{
//    uint16_t len = 0;
//    socket_buf_t *p;
//    
//    DMA_Cmd(DMA1_Channel5, DISABLE);       // 关闭DMA ，防止干扰
//    
//    DMA_ClearFlag( DMA1_FLAG_TC5|DMA1_FLAG_GL5|DMA1_FLAG_TE5 );           // 清DMA标志位
//    if(g_Machine_ReceiveBuf.Count<g_Machine_ReceiveBuf.Size)
//    {
//        len = BSP_USART2_RXBUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5); //获得接收到的字节数
//        g_Machine_ReceiveBuf.pData[]='\0';
//        g_Machine_ReceiveBuf.In++;
//        g_Machine_ReceiveBuf.In %= g_Machine_ReceiveBuf.Size;
//        g_Machine_ReceiveBuf.Count++;
//    }
//    p = &g_Machine_ReceiveBuf.Buf[g_Machine_ReceiveBuf.In];
//    DMA1_Channel5->CMAR =  (uint32_t)p->Buf;
//    DMA1_Channel5->CNDTR = BSP_USART2_RXBUF_SIZE;
//    DMA_Cmd(DMA1_Channel5, ENABLE);  
//}

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

uint16_t BSP_USART_ReadBytes(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t count)
{	
	if (BSP_USARTx==BSP_USART2) 
	{
		return BSP_USART_ReadBytesDMA(BSP_USARTx, pBuf, count);
	}
    else 
    {
        return 0;
    }
}
//
static uint16_t BSP_USART_ReadBytesDMA(uint8_t BSP_USARTx,uint8_t* pBuf,uint16_t count)
{
    uint16_t read_count = 0;
    uint8_t* p = pBuf;

    while (count--)
    {
        g_Machine_ReceiveBuf.In = g_Machine_ReceiveBuf.Size - DMA_GetCurrDataCounter(DMA1_Channel5);
        if (g_Machine_ReceiveBuf.In == g_Machine_ReceiveBuf.Out)
        {
            return read_count;
        }

        *p++ = g_Machine_ReceiveBuf.pData[g_Machine_ReceiveBuf.Out++];
        g_Machine_ReceiveBuf.Out %= g_Machine_ReceiveBuf.Size;
        read_count++;
    }
    return read_count;
}