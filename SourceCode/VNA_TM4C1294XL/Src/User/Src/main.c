#include "main.h"

void UARTReceived_Callback(char *message, uint8_t size);
void InitConsole(void);

int main(void)
{
    Led led1 = {.ui32Peripheral = LED1_BUILTIN_PERIPHERAL, .ui32Port = LED1_BUILTIN_PORT, .ui32Pin = LED1_BUILTIN_PIN};
    Led led2 = {.ui32Peripheral = LED2_BUILTIN_PERIPHERAL, .ui32Port = LED2_BUILTIN_PORT, .ui32Pin = LED2_BUILTIN_PIN};
    Led led3 = {.ui32Peripheral = LED3_BUILTIN_PERIPHERAL, .ui32Port = LED3_BUILTIN_PORT, .ui32Pin = LED3_BUILTIN_PIN};
    Led led4 = {.ui32Peripheral = LED4_BUILTIN_PERIPHERAL, .ui32Port = LED4_BUILTIN_PORT, .ui32Pin = LED4_BUILTIN_PIN};

    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                                SYSCTL_OSC_MAIN |
                                                SYSCTL_USE_OSC),
                                               25000000);

    delay_Init(ui32SysClock);
    UART_Init(UARTReceived_Callback);
    SPI_init();
    Led_Init(led1);
    Led_Init(led2);
    Led_Init(led3);
    Led_Init(led4);
    Button_Init(NULL, NULL, NULL);
    ADC_init();
    LCD5110_init();
    InitConsole();

    delay_ms(10);

    UARTprintf("HELLO WORLD");
    delay_ms(10);
    UART_SendStr("HELLO WORLD\0");

    /* Welcome screen */
    LCD5110_set_XY(3, 2);
    LCD5110_write_string("VNA Mini");
    LCD5110_set_XY(4, 3);
    LCD5110_write_string("UIT K9");
    delay_ms(750);

    while (true)
    {
        ScreenManager_Run();
    }
}

void UARTReceived_Callback(char *message, uint8_t size)
{

    // ECHO TEST
    UART_SendStr(message);
}

void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
