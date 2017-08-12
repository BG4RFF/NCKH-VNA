#ifndef __SCREEN_STRUCTURE__
#define __SCREEN_STRUCTURE__

/* Libraries */
#include <stdio.h>

/* Data Type */
typedef struct Screen_Struct
{
    void (*ScreenInitFunction)(void);
    void (*ScreenMainFunction)(void);
    void (*ScreenCloseFunction)(void);
    void (*Btn0Callback)(void);
    void (*Btn1Callback)(void);
    void (*Btn2Callback)(void);

} Screen;

#endif /* __SCREEN_STRUCTURE__ */
