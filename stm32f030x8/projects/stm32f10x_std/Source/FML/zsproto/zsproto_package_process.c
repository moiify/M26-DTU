/**
**************************************************************************************************
* @file        zsproto_package_process.c
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
#include "gprs_commond.h"
#include "gprs_process.h"
#include "stm32f0xx_bsp_usart.h"
#include "string.h"
#include "osal.h"
#include "zsproto_package_process.h"
#include "clog.h"
#include "system_param.h"
#include "gprs_task.h"
/**
* @addtogroup    XXX 
* @{  
*/

/**
* @addtogroup    zsproto_package_process_Modules 
* @{  
*/

/**
* @defgroup      zsproto_package_process_IO_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Macros_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Constants_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Private_Types
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Private_Variables 
* @brief         
* @{  
*/
/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Public_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Private_FunctionPrototypes 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Functions 
* @brief         
* @{  
*/
/**
 * @brief    设置配置命令包返回
 * @param    pBuf:uint8_t* 缓存
 * @param    result:uint8_t 返回结果
 * @param    seq:uint8_t 递增序列号
 * @retval   uint16_t: 最终组包长度
 */

uint16_t ZSProto_Make_ConfigSetResp(uint8_t *pBuf,uint8_t result,uint8_t seq)  
{
    uint8_t *p = NULL;
    
    ZSProtoAPDU_P2P_t* apd;
    ConfigSetRespPayload_t *payload;
    ZSProtoTLV_t *tlv;
    uint16_t len = 0;
    uint8_t *fcs;
    
    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;
    
    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPDU_P2P_t*)p;
    
    apd->FCF.bitfield.AckReq = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.reserve1 = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.reserve2 = 0;
    apd->FCF.bitfield.Gateway = 0;
    apd->FCF.bitfield.ConnType = ZSPROTO_CONNTYPE_P2P;
    
    apd->Seq = seq;
    apd->Cmd = ZSCmd_ConfigSetResp;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (ConfigSetRespPayload_t*)p;
    payload->Result = result;
    payload->TLVCount = 16;
    p += sizeof(payload->TLVCount) + sizeof(payload->Result); 
    //工作模式
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_OPEARTINGMODE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_Operatingmode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //信号强度反馈
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_RSSIFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_RssiReportEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;      
    //网络状态反馈
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_LINKSTATEFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_LinkstateReportEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;  
    //串口通信波特率
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTBAUDRATE;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Gprs_SerialPort_BaudRate;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;  
    //串口通信校验
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTPARITY;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_Parity;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //串口通信数据位位
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTDATABITS;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_DataBits;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //串口通信停止位
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTSTOPBITS;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_StopBits;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
//    // 主服务器使能
//    tlv = (ZSProtoTLV_t*)p;
//    tlv->Tag = CONFIG_TAG_MAINSERVER_ENABLE;
//    tlv->Len = 1;
//    tlv->Value.Bit8 =g_SystemInfo.Socket_ListInfo[0].ServerEN ;
//    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器域名使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[0].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器端口号
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[0].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
    // 主服务器IP地址
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[0].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器域名
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemInfo.Socket_ListInfo[0].ServerDomain); i++)
    {
        if (g_SystemInfo.Socket_ListInfo[0].ServerDomain[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemInfo.Socket_ListInfo[0].ServerDomain[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器域名使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器端口号
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[1].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
    // 备用服务器IP地址
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[1].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器域名
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemInfo.Socket_ListInfo[1].ServerDomain); i++)
    {
        if (g_SystemInfo.Socket_ListInfo[1].ServerDomain[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] =g_SystemInfo.Socket_ListInfo[1].ServerDomain[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
//    //M26通讯波特率
//    tlv = (ZSProtoTLV_t*)p;
//    tlv->Tag = CONFIG_TAG_MOUDLEBOUNDRATE;
//    tlv->Len = 4;
//    tlv->Value.Bit32 = g_SystemInfo.Gprs_Boundrate;
//    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;       
    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;
    
    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF;
    
    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    return len;
}

/**
 * @brief    服务器数据组包发至串口
 * @param    muxnum:uint8_t soket号
 * @param    pdata:uint8_t* 数据
 * @param    length:uint16_t 长度
 * @retval   uint16_t:组包后的长度 
 */

uint16_t ZSProto_Make_SocketDataPackage(uint8_t muxnum,uint8_t * pdata,uint16_t length)
{
    uint8_t *p =NULL ;
    uint8_t *pBuf =g_ZSProtoMakeCache.Buf;
    ZSProtoAPDU_P2P_t* apd;
    SocketDataPayload_t *payload;
    uint16_t len = 0;
    uint8_t *fcs;
    
    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;
    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPDU_P2P_t*)p;
    
    apd->FCF.bitfield.AckReq = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.reserve1 = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.reserve2 = 0;
    apd->FCF.bitfield.Gateway = 0;
    apd->FCF.bitfield.ConnType = ZSPROTO_CONNTYPE_P2P;
    
    apd->Seq = g_ZSProto_Seq++;
    apd->Cmd = ZSCmd_SocketPackageFromServer;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (SocketDataPayload_t*)p;
    payload->mux = muxnum;
    p += sizeof(payload->mux);     //memcpy(payload->pData,pdata,length)  不对
    //p += sizeof(payload->pData);
    memcpy(p,pdata,length);
    p +=length;
    
    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;
    
    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF;
    
    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, len);    
    return len;
}
/**
 * @brief    往服务器发送数据包payload内的数据
 * @param    pBuf:uint8_t* 数据包首地址
 * @param    length:uint16_t 数据长度
 */

void ZSProto_SocketPcakSend_Process(uint8_t *pBuf,uint16_t length)
{   
    GPRS_SendData(&pBuf[5],length-1,pBuf[4]);  //length-1减掉socket所占的一个字节
}
/**
 * @brief    解析配置包，设置系统参数
 * @param    pBuf:uint8_t* 配置包
 * @param    length:uint16_t 配置包长度
 */

void ZSProto_ConfigSetReq_Process(uint8_t *pBuf,uint16_t length)  
{
    uint8_t *p = pBuf;    
    ConfigSetReqPayload_t *payload;
    ZSProtoTLV_t* tlv;
    uint8_t result = 1;
    
    p += sizeof(ZSProtoAPDU_P2P_t) - 4;
    
    payload = (ConfigSetReqPayload_t*)p;
    p += sizeof(payload->TLVCount);
    
    while ((payload->TLVCount--)&&(*(p+1)!=0x53))  //还需要修改 最好通过数据包长来判断是否结束
    {
        tlv = (ZSProtoTLV_t *)p;
        DEBUG("[MT] Tag:%d Len:%d Value:%d\r\n",tlv->Tag,tlv->Len,tlv->Value.Bit8);
        switch (tlv->Tag)
        {
            case CONFIG_TAG_MAINSERVER_ENABLE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerEN = SERVER_DISABLE;
                    DEBUG("[MT] MainServer Disable\r\n");
                }
                else
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerEN = SERVER_ENABLE;
                    DEBUG("[MT] MainServer Enable\r\n");
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERDOMAIN_ENABLE: 
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerConnectway=IP_Connect;
                    DEBUG("[MT] MainServer IP Connect\r\n");
                }
                else
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerConnectway=Domain_Connect;
                    DEBUG("[MT] MainServer Domain Connect\r\n");
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerPort = tlv->Value.Bit16;
                    DEBUG("[MT] MainServerPort:%d\r\n",g_SystemInfo.Socket_ListInfo[0].ServerPort);
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERIP:
            {   
                if (tlv->Value.Bit32 > 0)
                {
                    sprintf((char *)g_SystemInfo.Socket_ListInfo[0].ServerIp,"%d.%d.%d.%d",tlv->Value.Array[0],tlv->Value.Array[1],tlv->Value.Array[2],tlv->Value.Array[3]);
                    //g_SystemInfo.Socket_ListInfo[0].byte_ServerIp=((uint32_t)0|(uint32_t)tlv->Value.Array[0]<<24|(uint32_t)tlv->Value.Array[1]<<16|(uint32_t)tlv->Value.Array[2]<<8|(uint32_t)tlv->Value.Array[3]);
                    g_SystemInfo.Socket_ListInfo[0].byte_ServerIp=tlv->Value.Bit32;
                    DEBUG("[MT] MainServerIP:%s\r\n",g_SystemInfo.Socket_ListInfo[0].ServerIp);
                }
                break;
            }
            case CONFIG_TAG_MAINSERVERDOMAINNAME:
            {
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemInfo.Socket_ListInfo[0].ServerDomain))
                {
                    tmp = sizeof(g_SystemInfo.Socket_ListInfo[0].ServerDomain) - 1;
                }
                
                for (i = 0; i <tmp; i++)
                {
                    g_SystemInfo.Socket_ListInfo[0].ServerDomain[i] = tlv->Value.Array[i];
                }
                g_SystemInfo.Socket_ListInfo[0].ServerDomain[i] = 0;
                DEBUG("[MT] MainServerDomain:%s\r\n",g_SystemInfo.Socket_ListInfo[0].ServerDomain);
                break;
            }
            case CONFIG_TAG_BACKUPSERVER_ENABLE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerEN = SERVER_DISABLE;
                    DEBUG("[MT] SpareServer Disable\r\n");
                }
                else
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerEN = SERVER_ENABLE;
                    DEBUG("[MT] SpareServer Enable\r\n");
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE: 
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerConnectway = IP_Connect;
                    DEBUG("[MT] SpareServer IP Connect\r\n");
                }
                else
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerConnectway = Domain_Connect;
                    DEBUG("[MT] SpareServer Domain Connect\r\n");
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERPORT:
            {
                if (tlv->Value.Bit16 > 0)
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerPort = tlv->Value.Bit16;
                    DEBUG("[MT] SpareServerPort:%d\r\n",g_SystemInfo.Socket_ListInfo[1].ServerPort);
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERIP:
            {   
                if (tlv->Value.Bit32> 0)
                {   
                    sprintf((char *)g_SystemInfo.Socket_ListInfo[1].ServerIp,"%d.%d.%d.%d",tlv->Value.Array[0],tlv->Value.Array[1],tlv->Value.Array[2],tlv->Value.Array[3]);
                   // g_SystemInfo.Socket_ListInfo[1].byte_ServerIp=((uint32_t)0|(uint32_t)tlv->Value.Array[0]<<24|(uint32_t)tlv->Value.Array[1]<<16|(uint32_t)tlv->Value.Array[2]<<8|(uint32_t)tlv->Value.Array[3]);
                    g_SystemInfo.Socket_ListInfo[1].byte_ServerIp=tlv->Value.Bit32;
                    DEBUG("[MT] SpareServerIP:%s\r\n",g_SystemInfo.Socket_ListInfo[1].ServerIp);
                }
                break;
            }
            case CONFIG_TAG_BACKUPSERVERDOMAINNAME:
            { 
                uint8_t tmp = tlv->Len;
                uint8_t i = 0;
                if (tlv->Len >= sizeof(g_SystemInfo.Socket_ListInfo[1].ServerDomain))
                {
                    tmp = sizeof(g_SystemInfo.Socket_ListInfo[1].ServerDomain) - 1;
                }
                
                for (i = 0; i < tmp; i++)
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerDomain[i] = tlv->Value.Array[i];
                }
                g_SystemInfo.Socket_ListInfo[1].ServerDomain[i] = 0;
                DEBUG("[MT] SpareServerDomain:%s\r\n",g_SystemInfo.Socket_ListInfo[1].ServerDomain);
                break;
            }
            case CONFIG_TAG_MOUDLEBOUNDRATE:
            {
                if (tlv->Value.Bit32 > 0)
                {
                    g_SystemInfo.Gprs_Boundrate=tlv->Value.Bit32;
                    DEBUG("[MT] Gprs_MoudelBaudrate:%d\r\n",g_SystemInfo.Gprs_Boundrate);
                    break;
                }
            }
            case CONFIG_TAG_OPEARTINGMODE:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Gprs_Operatingmode= Gprs_Transparentmode;
                    DEBUG("[MT] Transparentmode\r\n");
                }
                else
                {
                    g_SystemInfo.Gprs_Operatingmode= Gprs_Packagemode;
                    DEBUG("[MT] Gprs_Packagemode\r\n");
                }
                break;
            }
            case DATA_TAG_RSSIFEEDBACK:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Gprs_RssiReportEN= 0;
                    DEBUG("[MT] Gprs_RssiReport Disable\r\n");
                }
                else
                {
                    g_SystemInfo.Gprs_RssiReportEN= 1;
                    DEBUG("[MT] Gprs_RssiReport Enable\r\n");
                }
                break;
            }
			case DATA_TAG_LINKSTATEFEEDBACK:
			{
				if (tlv->Value.Bit8==0)
				{
					g_SystemInfo.Gprs_LinkstateReportEN=0;
					DEBUG("[MT] Gprs_LinkStateReport Disable\r\n");
				}
				else
				{
					g_SystemInfo.Gprs_LinkstateReportEN=1;
					DEBUG("[MT] Gprs_LinkStateReport Enable\r\n");
				}
				break;
			}
			case CONFIG_TAG_SERIALPORTBAUDRATE:
			{
				if (tlv->Value.Bit32 > 0)
				{
					g_SystemInfo.Gprs_SerialPort_BaudRate=tlv->Value.Bit32;
					DEBUG("[MT] Gprs_SerialPortBoundrate %d\r\n",g_SystemInfo.Gprs_SerialPort_BaudRate);
				}
				break;
			}
			case CONFIG_TAG_SERIALPORTPARITY:
			{
				g_SystemInfo.Gprs_SerialPort_Parity=tlv->Value.Bit8;
				if (g_SystemInfo.Gprs_SerialPort_Parity==0)
				{
					DEBUG("[MT] Parity None\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_Parity==1)
				{
					DEBUG("[MT] Parity Odd\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_Parity==2)
				{
					DEBUG("[MT] Parity Even\r\n");
				}
				break;
			}
			case CONFIG_TAG_SERIALPORTDATABITS:
			{
				g_SystemInfo.Gprs_SerialPort_DataBits=tlv->Value.Bit8;
				if (g_SystemInfo.Gprs_SerialPort_DataBits==0)
				{
					DEBUG("[MT] DataBits 7\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_DataBits==1)
				{
					DEBUG("[MT] DataBits 8\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_DataBits==2)
				{
					DEBUG("[MT] DataBits 9\r\n");
				}
				break;
			}
			case CONFIG_TAG_SERIALPORTSTOPBITS:
			{
				g_SystemInfo.Gprs_SerialPort_StopBits=tlv->Value.Bit8;
				if (g_SystemInfo.Gprs_SerialPort_StopBits==0)
				{
					DEBUG("[MT] StopBits 1\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_StopBits==1)
				{
					DEBUG("[MT] StopBits 1.5\r\n");
				}
				else if (g_SystemInfo.Gprs_SerialPort_StopBits==2)
				{
					DEBUG("[MT] StopBits 2\r\n");
				}
				break;
			}
        }
        p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    }
    SystemParam_Save();
    BSP_USART_Open(BSP_USART2);
    g_ZSProtoMakeCache.Length = ZSProto_Make_ConfigSetResp(g_ZSProtoMakeCache.Buf,result,g_ZSProto_Seq++);
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, g_ZSProtoMakeCache.Length);
    
    OS_Timer_Start(g_GprsTask_Id,GPRS_TASK_RESET_EVENT,100);
}
/**
 * @brief   收到配置获取包命令 
 */

void ZSProto_ConfigGetReq_Process()
{   
    uint8_t result = 1;
    g_ZSProtoMakeCache.Length = ZSProto_Make_ConfigGetResp(g_ZSProtoMakeCache.Buf,result,g_ZSProto_Seq++);
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, g_ZSProtoMakeCache.Length);
}
/**
 * @brief    配置获取包返回
 */

uint16_t ZSProto_Make_ConfigGetResp(uint8_t *pBuf,uint8_t result,uint8_t seq)  
{   
    uint8_t *p = NULL;
    
    ZSProtoAPDU_P2P_t* apd;
    ConfigGetRespPayload_t *payload;
    ZSProtoTLV_t *tlv;
    uint16_t len = 0;
    uint8_t *fcs;
    
    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;
    
    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPDU_P2P_t*)p;
    
    apd->FCF.bitfield.AckReq = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.reserve1 = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.reserve2 = 0;
    apd->FCF.bitfield.Gateway = 0;
    apd->FCF.bitfield.ConnType = ZSPROTO_CONNTYPE_P2P;
    
    apd->Seq = seq;
    apd->Cmd = ZSCmd_ConfigGetResp;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (ConfigGetRespPayload_t*)p;
    payload->TLVCount = 16;
    p += sizeof(payload->TLVCount); 
    //工作模式
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_OPEARTINGMODE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_Operatingmode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //信号强度反馈
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_RSSIFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_RssiReportEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;      
    //网络状态反馈
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_LINKSTATEFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_LinkstateReportEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;  
    //串口通信波特率
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTBAUDRATE;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Gprs_SerialPort_BaudRate;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;  
    //串口通信校验
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTPARITY;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_Parity;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //串口通信数据位位
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTDATABITS;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_DataBits;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //串口通信停止位
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_SERIALPORTSTOPBITS;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_SerialPort_StopBits;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
//    // 主服务器使能
//    tlv = (ZSProtoTLV_t*)p;
//    tlv->Tag = CONFIG_TAG_MAINSERVER_ENABLE;
//    tlv->Len = 1;
//    tlv->Value.Bit8 =g_SystemInfo.Socket_ListInfo[0].ServerEN ;
//    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器域名使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[0].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器端口号
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[0].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
    // 主服务器IP地址
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[0].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 主服务器域名
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemInfo.Socket_ListInfo[0].ServerDomain); i++)
    {
        if (g_SystemInfo.Socket_ListInfo[0].ServerDomain[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] = g_SystemInfo.Socket_ListInfo[0].ServerDomain[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器域名使能
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器端口号
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[1].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
    // 备用服务器IP地址
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[1].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 备用服务器域名
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAINNAME;
    for (int i=0; i < sizeof(g_SystemInfo.Socket_ListInfo[1].ServerDomain); i++)
    {
        if (g_SystemInfo.Socket_ListInfo[1].ServerDomain[i] == 0)
        {
            tlv->Len = i;
            break;
        }
        tlv->Value.Array[i] =g_SystemInfo.Socket_ListInfo[1].ServerDomain[i];
        tlv->Len = i;
    }
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
//    //M26通讯波特率
//    tlv = (ZSProtoTLV_t*)p;
//    tlv->Tag = CONFIG_TAG_MOUDLEBOUNDRATE;
//    tlv->Len = 4;
//    tlv->Value.Bit32 = g_SystemInfo.Gprs_Boundrate;
//    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;       
    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;
    
    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF;
    
    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    return len;
}
/**
 * @brief    信号强度返回
 * @param    rssi:uint8_t 	信号强度值 0-31  99代表异常
 */

void ZSProto_Make_RssiNotify(uint8_t rssi)
{
    uint8_t *p = NULL;
    uint8_t *pBuf =g_ZSProtoMakeCache.Buf;
    ZSProtoAPDU_P2P_t* apd;
    RssiRespPayload_t *payload;
    ZSProtoTLV_t *tlv;
    uint16_t len = 0;
    uint8_t *fcs;
    
    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;
    
    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPDU_P2P_t*)p;
    
    apd->FCF.bitfield.AckReq = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.reserve1 = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.reserve2 = 0;
    apd->FCF.bitfield.Gateway = 0;
    apd->FCF.bitfield.ConnType = ZSPROTO_CONNTYPE_P2P;
    
    apd->Seq = g_ZSProto_Seq++;
    apd->Cmd = ZSCmd_RssinotifyResp;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (RssiRespPayload_t*)p;
    payload->TLVCount = 1;
    p += sizeof(payload->TLVCount) ;
    
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_RSSIFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = rssi ;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    
    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;
    
    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF
        ;
    
    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, len);
}
/**
 * @brief    网络状态返回
 * @param    linkstate:uint8_t 服务器状态    00 主备失效   0
 *  										 01 主失备使   1
 *  										10 主使备失    2
 *  										11 主备使能    3
 *  
 */ 

void ZSProto_Make_LinkStateNotify(uint8_t linkstate)
{
    uint8_t *p = NULL;
    uint8_t *pBuf =g_ZSProtoMakeCache.Buf;
    ZSProtoAPDU_P2P_t* apd;
    LinkstateRespPayload_t *payload;
    ZSProtoTLV_t *tlv;
    uint16_t len = 0;
    uint8_t *fcs;
    
    pBuf[ZSPROTO_AHR_SIGN_OFFSET] = ZSPROTO_AHR_SIGN;
    
    p = pBuf + ZSPROTO_APD_DATA_OFFSET;
    apd = (ZSProtoAPDU_P2P_t*)p;
    
    apd->FCF.bitfield.AckReq = 0;
    apd->FCF.bitfield.Sec = 0;
    apd->FCF.bitfield.Pending = 0;
    apd->FCF.bitfield.Trans = 0;
    apd->FCF.bitfield.reserve1 = 0;
    apd->FCF.bitfield.FrameType = ZSPROTO_FRAMETYPE_DATA;
    apd->FCF.bitfield.reserve2 = 0;
    apd->FCF.bitfield.Gateway = 0;
    apd->FCF.bitfield.ConnType = ZSPROTO_CONNTYPE_P2P;
    
    apd->Seq = g_ZSProto_Seq++;
    apd->Cmd = ZSCmd_LinkStateNotifyResp;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (LinkstateRespPayload_t*)p;
    payload->TLVCount = 1;
    p += sizeof(payload->TLVCount) ;
    
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = DATA_TAG_LINKSTATEFEEDBACK;
    tlv->Len = 1;
    tlv->Value.Bit8 = linkstate ;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    
    fcs = p;
    p++;
    *p = ZSPROTO_AFR_SIGN;
    
    len = p - pBuf + 1;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET] = len&0x00FF;
    pBuf[ZSPROTO_AHR_LENGTH_OFFSET+1] = (len>>8)&0x00FF
        ;
    
    *fcs = 0;
    for (int i=0; i<len-3;i++)
    {
        *fcs += pBuf[i+ZSPROTO_AHR_LENGTH_OFFSET];
    }
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, len);

}

void ZSProto_RssiNotify_Process()
{
    ZSProto_Make_RssiNotify(Gprs_GetRssiValue());    
}
void ZSProto_LinkStateNotify_Process()
{
     ZSProto_Make_LinkStateNotify(Gprs_GetLinkState());
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

