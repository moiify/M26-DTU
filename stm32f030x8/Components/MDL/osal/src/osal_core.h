/**
 **************************************************************************************************
 * @file        osal_core.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_CORE_H_
#define _OSAL_CORE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_core_Modules 
 * @{  
 */

/**
 * @defgroup      osal_core_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_core_Exported_Types 
 * @{  
 */
typedef struct osal_tcb
{
    uint32_t (*task)(uint8_t taskid,uint32_t events);
    uint8_t  osalTaskId;
    uint32_t osalTCBEvents;
}OSTCB_t;
/**
 * @}
 */

/**
 * @defgroup      osal_core_Exported_Variables 
 * @{  
 */
extern OSTCB_t   g_OSTCBTbl[];
extern uint8_t   g_OSTCBTblIndex;
/**
 * @}
 */

/**
 * @defgroup      osal_core_Exported_Functions 
 * @{  
 */
void OS_Events_Set(uint8_t taskid,osal_event_t event_flag);
void OS_Events_Clear(uint8_t taskid,osal_event_t event_flag);
void OS_Init(void);
void OS_Start(void);
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
