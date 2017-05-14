#ifndef __HC05__
#define __HC05__

/*********** Defines ***********/

/*********** Libraries ***********/
#include "Driver/UART_Driver.h"

/*********** Methods ***********/
void HC05_Init(void)
{
    /* Init UART pin */
    UART_Init();

    /* Reset HC-05 Module */
    UART_Send("AT+RESET");
}

void HC05_Send(char *str)
{
    UART_Send(str);
}

#endif /* __HC05__ */
