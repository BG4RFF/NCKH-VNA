#include "stm32f10x.h"                  // Device header

EXTI_InitTypeDef   EXTI_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

void Led_Config(void);
void Led_on(void);
void Led_off(void);

void Button_Config(void);

volatile uint8_t state = 0; /* OFF */

int main(void)
{
	Led_Config();
	Button_Config();
	while (1)
	{
		
	}
}

void Led_Config(void)
{
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

void Button_Config(void)
{
	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* Configure PA.00 pin as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Enable AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/* Connect EXTI0 Line to PA.00 pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
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
}

void EXTI0_IRQHandler(void)
{
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
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
		
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
