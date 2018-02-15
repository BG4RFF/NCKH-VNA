#include "software_SPI.h"

software_SPI::software_SPI(PinName mosi, PinName sck)
{
    this->mosi = new DigitalOut(mosi);
    *(this->mosi) = 1;

    this->sck = new DigitalOut(sck);
    *(this->sck) = 0;
}

void software_SPI::sendData(char data)
{
    char counter = 0;
    for(; counter < 8; counter++) {
        if (data & 0x80) {
            *(this->mosi) = 1;
        } else {
            *(this->mosi) = 0;
        }

        data <<= 1;

        wait_us(SOFTWARE_SPI_SCK_LOW_TIME_US);
        *(this->sck) = 1;
        
        wait_us(SOFTWARE_SPI_SCK_HIGH_TIME_US);
        *(this->sck) = 0;
    }
    *(this->mosi) = 1;
}