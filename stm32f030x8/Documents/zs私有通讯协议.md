## ZS私有通讯协议

修订记录

| 日期       | 版本 | 说明 |
| ---------- | ---- | ---- |
| 2018-10-19 | V0.1 | 初稿 |

### 1、zsproto协议规范

协议格式如下
```
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t FCF;	// 帧控制域
        uint8_t  Seq;	// 序列号
        uint8_t  DeviceInfo[N]; // 设备信息域
        {
            uint8_t Cmd; 			// 命令类型
            uint8_t *CmdPayload; 	// 命令内容 
        }
    }
    uint8_t FCS; 	// 帧校验
    uint8_t Footer; // 帧尾
}ZSProto_t;
```
**帧头(Header)**

Header字段固定为0x5A

**数据包总长度(Length)**

Length字段表示数据包总长度，从Header字段到Footer字段


**帧控制域（FCF）**

帧控制域用于指示当前数据帧一些控制动作，具体定义如下：
```
bit12~bit15: ConnType; // 0-点对点，不限物理层；1-TCPIP；2-802.15.4；3-BLE；4-RS232/RS485；其他保留
bit11: Gateway; //网关标志；当该位置1，表示数据是一个经过网关转发的数据，在Seq字段后面会多一个uint32_t类型的网关id
bit8~bit10: 保留
bit6~bit7: FrameType; // 数据帧类型
bit4~bit5: 保留
bit3: Trans; // 当该位置1时，表示网关需要转发该数据
bit2: Pending; // 表示后续还有数据
bit1: Sec; // 数据加密
bit0: Ack; // 应答请求，
```
FCF各字段说明

ConnType:连接类型，对于不同连接方式的设备，通讯时需要的设备信息是不同的，该字段主要用于标识本数据包原始数据传输采用的连接方式，主要用于后续设备信息域字段的确定。其中
0：标识点对点传输，此种方式主要用于非组网通讯，不限物理层，不包含任何和组网通讯有关的数据字段。
1：TCPIP传输
2：802.15.4传输
3：BLE传输
4：RS232/RS485

Gateway:网关标志，当位置1时，标识该数据包含网关ID信息，同时在Seq字段后面多一个uint32_t 类型的网关ID。

FrameType:数据帧类型，用于指示当前数据帧的类型。其中
0：Data，普通数据包
1：AckResp，应答包，当FCF中Ack字段置1时，表示该帧数据需要接收方应答。此字段表示该帧数据是一个应答包。应答包有独立的格式，见后续章节说明。

Trans:透传标识，当该位置1时，网关需要转发该帧数据，当该位置0时，表示该帧数据是发送给网关内部的，不需要转发，例如发给网关的配置包，只需要网关内部处理，不需要做数据转发。

Pending:表示后续还有更多的数据要发送给接收设备，一般用于低功耗通讯，常规通讯可不用关心。

Sec:加密标志，当该位置1表示该帧数据的相关字段是加密的（此功能预留，暂不支持）

Ack:应答请求，当该位置1时，表示接收者需要回复一个应答包。

**序列号（Seq）**

序列号用于指示包唯一性，每次通讯自增

**设备信息域**

设备信息域包含设备型号，设备地址等信息，对于不同的通讯方式（见FCF中ConnType通讯类型），该字段的具体定义有所区别，具体见后续各通讯类型协议格式详细介绍。

**命令类型（Cmd）**

命令类型指示当前数据包类型

**命令内容（CmdPayload）**

命令内容包含当前命令对应的内容。

**校验（FCS）**

校验位，采用和校验方式，检验范围为`FCF`到`CmdPayload` 。

**帧尾（Footer）**

Footer固定为0x53。
### 2、zsproto协议说明

zsproto协议支持TCPIP类型设备直连服务器，同时也考虑了以后各种非TCPIP类型设备连接服务器的需求。两种类型传输方式如下：

- TCPIP Device -> Server
- End Device -> Gateway  -> Server

TCPIP类型设备可以直接连接服务器，而非TCPIP类型设备则无法直接连接服务器，因此该类设备需要网关进行协议转换。对于一些不关心网关信息的应用，网关工作在透传模式，直接转发收到的数据。而在一些特殊场合需要关心网关信息时，数据包FCF字段中Gateway位会置1，同时在Seq字段后面会有一个uint32_t类型的网关Id字段。

**点对点传输类型和其他传输类型的区别说明**

> 点对点传输类型只适合两个设备间互发数据，并不关心设备信息。它不包含任何和组网通讯相关的字段，无法识别多个设备，因此不适合组网传输。该种传输类型包含的字段最少，占用资源最少。

> 其他非点对点传输类型包含了设备相关信息，适用于组网通讯使用。因为包含了设备相关信息，占用资源相对较多。

> 常见组网通讯包括：一对多，多对一，多对对等，网络拓扑包括星型拓扑、树形拓扑、网状拓扑、总线型拓扑等。

> 点对点传输类型的设备不能包含其他传输类型的标准命令，其他传输类型的设备可以包含点对点传输类型的设备（此时只能点对点传输，不能组网传输）。

