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
SystemInfo_t g_SystemInfo=
{   
    .MainServerEN=SERVER_ENABLE,
    .MainServerIp="116.62.102.100",
    .MainServerPort=14000,
    .MainServerDomain="www.njzhhb.com",
    .MainServerConnectway=IP_Connect,
    
    .SpareServerIp="116.62.102.100",
    .SpareServerEN=SERVER_DISABLE,
    .SpareServerPort=8080,
    .SpareServerConnectway=IP_Connect,
    
    .Gprs_Init_Status=Gprs_Init_NotComplete,
    .Socket0_Status=Socket_Init_NotComplete,
    .Socket1_Status=Socket_Init_NotComplete,
};

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

