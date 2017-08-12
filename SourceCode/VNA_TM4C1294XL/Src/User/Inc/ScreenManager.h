#ifndef __SCREEN_MANAGER__
#define __SCREEN_MANAGER__

/* Libraries */
#include "ScreenStructure.h"
#include "Button_Control.h"

/* Variables */
static Screen* _screen = NULL;

/* Methods */
Screen ScreenManager_CreateDefaultScreen(void);
void ScreenManager_SetSceen(Screen* screen);
void ScreenManager_Run(void);

#endif /* __SCREEN_MANAGER__ */
