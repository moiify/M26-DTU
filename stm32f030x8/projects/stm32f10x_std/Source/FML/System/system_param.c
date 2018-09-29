/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *              存储原理:
 *              CDB_Inflash_Param_Init调用一次会自动分配一个扇区保存参数，同时要指定实际存储数据大小，
 *              SystemParam_xxx操作只提供了一个handle id参数，在对应的函数内部会根据ID读写相关的配置变量，如
 *              果需要新增参数存储在不同的扇区，需要多次调用CDB_Inflash_Param_Init，同时handle id务必要不同，
 *              并在SystemParam_xxx中增加对应的handle id操作。
 *              实际使用时，每个handle id都有一个全局的参数结构体变量，读取时，保存的参数会更新该变量。保存时
 *              直接修改该变量的值，然后调用对应handle id的保存函数即可。
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_info.h"
#include "cdb.h"
#include "system_param.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */
const SystemParam_Config_t SystemParam_Config_Default = 
{
    .ServerIp = 0xC0A8001A,
    .ServerPort = 20000,
    .WifiSSIDStr = "TP-LINK_wf",
    .WifiPasswordStr = "13951089024",
};
/**
 * @}
 */

/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
void SystemParam_Init()
{
    CDB_Inflash_Param_Init(SYSTEMPARAM_CONFIG,sizeof(g_SystemParam_Config));
}

int16_t SystemParam_Read(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            if (CDB_Inflash_Param_Read(handle, (uint8_t *)&g_SystemParam_Config) != 0)
            {
                g_SystemParam_Config = SystemParam_Config_Default;
            }
            break;
        }
    }
    return 0;
}

void SystemParam_Save(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            CDB_Inflash_Param_Write(handle, (uint8_t *)&g_SystemParam_Config);
            break;
        }
    }
}

void SystemParam_Reset(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            g_SystemParam_Config = SystemParam_Config_Default;
            SystemParam_Save(handle);
            break;
        }
    }
}

void SystemParam_Apply(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            g_SystemInfo.ServerIp = g_SystemParam_Config.ServerIp;
            uint32_t tmp = g_SystemInfo.ServerIp;
            sprintf(g_SystemInfo.ServerIpStr,"%d.%d.%d.%d",(uint8_t)(tmp>>24),(uint8_t)(tmp>>16),(uint8_t)(tmp>>8),(uint8_t)tmp);
            
            g_SystemInfo.ServerPort = g_SystemParam_Config.ServerPort;
            sprintf(g_SystemInfo.ServerPortStr,"%d",g_SystemInfo.ServerPort);

            memcpy(g_SystemInfo.WifiSSIDStr, g_SystemParam_Config.WifiSSIDStr, WIFI_SSID_LENGTH_MAX);
            memcpy(g_SystemInfo.WifiPasswordStr, g_SystemParam_Config.WifiPasswordStr, WIFI_PASSWORD_LENGTH_MAX);
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

