#ifndef __USR_GPIO_H__
#define __USR_GPIO_H__

#include <stdio.h>
#include "nrf.h"


// #define CLOCK_FREQ_16MHz (16000000UL)
#define CLOCK_FREQ_16MHz (64000000UL)



#if defined ( __CC_ARM   )
__STATIC_INLINE void nrf_delay_us2(uint32_t number_of_us)
{
    if(!number_of_us)
        return;
__asm
    {
loop:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    CMP SystemCoreClock, CLOCK_FREQ_16MHz
    BEQ cond
    NOP
#if defined(NRF52) || defined(NRF52840_XXAA) || defined(NRF52832)
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
#endif
cond:
    SUBS number_of_us, #1
    BNE loop
    }
}
#endif

__STATIC_INLINE void nrf_delay_ms2(uint32_t number_of_ms)
{
    nrf_delay_us2(1000*number_of_ms);
}



#define DEF_LED1        (17)
#define DEF_LED2        (18)
#define DEF_LED3        (19)
#define DEF_LED4        (20)

#define DEF_KEY1        (13)
#define DEF_KEY2        (14)
#define DEF_KEY3        (15)
#define DEF_KEY4        (16)

#define DEF_LED_DLYCNT	(1000)

void Usr_GPIO_InitSetup(void);

void Usr_GPIO_MainLoop(void);

#endif

