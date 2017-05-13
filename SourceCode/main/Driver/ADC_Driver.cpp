#include "ADC_Driver.h"

void ADC_Init(uint8_t pin)
{
    /* Initial Voltage Reference */
    analogReference(EXTERNAL);

    /* Init pin mode */
    //pinMode(pin, INPUT);
}

uint16_t ADC_Read(uint8_t pin)
{
    uint16_t result = 0xffff;

    /* Read value */
    result = analogRead(pin);

    return result;
}
