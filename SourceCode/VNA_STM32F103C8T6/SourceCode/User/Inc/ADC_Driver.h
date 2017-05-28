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
uint16_t ADC_readMag(void);
uint16_t ADC_readPhs(void);

#endif /* __ADC_DRIVER__ */
