/**
 **************************************************************************************************
 * @file        ModbusRTU_Slave.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUSRTU_SLAVE_H_
#define _MODBUSRTU_SLAVE_H_
#include "stm32f0xx.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    ModbusRTU_Slave_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusRTU_Slave_Exported_Macros 
 * @{  
 */
#define MBREGISTERCOILS 0
#define MBREGISTERDISCRETEINPUT    1
#define MBREGISTERHOLIDING  2
#define MBREGISTERINPUT  3
/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Exported_Types 
 * @{  
 */
typedef struct
{
	uint8_t Buf[20];
	uint8_t Len;
}ringBuf_t;

typedef struct
{
	ringBuf_t RingData[5];
	uint8_t RingIn;
	uint8_t RingOut;
	uint8_t RingCount;
	uint8_t RingSize;
}RingArray;


typedef struct
{
    uint8_t DataType;
    uint16_t DataI;
    float DataF;
}SlaveDataStruct_t;

typedef struct
{
    SlaveDataStruct_t Addr[20];
}SlaveAddrStruct_t;



typedef struct
{
    uint8_t Addr;
    uint8_t ID;
    uint8_t ReplyStatus;
    uint8_t StartAddr;
    uint8_t EndAddr;
    SlaveAddrStruct_t Register[4];              
}SlaveStruct_t;
/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Exported_Variables 
 * @{  
 */
extern SlaveStruct_t Slave;
/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Exported_Functions 
 * @{  
 */
void ModbusUartIRQn(void);
void ModbusTimIRQn(void);
void ModbusRingBufInit(void);
void ModbusDataProcess(void);
void ModbusSlaveInit(void);
void BSP_Switch_Close(void);
void BSP_Switch_Open(void);
void MB_WirteRegister(uint8_t Register, uint16_t Addr,uint16_t Data);       //Slave wirte register
uint16_t MB_ReadRegister(uint8_t Register, uint16_t Addr);                   //Slave read register
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
