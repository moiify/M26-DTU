/**
**************************************************************************************************
* @file        stm32f0xx_bsp_timer.c
* @author
* @version   v0.1.0
* @date        
* @brief
**************************************************************************************************
* @attention
*
**************************************************************************************************
*/
#include "stm32f0xx_bsp_timer.h"
#include "stm32f0xx_bsp_conf.h"
#include "gprs_cache.h"

/**
* @addtogroup    XXX 
* @{  
*/

/**
* @addtogroup    stm32f0xx_bsp_timer_Modules 
* @{  
*/

/**
* @defgroup      stm32f0xx_bsp_timer_IO_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Macros_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Constants_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Private_Types
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Private_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Public_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Private_FunctionPrototypes 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      stm32f0xx_bsp_timer_Functions 
* @brief         
* @{  
*/
void  BSP_Timer_Init(void)
{   
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef  NVIC_InitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    TIM_DeInit( TIM3);
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period=250-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=48;
    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPriority=1;
    NVIC_Init(&NVIC_InitStruct); 
    
    TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
    TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE);
    
}
void BSP_TIMER_IRQHandler(uint8_t BSP_TIMx)
{
    if(BSP_TIMx==BSP_TIM3)
    {

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

