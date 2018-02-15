#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

/*********** Libraries ***********/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/adc.h>
#include "PinConfiguration.h"

#define REFERENCE_VOLTAGE 3.3

/*********** Methods ***********/
void ADC_init(void);
double ADC_readMag(void);
double ADC_readPhs(void);

#endif /* __ADC_DRIVER__ */
