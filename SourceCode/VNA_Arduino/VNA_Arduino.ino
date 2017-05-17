#include "Button_Control.h"
#include "AD8302_Control.h"
#include "Driver/UART_Driver.h"

void setup() {
  Button_Init();
  AD8302_Init();
  UART_Init();
}

void loop() {
  UART_Send("\nMagnitude: ");
  UART_Send(AD8302_Read_Magnitude());
  UART_Send("\nPhase: ");
  UART_Send(AD8302_Read_Phase());
  delay(200);
}
