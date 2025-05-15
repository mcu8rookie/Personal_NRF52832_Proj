#ifndef __USR_I2C_SENSOR_H__
#define __USR_I2C_SENSOR_H__

#include <stdint.h>

#define DEF_SENS_PSF_EN         (1)

#define DEF_SENS_PAV3000_EN     (1)     // For PAV3000 or Renenses FS3000;

#define DEF_SENS_PGS7000_V1D0   (1)     // for Midea little board, or E1-PGS7000, PGS7000_V1.0 borad;


#define DEF_I2C_WT_MAXLEN   (64)
extern uint8_t I2C_WtLen;
extern uint8_t I2C_WtBuff[DEF_I2C_WT_MAXLEN];

#define DEF_I2C_RD_MAXLEN   (64)
extern uint8_t I2C_RdLen;
extern uint8_t I2C_RdBuff[DEF_I2C_RD_MAXLEN];



#if(defined(DEF_SENS_PSF_EN)&&(DEF_SENS_PSF_EN==1))


#endif



#if(defined(DEF_SENS_PAV3000_EN)&&(DEF_SENS_PAV3000_EN==1))

extern uint16_t PAV3000_Rawdata;
extern uint16_t PAV3000_Calidata;

void PAV3000_Read_Calidata(void);

void PAV3000_Read_Rawdata(void);


#endif

#if(defined(DEF_SENS_PGS7000_V1D0)&&(DEF_SENS_PGS7000_V1D0==1))

extern uint16_t PGS7000_V1D0_Tmpr;
extern uint16_t PGS7000_V1D0_Humi;

extern uint32_t PGS7000_V1D0_FW;

void PGS7000V1D0_Read_Datas1(void);

void PGS7000V1D0_Read_FW(void);

void PGS7000V1DD0_Read_SomeData(void);

// 3.1.2.读取模块SN命令(0x3615, 0xEC05)
extern uint32_t PGS7000_ProductNum;
extern uint64_t PGS7000_SN;

void PGS7000V1DD0_Read_SN(void);

// 3.1.3.设置气体类型(0x3608)
#if 0
气体类型定义如下：
0x0018：R-32
0x001C：R-454A
0x0019：R-454B
0x001B：R-454C
0x001D：R-455A
#endif

#define DEF_GASTYPE_R32         (0x0018)
#define DEF_GASTYPE_R454A       (0x001C)
#define DEF_GASTYPE_R454B       (0x0019)
#define DEF_GASTYPE_R454C       (0x001B)
#define DEF_GASTYPE_R455A       (0x001D)

extern uint16_t PGS7000_GasType;

void PGS7000V1D0_Write_GasType(void);


// 3.1.4.复位模块(0x3606)
void PGS7000V1D0_Write_Reset(void);


// 3.1.5.开启测量(0x3603)
extern uint16_t PGS7000_StartMeas;
void PGS7000V1D0_Write_StartMeas(void);


// 3.1.6.读取数据(0xEC05)
extern uint16_t PGS7000_PPM;
extern uint16_t PGS7000_ErrCode;
//extern uint16_t PGS7000_GasType;
extern int16_t PGS7000_Tmpr;
extern int16_t PGS7000_Humi;
extern int16_t PGS7000_AstValue;

void PGS7000V1D0_Read_Data(void);


// 3.2.1.读湿度速率(0x1000)
extern uint16_t PGS7000_HumiRate;
void PGS7000V1D0_Read_HumiRate(void);


// 3.2.2.读raw data(0x1001)
extern uint16_t PGS7000_TmprRaw;
extern int16_t PGS7000_SRaw_Original;
extern int16_t PGS7000_SRaw_Aft_TmprComp;

void PGS7000V1D0_Read_Rawdata(void);

// 3.2.3.读浓度(0x1002)

void PGS7000V1D0_Read_Concentration(void);



#endif



#endif



