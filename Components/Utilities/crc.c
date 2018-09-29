/**
 **************************************************************************************************
 * @file        crc.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "crc.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    crc_Modules 
 * @{  
 */

/**
 * @defgroup      crc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      crc_Functions 
 * @brief         
 * @{  
 */

/**
 * @brief    modbus crc16校验
 * @param    pbuf:uint8_t* 
 * @param    length:uint16_t 
 * @retval   uint16_t: 
 * @note     Poly:0x8005;Init:0xFFFF;Refin:True;Refout:True;Xorout:0x0000  
 */
uint16_t CRC16_Modbus(uint8_t *pbuf,uint16_t length)
{
    uint16_t crc,i,j;
    crc = 0xFFFF;

    for (i=0; i<length; i++)
    {
        crc = crc^(uint16_t)pbuf[i];
        for (j=0; j<8; j++)
        {
            if ((crc&0x0001) != 0)
            {
                crc = (crc>>1)^0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief    ymodem crc16校验
 * @param    pbuf:uint8_t* 
 * @param    length:uint16_t 
 * @retval   uint16_t: 
 * @note     Poly:0x1021;Init:0x0000;Refin:False;Refout:False;Xorout:0x0000  
 */
uint16_t CRC16_Ymodem(uint8_t *pbuf,uint16_t length)
{
    uint16_t crc,i,j;
    crc = 0x0000;

    for (i=0; i<length; i++)
    {
        crc = crc^((uint16_t)pbuf[i] << 8);
        for (j=0; j<8; j++)
        {
            if ((crc&0x8000) != 0)
            {
                crc = (crc<<1)^0x1021;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief    maxim crc16校验
 * @param    pbuf:uint8_t* 
 * @param    length:uint16_t 
 * @retval   uint16_t: 
 * @note     Poly:0x8005;Init:0x0000;Refin:True;Refout:True;Xorout:0xFFFF  
 */
uint16_t CRC16_Maxim(uint8_t *pbuf,uint16_t length)
{
    uint16_t crc,i,j;
    crc = 0x0000;

    for (i=0; i<length; i++)
    {
        crc = crc^(uint16_t)pbuf[i];
        for (j=0; j<8; j++)
        {
            if ((crc&0x0001) != 0)
            {
                crc = (crc>>1)^0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc^0xFFFF;
}

/**
 * @brief    CCITT crc16校验
 * @param    pbuf:uint8_t* 
 * @param    length:uint16_t 
 * @retval   uint16_t: 
 * @note     Poly:0x1021;Init:0x0000;Refin:True;Refout:True;Xorout:0x0000  
 */
uint16_t CRC16_CCITT(uint8_t *pbuf,uint16_t length)
{
    uint16_t crc,i,j;
    crc = 0x0000;

    for (i=0; i<length; i++)
    {
        crc = crc^(uint16_t)pbuf[i];
        for (j=0; j<8; j++)
        {
            if ((crc&0x0001) != 0)
            {
                crc = (crc>>1)^0x8408;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief    
 * @param    pbuf:uint8_t* 
 * @param    length:uint16_t 
 * @retval   uint16_t: 
 * @note     Poly:0x1021;Init:0xFFFF;Refin:False;Refout:False;Xorout:0x0000  
 */
uint16_t CRC16_CCITT_FALSE(uint8_t *pbuf,uint16_t length)
{
    uint16_t crc,i,j;
    crc = 0xFFFF;

    for (i=0; i<length; i++)
    {
        crc = crc^((uint16_t)pbuf[i] << 8);
        for (j=0; j<8; j++)
        {
            if ((crc&0x8000) != 0)
            {
                crc = (crc<<1)^0x1021;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
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

