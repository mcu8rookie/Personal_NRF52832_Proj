#ifndef __USR_CODE_C__
#define __USR_CODE_C__

#include "Usr_Code.h"
#include "Usr_GPIO.h"
#include "Usr_Uart.h"
#include "Usr_Timer.h"

void Usr_InitSetup(void)
{
    Usr_GPIO_InitSetup();
    
    Usr_Uart_InitSetup();
    
    Usr_Timer_InitSetup();
}


void Usr_MainLoop(void)
{
    //Usr_GPIO_MainLoop();
    
    Usr_Uart_MainLoop();
    
    Usr_Timer_MainLoop();
}




#endif

