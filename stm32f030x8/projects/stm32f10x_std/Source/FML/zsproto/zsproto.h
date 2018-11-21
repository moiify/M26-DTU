/**
 **************************************************************************************************
 * @file        zsproto.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_H_
#define _ZSPROTO_H_
#include "stm32f0xx.h"
#include "system_info.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Constants
 * @{  
 */
/************************* system define **************/
#define ZSPROTO_AHR_SIGN                'Z' // 0x5A, zsproto header
#define ZSPROTO_AFR_SIGN                'S' // 0x53, zsproto footer

#define ZSPROTO_BUFFER_SIZE_MAX         255

#define ZSPROTO_AHR_SIGN_OFFSET         0   
#define ZSPROTO_AHR_LENGTH_OFFSET       1    
#define ZSPROTO_APD_DATA_OFFSET         3

#define ZSPROTO_CONNTYPE_P2P            0
#define ZSPROTO_CONNTYPE_TCPIP          1
#define ZSPROTO_CONNTYPE_802            2
#define ZSPROTO_CONNTYPE_BLE            3
#define ZSPROTO_CONNTYPE_UART           4

#define ZSPROTO_FRAMETYPE_DATA          0
#define ZSPROTO_FRAMETYPE_ACK           1

#define ZSPROTO_MODEL_BROADCAST         0xFFFF
#define ZSPROTO_MODEL_NOTCASE           0x0000

#define ZSPROTO_ADDR_BROADCAST          0xFFFF
#define ZSPROTO_ADDR_NOTCARE            0x0000
/************************** user define *****************/
#define ZSPROTO_FLOWANALYSIS_ENABLE     1
#define ZSPROTO_FLOWCHANNEL_COUNT       1
#define ZSPROTO_FLOWCHANNEL_MAINTAIN    0

#define ZSPROTO_PACKETANALYSIS_ENABLE   0
#define ZSPROTO_PACKETCHANNEL_COUNT     1
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Types 
 * @{  
 */
#pragma pack(1)
typedef struct
{
    uint8_t Sign;
    uint16_t Length;
}ZSProtoAHR_t;

typedef struct
{
    uint8_t Sign;
}ZSProtoAFR_t;

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
}ZSProtoTLV_t;

typedef struct
{
    uint8_t Buf[ZSPROTO_BUFFER_SIZE_MAX];
    uint16_t Length;
}ZSProtoPacket_t;

typedef struct
{
    ZSProtoPacket_t *pData;
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}ZSProtoPacketQueue_t;


/**
 * zsproto standard cmd define 
 */
typedef enum
{
    /* 所有ConnType均遵循的标准命令 */
	ZSCmd_NotSupport            = 0,    // 不支持的命令应答
	
	ZSCmd_StdGetCmdListReq      = 1,    // 获取支持的命令列表请求
	ZSCmd_StdGetCmdListResp     = 2,    // 获取支持的命令列表应答
	
	
	ZSCmd_StdBeatNotify         = 10,   // 心跳
    
    ZSCmd_StdFWVersionGetReq    = 11,   // 获取版本号请求
    ZSCmd_StdFWVersionGetResp   = 12,   // 获取版本号应答
    
    ZSCmd_StdTimeSetReq         = 13,   // 时间设置请求
    ZSCmd_StdTimeSetResp        = 14,   // 时间设置应答
    ZSCmd_StdTimeGetReq         = 15,   // 时间获取请求
    ZSCmd_StdTimeGetResp        = 16,   // 时间获取应答
    
    ZSCmd_StdDownloadNotify     = 20,	// 下载通知
    ZSCmd_StdDownloadNameReq    = 21,   // 文件名请求
    ZSCmd_StdDownloadNameResp   = 22,   // 文件名应答
    ZSCmd_StdDownloadInfoReq    = 23,	// 文件信息请求
    ZSCmd_StdDownloadInfoResp   = 24,	// 文件信息应答
    ZSCmd_StdDownloadDataReq    = 25,	// 文件数据请求
    ZSCmd_StdDownloadDataResp   = 26,	// 文件数据应答
    
    /* 按ConnType类型遵循的标准命令 */
    ZSCmd_StdConnModelGetReq    = 50,    // 获取设备的传输类型和设备型号请求
	ZSCmd_StdConnModelGetResp   = 51,    // 获取设备的传输类型和设备型号应答
	
    ZSCmd_StdConfigGetReq       = 60,	// 配置获取请求
    ZSCmd_StdConfigGetResp      = 61,	// 配置获取应答
    
    ZSCmd_StdConfigSetReq       = 62,	// 配置设置请求
    ZSCmd_StdConfigSetResp      = 63,	// 配置设备应答
    
    ZSCmd_StdStatusReq          = 64,	// 状态获取请求
    ZSCmd_StdStatusResp         = 65,	// 状态获取应答
    
    ZSCmd_StdScanReq            = 70,	// 扫描请求
    ZSCmd_StdScanResp           = 71,	// 扫描应答
    
    ZSCmd_StdAssociateReq	    = 72,   // 关联请求
    ZSCmd_StdAssociateResp      = 73,   // 关联应答，传感->网关组网使用
    
    ZSCmd_StdRegisterReq        = 74,	// 注册请求，到服务器用
    ZSCmd_StdRegisterResp       = 75,	// 注册应答
    
    ZSCmd_ConfigGetReq          = 128,
    ZSCmd_ConfigGetResp         = 129,
    ZSCmd_ConfigSetReq          = 130,
    ZSCmd_ConfigSetResp         = 131,
    
    ZSProto_SocketPcakSend      = 132, //网络数据包发送
    ZSProto_SocketPcakReceive   = 133, //网络数据包接收
    
    
    ZSProto_RssiNotify          = 134, 
    ZSProto_LinkStateNotify     = 135,
    
}ZSCmd_e;

/**
 * zsproto standard cmdpayload define 
 */
typedef struct
{
    uint32_t UTCTicks;
}StdTimeSetReqPayload_t;

typedef struct
{
    uint8_t Result;
}StdTimeSetRespPayload_t;
#pragma pack()

#include "zsproto_p2p.h"
#include "zsproto_tcpip.h"
#include "zsproto_uart.h"
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Variables 
 * @{  
 */
extern uint32_t g_ZSProto_Seq;
extern ZSProtoPacket_t g_ZSProtoMakeCache;
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Functions 
 * @{  
 */
void ZSProto_FlowAnalysis(uint8_t channel,uint8_t *pBuf,uint8_t length);
void ZSProto_FlowSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length));
uint16_t ZSProto_FlowGetCacheIdleLength(uint8_t channel);
uint8_t ZSProto_IsPackage(uint8_t channel,uint8_t * pBuf,uint16_t length);
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
