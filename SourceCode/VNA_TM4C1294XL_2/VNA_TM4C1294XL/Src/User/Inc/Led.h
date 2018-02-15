#ifndef __LED__
#define __LED__

/*********** Libraries ***********/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include "PinConfiguration.h"

/*********** Data Types ***********/
enum Led_State
{
    Led_State_Off = 0,
    Led_State_On
};

typedef struct Led_Tag
{
    uint32_t ui32Peripheral;
    uint32_t ui32Port;
    uint32_t ui32Pin;
} Led;

/*********** Variables ***********/

/*********** Methods ***********/
void Led_Init(Led led);
void Led_ToggleLed(Led led);
int32_t Led_ReadState(Led led);
void Led_WriteState(Led led, int Led_State);

#endif /* __LED__ */
