#ifndef __HC05_DRIVER__
#define __HC05_DRIVER__

#include "UART_Driver.h"
#include "JSONObject.h"

/* Define */
#define MAX_SEND_BUFFER 70 // Bytes

/* Data Types */
typedef void (*HC05_FrequencyReceivedCallbackFunctionPointer)(double Frequency);
typedef void (*HC05_ConnectedCallbackFunctionPointer)(void);

static HC05_FrequencyReceivedCallbackFunctionPointer __HC05_FrequencyReceivedCallback;
static HC05_ConnectedCallbackFunctionPointer __HC05_ConnectedCallback;

/* Methods */
void HC05_Init(HC05_FrequencyReceivedCallbackFunctionPointer FrequencyReceivedCallback, HC05_ConnectedCallbackFunctionPointer ConnectedCallback);
void HC05_setFrequencyReceivedCallback(HC05_FrequencyReceivedCallbackFunctionPointer callback);
void HC05_setConnectedCallback(HC05_ConnectedCallbackFunctionPointer callback);
void HC05_sendData(double Frequency, double Magnitude);
void HC05_sendHello(void);

void UART_Received_CallBack(char *, uint8_t);

#endif /* __HC05_DRIVER__ */
