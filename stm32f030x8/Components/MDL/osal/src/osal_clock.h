/**
 **************************************************************************************************
 * @file        osal_clock.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_CLOCK_H_
#define _OSAL_CLOCK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_clock_Modules 
 * @{  
 */

/**
 * @defgroup      osal_clock_Exported_Macros 
 * @{  
 */
#define	IsLeapYear(yr)	(!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
/**
 * @}
 */

/**
 * @defgroup      osal_clock_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_clock_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hour;
    uint8_t Day;
    uint8_t Month;
    uint16_t Year;
}OSTime_t;
/**
 * @}
 */

/**
 * @defgroup      osal_clock_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_clock_Exported_Functions 
 * @{  
 */
void     OS_Clock_Update(uint32_t elapsedMSec);
void     OS_Clock_SetSeconds(uint32_t newTime);
uint32_t OS_Clock_GetSeconds(void);
uint32_t OS_Clock_GetSystemClock(void);
void     OS_Clock_ConvertToDateTime(uint32_t timestamp,OSTime_t *dt);
uint32_t OS_Clock_ConvertToSecs(OSTime_t *dt);
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
