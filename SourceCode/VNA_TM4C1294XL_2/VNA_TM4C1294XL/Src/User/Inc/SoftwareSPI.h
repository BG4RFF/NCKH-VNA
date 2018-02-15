#ifndef __SOFTWARE_SPI_H__
#define __SOFTWARE_SPI_H__

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include "delay.h"
#include "PinConfiguration.h"

/* Methods */
void SoftwareSPI_Init(void);
void SoftwareSPI_SendData(uint8_t data);

#endif /* __SOFTWARE_SPI_H__ */
