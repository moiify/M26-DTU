/**
 **************************************************************************************************
 * @file        ModbusHardwareInit.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ModbusHardwareInit.h"
#include "ModbusRTU_Slave.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ModbusHardwareInit_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusHardwareInit_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Functions 
 * @brief         
 * @{  
 */
void modbusGPIOInit(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_1;                  //PA 4:LED,6:Switch,1:RS485
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_Level_3;
    GPIO_Init(GPIOA, &GPIO_InitStruct);                                         //LED to show statue of program
    
    GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_1);                     //RS485 control Pin ,1 is send,0 is reveice

    GPIO_PinAFConfig( GPIOA,  GPIO_PinSource9,  GPIO_AF_1);
    GPIO_PinAFConfig( GPIOA,  GPIO_PinSource10,  GPIO_AF_1); 
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void modbusUartInit(void)
{
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef  NVIC_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    USART_DeInit( USART1);
    USART_InitStruct.USART_BaudRate=9600;
    USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStruct.USART_Parity=USART_Parity_No;
    USART_InitStruct.USART_StopBits=USART_StopBits_1;
    USART_InitStruct.USART_WordLength=USART_WordLength_8b;
    USART_Init( USART1, &USART_InitStruct);   
    
    NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPriority=2;
    NVIC_Init(&NVIC_InitStruct);   
	
    USART_ITConfig( USART1, USART_IT_RXNE, ENABLE);

    USART_Cmd( USART1, ENABLE);
} 

void modbusTimInit(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_DeInit( TIM3);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=4000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=48;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=1;
	NVIC_Init(&NVIC_InitStruct); 
	
	TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE);
	
//	TIM_Cmd(TIM3, DISABLE);
	
}


void LedToggle(void)
{
    static uint8_t n=0;
    n=~n;
    if(n==0)
    {
        GPIO_ResetBits( GPIOA,GPIO_Pin_4);
    }
    else
    {
        GPIO_SetBits( GPIOA, GPIO_Pin_4);
    }
}



void ModbusFunctionInit(void)
{
    modbusGPIOInit();
    modbusUartInit();  
	modbusTimInit();
	ModbusRingBufInit();
    ModbusSlaveInit();
}

void ModbusSend(uint8_t * Data,uint8_t Len)
{
    static uint8_t i=0;
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    for (i=0;i<Len;i++)
    {
        USART_SendData(USART1, *(Data+i));
        while(USART_GetFlagStatus( USART1, USART_FLAG_TC)==RESET);    
    }

    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
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

