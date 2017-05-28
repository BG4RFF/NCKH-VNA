#include "Button_Control.h"

void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void))
{
	/* Declare initialize structures */
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/*----- BTN0 -----*/
	_btn0_Callback = btn0_Callback; /* Assign Callback function */
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BTN0_RCC_APB2Periph, ENABLE);
	
	/* Configure pin as input pull-up */
	GPIO_InitStructure.GPIO_Pin  = BTN0_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(BTN0_PORT_PTR, &GPIO_InitStructure);
	
	/* Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(BTN0_GPIO_PortSource, BTN0_GPIO_PinSource);
	
	/* Configure EXTI0 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*----- BTN1 -----*/
	_btn1_Callback = btn1_Callback; /* Assign Callback function */
	
    /* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BTN1_RCC_APB2Periph, ENABLE);
	
	/* Configure pin as input pull-up */
	GPIO_InitStructure.GPIO_Pin = BTN1_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(BTN1_PORT_PTR, &GPIO_InitStructure);
	
	/* Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(BTN1_GPIO_PortSource, BTN1_GPIO_PinSource);
	
	/* Configure EXTI0 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*----- BTN2 -----*/
	_btn2_Callback = btn2_Callback; /* Assign Callback function */
	
    /* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(BTN2_RCC_APB2Periph, ENABLE);
	
	/* Configure pin as input pull-up */
	GPIO_InitStructure.GPIO_Pin = BTN2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(BTN2_PORT_PTR, &GPIO_InitStructure);
	
	/* Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(BTN2_GPIO_PortSource, BTN2_GPIO_PinSource);
	
	/* Configure EXTI0 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Button_SetBtn0Callback(void (*btn0_Callback)(void))
{
	_btn0_Callback = btn0_Callback; /* Assign Callback function */
}
	
void Button_SetBtn1Callback(void (*btn1_Callback)(void))
{
	_btn1_Callback = btn1_Callback; /* Assign Callback function */
}
	
void Button_SetBtn2Callback(void (*btn2_Callback)(void))
{
	_btn2_Callback = btn2_Callback; /* Assign Callback function */
}

void EXTI0_IRQHandler(void)
{
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		/* Call Callback function */
		_btn0_Callback();
		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		/* Call Callback function */
		_btn1_Callback();
		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void)
{
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		/* Call Callback function */
		_btn2_Callback();
		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
