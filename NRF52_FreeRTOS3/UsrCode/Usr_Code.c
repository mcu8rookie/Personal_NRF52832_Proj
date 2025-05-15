#ifndef __USR_CODE_C__
#define __USR_CODE_C__

#include "Usr_Config.h"
#include "Usr_Code.h"
#include "Usr_GPIO.h"
#include "Usr_Uart.h"
#include "Usr_Timer.h"
#include "Usr_I2C.h"

#include <nrfx_systick.h>

#include "nrf_power.h"


uint32_t CPU_ResetReas = 0;


void Usr_InitSetup(void)
{
    
    
    CPU_ResetReas = nrf_power_resetreas_get();
    
    nrf_power_resetreas_clear(0);
    
    #if(defined(DEF_GPIO_FUNC_EN)&&(DEF_GPIO_FUNC_EN==1))
    Usr_GPIO_InitSetup();
    #endif
    
    #if(defined(DEF_UART_FUNC_EN)&&(DEF_UART_FUNC_EN==1))
    Usr_Uart_InitSetup();
    #endif
    
    #if(defined(DEF_TIMER_FUNC_EN)&&(DEF_TIMER_FUNC_EN==1))
    Usr_Timer_InitSetup();
    #endif
    
    #if(defined(DEF_I2C_FUNC_EN)&&(DEF_I2C_FUNC_EN==1))
    Usr_I2C_InitSetup();
    #endif
    
    printf("\nCPU_ResetReas,0x%08X.",CPU_ResetReas);
    printf("\nSystemCoreClock,%d.",SystemCoreClock);
    
    printf("\nUsr_InitSetup().\n");
    
}


void Usr_MainLoop(void)
{
    #if(defined(DEF_GPIO_FUNC_EN)&&(DEF_GPIO_FUNC_EN==1))
    //Usr_GPIO_MainLoop();
    #endif
    
    #if(defined(DEF_UART_FUNC_EN)&&(DEF_UART_FUNC_EN==1))
    Usr_Uart_MainLoop();
    #endif
    
    #if(defined(DEF_TIMER_FUNC_EN)&&(DEF_TIMER_FUNC_EN==1))
    Usr_Timer_MainLoop();
    #endif
    
    #if(defined(DEF_I2C_FUNC_EN)&&(DEF_I2C_FUNC_EN==1))
    Usr_I2C_MainLoop();
    #endif
}




#endif

