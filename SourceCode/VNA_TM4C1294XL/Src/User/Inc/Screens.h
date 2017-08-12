#ifndef __SCREENS__
#define __SCREENS__

/* Libraries */
#include <stdio.h>
#include "ScreenStructure.h"
#include "ScreenManager.h"
#include "delay.h"
#include "LCD5110.h"

/* Screen Methods */
void _LoadingScreen_ScreenInitFunction(void);
void _LoadingScreen_ScreenMainFunction(void);
void _LoadingScreen_ScreenCloseFunction(void);

void _MainScreen_ScreenInitFunction(void);
void _MainScreen_ScreenMainFunction(void);
void _MainScreen_ScreenCloseFunction(void);
void _MainScreen_Btn0Callback(void);
void _MainScreen_Btn1Callback(void);
void _MainScreen_Btn2Callback(void);

/* Variables */
static Screen _LoadingScreen = {.ScreenInitFunction = _LoadingScreen_ScreenInitFunction, .ScreenMainFunction = _LoadingScreen_ScreenMainFunction, .ScreenCloseFunction = NULL, .Btn0Callback = NULL, .Btn1Callback = NULL, .Btn2Callback = NULL};
static Screen _MainScreen  = {.ScreenInitFunction = _LoadingScreen_ScreenInitFunction, .ScreenMainFunction = _LoadingScreen_ScreenMainFunction, .ScreenCloseFunction = _MainScreen_ScreenCloseFunction, .Btn0Callback = _MainScreen_Btn0Callback, .Btn1Callback = _MainScreen_Btn1Callback, .Btn2Callback = _MainScreen_Btn2Callback};

/* Methods */
Screen *GetLoadingScreen(void);
Screen *GetMainScreen(void);

#endif /* __SCREENS__ */
