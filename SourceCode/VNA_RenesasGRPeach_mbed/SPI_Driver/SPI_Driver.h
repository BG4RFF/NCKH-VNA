#ifndef __SPI_DRIVER__
#define __SPI_DRIVER__

/*********** Libraries ***********/
#include "mbed.h"
#include "PinConfiguration.h"

/*********** Data Types ***********/
class SPI_Driver
{
private:
    SPI * spi;
public:
    SPI_Driver(PinName mosi, PinName miso, PinName sclk, PinName Nss = NC);
    void send(int value);
    void sendStr(char * data);
};
#endif /* __SPI_DRIVER__ */
