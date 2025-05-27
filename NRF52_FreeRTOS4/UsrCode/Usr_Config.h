#ifndef __USR_CONFIG_H__
#define __USR_CONFIG_H__


#define DEF_GPIO_FUNC_EN    (1)
#define DEF_UART_FUNC_EN    (1)
#define DEF_TIMER_FUNC_EN   (1)
#define DEF_I2C_FUNC_EN     (1)


//#define DEF_NONEOS_EN       (1)
//#define DEF_OSAL_EN         (1)
#define DEF_FREERTOS_EN     (1)


#if(defined(DEF_GPIO_FUNC_EN)&&(DEF_GPIO_FUNC_EN==1))

#endif

#if(defined(DEF_UART_FUNC_EN)&&(DEF_UART_FUNC_EN==1))

#endif

#if(defined(DEF_TIMER_FUNC_EN)&&(DEF_TIMER_FUNC_EN==1))

#endif

#if(defined(DEF_I2C_FUNC_EN)&&(DEF_I2C_FUNC_EN==1))

#endif



#if(defined(DEF_NONEOS_EN)&&(DEF_NONEOS_EN==1))

#endif


#if(defined(DEF_OSAL_EN)&&(DEF_OSAL_EN==1))

#endif


#if(defined(DEF_FREERTOS_EN)&&(DEF_FREERTOS_EN==1))

#endif





#endif

