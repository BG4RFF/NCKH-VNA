#include "stm32f10x.h"                  // Device header
#include "cJSON.h"
#include "UART_Driver.h"

void UARTReceived_Callback(char *message, uint8_t size) {
	char a = message[0];
	char * b = &a;
	if (b != NULL)
	{
		b = NULL;
	}
}

int main(void)
{
	char a = 'a';
	char * json = &a;
	
	SystemInit();
	UART_Init(UARTReceived_Callback);
	
	cJSON * obj = cJSON_CreateObject();
	cJSON_AddStringToObject(obj, "Name", "Thao Nguyen");
	cJSON_AddNumberToObject(obj, "Age", 21);
	cJSON_AddBoolToObject(obj, "IsMale", cJSON_True);
	
	json = cJSON_Print(obj);
	
	UART_SendStr("Hello World");
	
	while (1) {};
	
	return 0;
}
