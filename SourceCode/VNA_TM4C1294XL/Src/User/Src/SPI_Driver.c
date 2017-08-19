#include "SPI_Driver.h"

void SPI_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI2))
    {
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    {
    }

    GPIOPinConfigure(GPIO_PD3_SSI2CLK);
    GPIOPinConfigure(GPIO_PD2_SSI2FSS);
    GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);
    GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);

    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);

    SSIConfigSetExpClk(SSI2_BASE, 16000000, SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 1000000, 8);

    SSIEnable(SSI2_BASE);
}

void SPI_send(uint32_t data)
{
    SSIDataPut(SSI2_BASE, data); // Blocking method
}

void SPI_sendStr(char data[])
{
    uint32_t index = 0;

    for (; data[index] != '\0'; index++)
    {
        SPI_send((uint32_t)data[index]);
    }
}
