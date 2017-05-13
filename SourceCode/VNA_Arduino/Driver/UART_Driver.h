#ifndef __UART_DRIVER__
#define __UART_DRIVER__

/*********** Defines ***********/

/*********** Libraries ***********/

/*********** Methods ***********/
void UART_Init(void)
{
    Serial.begin(9600); /* Start UART at baudrate of 9600 (Default of HC-05) */
}

void UART_Send(uint8_t data)
{
    Serial.print(data);
}

void UART_Send(char data[])
{
    Serial.print(data);
}

#endif /* __UART_DRIVER__ */
