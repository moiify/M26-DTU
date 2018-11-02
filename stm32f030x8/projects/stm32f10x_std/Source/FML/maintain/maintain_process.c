/**
 **************************************************************************************************
 * @file        maintain_process.c
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
#include "osal.h"
#include "zsproto.h"
#include "env_var.h"
#include "stm32_bsp_conf.h"
#include "clog.h"
#include "zsproto_package_process.h"
#include "zsproto_penetrate_process.h"
#include "maintain_process.h"
#include "gprs_cache.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    maintain_process_Modules 
 * @{  
 */

/**
 * @defgroup      maintain_process_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Macros_Defines 
 * @brief         
 * @{  
 */
#define NOT_SETPACKAGE  1
#define IS_SETPACKAGE   2
/**
 * @}
 */

/**
 * @defgroup      maintain_process_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      maintain_process_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void maintain_apd_process(uint8_t *pBuf,uint16_t length);
/**
 * @}
 */

/**
 * @defgroup      maintain_process_Functions 
 * @brief         
 * @{  
 */
void Maintain_Trans_Check(void)
{
    uint8_t buf[300];
    uint16_t len = 0;
//    static uint32_t reclen=0;
//    static uint16_t reccon=0;
    if(g_SystemInfo.Gprs_Operatingmode==Gprs_Packagemode)
    {
        len = ZSProto_FlowGetCacheIdleLength(ZSPROTO_FLOWCHANNEL_MAINTAIN);
        
        if (len > 0)
        {
            if (len > sizeof(buf))
            {
                len = sizeof(buf);
            }
            len = BSP_USART_ReadBytes(COM_USART_MAINTAIN, buf, len);
//            reclen+=len;
//            DEBUG("[MT] reclen:%d\r\n",reclen);
//            DEBUG("[MT] recbuf:%s\r\n",buf);
//            DEBUG("[MT] reccount:%d\r\n",reccon);
//            reccon++;
            if (len > 0)
            {
                ZSProto_FlowAnalysis(ZSPROTO_FLOWCHANNEL_MAINTAIN, buf, len);
            }
        }
        
    }
    else if(g_SystemInfo.Gprs_Operatingmode==Gprs_Transparentmode)
    {   
        uint8_t recbuf[512];
        len = BSP_USART_ReadBytes(COM_USART_MAINTAIN, recbuf, g_Machine_ReceiveBuf.Size);
        //DEBUG("[MT] reclen:%d\r\n",len);
        if(len>0)
        {   
            if(ZSProto_IsPackage(ZSPROTO_FLOWCHANNEL_MAINTAIN,recbuf,len)==NOT_SETPACKAGE)
            {
                ZSProto_TransparentData(recbuf,len);
            }    
        }
    }
}

void Maintain_Trans_Process(uint8_t *pBuf,uint16_t length)
{
    uint8_t fcs = 0;
    uint8_t data;

    /* 数据校验 */
    for (int i=0; i<length-3;i++)
    {
        data = pBuf[i+1];
        fcs += data;
    }

    if (fcs != pBuf[length-2])
    {
//        DEBUG("[MT] packet fcs error\r\n");
//        return;
    }
    
//    DEBUG("[MT] packcount:%d\r\n",packcon);
    maintain_apd_process(&pBuf[ZSPROTO_APD_DATA_OFFSET], length - 5);
}

static void maintain_apd_process(uint8_t *pBuf,uint16_t length)
{
    uint8_t *p = pBuf;
    ZSProtoAPDU_P2P_t *apd = (ZSProtoAPDU_P2P_t*)p;
    
    
    /* 需要应答 */
    if (apd->FCF.bitfield.AckReq == 1)
    {
         switch (apd->Cmd)
            {
                case ZSCmd_ConfigGetReq:  //测试用收发数据的命令
                {   
                    ZSProto_ConfigGetReq_Process();
                    //DEBUG("[GPRS] ConfigGetReq_Process\r\n");
                    break;
                }
            }
        
    }

    if (apd->FCF.bitfield.FrameType == ZSPROTO_FRAMETYPE_ACK)
    {
    }
    else if (apd->FCF.bitfield.FrameType == ZSPROTO_FRAMETYPE_DATA)
    {
           // DEBUG("[MT] zsproto cmd=%d\r\n", apd->Cmd);
            switch (apd->Cmd)
            {
                case ZSProto_SocketPcakReq:  //测试用收发数据的命令
                {   
                    ZSProto_SocketPcakReq_Process(pBuf,length-4);
                    DEBUG("[GPRS] SendDataReq_Process\r\n");
                    break;
                }
                case ZSCmd_ConfigSetReq:
                {
                    ZSProto_ConfigSetReq_Process(pBuf,length);
                    DEBUG("[GPRS] ConfigSetReq_Process\r\n");
                    break;
                }
            }
    }
}

void Server_Trans_Check()
{
  if(Server_receiveDataInfo.Count>0)
  {  
      ZSProto_Make_SocketDataPackage(Server_receiveDataInfo.buf[Server_receiveDataInfo.Out].SocketNum,Server_receiveDataInfo.buf[Server_receiveDataInfo.Out].Buf,Server_receiveDataInfo.buf[Server_receiveDataInfo.Out].Len);
      Server_receiveDataInfo.Out++;
      Server_receiveDataInfo.Count--;
      Server_receiveDataInfo.Out %=Server_receiveDataInfo.Size;
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

