/**
 **************************************************************************************************
 * @file        zsproto_tcpip.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_TCPIP_H_
#define _ZSPROTO_TCPIP_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_tcpip_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Types 
 * @{  
 */

#pragma pack(1)
typedef struct
{
    union
    {
        struct
        {
            uint8_t AckReq:1;
            uint8_t Sec:1;
            uint8_t Pending:1;
            uint8_t Trans:1;
            uint8_t reserve1:2;
            uint8_t FrameType:2;
            uint8_t reserve2:3;
            uint8_t Gateway:1;
            uint8_t ConnType:4;
        }bitfield;
        uint8_t Value;
    }FCF;
    uint8_t  Seq;
    uint16_t Model;
    uint32_t DeviceId;
    uint8_t  Cmd;
    uint8_t* CmdPayload;
}ZSProtoAPDU_TCPIP_t; // app protocol data unit
#pragma pack()

/**
 * zsproto cmd define 
 */
typedef enum
{
    /* standard cmd */
    ZSCmdTCPIP_StdConfigGetReq  = ZSCmd_StdConfigGetReq,
    ZSCmdTCPIP_StdConfigGetResp = ZSCmd_StdConfigGetResp,

    ZSCmdTCPIP_StdConfigSetReq  = ZSCmd_StdConfigSetReq,
    ZSCmdTCPIP_StdConfigSetResp = ZSCmd_StdConfigSetResp,

    ZSCmdTCPIP_StdScanReq   = ZSCmd_StdScanReq,
    ZSCmdTCPIP_StdScanResp  = ZSCmd_StdScanResp,
        
    /* custom cmd */
    ZSCmdTCPIP_ConfigGetReq  = 128,
    ZSCmdTCPIP_ConfigGetResp = 129,
    ZSCmdTCPIP_ConfigSetReq  = 130,
    ZSCmdTCPIP_ConfigSetResp = 131,
}ZSCmdTCPIP_e;

/**
 * zsproto p2p cmdpayload define
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Functions 
 * @{  
 */

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
