#include "Led.h"

void Led_Init(Led led)
{
    SysCtlPeripheralEnable(led.ui32Peripheral);
    while (!SysCtlPeripheralReady(led.ui32Peripheral))
    {
    }
    GPIOPinTypeGPIOOutput(led.ui32Port, led.ui32Pin);
    Led_WriteState(led, Led_State_Off);
}

void Led_ToggleLed(Led led)
{
	int32_t registerVal = Led_ReadState(led);
	registerVal ^= led.ui32Pin;
	GPIOPinWrite(led.ui32Port, led.ui32Pin, registerVal);
}

int32_t Led_ReadState(Led led)
{
	return GPIOPinRead(led.ui32Port, led.ui32Pin);
}

void Led_WriteState(Led led, int Led_State)
{
	if (Led_State == Led_State_On)
	{
    GPIOPinWrite(led.ui32Port, led.ui32Pin, 1);
	}
	else
	{
		GPIOPinWrite(led.ui32Port, led.ui32Pin, 0);
	}
}
