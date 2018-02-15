#ifndef __SOFTWARE_SPI__
#define __SOFTWARE_SPI__

#include "mbed.h"

#define SOFTWARE_SPI_SCK_LOW_TIME_US  15
#define SOFTWARE_SPI_SCK_HIGH_TIME_US 15

class software_SPI
{
private:
    DigitalOut *mosi, *sck;

public:
    software_SPI(PinName mosi, PinName sck);
    void sendData(char data);
};

#endif /* __SOFTWARE_SPI__ */