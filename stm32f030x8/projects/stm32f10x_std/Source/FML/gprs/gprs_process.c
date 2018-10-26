/**
**************************************************************************************************
* @file        gprs_process.c
* @author
* @version   v0.1.0
* @date        
* @brief
**************************************************************************************************
* @attention
*
**************************************************************************************************
*/
#include "gprs_process.h"
#include "gprs_commond.h"
#include "gprs_cache.h"
#include "bsp_gprs.h"
#include "gprs_task.h"
#include "self_def.h"
#include "system_info.h"
#include "stm32_bsp_conf.h"
#include "osal.h"
#include "clog.h"
#include "cshell.h"
#include "zsproto_package_process.h"
/**
* @addtogroup    XXX 
* @{  
*/

/**
* @addtogroup    gprs_process_Modules 
* @{  
*/

/**
* @defgroup      gprs_process_IO_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_process_Macros_Defines 
* @brief         
* @{  
*/
     
#define GPRS_AT_CMD_SENDBUF_MAX   300

/* 常规命令重发次数 */
#define GPRS_ATCMD_RETRYCOUNT_MAX   5

/* CSQ命令查询次数 */
#define GPRS_ATCMD_CSQ_RETRYCOUNT_MAX       30

#define GPRS_ATCMD_CREG_RETRYCOUNT_MAX      30

#define GPRS_ATCMD_CGREG_RETRYCOUNT_MAX     30

#define GPRS_ATCMD_QIOPEN_RETRYCOUNT_MAX    30
/* 常规命令超时时间*/
#define GPRS_TIMEOUT_TICKS              1000 // ms
/* 查询发送超时时间 */
#define GPRS_CMD_QISEND_TICKS           5000 // ms
/* 查询sim卡超时时间 */
#define GPRS_CMD_CPIN_TIMEOUT_TIME      2000 // ms

/* 关闭GPRS场景超时时间 */
#define GPRS_CMD_QIDEACT_TIMEOUT_TIME   40000 // ms

/* 激活GPRS场景超时时间 */
#define GPRS_CMD_QIACT_TIMEOUT_TIME     60000 // ms 

/* 连接服务器超时时间 */
#define GPRS_CMD_QIOPEN_TIMEOUT_TIME    5000 // ms

/* GPRS 断电时间；当GPRS长时间无法联网时，先断电，然后重新上电 */
#define GPRS_POWEROFF_HOLD_TIME         4000 // ms

/* GPRS 上电延时时间；GPRS先上电，上电后延时若干ms再进行其他操作 */
#define GPRS_POWERON_DELAY_TIME         5000 // ms

/* 开机键保持时间 */
#define GPRS_POWERKEY_HOLD_TIME         4000 // ms

/* 连续网络异常时间，当超过这个时间，模块将尝试断电重启 */
#define GPRS_CONTINUE_EXCEPTION_TIME    600000 // ms


#define GPRS_SENT_NOACK_COUT_MAX        3
/**
* @}
*/

/**
* @defgroup      gprs_process_Constants_Defines 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_process_Private_Types
* @brief         
* @{  
*/
typedef struct
{
    uint8_t  Socket_En;
    Socket_Connectway Conncet_way;
    uint8_t  Domain[20];
    uint8_t  IP_Address[16];
    uint32_t Server_port;
    uint8_t  Mux;
    uint8_t  LinkState;
}SocketSource_Info_t;

typedef struct
{
    uint8_t  Socket_En;
    Socket_Connectway Conncet_way;
    uint8_t  *Domain;
    uint8_t  *IP_Address;
    uint32_t Server_port;
    uint8_t  LinkState;
    uint8_t  Mux;
}CurSocket_Info_t;


typedef struct
{
    GPRSState_t state;                       // GPRS的状态
    uint8_t retry_count;                     // 重发次数，仅用于初始化命令，不包括socket相关命令
    uint8_t cur_socket_open_failed_count;                // 发送确认检查无确认次数
    SocketState_t socketline_state;
    uint32_t ticks;                          // 命令发送时间，用于超时判断
    uint32_t busyticks;                      // 命令发送时间，用于超时判断
    uint8_t rssi;                            // 信号强度
    uint8_t rssi_count;                      // 信号查询次数
    uint8_t scoket_count;                    // 目前Socket的数量
    CurSocket_Info_t cur_socket_info;        // 目前正在连接的socket信息
    SocketSource_Info_t Socket_Info_t[3];    // 服务器信息
 //   SocketSource_Info_t *pSocket_Info;
    uint8_t moudle_status;                   // 模块开关机状态
    GprsExtraReq extra_request;
    uint8_t qisack_count;
    uint8_t CurQISACKSocketNumber;
}GPRS_CB_t;

