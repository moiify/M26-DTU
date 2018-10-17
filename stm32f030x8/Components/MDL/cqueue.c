/**
 **************************************************************************************************
 * @file        cqueue.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "cqueue.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    cqueue_Modules 
 * @{  
 */

/**
 * @defgroup      cqueue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cqueue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       cqueue_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      cqueue_Functions 
 * @brief         
 * @{  
 */
void CQueue8_Init(CQueue8_t *queue,uint8_t *pBuf,uint16_t size)
{
    queue->pData = pBuf;
    queue->Size = size;
    queue->Count = 0;
    queue->In = 0;
    queue->Out = 0;
}

int16_t CQueue8_Enqueue(CQueue8_t *queue,uint8_t *pData,uint16_t count)
{
    if (queue->Size - queue->Count >= count)
    {
        for (int i=0; i<count; i++)
        {
            queue->pData[queue->In++] = pData[i];
            queue->In %= queue->Size;
        }
        queue->Count += count;

        return count;
    }

    return 0;
}

int16_t CQueue8_Deuqueue(CQueue8_t *queue,uint8_t *pBuf,uint16_t count)
{
    uint16_t tmp;

    if (queue->Count >= count)
    {
        tmp = count;
    }
    else
    {
        tmp = queue->Count;
    }

    for (int i=0; i<tmp; i++)
    {
        pBuf[i] = queue->pData[queue->Out++];
        queue->Out %= queue->Size;
    }
    queue->Count -= count;

    return tmp;
}

void CQueue16_Init(CQueue16_t *queue,uint16_t *pBuf,uint16_t size)
{
    queue->pData = pBuf;
    queue->Size = size;
    queue->Count = 0;
    queue->In = 0;
    queue->Out = 0;
}

int16_t CQueue16_Enqueue(CQueue16_t *queue,uint16_t *pData,uint16_t count)
{
    if (queue->Size - queue->Count >= count)
    {
        for (int i=0; i<count; i++)
        {
            queue->pData[queue->In++] = pData[i];
            queue->In %= queue->Size;
        }
        queue->Count += count;

        return count;
    }

    return 0;
}

int16_t CQueue16_Deuqueue(CQueue16_t *queue,uint16_t *pBuf,uint16_t count)
{
    uint16_t tmp;

    if (queue->Count >= count)
    {
        tmp = count;
    }
    else
    {
        tmp = queue->Count;
    }

    for (int i=0; i<tmp; i++)
    {
        pBuf[i] = queue->pData[queue->Out++];
        queue->Out %= queue->Size;
    }
    queue->Count -= count;

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

