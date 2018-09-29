/**
 **************************************************************************************************
 * @file        osal_msg.c
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "osal.h"
#include "osal_cfg.h"
#include "osal_cpu.h"
#include "osal_core.h"
#include "osal_task.h"
#include "osal_msg.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    osal_msg_Modules 
 * @{  
 */

/**
 * @defgroup      osal_msg_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_msg_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_msg_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Private_Variables 
 * @brief         
 * @{  
 */
static OSMsg_t s_osalMsgList[OSAL_TASK_COUNT];
/**
 * @}
 */

/**
 * @defgroup      osal_msg_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_msg_Functions 
 * @brief         
 * @{  
 */
void OS_Msg_Init(void)
{

}

uint8_t OS_Msg_Create(uint8_t taskid,void *start,uint16_t size)
{
    s_osalMsgList[taskid].Msg = start; 
    s_osalMsgList[taskid].In = 0;
    s_osalMsgList[taskid].Out = 0;
    s_osalMsgList[taskid].Size = size;
    s_osalMsgList[taskid].Count = 0;

    return OSAL_ERR_NONE;
}

//void *osalMsgAlloc(uint8_t taskid)
//{
//    void *p=NULL;
//    OSAL_CPU_SR cpu_sr;
//    OSAL_ENTER_CRITICAL(cpu_sr);
//    if (s_osalMsgList[taskid].Count < s_osalMsgList[taskid].Size)
//    {
//        p = &s_osalMsgList[taskid].Msg[s_osalMsgList[taskid].In];
//        s_osalMsgList[taskid].In++;
//        s_osalMsgList[taskid].In %= s_osalMsgList[taskid].Size;
//        s_osalMsgList[taskid].Count++;
//    }
//    OSAL_EXIT_CRITICAL(cpu_sr);
//    return p;
//}

uint8_t OS_Msg_Send(uint8_t taskid,void *pMsg)
{
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    if (s_osalMsgList[taskid].Count < s_osalMsgList[taskid].Size)
    {
        s_osalMsgList[taskid].Msg[s_osalMsgList[taskid].In] = pMsg; 
        s_osalMsgList[taskid].In++;
        s_osalMsgList[taskid].In %= s_osalMsgList[taskid].Size;
        s_osalMsgList[taskid].Count++;
    }
    OSAL_EXIT_CRITICAL(cpu_sr);
    OS_Events_Set(taskid,OSAL_MSG_EVENT);
    
    return OSAL_ERR_NONE;
}

uint8_t *OS_Msg_Receive(uint8_t taskid)
{
    void *p;
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    if (s_osalMsgList[taskid].Count == 0)
    {
        OSAL_EXIT_CRITICAL(cpu_sr);
        return NULL;
    }

    p = s_osalMsgList[taskid].Msg[s_osalMsgList[taskid].Out++];
    s_osalMsgList[taskid].Out %= s_osalMsgList[taskid].Size;
    s_osalMsgList[taskid].Count--;
    OSAL_EXIT_CRITICAL(cpu_sr);
    return p;
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

