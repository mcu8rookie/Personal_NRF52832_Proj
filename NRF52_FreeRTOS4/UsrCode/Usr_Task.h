#ifndef __USR_TASK_H__
#define __USR_TASK_H__

#include "semphr.h"

#define DEF_TASK_STACK_DEPTH    (128)


//#define DEF_TASK_TEST1_EN               (1)

#define DEF_TASK_ACCESS_PGS7000_V1D0    (1)     // for Midea little board, or E1-PGS7000, PGS7000_V1.0 borad;

#define DEF_TASK_UART_EN            (1)


void Usr_Task_Create(void);



#if(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN==1))

extern const char *Task_Test1_Name;
extern const configSTACK_DEPTH_TYPE    Task_Test1_StackDepth;
extern uint32_t Task_Test1_Arg;
extern uint32_t *Task_Test1_ArgPtr;
extern UBaseType_t Task_Test1_Priority;
extern TaskHandle_t Task_Test1_Handle;

void Task_Test1_Func(void *TaskParameter);

#endif


#if(defined(DEF_TASK_ACCESS_PGS7000_V1D0)&&(DEF_TASK_ACCESS_PGS7000_V1D0==1))

extern const char *Task_Access_PGS7000_V1D0_Name;
extern const configSTACK_DEPTH_TYPE     Task_Access_PGS7000_V1D0_StackDepth;
extern uint32_t Task_Access_PGS7000_V1D0_Arg;
extern uint32_t *Task_Access_PGS7000_V1D0_ArgPtr;
extern UBaseType_t Task_Access_PGS7000_V1D0_Priority;
extern TaskHandle_t Task_Access_PGS7000_V1D0_Handle;

void Task_Access_PGS7000_V1D0_Func(void *TaskParameter);

#endif


#if(defined(DEF_TASK_UART_EN)&&(DEF_TASK_UART_EN>0))

extern SemaphoreHandle_t Semap_UART_Dbg;
extern uint8_t Uart_Char;
extern BaseType_t Semap_UART_HigherPriorityTaskWoken;



extern const char *Task_UART_Name;
extern const configSTACK_DEPTH_TYPE     Task_Uart_StackDepth;
extern uint32_t Task_UART_Arg;
extern uint32_t *Task_UART_ArgPtr;
extern UBaseType_t Task_UART_Priority;
extern TaskHandle_t Task_UART_Handle;
void Task_UART_Func(void *TaskParameter);
#endif


#endif



