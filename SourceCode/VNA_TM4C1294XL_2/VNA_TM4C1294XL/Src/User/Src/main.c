#include "main.h"

static Led led_red = {.ui32Peripheral = LED_RED_BUILTIN_PERIPHERAL, .ui32Port = LED_RED_BUILTIN_PORT, .ui32Pin = LED_RED_BUILTIN_PIN};
static Led led_green = {.ui32Peripheral = LED_GREEN_BUILTIN_PERIPHERAL, .ui32Port = LED_GREEN_BUILTIN_PORT, .ui32Pin = LED_GREEN_BUILTIN_PIN};
static Led led_blue = {.ui32Peripheral = LED_BLUE_BUILTIN_PERIPHERAL, .ui32Port = LED_BLUE_BUILTIN_PORT, .ui32Pin = LED_BLUE_BUILTIN_PIN};

int main(void)
{
    // char text_buffer[100];
    int32_t connectedToPhoneState = 0, connectedToPhonePreviousState = 0;
    uint32_t currentF868FrequencyOffset = 0, currentF2400FrequencyOffset = 0;

    System_Init();

    // HC05_sendHello();

    measuringStated = 0;
    while (true)
    {
        connectedToPhoneState = GPIOPinRead(HC05_STATE_PORT_BASE, HC05_STATE_PIN) & HC05_STATE_PIN;

        if (connectedToPhoneState)
        {
            if (connectedToPhoneState != connectedToPhonePreviousState)
            {
                Led_State_CONNECTED();
            }

            if (measuringStated)
            {
                // Measure F868
                MeasureF868(currentF868FrequencyOffset);
                currentF868FrequencyOffset++;
                if (currentF868FrequencyOffset > F868_MAXIMUM_FREQUENCY_OFFSET)
                {
                    currentF868FrequencyOffset = 0;
                }

                // Measure F2400
                MeasureF2400(currentF2400FrequencyOffset);
                currentF2400FrequencyOffset++;
                if (currentF2400FrequencyOffset > F2400_MAXIMUM_FREQUENCY_OFFSET)
                {
                    currentF2400FrequencyOffset = 0;
                }
            }
            else
            {
                currentF868FrequencyOffset = 0;
                currentF2400FrequencyOffset = 0;
            }
        }
        else
        {
            if (connectedToPhoneState != connectedToPhonePreviousState)
            {
                Led_State_NOT_CONNECTED();
                currentF868FrequencyOffset = 0;
                currentF2400FrequencyOffset = 0;
                measuringStated = 0;
            }
        }

        connectedToPhonePreviousState = connectedToPhoneState;
    }
}

void System_Init(void)
{
    // System Clock Init
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                                SYSCTL_OSC_MAIN |
                                                SYSCTL_USE_PLL |
                                                SYSCTL_CFG_VCO_480),
                                               16000000);

    // Delay Init
    delay_Init(ui32SysClock);

    // Console Init
    InitConsole();

    // LORA Init
    SysCtlPeripheralEnable(LORA_RESET_PERIPHERAL);
    while (!SysCtlPeripheralReady(LORA_RESET_PERIPHERAL))
    {
    }
    GPIOPinTypeGPIOOutput(LORA_RESET_PORT, LORA_RESET_PIN);

    // nRF Init
		NRF_Init();

    // AD8302 Init
    ADC_init();

    // Bluetooth HC-05 Init
    HC05_Init(BluetoothStartCallback, BluetoothStopCallback);
    SysCtlPeripheralEnable(HC05_STATE_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(HC05_STATE_SYSCTL_PERIPH))
    {
    }
    GPIOPinTypeGPIOInput(HC05_STATE_PORT_BASE, HC05_STATE_PIN);

    // Led Init
    Led_Init(led_red);
    Led_Init(led_green);
    Led_Init(led_blue);
    Led_State_NOT_CONNECTED();

    // Wait for stabilizing
    delay_ms(10);
}

void Reset_Lora(void)
{
    GPIOPinWrite(LORA_RESET_PORT, LORA_RESET_PIN, 0);
    delay_ms(10);
    GPIOPinWrite(LORA_RESET_PORT, LORA_RESET_PIN, LORA_RESET_PIN);
    delay_ms(10);
}

void Lora_Set_Frequency(uint8_t freq)
{
    UARTwrite((char *)&freq, 1);
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
    //UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

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

void HardFault_Handler(void)
{
    Led_State_ERROR();
}

void Led_State_ERROR(void)
{
    Led_WriteState(led_red, Led_State_On);
    Led_WriteState(led_green, Led_State_Off);
    Led_WriteState(led_blue, Led_State_Off);
}

void Led_State_NOT_CONNECTED(void)
{
    Led_WriteState(led_red, Led_State_Off);
    Led_WriteState(led_green, Led_State_Off);
    Led_WriteState(led_blue, Led_State_On);
}

void Led_State_CONNECTED(void)
{
    Led_WriteState(led_red, Led_State_Off);
    Led_WriteState(led_green, Led_State_On);
    Led_WriteState(led_blue, Led_State_Off);
}

void BluetoothStartCallback(void)
{
    measuringStated = 1;
}

void BluetoothStopCallback(void)
{
    measuringStated = 0;
}

void MeasureF868(uint32_t offset)
{
    double measuringResult;
    char f = offset;

    UARTwrite(&f, 1);

    delay_ms(5);

    measuringResult = ADC_read868();
		measuringResult -= 4;
    HC05_send868Data(860 + offset, measuringResult);
}

void MeasureF2400(uint32_t offset)
{
    double measuringResult;

    // Set frequency
		NRF_SetChannel(offset > 125 ? 125 : offset);

    delay_ms(5);

    measuringResult = ADC_read2400();
		measuringResult *= -1;
    HC05_send2400Data(2400 + offset, measuringResult);
}
