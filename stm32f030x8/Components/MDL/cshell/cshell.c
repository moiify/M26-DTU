/**
 **************************************************************************************************
 * @file        cshell.c
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "self_def.h"
#include "cshell_port.h"
#include "cshell.h"
#include "cshell_user.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    cshell_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cshell_Macros_Defines 
 * @brief         
 * @{  
 */
#define CSHELL_ELEMENT_BUF_SIZE 15
#define CSHELL_DATA_BUF_SIZE    30
/**
 * @}
 */

/**
 * @defgroup      cshell_Constants_Defines 
 * @brief         
 * @{  
 */
const char CShell_Password[] = "123456";
/**
 * @}
 */

/**
 * @defgroup       cshell_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t  Buf[60];
    uint16_t Index;
}CShellCache_t;

#if CSHELL_PASSWORD_ENABLE == 1
typedef struct
{
    uint8_t PasswordIsInput;
    uint32_t IdleTicks;
}CShellPassword_CB_t;
#endif
/**
 * @}
 */

/**
 * @defgroup      cshell_Private_Variables 
 * @brief         
 * @{  
 */
static CShellCache_t s_CShellCache; 
#if CSHELL_PASSWORD_ENABLE == 1
static CShellPassword_CB_t s_CShellPassword_CB = 
{
    .PasswordIsInput = 0,
};
#endif
/**
 * @}
 */

/**
 * @defgroup      cshell_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static uint16_t CShell_Decode(void);
static void     CShell_Process(uint8_t *pBuf,uint16_t length);
static bool     CShell_Find_GetParam(uint8_t *pBuf,uint16_t length,uint8_t *param,uint8_t *param_length,uint8_t *data,uint8_t *data_length);
static bool     CShell_Find_SetParam(uint8_t *pBuf,uint16_t length,uint8_t *param,uint8_t *param_length,uint8_t *data,uint8_t *data_length);
static uint8_t  CShell_Find_Element(uint8_t *pBuf,uint16_t length,uint8_t *element,uint8_t *element_length);
static void     unknown_cmd(uint8_t *element,uint8_t element_length);
static void     unknown_device(uint8_t *element,uint8_t element_length);
static void     unknown_param(uint8_t *element,uint8_t element_length);
/**
 * @}
 */

/**
 * @defgroup      cshell_Functions 
 * @brief         
 * @{  
 */

/**
 * @brief    
 * @retval   uint16_t: 
 */
void CShell_Exec(void)
{
    uint16_t idle_count = 0,read_count = 0;

    idle_count = sizeof(s_CShellCache.Buf) - s_CShellCache.Index;

    read_count = CShell_ReadBytes(&s_CShellCache.Buf[s_CShellCache.Index],idle_count);
    if (read_count > 0)
    {
        s_CShellCache.Index += read_count;
        s_CShellCache.Index -= CShell_Decode();  
    }
}

static uint16_t CShell_Decode(void)
{
    uint16_t packet_length = 0; 
    uint16_t offset = 0; 
    uint16_t remove_count = 0;
    int16_t remain_length = 0;
    int i = 0;
  
    for (; i < s_CShellCache.Index; i++) 
    {
        if (s_CShellCache.Buf[i] == '\r' || s_CShellCache.Buf[i] == '\n') // 找到
        {
            // 记录当前包长度
            packet_length = i - offset;

            // 处理数据
            if (packet_length > 0)
            {
                CShell_Process(&s_CShellCache.Buf[offset],packet_length);
            }

            // 记录下一个数据开始位置
            offset = i+1;
            // 记录移除数据长度
            remove_count = i+1;
            // 更新剩余缓存长度
            remain_length = s_CShellCache.Index - i - 1;
        }
    }
    
    
    if (offset != 0)
    {
        for (i = 0; i < remain_length; i++) 
        {
            s_CShellCache.Buf[i] = s_CShellCache.Buf[offset+i];
        }
    }

    return remove_count;
}

/**
 * @brief    处理接收到的数据
 * @param    pBuf:uint8_t* 
 * @param    length:uint16_t 
 */
