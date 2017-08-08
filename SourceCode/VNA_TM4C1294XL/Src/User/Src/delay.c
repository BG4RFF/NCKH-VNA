#include "delay.h"

void delay_Init(uint32_t ui32SysClock)
{
    SysTickPeriodSet(ui32SysClock / 1000);
    IntMasterEnable();
    SysTickIntRegister(SysTickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void delay_ms(uint32_t milliseconds)
{
    g_ui32Counter = milliseconds;
    while (g_ui32Counter > 0)
    {
    }
}

void SysTickIntHandler(void)
{
    if (g_ui32Counter > 0)
        g_ui32Counter--;
}
