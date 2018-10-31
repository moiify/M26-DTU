/**
 **************************************************************************************************
 * @file        zsproto_config_make.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_CONFIG_MAKE_H_
#define _ZSPROTO_CONFIG_MAKE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_config_make_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_config_make_Exported_Macros 
 * @{  
 */
#define CONFIG_TAG_SWITCHDETECTIONMODE          0   // 1
#define CONFIG_TAG_PROBECOUNT                   1   // 1
#define CONFIG_TAG_REPORTINTERVAL               2   // 2
#define CONFIG_TAG_CLEANRATIO                   3   // 2
#define CONFIG_TAG_FANRATIO                     4   // 2
#define CONFIG_TAG_HJ212_EPC_HEAD               5   // 1
#define CONFIG_TAG_HJ212_EPC_MFCODE             6   // 4
#define CONFIG_TAG_HJ212_EPC_OBJCODE            7   // 4
#define CONFIG_TAG_HJ212_EPC_SEQ                8   // 4
#define CONFIG_TAG_HJ212_PASSWORD               9   // 6
#define CONFIG_TAG_MAINSERVERDOMAIN_ENABLE      10  // 1
#define CONFIG_TAG_MAINSERVERPORT               11  // 2
#define CONFIG_TAG_MAINSERVERIP                 12  // 4
#define CONFIG_TAG_MAINSERVERDOMAINNAME         13  // <=50
#define CONFIG_TAG_BACKUPSERVER_ENABLE          14  // 1
#define CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE    15  // 1
#define CONFIG_TAG_BACKUPSERVERPORT             16  // 2
#define CONFIG_TAG_BACKUPSERVERIP               17  // 4
#define CONFIG_TAG_BACKUPSERVERDOMAINNAME       18  // <=50
#define CONFIG_TAG_HOOKSERVER_ENABLE            19  // 1
#define CONFIG_TAG_HOOKSERVERDOMAIN_ENABLE      20  // 1
#define CONFIG_TAG_HOOKSERVERPORT               21  // 2
#define CONFIG_TAG_HOOKSERVERIP                 22  // 4
#define CONFIG_TAG_HOOKSERVERDOMAINNAME         23  // <=50
#define CONFIG_TAG_HOOKBAKSERVER_ENABLE         24  // 1
#define CONFIG_TAG_HOOKBAKSERVERDOMAIN_ENABLE   25  // 1
#define CONFIG_TAG_HOOKBAKSERVERPORT            26  // 2
#define CONFIG_TAG_HOOKBAKSERVERIP              27  // 4
#define CONFIG_TAG_HOOKBAKSERVERDOMAINNAME      28  // <=50
/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Exported_Types 
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
    uint8_t     HJ212_EPC96_Head;
    uint32_t    HJ212_EPC96_ManufacturesCode;
    uint32_t    HJ212_EPC96_ObjectCode;
    uint32_t    HJ212_EPC96_Sequence;
    uint8_t     HJ212_Password[9];

    uint16_t    ReportInterval; // 上报间隔，单位秒
    uint16_t    CleanRatio;
    uint16_t    FanRatio;

    uint8_t     ProbeCount;
    uint8_t     SwitchDetectionMode;

    uint8_t     DomainEnable;
    uint16_t    ServerPort;
    uint32_t    ServerIp;
    uint8_t     DomainLen;  
    char*       Domain;   

}ConfigGetRespPayload_t;

typedef struct
{
    uint8_t     HJ212_EPC96_Head;
    uint32_t    HJ212_EPC96_ManufacturesCode;
    uint32_t    HJ212_EPC96_ObjectCode;
    uint32_t    HJ212_EPC96_Sequence;
    uint8_t     HJ212_Password[9];

    uint16_t    ReportInterval; // 上报间隔，单位秒
    uint16_t    CleanRatio;
    uint16_t    FanRatio;

    uint8_t     ProbeCount;
    uint8_t     SwitchDetectionMode;

    uint8_t     DomainEnable;
    uint16_t    ServerPort;
    uint32_t    ServerIp;
    uint8_t     DomainLen;  
    char*       Domain;  

}ConfigSetReqPayload_t;

typedef struct
{
    uint8_t     HJ212_EPC96_Head;
    uint32_t    HJ212_EPC96_ManufacturesCode;
    uint32_t    HJ212_EPC96_ObjectCode;
    uint32_t    HJ212_EPC96_Sequence;
    uint8_t     HJ212_Password[9];

    uint16_t    ReportInterval; // 上报间隔，单位秒
    uint16_t    CleanRatio;
    uint16_t    FanRatio;

    uint8_t     ProbeCount;
    uint8_t     SwitchDetectionMode;

    uint8_t     DomainEnable;
    uint16_t    ServerPort;
    uint32_t    ServerIp;
    uint8_t     DomainLen;  
    char*       Domain;  

}ConfigSetRespPayload_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Exported_Functions 
 * @{  
 */
uint16_t ZSProto_Make_ConfigGetResp(uint8_t *pBuf,uint8_t seq);
uint16_t ZSProto_Make_ConfigSetResp(uint8_t *pBuf,uint8_t seq);
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
