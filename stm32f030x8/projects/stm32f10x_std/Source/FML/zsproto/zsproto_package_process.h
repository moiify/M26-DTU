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
#define CONFIG_TAG_OPEARTINGMODE                0 
#define DATA_TAG_RSSIFEEDBACK                   1
#define DATA_TAG_LINKSTATEFEEDBACK				2
#define CONFIG_TAG_SERIALPORTBAUDRATE			3
#define CONFIG_TAG_SERIALPORTPARITY				4
#define CONFIG_TAG_SERIALPORTDATABITS			5
#define CONFIG_TAG_SERIALPORTSTOPBITS			6
#define CONFIG_TAG_MAINSERVERDOMAIN_ENABLE      7  
#define CONFIG_TAG_MAINSERVERPORT               8      
#define CONFIG_TAG_MAINSERVERIP                 9  
#define CONFIG_TAG_MAINSERVERDOMAINNAME         10  // <=50
#define CONFIG_TAG_BACKUPSERVER_ENABLE          11  
#define CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE    12  
#define CONFIG_TAG_BACKUPSERVERPORT             13       
#define CONFIG_TAG_BACKUPSERVERIP               14  
#define CONFIG_TAG_BACKUPSERVERDOMAINNAME       15  // <=50  

#define CONFIG_TAG_MAINSERVER_ENABLE            88  // 暂时未用
#define CONFIG_TAG_MOUDLEBOUNDRATE              99  // 暂时未用 
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
}ConfigGetRespPayload_t;

typedef struct
{
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV;
}RssiRespPayload_t;

typedef struct
{
    uint8_t     TLVCount;
    ZSProtoTLV_t *pTLV;
}LinkstateRespPayload_t;

typedef struct
{   
    uint8_t  mux;
    uint8_t pData[1024];
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
void     ZSProto_SocketPcakSend_Process(uint8_t *pBuf,uint16_t length);
void     ZSProto_ConfigSetReq_Process(uint8_t *pBuf,uint16_t length);
void     ZSProto_ConfigGetReq_Process(void);
void     ZSProto_RssiNotify_Process(void);
void     ZSProto_LinkStateNotify_Process(void);
uint16_t ZSProto_Make_SocketDataPackage(uint8_t muxnum,uint8_t * pdata,uint16_t length);
uint16_t ZSProto_Make_ConfigSetResp(uint8_t *pBuf,uint8_t result,uint8_t seq);
uint16_t ZSProto_Make_ConfigGetResp(uint8_t *pBuf,uint8_t result,uint8_t seq);
void     ZSProto_Make_RssiNotify(uint8_t rssi);
void     ZSProto_Make_LinkStateNotify(uint8_t linkstate);


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
