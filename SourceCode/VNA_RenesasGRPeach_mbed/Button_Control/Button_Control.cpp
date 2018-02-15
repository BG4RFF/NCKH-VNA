#include "Button_Control.h"

Button::Button(void)
{
    Button(BUTTON_0_PIN, BUTTON_1_PIN, BUTTON_2_PIN);
}

Button::Button(PinName Button0, PinName Button1, PinName Button2)
{
    this->Btn0 = new InterruptIn(Button0);
    this->Btn1 = new InterruptIn(Button1);
    this->Btn2 = new InterruptIn(Button2);

    memset(&flags, 0, sizeof(ButtonFlagsAddress));
}

void Button::SetBtn0Callback(void (*btn0_Callback)(void))
{
    this->Btn0->rise(btn0_Callback);
}

void Button::SetBtn0Flag(bool *btn0_Flag)
{
    flags._btn0_Flag = btn0_Flag;
    *btn0_Flag = false;
    this->Btn0->rise(btn0UpdateFlag);
}

void Button::SetBtn1Callback(void (*btn1_Callback)(void))
{
    this->Btn1->rise(btn1_Callback);
}

void Button::SetBtn1Flag(bool *btn1_Flag)
{
    flags._btn1_Flag = btn1_Flag;
    *btn1_Flag = false;
    this->Btn1->rise(btn1UpdateFlag);
}

void Button::SetBtn2Callback(void (*btn2_Callback)(void))
{
    this->Btn2->rise(btn2_Callback);
}

void Button::SetBtn2Flag(bool *btn2_Flag)
{
    flags._btn2_Flag = btn2_Flag;
    *btn2_Flag = false;
    this->Btn2->rise(btn2UpdateFlag);
}

void btn0UpdateFlag(void)
{
    if (flags._btn0_Flag != NULL) {
        *(flags._btn0_Flag) = true;
    }
}

void btn1UpdateFlag(void)
{
    if (flags._btn1_Flag != NULL) {
        *(flags._btn1_Flag) = true;
    }
}

void btn2UpdateFlag(void)
{
    if (flags._btn2_Flag != NULL) {
        *(flags._btn2_Flag) = true;
    }
}
