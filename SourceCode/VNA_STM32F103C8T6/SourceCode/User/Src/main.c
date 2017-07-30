#include "stm32f10x.h" // Device header
#include "stdbool.h"
#include "Button_Control.h"
#include "delay.h"
#include "UART_Driver.h"
#include "LCD5110.h"
#include "ADC_Driver.h"

#include <stdio.h>
#include <string.h>

volatile uint8_t state = 0;

void Led_Config(void);
void Led_on(void);
void Led_off(void);

void UARTReceived_Callback(char *message, uint8_t size);

/* Menu */
uint8_t select = 0;
bool back = false;
bool lightOn = true;
void (*currentMenu)(void);

void menu_Main(void);
void menu_Main_BTN0_Callback(void);
void menu_Main_BTN1_Callback(void);
void menu_Main_BTN2_Callback(void);

void menuItem_RandomFreq(void);
void menuItem_RandomFreq_BTN0_Callback(void);
void menuItem_RandomFreq_BTN1_Callback(void);
void menuItem_RandomFreq_BTN2_Callback(void);

void menuItem_SetFreq(void);
void menuItem_SetFreq_BTN0_Callback(void);
void menuItem_SetFreq_BTN1_Callback(void);
void menuItem_SetFreq_BTN2_Callback(void);

void data(char *ret, float Frq, float Mag, float Phs);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/* System initialize */
	SystemInit();

	/* Module initialize */
	delay_Init();
	LCD5110_init();
	UART_Init(UARTReceived_Callback);
	Led_Config();
	Button_Init(NULL, NULL, NULL);
	ADC_init();

	/* Delay 10ms for initialization */
	delay_us(10000ul);

	/* Welcome screen */
	LCD5110_set_XY(3, 2);
	LCD5110_write_string("VNA Mini");
	LCD5110_set_XY(4, 3);
	LCD5110_write_string("UIT K9");
	delay_us(1500000ul); /* 1.5s */
	LCD5110_clear();

	/* Set default current menu */
	currentMenu = menu_Main;
	Button_SetBtn0Callback(menu_Main_BTN0_Callback);
	Button_SetBtn1Callback(menu_Main_BTN1_Callback);
	Button_SetBtn2Callback(menu_Main_BTN2_Callback);

	while (1)
	{
		currentMenu();
	}
}

void Led_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

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

void data(char *ret, float Frq, float Mag, float Phs)
{
	char tmp[10];

	strcpy(ret, "");

	strcat(ret, "{\"TYPE\":\"MEASURE\",\"DATA\":{\"FREQ\":");

	sprintf(tmp, "%.3f", Frq);
	strcat(ret, tmp);

	strcat(ret, ",\"MAG\":");
	sprintf(tmp, "%.3f", Mag);
	strcat(ret, tmp);

	strcat(ret, ",\"PHS\":");
	sprintf(tmp, "%.3f", Phs);
	strcat(ret, tmp);

	strcat(ret, "}}");
}

void menu_Main(void)
{
	/* INIT */
	LCD5110_clear();

	LCD5110_set_XY(0, 0);
	LCD5110_write_string("Current Value");

	LCD5110_set_XY(0, 1);
	LCD5110_write_string("MAG:");
	LCD5110_set_XY(0, 2);
	LCD5110_write_string("PHS:");

	select = 1;
	LCD5110_set_XY(0, 5);
	LCD5110_write_string("> Random Freq");

	/* LOOP */
	while (!back)
	{
		delay_us(1000000ul); /* 1s */

		/* Write MAG value */
		LCD5110_set_XY(5, 1);
		LCD5110_write_Dec(ADC_readMag());

		/* Write PHS value */
		LCD5110_set_XY(5, 2);
		LCD5110_write_Dec(ADC_readPhs());
	}

	back = false;
}

void menu_Main_BTN0_Callback(void)
{
	/* Clear item name */
	LCD5110_set_XY(2, 5);
	LCD5110_write_string("            ");
	LCD5110_set_XY(2, 5);

	switch (++select)
	{
	case 1:
		LCD5110_write_string("Random Freq");
		break;
	case 2:
		LCD5110_write_string("Set Freq");
		break;
	case 3:
		LCD5110_write_string("Light Switch");
		break;
	default:
		select = 1;
		LCD5110_write_string("Random Freq");
		break;
	}
}

