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

//#define DEF_I2C_WT_MAXLEN   (64)
extern uint8_t I2C_WtLen1;
extern uint8_t I2C_WtBuff1[DEF_I2C_WT_MAXLEN];

//#define DEF_I2C_RD_MAXLEN   (64)
extern uint8_t I2C_RdLen1;
extern uint8_t I2C_RdBuff1[DEF_I2C_RD_MAXLEN];

//#define DEF_I2C_WT_MAXLEN   (64)
extern uint8_t I2C_WtLen2;
extern uint8_t I2C_WtBuff2[DEF_I2C_WT_MAXLEN];

//#define DEF_I2C_RD_MAXLEN   (64)
extern uint8_t I2C_RdLen2;
extern uint8_t I2C_RdBuff2[DEF_I2C_RD_MAXLEN];



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
气体类型定义如下�?
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


// 3.1.5.开启测�?0x3603)
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

// 3.2.3.读浓�?0x1002)

void PGS7000V1D0_Read_Concentration(void);

extern uint16_t ErrorData1;
void PGS7000V1D0_Read_0x1130(void);



extern uint16_t ASC_Func_En;

extern uint16_t ASC_Usr_En;
extern uint16_t ASC_Param_En;
// 3.2.71.读ASC功能开�?0x1140)
void ASC_Read_ASC_Func_En(void);

// 3.2.72.写ASC功能开�?0x11C0)
void ASC_Write_ASC_Func_En(uint8_t arg);


extern uint16_t ASC_PPM_HighTh;
extern uint16_t ASC_PPM_LowTh;

// 3.2.73.读ASC判断漂移临界�?(0x1141)
void ASC_Read_ASC_PPM_HighTh(void);

// 3.2.74.写ASC判断漂移临界�?(0x11C1)
void ASC_Write_ASC_PPM_HighTh(uint16_t arg);

// 3.2.75.读ASC判断漂移临界�?(0x1142)
void ASC_Read_ASC_PPM_LowTh(void);

// 3.2.76.写ASC判断漂移临界�?(0x11C2)
void ASC_Write_ASC_PPM_LowTh(uint16_t arg);


extern int16_t ASC_Tmpr_RateTh;
extern int16_t ASC_Humi_RateTh;
// 3.2.77.读ASC温度变化速度临界�?0x1143)
void ASC_Read_ASC_Tmpr_RateTh(void);

// 3.2.78.写ASC温度变化速度临界�?0x11C3)
void ASC_Write_ASC_Tmpr_RateTh(uint16_t arg);

// 3.2.79.读ASC湿度变化速度临界�?0x1144)
void ASC_Read_ASC_Humi_RateTh(void);

// 3.2.80.写ASC湿度变化速度临界�?0x11C4)
void ASC_Write_ASC_Humi_RateTh(uint16_t arg);

extern int16_t ASC_Tmpr_Rt;
extern int16_t ASC_Humi_Rt;
extern int16_t ASC_Tmpr_RateMax30M;
extern int16_t ASC_Humi_RateMax30M;
extern int16_t ASC_Tmpr_Rate;
extern int16_t ASC_Humi_Rate;

// 3.2.81.读ASC温湿度实时数�?0x1145)
void ASC_Read_ASC_TmprHumi_Rt(void);


#define DEF_ASC_ADJUST_VALUE_MAX        (6)
extern uint16_t ASC_Adjust_Cnt;
extern int16_t ASC_Adjust_Value[DEF_ASC_ADJUST_VALUE_MAX];

// 3.2.82.读ASC校准值实时数�?0x1146)
void ASC_Read_ASC_Calidata_Rt(void);

// 3.2.83.写ASC校准值实时数�?0x11C6)
void ASC_Write_ASC_Calidata_Rt(void);



#endif


uint8_t Usr_I2C_Proc(uint8_t arg);


#endif



