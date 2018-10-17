/**
 **************************************************************************************************
 * @file        rtt_log.c
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
#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "clog.h"
#include "osal_clock.h"
#include "rtt_log.h"
#include "segger_rtt.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#if CLOG_APPENDER_RTT_ENABLE == 1
/**
 * @addtogroup    rtt_log_Modules 
 * @{  
 */

/**
 * @defgroup      rtt_log_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       rtt_log_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       rtt_log_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Private_Variables 
 * @brief         
 * @{  
 */
static char s_RTTLogBuf[RTT_LOG_BUF_SIZE];

static LogLevel_t   s_LogLevel = DEFAULT_RTT_LOG_LEVEL;
/**
 * @}
 */

/**
 * @defgroup      rtt_log_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void         RTTLog_Write(LogLevel_t level,const char *fmt,...);
static void         RTTLog_WriteRAW(uint8_t *pBuf,uint16_t length);
static LogLevel_t   RTTLog_GetLogLevel(void);
static void         RTTLog_SetLogLevel(LogLevel_t logLevel);
static int          RTTLog_vprintf(LogLevel_t level,const char *fmt, va_list args);
/**
 * @}
 */

/**
 * @defgroup      rtt_log_Functions 
 * @brief         
 * @{  
 */
void RTTLog_Init(RTTLog_t *log)
{
    log->Write = RTTLog_Write;
    log->WriteRAW = RTTLog_WriteRAW;
    log->SetLogLevel = RTTLog_SetLogLevel;
    log->GetLogLevel = RTTLog_GetLogLevel;
    log->vprintf = RTTLog_vprintf;
}

static void RTTLog_Write(LogLevel_t level,const char *fmt,...)
{
    va_list args;
    uint16_t length = 0;
    
    char *p = s_RTTLogBuf;

    if ((uint8_t)level <= (uint8_t)s_LogLevel) 
    {
        uint32_t sec;
        uint16_t ms;
        OSTime_t log_time;
        CLog_GetTime(&sec,&ms);
        OS_Clock_ConvertToDateTime(sec,&log_time);
        
        sprintf(p,"%02d:%02d:%02d(%03d),",log_time.Hour,log_time.Minutes,log_time.Seconds,ms);
        p += strlen(p);
        
        sprintf(p,"%02d,",CLog_GetCurrentTaskID());
        p += strlen(p);
        
        sprintf(p,g_LogLevelText[(uint8_t)level]);
        p += strlen(p);
        
        length = p - s_RTTLogBuf;
        va_start(args,fmt);
        length += vsnprintf((char*)p,sizeof(s_RTTLogBuf)-length,fmt,args);
        va_end(args);
        /*add send function*/
        SEGGER_RTT_Write(0,(uint8_t*)s_RTTLogBuf,length);
    }
}

static int RTTLog_vprintf(LogLevel_t level,const char *fmt, va_list args)
{
    uint16_t length = 0;
    
    char *p = s_RTTLogBuf;

    if ((uint8_t)level <= (uint8_t)s_LogLevel) 
    {
        uint32_t sec;
        uint16_t ms;
        OSTime_t log_time;
        CLog_GetTime(&sec,&ms);
        OS_Clock_ConvertToDateTime(sec,&log_time);
        
        sprintf(p,"%02d:%02d:%02d(%03d),",log_time.Hour,log_time.Minutes,log_time.Seconds,ms);
        p += strlen(p);
        
        sprintf(p,"%02d,",CLog_GetCurrentTaskID());
        p += strlen(p);
        
        sprintf(p,g_LogLevelText[(uint8_t)level]);
        p += strlen(p);

        length = p - s_RTTLogBuf;
        length += vsnprintf((char*)p,sizeof(s_RTTLogBuf)-strlen(s_RTTLogBuf),fmt,args);

        /*add send function*/
        SEGGER_RTT_Write(0,(uint8_t*)s_RTTLogBuf,length);
    }
    
    return length;
}

static void RTTLog_WriteRAW(uint8_t *pBuf,uint16_t length)
{
    SEGGER_RTT_Write(0,pBuf,length);
}

static LogLevel_t RTTLog_GetLogLevel(void)
{
    return s_LogLevel;
}

static void RTTLog_SetLogLevel(LogLevel_t logLevel)
{
    s_LogLevel = logLevel;
}
/**
 * @}
 */

/**
 * @}
 */
#endif
/**
 * @}
 */

