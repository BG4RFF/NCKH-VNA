#include "SoftwareSPI.h"

void SoftwareSPI_Init(void)
{
    SysCtlPeripheralEnable(ADF_SYSCTL_PERIPH_GPIOx);
	while (!SysCtlPeripheralReady(ADF_SYSCTL_PERIPH_GPIOx))
	{
	}
    GPIOPinTypeGPIOOutput(ADF_GPIO_PORT_BASE, ADF_CLK_PIN | ADF_DAT_PIN);
    GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_CLK_PIN | ADF_DAT_PIN, ADF_CLK_PIN | ADF_DAT_PIN);
}

void SoftwareSPI_SendData(uint8_t data)
{
    uint8_t counter = 0x80;
    for(; counter; counter >>= 1) {
        if (data & counter) {
            GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_DAT_PIN, ADF_DAT_PIN);
        } else {
            GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_DAT_PIN, 0);
        }

        delay_ms(1);
        GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_CLK_PIN, ADF_CLK_PIN);
        
        delay_ms(1);
        GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_CLK_PIN, 0);
    }
    GPIOPinWrite(ADF_GPIO_PORT_BASE, ADF_DAT_PIN, ADF_DAT_PIN);
}
