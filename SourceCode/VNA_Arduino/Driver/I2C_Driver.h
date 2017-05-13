#ifndef __I2C_DRIVER__
#define __I2C_DRIVER__

/*********** Defines ***********/

/*********** Libraries ***********/
#include <Wire.h>

/*********** Methods ***********/
void I2C_Init(void)
{
    Wire.begin();
}

void I2C_Begin(uint8_t slaveAddr)
{
    Wire.beginTransmission(slaveAddr);
}

void I2C_SendByte(uint8_t data)
{
    Wire.write(data);
}

void I2C_SendArray(uint8_t *arr, uint8_t count)
{
    int i = 0;
    for (i; i < count; i++)
    {
        I2C_SendByte(arr[i]);
    }
}

void I2C_End(void) {
    Wire.endTransmission();
}

#endif /* __I2C_DRIVER__ */
