#ifndef __UART_DRIVER__
#define __UART_DRIVER__

/* Libraries */
#include "mbed.h"
#include "PinConfiguration.h"

/* Defines */
#define RECEIVE_BUFFER_SIZE 100 /* Bytes */

/* Data Types*/
static void (*__UART_Received_CallBack)(char *, uint8_t);
class UART_Driver
{
private:
    Serial * uart;
    uint8_t _index;
    char _buffer[RECEIVE_BUFFER_SIZE];
    char _sendBuffer[RECEIVE_BUFFER_SIZE];

    void uart_receive_handler();
public:
    UART_Driver(PinName TxPin, PinName RxPin, void (*UART_Received_CallBack)(char *, uint8_t) );
    void SendStr(char *str);
};

#endif /* __UART_DRIVER__ */
