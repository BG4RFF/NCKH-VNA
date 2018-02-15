#include "HC05_Driver.h"

void HC05_Init(HC05_FrequencyReceivedCallbackFunctionPointer FrequencyReceivedCallback, HC05_ConnectedCallbackFunctionPointer ConnectedCallback)
{
    UART_Init(UART_Received_CallBack);

    __HC05_FrequencyReceivedCallback = FrequencyReceivedCallback;
    __HC05_ConnectedCallback = ConnectedCallback;
}

void HC05_setFrequencyReceivedCallback(HC05_FrequencyReceivedCallbackFunctionPointer callback)
{
    __HC05_FrequencyReceivedCallback = callback;
}

void HC05_setConnectedCallback(HC05_ConnectedCallbackFunctionPointer callback)
{
    __HC05_ConnectedCallback = callback;
}

void HC05_sendData(double Frequency, double Magnitude)
{
    char buffer[MAX_SEND_BUFFER];

    sprintf(buffer, "{\"FREQUENCY\":%.2f,\"MAGNITUDE\":%.2f}\0", Frequency, Magnitude);
    UART_SendStr(buffer);
}

void HC05_sendHello(void)
{
    UART_SendStr("{\"TYPE\":\"HELLO\"}\0");
}

void UART_Received_CallBack(char *jsonStr, uint8_t count)
{
    JSONObject *object = JSONObject_CreateObject();
    JSONObject_OperationResultCode result = JSONObject_Parse(object, jsonStr);

    if (result == OPERATION_SUCCESS)
    {
        char *type = NULL;
        result = JSONObject_GetString(object, "TYPE", &type);

        if (result == OPERATION_SUCCESS)
        {
            if (strcmp(type, "HELLO") == 0)
            {
                if (__HC05_ConnectedCallback != NULL)
                {
                    __HC05_ConnectedCallback();
                }
            }

            if (strcmp(type, "MEASURE") == 0)
            {
                double freq = 0;
                result = JSONObject_Getdouble(object, "FREQUENCY", &freq);
                if (result == OPERATION_SUCCESS)
                {
                    if (__HC05_FrequencyReceivedCallback != NULL)
                    {
                        __HC05_FrequencyReceivedCallback(freq);
                    }
                }
            }
        }
    }
}
