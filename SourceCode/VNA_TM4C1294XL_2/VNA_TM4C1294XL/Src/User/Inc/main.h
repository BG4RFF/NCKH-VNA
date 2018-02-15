#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <utils/uartstdio.h>

#include "UART_Driver.h"
#include "ADC_Driver.h"
#include "Led.h"
#include "delay.h"
#include "HC05_Driver.h"
#include "nrf.h"

/* Constants */
#define F868_MAXIMUM_FREQUENCY_OFFSET 71
#define F2400_MAXIMUM_FREQUENCY_OFFSET 126

/* Global Variables */
volatile int8_t measuringStated;

/* Methods */
void System_Init(void);
void Reset_Lora(void);
void Lora_Set_Frequency(uint8_t freq);
void InitConsole(void);
void HardFault_Handler(void);
void Led_State_ERROR(void);
void Led_State_NOT_CONNECTED(void);
void Led_State_CONNECTED(void);
void BluetoothStartCallback(void);
void BluetoothStopCallback(void);
void MeasureF868(uint32_t offset);
void MeasureF2400(uint32_t offset);
