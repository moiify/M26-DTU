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
#define SERVER_ENABLE 1
#define SERVER_DISABLE 0
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
typedef enum
{
  IP_Connect,
  Domain_Connect,   
}Socket_Connectway;

typedef enum
{
  Gprs_Init_NotComplete,
  Gprs_Init_Complete, 
}Gprs_Running_Status;

typedef enum
{
 Gprs_Transparentmode,   
 Gprs_Packagemode,  
}Gprs_OperatingMode;
typedef struct
{
    uint8_t                      MainServerEN;
    uint8_t                      MainServerIp[16];
    uint32_t                     MainServerPort;
    uint8_t                      MainServerDomain[80];
    Socket_Connectway            MainServerConnectway;
    uint8_t                      SpareServerEN;
    uint8_t                      SpareServerIp[16];
    uint32_t                     SpareServerPort;
    uint8_t                      SpareServerDomain[80];
    Socket_Connectway            SpareServerConnectway;
    
    uint8_t                      Gprs_Boundrate;
    Gprs_Running_Status          Gprs_Init_Status;
    Gprs_OperatingMode           Gprs_Operatingmode;

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
