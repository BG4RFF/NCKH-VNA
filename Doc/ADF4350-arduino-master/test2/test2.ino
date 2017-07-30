#include <SPI.h>

#define ADF4351_LE 3

// volatile uint32_t registers[6] =  {0x400000, 0x8008011, 0x4E42, 0x4B3, 0xCC802C, 0x580005} ; // 437 MHz
uint32_t registers[6] =  {0x580005, 0xBC803C, 0x4B3, 0x4E42, 0x80080C9, 0x4580A8 } ;

void WriteRegister32(const uint32_t value)
{
  digitalWrite(ADF4351_LE, LOW);
  for (int i = 3; i >= 0; i--)
    SPI.transfer((value >> (8 * i)) & 0xFF);
  digitalWrite(ADF4351_LE, HIGH);
  digitalWrite(ADF4351_LE, LOW);
}

void SetADF4351()
{ for (int i = 0; i <= 5; i++) {
    WriteRegister32(registers[i]);
    delay(500);
    WriteRegister32(registers[i]);
}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(ADF4351_LE, OUTPUT);          // Setup pins
  digitalWrite(ADF4351_LE, HIGH);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);           // CPHA = 0  Clock positive
  SPI.setBitOrder(MSBFIRST);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Sent");
  SetADF4351();
  delay(10000);
}
