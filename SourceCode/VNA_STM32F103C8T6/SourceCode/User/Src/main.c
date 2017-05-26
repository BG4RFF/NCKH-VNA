#include "stm32f10x.h"                  // Device header
#include "Button_Control.h"
#include "delay.h"
#include "UART_Driver.h"

volatile uint8_t state = 0;

void Led_Config(void);
void Led_on(void);
void Led_off(void);

void zbtn0_Callback(void);
void zbtn1_Callback(void);
void zbtn2_Callback(void);
void UARTReceived_Callback(char *message, uint8_t size);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	char buff[100] = "AT+RESET\0";
	SystemInit();
	
	UART_Init(UARTReceived_Callback);
	delay_Init();
	Led_Config();
	Button_Init(zbtn0_Callback, zbtn1_Callback, zbtn2_Callback);
	
	delay_us(1000000ul);
	UART_SendStr(buff);
	
	while (1)
	{
		
	}
}

void Led_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	/* Enable Clock for GPIOC */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	/* Config GPIOC Pin 13 as Output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* Turn off Led */
	Led_off();
}

void Led_on(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}

void Led_off(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void zbtn0_Callback(void)
{
	if (state == 0) /* OFF */
	{
		Led_on();
		state = 1;
	}
	else
	{
		Led_off();
		state = 0;
	}
}

void zbtn1_Callback(void)
{
	if (state == 0) /* OFF */
	{
		Led_on();
		state = 1;
	}
	else
	{
		Led_off();
		state = 0;
	}
}

void zbtn2_Callback(void)
{
	if (state == 0) /* OFF */
	{
		Led_on();
		state = 1;
	}
	else
	{
		Led_off();
		state = 0;
	}
}

void UARTReceived_Callback(char *message, uint8_t size)
{
	if (state == 0) /* OFF */
	{
		Led_on();
		state = 1;
	}
	else
	{
		Led_off();
		state = 0;
	}
	
	UART_SendStr(message);
}
