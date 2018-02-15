#ifndef __LED__
#define __LED__

/*********** Libraries ***********/
#include "mbed.h"
#include "PinConfiguration.h"

/*********** Data Types ***********/
typedef enum Led_State_Enum {
    Led_State_Off = 0,
    Led_State_On
} Led_State;

class Led
{
private:
    DigitalOut* myled;
public:
    Led(PinName pin);

    void Toggle(void);
    Led_State ReadState(void);
    void WriteState(Led_State state);
};

#endif /* __LED__ */