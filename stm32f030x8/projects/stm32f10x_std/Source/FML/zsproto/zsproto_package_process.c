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
//static uint8_t  SeqCount=0;

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
//static uint8_t ZSProto_PackageMake(ZSProtoAPDU_P2P_t apd,uint8_t * pacbuf);
//static uint8_t fsc(uint8_t * pbuf,uint8_t length);
/**
* @}
*/

/**
* @defgroup      zsproto_package_process_Functions 
* @brief         
* @{  
*/
void ZSProto_SendDataReq_Process(uint8_t *pBuf,uint16_t length)
{   
    GPRS_SendData(&pBuf[5],length-1,pBuf[4]); 
}

void ZSProto_ConfigSetReq_Process(uint8_t *pBuf,uint16_t length)  //
{
    uint8_t *p = pBuf;    
    ConfigSetReqPayload_t *payload;
    ZSProtoTLV_t* tlv;
    uint8_t result = 1;
    
    p += sizeof(ZSProtoAPDU_P2P_t) - 4;
    
    payload = (ConfigSetReqPayload_t*)p;
    p += sizeof(payload->TLVCount);
    
    while (payload->TLVCount--)
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
            case CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE: // 15
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerConnectway = IP_Connect;
                    DEBUG("[MT] SpareServer IP Connect\r\n");
                }
                else
                {
                    g_SystemInfo.Socket_ListInfo[1].ServerConnectway = Domain_Connect;
                    DEBUG("[MT] SpareServer IP Connect\r\n");
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
                if (tlv->Value.Bit32 > 0)
                {
                    sprintf((char *)g_SystemInfo.Socket_ListInfo[1].ServerIp,"%d.%d.%d.%d",tlv->Value.Array[0],tlv->Value.Array[1],tlv->Value.Array[2],tlv->Value.Array[3]);
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
                    DEBUG("[MT] Gprs_Boundrate:%d\r\n",g_SystemInfo.Gprs_Boundrate);
                    
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
            case CONFIG_TAG_HEARTBEATEN:
            {
                if (tlv->Value.Bit8 == 0)
                {
                    g_SystemInfo.Gprs_HeartbeatEN= 0;
                    DEBUG("[MT] Gprs_Heartbeat Enable\r\n");
                }
                else
                {
                    g_SystemInfo.Gprs_HeartbeatEN= 1;
                    DEBUG("[MT] Gprs_Heartbeat Disable\r\n");
                }
                break;
            }
        }
        p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    }
    
    SystemParam_Save();
    
    g_ZSProtoMakeCache.Length = ZSProto_Make_ConfigSetResp(g_ZSProtoMakeCache.Buf,result,g_ZSProto_Seq++);
    BSP_USART_WriteBytes(BSP_USART2, g_ZSProtoMakeCache.Buf, g_ZSProtoMakeCache.Length);
    
    OS_Timer_Start(g_GprsTask_Id,GPRS_TASK_RESET_EVENT,100);
}

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
    apd->Cmd = ZSCmd_ConfigGetResp;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (ConfigSetRespPayload_t*)p;
    payload->Result = result;
    payload->TLVCount = 13;
    p += sizeof(payload->TLVCount) + sizeof(payload->Result);
    // 1
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 =g_SystemInfo.Socket_ListInfo[0].ServerEN ;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 2
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[0].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 3
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[0].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 4
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MAINSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[0].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 5
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
    // 6
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVER_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerEN;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 7
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERDOMAIN_ENABLE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Socket_ListInfo[1].ServerConnectway;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 8
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERPORT;
    tlv->Len = 2;
    tlv->Value.Bit16 = g_SystemInfo.Socket_ListInfo[1].ServerPort;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 9
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_BACKUPSERVERIP;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Socket_ListInfo[1].byte_ServerIp;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;
    // 10
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
    //11
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_MOUDLEBOUNDRATE;
    tlv->Len = 4;
    tlv->Value.Bit32 = g_SystemInfo.Gprs_Boundrate;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len;    
    //12
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_OPEARTINGMODE;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_Operatingmode;
    p += sizeof(tlv->Tag) + sizeof(tlv->Len) + tlv->Len; 
    //13
    tlv = (ZSProtoTLV_t*)p;
    tlv->Tag = CONFIG_TAG_HEARTBEATEN;
    tlv->Len = 1;
    tlv->Value.Bit8 = g_SystemInfo.Gprs_HeartbeatEN;
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
    return len;
}

void ZSProto_Make_RssiResp(uint8_t rssi)
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
    apd->Cmd = ZSProto_RssiNotify;
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
uint16_t ZSProto_Make_SocketDataPackage(uint8_t muxnum,uint8_t * pdata,uint16_t length)
{
    uint8_t *p = NULL;
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
    apd->Cmd = ZSProto_SocketPcakReq;
    p += sizeof(ZSProtoAPDU_P2P_t) - sizeof(apd->CmdPayload);
    
    payload = (SocketDataPayload_t*)p;
    payload->mux = muxnum;
    p += sizeof(payload->mux);     //memcpy(payload->pData,pdata,length)  ²»¶Ô
    memcpy(p,pdata,length);
    p +=length;
    
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
    return len;
}
#if 1
//uint8_t ZSProto_CSQPackageMake(uint8_t *pBuf,uint16_t length)
//{   
////    uint8_t sendbuf[50];
//    ZSProtoAPDU_P2P_t apd;
//    apd.FCF.bitfield.AckReq=0;
//    apd.FCF.bitfield.Sec=0;
//    apd.FCF.bitfield.Pending=0;
//    apd.FCF.bitfield.Trans=1;
//    apd.FCF.bitfield.reserve1=0;
//    apd.FCF.bitfield.FrameType=0;
//    apd.FCF.bitfield.reserve2=0;
//    apd.FCF.bitfield.Gateway=0;
//    apd.FCF.bitfield.ConnType=0;
////    apd.FCF.Value=0x0000;
//    apd.Seq=g_ZSProto_Seq;
//    apd.Cmd=134;
//    apd.CmdPayload=pBuf;
//    length=ZSProto_PackageMake(apd,pBuf);
//    
//    return length;
//}
//
//uint8_t ZSProto_PackageMake(ZSProtoAPDU_P2P_t apd,uint8_t * pacbuf)
//{   
//    uint16_t len;
//    uint8_t i,fcs;
//    len=strlen((const char *)pacbuf)+9;
//    for(i=0;i<len-9;i++)
//    {
//      pacbuf[7+i]=pacbuf[i];  
//    }
//    fcs=fsc(&pacbuf[1],len-3);
//    pacbuf[0]='Z';
//    pacbuf[1]=*((uint8_t*)&len);
//    pacbuf[2]=*((uint8_t*)&len+1);
//    pacbuf[3]=*((uint8_t*)&apd.FCF);
//    pacbuf[4]=*((uint8_t*)&apd.FCF+1);   //0x0008  = 08 00
//    pacbuf[5]=*((uint8_t*)&apd.Seq);
//    pacbuf[6]=*((uint8_t*)&apd.Cmd);   
//    pacbuf[len-2]=fcs; 
//    pacbuf[len-1]='S';  
//    return len;
//        
//}
//uint8_t fsc(uint8_t * pbuf,uint8_t length)
//{
//    return 0;
//}
#endif
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

