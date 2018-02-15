#include "UART_Driver.h"

UART_Driver::UART_Driver(PinName TxPin, PinName RxPin, void (*UART_Received_CallBack)(char *, uint8_t) )
{
    this->_index = 0;
    memset(_buffer, '\0', RECEIVE_BUFFER_SIZE);

    this->uart = new Serial(TxPin, RxPin);
    this->uart->attach(this, &UART_Driver::uart_receive_handler);

    __UART_Received_CallBack = UART_Received_CallBack;
}

void UART_Driver::SendStr(char *str)
{
    this->uart->printf(str);
    this->uart->putc('\0');
}

void UART_Driver::uart_receive_handler()
{
    if (_index <= RECEIVE_BUFFER_SIZE) _buffer[_index++] = this->uart->getc(); /* If _buffer is available, add received char to _buffer */
    if (_buffer[_index-1] == '\0' ) { /* If the received char is \0, send it to user's function */
        strcpy(_sendBuffer, _buffer);
        if (__UART_Received_CallBack != NULL) {
            __UART_Received_CallBack(_sendBuffer, _index);
        }

        _index = 0;
    }
}
