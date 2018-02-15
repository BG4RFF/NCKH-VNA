#include "ADC_Driver.h"

ADC_Driver::ADC_Driver(PinName MagnitudePin, PinName PhasePin)
{
    this->mag = new AnalogIn(MagnitudePin);
    this->phs = new AnalogIn(PhasePin);
}

float ADC_Driver::readMag(void)
{
    float adcValue = *mag;
    float Voltage = REFERENCE_VOLTAGE * adcValue;
    float returnValue = (Voltage * 60/1.8) - 30;

    return returnValue;
}

float ADC_Driver::readPhs(void)
{
    float adcValue = *phs;
    float Voltage = REFERENCE_VOLTAGE * adcValue;
    float returnValue=  (180 - (Voltage * 100));

    return returnValue;
}
