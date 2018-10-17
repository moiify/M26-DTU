/**
 **************************************************************************************************
 * @file        ModbusRTU_Slave.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention 
 * resgister    Function
 * 0            AD
 * 1            AD
 * 2            AD
 * 3            
 * 4            
 * 5            
 * 6            
 * 7            
 * 8            
 * 9            
 * 10           
 * 11           
 * 12           
 * 13           
 * 14           
 * 15           
 * 16           
 * 17           
 * 18           
 * 19           Slave.ID
 **************************************************************************************************
 */
#include "ModbusRTU_Slave.h"
#include "stm32f0xx.h"
#include "ModbusHardwareInit.h"
#include "ModbusCRC.h"
#include "BSP_EqpOption.h"
#include "user_task.h"
#include <string.h>
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ModbusRTU_Slave_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusRTU_Slave_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Private_Types
 * @brief         
 * @{  
 */



/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t Uart2RBuf[20];
uint8_t Uart2RBuf_Ptr=0;
RingArray Modbus;
SlaveStruct_t Slave;
/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void rBufToRing(void);
static void MBFunction_03(void); 
static void MBFunction_04(void);
static void MBFunction_05(void);
static void MBFunction_06(void);
/**
 * @}
 */

/**
 * @defgroup      ModbusRTU_Slave_Functions 
 * @brief         
 * @{  
 */

void ModbusSlaveInit(void) //Slave ID startaddr endaddr init
{
    if(ReadOption()<0)
    {
        Slave.ID=0x02;        
    }
    Slave.StartAddr=0;
    Slave.EndAddr=19;
}

void ModbusRingBufInit(void)    //RingBuf init
{
	Modbus.RingCount=0;
	Modbus.RingIn=0;
	Modbus.RingOut=0;
	Modbus.RingSize=5;
}


void ModbusUartIRQn(void)       
{
    USART_ClearITPendingBit(USART1, USART_IT_ORE);
	if((USART_GetITStatus(USART1, USART_IT_RXNE))==1)	//juge interrupt is RNXE :1;
	{
		TIM_Cmd(TIM3, DISABLE);
		TIM_SetCounter( TIM3, 0);
		uint8_t tmp = USART_ReceiveData(USART1);
		if(Uart2RBuf_Ptr<sizeof(Uart2RBuf))
		{
			Uart2RBuf[Uart2RBuf_Ptr++]= tmp;
		}
		TIM_Cmd(TIM3, ENABLE);
	}
}

void ModbusTimIRQn(void)
{
	if(TIM_GetITStatus( TIM3, TIM_IT_Update)!= RESET)
	{
		TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
		TIM_Cmd(TIM3, DISABLE);
		rBufToRing();
	}
}

void rBufToRing(void)   
{
	memcpy(Modbus.RingData[Modbus.RingIn].Buf,Uart2RBuf,Uart2RBuf_Ptr);
	Modbus.RingData[Modbus.RingIn].Len=Uart2RBuf_Ptr;
	Uart2RBuf_Ptr=0;

	Modbus.RingIn++;
	Modbus.RingIn%=Modbus.RingSize;
	Modbus.RingCount++;
	Modbus.RingCount%=10;
}

void ModbusDataProcess(void)
{
	if(Modbus.RingCount>0)              //if ringbuf has data
	{
        if (Modbus.RingData[Modbus.RingOut].Buf[0] == Slave.ID)     //if askdata is slaveID
        {           
            if (checkCRC(Modbus.RingData[Modbus.RingOut].Buf, Modbus.RingData[Modbus.RingOut].Len) == 0x0000) //check CRC
            {
               switch (Modbus.RingData[Modbus.RingOut].Buf[1])  //choose function
               {
                   case 0x03:MBFunction_03(); break;
                   case 0x04:MBFunction_04(); break;     
                   case 0x05:MBFunction_05(); break;
                   case 0x06:MBFunction_06(); break;
                   default:break;
               }
            }
        }
        
        Modbus.RingOut++;                           //deal with ringbuf
        Modbus.RingOut %= Modbus.RingSize;
        Modbus.RingCount--;
        
	}

}

void MB_WirteRegister(uint8_t Register, uint16_t Addr,uint16_t Data)       //Slave wirte register
{
    Slave.Register[Register].Addr[Addr].DataI = Data;
}

uint16_t MB_ReadRegister(uint8_t Register, uint16_t Addr)                   //Slave read register
{
    return Slave.Register[Register].Addr[Addr].DataI;
}


void MBFunction_03(void)
{
    static uint16_t addr=0;
    static uint8_t ask_data_count=0;
    static uint8_t modbus_send_buf[20];
    static uint8_t i=0;
    static uint16_t crctemp=0;
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    ask_data_count =  (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[4] * 256 + Modbus.RingData[Modbus.RingOut].Buf[5]);
    if ((addr >= Slave.StartAddr) && (addr + ask_data_count <= Slave.EndAddr))
    {
        for (i = 0; (i < ask_data_count) ; i++)
        {
            modbus_send_buf[3+i*2]= (MB_ReadRegister(MBREGISTERHOLIDING, addr+i))>>8;           
            modbus_send_buf[3+i*2+1]= (uint8_t)(MB_ReadRegister(MBREGISTERHOLIDING, addr+i)&0x00ff);
        }
        modbus_send_buf[0] = Slave.ID;
        modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
        modbus_send_buf[2] = ask_data_count*2;
        crctemp = ModbusCRC(modbus_send_buf,ask_data_count*2+3);
        modbus_send_buf[ask_data_count*2+3]=crctemp>>8;
        modbus_send_buf[ask_data_count*2+3+1]=(uint8_t)(crctemp&0x00ff);
        ModbusSend(modbus_send_buf,ask_data_count*2+3+2);
    }
}
void MBFunction_04(void)
{
    static uint16_t addr=0;
    static uint8_t ask_data_count=0;
    static uint8_t modbus_send_buf[20];
    static uint8_t i=0;
    static uint16_t crctemp=0;
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    ask_data_count =  (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[4] * 256 + Modbus.RingData[Modbus.RingOut].Buf[5]);
    if ((addr >= Slave.StartAddr) && (addr + ask_data_count <= Slave.EndAddr))
    {
        for (i = 0; (i < ask_data_count) ; i++)
        {
            modbus_send_buf[3+i*2]= (MB_ReadRegister(MBREGISTERINPUT, addr+i))>>8;           
            modbus_send_buf[3+i*2+1]= (uint8_t)(MB_ReadRegister(MBREGISTERINPUT, addr+i)&0x00ff);
        }
        modbus_send_buf[0] = Slave.ID;
        modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
        modbus_send_buf[2] = ask_data_count*2;
        crctemp = ModbusCRC(modbus_send_buf,ask_data_count*2+3);
        modbus_send_buf[ask_data_count*2+3]=crctemp>>8;
        modbus_send_buf[ask_data_count*2+3+1]=(uint8_t)(crctemp&0x00ff);
        ModbusSend(modbus_send_buf,ask_data_count*2+3+2);
    }
}

void MBFunction_05(void)
{
    static uint16_t addr=0;
    static uint16_t crctemp=0;
    static uint16_t data=0;
    static uint8_t modbus_send_buf[20];
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    data = Modbus.RingData[Modbus.RingOut].Buf[4]*256 + Modbus.RingData[Modbus.RingOut].Buf[5] ;

    MB_WirteRegister(MBREGISTERCOILS, addr,data);

    modbus_send_buf[0] = Slave.ID;
    modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
    modbus_send_buf[2] = (addr & 0xff00)>>8;
    modbus_send_buf[3] = (uint8_t)(addr & 0x00ff);
    modbus_send_buf[4] = MB_ReadRegister(MBREGISTERCOILS, addr)>>8; 
    modbus_send_buf[5] = (uint8_t)(MB_ReadRegister(MBREGISTERCOILS, addr)&0x00ff);;

    crctemp = ModbusCRC(modbus_send_buf,6);
    modbus_send_buf[6]=crctemp>>8;
    modbus_send_buf[7]=(uint8_t)(crctemp&0x00ff);

    if ((addr==1)&&(MB_ReadRegister(MBREGISTERCOILS, addr)==0xff00))
    {
        UserTask_Send_Event(USER_TASK_OPEN_CMD_EVENT);
    }

    ModbusSend(modbus_send_buf,8);
}

void MBFunction_06(void)
{
    static uint16_t addr=0;
    static uint16_t crctemp=0;
    static uint16_t data=0;
    static uint8_t modbus_send_buf[20];
    addr = (uint16_t)(Modbus.RingData[Modbus.RingOut].Buf[2]*256 + Modbus.RingData[Modbus.RingOut].Buf[3]);
    data = Modbus.RingData[Modbus.RingOut].Buf[4]*256 + Modbus.RingData[Modbus.RingOut].Buf[5] ;

    MB_WirteRegister(MBREGISTERHOLIDING, addr,data);

    modbus_send_buf[0] = Slave.ID;
    modbus_send_buf[1] = Modbus.RingData[Modbus.RingOut].Buf[1];
    modbus_send_buf[2] = (addr & 0xff00)>>8;
    modbus_send_buf[3] = (uint8_t)(addr & 0x00ff);
    modbus_send_buf[4] = MB_ReadRegister(MBREGISTERHOLIDING, addr)>>8; 
    modbus_send_buf[5] = (uint8_t)(MB_ReadRegister(MBREGISTERHOLIDING, addr)&0x00ff);;

    crctemp = ModbusCRC(modbus_send_buf,6);
    modbus_send_buf[6]=crctemp>>8;
    modbus_send_buf[7]=(uint8_t)(crctemp&0x00ff);

    if ((addr==1)&&(MB_ReadRegister(MBREGISTERHOLIDING, addr)==0xff00))
    {
        UserTask_Send_Event(USER_TASK_OPEN_CMD_EVENT);
    }

    ModbusSend(modbus_send_buf,8);
}


void BSP_Switch_Open(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_6);
}

void BSP_Switch_Close(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_6);
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

