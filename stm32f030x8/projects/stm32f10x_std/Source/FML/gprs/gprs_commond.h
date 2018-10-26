/**
 **************************************************************************************************
 * @file        gprs_commond.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_COMMOND_H_
#define _GPRS_COMMOND_H_
#include "stm32f0xx.h"
#include "system_info.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    gprs_commond_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_commond_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_commond_Exported_Constants
 * @{  
 */
#define FULLCHECK  0 
#define PARTCHECK  1 
#define CHECKRIGHT  0
#define CHECKERROR ((unsigned char)-1)
/**
 * @}
 */

/**
 * @defgroup      gprs_commond_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_commond_Exported_Variables 
 * @{  
 */
/**
 * @}
 */

/**
 * @defgroup      gprs_commond_Exported_Functions 
 * @{  
 */
void GPRS_WriteBytes(uint8_t *pbuf);
char Gprs_ACK_Check(uint8_t *ackparm,uint8_t chack_way);
void Gprs_GetSocketAndLength(void);
void GPRS_SendData(uint8_t * pbuf,uint8_t length,uint8_t mux);
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
