
#include "LM75A.h"

TempDataStruct Tempdata = {0};
uint8_t Sign = ' '; //温度符号

void LM75A_GetTemperature(void)
{
    /*
    Temp register
    -------------------------------------------------------------
    MSByte                         |LSByte
    7   6   5   4   3   2   1   0  |7   6  5   4   3   2    1   0
    D10 D9 D8  D7  D6  D5  D4  D3  |D2  D1 D0  X   X   X    X   X
    -------------------------------------------------------------
    D10=0温度为+,D10=1温度为-
    */
    uint8_t TempHL[2];
    HAL_I2C_Mem_Read(&hi2c1, LM75AD_devAddr, LM75AD_TempReg, I2C_MEMADD_SIZE_8BIT, TempHL, 2, 100);
    Tempdata.TempAll = ((TempHL[0] << 8) | TempHL[1]);
    if ((TempHL[0] & 0x80) != 0) //如果D10不等于0，则温度为负
    {
        Tempdata.TempAll = ~(Tempdata.TempAll) + 1;
        Sign = '-';
    }
    //低5位数据无效移除
    Tempdata.TempAll >>= 5;
    Tempdata.TempAll = Tempdata.TempAll * 0.125 * 10 + 0.5;
    //提取各位部分数据
    Tempdata.Hun = Tempdata.TempAll / 1000;
    Tempdata.Tens = (Tempdata.TempAll / 100) % 10;
    Tempdata.Unit = (Tempdata.TempAll / 10) % 10;
    Tempdata.Decimals = Tempdata.TempAll % 10;
}
