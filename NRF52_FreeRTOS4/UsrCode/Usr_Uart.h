#ifndef __USR_UART_H__
#define __USR_UART_H__

#include <stdio.h>
#include <stdint.h>


void Usr_Uart_InitSetup(void);

extern uint8_t Uart0_Data_Flag;

void Usr_Uart_MainLoop(void);


#endif


