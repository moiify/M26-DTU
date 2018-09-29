/**
 **************************************************************************************************
 * @file        tea.h
 * @author
 * @version
 * @date        6/24/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _TEA_H_
#define _TEA_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    tea_Modules 
 * @{  
 */

/**
 * @defgroup      tea_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Exported_Functions 
 * @{  
 */
void TEA_Encrypt(uint8_t *pPlain,uint8_t *pCipher,uint32_t *pKey);
void TEA_Decrypt(uint8_t *pCipher,uint8_t *pPlain,uint32_t *pKey);
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
