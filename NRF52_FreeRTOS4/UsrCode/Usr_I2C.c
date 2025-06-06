#ifndef __USR_I2C_C__
#define __USR_I2C_C__

#include <stdint.h>
#include <stdbool.h>
#include "Usr_Config.h"
#include "Usr_Mcu.h"
#include "Usr_Board.h"
#include "nrf_drv_twi.h"
#include "Usr_I2C.h"
#include "nrf_drv_twi.h"

#include "nrfx_log.h"

/* TWI instance ID. */
#define TWI_INSTANCE_ID     0

/* Mode for LM75B. */
#define NORMAL_MODE         0U


uint8_t I2C_Addr_7B = I2C_DEVICE1_ADDR_7B;
uint8_t I2C_Addr_Wt = I2C_DEVICE1_ADDR_WT;
uint8_t I2C_Addr_Rd = I2C_DEVICE1_ADDR_RD;

#define DEF_I2C_TIMEOUT_MAX 20
uint8_t I2C_Timeout_Cnt;

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Buffer for samples read from temperature sensor. */
static uint8_t m_sample;


/**
 * @brief Function for handling data from temperature sensor.
 *
 * @param[in] temp          Temperature in Celsius degrees read from sensor.
 */
__STATIC_INLINE void data_handler(uint8_t temp)
{
    NRF_LOG_INFO("Temperature: %d Celsius degrees.", temp);
}

/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
                data_handler(m_sample);
            }
            m_xfer_done = true;
            break;
        default:
            break;
    }
}


void twi_init (void)
{
    uint32_t err_code;

    const nrf_drv_twi_config_t twi_lm75b_config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = (nrf_drv_twi_frequency_t)NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_lm75b_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}


void Usr_I2C_InitSetup(void)
{
    uint32_t err_code;
    
    const nrf_drv_twi_config_t twi_device1_config = 
    {
        .scl = I2C_DEVICE1_SCL_PIN,
        .sda = I2C_DEVICE1_SDA_PIN,
        .frequency = (nrf_drv_twi_frequency_t)NRF_TWI_FREQ_100K,
        .interrupt_priority = 1,
        .clear_bus_init = false
    };
    
    err_code = nrf_drv_twi_init(&m_twi, &twi_device1_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi);
    
}

#if 0
void LM75B_set_mode(void)
{
    ret_code_t err_code;

    /* Writing to LM75B_REG_CONF "0" set temperature sensor in NORMAL mode. */
    uint8_t reg[2] = {0xD0, 0xD1};
    err_code = nrf_drv_twi_tx(&m_twi, I2C_Addr_7B, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    /* Writing to pointer byte. */
    reg[0] = 0X01;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, I2C_Addr_7B, reg, 1, false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}
static void read_sensor_data(void)
{
    m_xfer_done = false;

    /* Read 1 byte from the specified address - skip 3 bits dedicated for fractional part of temperature. */
    ret_code_t err_code = nrf_drv_twi_rx(&m_twi, I2C_Addr_7B, &m_sample, sizeof(m_sample));
    APP_ERROR_CHECK(err_code);
}
#endif

ret_code_t Usr_I2C_Write(unsigned char addr7b,unsigned char *ptr,unsigned char len,unsigned char np)
{
    ret_code_t rtn;
    
    m_xfer_done = false;
    
    rtn = nrf_drv_twi_tx(&m_twi,addr7b,ptr,len,np);
    APP_ERROR_CHECK(rtn);
    I2C_Timeout_Cnt = DEF_I2C_TIMEOUT_MAX;
    while((m_xfer_done == false)&&(I2C_Timeout_Cnt>0));
    if(I2C_Timeout_Cnt==0)
    {
        return NRFX_ERROR_TIMEOUT;
    }
    return rtn;
}
ret_code_t Usr_I2C_Read(unsigned char addr7b,unsigned char *ptr,unsigned char len)
{
    ret_code_t rtn = 0xFF;
    
    m_xfer_done = false;
    
    rtn = nrf_drv_twi_rx(&m_twi,addr7b,ptr,len);
    
    if(rtn != NRF_SUCCESS)
    {
        printf("\nUsr_I2C_Read():\trtn = %d,",rtn);
    }
    
    APP_ERROR_CHECK(rtn);
    I2C_Timeout_Cnt = DEF_I2C_TIMEOUT_MAX;
    while((m_xfer_done == false)&&(I2C_Timeout_Cnt>0));
    if(I2C_Timeout_Cnt==0)
    {
        return NRFX_ERROR_TIMEOUT;
    }
    return rtn;
}

void Usr_I2C_MainLoop(void)
{
    
    
    
}




#endif