static void CShell_Process(uint8_t *pBuf,uint16_t length)
{
    uint8_t offset = 0;

    uint8_t element[CSHELL_ELEMENT_BUF_SIZE];
    uint8_t element_length;

#if CSHELL_PASSWORD_ENABLE == 1
    if (s_CShellPassword_CB.PasswordIsInput == 0)
    {
        if (length > strlen(CShell_Password))
        {
            length = strlen(CShell_Password);
        }

        if (memcmp(pBuf, CShell_Password,length) == 0)
        {
            s_CShellPassword_CB.PasswordIsInput = 1;
            s_CShellPassword_CB.IdleTicks = CShell_GetTicks();
            CShell_WriteBytes("password are correct.please input cmd\r\n",39);
            return;
        }
        else
        {
            CShell_WriteBytes("invalid password.please re-enter\r\n",34);
            return;
        }
    }
    else
    {
        if (CShell_GetTicks() - s_CShellPassword_CB.IdleTicks > 60)
        {
            s_CShellPassword_CB.PasswordIsInput = 0;
            CShell_WriteBytes("invalid password.please re-enter\r\n",34);
            return;
        }
        s_CShellPassword_CB.IdleTicks = CShell_GetTicks();
    }
#endif

    /* find cmd */
    if ((offset = CShell_Find_Element(pBuf,length,element,&element_length)) > 0) 
    {
        pBuf += offset; // 更新缓存
        length -= offset; // 更新长度

        if ((element_length == 4) && (memcmp(element,"help",4) == 0)) // help
        {
            uint16_t i=0,len=0;
            while (i < g_CShellHelp_Size)
            {
                if (g_CShellHelp_Size - i > 200)
                {
                    len = 200;
                }
                else
                {
                    len = g_CShellHelp_Size - i;
                }
                CShell_WriteBytes((uint8_t*)&g_CShellHelp[i],len);
                //OSTimeDly(50);
                i += len;
            }
        }
        else if ((element_length == 7) && (memcmp(element,"log-off",7) == 0)) // log off
        {
            CShell_GPRS_Log_off_CB();
        }
        else if ((element_length == 6) && (memcmp(element,"log-on",6) == 0)) // log on
        {
            CShell_GPRS_Log_on_CB();
        }
        else if ((element_length == 6) && (memcmp(element,"reboot",6) == 0)) // reboot
        {
            CShell_GPRS_Reboot_CB();
        }
        else if ((element_length == 3) && (memcmp(element, "set", 3) == 0)) // set
        {
            // find device
            if ((offset = CShell_Find_Element(pBuf,length,element,&element_length)) > 0)
            {
                pBuf += offset;
                length -= offset;

                for (int i=0; i<g_CShellDevice_Count; i++)
                {
                    // match device
                    if ((element_length == g_CShellDevice[i].DeviceNameLength) && 
                        (memcmp(element,g_CShellDevice[i].DeviceName,g_CShellDevice[i].DeviceNameLength) == 0))
                    {
                        uint8_t databuf[CSHELL_DATA_BUF_SIZE];
                        uint8_t databuf_length = 0;
                        // find param
                        if ( CShell_Find_SetParam(pBuf,length,element,&element_length,databuf,&databuf_length))
                        {
                            for (int j=0; j<g_CShellDevice[i].ParamsCount; j++)
                            {
                                // match param
                                if ((element_length == g_CShellDevice[i].Params[j].NameLength) && 
                                    (memcmp(element,g_CShellDevice[i].Params[j].Name,g_CShellDevice[i].Params[j].NameLength) == 0))
                                {
                                    // set cmd callback 
                                    if (databuf_length > 0)
                                    {
                                        if (g_CShellDevice[i].Params[j].set_callback != NULL)
                                        {
                                            g_CShellDevice[i].Params[j].set_callback(i,j,databuf,databuf_length);
                                        }
                                    }
                                    else
                                    {
                                        CShell_WriteBytes("error:param data length is 0\r\n",30);
                                    }
                                    return;
                                }
                            }
                            unknown_param(element,element_length);
                            return;
                        }
                        else
                        {
                            unknown_param(element,element_length);
                            return;
                        }
                    }
                }
                unknown_device(element,element_length);
                return;
            }
            else
            {
                unknown_device(element,element_length);
            }
        }
        else if ((element_length == 3) && (memcmp(element,"get",3) == 0)) // get cmd
        {
            // find device
            if ((offset = CShell_Find_Element(pBuf,length,element,&element_length)) > 0)
            {
                pBuf += offset;
                length -= offset;

                for (int i=0; i<g_CShellDevice_Count; i++)
                {
                    // match device
                    if ((element_length == g_CShellDevice[i].DeviceNameLength) && 
                        (memcmp(element,g_CShellDevice[i].DeviceName,g_CShellDevice[i].DeviceNameLength) == 0))
                    {
                        uint8_t databuf[CSHELL_DATA_BUF_SIZE];
                        uint8_t databuf_length = 0;
                        if ((offset = CShell_Find_GetParam(pBuf,length,element,&element_length,databuf,&databuf_length)) > 0)
                        {
                            // find param
                            for (int j=0; j<g_CShellDevice[i].ParamsCount; j++)
                            {
                                // match param
                                if ((element_length == g_CShellDevice[i].Params[j].NameLength) && 
                                    (memcmp(element,g_CShellDevice[i].Params[j].Name,g_CShellDevice[i].Params[j].NameLength) == 0))
                                {
                                    // get cmd callback
                                    if (g_CShellDevice[i].Params[j].get_callback != NULL)
                                    {
                                        g_CShellDevice[i].Params[j].get_callback(i,j,databuf,databuf_length);
                                    }
                                    return;
                                }
                            }
                            unknown_param(element,element_length); // unknown param
                            return;
                        }
                        else
                        {
                            unknown_param(element,element_length); // unknown param
                            return;
                        }
                    }
                }
                unknown_device(element,element_length); // unknown device
                return;
            }
            else
            {
                unknown_device(element,element_length); // unknown device
            }
        }
        else
        {
            unknown_cmd(element,element_length); // unknown cmd
        }
    }
}

