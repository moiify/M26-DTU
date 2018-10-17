/**
 **************************************************************************************************
 * @file        cstring.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CSTRING_H_
#define _CSTRING_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cstring_Modules 
 * @{  
 */

/**
 * @defgroup      cstring_Exported_Macros 
 * @{  
 */
#define CSTRING_ERR_NONE            (0)
#define CSTRING_ERR_EMPTY_STRING    (-1)
#define CSTRING_ERR_INVALID_DATA    (-2)
/**
 * @}
 */

/**
 * @defgroup      cstring_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cstring_Exported_Functions 
 * @{  
 */
unsigned short CString_HexStrToValueArray(char* srcStr,unsigned char* destArray);
unsigned short CString_ValueArrayToHexStr(unsigned char* srcArray,unsigned short arrayLength,char* destStr);

char* CString_Search(char *pBuf,char delim,unsigned char offset);
unsigned short CMem_RemoveAt(unsigned char* src,unsigned short src_len,unsigned char *delim,unsigned short delim_len);
unsigned short CMem_RemoveAll(unsigned char* src,unsigned short src_len,unsigned char *delim,unsigned short delim_len);
unsigned short CMem_RemoveBlock(unsigned char *src,unsigned short src_len,unsigned char *dest,unsigned short length);
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
