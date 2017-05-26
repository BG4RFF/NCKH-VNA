#ifndef __UART_DRIVER__
#define __UART_DRIVER__

/* Libraries */
#include "stm32f10x.h"
#include <stdlib.h>
#include <string.h>

/* Defines */
#define RECEIVE_BUFFER_SIZE 100 /* Bytes */

/* Variable */
static void (*UART_Received_CallBack)(char *, uint8_t);
static char *_buffer, *_sendBuffer;
static uint8_t _index = 0;

/* Methods */
void UART_Init(void (*_UART_Received_CallBack)(char *, uint8_t));
void UART_Send(char ch);
void UART_SendStr(char* str);

#endif /* __UART_DRIVER__ */
