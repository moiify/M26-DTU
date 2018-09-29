/**
 **************************************************************************************************
 * @file        cshell_user.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CSHELL_USER_H_
#define _CSHELL_USER_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cshell_user_Modules 
 * @{  
 */

/**
 * @defgroup      cshell_user_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_user_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_user_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cshell_user_Exported_Variables 
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
 * @defgroup      cshell_user_Exported_Functions 
 * @{  
 */
void CShell_User_Log_off_CB(void);
void CShell_User_Log_on_CB(void);
void CShell_User_Reboot_CB(void);
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
