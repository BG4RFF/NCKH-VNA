#include "main.h"

Led led_red(LED_0_PIN), led_green(LED_1_PIN), led_blue(LED_2_PIN);
Serial pc(USBTX, USBRX);
Button buttons(BUTTON_0_PIN, BUTTON_1_PIN, BUTTON_2_PIN);
ADC_Driver ad8302(AD8302_MAGNITUDE_PIN, AD8302_PHASE_PIN);
HC05_Driver hc05(NULL, NULL);

DigitalIn muxout(ADF435x_MUXOUT_PIN);

void System_Init(void);

void LCD_WellcomeScreen(void);
void LCD_GetFrequency(void);
void LCD_ShowResult(void);

bool connected = false;
void PhoneConnectedCallback(void);
void FrequencyReceivedCallback(float Frequency);

int main(void)
{
    System_Init();
    
    /* Welcome screen */
    pc.printf("VNA Mini\n");
    LCD_WellcomeScreen();

    while (true) {
        LCD_GetFrequency();
    }
}

void System_Init(void)
{
    // ADF
    ADF4350_Init();

    // LCD
    LCD5110_init(LCD5110_CLK_PIN, LCD5110_DIN_PIN, LCD5110_CE_PIN, LCD5110_RST_PIN, LCD5110_DC_PIN, LCD5110_LIGHT_PIN);

    delay_ms(100);

    // LED
    led_red.WriteState(Led_State_On);
    led_green.WriteState(Led_State_Off);
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
    int frequencyIndex = 0;
    int frequenciesValue[] = {315, 433, 868, 2400};
    char * frequenciesString[] = {" 315", " 433", " 868", "2400"};

    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Set Frequency:");
    LCD5110_set_XY(0, 1);
    LCD5110_write_string(" 433 MHz");

    bool btn0Flag=false, btn1Flag=false, btn2Flag=false;
    buttons.SetBtn0Flag(&btn0Flag);
    buttons.SetBtn1Flag(&btn1Flag);
    buttons.SetBtn2Flag(&btn2Flag);

    hc05.setConnectedCallback(PhoneConnectedCallback);

    while (!connected) {
        if (btn0Flag) {
            btn0Flag = false;
            break;
        }

        if (btn1Flag) {
            if (++frequencyIndex > 3) {
                frequencyIndex = 0;
            }
            LCD5110_set_XY(0, 1);
            LCD5110_write_string(frequenciesString[frequencyIndex]);
            btn1Flag = false;
        }

        if (btn2Flag) {
            light = !light;
            if (light) {
                LCD5110_light_on();
            } else {
                LCD5110_light_off();
            }

            btn2Flag = false;
        }
    }

    if (connected) {
        LCD5110_clear();
        LCD5110_set_XY(0, 0);
        LCD5110_write_string("Waiting for");
        LCD5110_set_XY(0, 1);
        LCD5110_write_string("request...");

        DigitalIn state(HC05_STATE);
        while (state == 1);

        connected = false;

        led_red.WriteState(Led_State_On);
        led_green.WriteState(Led_State_Off);
    } else {
        ADF4350_SetFrequency(frequenciesValue[frequencyIndex]);

        LCD5110_clear();
        LCD5110_set_XY(0, 0);
        LCD5110_write_string("Measuring...");
        delay_ms(DELAY_FOR_ADF_STABLE_MS);

        LCD_ShowResult();
    }
}

void LCD_ShowResult(void)
{
    float mag, phs;

    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Magnitude:");
    LCD5110_set_XY(0, 2);
    LCD5110_write_string("Phase:");

    while (true) {
        mag = ad8302.readMag();
        LCD5110_set_XY(3, 1);
        char buff[20];
        sprintf(buff, "%7.2f db", mag);
        LCD5110_write_string(buff);

        phs = ad8302.readPhs();
        LCD5110_set_XY(3, 3);
        sprintf(buff, "%7.2f deg", phs);
        LCD5110_write_string(buff);

        if (muxout != 0) {
            led_blue.WriteState(Led_State_On);
        } else {
            led_blue.WriteState(Led_State_Off);
        }

        delay_ms(500); // 0.5s
    }
}

void PhoneConnectedCallback(void)
{
    connected = true;
    hc05.setConnectedCallback(NULL);
    hc05.setFrequencyReceivedCallback(FrequencyReceivedCallback);
    hc05.sendHello();

    led_red.WriteState(Led_State_Off);
    led_green.WriteState(Led_State_On);
}

void FrequencyReceivedCallback(float Frequency)
{
    ADF4350_SetFrequency(Frequency);

    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Measuring at");
    LCD5110_set_XY(0, 1);

    char buff[30];
    sprintf(buff, "%7.2f MHz", Frequency);
    LCD5110_write_string(buff);

    delay_ms(DELAY_FOR_ADF_STABLE_MS);

    LCD5110_clear();
    LCD5110_set_XY(0, 0);
    LCD5110_write_string("Sending result");

    float mag;
    mag = ad8302.readMag();

    hc05.sendData(Frequency, mag);

    if (muxout != 0) {
        led_blue.WriteState(Led_State_On);
    } else {
        led_blue.WriteState(Led_State_Off);
    }
}