void menu_Main_BTN1_Callback(void)
{
	/* Clear item name */
	LCD5110_set_XY(2, 5);
	LCD5110_write_string("            ");
	LCD5110_set_XY(2, 5);

	switch (--select)
	{
	case 1:
		LCD5110_write_string("Random Freq");
		break;
	case 2:
		LCD5110_write_string("Set Freq");
		break;
	case 3:
		LCD5110_write_string("Light Switch");
		break;
	default:
		select = 3;
		LCD5110_write_string("Light Switch");
		break;
	}
}

void menu_Main_BTN2_Callback(void)
{
	switch (select)
	{
	case 1:
		back = true;
		currentMenu = menuItem_RandomFreq;
		Button_SetBtn0Callback(menuItem_RandomFreq_BTN0_Callback);
		Button_SetBtn1Callback(menuItem_RandomFreq_BTN1_Callback);
		Button_SetBtn2Callback(menuItem_RandomFreq_BTN2_Callback);
		break;
	case 2:
		back = true;
		currentMenu = menuItem_SetFreq;
		Button_SetBtn0Callback(menuItem_SetFreq_BTN0_Callback);
		Button_SetBtn1Callback(menuItem_SetFreq_BTN1_Callback);
		Button_SetBtn2Callback(menuItem_SetFreq_BTN2_Callback);
		break;
	case 3:
		lightOn = !lightOn;
		if (lightOn)
		{
			LCD5110_light_on();
		}
		else
		{
			LCD5110_light_off();
		}
		break;
	default:
		select = 1;
		LCD5110_write_string("Random Freq");
		break;
	}
}

void menuItem_RandomFreq(void)
{
	char buff[100];
	unsigned int tmp = 0;

	/* INIT */
	LCD5110_clear();

	LCD5110_set_XY(0, 0);
	LCD5110_write_string("Freq: ");
	LCD5110_set_XY(0, 2);
	LCD5110_write_string("Mag: ");
	LCD5110_set_XY(0, 4);
	LCD5110_write_string("Phs: ");

	/* LOOP */
	while (!back)
	{
		delay_us(750000ul); /* 0.75s */

		data(buff, tmp, tmp * 2, tmp + 2);
		UART_SendStr(buff);

		LCD5110_set_XY(3, 1);
		LCD5110_write_Dec(tmp);
		LCD5110_set_XY(3, 3);
		LCD5110_write_Dec(tmp * 2);
		LCD5110_set_XY(3, 5);
		LCD5110_write_Dec(tmp + 2);

		if (tmp < 30)
		{
			tmp += 1;
		}
		else
		{
			tmp = 0;
		}
	}

	back = false;

	Button_SetBtn0Callback(menu_Main_BTN0_Callback);
	Button_SetBtn1Callback(menu_Main_BTN1_Callback);
	Button_SetBtn2Callback(menu_Main_BTN2_Callback);
}

void menuItem_RandomFreq_BTN0_Callback(void)
{
}

void menuItem_RandomFreq_BTN1_Callback(void)
{
}

void menuItem_RandomFreq_BTN2_Callback(void)
{
	currentMenu = menu_Main;
	back = true;
}

void menuItem_SetFreq(void)
{
	/* INIT */
	LCD5110_clear();

	LCD5110_set_XY(0, 0);
	LCD5110_write_string("Set Frequency");

	/* LOOP */
	while (!back)
	{
	}

	back = false;
}

void menuItem_SetFreq_BTN0_Callback(void)
{
}

void menuItem_SetFreq_BTN1_Callback(void)
{
}

void menuItem_SetFreq_BTN2_Callback(void)
{
	currentMenu = menu_Main;
	back = true;

	Button_SetBtn0Callback(menu_Main_BTN0_Callback);
	Button_SetBtn1Callback(menu_Main_BTN1_Callback);
	Button_SetBtn2Callback(menu_Main_BTN2_Callback);
}
