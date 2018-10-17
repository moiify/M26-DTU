/**
 **************************************************************************************************
 * @file        serial_log.c
 * @author
 * @version
 * @date        5/10/2017
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
#include "serial_log.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#if CLOG_APPENDER_SERIAL_ENABLE == 1
/**
 * @addtogroup    serial_log_Modules 
 * @{  
 */

/**
 * @defgroup      serial_log_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Macros_Defines 
 * @brief         
 * @{  
 */
#define BSP_USART_DEBUG BSP_USART1
/**
 * @}
 */

/**
 * @defgroup      serial_log_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Private_Variables 
 * @brief         
 * @{  
 */
static char s_SerialLogBuf[SERIAL_LOG_BUF_SIZE];
static LogLevel_t   s_LogLevel = DEFAULT_SERIAL_LOG_LEVEL;
/**
 * @}
 */

/**
 * @defgroup      serial_log_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static LogLevel_t   SerialLog_GetLogLevel(void);
static void         SerialLog_SetLogLevel(LogLevel_t logLevel);
static void         SerialLog_Write(LogLevel_t level,const char *fmt,...);
static void         SerialLog_WriteRAW(uint8_t *pBuf,uint16_t length);
static int          SerialLog_vprintf(LogLevel_t level,const char *fmt, va_list args);
/**
 * @}
 */

/**
 * @defgroup      serial_log_Functions 
 * @brief         
 * @{  
 */
void SerialLog_Init(SerialLog_t *log)
{
    log->Write = SerialLog_Write;
    log->WriteRAW = SerialLog_WriteRAW;
    log->SetLogLevel = SerialLog_SetLogLevel;
    log->GetLogLevel = SerialLog_GetLogLevel;
    log->vprintf = SerialLog_vprintf;
}

static void SerialLog_Write(LogLevel_t level,const char *fmt,...)
{
    va_list args;
    uint16_t length = 0;
    
    char *p = s_SerialLogBuf;

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
        
        length = p - s_SerialLogBuf;
        va_start(args,fmt);
        length += vsnprintf((char*)p,sizeof(s_SerialLogBuf)-length,fmt,args);
        va_end(args);
        /*add usart send function*/
        BSP_USART_WriteBytes(BSP_USART_DEBUG,(uint8_t*)s_SerialLogBuf,length);
    }
}

static int SerialLog_vprintf(LogLevel_t level,const char *fmt, va_list args)
{
    uint16_t length = 0;
    
    char *p = s_SerialLogBuf;

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

        length = p - s_SerialLogBuf;
        length += vsnprintf((char*)p,sizeof(s_SerialLogBuf)-strlen(s_SerialLogBuf),fmt,args);

        /*add send function*/
        BSP_USART_WriteBytes(BSP_USART_DEBUG,(uint8_t*)s_SerialLogBuf,length);
    }
    
    return length;
}

static void SerialLog_WriteRAW(uint8_t *pBuf,uint16_t length)
{
    BSP_USART_WriteBytes(BSP_USART_DEBUG,pBuf,length);
}

static LogLevel_t SerialLog_GetLogLevel(void)
{
    return s_LogLevel;
}

static void SerialLog_SetLogLevel(LogLevel_t logLevel)
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

