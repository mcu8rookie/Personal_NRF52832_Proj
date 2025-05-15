#ifndef __USR_CODE_C__
#define __USR_CODE_C__

#include "Usr_Code.h"
#include "Usr_GPIO.h"

void Usr_InitSetup(void)
{
	Usr_GPIO_InitSetup();
}


void Usr_MainLoop(void)
{
		Usr_GPIO_MainLoop();
}




#endif

