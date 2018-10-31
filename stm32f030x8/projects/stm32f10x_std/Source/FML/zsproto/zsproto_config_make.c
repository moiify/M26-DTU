/**
 **************************************************************************************************
 * @file        zsproto_config_make.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "zsproto.h"
#include "system_info.h"
#include "system_param.h"
#include "zsproto_config_make.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_config_make_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_config_make_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_make_Functions 
 * @brief         
 * @{  
 */
uint16_t ZSProto_Make_ConfigGetResp(uint8_t *pBuf,uint8_t seq)
{
    uint8_t *p = NULL;

    ZSProtoAPD_Uart_t* apd;
    ZSProtoConfigTLV_t *tlv;
    uint16_t len = 0;
    uint8_t *fcs;

    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;

    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPD_Uart_t*)p;
    apd->FCF.bitfield.reserve = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.AckReq = 0;
    apd->Seq = seq;
    apd->Model = THIS_DEVICE_MODEL;
    apd->DeviceId = g_SystemInfo.DeviceId;
    apd->Addr = ZSPROTO_ADDR_NOTCARE;
    apd->Cmd = ZSCmd_ConfigGetResp;
    p += sizeof(ZSProtoAPD_Uart_t) - sizeof(apd->CmdPayload);

    // 0
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SWITCHDETECTIONMODE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.SwitchDetectionMode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 1
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_PROBECOUNT;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.ProbeCount;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 2
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_REPORTINTERVAL;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.ReportInterval;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 3
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_CLEANRATIO;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.CleanRatio;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 4
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_FANRATIO;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.FanRatio;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 5
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HJ212_EPC_HEAD;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.HJ212_EPC96_Head;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 6
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HJ212_EPC_MFCODE;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.HJ212_EPC96_ManufacturesCode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 7
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HJ212_EPC_OBJCODE;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.HJ212_EPC96_ObjectCode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 8
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HJ212_EPC_SEQ;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.HJ212_EPC96_Sequence;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 9
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HJ212_PASSWORD;
    tlv->Len = 6;
    for (int i=0; i < sizeof(g_SystemParam_Config.HJ212_Password); i++)
    {
        tlv->Value.Array[i] = g_SystemParam_Config.HJ212_Password[i];
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 10
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.MainServerInfo.DomainEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 11
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.MainServerInfo.Port;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 12
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit16 = g_SystemParam_Config.MainServerInfo.Ip;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 13
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemParam_Config.MainServerInfo.DomainNameStr); i++)
    {
        if (g_SystemParam_Config.MainServerInfo.DomainNameStr[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemParam_Config.MainServerInfo.DomainNameStr[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 14
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.BackupServerEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 15
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.BackupServerInfo.DomainEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 16
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.BackupServerInfo.Port;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 17
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.BackupServerInfo.Ip;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 18
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemParam_Config.BackupServerInfo.DomainNameStr); i++)
    {
        if (g_SystemParam_Config.BackupServerInfo.DomainNameStr[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemParam_Config.BackupServerInfo.DomainNameStr[i];
        tlv->Len = i;
    }
    tlv->Value.Bit16 = g_SystemParam_Config.HJ212_EPC96_ObjectCode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 19
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.HookServerEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 20
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.HookServerInfo.DomainEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 21
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.HookServerInfo.Port;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 22
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.HookServerInfo.Ip;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 23
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemParam_Config.HookServerInfo.DomainNameStr); i++)
    {
        if (g_SystemParam_Config.HookServerInfo.DomainNameStr[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemParam_Config.HookServerInfo.DomainNameStr[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 24
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKBAKSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.HookBAKServerEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 25
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKBAKSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemParam_Config.HookBAKServerInfo.DomainEnable;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 26
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKBAKSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemParam_Config.HookBAKServerInfo.Port;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 27
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKBAKSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemParam_Config.HookBAKServerInfo.Ip;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 28
    tlv = (ZSProtoConfigTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HOOKBAKSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemParam_Config.HookBAKServerInfo.DomainNameStr); i++)
    {
        if (g_SystemParam_Config.HookBAKServerInfo.DomainNameStr[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemParam_Config.HookBAKServerInfo.DomainNameStr[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;

    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;

    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF
        ;

    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    return len;
}

uint16_t ZSProto_Make_ConfigSetResp(uint8_t *pBuf,uint8_t seq)
{
    return ZSProto_Make_ConfigGetResp(pBuf,seq);
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

