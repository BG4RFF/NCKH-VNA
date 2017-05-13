#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

/*********** Defines ***********/
#define ADC_REFERENCE_VOLTAGE EXTERNAL

/*********** Libraries ***********/


/*********** Methods ***********/
void ADC_Init(uint8_t pin)
{
    /* Initial Voltage Reference */
    analogReference(ADC_REFERENCE_VOLTAGE);

    /* Init pin mode */
    //pinMode(pin, INPUT);
}

uint16_t ADC_Read(uint8_t pin)
{
    uint16_t result = 0;

    /* Read value */
    result = analogRead(pin);

    return result;
}

#endif /* __ADC_DRIVER__ */