#### 2.1 点对点传输类型
标识点对点传输，此种方式主要用于非组网通讯，不限物理层，不包含任何和组网通讯有关的数据字段。
```
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t FCF;	// 帧控制域
        uint8_t  Seq;	// 序列号
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾         5a [ 00 00 ]  
}ZSProto_t;
```

#### 2.2 TCPIP传输类型设备通讯协议格式
```
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t  FCF;	// 帧控制域
        uint8_t   Seq;	// 序列号
        uint16_t  Model;	// 发送方设备型号
        uint32_t  DeviceId;	// 发送方设备ID
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
}ZSProto_t;
```

#### 2.3 802.15.4传输类型设备通讯协议格式
````
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t  FCF;	// 帧控制域
        uint8_t   Seq;	// 序列号
        uint16_t  Model;	// 发送方设备型号
        uint32_t  DeviceId;	// 发送方设备ID
        uint16_t  ShortAddr; // 发送方802.15.4短地址
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
}ZSProto_t;
````
#### 2.4 BLE传输类型设备通讯协议
```
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t  FCF;	// 帧控制域
        uint8_t   Seq;	// 序列号
        uint16_t  Model;	// 发送方设备型号
        uint32_t  DeviceId;	// 发送方设备Id
        uint8_t   MAC[6];	// BLE MAC地址
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
}ZSProto_t;
```
#### 2.5 RS485/RS232传输类型设备通讯协议
```
typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t FCF;	// 帧控制域
        uint8_t  Seq;	// 序列号
        uint16_t Model;	// 发送方设备型号
        uint32_t DeviceId;	// 发送方设备ID
        uint8_t  Addr;		// 从机设备地址
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
}ZSProto_t;
```

### 3、zsproto Model规范

zsproto协议中model 字段用于定义设备型号，其中

* 0x0000：当不需要对方关心该数据时，设备型号可设置为0x0000
* 0xFFFF：预留
* 其他：对应实际设备型号，见各设备定义。

### 4、zsproto Cmd规范

zsproto命令分标准命令和自定义命令。

> 对于同一种ConnType类型的设备，其标准命令对应的CmdPayload格式是固定的，不允许修改。不同ConnType类型的标准命令可以有区别。


> 自定义命令为不同设备私有命令，对字段格式按设备需求自定义，自定义命名必须从128开始。

> 标准命令为一个命令集，不同的设备可能只支持其中某些标准命令

```
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
    
    ZSCmd_StdAssociateReq,	    = 72,   // 关联请求
    ZSCmd_StdAssociateResp      = 73,   // 关联应答，传感->网关组网使用
    
    ZSCmd_StdRegisterReq        = 74,	// 注册请求，到服务器用
    ZSCmd_StdRegisterResp       = 75,	// 注册应答
}ZSCmd_e;
```
#### 4.1 所有ConnType均遵循的标准命令

##### 4.1.1 不支持命令应答
```
// 不支持的命令应答
Cmd：ZSCmd_NotSupport
CmdPayload:
typedef struct
{
    uint8_t Cmd; // 不支持的命令类型
}NotSupportPayload_t;
```

##### 4.1.2 获取支持的命令列表
```
请求：
Cmd:ZSCmd_CmdListGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_CmdListGetResp
CmdPayload:
typedef struct
{
    uint8_t CmdCount;
    uint8_t Cmd[CmdCount];
}CmdListGetReqPayload_t;
```

##### 4.1.3 设备心跳
```
通知：
Cmd:ZSCmd_BeatNotify
CmdPayload:
typedef struct
{
    uint16_t BeatInterval; // 心跳间隔，单位ms
}StdBeatPayload_t;
```

##### 4.1.4 版本号获取
```
请求：
Cmd:ZSCmd_StdFWVersionGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_StdFWVersionGetResp
CmdPayload:
typedef struct
{
    uint32_t UTCTicks;
}StdFWVersionGetRespPayload_t;
```

##### 4.1.5 时间设置
```
请求：
Cmd:ZSCmd_StdTimeSetReq
CmdPayload:
typedef struct
{
    uint32_t UTCTicks;
}StdTimeSetReqPayload_t;

应答：
Cmd:ZSCmd_StdTimeSetResp
CmdPayload:
typedef struct
{
    uint32_t UTCTicks;
}StdTimeSetRespPayload_t;
```

##### 4.1.6 时间获取
```
请求：
Cmd:ZSCmd_StdTimeGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_StdTimeGetResp
CmdPayload:
typedef struct
{
    uint32_t UTCTicks;
}StdTimeGetRespPayload_t;
```

##### 4.1.7 文件下载

ZS文件下载协议适用于各种文件下载，包括固件升级、参数等，ZS文件下载协议对文件名由严格要求，文件名必须满足以下格式：`FileType_FileVersion` 其中FileType用于确定该文件属于哪一类文件，FileVersion用于确定文件版本，在一些应用中当FileVersion相同时，是不进行文件下载的。