typedef struct
{
    GPRSState_t State[10];
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}GPRSMsgQueue_t;
/**
* @}
*/



/**
* @defgroup      gprs_process_Private_Variables 
* @brief         
* @{  
*/

static GPRS_CB_t    s_GPRS_CB = 
{
    .state = GPRSState_PowerOn_Req,
    .retry_count = GPRS_ATCMD_RETRYCOUNT_MAX,
    .ticks = 0,
    .rssi = 0xFF,
    .rssi_count=0,
    .socketline_state=SocketState_Busy,
    .cur_socket_open_failed_count = 0,
    .scoket_count=0,
	.Socket_Info_t=
    {
        {   .Socket_En=0,.LinkState=GPRSLinkState_Lost,},
        {   .Socket_En=0,.LinkState=GPRSLinkState_Lost,},
        {   .Socket_En=0,.LinkState=GPRSLinkState_Lost,},
    },
    .moudle_status=1,
    .qisack_count=0,
    .CurQISACKSocketNumber=0,
//    .cur_sent_len = 0,
//    .prev_sent_len = 0,
//    .cur_noack_len = 0,
//    .prev_noack_len = 0,
};
static GPRSMsgQueue_t s_GPRSMsgQueue=
{
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(s_GPRSMsgQueue.State)/sizeof(s_GPRSMsgQueue.State[0]),
};
//static uint8_t s_Gprs_UpdateRssiCount=0;
/**
* @}
*/
/**
* @defgroup      gprs_process_Public_Variables 
* @brief         
* @{  
*/

/**
* @}
*/

/**
* @defgroup      gprs_process_Private_FunctionPrototypes 
* @brief         
* @{  
*/
static void gprs_check_process(void);
static void gprs_idle_process(void);
static void gprs_add_state(GPRSState_t next_state);
static void gprs_update_state(void);
static void gprs_update_request(void);
static void gprs_update_socket(void);
static void gprs_msg_queue_clear(void);
static void gprs_socket_deinit(void);
/**
* @}
*/

