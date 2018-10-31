/**
 **************************************************************************************************
 * @file        zsproto_config_process.c
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
#include "clog.h"
#include "stm32_bsp_conf.h"
#include "system_info.h"
#include "system_param.h"
#include "zsproto_config_make.h"
#include "env_var.h"
#include "zsproto_config_make.h"
#include "zsproto_config_process.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_config_process_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_config_process_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_config_process_Functions 
 * @brief         
 * @{  
 */
void ZSProto_ConfigGetReq_Process(uint8_t *pBuf,uint16_t length)
{
    g_ZSProtoMakeCache.Length = ZSProto_Make_ConfigGetResp(g_ZSProtoMakeCache.Buf, g_ZSProto_Seq++);
    BSP_USART_WriteBytes(COM_USART_MAINTAIN, g_ZSProtoMakeCache.Buf, g_ZSProtoMakeCache.Length);
}

void ZSProto_ConfigSetReq_Process(uint8_t *pBuf,uint16_t length)
{
    uint8_t *p = pBuf;
    ZSProtoConfigTLV_t *tlv;

    //ZSProtoAPD_Uart_t *apd = (ZSProtoAPD_Uart_t*)p;
    p += sizeof(ZSProtoAPD_Uart_t) - 4;//sizeof(apd->CmdPayload);

    while (1)
    {
        if (p - pBuf >= length - 2)
        {
            break;
        }
        tlv = (ZSProtoConfigTLV_t *)p;
        switch (tlv->Tag)
        {
            case CONFIG_TAG_SWITCHDETECTIONMODE:
            {
                if (tlv->Value.Bit8 < SwitchDetectionMode_All)
                {
                    g_SystemParam_Config.SwitchDetectionMode = (SwitchDetectionMode_e)tlv->Value.Bit8;
                }
                break;
            }
            case CONFIG_TAG_PROBECOUNT:
            {
                if (tlv->Value.Bit8 <= PROBE_COUNT_MAX)
                {
                    g_SystemParam_Config.ProbeCount = tlv->Value.Bit8;
                }
                break;
            }
            case CONFIG_TAG_REPORTINTERVAL:
            {
                if (tlv->Value.Bit16 > 0 && tlv->Value.Bit16 <= 3600)
                {
                    g_SystemParam_Config.ReportInterval = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_CLEANRATIO:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemParam_Config.CleanRatio = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_FANRATIO:
            {
                if (tlv->Value.Bit16 > 0)
                {
                        g_SystemParam_Config.FanRatio = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_HJ212_EPC_HEAD: // 5
            {
                g_SystemParam_Config.HJ212_EPC96_Head = tlv->Value.Bit8;
                break;
            }
            case CONFIG_TAG_HJ212_EPC_MFCODE:
            {
                g_SystemParam_Config.HJ212_EPC96_ManufacturesCode = tlv->Value.Bit32;
                break;
            }
            case CONFIG_TAG_HJ212_EPC_OBJCODE:
            {
                g_SystemParam_Config.HJ212_EPC96_ObjectCode = tlv->Value.Bit32;
                break;
            }
            case CONFIG_TAG_HJ212_EPC_SEQ:
            {
                g_SystemParam_Config.HJ212_EPC96_Sequence = tlv->Value.Bit32;
                break;
            }
            case CONFIG_TAG_HJ212_PASSWORD:
            {
                for (int i=0; i < sizeof(g_SystemParam_Config.HJ212_Password); i++)
                {
                    g_SystemParam_Config.HJ212_Password[i] = tlv->Value.Array[i];
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERDOMAIN_ENABLE: // 10
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.MainServerInfo.DomainEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.MainServerInfo.DomainEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemParam_Config.MainServerInfo.Port = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERIP:
            {
                if (tlv->Value.Bit32 > 0)
                {
                    g_SystemParam_Config.MainServerInfo.Ip = tlv->Value.Bit32;
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERDOMAINNAME:
            {
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemParam_Config.MainServerInfo.DomainNameStr))
                {
                    tmp = sizeof(g_SystemParam_Config.MainServerInfo.DomainNameStr) - 1;
                }

                for (i = 0; i <= tmp; i++)
                {
                    g_SystemParam_Config.MainServerInfo.DomainNameStr[i] = tlv->Value.Array[i];
                }
                g_SystemParam_Config.MainServerInfo.DomainNameStr[i] = 0;
                break;
            }
            case CONFIG_TAG_BACKUPSERVER_ENABLE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.BackupServerEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.BackupServerEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE: // 15
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.BackupServerInfo.DomainEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.BackupServerInfo.DomainEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemParam_Config.BackupServerInfo.Port = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERIP:
            {
                if (tlv->Value.Bit32 > 0)
                {
                    g_SystemParam_Config.BackupServerInfo.Ip = tlv->Value.Bit32;
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERDOMAINNAME:
            {
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemParam_Config.BackupServerInfo.DomainNameStr))
                {
                    tmp = sizeof(g_SystemParam_Config.BackupServerInfo.DomainNameStr) - 1;
                }

                for (i = 0; i <= tmp; i++)
                {
                    g_SystemParam_Config.BackupServerInfo.DomainNameStr[i] = tlv->Value.Array[i];
                }
                g_SystemParam_Config.BackupServerInfo.DomainNameStr[i] = 0;
                break;
            }
            case CONFIG_TAG_HOOKSERVER_ENABLE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.HookServerEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.HookServerEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_HOOKSERVERDOMAIN_ENABLE: // 20
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.HookServerInfo.DomainEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.HookServerInfo.DomainEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_HOOKSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemParam_Config.HookServerInfo.Port = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_HOOKSERVERIP:
            {
                if (tlv->Value.Bit32 > 0)
                {
                    g_SystemParam_Config.HookServerInfo.Ip = tlv->Value.Bit32;
                }
                break;
            }
            case CONFIG_TAG_HOOKSERVERDOMAINNAME:
            {
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemParam_Config.HookServerInfo.DomainNameStr))
                {
                    tmp = sizeof(g_SystemParam_Config.HookServerInfo.DomainNameStr) - 1;
                }

                for (i = 0; i <= tmp; i++)
                {
                    g_SystemParam_Config.HookServerInfo.DomainNameStr[i] = tlv->Value.Array[i];
                }
                g_SystemParam_Config.HookServerInfo.DomainNameStr[i] = 0;
                break;
            }
            case CONFIG_TAG_HOOKBAKSERVER_ENABLE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.HookBAKServerEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.HookBAKServerEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_HOOKBAKSERVERDOMAIN_ENABLE: // 25
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemParam_Config.HookBAKServerInfo.DomainEnable = 0;
                }
                else
                {
                    g_SystemParam_Config.HookBAKServerInfo.DomainEnable = 1;
                }
                break;
            }
            case CONFIG_TAG_HOOKBAKSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemParam_Config.HookBAKServerInfo.Port = tlv->Value.Bit16;
                }
                break;
            }
            case CONFIG_TAG_HOOKBAKSERVERIP:
            {
                if (tlv->Value.Bit32 > 0)
                {
                    g_SystemParam_Config.HookBAKServerInfo.Ip = tlv->Value.Bit32;
                }
                break;
            }
            case CONFIG_TAG_HOOKBAKSERVERDOMAINNAME:
            {
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemParam_Config.HookBAKServerInfo.DomainNameStr))
                {
                    tmp = sizeof(g_SystemParam_Config.HookBAKServerInfo.DomainNameStr) - 1;
                }

                for (i = 0; i <= tmp; i++)
                {
                    g_SystemParam_Config.HookBAKServerInfo.DomainNameStr[i] = tlv->Value.Array[i];
                }
                g_SystemParam_Config.HookBAKServerInfo.DomainNameStr[i] = 0;
                break;
            }
        }
        p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    }

    SystemParam_Save();

    g_ZSProtoMakeCache.Length = ZSProto_Make_ConfigSetResp(g_ZSProtoMakeCache.Buf, g_ZSProto_Seq++);
    BSP_USART_WriteBytes(COM_USART_MAINTAIN, g_ZSProtoMakeCache.Buf, g_ZSProtoMakeCache.Length);

    //OS_Timer_Start(g_UserTask_Id, USER_TASK_SYSTEMRESET_EVENT,2000);
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

