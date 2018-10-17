/**
 **************************************************************************************************
 * @file        cshell.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CSHELL_H_
#define _CSHELL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cshell_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_Exported_Macros 
 * @{  
 */
#define CSHELL_PASSWORD_ENABLE  1

/**
 * @}
 */

/**
 * @defgroup      cshell_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t *Name;          /*!< 参数名称 */
    uint8_t NameLength;     /*!< 参数名称长度 */
    void (*get_callback)(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length); /*!< 获取参数回调 */
    void (*set_callback)(uint8_t device_index,uint8_t param_index,uint8_t *data,uint8_t data_length); /*!< 配置参数回调 */
}CShellParam_t;

typedef struct
{
    uint8_t *DeviceName;        /*!< 设备名称 */
    uint8_t DeviceNameLength;   /*!< 设备名称长度 */
    const CShellParam_t *Params;    /*!< 参数列表 */
    uint8_t ParamsCount;            /*!< 参数列表数量 */
}CShellDevice_t;
/**
 * @}
 */

/**
 * @defgroup      cshell_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_Exported_Functions 
 * @{  
 */
void CShell_Exec(void);
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
