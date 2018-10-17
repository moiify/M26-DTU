/**
 **************************************************************************************************
 * @file        stopwatch.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stopwatch_Modules 
 * @{  
 */

/**
 * @defgroup      stopwatch_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Exported_Types 
 * @{  
 */
typedef struct
{
    void *Next;
    uint32_t TickCount;
    uint8_t State;
    uint8_t Rdy;
}Stopwatch;
/**
 * @}
 */

/**
 * @defgroup      stopwatch_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stopwatch_Exported_Functions 
 * @{  
 */
void Stopwatch_Service(void);
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
