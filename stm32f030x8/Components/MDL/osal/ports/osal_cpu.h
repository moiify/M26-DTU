/**
 **************************************************************************************************
 * @file        osal_cpu.h
 * @author
 * @version     V1.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _OSAL_CPU_H_
#define _OSAL_CPU_H_

#include "stdint.h"
#include "intrinsics.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    osal_cpu_Modules 
 * @{  
 */

/**
 * @defgroup      osal_cpu_Exported_Macros 
 * @{  
 */
#define  OSAL_ENTER_CRITICAL(cpu_sr)  {cpu_sr = __get_PRIMASK();__set_PRIMASK(1);}
#define  OSAL_EXIT_CRITICAL(cpu_sr)   {__set_PRIMASK(cpu_sr);}
/**
 * @}
 */

/**
 * @defgroup      osal_cpu_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_cpu_Exported_Types 
 * @{  
 */
typedef unsigned int   OSAL_CPU_SR;
/**
 * @}
 */

/**
 * @defgroup      osal_cpu_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      osal_cpu_Exported_Functions 
 * @{  
 */

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
