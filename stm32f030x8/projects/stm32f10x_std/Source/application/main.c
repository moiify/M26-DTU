/**
 **************************************************************************************************
 * @file        main.c
 * @author
 * @version
 * @date        4/25/2017
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "string.h"
#include "stm32_bsp_conf.h"
#include "osal.h"
#include "bsp_init.h"
#include "system_init.h"
#include "main.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    main_Modules 
 * @{  
 */

/**
 * @defgroup      main_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       main_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       main_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      main_Functions 
 * @brief         
 * @{  
 */
int main()
{
    Board_Init();
    
    BSP_SYSTICK_Open();
 
    __enable_irq();
    
    System_Load();
    
    OS_Init();
    
    OS_Start();
    
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

