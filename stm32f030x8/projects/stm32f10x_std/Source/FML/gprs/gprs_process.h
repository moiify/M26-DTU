/**
 **************************************************************************************************
 * @file        gprs_process.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_PROCESS_H_
#define _GPRS_PROCESS_H_
#include "stm32f0xx.h"
#include "system_info.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    gprs_process_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_process_Exported_Macros 
 * @{  
 */
#define GPRS_SOCKET_COUNT_MAX   2
/**
 * @}
 */

/**
 * @defgroup      gprs_process_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_process_Exported_Types 
 * @{  
 */
typedef enum
{
    GPRSState_NULL,
    GPRSState_PowerOff_Req,
    GPRSState_PowerOff_Resp,
    GPRSState_PowerOn_Req,
    GPRSState_PowerOn_Resp,
    GPRSState_PowerKey_Req,
    GPRSState_PowerKey_Resp,
    GPRSState_AT_Req,
    GPRSState_AT_Resp,
    GPRSState_ATE_Req,
    GPRSState_ATE_Resp,
    GPRSState_IPR_Req,
    GPRSState_IPR_Resp,
    GPRSState_CPIN_Req,
    GPRSState_CPIN_Resp,
    GPRSState_CSQ_Req,
    GPRSState_CSQ_Resp,
    GPRSState_CREG_Req,
    GPRSState_CREG_Resp,
    GPRSState_CGREG_Req,
    GPRSState_CGREG_Resp,
    GPRSState_CGATT_Req,
    GPRSState_CGATT_Resp,
    GPRSState_QIFGCNT_Req,
    GPRSState_QIFGCNT_Resp,
    GPRSState_QICSGP_Req,
    GPRSState_QICSGP_Resp,
    GPRSState_QIMODE_Req,
    GPRSState_QIMODE_Resp,
    GPRSState_QIMUX_Req,
    GPRSState_QIMUX_Resp,
    GPRSState_QIMUXE_Req,
    GPRSState_QIMUXE_Resp,
    GPRSState_QIDEACT_Req,
    GPRSState_QIDEACT_Resp,
    GPRSState_QIREGAPP_Req,
    GPRSState_QIREGAPP_Resp,
    GPRSState_QIACT_Req,
    GPRSState_QIACT_Resp,
    GPRSState_QILOCIP_Req,
    GPRSState_QILOCIP_Resp,
    GPRSState_QIDNSIP_Req,
    GPRSState_QIDNSIP_Resp,
    GPRSState_QIHEAD_Req,
    GPRSState_QIHEAD_Resp,
    GPRSState_QIOPEN_Req,
    GPRSState_QIOPEN_Resp,
    GPRSState_QICLOSE_Req,
    GPRSState_QICLOSE_Resp,
    GPRSState_Idle,
    GPRSState_QISEND_Req,
    GPRSState_QISEND_Resp,
    GPRSState_QISEND_Data_Req,
    GPRSState_QISEND_Data_Resp,    
    GPRSState_QISACK_Req,
    GPRSState_QISACK_Resp,
}GPRSState_t;

typedef enum
{
    GPRSLinkState_Lost,
    GPRSLinkState_Init,
    GPRSLinkState_Connecting,
    GPRSLinkState_Establish,
}GPRSLinkState_t;

typedef enum
{
    SocketState_Busy,
    SocketState_Idle,
}SocketState_t;
typedef enum
{   
    GPRS_None_Req,
    GPRS_SendData_Req,
    GPRS_CheckRssi_Req,
    GPRS_QISACK_Req,
    GPRS_Busy_Req,
}GprsExtraReq;

/**
 * @}
 */

/**
 * @defgroup      gprs_process_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_process_Exported_Functions 
 * @{  
 */
void GPRS_Loop_Process(void);
void GPRS_ACK_Process(void);     
void Gprs_UpdateRssi(void);
void Gprs_Cmd_QIACK(void);
void Gprs_Reset_Moudle(void);
void Gprs_Add_Sockets(Socket_Info_t scoket);
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
