/**
 **************************************************************************************************
 * @file        BSP_LED.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "osal.h"
#include "stm32_bsp_conf.h"
#include "hal_task.h"
#include "bsp_led.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    BSP_LED_Modules 
 * @{  
 */

/**
 * @defgroup      BSP_LED_IO_Defines 
 * @brief         
 * @{  
 */
typedef struct
{
    GPIO_InstanceTypedef Pin;
    BitAction OnLevel;
    BitAction OffLevel;
}LED_IO_Typedef;

const LED_IO_Typedef LED_IO[BSP_LEDCOUNT]=
{
    {
        {RCC_AHBPeriph_GPIOC,GPIOC,GPIO_Pin_13,GPIO_Mode_OUT,GPIO_Speed_50MHz,GPIO_OType_PP,GPIO_PuPd_NOPULL},
        .OnLevel = Bit_RESET,
        .OffLevel = Bit_SET,
    },
    {
        {RCC_AHBPeriph_GPIOB,GPIOB,GPIO_Pin_0,GPIO_Mode_OUT,GPIO_Speed_50MHz,GPIO_OType_PP,GPIO_PuPd_NOPULL},
        .OnLevel = Bit_SET,
        .OffLevel =Bit_RESET,
    },
    {
        {RCC_AHBPeriph_GPIOA,GPIOA,GPIO_Pin_11,GPIO_Mode_OUT,GPIO_Speed_50MHz,GPIO_OType_PP,GPIO_PuPd_NOPULL},
        .OnLevel = Bit_SET,
        .OffLevel =Bit_RESET,
    },
};
/**
 * @}
 */

/**
 * @defgroup       BSP_LED_Macros_Defines 
 * @brief         
 * @{  
 */
