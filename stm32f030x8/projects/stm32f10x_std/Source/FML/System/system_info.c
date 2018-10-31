/**
 **************************************************************************************************
 * @file        system_info.c
 * @author
 * @version
 * @date        2/7/2018
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_info.h"
#include "system_param.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    system_info_Modules 
 * @{  
 */

/**
 * @defgroup      system_info_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       system_info_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       system_info_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Public_Variables 
 * @brief         
 * @{  
 */
SystemInfo_t g_SystemInfo;

/**
 * @}
 */

/**
 * @defgroup      system_info_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Functions 
 * @brief         
 * @{  
 */
void SystemInfo_Init(void)
{
    SystemParam_Init();
}

void SystemInfo_ReadSn(uint8_t *pBuf)
{

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

