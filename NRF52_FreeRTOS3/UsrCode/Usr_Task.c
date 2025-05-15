#ifndef __USR_TASK_C__
#define __USR_TASK_C__

#include "Usr_Config.h"
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Usr_Task.h"
#include "Usr_I2C_Sensor.h"


void Usr_TaskDelayMs(uint32_t ms)
{
    uint32_t MsToTick;
    
    MsToTick = ms*configTICK_RATE_HZ;
    MsToTick = MsToTick+500;
    MsToTick = MsToTick/1000;
    
    if(MsToTick<1)
    {
        MsToTick = 1;
    }
    
    vTaskDelay(MsToTick);
}

void Usr_Task_Create(void)
{
    BaseType_t rtn;
    
    
    printf("\nUsr_Task_Create();\n");
    
    
    #if(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN==1))
    {   //Create Task_Test1;
        printf("\nCreate Task;");
        
        rtn = pdFALSE;
        
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
    
    #if(defined(DEF_TASK_ACCESS_PGS7000_V1D0)&&(DEF_TASK_ACCESS_PGS7000_V1D0==1))
    {   // Create Task;
        printf("\nCreate Task;");
        
        rtn = pdFALSE;
        
        rtn = xTaskCreate(
            Task_Access_PGS7000_V1D0_Func,
            Task_Access_PGS7000_V1D0_Name,
            Task_Access_PGS7000_V1D0_StackDepth,
            Task_Access_PGS7000_V1D0_ArgPtr,
            Task_Access_PGS7000_V1D0_Priority,
            &Task_Access_PGS7000_V1D0_Hanle
        );
        
        if(rtn == pdPASS)
        {
            printf("\t Create Task %s, OK;",Task_Access_PGS7000_V1D0_Name);
        }
        else
        {
            printf("\t Create Task %s, NG;",Task_Access_PGS7000_V1D0_Name);
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
    static uint32_t RunCnt = 0;
    
    printf("\nTask_Test1_Func(), RunCnt, %d,",RunCnt);
    
    Usr_TaskDelayMs(10);
    
    while(1==1)
    {
        RunCnt++;
        
        //printf("\nTask_Test1_Func(), RunCnt, %d,",RunCnt);
        
        Usr_TaskDelayMs(1000);
        
        //PAV3000_Read_Rawdata();
        //Usr_TaskDelayMs(5);
        
        PAV3000_Read_Calidata();
    }
}

#endif

#if(defined(DEF_TASK_ACCESS_PGS7000_V1D0)&&(DEF_TASK_ACCESS_PGS7000_V1D0==1))

const char *Task_Access_PGS7000_V1D0_Name = "Task_Access_PGS7000_V1.0";
const configSTACK_DEPTH_TYPE    Task_Access_PGS7000_V1D0_StackDepth = DEF_TASK_STACK_DEPTH;
uint32_t Task_Access_PGS7000_V1D0_Arg = 2;
uint32_t *Task_Access_PGS7000_V1D0_ArgPtr = &Task_Access_PGS7000_V1D0_Arg;
UBaseType_t Task_Access_PGS7000_V1D0_Priority = 9;
TaskHandle_t Task_Access_PGS7000_V1D0_Hanle;

void Task_Access_PGS7000_V1D0_Func(void * TaskParameter)
{
    static uint32_t RunCnt = 0;
    
    printf("\nPGS7, RunCnt, %d,",RunCnt);
    
    PGS7000V1D0_Read_FW();
    Usr_TaskDelayMs(100);
    PGS7000V1D0_Write_GasType();
    Usr_TaskDelayMs(100);
    
    while(1==1)
    {
        RunCnt++;
        
        //printf("\nPGS7, RunCnt, %d,",RunCnt);
        
        //PGS7000V1D0_Read_Datas1();
        //PGS7000V1DD0_Read_SN();
        //Usr_TaskDelayMs(1000);
        
        //PGS7000V1D0_Read_FW();
        //Usr_TaskDelayMs(1000);
        
        //PGS7000V1DD0_Read_SN();
        
        //PGS7000V1D0_Write_Reset();
        //PGS7000V1D0_Read_Data();
        
        //PGS7000V1D0_Read_HumiRate();
        PGS7000V1D0_Read_Rawdata();
        
        Usr_TaskDelayMs(1000);
        
    }
}

#endif


#endif



