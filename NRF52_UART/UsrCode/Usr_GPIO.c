#ifndef __USR_GPIO_C__
#define __USR_GPIO_C__

#include "Usr_Mcu.h"
#include "Usr_Board.h"
#include "nrf_gpio.h"
#include "Usr_GPIO.h"
#include "nrf_delay.h"

#define DEF_LED1        (17)
#define DEF_LED2        (18)
#define DEF_LED3        (19)
#define DEF_LED4        (20)

#define DEF_KEY1        (13)
#define DEF_KEY2        (14)
#define DEF_KEY3        (15)
#define DEF_KEY4        (16)

#define DEF_LED_DLYCNT  (1000)

void Usr_GPIO_InitSetup(void)
{
    nrf_gpio_cfg_output(DEF_LED1);
    nrf_gpio_cfg_output(DEF_LED2);
    nrf_gpio_cfg_output(DEF_LED3);
    nrf_gpio_cfg_output(DEF_LED4);

    nrf_gpio_pin_clear(DEF_LED1);
    nrf_gpio_pin_clear(DEF_LED2);
    nrf_gpio_pin_clear(DEF_LED3);
    nrf_gpio_pin_clear(DEF_LED4);

    nrf_gpio_pin_set(DEF_LED1);
    nrf_gpio_pin_set(DEF_LED2);
    nrf_gpio_pin_set(DEF_LED3);
    nrf_gpio_pin_set(DEF_LED4);
}

void Usr_GPIO_MainLoop(void)
{
    #if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_IKM52))
    nrf_gpio_pin_clear(DEF_LED1);
    nrf_gpio_pin_set(DEF_LED2);
    nrf_gpio_pin_set(DEF_LED3);
    nrf_gpio_pin_set(DEF_LED4);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    
    nrf_gpio_pin_set(DEF_LED1);
    nrf_gpio_pin_clear(DEF_LED2);
    nrf_gpio_pin_set(DEF_LED3);
    nrf_gpio_pin_set(DEF_LED4);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    
    nrf_gpio_pin_set(DEF_LED1);
    nrf_gpio_pin_set(DEF_LED2);
    nrf_gpio_pin_clear(DEF_LED3);
    nrf_gpio_pin_set(DEF_LED4);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    
    nrf_gpio_pin_set(DEF_LED1);
    nrf_gpio_pin_set(DEF_LED2);
    nrf_gpio_pin_set(DEF_LED3);
    nrf_gpio_pin_clear(DEF_LED4);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    #endif
    
    #if(defined(DEF_BOARD_TYPE)&&(DEF_BOARD_TYPE==DEF_BOARD_NRF52832_MINI))
    nrf_gpio_pin_clear(DEF_LED1);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    
    nrf_gpio_pin_set(DEF_LED1);
    nrf_delay_ms2(DEF_LED_DLYCNT);
    #endif
}




#endif

