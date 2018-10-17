/**
 **************************************************************************************************
 * @file        ModbusHardwareInit.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUSHARDWAREINIT_H_
#define _MODBUSHARDWAREINIT_H_
#include "stm32f0xx.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    ModbusHardwareInit_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Functions 
 * @{  
 */
void ModbusFunctionInit(void);
void LedToggle(void);
void ModbusSend(uint8_t * Data,uint8_t Len);
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
