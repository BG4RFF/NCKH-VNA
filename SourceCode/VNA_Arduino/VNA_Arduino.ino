#include "Driver/UART_Driver.h"

void setup() {
  UART_Init();
}

void loop() {
  UART_Send(0x65);
  delay(500);
}
