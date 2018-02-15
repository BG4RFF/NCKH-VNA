#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <utils/uartstdio.h>

#include "Button_Control.h"
#include "UART_Driver.h"
#include "ADC_Driver.h"
#include "Led.h"
#include "LCD5110.h"
#include "delay.h"
#include "HC05_Driver.h"
#include "ADF4350.h"

/* Constants */
#define DELAY_FOR_ADF_STABLE_MS 2000 // 2s

/* Global Variables */
volatile bool connected = false;

void UARTReceived_Callback(char *message, uint8_t size);
void InitConsole(void);

void LCD_WellcomeScreen(void);
void LCD_GetFrequency(void);
void PhoneConnectedCallback(void);
void FrequencyReceivedCallback(double Frequency);
void LCD_ShowResult(void);
