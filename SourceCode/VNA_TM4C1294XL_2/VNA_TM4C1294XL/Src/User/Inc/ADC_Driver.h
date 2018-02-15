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
double ADC_read868(void);
double ADC_read2400(void);
double __AdcValueToVoltage(uint32_t AdcValue);
double __VoltageToDBm(double voltage);

#endif /* __ADC_DRIVER__ */
