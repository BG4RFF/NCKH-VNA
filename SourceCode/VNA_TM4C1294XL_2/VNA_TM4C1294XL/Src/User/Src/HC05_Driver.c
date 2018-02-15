#include "HC05_Driver.h"

void HC05_Init(HC05_StartPointer HC05_StartCallback, HC05_StopPointer HC05_StopCallback)
{
    UART_Init(UART_Received_CallBack);

    __HC05_StartCallback = HC05_StartCallback;
    __HC05_StopCallback = HC05_StopCallback;
}

void HC05_setStartCallback(HC05_StartPointer HC05_StartCallback)
{
    __HC05_StartCallback = HC05_StartCallback;
}

void HC05_setStopCallback(HC05_StopPointer HC05_StopCallback)
{
    __HC05_StopCallback = HC05_StopCallback;
}

void HC05_send868Data(int frequency, double result)
{
    char buffer[MAX_SEND_BUFFER];

    sprintf(buffer, "{\"TYPE\":\"F868\",\"FREQ\":%d,\"RES\":%.2f}\0", frequency, result);

    UART_SendStr(buffer);
}

void HC05_send868DataArray(double *Result_868)
{
    char buffer[MAX_SEND_BUFFER];

    char tmp[10];

    strcpy(buffer, "{\"TYPE\":\"F868A\",\"DATA\":[");

    for (int i = 0; i < 70; i++)
    {
        sprintf(tmp, "%.2f,", Result_868[i]);
        strcat(buffer, tmp);
    }

    sprintf(tmp, "%.2f", Result_868[70]);
    strcat(buffer, tmp);

    strcat(buffer, "]}");

    UART_SendStr(buffer);
}

void HC05_send2400Data(int frequency, double result)
{
    char buffer[MAX_SEND_BUFFER];

    sprintf(buffer, "{\"TYPE\":\"F2400\",\"FREQ\":%d,\"RES\":%.2f}\0", frequency, result);

    UART_SendStr(buffer);
}

void HC05_send2400DataArray(double *Result_2400)
{
    char buffer[MAX_SEND_BUFFER];

    char tmp[10];

    strcpy(buffer, "{\"TYPE\":\"F2400A\",\"DATA\":[");

    for (int i = 0; i < 125; i++)
    {
        sprintf(tmp, "%.2f,", Result_2400[i]);
        strcat(buffer, tmp);
    }

    sprintf(tmp, "%.2f", Result_2400[125]);
    strcat(buffer, tmp);

    strcat(buffer, "]}");

    UART_SendStr(buffer);
}

void HC05_sendHello(void)
{
    char *helloStr = "VNA UIT-CEEC\0";
    UART_SendStr(helloStr);
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
            if (strcmp(type, "START") == 0)
            {
                if (__HC05_StartCallback != NULL)
                {
                    __HC05_StartCallback();
                }
            }

            if (strcmp(type, "STOP") == 0)
            {
                if (__HC05_StopCallback != NULL)
                {
                    __HC05_StopCallback();
                }
            }
        }
    }
}
