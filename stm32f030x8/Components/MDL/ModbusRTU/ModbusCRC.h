/**
 **************************************************************************************************
 * @file        ModbusCRC.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUSCRC_H_
#define _MODBUSCRC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    ModbusCRC_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusCRC_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Exported_Functions 
 * @{  
 */

unsigned short checkCRC(unsigned char *ptr, unsigned char size);

unsigned short ModbusCRC(unsigned char *ptr, unsigned char size);
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
