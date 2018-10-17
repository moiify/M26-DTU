/**
 **************************************************************************************************
 * @file        flash_log.c
 * @author
 * @version
 * @date        5/28/2016
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
#include "osal.h"
#include "clog.h"
#include "stm32_bsp_conf.h"
#include "flash_log.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#if CLOG_APPENDER_FLASH_ENABLE == 1
/**
 * @addtogroup    flash_log_Modules 
 * @{  
 */

/**
 * @defgroup      flash_log_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Constants_Defines 
 * @brief         
 * @{  
 */
static char s_FlashLogBuf[LOGFLASH_BUF_SIZE];
/**
 * @}
 */

/**
 * @defgroup      flash_log_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint16_t Key;
    uint32_t Head;
    LogLevel_t Log_Level;
}FlashLogInfo_t;
/**
 * @}
 */

/**
 * @defgroup      flash_log_Private_Variables 
 * @brief         
 * @{  
 */
static void (*flash_write)(uint32_t addr,uint8_t* pBuf,uint32_t count);
static void (*flash_erase_sector)(uint32_t addr);
static void (*flash_read)(uint32_t addr,uint8_t *pBuf,uint32_t count);

static uint16_t (*dump)(uint8_t *pBuf,uint16_t length);

static FlashLogInfo_t s_FlashLogInfo;
static LogLevel_t s_LogLevel;
/**
 * @}
 */

/**
 * @defgroup      flash_log_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void         FlashLog_Write(LogLevel_t level,const char *fmt,...);
static void         FlashLog_WriteRAW(uint8_t *pBuf,uint16_t length);
static int          FlashLog_vprintf(LogLevel_t level,const char *fmt, va_list args);
static void         FlashLog_Read(uint32_t page);
static void         FlashLog_Clear();
static LogLevel_t   FlashLog_GetLogLevel(void);
static void         FlashLog_SetLogLevel(LogLevel_t logLevel);

static void FlashLog_InfoInit(void);
/**
 * @}
 */

/**
 * @defgroup      flash_log_Functions 
 * @brief         
 * @{  
 */

void FlashLog_Init(FlashLog_t *log)
{
    flash_read = BSP_W25Qxx_ReadBytes;
    flash_write = BSP_W25Qxx_WriteBytes;
    flash_erase_sector = BSP_W25Qxx_EraseSector;
    dump = NULL;

    log->Write = FlashLog_Write;
    log->WriteRAW = FlashLog_WriteRAW;
    log->SetLogLevel = FlashLog_SetLogLevel;
    log->GetLogLevel = FlashLog_GetLogLevel;
    log->vprintf = FlashLog_vprintf;
    log->Clear = FlashLog_Clear;
    log->Read = FlashLog_Read;
    FlashLog_InfoInit();
}

/**
 * @brief    read log file infomation
 */
static void _flashloginfo_clear()
{
    flash_erase_sector(LOGFLASH_INFO_ADDR);
    s_FlashLogInfo.Key = 0xA55A;
    s_FlashLogInfo.Head = LOGFLASH_START_ADDR;
    s_FlashLogInfo.Log_Level = LogLevel_Warn;
    flash_erase_sector(s_FlashLogInfo.Head);
}

static void FlashLog_InfoInit(void)
{
    FlashLogInfo_t info;
    flash_read(LOGFLASH_INFO_ADDR,(uint8_t*)&info,sizeof(FlashLogInfo_t));
    if (info.Key == 0xA55A)
    {
        s_FlashLogInfo = info;
    }
    else
    {
        _flashloginfo_clear();
    }
}

/**
 * @brief    write single log to flash,exclude erase the used sector
 * @param    pBuf:uint8_t* 
 * @param    length:uint16_t 
 */
static void FlashLog_Write_Single(uint8_t *pBuf,uint16_t length)
{
    uint32_t head = s_FlashLogInfo.Head;
    uint32_t next_addr = s_FlashLogInfo.Head + length;
 
    /* log write */
    if (next_addr <= LOGFLASH_END_ADDR)
    {
        flash_write(head,pBuf,length);
        s_FlashLogInfo.Head = next_addr;
    }
    else
    {
        uint32_t tmp_length = 0;
        tmp_length = LOGFLASH_SECTOR_SIZE - (head&LOGFLASH_SECTOR_PAGE_MASK);
        flash_write(head,pBuf,tmp_length);
        head = LOGFLASH_START_ADDR;
        flash_write(head,pBuf+tmp_length,length-tmp_length);

        s_FlashLogInfo.Head = head + tmp_length;
    }
}

/**
 * @brief    write single log to flash,include erase the used sector
 * @param    pBuf:uint8_t* 
 * @param    length:uint16_t 
 */
static void FlashLog_SaveLog(uint8_t *pBuf,uint16_t length)
{
    uint16_t remain_length = 0;
    uint32_t head = s_FlashLogInfo.Head;
    
    remain_length = LOGFLASH_SECTOR_SIZE - (head & LOGFLASH_SECTOR_PAGE_MASK);
    if (remain_length >= length) //the remaining length exceeds the length of the write
    {
        FlashLog_Write_Single(pBuf,length);
    }
    else //the remaining length is not enough
    {
        if (head + length > LOGFLASH_END_ADDR) 
        {
            flash_erase_sector(LOGFLASH_START_ADDR);
        }
        else 
        {
            flash_erase_sector(head + length);
        }
        FlashLog_Write_Single(pBuf,length);
    }
}

/**
 * @brief    write a log to flash
 * @param    level:LogLevel 
 * @param    fmt:const char* 
 */
static void FlashLog_Write(LogLevel_t level,const char *fmt,...)
{
    va_list args;
    uint16_t length = 0;

    char *p = s_FlashLogBuf;

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
        
        length = p - s_FlashLogBuf;
        va_start(args,fmt);
        length += vsnprintf((char*)p,sizeof(s_FlashLogBuf)-length,fmt,args);
        va_end(args);
      
        FlashLog_SaveLog((uint8_t*)s_FlashLogBuf,length);
    }
}

static void FlashLog_WriteRAW(uint8_t *pBuf,uint16_t length)
{
    FlashLog_SaveLog(pBuf,length);
}

static int FlashLog_vprintf(LogLevel_t level,const char *fmt, va_list args)
{
    uint16_t length = 0;
    
    char *p = s_FlashLogBuf;

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

        length = p - s_FlashLogBuf;
        length += vsnprintf((char*)p,sizeof(s_FlashLogBuf)-length,fmt,args);

        /*add send function*/
        FlashLog_SaveLog((uint8_t*)s_FlashLogBuf,length);
    }
    
    return length;
}

void FlashLog_Read(uint32_t page)
{
    uint8_t rdbuf[64];
    uint32_t addr = LOGFLASH_SECTOR_SIZE;
    addr += page * LOGFLASH_SECTOR_SIZE;
    uint8_t count = LOGFLASH_SECTOR_SIZE/sizeof(rdbuf);
    for (uint8_t i=0; i <count ; i++)
    {
        BSP_W25Qxx_ReadBytes(addr,rdbuf,sizeof(rdbuf));
        if (dump != NULL)
        {
            dump(rdbuf,sizeof(rdbuf));
        }
        addr += sizeof(rdbuf);
    }
}


static void FlashLog_Clear()
{
    _flashloginfo_clear();
}

static LogLevel_t FlashLog_GetLogLevel(void)
{
    return s_LogLevel;
}

static void FlashLog_SetLogLevel(LogLevel_t logLevel)
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

