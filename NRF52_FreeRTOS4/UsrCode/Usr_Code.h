#ifndef __USR_CODE_H__
#define __USR_CODE_H__


#include <stdint.h>
#include <stdio.h>


extern uint32_t CPU_ResetReas;

void Usr_InitSetup(void);

void Usr_MainLoop(void);

#endif

