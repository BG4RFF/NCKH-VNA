#include "UART_Driver.h"

void UART_Init(void (*UART_Received_CallBack)(char *, uint8_t))
{
  _UART_Received_CallBack = UART_Received_CallBack;

  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1))
  {
  }
  UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

  UARTIntDisable(UART1_BASE, UART_INT_RX);
  UARTIntClear(UART1_BASE, UART_INT_RX);
  UARTIntRegister(UART1_BASE, UART1_Handler);
  UARTIntEnable(UART1_BASE, UART_INT_RX);
}

void UART_Send(char ch)
{
  while (UARTCharGetNonBlocking(UART1_BASE))
  {
  }
  UARTCharPut(UART1_BASE, (unsigned char)ch);
}

void UART_SendStr(char *str)
{
  while (*str != '\0')
  {
    UART_Send(*str);
    str++;
  }
}

void UART1_Handler(void)
{
  if (UARTIntStatus(UART1_BASE, false) & UART_INT_RX)
	{
		if (_index <= RECEIVE_BUFFER_SIZE) _buffer[_index++] = (char)UARTCharGet(UART1_BASE);
		if (_buffer[_index - 1] == '\0')
		{
			strcpy(_sendBuffer, _buffer);
			_UART_Received_CallBack(_sendBuffer, _index);
			_index = 0;
		}
	
		UARTIntClear(UART1_BASE, UART_INT_RX);
	}
}
