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
    .MainServerIp="103.46.128.43",
    .MainServerPort=56527,
    .MainServerDomain="www.njzhhb.com",
    .MainServerConnectway=IP_Connect,
    
    .SpareServerIp="103.46.128.43",
    .SpareServerEN=SERVER_DISABLE,
    .SpareServerPort=56527,
    .SpareServerConnectway=IP_Connect,
    
    .Gprs_Init_Status=Gprs_Init_NotComplete,
    .Gprs_Operatingmode=Gprs_Packagemode,
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