工作流程：

有新文件通知/主动获取文件名->获取文件信息->获取文件数据->通知结束

* 文件下载通知
```
通知：
Cmd:ZSCmd_StdDownloadNotify
CmdPayload:
typedef struct
{
    uint8_t Type; 	// 通知类型StdDownloadNotifyType_e，见下定义
    uint8_t Code;	// 通知码，见下定义
}StdDownloadNotifyPayload;
    
// 通知类型定义
typedef enum
{
	// server->device
    DownloadNotifyType_NewFileIncoming, // 有新文件，用于服务器主动推送新文件通知
    DownloadNotifyType_FileDamage,		// 文件损坏，在下载过程中，当正在下载的文件损坏时推送
    DownloadNotifyType_FileChange,		// 文件变化，在下载过程中，当正在下载的文件变化时推送
    
    // device->server
    DownloadNotifyType_DownloadFail,	// 下载失败，
    DownloadNotifyType_DownloadOK,		// 下载完成
}StdDownloadNotifyType_e;
```

* 文件名称获取
```
请求：
Cmd:ZSCmd_StdDownloadNameReq
CmdPayload:
typedef struct
{
    uint8_t FileTypeLength;
    uint8_t FileTypeString[FileTypeLength];
}StdDownloadNameReqPayload_t;

应答：
Cmd:ZSCmd_StdDownloadNameResp
CmdPayload:
typedef struct
{
    uint8_t FileNameLength;
    uint8_t FileNameString[FileNameLength];
}StdDownloadNameRespPayload_t;
```

* 文件信息获取
```
请求：
Cmd:ZSCmd_StdDownloadInfoReq
CmdPayload:
typedef struct
{
    uint8_t FileNameLength;
    uint8_t FileNameString[FileNameLength];
}StdDownloadInfoReqPayload_t;

应答：
Cmd:ZSCmd_StdDownloadInfoResp
CmdPayload:
typedef struct
{
    uint32_t Size;			// 文件大小，单位Byte
    uint32_t FileId; 		// 文件Id。由下载服务器生成，和文件名对应，供后续使用
    uint8_t FileNameLength; // 文件名长度
    uint8_t FileNameString[FileNameLength]; // 文件名
}StdDownloadInfoRespPayload_t;
```

* 文件数据获取
```
请求：
Cmd:ZSCmd_StdDownloadDataReq
CmdPayload:
typedef struct
{
    uint32_t FileId;	// 下载文件Id
    uint32_t Offset;	// 请求的文件数据偏移
    uint16_t Size;		// 请求的文件数据大小
}StdDownloadDataReqPayload_t;

应答：
Cmd:ZSCmd_StdDownloadDataResp
CmdPayload:
typedef struct
{
    uint32_t FileId;	// 下载文件Id
    uint32_t Offset;	// 返回的文件数据偏移
    uint32_t Size;		// 返回的文件实际长度大小
    uint8_t Data[Size];		// 数据
}StdDownloadDataRespPayload_t;
```

#### 4.2 点对点传输类型

点对点传输类型标准命令定义。点对点传输和其他传输类型最大的区别在于，点对点传输类型不支持组网通讯，而其他类型支持组网通讯。

一般用于透传设备使用，同时也可用于其他设备获取传输类型和设备类型使用。

> 点对点传输类型不能用于组网通讯，仅仅适用于两个设备间通讯。


##### 4.2.1 获取设备传输类型和设备型号
```
请求：
Cmd:ZSCmd_StdConnModelGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_StdConnModelGetResp
CmdPayload:
typedef struct
{
    uint8_t ConnType;
    uint16_t Model;
}StdConnModelGetRespPayload_t
```

#### 4.3 TCPIP传输类型

TCPIP传输类型标准命令定义。

##### 4.3.1 设备扫描
```
请求：
Cmd:ZSCmd_StdScanReq
CmdPayload:
typedef struct
{
    uint16_t TargetModel; 	
    uint32_t TargetDeviceId;
}StdScanReqPayload_t;

应答：
Cmd:ZSCmd_StdScanResp
CmdPayload:
typedef struct
{
    uint16_t Model; 	
    uint32_t DeviceId;
}StdScanRespPayload_t;

```

##### 4.3.2 获取设备配置
```
请求：
Cmd:ZSCmd_StdConfigGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_StdConfigGetResp
CmdPayload:
typedef struct
{
    NULL; // 配置获取请求Payload为空 
}StdConfigGetRespPayload_t;
```

##### 4.3.3 设置设备配置
```
请求：
Cmd:ZSCmd_StdConfigSetReq
CmdPayload:
typedef struct
{
    uint8_t     TLVCount;
    TLVUnit_t   TLV[TLVCount];
}StdConfigSetReqPayload_t;
    
应答：
Cmd:ZSCmd_StdConfigSetResp
CmdPayload:
typedef struct
{
    uint8_t     Result;
    uint8_t     TLVCount;
    TLCUnit_t   TLV[TLVCount];
}StdConfigSetRespPayload_t;
```