/**
 **************************************************************************************************
 * @file        cstring.c
 * @author
 * @version
 * @date        5/27/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "string.h"
#include "cstring.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    cstring_Modules 
 * @{  
 */

/**
 * @defgroup      cstring_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Functions 
 * @brief         
 * @{  
 */
int16_t CString_HexStrToValueArray(char* srcStr,uint8_t* destArray)
{
    uint8_t high,low;
    uint16_t length = 0;
    char *p_src = srcStr;
    uint8_t *p_dest = destArray;

    length = strlen(p_src);
    if (length <= 0)
    {
        return CSTRING_ERR_EMPTY_STRING;
    }

    if ((length%2) != 0)
    {
        low = *p_src++;
        if ((low >= 0x30) && (low <= 0x39))
        {
            low -= 0x30;
        }
        else if ((low >= 0x41) && (low <= 0x46))
        {
            low -= 55;
        }
        else if ((low >= 0x61) && (low <= 0x66))
        {
            low -= 87;
        }
        else
        {
            return CSTRING_ERR_INVALID_DATA;
        }
        *p_dest++ = low;
    }

    while (*p_src != 0)
    {
        high = *p_src++;
        if ((high >= 0x30) && (high <= 0x39))
        {
            high -= 0x30;
        }
        else if ((high >= 0x41) && (high <= 0x46))
        {
            high -= 55;
        }
        else if ((high >= 0x61) && (high <= 0x66))
        {
            high -= 87;
        }
        else
        {
            return CSTRING_ERR_INVALID_DATA;
        }

        low = *p_src++;
        if ((low >= 0x30) && (low <= 0x39))
        {
            low -= 0x30;
        }
        else if ((low>=0x41)&&(low<=0x46))
        {
            low -= 55;
        }
        else if ((low>=0x61)&&(low<=0x66))
        {
            low -= 87;
        }
        else
        {
            return CSTRING_ERR_INVALID_DATA;
        }
        *p_dest++ = (high<<4)+low;
    }
    return (length+1)/2;
}

uint16_t CString_ValueArrayToHexStr(uint8_t* srcArray,uint16_t arrayLength,char* destStr)
{
    uint16_t i;
    uint8_t tmp;
    uint8_t *p_array = srcArray;
    char *p_str = destStr;

    for (i=0; i<arrayLength; i++) 
    {
        tmp = p_array[i]>>4;
        if (tmp <= 9)
        {
            tmp += 0x30;
        }
        else
        {
            tmp += 55;
        }
        *p_str++ = tmp;

        tmp = p_array[i]&0x0F;
        if (tmp <= 9)
        {
            tmp += 0x30;
        }
        else
        {
            tmp += 55;
        }
        *p_str++ = tmp;
    }
    *p_str = 0;
    return i*2;
}

int16_t CString_HexStrToUint32(char* srcStr,uint32_t *value)
{
    uint8_t length = 0,i;
    uint8_t tmp = 0;
    uint32_t data = 0;
    char *p_src = srcStr;

    length = strlen(srcStr);

    if (length <= 0)
    {
        return CSTRING_ERR_EMPTY_STRING;
    }

    for (i=0; i<length; i++)
    {
        data <<= 4;
        tmp = *p_src++;
        if ((tmp >= 0x30) && (tmp <= 0x39))
        {
            tmp -= 0x30;
        }
        else if ((tmp >= 0x41) && (tmp <= 0x46))
        {
            tmp -= 55;
        }
        else if ((tmp >= 0x61) && (tmp <= 0x66))
        {
            tmp -= 87;
        }
        else
        {
            return CSTRING_ERR_INVALID_DATA;
        }
        data |= tmp;
    }
    *value = data;
    return CSTRING_ERR_NONE;
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

