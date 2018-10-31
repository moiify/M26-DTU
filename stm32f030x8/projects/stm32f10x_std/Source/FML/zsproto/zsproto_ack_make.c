/**
 **************************************************************************************************
 * @file        zsproto_ack_make.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "zsproto.h"
#include "zsproto_ack_make.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_ack_make_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_ack_make_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_ack_make_Functions 
 * @brief         
 * @{  
 */
uint16_t ZSProto_MakeTCPIP_Ack(uint8_t *pBuf,uint8_t ftf,uint8_t fcf,uint8_t seq)
{
//    uint8_t *p = pBuf;
//    ZSProtoAHR_t *ahr;
//    ZSProtoTCPIPAPDH_t *apdh;
//    ZSProtoAFR_t *afr;
//
//    ahr = (ZSProtoAHR_t*)p;
//    ahr->Sign = ZSPROTO_AHR_SIGN;
//    ahr->Length = 0;
//    ahr->FTF.Value = ftf;
//    p += sizeof(ZSProtoAHR_t);
//
//    apdh = (ZSProtoTCPIPAPDH_t*)p;
//    apdh->FCF.Value= fcf;
//    apdh->Seq = seq;
//    apdh->Model = 1;
//    apdh->DeviceId = 10;
//    p += sizeof(ZSProtoTCPIPAPDH_t);
//
//    afr = (ZSProtoAFR_t*)p;
//    afr->Sign = ZSPROTO_AFR_SIGN;
//
//    ahr->Length = p - pBuf + 1;
//
//    return ahr->Length;
    return 0;
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

