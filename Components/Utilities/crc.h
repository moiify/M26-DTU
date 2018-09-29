/**
 **************************************************************************************************
 * @file        crc.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CRC_H_
#define _CRC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    crc_Modules 
 * @{  
 */

/**
 * @defgroup      crc_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Exported_Functions 
 * @{  
 */
uint16_t CRC16_Modbus(uint8_t *pbuf,uint16_t length);
uint16_t CRC16_Ymodem(uint8_t *pbuf,uint16_t length);
uint16_t CRC16_Maxim(uint8_t *pbuf,uint16_t length);
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
