#include "ScreenManager.h"

Screen ScreenManager_CreateDefaultScreen(void)
{
    Screen returnObject;
    returnObject.ScreenInitFunction = NULL;
    returnObject.ScreenMainFunction = NULL;
    returnObject.ScreenCloseFunction = NULL;
    returnObject.Btn0Callback = NULL;
    returnObject.Btn1Callback = NULL;
    returnObject.Btn2Callback = NULL;

    return returnObject;
}

void ScreenManager_SetSceen(Screen *screen)
{
    _screen = screen;

    if (_screen != NULL)
    {
        Button_SetBtnsCallback(_screen->Btn0Callback, _screen->Btn1Callback, _screen->Btn2Callback);
    }
}

void ScreenManager_Run(void)
{
    if (_screen != NULL)
    {
        if (_screen->ScreenInitFunction != NULL)
            _screen->ScreenInitFunction();

        if (_screen->ScreenMainFunction != NULL)
            _screen->ScreenMainFunction();

        if (_screen->ScreenCloseFunction != NULL)
            _screen->ScreenCloseFunction();
    }
}
