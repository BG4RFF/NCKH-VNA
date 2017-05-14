#ifndef __BUTTON_CONTROL__
#define __BUTTON_CONTROL__

/*********** Defines ***********/
#define BTN0 2 /* Define button pin */
#define BTN1 3 /* Define button pin */

#define DEBOUNCE_TIME 50 /* 50ms */

/*********** Libraries ***********/
#include "Driver/GPIO_Driver.h"

/*********** Methods ***********/
void Button_Init(void)
{
    /* Init BTN0 pin as pull-up input */
    GPIO_Init(BTN0, GPIO_Pin_Mode_INPUT_PULLUP);

    /* Init BTN1 pin as pull-up input */
    GPIO_Init(BTN1, GPIO_Pin_Mode_INPUT_PULLUP);
}

uint8_t Button_get(uint8_t Button)
{
    uint8_t result = 0; /* 0 indicates that button isn't press */
    uint8_t tmp, tmp2;

    switch (Button)
    {
        case BTN0:
        case BTN1:
            tmp = GPIO_Input_Read(Button);
            delay(DEBOUNCE_TIME);
            tmp2 = GPIO_Input_Read(Button);
            if (tmp == LOW && tmp2 == HIGH)
            {
                result = 1;
            }
        break;
        default:
        break;
    }

    return result;
}

#endif /* __BUTTON_CONTROL__ */
