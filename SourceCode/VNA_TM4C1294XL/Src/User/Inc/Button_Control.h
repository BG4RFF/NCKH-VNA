#ifndef __BUTTON_CONTROL__
#define __BUTTON_CONTROL__

/*********** Libraries ***********/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>

/*********** Constants ***********/

/*********** Variables ***********/
typedef struct Button_Callback_Tag {
    void (*_btn0_Callback)(void);
    void (*_btn1_Callback)(void);
    void (*_btn2_Callback)(void);
} Button_Callback;
static Button_Callback _button_callback;

/*********** Methods ***********/
void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void));
void Button_SetBtn0Callback(void (*btn0_Callback)(void));
void Button_SetBtn1Callback(void (*btn1_Callback)(void));
void Button_SetBtn2Callback(void (*btn2_Callback)(void));
void Button_SetBtnsCallback(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void));

void GPIOPortLIntHandler(void);

#endif /* __BUTTON_CONTROL__ */
