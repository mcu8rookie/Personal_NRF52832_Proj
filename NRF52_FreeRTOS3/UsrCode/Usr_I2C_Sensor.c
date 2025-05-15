#ifndef __USR_I2C_SENSOR_C__
#define __USR_I2C_SENSOR_C__


#include "Usr_Config.h"
#include <stdint.h>
#include <nrfx.h>
#include "sdk_errors.h"
#include "Usr_I2C.h"
#include "Usr_I2C_Sensor.h"



//#define DEF_I2C_WT_MAXLEN   (64)
uint8_t I2C_WtLen;
uint8_t I2C_WtBuff[DEF_I2C_WT_MAXLEN];

//#define DEF_I2C_RD_MAXLEN   (64)
uint8_t I2C_RdLen;
uint8_t I2C_RdBuff[DEF_I2C_RD_MAXLEN];


#if(defined(DEF_SENS_PSF_EN)&&(DEF_SENS_PSF_EN==1))


#endif



#if(defined(DEF_SENS_PAV3000_EN)&&(DEF_SENS_PAV3000_EN==1))

#define I2C_PAV3000_ADDR_7B         (0x28)
#define I2C_PAV3000_ADDR_WT         ((I2C_PAV3000_ADDR_7B<<1)+0)
#define I2C_PAV3000_ADDR_RD         ((I2C_PAV3000_ADDR_7B<<1)+1)

uint16_t PAV3000_Rawdata;
uint16_t PAV3000_Calidata;



void PAV3000_Read_Calidata(void)
{
    uint8_t i;
    
    ret_code_t rtn;
    
    uint8_t chkdat;
    
    I2C_RdLen = 5;
    
    rtn = Usr_I2C_Read(I2C_PAV3000_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn == NRFX_SUCCESS)
    {
        chkdat = 0;
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
            chkdat += I2C_RdBuff[i];
        }
        
        if(chkdat == 0)
        {
            printf("\tchkdat,\t0x%02X,\tOK,",chkdat);
        }
        else
        {
            printf("\tchkdat,\t0x%02X,\tNG",chkdat);
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
    
    uint8_t chkdat;
    
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
        chkdat = 0;
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
            chkdat += I2C_RdBuff[i];
        }
        
        if(chkdat == 0)
        {
            printf("\tchkdat,\t0x%02X,\tOK,",chkdat);
        }
        else
        {
            printf("\tchkdat,\t0x%02X,\tNG",chkdat);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn);
    }
    
}


#endif

#if(defined(DEF_SENS_PGS7000_V1D0)&&(DEF_SENS_PGS7000_V1D0==1))

#if 1
#if 0
2.CRC校验
本协议采用CRC8校验，校验参数如下：
宽度 WIDTH	8 bits
多项式 POLY	0x31 (X8 + X5 + X4 + 1)
初始值 INIT	0xFF
结果异或值 XOROUT	0x00
输入数据反转 REFIN	FALSE
输出数据反转 REFOUT	FALSE
查表法例程：
#endif
// 按照多项式 X^8 + X^5 + X^4 + 1 生成。
static const uint8_t crc8_table[256] =
{
  0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e, 
  0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d, 
  0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8, 
  0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb, 
  0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13, 
  0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50, 
  0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95, 
  0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6, 
  0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54, 
  0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17, 
  0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2, 
  0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91, 
  0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69, 
  0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a, 
  0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef, 
  0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};

// 使用CRC8表计算数据的CRC8值
// static uint8_t compute_crc8(uint8_t *data, uint16_t size) 
static uint8_t PAV7000_CRC8(uint8_t *data, uint16_t size) 
{
    uint8_t crc = 0xFF;
    
    while(size--)
    {
        //crc = crc8_table[crc ^ data++];
        crc = crc8_table[crc ^ (*data)];
        data++;
    }
    return crc;
}

#endif


#define I2C_PGS7000_V1D0_ADDR_7B    (0x13)
#define I2C_PGS7000_V1D0_ADDR_WT    ((I2C_PGS7000_V1D0_ADDR_7B<<1)+0)
#define I2C_PGS7000_V1D0_ADDR_RD    ((I2C_PGS7000_V1D0_ADDR_7B<<1)+1)

uint16_t PGS7000_V1D0_Tmpr;
uint16_t PGS7000_V1D0_Humi;

uint32_t PGS7000_V1D0_FW;

void PGS7000V1D0_Read_Datas1(void)
{
    uint8_t i;
    
    ret_code_t rtn;
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0xEC;
    I2C_WtBuff[1] = 0x05;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
    
    I2C_RdLen = 18;
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            //printf("\tchkdat,\t0x%02X,\tOK,",chkdat);
            
            PGS7000_V1D0_Tmpr = I2C_RdBuff[9];
            PGS7000_V1D0_Tmpr<<=8;
            PGS7000_V1D0_Tmpr += I2C_RdBuff[10];
            
            PGS7000_V1D0_Humi = I2C_RdBuff[12];
            PGS7000_V1D0_Humi<<=8;
            PGS7000_V1D0_Humi += I2C_RdBuff[13];
            
            printf("\tTmpr,%d,\tHumi,%d,",PGS7000_V1D0_Tmpr,PGS7000_V1D0_Humi);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn);
    }
    
}

