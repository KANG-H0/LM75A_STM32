
#ifndef __LM75AD_H__
#define __LM75AD_H__

#include "i2c.h"

typedef struct
{
    uint16_t Hun;
    uint16_t Tens;
    uint16_t Unit;
    uint16_t Decimals;
    uint16_t TempAll;
} TempDataStruct;

extern TempDataStruct Tempdata;
extern uint8_t Sign;

#define LM75AD_devAddr 0x9e //LM75AD器件地址
#define LM75AD_TempReg 0x00 //温度寄存器(只读，包含2个字节的温度数据)
// #define LM75AD_ConfigReg 0x01  //配置寄存器
// #define Lm75AD_ThystReg 0x02   //滞后寄存器
// #define Lm75AD_TosReg 0x03     //过热关断寄存器

void LM75A_GetTemperature(void);

#endif
