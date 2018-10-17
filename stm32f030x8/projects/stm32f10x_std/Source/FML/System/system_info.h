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
  Socket_Init_NotComplete,
  Socket_Init_Complete, 
  Socket_Open_Success, 
  Socket_Open_Failed, 
}Socket_Status;

typedef struct
{
    uint8_t     MainServerEN;
    uint8_t     MainServerIp[15];
    uint32_t    MainServerPort;
    uint8_t     MainServerDomain[20];
    Socket_Connectway MainServerConnectway;
    uint8_t     SpareServerEN;
    uint8_t     SpareServerIp[15];
    uint32_t    SpareServerPort;
    uint8_t     SpareServerDomain[20];
    Socket_Connectway SpareServerConnectway;
    
    uint8_t      Gprs_Boundrate;
    Gprs_Running_Status    Gprs_Init_Status;
    Socket_Status  Socket0_Status;
    Socket_Status  Socket1_Status;
    uint8_t      Gprs_RssiValue;
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
