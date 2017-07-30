#include<SPI.h>

#define ADF4351_LE 3

uint32_t registers[6] = {0x4580A8, 0x80080C9, 0x4E42, 0x4B3, 0xBC803C, 0x580005};
double INT;
unsigned int long INTA, MOD, FRAC;

void WriteRegister32(const uint32_t value)
{
  digitalWrite(ADF4351_LE, LOW);
  for (int i = 3; i >= 0; i--)
    SPI.transfer((value >> 8 * i) & 0xFF);
  digitalWrite(ADF4351_LE, HIGH);
  digitalWrite(ADF4351_LE, LOW);
}

void SetADF4351()
{
  for (int i = 5; i >= 0; i--)
    WriteRegister32(registers[i]);
}

void setup()
{
  Serial.begin(9600);

  pinMode(ADF4351_LE, OUTPUT);
  digitalWrite(ADF4351_LE, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  delay(500);
  bitWrite(registers[4], 22, 0);
  bitWrite(registers[4], 21, 0);
  bitWrite(registers[4], 20, 0);

  INTA = 215;
  MOD = 5;
  FRAC = 3;

  registers[0] = 0;
  registers[0] = INTA << 15;
  FRAC = FRAC << 3;
  registers[0] = registers[0] + FRAC;

  registers[1] = 0;
  registers[1] = MOD << 3;
  registers[1] = registers[1] + 1;
  bitSet(registers[1], 27);

  bitSet(registers[2], 28);
  bitSet(registers[2], 27);
  bitClear(registers[2], 26);
}

//*************************************Loop***********************************
void loop()
{
  SetADF4351();
  Serial.println("Transmitted");
  delay(10000);

}