/**
 * @brief    从缓存查找一个元素
 * @param    pBuf:uint8_t* 数据缓存
 * @param    length:uint16_t 缓存长度
 * @param    element:uint8_t* 保存找到的元素
 * @param    element_length:uint8_t* 保存找到的元素的长度
 * @retval   uint8_t: 下一个元素的起始偏移位置，0表示未找到元素
 */
static uint8_t CShell_Find_Element(uint8_t *pBuf,uint16_t length,uint8_t *element,uint8_t *element_length)
{
    int i=0;
    
    *element_length = 0;
    
    for (i=0; i<length; i++)
    {
        if (pBuf[i] == ' ')
        {
            *element_length = i;
            if (*element_length > CSHELL_ELEMENT_BUF_SIZE)
            {
                *element_length = CSHELL_ELEMENT_BUF_SIZE;
            }
            memcpy(element, pBuf, *element_length); 
            return (i+1);
        }
        else if (i == length-1)
        {
            *element_length = i+1;
            if (*element_length > CSHELL_ELEMENT_BUF_SIZE)
            {
                *element_length = CSHELL_ELEMENT_BUF_SIZE;
            }
            memcpy(element, pBuf, *element_length); 
            return (i+1);
        }
    }

    return 0;
}

bool CShell_Find_GetParam(uint8_t *pBuf,uint16_t length,uint8_t *param,uint8_t *param_length,uint8_t *data,uint8_t *data_length)
{
    int i = 0;
    bool arg_used = false;
    *param_length = 0;
    *data_length = 0;
    
    for (i=0; i<length; i++)
    {
        if (pBuf[i] == '=')
        {
            arg_used = true;
            *param_length = i;
            if (*param_length > CSHELL_ELEMENT_BUF_SIZE)
            {
                *param_length = CSHELL_ELEMENT_BUF_SIZE;
            }
            memcpy(param, pBuf, *param_length); 
        }
        else if (i == length-1)
        {
            if (arg_used == true)
            {
                *data_length = i - *param_length;
                if (*data_length > CSHELL_DATA_BUF_SIZE)
                {
                    *data_length = CSHELL_DATA_BUF_SIZE;
                }
                memcpy(data, &pBuf[*param_length+1], *data_length); 
            }
            else
            {
                *param_length = i+1;
                if (*param_length > CSHELL_ELEMENT_BUF_SIZE)
                {
                    *param_length = CSHELL_ELEMENT_BUF_SIZE;
                }
                memcpy(param, pBuf, *param_length); 
            }
        }
    }
    return true;
}

