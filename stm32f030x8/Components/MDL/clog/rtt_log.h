/**
 **************************************************************************************************
 * @file        rtt_log.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _RTT_LOG_H_
#define _RTT_LOG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#if CLOG_APPENDER_RTT_ENABLE == 1
/**
 * @addtogroup    rtt_log_Modules 
 * @{  
 */

/**
 * @defgroup      rtt_log_Exported_Macros 
 * @{  
 */
#define RTT_LOG_BUF_SIZE         BUFFER_SIZE_UP
#define DEFAULT_RTT_LOG_LEVEL    LogLevel_Debug
/**
 * @}
 */

/**
 * @defgroup      rtt_log_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtt_log_Exported_Functions 
 * @{  
 */
void RTTLog_Init(RTTLog_t *log);
/**
 * @}
 */

/**
 * @}
 */
#endif
/**
 * @}
 */
#endif
