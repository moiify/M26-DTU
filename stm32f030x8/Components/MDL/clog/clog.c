/**
 **************************************************************************************************
 * @file        clog.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "stdio.h"
#include "stdarg.h"
#include "osal.h"
#include "clog.h"
#include "serial_log.h"
#include "rtt_log.h"
#include "flash_log.h"
#include "SEGGER_RTT.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    clog_Modules 
 * @{  
 */

/**
 * @defgroup      clog_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Private_Variables 
 * @brief         
 * @{  
 */
#if CLOG_APPENDER_SERIAL_ENABLE == 1
SerialLog_t s_SerialLog;
#endif

#if CLOG_APPENDER_RTT_ENABLE == 1
RTTLog_t s_RTTLog;
#endif

#if CLOG_APPENDER_FLASH_ENABLE == 1
FlashLog_t s_FlashLog;
#endif
/**
 * @}
 */

/**
 * @defgroup      clog_Public_Variables 
 * @brief         
 * @{  
 */
const char* g_LogLevelText[]={" ","fatal,","error,","warn,","info,","debug,","detail,"};
/**
 * @}
 */

/**
 * @defgroup      clog_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Functions 
 * @brief         
 * @{  
 */
uint8_t CLog_GetCurrentTaskID(void)
{
    return 0;
}

void CLog_GetTime(uint32_t *sec,uint16_t *ms)
{
    *sec = OS_Clock_GetSeconds();
    *ms = OS_Clock_GetSystemClock()%1000;
}

void CLog_Init(CLogAppender_t appender)
{
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            SerialLog_Init(&s_SerialLog);
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            RTTLog_Init(&s_RTTLog);
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            FlashLog_Init(&s_FlashLog);
            break;
        }
        #endif

        default:
        {
            break;
        }
    }
}

void CLog_Fatal(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            if (LogLevel_Fatal <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Fatal,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            
            if (LogLevel_Fatal <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Fatal,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Fatal <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_FlashLog.vprintf(LogLevel_Fatal,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

void CLog_Error(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            if (LogLevel_Error <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Error,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            if (LogLevel_Error <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Error,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Error <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_FlashLog.vprintf(LogLevel_Error,fmt,args);
                va_end(args);
            }
            
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

void CLog_Warn(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            if (LogLevel_Warn <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Warn,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            if (LogLevel_Warn <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Warn,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Warn <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_FlashLog.vprintf(LogLevel_Warn,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

void CLog_Info(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            if (LogLevel_Info <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Info,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            if (LogLevel_Info <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Info,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Info <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_FlashLog.vprintf(LogLevel_Info,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

void CLog_Debug(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            
            if (LogLevel_Debug <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Debug,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            if (LogLevel_Debug <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Debug,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Debug <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_FlashLog.vprintf(LogLevel_Debug, fmt, args);
                va_end(args);
            }
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

void CLog_Trace(CLogAppender_t appender,const char *fmt,...)
{
    va_list args;
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            if (LogLevel_Trace <= s_SerialLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_SerialLog.vprintf(LogLevel_Trace,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            
            if (LogLevel_Trace <= s_RTTLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Trace,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            if (LogLevel_Trace <= s_FlashLog.GetLogLevel())
            {
                va_start(args,fmt);
                s_RTTLog.vprintf(LogLevel_Trace,fmt,args);
                va_end(args);
            }
            break;
        }
        #endif
        
        default:
        {
            break;
        }
    }
}

LogLevel_t CLog_GetLogLevel(CLogAppender_t appender)
{
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            return s_SerialLog.GetLogLevel();
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            return s_RTTLog.GetLogLevel();
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            return s_FlashLog.GetLogLevel();
            break;
        }
        #endif

        default:
        {
            return LogLevel_None;
        }
    }
}

void CLog_SetLogLevel(CLogAppender_t appender,LogLevel_t level)
{
    switch (appender)
    {
        #if CLOG_APPENDER_SERIAL_ENABLE == 1
        case CLogAppender_Serial:
        {
            s_SerialLog.SetLogLevel(level);
            break;
        }
        #endif

        #if CLOG_APPENDER_RTT_ENABLE == 1
        case CLogAppender_RTT:
        {
            s_RTTLog.SetLogLevel(level);
            break;
        }
        #endif

        #if CLOG_APPENDER_FLASH_ENABLE == 1
        case CLogAppender_Flash:
        {
            s_FlashLog.SetLogLevel(level);
            break;
        }
        #endif

        default:
        {
            break;
        }
    }
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

