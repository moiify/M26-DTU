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
            uint8_t FrameType:2;
            uint8_t reserve:2;
        }bitfield;
        uint8_t Value;
    }FCF;
    uint8_t  Seq;
    uint16_t Model;
    uint32_t DeviceId;
    uint8_t  Addr;
    uint8_t  Cmd;
    uint8_t* CmdPayload;
}ZSProtoAPD_Uart_t;

#pragma pack()
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
