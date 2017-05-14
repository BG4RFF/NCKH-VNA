#ifndef __UART_DRIVER__
#define __UART_DRIVER__

/*********** Defines ***********/
#define RX 0 /* Define Receive pin */
#define TX 1 /* Define Transmit pin */

/*********** Libraries ***********/

/*********** Methods ***********/
void UART_Init(void)
{
    /* Init pin */
    //pinMode(RX, INPUT);
    //pinMode(TX, OUTPUT);

    /* Init UART module */
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

void UART_Send(float data)
{
    Serial.print(data);
}

#endif /* __UART_DRIVER__ */
