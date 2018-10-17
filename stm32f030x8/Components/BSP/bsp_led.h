/**
 **************************************************************************************************
 * @file        BSP_LED.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LED_H_
#define _BSP_LED_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    BSP_LED_Modules 
 * @{  
 */

/**
 * @defgroup      BSP_LED_Exported_Macros 
 * @{  
 */
#define BSP_LEDRUN          0
#define BSP_LEDM26          1     


#define BSP_LEDCOUNT        3


#define BSP_LED_BLINK_ENABLE   TRUE
/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Exported_Functions 
 * @{  
 */
void BSP_LED_Init(void);
void BSP_LED_Open(uint8_t LEDx);
void BSP_LED_Close(uint8_t LEDx);
void BSP_LED_Toggle(uint8_t LEDx);
void BSP_LED_Blink(uint8_t BSP_LEDx, uint8_t numBlinks, uint8_t percent, uint16_t period);
void BSP_LED_Update();
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