/**
 * @brief    从缓存中查找一个参数及其参数值
 * @param    pBuf:uint8_t* 数据缓存
 * @param    length:uint16_t 数据缓存长度
 * @param    param:uint8_t* 获取的参数名称
 * @param    param_length:uint8_t* 获取的参数名称长度 
 * @param    data:uint8_t* 获取的参数
 * @param    data_length:uint8_t* 获取的参数长度
 * @retval   bool: 
 */
bool CShell_Find_SetParam(uint8_t *pBuf,uint16_t length,uint8_t *param,uint8_t *param_length,uint8_t *data,uint8_t *data_length)
{
    int i = 0;
    
    *param_length = 0;
    *data_length = 0;
    
    for (i=0; i<length; i++)
    {
        if (pBuf[i] == '=')
        {
            *param_length = i;
            if (*param_length > CSHELL_ELEMENT_BUF_SIZE)
            {
                *param_length = CSHELL_ELEMENT_BUF_SIZE;
            }
            memcpy(param, pBuf, *param_length); 
        }
        else if (i == length-1)
        {
            if(*param_length > 0)
            {
                *data_length = i - *param_length;
                if (*data_length > CSHELL_DATA_BUF_SIZE)
                {
                    *data_length = CSHELL_DATA_BUF_SIZE;
                }
                memcpy(data, &pBuf[*param_length+1], *data_length); 
            }
            else
            {
                *param_length = i+1;
                if (*param_length > CSHELL_ELEMENT_BUF_SIZE)
                {
                    *param_length = CSHELL_ELEMENT_BUF_SIZE;
                }
                memcpy(param, pBuf, *param_length); 
            }
        }
    }
    return true;
}

static void unknown_cmd(uint8_t *element,uint8_t element_length)
{
    char buf[CSHELL_ELEMENT_BUF_SIZE+21]="error.unknown cmd";
    buf[17] = '(';
    if (element_length > CSHELL_ELEMENT_BUF_SIZE)
    {
        element_length = CSHELL_ELEMENT_BUF_SIZE;
    }
    memcpy(&buf[18],element,element_length);
    buf[element_length+18] = ')';
    buf[element_length+19] = '\r';
    buf[element_length+20] = '\n';
    
    CShell_WriteBytes((uint8_t*)buf,element_length+21);
}

static void unknown_device(uint8_t *element,uint8_t element_length)
{
    char buf[CSHELL_ELEMENT_BUF_SIZE+24]="error.unknown device";
    buf[20] = '(';
    if (element_length > CSHELL_ELEMENT_BUF_SIZE)
    {
        element_length = CSHELL_ELEMENT_BUF_SIZE;
    }
    memcpy(&buf[21],element,element_length);
    buf[element_length+22] = ')';
    buf[element_length+23] = '\r';
    buf[element_length+24] = '\n';
    
    CShell_WriteBytes((uint8_t*)buf,element_length+24);
}

static void unknown_param(uint8_t *element,uint8_t element_length)
{
    char buf[CSHELL_ELEMENT_BUF_SIZE+23]="error.unknown param";
    buf[19] = '(';
    if (element_length > CSHELL_ELEMENT_BUF_SIZE)
    {
        element_length = CSHELL_ELEMENT_BUF_SIZE;
    }
    memcpy(&buf[20],element,element_length);
    buf[element_length+20] = ')';
    buf[element_length+21] = '\r';
    buf[element_length+22] = '\n';
    
    CShell_WriteBytes((uint8_t*)buf,element_length+23);
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

