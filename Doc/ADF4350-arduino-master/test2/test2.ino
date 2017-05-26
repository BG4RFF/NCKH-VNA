#include <SPI.h>

#define ADF4351_LE 3

volatile uint32_t registers[6] =  {0xAE8018, 0x8008029, 0x4E42, 0x4B3, 0xB5003C, 0x580005} ; // 437 MHz

void WriteRegister32(const uint32_t value)
{
  digitalWrite(ADF4351_LE, LOW);
  for (int i = 3; i >= 0; i--)
    SPI.transfer((value >> (8 * i)) & 0xFF);
  digitalWrite(ADF4351_LE, HIGH);
  digitalWrite(ADF4351_LE, LOW);
}

void SetADF4351()
{ for (int i = 5; i >= 0; i--)
    WriteRegister32(registers[i]);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ADF4351_LE, OUTPUT);          // Setup pins
  digitalWrite(ADF4351_LE, HIGH);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);           // CPHA = 0  Clock positive
  SPI.setBitOrder(MSBFIRST);
  delay(500);

  SetADF4351();
}

void loop() {
  // put your main code here, to run repeatedly:

}
