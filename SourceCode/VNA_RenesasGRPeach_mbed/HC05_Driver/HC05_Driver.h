#ifndef __HC05_DRIVER__
#define __HC05_DRIVER__

/* Libraries */
#include "mbed.h"
#include "UART_Driver.h"
#include "JSONObject.h"
#include "PinConfiguration.h"

/* Define */
#define MAX_SEND_BUFFER 70 // Bytes

/* Data Types */
typedef void (*HC05_FrequencyReceivedCallbackFunctionPointer)(float Frequency);
typedef void (*HC05_ConnectedCallbackFunctionPointer)(void);

static HC05_FrequencyReceivedCallbackFunctionPointer __HC05_FrequencyReceivedCallback;
static HC05_ConnectedCallbackFunctionPointer __HC05_ConnectedCallback;

void UART_Received_CallBack(char *, uint8_t);

class HC05_Driver : public UART_Driver
{
public:
    HC05_Driver(HC05_FrequencyReceivedCallbackFunctionPointer FrequencyReceivedCallback, HC05_ConnectedCallbackFunctionPointer ConnectedCallback);
    void setFrequencyReceivedCallback(HC05_FrequencyReceivedCallbackFunctionPointer callback);
    void setConnectedCallback(HC05_ConnectedCallbackFunctionPointer callback);
    void sendData(float Frequency, float Magnitude);
    void sendHello(void);
};

#endif /* __HC05_DRIVER__ */