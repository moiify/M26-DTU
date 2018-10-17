/**
 **************************************************************************************************
 * @file        cshell_GPRS.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CSHELL_GPRS_H_
#define _CSHELL_GPRS_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cshell_GPRS_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_GPRS_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Exported_Variables 
 * @{  
 */
extern const uint32_t g_CShellHelp_Size;
extern const char g_CShellHelp[];
extern const uint32_t g_CShellDevice_Count;
extern const CShellDevice_t g_CShellDevice[];
/**
 * @}
 */

/**
 * @defgroup      cshell_GPRS_Exported_Functions 
 * @{  
 */
void CShell_GPRS_Log_off_CB(void);
void CShell_GPRS_Log_on_CB(void);
void CShell_GPRS_Reboot_CB(void);
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
