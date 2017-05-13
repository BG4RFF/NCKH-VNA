#ifndef __SPI_DRIVER__
#define __SPI_DRIVER__

/*********** Defines ***********/

/*********** Libraries ***********/
#include <SPI.h>

/*********** Methods ***********/
void SPI_Init(void)
{
    SPI.begin();
}

void SPI_Send(uint8_t data)
{
    SPI.beginTransaction();

    SPI.transfer(data);

    SPI.endTransaction();
}

void SPI_Send(uint8_t data[], uint8_t count)
{
    int i = 0;

    SPI.beginTransaction();

    for (i; i < count; i++)
    {
        SPI.transfer(data[i]);
    }

    SPI.endTransaction();
}

#endif /* __SPI_DRIVER__ */
