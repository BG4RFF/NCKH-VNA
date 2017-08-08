#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

/*********** Libraries ***********/
#include "stm32f10x.h"

/*********** Defines ***********/
#define VMAG ADC_Channel_8
#define VPHS ADC_Channel_9

/*********** Methods ***********/
void ADC_init(void);
uint16_t ADC_readADC1(uint8_t channel);
float ADC_readMag(void);
float ADC_readPhs(void);

float _ADC_to_voltage(uint16_t adc_value);

#endif /* __ADC_DRIVER__ */
