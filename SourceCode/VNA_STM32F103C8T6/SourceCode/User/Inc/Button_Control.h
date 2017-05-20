#ifndef __BUTTON_CONTROL__
#define __BUTTON_CONTROL__

/*********** Libraries ***********/
#include "stm32f10x.h"

/*********** Constants ***********/
#define BTN0_PORT_PTR          GPIOA
#define BTN0_Pin               GPIO_Pin_0
#define BTN0_RCC_APB2Periph    RCC_APB2Periph_GPIOA
#define BTN0_GPIO_PortSource   GPIO_PortSourceGPIOA
#define BTN0_GPIO_PinSource    GPIO_PinSource0

#define BTN1_PORT_PTR          GPIOA
#define BTN1_Pin               GPIO_Pin_1
#define BTN1_RCC_APB2Periph    RCC_APB2Periph_GPIOA
#define BTN1_GPIO_PortSource   GPIO_PortSourceGPIOA
#define BTN1_GPIO_PinSource    GPIO_PinSource1

#define BTN2_PORT_PTR          GPIOA
#define BTN2_Pin               GPIO_Pin_2
#define BTN2_RCC_APB2Periph    RCC_APB2Periph_GPIOA
#define BTN2_GPIO_PortSource   GPIO_PortSourceGPIOA
#define BTN2_GPIO_PinSource    GPIO_PinSource2

/*********** Variables ***********/
static void (*_btn0_Callback)(void);
static void (*_btn1_Callback)(void);
static void (*_btn2_Callback)(void);

/*********** Methods ***********/
void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void));

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);

#endif /* __BUTTON_CONTROL__ */
