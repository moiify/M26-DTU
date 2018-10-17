/**
 **************************************************************************************************
 * @file        cshell_GPRS.c
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
#include "stm32_bsp_conf.h"
#include "cshell_port.h"
#include "clog.h"
#include "cshell.h"
#include "cshell_user.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    cshell_GPRS_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_GPRS_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cshell_GPRS_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cshell_GPRS_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Private_Variables 
 * @brief         
 * @{  
 */
/* 帮助说明 */
const char g_CShellHelp[] = 
{
    "c shell help\r\n" \
    "-support cmd:(help)(log-off)(log-on)(reboot)(set)(get)\r\n" \
    "--cmd(set)\r\n" \
    "----format:set <device> <param=xxxx>\r\n" \
    "----return:ok.param=xxx or error.xxx\r\n" \
    "--cmd(get)\r\n" \
    "----format:get <device> <param>\r\n" \
    "----return:ok.param=xxx or error.xxx\r\n" \
    "---support device and param\r\n" \
    "----device:(router)\r\n" \
    "-----param:(ip)(netmask)(gateway)(mac)(remoteip)(remoteport)\r\n"
};

/* 帮助说明长度 */
const uint32_t g_CShellHelp_Size = sizeof(g_CShellHelp);

static void default_get_callback(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length);
static void default_set_callback(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length);
//static void get_ip_cb(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length);

const CShellParam_t  s_RouterParamList[] = 
{
    {"ip",2,default_get_callback,default_set_callback},
    {"netmask",7,default_get_callback,default_set_callback},
    {"gateway",7,default_get_callback,default_set_callback},
    {"mac",3,default_get_callback,default_set_callback},
    {"remoteip",8,default_get_callback,default_set_callback},
    {"remoteport",10,default_get_callback,default_set_callback},
};


static LogLevel_t s_LogLevel_Backup;
/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Public_Variables 
 * @brief         
 * @{  
 */
const CShellDevice_t g_CShellDevice[] = 
{
    {
        "router",
        6,
        s_RouterParamList,
        sizeof(s_RouterParamList)/sizeof(s_RouterParamList[0]),
    },
};

const uint32_t g_CShellDevice_Count = sizeof(g_CShellDevice)/sizeof(g_CShellDevice[0]);;
/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Functions 
 * @brief         
 * @{  
 */
void default_get_callback(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length)
{
    CShell_WriteBytes("default.get ",12);
    CShell_WriteBytes(g_CShellDevice[device_index].DeviceName,g_CShellDevice[device_index].DeviceNameLength);
    CShell_WriteBytes(" ",1);
    CShell_WriteBytes(g_CShellDevice[device_index].Params[param_index].Name,g_CShellDevice[device_index].Params[param_index].NameLength);
    if (data_length > 0)
    {
        CShell_WriteBytes("=",1);
        CShell_WriteBytes(data,data_length);
    }
    CShell_WriteBytes("\r\n",2);
}

void default_set_callback(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length)
{
    CShell_WriteBytes("default.set ",12);
    CShell_WriteBytes(g_CShellDevice[device_index].DeviceName,g_CShellDevice[device_index].DeviceNameLength);
    CShell_WriteBytes(" ",1);
    CShell_WriteBytes(g_CShellDevice[device_index].Params[param_index].Name,g_CShellDevice[device_index].Params[param_index].NameLength);
    CShell_WriteBytes("=",1);
    CShell_WriteBytes(data,data_length);
    CShell_WriteBytes("\r\n",2);
}

//void get_ip_cb(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length)
//{
//    char buf[30];
//    uint8_t length = 0; 
//    //length = sprintf(buf,"ok.ip=%d.%d.%d.%d\r\n",(uint8_t)Lwip_Get_IP(),(uint8_t)(Lwip_Get_IP()>>8),(uint8_t)(Lwip_Get_IP()>>16),(uint8_t)(Lwip_Get_IP()>>24));
//    CShell_WriteBytes((uint8_t*)buf,length);
//}

void CShell_GPRS_Log_off_CB(void)
{
    s_LogLevel_Backup = CLog_GetLogLevel(CLogAppender_RTT);
    CLog_SetLogLevel(CLogAppender_RTT,LogLevel_None);
    char buf[]="ok.log off\r\n";
    CShell_WriteBytes((uint8_t*)buf,sizeof(buf)-1);
}

void CShell_GPRS_Log_on_CB(void)
{
    CLog_SetLogLevel(CLogAppender_RTT,s_LogLevel_Backup);
    char buf[]="ok.log on\r\n";
    CShell_WriteBytes((uint8_t*)buf,sizeof(buf)-1);
}

void CShell_GPRS_Reboot_CB(void)
{
    char buf[]="ok.reboot\r\n";
    CShell_WriteBytes((uint8_t*)buf,sizeof(buf)-1);
    NVIC_SystemReset();
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

