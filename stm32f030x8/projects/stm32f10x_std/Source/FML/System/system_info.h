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
     
#define SOCKETCOUNT 2 
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
#pragma pack(1)
typedef struct
{
    uint8_t                      ServerEN;
    uint8_t                      ServerIp[16];
    uint32_t                     byte_ServerIp;
    uint16_t                     ServerPort;
    uint8_t                      ServerDomain[80];
    Socket_Connectway            ServerConnectway;
}Socket_Info_t;


typedef struct
{
  
    Socket_Info_t   Socket_ListInfo[SOCKETCOUNT];

    uint32_t                     Gprs_Boundrate;
    
    Gprs_OperatingMode           Gprs_Operatingmode; //0 透传 1包模式
    
    uint32_t                     Gprs_SerialPort_BaudRate; //  9600  115200   
    uint8_t                      Gprs_SerialPort_Parity;   // 0 无校验 1 奇 2偶    
    uint8_t                      Gprs_SerialPort_DataBits; // 0：5位   1:6  2:7 3:8
    uint8_t                      Gprs_SerialPort_StopBits; // 0:1 位  1:1.5位  2:2

    uint8_t                      Gprs_RssiReportEN;
    uint8_t                      Gprs_LinkstateReportEN;
    uint16_t                     crc;
}SystemInfo_t;
#pragma pack()
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
