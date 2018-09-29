/**
 **************************************************************************************************
 * @file        osal_msg.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_MSG_H_
#define _OSAL_MSG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_msg_Modules 
 * @{  
 */

/**
 * @defgroup      osal_msg_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t Event;
}osalMsgHdr_t;

typedef struct
{
    void **Msg;
    uint16_t In;
    uint16_t Out;
    uint16_t Size;
    uint16_t Count;
}OSMsg_t;
/**
 * @}
 */

/**
 * @defgroup      osal_msg_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Exported_Functions 
 * @{  
 */
void    OS_Msg_Init(void);
uint8_t OS_Msg_Create(uint8_t taskid,void *start,uint16_t size);

uint8_t OS_Msg_Send(uint8_t taskid,void *pMsg);
uint8_t *OS_Msg_Receive(uint8_t taskid);
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
