#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

/*********** Libraries ***********/
#include "stm32f10x.h"

/*********** Methods ***********/
void ADC_init(void);
uint16_t ADC_readADC1(uint8_t channel);

#endif /* __ADC_DRIVER__ */
