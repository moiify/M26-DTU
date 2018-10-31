/**
 **************************************************************************************************
 * @file        zsproto_package_process.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_PACKAGE_PROCESS_H_
#define _ZSPROTO_PACKAGE_PROCESS_H_
#include "zsproto.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_package_process_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_package_process_Exported_Macros 
 * @{  
 */
#define CONFIG_TAG_MAINSERVER_ENABLE            1  // 1     
#define CONFIG_TAG_MAINSERVERDOMAIN_ENABLE      2  // 1
#define CONFIG_TAG_MAINSERVERIP                 3  // 4
#define CONFIG_TAG_MAINSERVERPORT               4  // 2
#define CONFIG_TAG_MAINSERVERDOMAINNAME         5  // <=50
#define CONFIG_TAG_BACKUPSERVER_ENABLE          6  // 1
#define CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE    7  // 1
#define CONFIG_TAG_BACKUPSERVERIP               8  // 4
#define CONFIG_TAG_BACKUPSERVERPORT             9  // 2
#define CONFIG_TAG_BACKUPSERVERDOMAINNAME       10 // <=50  A
#define CONFIG_TAG_MOUDLEBOUNDRATE              11 // 4
#define CONFIG_TAG_OPEARTINGMODE                12 // 1
#define CONFIG_TAG_HEARTBEATEN                  13 // 1
     
#define DATA_TAG_RSSIFEEDBACK                   21
/**
 * @}
 */

/**
 * @defgroup      zsproto_package_process_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_package_process_Exported_Types 
 * @{  
 */
#pragma pack(1)

typedef struct
{
    uint8_t Tag;
    uint8_t Len;
    union
    {
        uint8_t  Bit8;
        uint16_t Bit16;
        uint32_t Bit32;
        uint8_t  Array[100];
    }Value;
}ZSProtoConfigTLV_t;

typedef struct
{
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV;
}ConfigGetRespPayload_t;

typedef struct
{
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV; 
}ConfigSetReqPayload_t;

typedef struct
{
    uint8_t     Result;
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV;
}ConfigSetRespPayload_t;

typedef struct
{
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV;
}RssiRespPayload_t;

typedef struct
{   
    uint8_t  mux;
    uint8_t *pData;
}SocketDataPayload_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      zsproto_package_process_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_package_process_Exported_Functions 
 * @{  
 */
void ZSProto_SendDataReq_Process(uint8_t *pBuf,uint16_t length);
uint8_t ZSProto_CSQPackageMake(uint8_t *pBuf,uint16_t length);
void ZSProto_ConfigSetReq_Process(uint8_t *pBuf,uint16_t length);
uint16_t ZSProto_Make_ConfigSetResp(uint8_t *pBuf,uint8_t result,uint8_t seq);
void ZSProto_Make_RssiResp(uint8_t rssi);
uint16_t ZSProto_Make_SocketDataPackage(uint8_t muxnum,uint8_t * pdata,uint16_t length);
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
