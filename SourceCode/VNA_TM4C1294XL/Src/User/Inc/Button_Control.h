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
#include "PinConfiguration.h"

/*********** Constants ***********/

/*********** Variables ***********/
typedef struct Button_Callback_Tag
{
  void (*_btn0_Callback)(void);
  void (*_btn1_Callback)(void);
  void (*_btn2_Callback)(void);
  bool *btn0_flag;
  bool *btn1_flag;
  bool *btn2_flag;
} Button_Callback;
static Button_Callback _button_callback;

/*********** Methods ***********/
void Button_Init(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void));
void Button_SetBtn0Callback(void (*btn0_Callback)(void));
void Button_SetBtn1Callback(void (*btn1_Callback)(void));
void Button_SetBtn2Callback(void (*btn2_Callback)(void));
void Button_SetBtnsCallback(void (*btn0_Callback)(void), void (*btn1_Callback)(void), void (*btn2_Callback)(void));

void Button_SetBtn0Flag(bool *btn0_Flag);
void Button_SetBtn1Flag(bool *btn1_Flag);
void Button_SetBtn2Flag(bool *btn2_Flag);

void btn0UpdateFlag(void);
void btn1UpdateFlag(void);
void btn2UpdateFlag(void);

void GPIOPortLIntHandler(void);

#endif /* __BUTTON_CONTROL__ */
