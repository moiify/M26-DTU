/**
 **************************************************************************************************
 * @file        gprs_cache.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_CACHE_H_
#define _GPRS_CACHE_H_
#include "stm32f0xx.h"
#include "system_info.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    gprs_cache_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_cache_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_cache_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_cache_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t SocketNum;
    uint16_t Len;
    uint8_t Buf[512];
}Server_receiveDataInfo_t;


typedef struct
{
	uint8_t Buf[300];
	uint16_t Len;
}receive_buf_t;

typedef struct
{
	uint8_t Buf[512];
	uint16_t Len;
	uint8_t Mux;
}socket_buf_t;

typedef struct
{
    Server_receiveDataInfo_t buf[1];
    uint8_t In;	
    uint8_t Out;
    uint8_t Count;
    uint8_t Size;
}Server_receiveDataInfo_Cache_t;  //服务器消息缓存   1K  

typedef struct 
{ 
  socket_buf_t Buf[2];
  uint8_t In;	
  uint8_t Out;
  uint16_t Count;
  uint16_t Size;  
}Socket_Cache_t;  //USART1发送 服务器  

typedef struct 
{ 
  receive_buf_t Buf[2];
  uint8_t In;	
  uint8_t Out;
  uint16_t Count;
  uint16_t Size;  
}Receive_Cache_t; //USART1接收缓存 AT返回

typedef struct 
{ 
  uint8_t *pData;
  uint16_t In;	
  uint16_t Out;
  uint16_t Count;
  uint16_t Size;  
}USART_Receive_t; //USART2接收缓存  
/**
 * @}
 */

/**
 * @defgroup      gprs_cache_Exported_Variables 
 * @{  
 */
extern Server_receiveDataInfo_Cache_t Server_receiveDataInfo;  //解析到的服务器端信息  √
extern Receive_Cache_t g_AT_ReceiveBuf ;  // AT指令返回 USART1   
extern Socket_Cache_t g_Machine_TransmitBuf; //组包好后的数据发送缓存     √
extern USART_Receive_t g_Machine_ReceiveBuf;  //单片机接收采控平台串口的缓存  待组包和解析  ×
  /**
 * @}
 */

/**
 * @defgroup      gprs_cache_Exported_Functions 
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
