#ifndef __USR_I2C_SENSOR_C__
#define __USR_I2C_SENSOR_C__


#include "Usr_Config.h"
#include <nrfx.h>
#include "sdk_errors.h"
#include "Usr_I2C.h"
#include "Usr_I2C_Sensor.h"


#if(defined(DEF_SENS_PSF_EN)&&(DEF_SENS_PSF_EN==1))


#endif



#if(defined(DEF_SENS_PAV3000_EN)&&(DEF_SENS_PAV3000_EN==1))

#define I2C_PAV3000_ADDR_7B         (0x28)

#define I2C_PAV3000_ADDR_WT         ((I2C_PAV3000_ADDR_7B<<1)+1)
#define I2C_PAV3000_ADDR_RD         ((I2C_PAV3000_ADDR_7B<<1)+1)


uint16_t PAV3000_Rawdata;
uint16_t PAV3000_Calidata;

uint8_t I2C_WtLen;
uint8_t I2C_WtBuff[10];

uint8_t I2C_RdLen;
uint8_t I2C_RdBuff[10];


void PAV3000_Read_Calidata(void)
{
    uint8_t i;
    
    ret_code_t rtn;
    
    uint8_t chksum;
    
    I2C_RdLen = 5;
    
    rtn = Usr_I2C_Read(I2C_PAV3000_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn == NRFX_SUCCESS)
    {
        chksum = 0;
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
            chksum += I2C_RdBuff[i];
        }
        
        if(chksum == 0)
        {
            printf("\tchksum,\t0x%02X,\tOK,",chksum);
        }
        else
        {
            printf("\tchksum,\t0x%02X,\tNG",chksum);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d.",rtn);
    }
    
}

void PAV3000_Read_Rawdata(void)
{
    uint8_t i;
    
    ret_code_t rtn;
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chksum;
    
    I2C_WtLen = 1;
    I2C_WtBuff[0] = 0xD0;
    
    rtn1 = Usr_I2C_Write(I2C_PAV3000_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PAV3000_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
    if(rtn1 == NRFX_SUCCESS)
    {
        printf("\nI2C Write %d byte:",I2C_WtLen);
        
        for(i=0;i<I2C_WtLen;i++)
        {
            printf("\t0x%02X,",I2C_WtBuff[i]);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn);
    }
    
    I2C_RdLen = 6;
    
    rtn2 = Usr_I2C_Read(I2C_PAV3000_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        chksum = 0;
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
            chksum += I2C_RdBuff[i];
        }
        
        if(chksum == 0)
        {
            printf("\tchksum,\t0x%02X,\tOK,",chksum);
        }
        else
        {
            printf("\tchksum,\t0x%02X,\tNG",chksum);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn);
    }
    
}



#endif


#endif




