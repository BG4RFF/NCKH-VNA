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

/*********** Defines ***********/
#define VMAG ADC_Channel_8
#define VPHS ADC_Channel_9

/*********** Methods ***********/
void ADC_init(void);
uint16_t ADC_readMag(void);
uint16_t ADC_readPhs(void);

#endif /* __ADC_DRIVER__ */
