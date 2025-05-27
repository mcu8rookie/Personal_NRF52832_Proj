#ifndef __USR_UART_C__
#define __USR_UART_C__

#include <stdio.h>
#include "Usr_Config.h"
#include "Usr_Uart.h"
#include "nrfx_uart.h"
#include "app_uart.h"
#include "Usr_I2C.h"
#include "Usr_I2C_Sensor.h"

#if(defined(DEF_FREERTOS_EN)&&(DEF_FREERTOS_EN))
#include "FreeRTOS.h"
#include "semphr.h"
#include "Usr_Task.h"
#endif

#if 0
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\components\libraries\uart\app_uart.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\components\libraries\log\src\nrf_log_internal.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\examples\peripheral\uart\pca10040\blank\config\sdk_config.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\config\nrf52832\config\sdk_config.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nRF52832

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nRF52832\nrfx_config.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\nrfx.h


D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\drivers\include\nrfx_uart.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\drivers\include\nrfx_uart.h


D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\components\libraries\util\sdk_errors.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\drivers\src\prs\nrfx_prs.c

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nrfx_glue.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\integration\nrfx\nrfx_glue.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nrfx_glue.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\integration\nrfx\nrfx_glue.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nrfx_glue.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\modules\nrfx\templates\nRF52832\nrfx_config.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\integration\nrfx\nrfx_config.h

D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\config\nrf52832\config\sdk_config.h
D:\M14D\PersonalProject\PicoMCU\Foreign\Nordic\NRF52832_Proj\nRF5_SDK_17.1.0_ddde560\examples\peripheral\uart\pca10040\blank\config\sdk_config.h







BOARD_PCA10040 
BSP_DEFINES_ONLY 
CONFIG_GPIO_AS_PINRESET 
FLOAT_ABI_HARD 
NRF52 
NRF52832_XXAA 
NRF52_PAN_74 
__HEAP_SIZE=8192 
__STACK_SIZE=8192


#endif


//#define RX_PIN_NUMBER       (8)
//#define TX_PIN_NUMBER       (6)

#define RX_PIN_NUMBER       (6)
#define TX_PIN_NUMBER       (8)

#define CTS_PIN_NUMBER      (7)
#define RTS_PIN_NUMBER      (5)
#define UART_HWFC           (APP_UART_FLOW_CONTROL_DISABLED)

#define UART_TX_BUF_SIZE    (256)
#define UART_RX_BUF_SIZE    (256)



const app_uart_comm_params_t Usr_Uart0_Params = 
{
    RX_PIN_NUMBER,
    TX_PIN_NUMBER,
    RTS_PIN_NUMBER,
    CTS_PIN_NUMBER,
    UART_HWFC,
    false,
    NRF_UART_BAUDRATE_115200,
};

void uart_error_handler(app_uart_evt_t *p_event)
{
    if(p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if(p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
    else if(p_event->evt_type == APP_UART_DATA_READY)
    {
        #if(defined(DEF_NONEOS_EN)&&(DEF_NONEOS_EN>0))
        Uart0_Data_Flag = 1;
        #endif
        
        #if(defined(DEF_FREERTOS_EN)&&(DEF_FREERTOS_EN))
        {
            if(pdPASS == xSemaphoreGiveFromISR(Semap_UART_Dbg,&Semap_UART_HigherPriorityTaskWoken))
            {
                
            }
            else
            {
                
            }
        }
        #endif
        
    }
    else if(p_event->evt_type == APP_UART_TX_EMPTY)
    {
        #if(defined(DEF_NONEOS_EN)&&(DEF_NONEOS_EN>0))
        Uart0_Data_Flag = 2;
        #endif
    }
    else
    {
        
    }
}

void Usr_Uart_InitSetup(void)
{
    uint32_t err_code;
    
    APP_UART_FIFO_INIT(&Usr_Uart0_Params,\
                        UART_RX_BUF_SIZE,\
                        UART_TX_BUF_SIZE,\
                        uart_error_handler,\
                        APP_IRQ_PRIORITY_LOWEST,\
                        err_code);
    
    APP_ERROR_CHECK(err_code);
    
    printf("\n\n");
    //printf("\nUart0 InitSetup.\n");
}

uint8_t Uart0_Data_Flag;

void Usr_Uart_MainLoop(void)
{
    uint8_t cr;

    #if 0
    while(app_uart_get(&cr) != NRF_SUCCESS);
    while(app_uart_put(cr) != NRF_SUCCESS);
    #endif
    
    #if 0 //(defined(DEF_SENS_PAV3000_EN)&&(DEF_SENS_PAV3000_EN==1))
    
    if(cr == 'r')
    {
        PAV3000_Read_Rawdata();
    }
    else if(cr == 'c')
    {
        PAV3000_Read_Calidata();
    }
    #endif
    
    #if(defined(DEF_NONEOS_EN)&&(DEF_NONEOS_EN==1))
    if(Uart0_Data_Flag == 1)
    {
        Uart0_Data_Flag = 0;
        
        if(app_uart_get(&cr) == NRF_SUCCESS)
        {
            if(app_uart_put(cr) == NRF_SUCCESS)
            {
                
            }
            else
            {
                printf("\nError happened at app_uart_put();");
            }
            
        }
        else
        {
            printf("\nError happened at app_uart_get();");
        }
    }
    #endif
    
    Usr_I2C_Proc(cr);
    
    cr = 0;
    
    
}

#endif


