#ifndef __USR_TASK_C__
#define __USR_TASK_C__

#include "Usr_Config.h"
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Usr_Task.h"


void Usr_TaskDelayMs(uint32_t ms)
{
    uint32_t MsToTick;
    MsToTick = ms*configTICK_RATE_HZ;
    MsToTick = MsToTick+500;
    MsToTick = MsToTick/1000;
    if(MsToTick<2)
    {
        MsToTick = 1;
    }
    vTaskDelay(MsToTick);
}

void Usr_Task_Create(void)
{
    BaseType_t rtn;
    
    #if 0 //(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN==1))
    // aboue Task;
    {
        NOS_printf("\nCreate Task: %s;",Task_Test1_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test1,
            Task_Test1_Name,
            Task_Test1_StackDepth, 
            Task_Test1_ArgPtr,
            Task_Test1_Priority,
            &Task_Test1_Handle);
        
        if(rtn == pdPASS)
        {
            NOS_printf("\tCreate OK, rtn = %d;",rtn);
        }
        else
        {
            NOS_printf("\tCreate NG, rtn = %d;",rtn);
        }
    }
    #endif

    #if(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN==1))
    {   //Create Task_Test1;
        printf("\nCreate Task_Test1;");
        
        rtn = xTaskCreate(
            Task_Test1_Func,
            Task_Test1_Name,
            Task_Test1_StackDepth,
            Task_Test1_ArgPtr,
            Task_Test1_Priority,
            &Task_Test1_Handle
        );
        
        if(rtn == pdPASS)
        {
            printf("\t Create Task %s, OK;",Task_Test1_Name);
        }
        else
        {
            printf("\t Create Task %s, NG;",Task_Test1_Name);
        }
    }
    #endif
    
}



#if(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN==1))

const char *Task_Test1_Name = "Task_Test1";
const configSTACK_DEPTH_TYPE    Task_Test1_StackDepth = DEF_TASK_STACK_DEPTH;
uint32_t Task_Test1_Arg = 1;
uint32_t *Task_Test1_ArgPtr = &Task_Test1_Arg;
UBaseType_t Task_Test1_Priority = 10;
TaskHandle_t Task_Test1_Handle;

void Task_Test1_Func(void *TaskParameter)
{
    static uint32_t RunCnt=0;
    printf("\nTask_Test1_Func(), RunCnt, %d,",RunCnt);
    
    while(1==1)
    {
        RunCnt++;
        
        printf("\nTask_Test1_Func(), RunCnt, %d,",RunCnt);
        
        Usr_TaskDelayMs(1000);
    }
}



#endif

#endif



