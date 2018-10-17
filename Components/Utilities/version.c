/**
 **************************************************************************************************
 * @file        version.c
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
#include "stdio.h"
#include "version.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Macros_Defines 
 * @brief         
 * @{  
 */
#define DIGIT(s, no) ((s)[no] - '0')    

#define BUILD_YEAR      ( 1000 * DIGIT(__DATE__, 7) + 100 * DIGIT(__DATE__, 8) + 10 * DIGIT(__DATE__, 9) + DIGIT(__DATE__, 10) )
#define BUILD_MONTH     ( __DATE__[2] == 'b' ? 2 : \
                           (__DATE__[2] == 'y' ? 5 : \
                             (__DATE__[2] == 'l' ? 7 : \
                               (__DATE__[2] == 'g' ? 8 : \
                                 (__DATE__[2] == 'p' ? 9 : \
                                   (__DATE__[2] == 't' ? 10 : \
                                     (__DATE__[2] == 'v' ? 11 : \
                                       (__DATE__[2] == 'c' ? 12 : \
                                         (__DATE__[2] == 'n' ?  \
                                           (__DATE__[1] == 'a' ? 1 : 6) : \
                                             (__DATE__[1] == 'a' ? 3 : 4))))))))) )
#define BUILD_DAY       ( 10 * (__DATE__[4] == ' ' ? 0 : DIGIT(__DATE__, 4)) + DIGIT(__DATE__, 5) )
#define BUILD_HOUR      ( 10 * DIGIT(__TIME__, 0) + DIGIT(__TIME__, 1) )
#define BUILD_MINUTE    ( 10 * DIGIT(__TIME__, 3) + DIGIT(__TIME__, 4) )
#define BUILD_SECOND    ( 10 * DIGIT(__TIME__, 6) + DIGIT(__TIME__, 7) )
/**
 * @}
 */

/**
 * @defgroup      version_Constants_Defines 
 * @brief         
 * @{  
 */
//static const int buildday = ( 10 * (__DATE__[4] == ' ' ? 0 : DIGIT(__DATE__, 4)) + DIGIT(__DATE__, 5));
//#pragma location = 0x0800E000
//const char datetime[50] @ 0x0800B000 = ""__DATE__""__TIME__"";
//char datetime[2] = {0,0};
/**
 * @}
 */

/**
 * @defgroup      version_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Public_Variables 
 * @brief         
 * @{  
 */
const Version g_Version =
{
    .PublicMajor = PUBLIC_VERSION_MAJOR,
    .PublicMinor = PUBLIC_VERSION_MINOR,
    .PublicRevison = PUBLIC_VERSION_REVISION,
    .PublicBuild = PUBLIC_VERSION_BUILD,
    .PrivateMajor = PRIVATE_VERSION_MAJOR,
    .PrivateMinor = PRIVATE_VERSION_MINOR,
    .PrivateRevison = PRIVATE_VERSION_REVISION,
    .BuildYear = BUILD_YEAR,
    .BuildMonth = BUILD_MONTH,
    .BuildDay = BUILD_DAY,
    .BuildHour = BUILD_HOUR,
    .BuildMinute = BUILD_MINUTE,
    .BuildSecond = BUILD_SECOND,
};
/**
 * @}
 */

/**
 * @defgroup      version_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Functions 
 * @brief         
 * @{  
 */


void Version_PublicToString(char* str)
{
    sprintf(str,"%d.%d.%d",g_Version.PublicMajor,g_Version.PublicMinor,g_Version.PublicRevison);
}

void Version_PrivateToString(char* str)
{
    sprintf(str,"%d.%d.%d",g_Version.PrivateMajor,g_Version.PrivateMinor,g_Version.PrivateRevison);
}

uint16_t Version_GetPrivateStamp(void)
{
    return (uint16_t)((PRIVATE_VERSION_MAJOR<<12) | (PRIVATE_VERSION_MINOR<<6) | (PRIVATE_VERSION_REVISION));
}

void Version_BuildDateToString(char *str)
{
    sprintf(str,"%4d-%02d-%02d %02d:%02d:%02d",g_Version.BuildYear,g_Version.BuildMonth,g_Version.BuildDay,g_Version.BuildHour,g_Version.BuildMinute,g_Version.BuildSecond);
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

