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
#include "osal.h"
#include "cshell_port.h"
#include "clog.h"
#include "string.h"

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
Server_receiveDataInfo_Cache Server_receiveDataInfo=
{
    .In=0,
    .Out=0,
    .Count=0,
    .Size=sizeof(Server_receiveDataInfo.buf)/sizeof(Server_receiveDataInfo.buf[0]),
};
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
void GPRS_WriteBytes(uint8_t *pbuf)    //USART1 发送AT命令
{   
    BSP_USART_WriteBytes(BSP_USART1,pbuf,strlen((char *)pbuf));
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
    uint8_t i=0;
    pbuf=g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf;
    for(i=0;i<strlen((const char*)pbuf);i++)
    {
        if(pbuf[i]==',')
        {
            Server_receiveDataInfo.buf[Server_receiveDataInfo.In].SocketNum=pbuf[i-1]-48;
            if(pbuf[i+3]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=pbuf[i+2]-48;
            }
            else if(pbuf[i+4]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=(pbuf[i+2]-48)*10+(pbuf[i+3]-48); 
            }
            else if(pbuf[i+5]=='\r')
            {
                Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Len=(pbuf[i+2]-48)*100+(pbuf[i+3]-48)*10+(pbuf[i+4]-48);   
            }
        }
        if(pbuf[i]=='\n')
        {
            strcpy((char *)Server_receiveDataInfo.buf[Server_receiveDataInfo.In].Buf,(const char *)&pbuf[i+1]);
        }
    }    
}
void GPRS_SendData(uint8_t * pbuf,uint8_t length,uint8_t mux) // 发送数据接口
{
    sprintf((char*)g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.In].Buf,"%s",(const char *)pbuf);
    g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.In].Len=length;
    g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.In].Mux=mux;
    g_Machine_TransmitBuf.In++;
    g_Machine_TransmitBuf.In %= sizeof (g_Machine_TransmitBuf.Buf)/sizeof(g_Machine_TransmitBuf.Buf[0]);
    g_Machine_TransmitBuf.Count++;    
    
}

/**
* @}
*/

