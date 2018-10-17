/**
 **************************************************************************************************
 * @file        flash_log.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _FLASH_LOG_H_
#define _FLASH_LOG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#if CLOG_APPENDER_FLASH_ENABLE == 1
/**
 * @addtogroup    flash_log_Modules 
 * @{  
 */

/**
 * @defgroup      flash_log_Exported_Macros 
 * @{  
 */
#define LOGFLASH_SECTOR_SIZE        4096
#define LOGFLASH_SECTOR_PAGE_MASK   0x000000FF
#define LOGFLASH_START_ADDR         4096
#define LOGFLASH_END_ADDR           8191
#define LOGFLASH_INFO_ADDR          0

#define LOGFLASH_BUF_SIZE           100
/**
 * @}
 */

/**
 * @defgroup      flash_log_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      flash_log_Exported_Functions 
 * @{  
 */
void FlashLog_Init(FlashLog_t *log);
void FlashLog_Read(uint32_t page);
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
