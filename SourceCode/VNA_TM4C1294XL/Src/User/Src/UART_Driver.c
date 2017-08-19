#include "UART_Driver.h"

void UART_Init(void (*UART_Received_CallBack)(char *, uint8_t))
{
  _UART_Received_CallBack = UART_Received_CallBack;

  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5))
  {
  }

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
  }
	
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6);
	GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_7);

  GPIOPinConfigure(GPIO_PC7_U5TX);
  GPIOPinConfigure(GPIO_PC6_U5RX);

  UARTConfigSetExpClk(UART5_BASE, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

  UARTIntDisable(UART5_BASE, UART_INT_RX);
  UARTIntClear(UART5_BASE, UART_INT_RX);
  UARTIntRegister(UART5_BASE, UART1_Handler);
  UARTIntEnable(UART5_BASE, UART_INT_RX);
}

void UART_Send(char ch)
{
  UARTCharPut(UART5_BASE, (unsigned char)ch);
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
	uint32_t a = UARTIntStatus(UART5_BASE, false);
  if (a & UART_INT_RX)
  {
    if (_index <= RECEIVE_BUFFER_SIZE)
      _buffer[_index++] = (char)UARTCharGet(UART5_BASE);
    if (_buffer[_index - 1] == '\0')
    {
      strcpy(_sendBuffer, _buffer);
      _UART_Received_CallBack(_sendBuffer, _index);
      _index = 0;
    }

    UARTIntClear(UART5_BASE, UART_INT_RX);
  }
}
