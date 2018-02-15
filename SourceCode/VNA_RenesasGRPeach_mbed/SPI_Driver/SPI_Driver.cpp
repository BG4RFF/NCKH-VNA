#include "SPI_Driver.h"

SPI_Driver::SPI_Driver(PinName mosi, PinName miso, PinName sclk, PinName Nss)
{
    this->spi = new SPI(mosi, miso, sclk, Nss);
    this->spi->format(8,0);// 8 bit, mode 0
    this->spi->frequency(1000000); // 1MHz
}

void SPI_Driver::send(int value)
{
    this->spi->write(value);
}

void SPI_Driver::sendStr(char * data)
{
    uint32_t index = 0;

    for (; data[index] != '\0'; index++) {
        this->send((uint32_t)data[index]);
    }
}
