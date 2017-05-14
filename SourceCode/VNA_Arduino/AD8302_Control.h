#ifndef __AD8302_CONTROL__
#define __AD8302_CONTROL__

/*********** Defines ***********/
#define VMAG A0 /* Define VMAG pin */
#define VPHS A1 /* Define VPHS pin */

/*********** Libraries ***********/
#include "Driver/ADC_Driver.h"

/*********** Methods ***********/
void AD8302_Init(void)
{
    /* Init VMAG pin as ADC input */
    ADC_Init(VMAG);

    /* Init VPHS pin as ADC input */
    ADC_Init(VPHS);
}

float AD8302_Read_Magnitude(void)
{
    float result = 0, tmp = 0;

    /* Read ADC value from VMAG pin */
    tmp = ADC_Read(VMAG);

    /* Calculate magnitude ratio */
    result = -30 + (tmp * 60 / 1024);

    return result;
}

float AD8302_Read_Phase(void)
{
    float result = 0, tmp = 0;

    /* Read ADC value from VPHS pin */
    tmp = ADC_Read(VPHS);

    /* Calculate phase difference */
    result = 180 - (tmp * 180 / 1024);

    return result;
}

#endif /* __AD8302_CONTROL__ */
