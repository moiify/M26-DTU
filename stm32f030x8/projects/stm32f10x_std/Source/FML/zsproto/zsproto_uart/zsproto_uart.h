/**
 **************************************************************************************************
 * @file        zsproto_uart.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_UART_H_
#define _ZSPROTO_UART_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_uart_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_uart_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_uart_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_uart_Exported_Types 
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
    uint8_t  Addr;
    uint8_t  Cmd;
    uint8_t* CmdPayload;
}ZSProtoAPDU_Uart_t; // app protocol data unit
#pragma pack()

/**
 * zsproto standard cmd define 
 */
typedef enum
{
    /* standard cmd */
    /* custom cmd */
    ZSCmdUart_ConfigGetReq  = 128,
    ZSCmdUart_ConfigGetResp = 129,
    ZSCmdUart_ConfigSetReq  = 130,
    ZSCmdUart_ConfigSetResp = 131,
}ZSCmdUart_e;

/**
 * zsproto p2p standard cmdpayload define
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_uart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_uart_Exported_Functions 
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
