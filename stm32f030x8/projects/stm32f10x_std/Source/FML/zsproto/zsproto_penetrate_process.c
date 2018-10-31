/**
 **************************************************************************************************
 * @file        zsproto_penetrate_process.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_commond.h"
#include "zsproto_penetrate_process.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_penetrate_process_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_penetrate_process_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Macros_Defines 
 * @brief         
 * @{  
 */
#define SOCKETCOUNT 2
/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_penetrate_process_Functions 
 * @brief         
 * @{  
 */
void ZSProto_TransparentData(uint8_t *pBuf,uint16_t length)
{   
    uint8_t muxnum;
    for(muxnum=0;muxnum<SOCKETCOUNT;muxnum++)
    {
        if(g_SystemInfo.Socket_ListInfo[muxnum].ServerEN==SERVER_ENABLE)
        {
            GPRS_SendData(pBuf,length,muxnum); 
            break;
        }
    }
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