void PGS7000V1D0_Read_FW(void)
{
    uint8_t i;
    
    ret_code_t rtn;
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x10;
    I2C_WtBuff[1] = 0x0F;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            //printf("\tchkdat,\t0x%02X,\tOK,",chkdat);
            
            PGS7000_V1D0_FW = I2C_RdBuff[0];
            PGS7000_V1D0_FW <<= 8;
            PGS7000_V1D0_FW += I2C_RdBuff[1];
            PGS7000_V1D0_FW <<= 8;
            PGS7000_V1D0_FW += I2C_RdBuff[3];
            PGS7000_V1D0_FW <<= 8;
            PGS7000_V1D0_FW += I2C_RdBuff[4];
            
            printf("\tFW,0x%08X,",PGS7000_V1D0_FW);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn);
    }
    
}



void PGS7000V1DD0_Read_SomeData(void)
{
    
}


// 3.1.2.读取模块SN命令(0x3615, 0xEC05)
uint32_t PGS7000_ProductNum;
uint64_t PGS7000_SN;

void PGS7000V1DD0_Read_SN(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x36;
    I2C_WtBuff[1] = 0x15;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Read Error:\trtn = %d,",rtn1);
    }
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0xEC;
    I2C_WtBuff[1] = 0x05;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Read Error:\trtn = %d,",rtn1);
    }
    
    I2C_RdLen = 18;
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            //printf("\tchkdat,\t0x%02X,\tOK,",chkdat);
            
            PGS7000_ProductNum = I2C_RdBuff[0];
            PGS7000_ProductNum <<= 8;
            PGS7000_ProductNum += I2C_RdBuff[1];
            PGS7000_ProductNum <<= 8;
            PGS7000_ProductNum += I2C_RdBuff[3];
            PGS7000_ProductNum <<= 8;
            PGS7000_ProductNum += I2C_RdBuff[4];
            
            printf("\tProductNum,0x%08X,",PGS7000_ProductNum);
            
            PGS7000_SN = I2C_RdBuff[6];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[7];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[9];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[10];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[12];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[13];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[15];
            PGS7000_SN <<= 8;
            PGS7000_SN += I2C_RdBuff[16];
            
            printf("\tSN,0x%016llX,",PGS7000_SN);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn2);
    }
    
}

// 3.1.3.设置气体类型(0x3608)

uint16_t PGS7000_GasType = DEF_GASTYPE_R454B;

void PGS7000V1D0_Write_GasType(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    
    I2C_WtLen = 5;
    I2C_WtBuff[0] = 0x36;
    I2C_WtBuff[1] = 0x08;
    I2C_WtBuff[2] = PGS7000_GasType>>8;
    I2C_WtBuff[3] = PGS7000_GasType;
    I2C_WtBuff[4] = PAV7000_CRC8(I2C_WtBuff+2,2);
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
    if(rtn1 == NRFX_SUCCESS)
    {
        printf("\nI2C Write %d byte:",I2C_WtLen);
        
        for(i=0;i<I2C_WtLen;i++)
        {
            printf("\t0x%02X,",I2C_WtBuff[i]);
        }
        
        printf("\tProductNum,0x%04X,",PGS7000_GasType);
        
    }
    else
    {
        printf("\nI2C Write Error:\trtn = %d,",rtn1);
    }
    
}

// 3.1.4.复位模块(0x3606)
void PGS7000V1D0_Write_Reset(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x36;
    I2C_WtBuff[1] = 0x06;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Write Error:\trtn = %d,",rtn1);
    }
}

// 3.1.5.开启测量(0x3603)
uint16_t PGS7000_StartMeas = 1;
void PGS7000V1D0_Write_StartMeas(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x36;
    I2C_WtBuff[1] = 0x03;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
    if(rtn1 == NRFX_SUCCESS)
    {
        printf("\nI2C Write %d byte:",I2C_WtLen);
        
        for(i=0;i<I2C_WtLen;i++)
        {
            printf("\t0x%02X,",I2C_WtBuff[i]);
        }
        
        PGS7000_StartMeas = 1;
    }
    else
    {
        printf("\nI2C Write Error:\trtn = %d,",rtn1);
    }
}

// 3.1.6.读取数据(0xEC05)
uint16_t PGS7000_PPM;
uint16_t PGS7000_ErrCode;
//uint16_t PGS7000_GasType;
int16_t PGS7000_Tmpr;
int16_t PGS7000_Humi;
int16_t PGS7000_AstValue;

