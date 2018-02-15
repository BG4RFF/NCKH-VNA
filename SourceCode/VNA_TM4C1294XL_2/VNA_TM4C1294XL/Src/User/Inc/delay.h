#ifndef __DELAY__
#define __DELAY__

/*********** Libraries ***********/
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/*********** Variables ***********/
static volatile uint32_t g_ui32Counter = 0;

/*********** Methods ***********/
void delay_Init(uint32_t ui32SysClock);
void delay_ms(uint32_t milliseconds);
void SysTickIntHandler(void);

#endif /* __DELAY__ */
