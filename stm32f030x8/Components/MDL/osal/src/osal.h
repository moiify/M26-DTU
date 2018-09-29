/**
 **************************************************************************************************
 * @file        osal.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_H_
#define _OSAL_H_

#include "osal.h"

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_Modules 
 * @{  
 */

/**
 * @defgroup      osal_Exported_Macros 
 * @{  
 */
#ifndef NULL
    #define NULL    0
#endif

/*********************************************** 
* Global Events 
************************************************/ 
#define OSAL_MSG_EVENT      0x8000
#define OSAL_TIMEOUT_EVENT  0x4000
/************************************************
* Error Code
************************************************/
#define OSAL_ERR_NONE               0x00

typedef unsigned int osal_event_t;
/**
 * @}
 */

/**
 * @defgroup      osal_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_Exported_Variables 
 * @{  
 */
#include "osal_cpu.h"
#include "osal_cfg.h"
#include "osal_core.h"
#include "osal_msg.h"
#include "osal_clock.h"
#include "osal_task.h"
#include "osal_timer.h"
/**
 * @}
 */

/**
 * @defgroup      osal_Exported_Functions 
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
