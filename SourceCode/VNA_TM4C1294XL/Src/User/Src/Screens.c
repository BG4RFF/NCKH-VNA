#include "Screens.h"

Screen *GetLoadingScreen(void)
{
    return &_LoadingScreen;
}

Screen *GetMainScreen(void)
{
    return &_MainScreen;
}



void _LoadingScreen_ScreenInitFunction(void)
{
    LCD5110_set_XY(3, 2);
    LCD5110_write_string("VNA Mini");
    LCD5110_set_XY(4, 3);
    LCD5110_write_string("UIT K9");
}

void _LoadingScreen_ScreenMainFunction(void)
{
    delay_ms(1500); /* 1.5s */
    LCD5110_clear();
}

void _LoadingScreen_ScreenCloseFunction(void)
{
    ScreenManager_SetSceen(GetMainScreen());
}



void _MainScreen_ScreenInitFunction(void)
{
}

void _MainScreen_ScreenMainFunction(void)
{
}

void _MainScreen_ScreenCloseFunction(void)
{
}

void _MainScreen_Btn0Callback(void)
{
}

void _MainScreen_Btn1Callback(void)
{
}

void _MainScreen_Btn2Callback(void)
{
}
