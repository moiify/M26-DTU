/**
 **************************************************************************************************
 * @file        cshell_port.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CSHELL_PORT_H_
#define _CSHELL_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cshell_port_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_port_Exported_Functions 
 * @{  
 */
uint16_t CShell_ReadBytes(uint8_t *pBuf,uint16_t count);
void     CShell_WriteBytes(uint8_t *pBuf,uint16_t count);
uint32_t CShell_GetTicks(void);
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
