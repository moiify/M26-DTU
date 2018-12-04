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
        
    }

    if (apd->FCF.bitfield.FrameType == ZSPROTO_FRAMETYPE_ACK)
    {
    }
	else if (apd->FCF.bitfield.FrameType == ZSPROTO_FRAMETYPE_DATA)
	{
		// DEBUG("[MT] zsproto cmd=%d\r\n", apd->Cmd);
		switch (apd->Cmd)
		{
			case ZSCmd_SocketPackageFromChip:   //payload转成GPRS发走
				{
					ZSProto_SocketPcakSend_Process(pBuf, length - 4);
					DEBUG("[GPRS] SendDataReq_Process\r\n");
					break;
				}
			case ZSCmd_ConfigSetReq:      //设置配置请求
				{
					ZSProto_ConfigSetReq_Process(pBuf, length);
					DEBUG("[GPRS] ConfigSetReq_Process\r\n");
					break;
				}
			case ZSCmd_ConfigGetReq:  	  //配置获取请求
				{
					ZSProto_ConfigGetReq_Process();
					DEBUG("[GPRS] ConfigGetReq_Process\r\n");
					break;
				}
			case ZSCmd_RssinotifyReq:	  //信号强度请求
				{	
                    ZSProto_RssiNotify_Process();
					DEBUG("[GPRS] RssiNotify_Process\r\n");
					break;
				}
			case ZSCmd_LinkStateNotifyReq: //连接状态请求
				{	
                    ZSProto_LinkStateNotify_Process();
					DEBUG("[GPRS] LinkStateNotify_Process\r\n");
					break;
				}
		}
	}
}

void Maintain_Trans_Check(void)
{
    uint8_t spbuf[500]={0};
    uint16_t len = 0,idlelen;
    //    static uint32_t reclen=0;
    //    static uint16_t reccon=0;
    //DEBUG("[GPRS] g_Machine_TransmitBuf.Count%d\r\n",g_Machine_TransmitBuf.Count);
    
    if(g_SystemInfo.Gprs_Operatingmode==Gprs_Packagemode)
    {
        len = ZSProto_FlowGetCacheIdleLength(ZSPROTO_FLOWCHANNEL_MAINTAIN);
        idlelen=len;
        if (len > 0)
        {
            if (len > sizeof(spbuf))
            {
                len = sizeof(spbuf);
            }
            len = BSP_USART_ReadBytes(COM_USART_MAINTAIN, spbuf, len);
            
        }
        if (idlelen > 0)
        {   
            DEBUG("[ZSProto] Package FlowAnalysis\r\n");
            ZSProto_FlowAnalysis(ZSPROTO_FLOWCHANNEL_MAINTAIN, spbuf, len);
        }  
    }
    else if(g_SystemInfo.Gprs_Operatingmode==Gprs_Transparentmode)
    {   
        len = BSP_USART_ReadBytes(COM_USART_MAINTAIN, spbuf,sizeof(spbuf));
        //DEBUG("[MT] reclen:%d\r\n",len);
//        if(len>0)
//        {   
            if(ZSProto_IsPackage(ZSPROTO_FLOWCHANNEL_MAINTAIN,spbuf,len)==NOT_SETPACKAGE)
            {
                ZSProto_TransparentData(spbuf,len);
                DEBUG("[ZSProto] Transparent FlowAnalysis\r\n");
            }    
//        }
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

