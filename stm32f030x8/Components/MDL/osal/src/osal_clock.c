/**
 **************************************************************************************************
 * @file        osal_clock.c
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
#include "osal_clock.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    osal_clock_Modules 
 * @{  
 */

/**
 * @defgroup      osal_clock_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_clock_Macros_Defines 
 * @brief         
 * @{  
 */
#define BEGYEAR     2000
#define DAY         86400ul

#define YEAR_LENGTH(yr) ((uint16_t)(IsLeapYear(yr) ? 366 : 365))
/**
 * @}
 */

/**
 * @defgroup      osal_clock_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       osal_clock_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_clock_Private_Variables 
 * @brief         
 * @{  
 */
static uint32_t s_osalClock_Seconds = 0;
static uint16_t s_osalClock_MilliSeconds = 0;
static uint32_t s_osalClock_ElapsedMs = 0;
/**
 * @}
 */

/**
 * @defgroup      osal_clock_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_clock_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_clock_Functions 
 * @brief         
 * @{  
 */
void OS_Clock_Update(uint32_t elapsedMSec)
{
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    s_osalClock_MilliSeconds += elapsedMSec;
    s_osalClock_ElapsedMs += elapsedMSec;
    if (s_osalClock_MilliSeconds >= 1000)
    {
        s_osalClock_Seconds += s_osalClock_MilliSeconds/1000;
        s_osalClock_MilliSeconds = s_osalClock_MilliSeconds%1000;
    }
    OSAL_EXIT_CRITICAL(cpu_sr);
}

void OS_Clock_SetSeconds(uint32_t newTime)
{
    OSAL_CPU_SR cpu_sr;
    OSAL_ENTER_CRITICAL(cpu_sr);
    s_osalClock_Seconds = newTime;
    OSAL_EXIT_CRITICAL(cpu_sr);
}

uint32_t OS_Clock_GetSeconds(void)
{
    uint32_t ticks = 0;
    do
    {
        ticks = s_osalClock_Seconds;
    }while(ticks != s_osalClock_Seconds);

    return ticks;
}


uint32_t OS_Clock_GetSystemClock(void)
{
    uint32_t ticks = 0;
    do
    {
        ticks = s_osalClock_ElapsedMs;
    }while(ticks != s_osalClock_ElapsedMs);

    return ticks;
}

static uint8_t month_length( uint8_t lpyr, uint8_t mon )
{
    uint8_t days = 30;

    if (mon == 2) 
    {
        days = (28 + lpyr);
    }
    else 		
    {
        if (mon > 7) 
        {
            mon--;
        }

        if (mon & 1)
        {
            days = 31;
        }
    }
    return (days); 
}

void OS_Clock_ConvertToDateTime(uint32_t timestamp,OSTime_t *dt)
{
    // calculate the time less than a day
    uint32_t day = timestamp % DAY;
    dt->Seconds = day % 60UL;
    dt->Minutes = (day % 3600UL) / 60UL;
    dt->Hour = day / 3600UL;

    //fill in the calendar
    uint16_t numDays = timestamp / DAY + 1;
    dt->Year = BEGYEAR;
    while (numDays >= YEAR_LENGTH(dt->Year))
    {
        numDays -= YEAR_LENGTH(dt->Year);
        dt->Year++;
    }

    dt->Month = 1;
    while ( numDays > month_length( IsLeapYear( dt->Year ), dt->Month ) )
    {
        numDays -= month_length( IsLeapYear( dt->Year ), dt->Month );
        dt->Month++;
    }

    dt->Day = numDays;
}

uint32_t OS_Clock_ConvertToSecs(OSTime_t *dt)
{
    uint32_t seconds;

    /* Seconds for the partial day */
    seconds = (((dt->Hour * 60UL) + dt->Minutes) * 60UL) + dt->Seconds;

    /* Account for previous complete days */
    {
        /* Start with complete days in current month */
        uint16_t days = dt->Day - 1;

        /* Next, complete months in current year */
        {
            int8_t month = dt->Month;
            while (--month >= 1)
            {
                days += month_length(IsLeapYear(dt->Year), month);
            }
        }

        /* Next, complete years before current year */
        {
            uint16_t year = dt->Year;
            while (--year >= BEGYEAR)
            {
                days += YEAR_LENGTH(year);
            }
        }

        /* Add total seconds before partial day */
        seconds += (days * DAY);
    }

    return (seconds); 
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

