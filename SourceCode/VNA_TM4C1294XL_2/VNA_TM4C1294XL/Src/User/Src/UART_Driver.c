#include "UART_Driver.h"

void UART_Init(void (*UART_Received_CallBack)(char *, uint8_t))
{
	_buffer = (char *)malloc(sizeof(char) * RECEIVE_BUFFER_SIZE);
	memset(_buffer, 0, RECEIVE_BUFFER_SIZE);
	
	_sendBuffer = (char *)malloc(sizeof(char) * RECEIVE_BUFFER_SIZE);
	memset(_buffer, 0, RECEIVE_BUFFER_SIZE);
	
  _UART_Received_CallBack = UART_Received_CallBack;

  SysCtlPeripheralEnable(HC05_SYSCTL_PERIPH_UARTx);
  while (!SysCtlPeripheralReady(HC05_SYSCTL_PERIPH_UARTx))
  {
  }

  SysCtlPeripheralEnable(HC05_SYSCTL_PERIPH_GPIOx);
  while (!SysCtlPeripheralReady(HC05_SYSCTL_PERIPH_GPIOx))
  {
  }

  GPIOPinTypeUART(HC05_UART_RX_GPIO_PORT_BASE, HC05_UART_RX_GPIO_PIN);
  GPIOPinTypeUART(HC05_UART_TX_GPIO_PORT_BASE, HC05_UART_TX_GPIO_PIN);

  GPIOPinConfigure(HC05_UART_TX_GPIO_AF);
  GPIOPinConfigure(HC05_UART_RX_GPIO_AF);

  UARTConfigSetExpClk(HC05_UART_BASE, 16000000, 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTFIFODisable(HC05_UART_BASE);
	
  UARTIntDisable(HC05_UART_BASE, UART_INT_RX);
  UARTIntClear(HC05_UART_BASE, UART_INT_RX);
	IntPrioritySet(INT_UART3, 0x20);
  UARTIntRegister(HC05_UART_BASE, UART_Handler);
  UARTIntEnable(HC05_UART_BASE, UART_INT_RX);
}

void UART_Send(char ch)
{
  UARTCharPut(HC05_UART_BASE, (unsigned char)ch);
}

void UART_SendStr(char *str)
{
  while (*str != '\0')
  {
    UART_Send(*str);
    str++;
  }
	UART_Send('\0');
}

void UART_Handler(void)
{
  uint32_t status = UARTIntStatus(HC05_UART_BASE, true);
	char in;
	
  if (status & UART_INT_RX)
  {
		in = (char)UARTCharGet(HC05_UART_BASE);
    if (_index <= RECEIVE_BUFFER_SIZE)
		{
      _buffer[_index] = in;
			_index++;
		}
		
    if (in == '\0')
    {
      strcpy(_sendBuffer, _buffer);
      _UART_Received_CallBack(_sendBuffer, _index);
      _index = 0;
    }

    UARTIntClear(HC05_UART_BASE, UART_INT_RX);
  }
}
