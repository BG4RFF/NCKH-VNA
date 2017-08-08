#ifndef __SPI_DRIVER__
#define __SPI_DRIVER__

/*********** Libraries ***********/
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/*********** Constants ***********/

/*********** Data Types ***********/

/*********** Variables ***********/

/*********** Methods ***********/
void SPI_init(void);
void SPI_send(uint32_t data);
void SPI_sendStr(char data[]);

#endif /* __SPI_DRIVER__ */
