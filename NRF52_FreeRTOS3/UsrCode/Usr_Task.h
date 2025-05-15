#ifndef __USR_TASK_H__
#define __USR_TASK_H__



#define DEF_TASK_STACK_DEPTH    (64)


//#define DEF_TASK_TEST1_EN               (1)

#define DEF_TASK_ACCESS_PGS7000_V1D0    (1)     // for Midea little board, or E1-PGS7000, PGS7000_V1.0 borad;




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
extern TaskHandle_t Task_Access_PGS7000_V1D0_Hanle;

void Task_Access_PGS7000_V1D0_Func(void *TaskParameter);

#endif




#endif



