/**
 **************************************************************************************************
 * @file        ModbusCRC.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ModbusCRC.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ModbusCRC_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusCRC_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusCRC_Functions 
 * @brief         
 * @{  
 */
unsigned short ModbusCRC(unsigned char *ptr, unsigned char size)
{
	unsigned short a, b, tmp, CRC16;
	CRC16 = 0xffff;
	for (a = 0; a < size; a++)
	{
		CRC16 = *ptr^CRC16;
		for (b = 0; b < 8; b++)
		{
			tmp = CRC16 & 0x0001;
			CRC16 = CRC16 >> 1;
			if (tmp)
				CRC16 = CRC16 ^ 0xa001;
		}
		*ptr++;
	}
	return (((CRC16 & 0x00FF) << 8) | ((CRC16 & 0xFF00) >> 8));
}


unsigned short checkCRC(unsigned char *ptr, unsigned char size)
{
	unsigned short tmp = 0;
	tmp = ModbusCRC(ptr, size);
    return tmp;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