void PGS7000V1D0_Read_Data(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0xEC;
    I2C_WtBuff[1] = 0x05;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Read Error:\trtn = %d,",rtn1);
    }
    
    I2C_RdLen = 18;
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            PGS7000_PPM = I2C_RdBuff[0];
            PGS7000_PPM <<= 8;
            PGS7000_PPM += I2C_RdBuff[1];
            
            PGS7000_ErrCode = I2C_RdBuff[3];
            PGS7000_ErrCode <<= 8;
            PGS7000_ErrCode += I2C_RdBuff[4];
            
            PGS7000_GasType = I2C_RdBuff[6];
            PGS7000_GasType <<= 8;
            PGS7000_GasType += I2C_RdBuff[7];
            
            PGS7000_Tmpr = I2C_RdBuff[9];
            PGS7000_Tmpr <<= 8;
            PGS7000_Tmpr += I2C_RdBuff[10];
            
            PGS7000_Humi = I2C_RdBuff[12];
            PGS7000_Humi <<= 8;
            PGS7000_Humi += I2C_RdBuff[13];
            
            printf("\tPPM,%d,\tErrCode,0x%04X,\tGasType,0x%04x,\tTmpr,%d,\tHumi,%d,",PGS7000_PPM,PGS7000_ErrCode,PGS7000_GasType,PGS7000_Tmpr,PGS7000_Humi);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn2);
    }
    
}


// 3.2.1.读湿度速率(0x1000)
uint16_t PGS7000_HumiRate;
void PGS7000V1D0_Read_HumiRate(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x10;
    I2C_WtBuff[1] = 0x00;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Read Error:\trtn = %d,",rtn1);
    }
    
    I2C_RdLen = 3;
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            PGS7000_HumiRate = I2C_RdBuff[0];
            PGS7000_HumiRate <<= 8;
            PGS7000_HumiRate += I2C_RdBuff[1];
            
            printf("\tHumiRate,%d,",PGS7000_HumiRate);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn2);
    }
    
}

// 3.2.2.读raw data(0x1001)
uint16_t PGS7000_TmprRaw;
int16_t PGS7000_SRaw_Original;
int16_t PGS7000_SRaw_Aft_TmprComp;

void PGS7000V1D0_Read_Rawdata(void)
{
    uint8_t i;
    
    ret_code_t rtn1 = 0xFF;
    ret_code_t rtn2 = 0xFF;
    
    uint8_t chkdat;
    uint8_t chkerr;
    
    I2C_WtLen = 2;
    I2C_WtBuff[0] = 0x10;
    I2C_WtBuff[1] = 0x01;
    
    rtn1 = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 0);     // have stop condition at the end of write.
    //rtn = Usr_I2C_Write(I2C_PGS7000_V1D0_ADDR_7B, I2C_WtBuff, I2C_WtLen, 1);   // none stop condition at the end of write.
    
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
        printf("\nI2C Read Error:\trtn = %d,",rtn1);
    }
    
    I2C_RdLen = 9;
    
    rtn2 = Usr_I2C_Read(I2C_PGS7000_V1D0_ADDR_7B, I2C_RdBuff, I2C_RdLen);
    
    if(rtn2 == NRFX_SUCCESS)
    {
        
        printf("\nI2C Read %d byte:",I2C_RdLen);
        
        for(i=0;i<I2C_RdLen;i++)
        {
            printf("\t0x%02X,",I2C_RdBuff[i]);
        }
        
        chkerr = 0;
        for(i=0;i<I2C_RdLen;i+=3)
        {
            chkdat = 0;
            
            chkdat = PAV7000_CRC8(I2C_RdBuff+i,2);
            
            if(chkdat == I2C_RdBuff[i+2])
            {
                
            }
            else
            {
                chkerr++;
                printf("\tchk%d,0x%02X\tNG",i+2,chkdat);
            }
        }
        
        if(chkerr == 0)
        {
            PGS7000_TmprRaw = I2C_RdBuff[0];
            PGS7000_TmprRaw <<= 8;
            PGS7000_TmprRaw += I2C_RdBuff[1];
            
            PGS7000_SRaw_Original = I2C_RdBuff[0];
            PGS7000_SRaw_Original <<= 8;
            PGS7000_SRaw_Original += I2C_RdBuff[1];
            
            PGS7000_SRaw_Aft_TmprComp = I2C_RdBuff[0];
            PGS7000_SRaw_Aft_TmprComp <<= 8;
            PGS7000_SRaw_Aft_TmprComp += I2C_RdBuff[1];
            
            printf("\tTmprRaw,%d,\tSRaw_Ofiginal,%d,\tSRaw_Aft_TmprComp,%d,",PGS7000_TmprRaw,PGS7000_SRaw_Original,PGS7000_SRaw_Aft_TmprComp);
        }
        else
        {
            printf("\tNG_Cnt,\t0x%02X,\t",chkerr);
        }
    }
    else
    {
        printf("\nI2C Read Error:\trtn = %d,",rtn2);
    }
    
}

// 3.2.3.读浓度(0x1002)

void PGS7000V1D0_Read_Concentration(void)
{
    
}


#endif





#endif




