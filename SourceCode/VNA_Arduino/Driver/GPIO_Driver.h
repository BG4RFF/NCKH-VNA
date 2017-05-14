#ifndef __GPIO_DRIVER__
#define __GPIO_DRIVER__

/*********** Defines ***********/
enum GPIO_Pin_Mode {
    GPIO_Pin_Mode_INPUT = 0,
    GPIO_Pin_Mode_INPUT_PULLUP,
    GPIO_Pin_Mode_OUTPUT
};

enum GPIO_Pin_State {
    GPIO_Pin_State_LOW = 0,
    GPIO_Pin_State_HIGH
};

/*********** Libraries ***********/

/*********** Methods ***********/
void GPIO_Init(uint8_t Pin, GPIO_Pin_Mode mode)
{
    switch (mode)
    {
        case GPIO_Pin_Mode_INPUT:
            pinMode(Pin, INPUT);
        break;
        case GPIO_Pin_Mode_INPUT_PULLUP:
            pinMode(Pin, INPUT_PULLUP);
        break;
        case GPIO_Pin_Mode_OUTPUT:
            pinMode(Pin, OUTPUT);
        break;
        default:
            // Do nothing
        break;
    }
}

uint8_t GPIO_Input_Read(uint8_t Pin)
{
    uint8_t result = 0;

    /* Get pin digital value */
    result = digitalRead(Pin);

    return result;
}

void GPIO_Output_Write(uint8_t Pin, GPIO_Pin_State State)
{
    switch (State)
    {
        case GPIO_Pin_State_LOW: /* Low */
            digitalWrite(Pin, LOW);
        break;
        case GPIO_Pin_State_HIGH: /* High */
            digitalWrite(Pin, HIGH);
        break;
        default:
            // Do nothing
        break;    
    }
}

#endif /* __GPIO_DRIVER__ */
