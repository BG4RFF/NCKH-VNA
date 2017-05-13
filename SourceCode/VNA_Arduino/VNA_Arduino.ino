#include "Driver/GPIO_Driver.h"

uint8_t Pin = LED_BUILTIN;

void setup() {
  // put your setup code here, to run once:
  GPIO_Init(Pin, GPIO_Pin_Mode_OUTPUT);
  Serial.begin(9600);
  Serial.println(Pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  GPIO_Output_Write(Pin, GPIO_Pin_State_HIGH);
  Serial.println("HIGH");
  delay(500);

  GPIO_Output_Write(Pin, GPIO_Pin_State_LOW);
  Serial.println("LOW");
  delay(500);
}
