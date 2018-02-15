#include "Led.h"

Led::Led(PinName pin)
{
    this->myled = new DigitalOut(pin);
}

void Led::Toggle(void)
{
    *(this->myled) = !this->myled->read();
}

Led_State Led::ReadState(void)
{
    return (Led_State)(this->myled->read());
}

void Led::WriteState(Led_State state)
{
    *(this->myled) = (int) state;
}
