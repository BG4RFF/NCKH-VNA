#include "Button_Control.h"

void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void))
{
	/*----- BTNs -----*/
	_button_callback._btn0_Callback = btn0_Callback;
	_button_callback._btn1_Callback = btn1_Callback;
	_button_callback._btn2_Callback = btn2_Callback;
	_button_callback.btn0_flag = NULL;
	_button_callback.btn1_flag = NULL;
	_button_callback.btn2_flag = NULL;

	// BTN0
	SysCtlPeripheralEnable(BUTTON_BTN0_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(BUTTON_BTN0_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOInput(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN);
	GPIOPadConfigSet(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntDisable(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN);
	GPIOIntClear(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN);
	GPIOIntRegister(BUTTON_BTN0_PORT_BASE, GPIOPortLIntHandler);
	GPIOIntTypeSet(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN, GPIO_RISING_EDGE);
	GPIOIntEnable(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN);
	
	// BTN1
	SysCtlPeripheralEnable(BUTTON_BTN1_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(BUTTON_BTN1_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOInput(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN);
	GPIOPadConfigSet(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntDisable(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN);
	GPIOIntClear(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN);
	GPIOIntRegister(BUTTON_BTN1_PORT_BASE, GPIOPortLIntHandler);
	GPIOIntTypeSet(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN, GPIO_RISING_EDGE);
	GPIOIntEnable(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN);
	
	// BTN2
	SysCtlPeripheralEnable(BUTTON_BTN2_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(BUTTON_BTN2_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOInput(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN);
	GPIOPadConfigSet(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOIntDisable(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN);
	GPIOIntClear(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN);
	GPIOIntRegister(BUTTON_BTN2_PORT_BASE, GPIOPortLIntHandler);
	GPIOIntTypeSet(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN, GPIO_RISING_EDGE);
	GPIOIntEnable(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN);
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

void Button_SetBtn0Flag(bool *btn0_Flag)
{
	_button_callback._btn0_Callback = btn0UpdateFlag;
	_button_callback.btn0_flag = btn0_Flag;
	*btn0_Flag = false;
}

void Button_SetBtn1Flag(bool *btn1_Flag)
{
	_button_callback._btn1_Callback = btn1UpdateFlag;
	_button_callback.btn1_flag = btn1_Flag;
	*btn1_Flag = false;
}

void Button_SetBtn2Flag(bool *btn2_Flag)
{
	_button_callback._btn2_Callback = btn2UpdateFlag;
	_button_callback.btn2_flag = btn2_Flag;
	*btn2_Flag = false;
}

void btn0UpdateFlag(void)
{
	*(_button_callback.btn0_flag) = true;
}

void btn1UpdateFlag(void)
{
	*(_button_callback.btn1_flag) = true;
}

void btn2UpdateFlag(void)
{
	*(_button_callback.btn2_flag) = true;
}

void GPIOPortLIntHandler(void)
{
	if (GPIOIntStatus(BUTTON_BTN0_PORT_BASE, false) & BUTTON_BTN0_PIN)
	{
		if (_button_callback._btn0_Callback != NULL)
		{
			_button_callback._btn0_Callback();
		}

		GPIOIntClear(BUTTON_BTN0_PORT_BASE, BUTTON_BTN0_PIN);
	}
	if (GPIOIntStatus(BUTTON_BTN1_PORT_BASE, false) & BUTTON_BTN1_PIN)
	{
		if (_button_callback._btn1_Callback != NULL)
		{
			_button_callback._btn1_Callback();
		}

		GPIOIntClear(BUTTON_BTN1_PORT_BASE, BUTTON_BTN1_PIN);
	}
	if (GPIOIntStatus(BUTTON_BTN2_PORT_BASE, false) & BUTTON_BTN2_PIN)
	{
		if (_button_callback._btn2_Callback != NULL)
		{
			_button_callback._btn2_Callback();
		}

		GPIOIntClear(BUTTON_BTN2_PORT_BASE, BUTTON_BTN2_PIN);
	}
}
