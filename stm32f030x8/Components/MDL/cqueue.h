/**
 **************************************************************************************************
 * @file        cqueue.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CQUEUE_H_
#define _CQUEUE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    cqueue_Modules 
 * @{  
 */

/**
 * @defgroup      cqueue_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t *pData;
    uint16_t Size;
    uint16_t Count;
    uint16_t In;
    uint16_t Out;
}CQueue8_t;

typedef struct
{
    uint16_t *pData;
    uint16_t Size;
    uint16_t Count;
    uint16_t In;
    uint16_t Out;
}CQueue16_t;
/**
 * @}
 */

/**
 * @defgroup      cqueue_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Exported_Functions 
 * @{  
 */
void CQueue8_Init(CQueue8_t *queue,uint8_t *pBuf,uint16_t size);
int16_t CQueue8_Enqueue(CQueue8_t *queue,uint8_t *pData,uint16_t count);
int16_t CQueue8_Deuqueue(CQueue8_t *queue,uint8_t *pBuf,uint16_t count);

void CQueue16_Init(CQueue16_t *queue,uint16_t *pBuf,uint16_t size);
int16_t CQueue16_Enqueue(CQueue16_t *queue,uint16_t *pData,uint16_t count);
int16_t CQueue16_Deuqueue(CQueue16_t *queue,uint16_t *pBuf,uint16_t count);
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
