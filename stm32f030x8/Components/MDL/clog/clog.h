/**
 **************************************************************************************************
 * @file        clog.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CLOG_H_
#define _CLOG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "stdarg.h"
/**
 * @addtogroup    clog_Modules 
 * @{  
 */

/**
 * @defgroup      clog_Exported_Macros 
 * @{  
 */

/************************************************
               system define 
 ************************************************/
#define CLOG_APPENDER_NONE      0
#define CLOG_APPENDER_SERIAL    1
#define CLOG_APPENDER_FLASH     2
#define CLOG_APPENDER_RTT       3

/************************************************
               GPRS config
 ************************************************/
#define CLOG_APPENDER_SERIAL_ENABLE      0
#define CLOG_APPENDER_FLASH_ENABLE       0
#define CLOG_APPENDER_RTT_ENABLE         1
     
#define CLOG_DEFAULT_APPENDER   CLOG_APPENDER_RTT

/************************************************
               system define 
 ************************************************/
#if (CLOG_DEFAULT_APPENDER == CLOG_APPENDER_SERIAL) && (CLOG_APPENDER_SERIAL_ENABLE == 1)
#define RAW(pBuf,length)    s_SerialLog.WriteRAW(pBuf,length);
#define FATAL(args...)      s_SerialLog.Write(LogLevel_Fatal,args);
#define ERROR(args...)      s_SerialLog.Write(LogLevel_Error,args);
#define WARN(args...)       s_SerialLog.Write(LogLevel_Warn,args);
#define INFO(args...)       s_SerialLog.Write(LogLevel_Info,args);
#define DEBUG(args...)      s_SerialLog.Write(LogLevel_Debug,args);
#define TRACE(args...)      s_SerialLog.Write(LogLevel_Trace,args);
#elif (CLOG_DEFAULT_APPENDER == CLOG_APPENDER_FLASH) && (CLOG_APPENDER_FLASH_ENABLE == 1)
#define RAW(pBuf,length)    s_FlashLog.WriteRAW(pBuf,length);
#define FATAL(args...)      s_FlashLog.Write(LogLevel_Fatal,args);
#define ERROR(args...)      s_FlashLog.Write(LogLevel_Error,args);
#define WARN(args...)       s_FlashLog.Write(LogLevel_Warn,args);
#define INFO(args...)       s_FlashLog.Write(LogLevel_Info,args);
#define DEBUG(args...)      s_FlashLog.Write(LogLevel_Debug,args);
#define TRACE(args...)      s_FlashLog.Write(LogLevel_Trace,args);
#elif (CLOG_DEFAULT_APPENDER == CLOG_APPENDER_RTT) && (CLOG_APPENDER_RTT_ENABLE == 1)
#define RAW(pBuf,length)    s_RTTLog.WriteRAW(pBuf,length);
#define FATAL(args...)      s_RTTLog.Write(LogLevel_Fatal,args);
#define ERROR(args...)      s_RTTLog.Write(LogLevel_Error,args);
#define WARN(args...)       s_RTTLog.Write(LogLevel_Warn,args);
#define INFO(args...)       s_RTTLog.Write(LogLevel_Info,args);
#define DEBUG(args...)      s_RTTLog.Write(LogLevel_Debug,args);
#define TRACE(args...)      s_RTTLog.Write(LogLevel_Trace,args);
#else
#define RAW(args...)   
#define FATAL(args...) 
#define ERROR(args...)  
#define WARN(args...)   
#define INFO(args...)   
#define DEBUG(args...)  
#define TRACE(args...) 
#endif
/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Types 
 * @{  
 */
typedef enum
{
    LogLevel_None       = 0,
    LogLevel_Fatal      = 1,
    LogLevel_Error      = 2,
    LogLevel_Warn       = 3,
    LogLevel_Info       = 4,
    LogLevel_Debug      = 5,
    LogLevel_Trace      = 6,
}LogLevel_t;

typedef struct
{
    LogLevel_t  (*GetLogLevel)(void);
    void        (*SetLogLevel)(LogLevel_t loglevel);
    void        (*Write)(LogLevel_t level,const char *fmt,...);
    void        (*WriteRAW)(uint8_t *pBuf,uint16_t length);
    int         (*vprintf)(LogLevel_t level,const char *fmt, va_list args);
}SerialLog_t;

typedef struct
{
    LogLevel_t  (*GetLogLevel)(void);
    void        (*SetLogLevel)(LogLevel_t loglevel);
    void        (*Write)(LogLevel_t level,const char *fmt,...);
    void        (*WriteRAW)(uint8_t *pBuf,uint16_t length);
    int         (*vprintf)(LogLevel_t level,const char *fmt, va_list args);
}RTTLog_t;

typedef struct
{
    LogLevel_t  (*GetLogLevel)(void);
    void        (*SetLogLevel)(LogLevel_t loglevel);
    void        (*Write)(LogLevel_t level,const char *fmt,...);
    void        (*WriteRAW)(uint8_t *pBuf,uint16_t length);
    int         (*vprintf)(LogLevel_t level,const char *fmt, va_list args);
    void        (*Read)(uint32_t page);
    void        (*Clear)(void);
}FlashLog_t;

typedef union
{
    SerialLog_t SerialLog;
    RTTLog_t    RTTLog;
    FlashLog_t  FlashLog;
}CLog_t;

typedef enum
{
    CLogAppender_Serial  = 0,
    CLogAppender_Flash,
    CLogAppender_RTT,
}CLogAppender_t;
/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Variables 
 * @{  
 */
extern const char* g_LogLevelText[];
#if CLOG_APPENDER_SERIAL_ENABLE == 1
extern SerialLog_t s_SerialLog;
#endif

#if CLOG_APPENDER_RTT_ENABLE == 1
extern RTTLog_t s_RTTLog;
#endif

#if CLOG_APPENDER_FLASH_ENABLE == 1
extern FlashLog_t s_FlashLog;
#endif
/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Functions 
 * @{  
 */
void    CLog_Init(CLogAppender_t appender);
uint8_t CLog_GetCurrentTaskID(void);
void    CLog_GetTime(uint32_t *sec,uint16_t *ms);

void CLog_Fatal(CLogAppender_t appender,const char *fmt,...);
void CLog_Error(CLogAppender_t appender,const char *fmt,...);
void CLog_Warn(CLogAppender_t appender,const char *fmt,...);
void CLog_Info(CLogAppender_t appender,const char *fmt,...);
void CLog_Debug(CLogAppender_t appender,const char *fmt,...);
void CLog_Trace(CLogAppender_t appender,const char *fmt,...);

LogLevel_t  CLog_GetLogLevel(CLogAppender_t appender);
void        CLog_SetLogLevel(CLogAppender_t appender,LogLevel_t level);

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