/**
* @defgroup      gprs_process_Functions 
* @brief         
* @{
*/
static void gprs_add_state(GPRSState_t next_state)
{
    if (s_GPRSMsgQueue.Count < s_GPRSMsgQueue.Size)
    {
        s_GPRSMsgQueue.State[s_GPRSMsgQueue.In++] = next_state;
        s_GPRSMsgQueue.In %= s_GPRSMsgQueue.Size;
        s_GPRSMsgQueue.Count++;
    }
}
static void gprs_update_state(void)
{
    if(s_GPRSMsgQueue.Count>0)
    {
        s_GPRS_CB.state= s_GPRSMsgQueue.State[s_GPRSMsgQueue.Out++];
        s_GPRSMsgQueue.Out %= s_GPRSMsgQueue.Size;
        s_GPRSMsgQueue.Count--;
    }
}
static void gprs_update_request(void)    //
{   
    if(g_Machine_TransmitBuf.Count>0&&s_GPRS_CB.extra_request==GPRS_None_Req)
    {    
        if(s_GPRS_CB.Socket_Info_t[g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Mux].LinkState==GPRSLinkState_Establish)
        {
            s_GPRS_CB.extra_request=GPRS_SendData_Req;
        }
    }
    else if(s_GPRS_CB.qisack_count>0&&s_GPRS_CB.extra_request==GPRS_None_Req)
    {   
        s_GPRS_CB.extra_request=GPRS_QISACK_Req;
    }    
    else if(s_GPRS_CB.rssi_count>0&&s_GPRS_CB.extra_request==GPRS_None_Req)
    {
        s_GPRS_CB.extra_request=GPRS_CheckRssi_Req;
    }
    switch(s_GPRS_CB.extra_request)
    {
        case GPRS_None_Req:
        {   
            break;
        }
        case GPRS_SendData_Req:
        {   
            gprs_add_state(GPRSState_QISEND_Req);
            s_GPRS_CB.extra_request=GPRS_Busy_Req;
            break;
        }
        case GPRS_CheckRssi_Req:
        {
            gprs_add_state(GPRSState_CSQ_Req);
            s_GPRS_CB.extra_request=GPRS_Busy_Req;
            break;
        }
        case GPRS_QISACK_Req:
        {
            gprs_add_state(GPRSState_QISACK_Req);
            s_GPRS_CB.extra_request=GPRS_Busy_Req;
            break;
        }
        case GPRS_Busy_Req:
        {
            break;
        }
        default:
            break;
    }
}
static void gprs_update_socket(void)  //更新目前socket信息
{	
    static uint8_t count=0;
    if(s_GPRS_CB.socketline_state==SocketState_Idle)
    {   
        if(count== s_GPRS_CB.scoket_count)
        {
            count=0;
        }
        if(s_GPRS_CB.Socket_Info_t[count].Socket_En=1&&s_GPRS_CB.Socket_Info_t[count].LinkState==GPRSLinkState_Lost)
        {
            s_GPRS_CB.socketline_state=SocketState_Busy;
            s_GPRS_CB.cur_socket_info.Conncet_way=s_GPRS_CB.Socket_Info_t[count].Conncet_way;
            s_GPRS_CB.cur_socket_info.Domain=s_GPRS_CB.Socket_Info_t[count].Domain;
            s_GPRS_CB.cur_socket_info.IP_Address=s_GPRS_CB.Socket_Info_t[count].IP_Address;
            s_GPRS_CB.cur_socket_info.Server_port=s_GPRS_CB.Socket_Info_t[count].Server_port;
            s_GPRS_CB.cur_socket_info.Mux=s_GPRS_CB.Socket_Info_t[count].Mux;
            gprs_add_state(GPRSState_QIDNSIP_Req);
        }
        count++;
    }
}
static void gprs_check_process(void)
{   
    switch (s_GPRS_CB.state)
    {   
        case GPRSState_AT_Resp:
        {   
            if (Gprs_ACK_Check("OK",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_ATE_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_ATE_Resp:
        {
            if (Gprs_ACK_Check("OK",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_CPIN_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_CPIN_Resp:
        {
            if (Gprs_ACK_Check("READY",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                //gprs_add_state(GPRSState_CSQ_Req);
                gprs_add_state(GPRSState_CREG_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_CREG_Resp:
        {
            if (Gprs_ACK_Check("0,1",PARTCHECK)==CHECKRIGHT||
                Gprs_ACK_Check("0,5",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_CGREG_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            } 
            break;
        }
        case GPRSState_CSQ_Resp:
        {   
            uint8_t i;
            uint8_t *p;
          //  uint8_t csqbuf[20],buflen;
            if(Gprs_ACK_Check("OK",PARTCHECK)==CHECKRIGHT)
            {   
                p=g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf;
                for(i=0;i<strlen((char const*)p);i++)
                {
                    if(p[0]!=':')
                    {
                        p++;
                    }
                    else 
                    {
                        break;
                    }
                }
                if(p[3]==0x2C)
                {
                    s_GPRS_CB.rssi=(p[2]-48);
                }
                else
                {
                    s_GPRS_CB.rssi=(p[2]-48)*10+(p[3]-48);
                }
                s_GPRS_CB.rssi_count--;
                s_GPRS_CB.extra_request=GPRS_None_Req;  
                s_GPRS_CB.state = GPRSState_Idle;
//                buflen=sprintf((char *)csqbuf,"+CSQ:%d\r\n",s_GPRS_CB.rssi);
//                i=ZSProto_CSQPackageMake(csqbuf,buflen);
//                BSP_USART_WriteBytes(BSP_USART2,csqbuf,i);
                DEBUG("[GPRS] Rssi:%d\r\n",s_GPRS_CB.rssi);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
          break;
        }
        case GPRSState_CGREG_Resp:
        {
            if (Gprs_ACK_Check("0,1",PARTCHECK)==CHECKRIGHT||
                Gprs_ACK_Check("0,5",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_CGATT_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_CGATT_Resp:
        {
            if (Gprs_ACK_Check("1",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_QIMUX_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QIMUX_Resp:
        {   
            uint8_t check_result;
            check_result=Gprs_ACK_Check("OK",PARTCHECK);
            if (check_result==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                 s_GPRS_CB.socketline_state=SocketState_Idle;
                g_SystemInfo.Gprs_Init_Status=Gprs_Init_Complete;
                INFO("[GPRS] GPRS Init OK\r\n");                
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            else if(check_result==CHECKERROR)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_QIMUXE_Req);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        } 
        case GPRSState_QIMUXE_Resp:
        {
            if (Gprs_ACK_Check("1",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.socketline_state=SocketState_Idle;
                g_SystemInfo.Gprs_Init_Status=Gprs_Init_Complete;          
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QIDNSIP_Resp:
        {   
            if (Gprs_ACK_Check("OK",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_QIOPEN_Req);            
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QIOPEN_Resp:
        { 
            uint8_t check_result;
            check_result=Gprs_ACK_Check("CONNECT OK",PARTCHECK);            
            if (check_result==CHECKRIGHT)
            {   
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.socketline_state=SocketState_Idle;
                s_GPRS_CB.Socket_Info_t[s_GPRS_CB.cur_socket_info.Mux].LinkState=GPRSLinkState_Establish;
                DEBUG("[GPRS] Socket:%d Connect OK\r\n",s_GPRS_CB.cur_socket_info.Mux);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QICLOSE_Resp:
        {
            if (Gprs_ACK_Check("CLOSE OK",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.Socket_Info_t[s_GPRS_CB.cur_socket_info.Mux].LinkState=GPRSLinkState_Lost;
                DEBUG("[GPRS] Socket:%d Close OK\r\n",s_GPRS_CB.cur_socket_info.Mux);
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QISEND_Resp:
        {
            if (Gprs_ACK_Check(">",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_QISEND_Data_Req;      
                GprsTask_Send_Event(GPRS_TASK_LOOP_EVENT);
            }
            break;
        }
        case GPRSState_QISEND_Data_Resp:
        {
            if (Gprs_ACK_Check("SEND OK",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.extra_request=GPRS_None_Req;
                g_Machine_TransmitBuf.Out++;
                g_Machine_TransmitBuf.Out %= g_Machine_TransmitBuf.Size;
                g_Machine_TransmitBuf.Count--;  
                DEBUG("[GPRS] SEND OK\r\n");
            }
            break;
        }  
        case GPRSState_QISACK_Resp:
        {
            if (Gprs_ACK_Check("QIACK:",PARTCHECK)==CHECKRIGHT)
            {
                s_GPRS_CB.retry_count = 0;
//                char *p_sent = NULL;
//                char *p_noack = NULL;
//                uint32_t cur_sent_len = 0;
//                uint32_t cur_noack_len = 0;

                /* 查找已发长度 */
//                if ((p_sent = CString_Search(p,':',1)) != NULL)
//                {
//                    p_sent += 2; // 跳过冒号和空格，指向实际数据位置
//                    /* 截取出已发长度字段，并保存后续字符地址 */
//                    if ((p_noack = CString_Split(p_sent,',')) != p_sent) 
//                    {
//                        cur_sent_len = atoi(p_sent);
//                    }
//                    else
//                    {
//                        break;
//                    }
//                }
                /* 查找无ACK长度 */
//                if ((p_noack = CString_Search(p_noack,',',1)) != NULL)
//                {
//                    p_noack += 2; // 跳过逗号和空格，指向实际数据位置
//                    if (CString_Split(p_noack,0x0D) != NULL)
//                    {
//                        cur_noack_len = atoi(p_noack); // 截取无应答数据长度
//                        DEBUG("[GPRS] sent=%d,unack=%d\r\n", cur_sent_len,cur_noack_len);
//                        gprs_update_qiack_data(s_GPRS_CB.CurQISACKSocketNumber, cur_sent_len, cur_noack_len);
//                        s_GPRS_CB.state = GPRSState_Idle;
//                    }
//                }
            }
        }
        default:
           break;
        }
}
static void gprs_idle_process(void)
{
    gprs_update_state();
    gprs_update_request();
    gprs_update_socket();
}
static void gprs_msg_queue_clear(void)
{   
   s_GPRSMsgQueue.In = 0;
   s_GPRSMsgQueue.Out = 0;
   s_GPRSMsgQueue.Count = 0;
}
static void gprs_socket_deinit(void)
{
    uint8_t i;
    for(i=0;i<s_GPRS_CB.scoket_count;i++)
    {
        s_GPRS_CB.Socket_Info_t[i].LinkState=GPRSLinkState_Lost;
    }
}
void GPRS_Loop_Process(void)
{
    static char send_buf[100];
    switch (s_GPRS_CB.state)
    {
        case GPRSState_PowerOff_Req:
        {
            gprs_msg_queue_clear();
            gprs_socket_deinit();
            s_GPRS_CB.state = GPRSState_PowerOff_Resp;
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            BSP_GPRS_PowerOff();
            INFO("[GPRS] Moudle start power off\r\n");
            break;
        }
        case GPRSState_PowerOff_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_POWEROFF_HOLD_TIME)
            {
                s_GPRS_CB.state = GPRSState_PowerOn_Req;
            }
            break;
        }
        case GPRSState_PowerOn_Req:
        {   
            //gprs_socket_state_reset_all();
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_PowerOn_Resp;
            BSP_GPRS_PowerOn();
            INFO("[GPRS] Moudle start power on\r\n");
            break;
        }
        case GPRSState_PowerOn_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_POWERON_DELAY_TIME)
            {
                s_GPRS_CB.state = GPRSState_PowerKey_Req;
            }
            break;
        }
        case GPRSState_PowerKey_Req:
        {
            BSP_GPRS_PowerKeyLow();
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_PowerKey_Resp;
            INFO("[GPRS] Gprs start boot \r\n");
            break;
        }
        case GPRSState_PowerKey_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_POWERKEY_HOLD_TIME)
            {   
                s_GPRS_CB.moudle_status=~s_GPRS_CB.moudle_status;
                BSP_GPRS_PowerKeyHigh();  //保持M26引脚持续高电平
                s_GPRS_CB.state = GPRSState_Idle;
                gprs_add_state(GPRSState_AT_Req);
            }
            break;
        }
        case GPRSState_AT_Req:
        {   
            GPRS_WriteBytes("AT\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_AT_Resp;
            s_GPRS_CB.socketline_state=SocketState_Busy;
            s_GPRS_CB.extra_request=GPRS_None_Req;
            gprs_msg_queue_clear();
            gprs_socket_deinit(); 
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:AT,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;            
        }
        case GPRSState_AT_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD AT timeout\r\n");
                if (s_GPRS_CB.retry_count >= 20)
                {
                    s_GPRS_CB.retry_count = 0;
                    s_GPRS_CB.state = GPRSState_PowerOff_Req;
                    gprs_socket_deinit();
                }
                else
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                }
            }
            break;
        }
        case GPRSState_ATE_Req:
        {
            GPRS_WriteBytes("ATE0\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_ATE_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:ATE,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_ATE_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD ATE timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_ATE_Req;
                }
            }
            break;
        }
        case GPRSState_CPIN_Req:
        {
            GPRS_WriteBytes("AT+CPIN?\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_CPIN_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:CPIN,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_CPIN_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_CMD_CPIN_TIMEOUT_TIME)
            {
                DEBUG("[GPRS] CMD CPIN timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_CPIN_Req;
                }
            }
            break;
        }
        case GPRSState_CSQ_Req:
        {
            GPRS_WriteBytes("AT+CSQ\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_CSQ_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:CSQ\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_CSQ_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks >= GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD CSQ timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_CSQ_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_CSQ_Req;
                }
            }
            break;
        }
        case GPRSState_CREG_Req:
        {
            GPRS_WriteBytes("AT+CREG?\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_CREG_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:CREG,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_CREG_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD CREG timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_CREG_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_CREG_Req;
                }
            }
            break;
        }
        case GPRSState_CGREG_Req:
        {
            GPRS_WriteBytes("AT+CGREG?\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_CGREG_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:CGREG,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_CGREG_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD CGREG timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_CGREG_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_CGREG_Req;
                }
            }
            break;
        }
        case GPRSState_CGATT_Req:
        {
            GPRS_WriteBytes("AT+CGATT?\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_CGATT_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:CREG,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }        
        case GPRSState_CGATT_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD CREG timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_CREG_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_CGATT_Req;
                }
            }
            break;
        }        
        case GPRSState_QIMUX_Req:
        {
            GPRS_WriteBytes("AT+QIMUX=1\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QIMUX_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QIMUX,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_QIMUX_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD QIMUX timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_QIMUX_Req;
                }
            }
            break;
        }
        case GPRSState_QIMUXE_Req:
        {   
            GPRS_WriteBytes("AT+QIMUX?\r\n");
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QIMUXE_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QIMUXE,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_QIMUXE_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {            
                DEBUG("[GPRS] CMD QIMUXE timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_QIMUXE_Req;
                }
            }
            break;
        }
        case GPRSState_QIDNSIP_Req:
        {   
            if(s_GPRS_CB.cur_socket_info.Conncet_way==IP_Connect)
            {
                GPRS_WriteBytes("AT+QIDNSIP=0\r\n");
            }
            else if(s_GPRS_CB.cur_socket_info.Conncet_way==Domain_Connect)
            {
                GPRS_WriteBytes("AT+QIDNSIP=1\r\n");
            }
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QIDNSIP_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QIDNSIP,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_QIDNSIP_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD QIDNSIP timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_AT_Req;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_QIDNSIP_Req;
                }
            }
            break;
        }
        case GPRSState_QIOPEN_Req:
        {
            if(s_GPRS_CB.cur_socket_info.Conncet_way==IP_Connect)
            {
                 sprintf(send_buf,"AT+QIOPEN=%d,\"TCP\",\"%s\",\"%d\"\r\n",s_GPRS_CB.cur_socket_info.Mux,s_GPRS_CB.cur_socket_info.IP_Address,s_GPRS_CB.cur_socket_info.Server_port);
                 GPRS_WriteBytes((uint8_t *)send_buf);
            }
            else if(s_GPRS_CB.cur_socket_info.Conncet_way==Domain_Connect)
            {
                 sprintf(send_buf,"AT+QIOPEN=%d,\"TCP\",\"%s\",\"%d\"\r\n",s_GPRS_CB.cur_socket_info.Mux,s_GPRS_CB.cur_socket_info.Domain,s_GPRS_CB.cur_socket_info.Server_port);
                 GPRS_WriteBytes((uint8_t *)send_buf);
            }
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QIOPEN_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QIOPEN,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        }
        case GPRSState_QIOPEN_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_CMD_QIOPEN_TIMEOUT_TIME)
            {
                    s_GPRS_CB.cur_socket_open_failed_count++;
                    if(s_GPRS_CB.cur_socket_open_failed_count==3)
                    {   
                        s_GPRS_CB.cur_socket_open_failed_count=0;
                        s_GPRS_CB.socketline_state=SocketState_Idle;
                    }
                    
                    else
                    {
                        gprs_add_state(GPRSState_QICLOSE_Req);
                        gprs_add_state(GPRSState_QIDNSIP_Req);
                    }
                    s_GPRS_CB.retry_count=0;
                    s_GPRS_CB.state = GPRSState_Idle;
            }
            break;
        }
        case GPRSState_QICLOSE_Req:
        {   
            sprintf(send_buf,"AT+QICLOSE=%d\r\n",s_GPRS_CB.cur_socket_info.Mux);
            GPRS_WriteBytes((uint8_t *)send_buf);
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QICLOSE_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QICLOSE,retry(%d)\r\n",s_GPRS_CB.retry_count);
            break;
        } 
        case GPRSState_QICLOSE_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD QICLOSE timeout\r\n");
                if (s_GPRS_CB.retry_count >= GPRS_ATCMD_RETRYCOUNT_MAX)
                {
                    s_GPRS_CB.state = GPRSState_Idle;
                    s_GPRS_CB.retry_count=0;
                }
                else 
                {
                    s_GPRS_CB.state = GPRSState_QICLOSE_Req;
                }
            }
            break;
        }
        case GPRSState_QISEND_Req:
        {
            sprintf(send_buf,"AT+QISEND=%d,%d\r\n",g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Mux,g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Len);
            GPRS_WriteBytes((uint8_t *)send_buf);
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QISEND_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:%s\r\n",send_buf);
            break;
        }
        case GPRSState_QISEND_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {   
                s_GPRS_CB.Socket_Info_t[g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Mux].LinkState=GPRSLinkState_Lost;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.extra_request=GPRS_None_Req;
                s_GPRS_CB.retry_count=0;
            }
            break;
        }
        case GPRSState_QISEND_Data_Req:
        {
            sprintf(send_buf,"%s",g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Buf);
            s_GPRS_CB.state = GPRSState_QISEND_Data_Resp;
            GPRS_WriteBytes((uint8_t *)send_buf);
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:%s\r\n",send_buf);
            break;
        }
        case GPRSState_QISEND_Data_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > 10000)
            {
                DEBUG("[GPRS] CMD SendData timeout\r\n");
                s_GPRS_CB.Socket_Info_t[g_Machine_TransmitBuf.Buf[g_Machine_TransmitBuf.Out].Mux].LinkState=GPRSLinkState_Lost;
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.extra_request=GPRS_None_Req;
                s_GPRS_CB.retry_count=0;
            }
            break;
        }        

        case GPRSState_QISACK_Req:
        {
            sprintf((char *)send_buf, "AT+QISACK=%d\r\n", s_GPRS_CB.CurQISACKSocketNumber);
            GPRS_WriteBytes((uint8_t *)send_buf);
            s_GPRS_CB.ticks = OS_Clock_GetSystemClock();
            s_GPRS_CB.state = GPRSState_QISACK_Resp;
            s_GPRS_CB.retry_count++;
            DEBUG("[GPRS] CMD:QISACK(%d)\r\n", s_GPRS_CB.CurQISACKSocketNumber);
            break;
        }
        case GPRSState_QISACK_Resp:
        {
            if (OS_Clock_GetSystemClock() - s_GPRS_CB.ticks > GPRS_TIMEOUT_TICKS)
            {
                DEBUG("[GPRS] CMD QISACK timeout\r\n");
                s_GPRS_CB.state = GPRSState_Idle;
                s_GPRS_CB.retry_count=0;
                s_GPRS_CB.extra_request=GPRS_None_Req;
            }
            break;
        }
        case GPRSState_Idle:
        {
            gprs_idle_process();
            break;
        }
        default:
        {
            break;
        }
    }
}
void GPRS_ACK_Process(void)
{   
    uint8_t muxnum;
    if(g_AT_ReceiveBuf.Count>0)
    {   
        if( strstr((char *)g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf,"CLOSED")!=NULL&&strstr((char *)g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf,"OK")==NULL)
        {   
            muxnum=g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf[2]-48;
            s_GPRS_CB.Socket_Info_t[muxnum].LinkState=GPRSLinkState_Lost;
            DEBUG("[GPRS] Socket:%d Closed\r\n",muxnum);
            g_AT_ReceiveBuf.Count--;
            g_AT_ReceiveBuf.Out++;
            g_AT_ReceiveBuf.Out %=sizeof (g_AT_ReceiveBuf.Buf)/sizeof(g_AT_ReceiveBuf.Buf[0]);
        }
        else if( strstr((char *)g_AT_ReceiveBuf.Buf[g_AT_ReceiveBuf.Out].Buf,"RECEIVE")!=NULL)
        {  
            Gprs_GetSocketAndLength();
            Server_receiveDataInfo.In++;
            Server_receiveDataInfo.Count++;
            Server_receiveDataInfo.In %=Server_receiveDataInfo.Size;
            g_AT_ReceiveBuf.Count--;
            g_AT_ReceiveBuf.Out++;
            g_AT_ReceiveBuf.Out %=sizeof (g_AT_ReceiveBuf.Buf)/sizeof(g_AT_ReceiveBuf.Buf[0]);
        }
        else
        {
            gprs_check_process();
            g_AT_ReceiveBuf.Count--;
            g_AT_ReceiveBuf.Out++;
            g_AT_ReceiveBuf.Out %=g_AT_ReceiveBuf.Size;
        }
    }
}
void Gprs_Add_Sockets(Socket_Connectway connectway,uint8_t * address,uint32_t port)  //添加Sokcet的接口
{  
    s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Socket_En=1;
    s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Conncet_way=connectway;
    if(s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Conncet_way==0)
    {
        sprintf((char *)s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].IP_Address,(const char *)address);
    }
    else 
    {
        sprintf((char *)s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Domain,(const char *)address);
    }
    s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Server_port=port;
    s_GPRS_CB.Socket_Info_t[s_GPRS_CB.scoket_count].Mux=s_GPRS_CB.scoket_count;
    s_GPRS_CB.scoket_count++;
}
void Gprs_UpdateRssi()   //更新信号强度
{   
    if(g_SystemInfo.Gprs_Init_Status==Gprs_Init_Complete)
    {
        s_GPRS_CB.rssi_count++;
    }
}
void Gprs_Cmd_QIACK()   //更新信号强度
{   
    uint8_t i;
    for(i=0;i<s_GPRS_CB.scoket_count;i++)
    {
        if(s_GPRS_CB.Socket_Info_t[i].LinkState==GPRSLinkState_Establish)
        {
            s_GPRS_CB.qisack_count++;
            break;
        }
    }
}