#include "Button_Control.h"

void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void))
{
	/*----- BTNs -----*/
	_button_callback._btn0_Callback = btn0_Callback;
	_button_callback._btn1_Callback = btn1_Callback;
	_button_callback._btn2_Callback = btn2_Callback;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL))
	{
	}
	GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
	GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntDisable(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
	GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
	GPIOIntRegister(GPIO_PORTL_BASE, GPIOPortLIntHandler);
	GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_RISING_EDGE);
	GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
}

void Button_SetBtn0Callback(void (*btn0_Callback)(void))
{
	_button_callback._btn0_Callback = btn0_Callback;
}

void Button_SetBtn1Callback(void (*btn1_Callback)(void))
{
	_button_callback._btn1_Callback = btn1_Callback;
}

void Button_SetBtn2Callback(void (*btn2_Callback)(void))
{
	_button_callback._btn2_Callback = btn2_Callback;
}

void Button_SetBtnsCallback(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void))
{
	_button_callback._btn0_Callback = btn0_Callback;
	_button_callback._btn1_Callback = btn1_Callback;
	_button_callback._btn2_Callback = btn2_Callback;
}

void GPIOPortLIntHandler(void)
{
	if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_0)
	{
		if (_button_callback._btn0_Callback != NULL)
		{
			_button_callback._btn0_Callback();
		}

		GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);
	}
	if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_1)
	{
		if (_button_callback._btn1_Callback != NULL)
		{
			_button_callback._btn1_Callback();
		}

		GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);
	}
	if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_2)
	{
		if (_button_callback._btn2_Callback != NULL)
		{
			_button_callback._btn2_Callback();
		}

		GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_2);
	}
}
