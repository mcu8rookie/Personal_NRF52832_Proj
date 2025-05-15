#ifndef __USR_TIMER_C__
#define __USR_TIMER_C__

#include "nrf52.h"
#include "nrf_drv_timer.h"
#include "nrfx_timer.h"

#include "Usr_Mcu.h"
#include "Usr_Board.h"
#include "Usr_Timer.h"
#include "Usr_I2C.h"
#include "nrf_gpio.h"
#include "Usr_GPIO.h"


const nrf_drv_timer_t Timer0_St = 
{
    //.p_reg = NRF_TIMER0,
    // .instance_id = TIMER0_INSTANCE_INDEX,
    .p_reg = NRF_TIMER0,
    .instance_id = NRFX_TIMER0_INST_IDX,
    .cc_channel_count = 0
};

const nrf_drv_timer_config_t Timer0_Config = 
{
    .frequency = (nrf_timer_frequency_t)NRF_TIMER_FREQ_16MHz,
    .mode = (nrf_timer_mode_t)NRF_TIMER_MODE_TIMER,
    .bit_width = (nrf_timer_bit_width_t)NRF_TIMER_BIT_WIDTH_16,
    .interrupt_priority = 3,
    .p_context = (void*)0,
};

nrf_timer_event_handler_t Timer0_Handler_Ptr;

void Timer0_Handler(nrf_timer_event_t et,void*p_context)
{
    static uint32_t Timer0_Cnt = 0;
    
    et = et;
    p_context = p_context;
    
    
    switch(et)
    {
        case NRF_TIMER_EVENT_COMPARE0:
        {
            Timer0_Cnt++;
            
            if(I2C_Timeout_Cnt>0)
            {
                I2C_Timeout_Cnt--;
            }
            
            if(Timer0_Cnt>=1000)
            {
                Timer0_Cnt = 0;
                nrf_gpio_pin_toggle(DEF_LED1);
            }
        }
        break;
        
        default:
        
        break;
    }
    
    
}

void Usr_Timer_InitSetup(void)
{
    uint32_t err_code = NRF_SUCCESS;
    uint32_t time_ms = 1;
    uint32_t time_ticks;
    
    Timer0_Handler_Ptr = Timer0_Handler;
    
    err_code = nrf_drv_timer_init(&Timer0_St,&Timer0_Config,Timer0_Handler_Ptr);
    
    APP_ERROR_CHECK(err_code);
    
    time_ticks = nrf_drv_timer_ms_to_ticks(&Timer0_St,time_ms);
    
    nrf_drv_timer_extended_compare(&Timer0_St,NRF_TIMER_CC_CHANNEL0,time_ticks,
    NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,true);
    
    nrf_drv_timer_enable(&Timer0_St);
    
}

void Usr_Timer_MainLoop(void)
{
    
}

#endif


