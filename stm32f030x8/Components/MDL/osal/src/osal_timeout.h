/**
 **************************************************************************************************
 * @file        osal_timeout.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_TIMEOUT_H_
#define _OSAL_TIMEOUT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_timeout_Modules 
 * @{  
 */

/**
 * @defgroup      osal_timeout_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Exported_Types 
 * @{  
 */
typedef struct osal_timeout
{
    struct osal_timeout *Next;
    uint32_t Count;
    uint32_t ReloadValue;
    void (*callback)(void);
}OSTimeout_t;
/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_timeout_Exported_Functions 
 * @{  
 */
int8_t   OS_Timeout_Init(OSTimeout_t *timeout,void (*callback)(void));
void     OS_Timeout_Start(OSTimeout_t *timeout);
void     OS_Timeout_Stop(OSTimeout_t *timeout);
void     OS_Timeout_SetValue(OSTimeout_t *timeout,uint32_t value);
uint32_t OS_Timeout_GetTimeout(OSTimeout_t *timeout);
uint32_t OS_Timeout_GetNextTimeout(void);
void     OS_Timeout_Update(void);
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