/* Modes */
#define BSP_LED_MODE_OFF     0x00
#define BSP_LED_MODE_ON      0x01
#define BSP_LED_MODE_BLINK   0x02
#define BSP_LED_MODE_FLASH   0x04
/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       BSP_LED_Private_Types
 * @brief         
 * @{  
 */
typedef struct {
  uint8_t mode;       /* Operation mode */
#if (defined BSP_LED_BLINK_ENABLE) && (BSP_LED_BLINK_ENABLE == TRUE)
  uint8_t todo;       /* Blink cycles left */
  uint8_t onPct;      /* On cycle percentage */
  uint16_t time;      /* On/off cycle time (msec) */
  uint32_t next;      /* Time for next change */
  uint8_t preBlinkState;
#endif
} BSPLedControl_t;
/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Private_Variables 
 * @brief         
 * @{  
 */
static BSPLedControl_t s_BSPLedControlTable[BSP_LEDCOUNT] =
{
    {BSP_LED_MODE_OFF},
};
/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      BSP_LED_Functions 
 * @brief         
 * @{  
 */
void BSP_LED_Init()
{
    uint32_t i = 0;

    for (i=0; i<BSP_LEDCOUNT; i++)
    {
        RCC_AHBPeriphClockCmd(LED_IO[i].Pin.Clock,ENABLE);
        GPIO_Init(LED_IO[i].Pin.GPIOx,(GPIO_InitTypeDef*)&LED_IO[i].Pin.Init);
        GPIO_WriteBit(LED_IO[i].Pin.GPIOx, LED_IO[i].Pin.Init.GPIO_Pin, LED_IO[i].OffLevel);
    } 
}

/**
 * @brief    Open the specified LED
 * @param    LEDx:uint8_t  specifies the led device
 */
void BSP_LED_Open(uint8_t BSP_LEDx)
{
    GPIO_WriteBit(LED_IO[BSP_LEDx].Pin.GPIOx, LED_IO[BSP_LEDx].Pin.Init.GPIO_Pin, LED_IO[BSP_LEDx].OnLevel);
    s_BSPLedControlTable[BSP_LEDx].mode = BSP_LED_MODE_ON;
}

/**
 * @brief    Close the specified LED
 * @param    LEDx:uint8_t  specifies the led device to be close
 */
void BSP_LED_Close(uint8_t BSP_LEDx)
{
    GPIO_WriteBit(LED_IO[BSP_LEDx].Pin.GPIOx, LED_IO[BSP_LEDx].Pin.Init.GPIO_Pin, LED_IO[BSP_LEDx].OffLevel);
    s_BSPLedControlTable[BSP_LEDx].mode = BSP_LED_MODE_OFF;
}

/**
 * @brief    Toggles the specified LED
 * @param    LEDx:uint8_t  specifies the led device to be toggled
 */
void BSP_LED_Toggle(uint8_t BSP_LEDx)
{
    if (s_BSPLedControlTable[BSP_LEDx].mode & BSP_LED_MODE_ON)
    {
        BSP_LED_Close(BSP_LEDx);
    }
    else 
    {
        BSP_LED_Open(BSP_LEDx);
    }
}

void BSP_LED_Blink(uint8_t BSP_LEDx, uint8_t numBlinks, uint8_t percent, uint16_t period)
{
  #if (defined BSP_LED_BLINK_ENABLE) && (BSP_LED_BLINK_ENABLE == TRUE)
    BSPLedControl_t *ctl;

    if (percent && period)
    {
        ctl = &s_BSPLedControlTable[BSP_LEDx];

        if (ctl->mode < BSP_LED_MODE_BLINK)
        {
            ctl->preBlinkState = ctl->mode;
        }

        ctl->mode = BSP_LED_MODE_OFF;
        ctl->time = period;
        ctl->onPct = percent;
        ctl->todo = numBlinks;
        if (!numBlinks) ctl->mode |= BSP_LED_MODE_FLASH;
        ctl->next = OS_Clock_GetSystemClock();
        ctl->mode |= BSP_LED_MODE_BLINK;
        
        OS_Timer_Stop(g_HalTask_Id, HAL_TASK_LED_BLINK_EVENT);
        OS_Events_Set(g_HalTask_Id, HAL_TASK_LED_BLINK_EVENT);
    }
  #endif
}

void BSP_LED_Update()
{
  #if (defined BSP_LED_BLINK_ENABLE) && (BSP_LED_BLINK_ENABLE == TRUE)
    BSPLedControl_t *ctl;
    uint32_t time;
    uint16_t next;
    uint16_t wait;
    uint8_t pct;

    
    for (uint8_t i=0; i < BSP_LEDCOUNT; i++)
    {
        ctl = &s_BSPLedControlTable[i];
        if (ctl->mode & BSP_LED_MODE_BLINK)
        {
            time = OS_Clock_GetSystemClock();
            if (time >= ctl->next)
            {
                if (ctl->mode & BSP_LED_MODE_ON)
                {
                    pct = 100 - ctl->onPct;
                    ctl->mode &= ~BSP_LED_MODE_ON;
                    GPIO_WriteBit(LED_IO[i].Pin.GPIOx, LED_IO[i].Pin.Init.GPIO_Pin, LED_IO[i].OffLevel);

                    if (!(ctl->mode & BSP_LED_MODE_FLASH))
                    {
                        ctl->todo--;
                    }
                }
                else if ((!ctl->todo) && !(ctl->mode & BSP_LED_MODE_FLASH))
                {
                    ctl->mode ^= BSP_LED_MODE_BLINK;
                }
                else
                {
                    pct = ctl->onPct;
                    ctl->mode |= BSP_LED_MODE_ON;
                    GPIO_WriteBit(LED_IO[i].Pin.GPIOx, LED_IO[i].Pin.Init.GPIO_Pin, LED_IO[i].OnLevel);
                }

                if (ctl->mode & BSP_LED_MODE_BLINK)
                {
                    wait = (((uint32_t)pct * (uint32_t)ctl->time) / 100);
                    ctl->next = time + wait; // next change time
                }
                else
                {
                    wait = 0;
                    if (ctl->preBlinkState)
                        GPIO_WriteBit(LED_IO[i].Pin.GPIOx, LED_IO[i].Pin.Init.GPIO_Pin, LED_IO[i].OnLevel);
                    else
                        GPIO_WriteBit(LED_IO[i].Pin.GPIOx, LED_IO[i].Pin.Init.GPIO_Pin, LED_IO[i].OffLevel);

                    ctl->preBlinkState = BSP_LED_MODE_OFF;
                }
            }
            else
            {
                wait = ctl->next - time; // time left
            }

            if (!next || (wait && (wait < next)))
            {
                next = wait;
            }
        }
    }
    
    if (next)
    {
        OS_Timer_Start(g_HalTask_Id, HAL_TASK_LED_BLINK_EVENT, next);
    }
  #endif
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

