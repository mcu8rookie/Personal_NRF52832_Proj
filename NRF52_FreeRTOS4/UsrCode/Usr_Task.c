#ifndef __USR_TASK_C__
#define __USR_TASK_C__

#include "Usr_Config.h"
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "nrf_error.h"
#include "portmacro.h"
#include "task.h"
#include "app_uart.h"
#include "queue.h"
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
            &Task_Access_PGS7000_V1D0_Handle
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
    
    #if(defined(DEF_TASK_UART_EN)&&(DEF_TASK_UART_EN>0))
    {
        Semap_UART_Dbg = xSemaphoreCreateBinary();
        printf("\nCreate Task;");
        rtn = pdFALSE;
        rtn = xTaskCreate(
            Task_UART_Func,
            Task_UART_Name,
            Task_Uart_StackDepth,
            Task_UART_ArgPtr,
            Task_UART_Priority,
            &Task_UART_Handle
        );
        if(rtn == pdPASS)
        {
            printf("\t Create Task %s, OK;",Task_UART_Name);
        }
        else
        {
            printf("\t Create Task %s, NG;",Task_UART_Name);
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
TaskHandle_t Task_Access_PGS7000_V1D0_Handle;

void Task_Access_PGS7000_V1D0_Func(void * TaskParameter)
{
    static uint32_t RunCnt = 0;
    
    printf("\nPGS7, RunCnt, %d,",RunCnt);
    
    #if 0
    PGS7000V1D0_Read_FW();
    Usr_TaskDelayMs(100);
    PGS7000V1D0_Write_GasType();
    Usr_TaskDelayMs(100);
    #endif
    
    while(1==1)
    {
        RunCnt++;
        
        printf("\nPGS7, RunCnt, %d,",RunCnt);
        
        //PGS7000V1D0_Read_Datas1();
        //PGS7000V1DD0_Read_SN();
        //Usr_TaskDelayMs(1000);
        
        //PGS7000V1D0_Read_FW();
        //Usr_TaskDelayMs(1000);
        
        //PGS7000V1DD0_Read_SN();
        
        //PGS7000V1D0_Write_Reset();
        //PGS7000V1D0_Read_Data();
        
        //PGS7000V1D0_Read_HumiRate();
        
        //PGS7000V1D0_Read_Datas1();
        //Usr_TaskDelayMs(100);
        //PGS7000V1D0_Read_Rawdata();
        
        
        //printf("\nTask:%s,",pxCurrentTCB->pcTaskName);
        
        Usr_TaskDelayMs(1000);
        
    }
}

#endif

#if(defined(DEF_TASK_UART_EN)&&(DEF_TASK_UART_EN>0))

SemaphoreHandle_t Semap_UART_Dbg;
uint8_t Uart_Char;
BaseType_t Semap_UART_HigherPriorityTaskWoken;



const char *Task_UART_Name = "Task_UART";
const configSTACK_DEPTH_TYPE        Task_Uart_StackDepth = DEF_TASK_STACK_DEPTH;
uint32_t Task_UART_Arg = 1;         // The number of UART;
uint32_t *Task_UART_ArgPtr = &Task_UART_Arg;
UBaseType_t Task_UART_Priority = 11;
TaskHandle_t Task_UART_Handle;
void Task_UART_Func(void *TaskParameter)
{
    BaseType_t rtn1;
    UBaseType_t * ptr;
    //int16_t ValueOffset;
    
    
    ptr = (UBaseType_t * )Semap_UART_Dbg;
    printf("\n&Semap_UART_Dbg = %p,",ptr);
    
    //#define offset(type, v) (&(((type *)0)->v))
    
    //ValueOffset = (&(((SemaphoreHandle_t)0)->uxItemSize));
    
    //printf("\nValueOffset of uxItemSize = %d,",ValueOffset);
    
    while(1)
    {
        //printf("\nTask:%s,",pxCurrentTCB->pcTaskName);
        
        rtn1 = xSemaphoreTake(Semap_UART_Dbg, portMAX_DELAY);
        
        if(rtn1 == pdTRUE)
        {
            if(app_uart_get(&Uart_Char) == NRF_SUCCESS)
            {
                if(app_uart_put(Uart_Char) == NRF_SUCCESS)
                {
                    
                }
                else
                {
                    printf("\nError happened at app_uart_put();");
                }
                
            }
            else
            {
                printf("\nError happened at app_uart_get();");
            }
            
            Usr_I2C_Proc(Uart_Char);
            
        }
        else
        {
            
        }
    }
    
}


#endif



#endif



