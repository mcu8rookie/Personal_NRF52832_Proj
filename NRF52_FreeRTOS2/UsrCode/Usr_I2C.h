#ifndef __USR_I2C_H__
#define __USR_I2C_H__

#include "stdint.h"
#include "sdk_errors.h"

#define ARDUINO_SCL_PIN             27    // SCL signal pin
#define ARDUINO_SDA_PIN             26    // SDA signal pin

#define I2C_DEVICE1_SCL_PIN         (25)  
#define I2C_DEVICE1_SDA_PIN         (26)

#define I2C_DEVICE1_ADDR_7B         (0x28)

#define I2C_DEVICE1_ADDR_WT         ((I2C_DEVICE1_ADDR_7B<<1)+1)
#define I2C_DEVICE1_ADDR_RD         ((I2C_DEVICE1_ADDR_7B<<1)+1)



extern uint8_t I2C_Addr_7B;
extern uint8_t I2C_Addr_Wt;
extern uint8_t I2C_Addr_Rd;


void Usr_I2C_InitSetup(void);

void Usr_I2C_MainLoop(void);


ret_code_t Usr_I2C_Write(unsigned char addr7b,unsigned char *ptr,unsigned char len,unsigned char np);
ret_code_t Usr_I2C_Read(unsigned char addr7b,unsigned char *ptr,unsigned char len);





#endif


