#include "main.h"

void UARTReceived_Callback(char *message, uint8_t size);

int main(void)
{
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
	
	UART_Init(UARTReceived_Callback);
	Button_Init(NULL, NULL, NULL);
	
	while (true)
	{
	
	}
}

void UARTReceived_Callback(char *message, uint8_t size)
{
	
	// ECHO TEST
	UART_SendStr(message);
}
