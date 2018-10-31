/**
 **************************************************************************************************
 * @file        maintain_process.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MAINTAIN_PROCESS_H_
#define _MAINTAIN_PROCESS_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    maintain_process_Modules 
 * @{  
 */

/**
 * @defgroup      maintain_process_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Exported_Functions 
 * @{  
 */

void Maintain_Trans_Check(void);
void Server_Trans_Check(void);
void Maintain_Trans_Process(uint8_t *pBuf,uint16_t length);
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
