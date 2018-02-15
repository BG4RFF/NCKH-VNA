#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

/*********** Libraries ***********/
#include "mbed.h"
#include "PinConfiguration.h"

#define REFERENCE_VOLTAGE 3.3

/*********** Data Types ***********/
class ADC_Driver
{
private:
    AnalogIn *mag, *phs;
public:
    ADC_Driver(PinName MagnitudePin, PinName PhasePin);
    float readMag(void);
    float readPhs(void);
};

#endif /* __ADC_DRIVER__ */
