#ifndef __BUTTON_CONTROL__
#define __BUTTON_CONTROL__

/*********** Libraries ***********/
#include "mbed.h"
#include "PinConfiguration.h"

/*********** Variables ***********/
typedef struct {
    bool *_btn0_Flag, *_btn1_Flag, *_btn2_Flag;
} ButtonFlagsAddress;
static ButtonFlagsAddress flags;

void btn0UpdateFlag(void);
void btn1UpdateFlag(void);
void btn2UpdateFlag(void);

class Button
{
private:
    InterruptIn *Btn0, *Btn1, *Btn2;
public:
    Button(void);
    Button(PinName Button0, PinName Button1, PinName Button2);

    void SetBtn0Callback(void (*btn0_Callback)(void));
    void SetBtn0Flag(bool *btn0_Flag);
    void SetBtn1Callback(void (*btn1_Callback)(void));
    void SetBtn1Flag(bool *btn1_Flag);
    void SetBtn2Callback(void (*btn2_Callback)(void));
    void SetBtn2Flag(bool *btn2_Flag);
};

#endif /* __BUTTON_CONTROL__ */
