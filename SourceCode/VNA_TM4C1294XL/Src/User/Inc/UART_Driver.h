#ifndef __UART_DRIVER__
#define __UART_DRIVER__

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/uart.h>

/* Defines */
#define RECEIVE_BUFFER_SIZE 100 /* Bytes */

/* Variable */
static void (*_UART_Received_CallBack)(char *, uint8_t);
static char *_buffer, *_sendBuffer;
static uint8_t _index = 0;

/* Methods */
void UART_Init(void (*UART_Received_CallBack)(char *, uint8_t));
void UART_Send(char ch);
void UART_SendStr(char* str);

void UART1_Handler(void);

#endif /* __UART_DRIVER__ */
