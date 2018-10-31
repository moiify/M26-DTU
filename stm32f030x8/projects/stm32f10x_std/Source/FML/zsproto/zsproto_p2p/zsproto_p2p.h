/**
 **************************************************************************************************
 * @file        zsproto_p2p.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_P2P_H_
#define _ZSPROTO_P2P_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_p2p_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_p2p_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_p2p_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_p2p_Exported_Types 
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
        uint16_t Value;
    }FCF;
    uint8_t  Seq;
    uint8_t  Cmd;
    uint8_t* CmdPayload;
}ZSProtoAPDU_P2P_t; // app protocol data unit
#pragma pack()

/**
 * zsproto cmd define 
 */
typedef enum
{
    /* standard cmd */
    ZSCmdP2P_StdConnModelGetReq     = 50,
    ZSCmdP2P_StdConnModelGetResp    = 51,
    /* custom cmd */
}ZSCmdP2P_e;

/**
 * zsproto p2p cmdpayload define
 */

/* ZSCmdP2P_StdConnModelGetReq√¸¡ÓŒﬁCmdPayload◊÷∂Œ */

/* ZSCmdP2P_StdConnModelGetResp√¸¡ÓCmdPayload∂®“Â */
typedef struct
{
    uint8_t ConnType;
    uint16_t Model;
}P2PStdConnModelGetRespPayload_t;

/**
 * @}
 */

/**
 * @defgroup      zsproto_p2p_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_p2p_Exported_Functions 
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
