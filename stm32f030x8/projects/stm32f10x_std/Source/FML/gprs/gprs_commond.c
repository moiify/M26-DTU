/**
**************************************************************************************************
* @file        gprs_commond.c
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
#include "stm32_bsp_conf.h"
#include "system_info.h"
#include "gprs_cache.h"
#include "string.h"
#include "clog.h"

/**
* @addtogroup    XXX 
* @{  
*/

/**
* @addtogroup    gprs_commond_Modules 
* @{  
*/

/**
* @defgroup      gprs_commond_IO_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_commond_Macros_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_commond_Constants_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_commond_Private_Types
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_commond_Private_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_commond_Public_Variables 
* @brief         
* @{  
*/
/**
* @}
*/

/**
* @defgroup      gprs_commond_Private_FunctionPrototypes 
* @brief         
* @{  
*/
static char gprs_check_param(uint8_t *ackparm,uint8_t chack_way);

/**
* @}
*/

/**
* @defgroup      gprs_commond_Functions 
* @brief         
* @{  
*/

/**
* @}
*/
/**
* @}
*/
static char gprs_check_param(uint8_t *ackparm,uint8_t check_way)    
{ 
    uint8_t *p_recebuf;
    p_recebuf=g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf;
    if(check_way==FULLCHECK)
    {
        while(ackparm[0]!='\0')
        {
            if(*p_recebuf!=*ackparm)
            {
                return (unsigned char)(-1) ;
            }  
            p_recebuf++;
            ackparm++;
        }
        return 0;
    }
    else if(check_way==PARTCHECK)
    {
        if( strstr((char *)g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf,(char *)ackparm)!=NULL)
        {
            return 0;
        }
        else
        {
            return (unsigned char)-1;
        }
    }
    else return (unsigned char)-1;
}
void GPRS_WriteBytes(uint8_t *pbuf,uint16_t length)    //USART1 发送AT命令
{   
    BSP_USART_WriteBytes(BSP_USART1,pbuf,length);
}
char Gprs_ACK_Check(uint8_t *ackparm,uint8_t chack_way)  //检查收到的数据
{       
    char checkresult;
    checkresult=gprs_check_param(ackparm,chack_way); 
    return checkresult;       
}
void Gprs_GetSocketAndLength(void)            
{   
    uint8_t *pbuf;
    uint16_t i=0;
    pbuf=g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf;
    for(i=0;i<SERVER_RECEIVE_BUFMAX;i++)
    {
        if(pbuf[i]==',')
        {
            Server_receiveDataInfo.buf[Server_receiveDataInfo.In].SocketNum=pbuf[i-1]-48;
            if(pbuf[i+3]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=pbuf[i+2]-48;
                memcpy(Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Buf,&pbuf[i+5],Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len);
                break;
            }
            else if(pbuf[i+4]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=(pbuf[i+2]-48)*10+(pbuf[i+3]-48);
                memcpy(Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Buf,&pbuf[i+6],Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len);
                break;
            }
            else if(pbuf[i+5]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=(pbuf[i+2]-48)*100+(pbuf[i+3]-48)*10+(pbuf[i+4]-48);
                memcpy(Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Buf,&pbuf[i+7],Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len);
                break;
            }
        }
    }    
}
void GPRS_SendData(uint8_t * pbuf,uint16_t length,uint8_t mux) // 发送数据接口
{	
    uint16_t i;
    if( g_Machine_TransmitBuf.Count+length+3< g_Machine_TransmitBuf.Size
      &&g_SystemInfo.Socket_ListInfo[mux].ServerEN==SERVER_ENABLE)
    {   
       g_Machine_TransmitBuf.pData[g_Machine_TransmitBuf.In++]=mux;
       g_Machine_TransmitBuf.In %= g_Machine_TransmitBuf.Size;
       g_Machine_TransmitBuf.pData[g_Machine_TransmitBuf.In++]=length>>8;
       g_Machine_TransmitBuf.In %= g_Machine_TransmitBuf.Size;
       g_Machine_TransmitBuf.pData[g_Machine_TransmitBuf.In++]=length&0xff;
       g_Machine_TransmitBuf.In %= g_Machine_TransmitBuf.Size;
       for(i=0;i<length;i++)
       {
          g_Machine_TransmitBuf.pData[g_Machine_TransmitBuf.In++]=*pbuf+i;
          g_Machine_TransmitBuf.In %= g_Machine_TransmitBuf.Size;
       } 
       g_Machine_TransmitBuf.Count+=length+3; 
    }
}

/**
* @}
*/

