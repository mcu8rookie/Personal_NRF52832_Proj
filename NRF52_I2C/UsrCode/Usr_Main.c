#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__


#include "Usr_Main.h"

#include "Usr_Code.h"

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

