/**
 **************************************************************************************************
 * @file        zsproto.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "zsproto.h"
#include "self_def.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t buf[ZSPROTO_BUFFER_SIZE_MAX + 50];
    uint16_t index;
    void (*recv)(uint8_t *pBuf,uint16_t length);
}ZSProtoFlowCache_t;

#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
typedef struct
{
    void (*recv)(uint8_t *pBuf,uint16_t length);
}ZSProtoPacketCache_t;
#endif
/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_Variables 
 * @brief         
 * @{  
 */
static ZSProtoFlowCache_t s_ZSProtoFlowCacheList[ZSPROTO_FLOWCHANNEL_COUNT];

#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
static ZSProtoPacketCache_t s_ZSProtoPacketCacheList[ZSPROTO_PACKETCHANNEL_COUNT] = 
{
    NULL,
};
#endif
/**
 * @}
 */

/**
 * @defgroup      zsproto_Public_Variables 
 * @brief         
 * @{  
 */
uint32_t g_ZSProto_Seq = 0;

ZSProtoPacket_t g_ZSProtoMakeCache;
/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Functions 
 * @brief         
 * @{  
 */
#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
void ZSProto_PacketSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length))
{
    s_ZSProtoPacketCacheList[channel].recv = recv;
}
#endif

static uint16_t zsproto_flow_decode(uint8_t channel)
{
    uint16_t offset = 0;
    uint16_t remove_count = 0;
    uint16_t remain_len = s_ZSProtoFlowCacheList[channel].index;
    uint8_t *pBuf = s_ZSProtoFlowCacheList[channel].buf;

    while (remain_len >= sizeof(ZSProtoAHR_t) + sizeof(ZSProtoAFR_t))
    {
        if (pBuf[ZSPROTO_AHR_SIGN_OFFSET + offset] == ZSPROTO_AHR_SIGN)
        {
            uint16_t len;
            len =pBuf[ZSPROTO_AHR_LENGTH_OFFSET + offset]+pBuf[ZSPROTO_AHR_LENGTH_OFFSET + offset+1]*256;
            if (len <= ZSPROTO_BUFFER_SIZE_MAX)
            {
                if (remain_len >= len)
                {
                    if (pBuf[ZSPROTO_AHR_SIGN_OFFSET + offset + len - 1] == ZSPROTO_AFR_SIGN)
                    {   
                        if (s_ZSProtoFlowCacheList[channel].recv != NULL)
                        {   
                            s_ZSProtoFlowCacheList[channel].recv(&pBuf[ZSPROTO_AHR_SIGN_OFFSET+offset], len);
                            
                        }
                        remain_len -= len;
                        remove_count += len;
                        offset += len;
                    }
                    else
                    {
                        offset++;
                        remain_len--;
                        remove_count++;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                offset++;
                remain_len--;
                remove_count++;
            }
        }
        else
        {
            offset++;
            remain_len--;
            remove_count++;
        }
    }

    if (offset != 0)
    {
        for (int i=0; i < remain_len; i++)
        {
            pBuf[i] = pBuf[offset+i];
        }
    }

    return remove_count;
}

void ZSProto_FlowAnalysis(uint8_t channel,uint8_t *pBuf,uint16_t length)
{
    uint16_t empty_count = 0,read_count = 0;

    if (length > 0)
    {
        empty_count = sizeof(s_ZSProtoFlowCacheList[channel].buf) - s_ZSProtoFlowCacheList[channel].index;  //获取流缓存中剩余大小

        if (length > empty_count)    //如果要处理的数据长度大于缓存剩余大小,处理剩余缓存长度的数据
        {
            read_count = empty_count;
        }
        else
        {
            read_count = length;
        }

        memcpy(&s_ZSProtoFlowCacheList[channel].buf[s_ZSProtoFlowCacheList[channel].index],pBuf,read_count); //数据加载进缓存
        s_ZSProtoFlowCacheList[channel].index += read_count;   //索引+
        s_ZSProtoFlowCacheList[channel].index -= zsproto_flow_decode(channel);
    }
}

void ZSProto_FlowSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length))
{
    s_ZSProtoFlowCacheList[channel].recv = recv;
}

uint16_t ZSProto_FlowGetCacheIdleLength(uint8_t channel)
{   
    return (sizeof(s_ZSProtoFlowCacheList[channel].buf) - s_ZSProtoFlowCacheList[channel].index);
}

uint8_t ZSProto_IsPackage(uint8_t channel,uint8_t * pBuf,uint16_t length)
{
    uint16_t len = 0;
    if (pBuf[ZSPROTO_AHR_SIGN_OFFSET] == ZSPROTO_AHR_SIGN)
    {
        DEBUG("[Package] AHR_SIGH->PASS\r\n");
        len = (*(pBuf + ZSPROTO_AHR_LENGTH_OFFSET)) + *(pBuf + ZSPROTO_AHR_LENGTH_OFFSET+1)*256;
        if (len <= ZSPROTO_BUFFER_SIZE_MAX)
        {
            DEBUG("[Package] LEN_Check->PASS\r\n");
            if (pBuf[ZSPROTO_AHR_SIGN_OFFSET + len - 1] == ZSPROTO_AFR_SIGN)
            {
                DEBUG("[Package] AFR_SIGN->PASS\r\n");
                if (s_ZSProtoFlowCacheList[channel].recv != NULL)
                {
                    s_ZSProtoFlowCacheList[channel].recv(pBuf,length);
                    return 2;
                }
            }
        }
    }
    
    return 1;
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

