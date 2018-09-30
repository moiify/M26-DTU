/**
 **************************************************************************************************
 * @file        system_info.h
 * @author
 * @version
 * @date        2/7/2018
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    system_info_Modules 
 * @{  
 */

/**
 * @defgroup      system_info_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_info_Exported_Types 
 * @{  
 */
typedef struct
{
//    uint8_t     MainServerDomainEnable;
    uint32_t    MainServerIp;
//    uint8_t     MainServerDomainLen;
//    char        MainServerDomainStr[DOMAIN_LENGTH_MAX+1];
//    uint16_t    MainServerPort;


}SystemInfo_t;
/**
 * @}
 */

/**
 * @defgroup      system_info_Exported_Variables 
 * @{  
 */
extern SystemInfo_t g_SystemInfo;
/**
 * @}
 */

/**
 * @defgroup      system_info_Exported_Functions 
 * @{  
 */
void    SystemInfo_Init(void);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
