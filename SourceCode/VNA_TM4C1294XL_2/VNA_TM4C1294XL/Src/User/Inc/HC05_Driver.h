#ifndef __HC05_DRIVER__
#define __HC05_DRIVER__

#include "UART_Driver.h"
#include "JSONObject.h"

/* Define */
#define MAX_SEND_BUFFER 2048 // Bytes

/* Data Types */
typedef void (*HC05_StartPointer)(void);
typedef void (*HC05_StopPointer)(void);

static HC05_StartPointer __HC05_StartCallback;
static HC05_StopPointer __HC05_StopCallback;

/* Methods */
void HC05_Init(HC05_StartPointer HC05_StartCallback, HC05_StopPointer HC05_StopCallback);
void HC05_setStartCallback(HC05_StopPointer HC05_StopCallback);
void HC05_setStopCallback(HC05_StopPointer HC05_StopCallback);
void HC05_send868Data(int frequency, double result);
void HC05_send868DataArray(double* Result_868);
void HC05_send2400Data(int frequency, double result);
void HC05_send2400DataArray(double* Result_2400);
void HC05_sendHello(void);

void UART_Received_CallBack(char *, uint8_t);

#endif /* __HC05_DRIVER__ */
