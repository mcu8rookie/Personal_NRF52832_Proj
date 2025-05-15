#ifndef __USR_TASK_H__
#define __USR_TASK_H__



#define DEF_TASK_STACK_DEPTH    (64)


#define DEF_TASK_TEST1_EN       (1)



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




#endif



