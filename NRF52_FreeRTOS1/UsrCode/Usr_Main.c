#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__


#include <stdint.h>
#include "Usr_Config.h"
#include "Usr_Main.h"

#include "Usr_Code.h"




#if(defined(DEF_NONEOS_EN)&&(DEF_NONEOS_EN==1))

int main(void)
{
    Usr_InitSetup();
    
    printf("\nInitSetup() completed, will run loop forever.\n");
    
    while(1)
    {
        Usr_MainLoop();
    }
}

#endif


#if(defined(DEF_OSAL_EN)&&(DEF_OSAL_EN==1))

#endif


#if(defined(DEF_FREERTOS_EN)&&(DEF_FREERTOS_EN==1))

#include "FreeRTOS.h"
#include "task.h"
#include "Usr_Task.h"

int main(void)
{
    Usr_InitSetup();
    
    printf("%d.\n",SystemCoreClock);
    
    printf("\nUsr_InitSetup();\n");
    
    Usr_Task_Create();
    printf("\nUsr_Task_Create();\n");
    
    printf("\nWill Run vTaskStartScheduler();\n");
    
    vTaskStartScheduler();
    
    while(1)
    {
        Usr_MainLoop();
    }
}

#endif



#endif

