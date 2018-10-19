/**
 **************************************************************************************************
 * @file        stm32f0xx_bsp_nvic.c
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
#if BSP_NVIC_MODULE_ENABLE == 1
/**
 * @addtogroup    stm32f0xx_bsp_nvic_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Constants_Defines 
 * @brief         
 * @{  
 */
#define NVIC_PRIORITY_LIST_COUNT    15
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t IRQChannel;
    uint8_t Priority;
}NVIC_PriorityTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Private_Variables 
 * @brief         
 * @{  
 */
volatile static NVIC_PriorityTypedef NVIC_PriorityList[NVIC_PRIORITY_LIST_COUNT];
static uint8_t              NVIC_PriorityListCount = 0;
/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f0xx_bsp_nvic_Functions 
 * @brief         
 * @{  
 */
void BSP_NVIC_Config(uint8_t IRQChannel,uint8_t Priority,FunctionalState NewState)
{
    NVIC_InitTypeDef NVIC_InitStructure;

//    NVIC_PriorityGroupConfig(BSP_NVIC_PRIORITYGROUP_DEFAULT);
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPriority =Priority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Init(&NVIC_InitStructure);

    if (NVIC_PriorityListCount < NVIC_PRIORITY_LIST_COUNT)
    {
        NVIC_PriorityList[NVIC_PriorityListCount].IRQChannel = IRQChannel; 
        NVIC_PriorityList[NVIC_PriorityListCount].Priority = Priority;
        NVIC_PriorityListCount++;
    }
}
/**
 * @}
 */
#endif
/**
 * @}
 */

/**
 * @}
 */

