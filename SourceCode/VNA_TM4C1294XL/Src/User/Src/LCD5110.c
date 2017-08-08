#include "LCD5110.h"

void LCD5110_init()
{
    LCD5110_GPIO_Config();

    LCD5110_light_on(); // Light on
    LCD5110_DC(1);      // LCD_DC = 1;
    LCD5110_DIN(1);     // SPI_MO = 1;
    LCD5110_CLK(1);     // SPI_SCK = 1;
    LCD5110_CE(1);      // SPI_CS = 1;

    LCD5110_RST(0); // LCD_RST = 0;
    LCD5110_LCD_delay_ms(10);
    LCD5110_RST(1); // LCD_RST = 1;

    /* LCD Initialize sequence */
    LCD5110_LCD_write_byte(0x21, 0);
    LCD5110_LCD_write_byte(0xc6, 0);
    LCD5110_LCD_write_byte(0x06, 0);
    LCD5110_LCD_write_byte(0x13, 0);
    LCD5110_LCD_write_byte(0x20, 0);
    LCD5110_clear();
    LCD5110_LCD_write_byte(0x0c, 0);
}

void LCD5110_LCD_write_byte(unsigned char dat, unsigned char mode)
{
    unsigned char i;

    /* Simulate SPI Transfer */
    LCD5110_CE(0); // SPI_CS = 0;

    if (0 == mode)
        LCD5110_DC(0); // LCD_DC = 0;
    else
        LCD5110_DC(1); // LCD_DC = 1;

    for (i = 0; i < 8; i++)
    {
        LCD5110_DIN(dat & 0x80); // SPI_MO = dat & 0x80;
        dat = dat << 1;
        LCD5110_CLK(0); // SPI_SCK = 0;
        LCD5110_CLK(1); // SPI_SCK = 1;
    }

    LCD5110_CE(1); // SPI_CS = 1;
}

void LCD5110_write_char(unsigned char c)
{
    unsigned char line;
    unsigned char ch = 0;

    c = c - 32;

    for (line = 0; line < 6; line++)
    {
        ch = font6_8[c][line];
        LCD5110_LCD_write_byte(ch, 1);
    }
}

void LCD5110_write_char_reg(unsigned char c)
{
    unsigned char line;
    unsigned char ch = 0;

    c = c - 32;

    for (line = 0; line < 6; line++)
    {
        ch = ~font6_8[c][line];
        LCD5110_LCD_write_byte(ch, 1);
    }
}

void LCD5110_write_string(char *s)
{
    unsigned char ch;
    while (*s != '\0')
    {
        ch = *s;
        LCD5110_write_char(ch);
        s++;
    }
}

void LCD5110_clear(void)
{
    unsigned char i, j;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 84; j++)
            LCD5110_LCD_write_byte(0, 1);
}

void LCD5110_set_XY(unsigned char X, unsigned char Y)
{
    unsigned char x = 6 * X;

    /* Set cursor location */
    LCD5110_LCD_write_byte(0x40 | Y, 0);
    LCD5110_LCD_write_byte(0x80 | x, 0);
}

void LCD5110_write_Dec(unsigned int b)
{

    unsigned char datas[4];

    datas[0] = b / 1000;
    b = b - datas[0] * 1000;
    datas[1] = b / 100;
    b = b - datas[1] * 100;
    datas[2] = b / 10;
    b = b - datas[2] * 10;
    datas[3] = b;

    datas[0] += 48;
    datas[1] += 48;
    datas[2] += 48;
    datas[3] += 48;

    LCD5110_write_char(datas[0]);
    LCD5110_write_char(datas[1]);
    LCD5110_write_char(datas[2]);
    LCD5110_write_char(datas[3]);

    //a++;
}

void LCD5110_light_on(void)
{
    LCD5110_LIGHT(1); // Light on
}

void LCD5110_light_off(void)
{
    LCD5110_LIGHT(0); // Light off
}

void LCD5110_LCD_delay_ms(unsigned int nCount)
{
    ////////////////////// NOT TESTED
    unsigned long t;
    t = nCount * 40000;
    while (t--)
    {
    }
}

void LCD5110_GPIO_Config(void)
{
    /* RST - PH0 */
    /* CE - PH1 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOH))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* DC - PK6 */
    /* DIN - PK7 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    /* CLK - PB5 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);

    /* LIGHT - PA7 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
}

void LCD5110_CLK(unsigned char temp)
{
    /* CLK - PB5 */
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, (temp ? 1 : 0));
}

void LCD5110_DIN(unsigned char temp)
{
    /* DIN - PK7 */
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_7, (temp ? 1 : 0));
}

void LCD5110_CE(unsigned char temp)
{
    /* CE - PH1 */
    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, (temp ? 1 : 0));
}

void LCD5110_RST(unsigned char temp)
{
    /* RST - PH0 */
    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, (temp ? 1 : 0));
}

void LCD5110_DC(unsigned char temp)
{
    /* DC - PK6 */
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_6, (temp ? 1 : 0));
}

void LCD5110_LIGHT(unsigned char temp)
{
    /* LIGHT - PA7 */
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, (temp ? 1 : 0));
}
