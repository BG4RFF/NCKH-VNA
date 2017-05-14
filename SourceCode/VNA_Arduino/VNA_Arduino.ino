#include "Button_Control.h"
#include "AD8302_Control.h"
#include "Driver/UART_Driver.h"

void setup() {
  Button_Init();
  AD8302_Init();
  UART_Init();
}

void loop() {
  Serial.println(AD8302_Read_Magnitude());
  Serial.println(AD8302_Read_Phase());
  delay(200);
}
