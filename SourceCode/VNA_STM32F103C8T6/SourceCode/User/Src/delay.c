#include "delay.h"

void delay_Init(void)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; /* Enable SysTick */
}

void delay_us(unsigned long microsecond)
{
	/*
	 * Load the delay period in microseconds
	 * assuming a 8MHz source
	 */
	SysTick->LOAD = microsecond * 9;

	/*
	 * Clears the current value and the count flag
	 */
	SysTick->VAL = 0;
	
	/*
	 * Waits until the count ends
	 */
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}
