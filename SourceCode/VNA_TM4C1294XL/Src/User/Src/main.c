#include "main.h"

static Led led1 = {.ui32Peripheral = LED1_BUILTIN_PERIPHERAL, .ui32Port = LED1_BUILTIN_PORT, .ui32Pin = LED1_BUILTIN_PIN};
static Led led2 = {.ui32Peripheral = LED2_BUILTIN_PERIPHERAL, .ui32Port = LED2_BUILTIN_PORT, .ui32Pin = LED2_BUILTIN_PIN};
static Led led3 = {.ui32Peripheral = LED3_BUILTIN_PERIPHERAL, .ui32Port = LED3_BUILTIN_PORT, .ui32Pin = LED3_BUILTIN_PIN};
static Led led4 = {.ui32Peripheral = LED4_BUILTIN_PERIPHERAL, .ui32Port = LED4_BUILTIN_PORT, .ui32Pin = LED4_BUILTIN_PIN};

void System_Init(void);

int main(void)
{
    System_Init();

    UARTprintf("VNA Mini\nUIT K9\n");
    delay_ms(10);

    /* Welcome screen */
    HC05_sendHello(); // FOR DEBUGING
    LCD_WellcomeScreen();

    while (true)
    {
        LCD_GetFrequency();
    }
}

void System_Init(void)
{
    uint32_t ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                                SYSCTL_OSC_MAIN |
                                                SYSCTL_USE_PLL |
                                                SYSCTL_CFG_VCO_480),
                                               16000000);
    delay_Init(ui32SysClock);

    Led_Init(led1);
    Led_Init(led2);
    Led_Init(led3);
    Led_Init(led4);

    Button_Init(NULL, NULL, NULL);

    HC05_Init(NULL, NULL);

    ADC_init();

    LCD5110_init();

    ADF4350_Init();

    InitConsole();

    SysCtlPeripheralEnable(HC05_STATE_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(HC05_STATE_SYSCTL_PERIPH))
    {
    }
    GPIOPinTypeGPIOInput(HC05_STATE_PORT_BASE, HC05_STATE_PIN);

    SysCtlPeripheralEnable(HC05_EN_SYSCTL_PERIPH);
    while (!SysCtlPeripheralReady(HC05_EN_SYSCTL_PERIPH))
    {
    }
    GPIOPinTypeGPIOOutput(HC05_EN_PORT_BASE, HC05_EN_PIN);

    delay_ms(10);
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

void LCD_WellcomeScreen(void)
{
    LCD5110_set_XY(3, 2);
    LCD5110_write_string("VNA Mini");
    LCD5110_set_XY(4, 3);
    LCD5110_write_string("UIT K9");
    delay_ms(1500); /* 1.5s */
    LCD5110_clear();
}

void LCD_GetFrequency(void)
{
    bool light = true;
    int frequencyIndex = 1;
    int frequenciesValue[] = {315, 433, 868, 2400};
    char *frequenciesString[] = {" 315", " 433", " 868", "2400"};

    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Set Frequency:");
    LCD5110_set_XY(0, 1);
    LCD5110_write_string(" 433 MHz");

    bool btn0Flag = false, btn1Flag = false, btn2Flag = false;
    Button_SetBtn0Flag(&btn0Flag);
    Button_SetBtn1Flag(&btn1Flag);
    Button_SetBtn2Flag(&btn2Flag);

    HC05_setConnectedCallback(PhoneConnectedCallback);

    while (!connected)
    {
        if (btn0Flag)
        {
            btn0Flag = false;

            break;
        }

        if (btn1Flag)
        {
            if (++frequencyIndex > 3)
            {
                frequencyIndex = 0;
            }
            LCD5110_set_XY(0, 1);
            LCD5110_write_string(frequenciesString[frequencyIndex]);
            btn1Flag = false;
        }

        if (btn2Flag)
        {
            light = !light;
            if (light)
            {
                LCD5110_light_on();
            }
            else
            {
                LCD5110_light_off();
            }

            btn2Flag = false;
        }
    }

    if (connected)
    {
        LCD5110_clear();
        LCD5110_set_XY(0, 0);
        LCD5110_write_string("Waiting for");
        LCD5110_set_XY(0, 1);
        LCD5110_write_string("request...");

        // If HC05 State pin is HIGH (still connected), loop forever
        while (GPIOPinRead(HC05_STATE_PORT_BASE, HC05_STATE_PIN) & HC05_STATE_PIN)
        {
        }

        connected = false;

        // Led not connected
        Led_WriteState(led1, Led_State_Off);
    }
    else
    {
        // Set ADF to selected frequency
        ADF4350_SetFrequency(frequenciesValue[frequencyIndex]);

        LCD5110_clear();
        LCD5110_set_XY(0, 0);
        LCD5110_write_string("Measuring...");
        delay_ms(DELAY_FOR_ADF_STABLE_MS);

        LCD_ShowResult();
    }
}

void PhoneConnectedCallback(void)
{
    connected = true;
    HC05_setConnectedCallback(NULL);
    HC05_setFrequencyReceivedCallback(FrequencyReceivedCallback);
    HC05_sendHello();

    // Led connected
    Led_WriteState(led1, Led_State_On);
}

void FrequencyReceivedCallback(double Frequency)
{
    Led_WriteState(led2, Led_State_On);

    // Set ADF
    ADF4350_SetFrequency(Frequency);

    // Show processing on LCD
    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Measuring at");
    LCD5110_set_XY(0, 1);

    char buff[30];
    sprintf(buff, "%7.2f MHz", Frequency);
    LCD5110_write_string(buff);

    // Delay for ADF to stable
    delay_ms(DELAY_FOR_ADF_STABLE_MS); // stuck

    // Get result from AD8302
    double mag = 0;
    mag = ADC_readMag();

    // Show result on LCD
    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Sending result");

    // Send result to phone
    HC05_sendData(Frequency, mag);
}

void LCD_ShowResult(void)
{
    double mag = 0, phs = 0;

    // Show LCD
    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Magnitude:");
    LCD5110_set_XY(0, 2);
    LCD5110_write_string("Phase:");

    while (true)
    {
        // Get Magnitude from AD8302
        mag = ADC_readMag();

        // Show Magnitude on LCD
        LCD5110_set_XY(3, 1);
        char buff[20];
        sprintf(buff, "%7.2f db", mag);
        LCD5110_write_string(buff);

        // Get Phase from AD8302
        phs = ADC_readPhs();

        // Show Phase on LCD
        LCD5110_set_XY(3, 3);
        sprintf(buff, "%7.2f deg", phs);
        LCD5110_write_string(buff);

        delay_ms(500); // 0.5s
    }
}
