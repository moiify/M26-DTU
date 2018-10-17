/**
 **************************************************************************************************
 * @file        serial_log.h
 * @author
 * @version
 * @date        5/10/2017
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SERIAL_LOG_H_
#define _SERIAL_LOG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#if CLOG_APPENDER_SERIAL_ENABLE == 1
/**
 * @addtogroup    serial_log_Modules 
 * @{  
 */

/**
 * @defgroup      serial_log_Exported_Macros 
 * @{  
 */
#define SERIAL_LOG_BUF_SIZE         200
#define DEFAULT_SERIAL_LOG_LEVEL    LogLevel_Trace
/**
 * @}
 */

/**
 * @defgroup      serial_log_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      serial_log_Exported_Functions 
 * @{  
 */
void SerialLog_Init(SerialLog_t *log);
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
