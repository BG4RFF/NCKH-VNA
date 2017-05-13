#include <SPI.h>
#include "ADF4350.h"

#define COM_PIN 3
ADF4350 PLL(COM_PIN);

void setup() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  delay(500);

  /* 00 40 00 00 */
  PLL._r0[0] = 0x00;
  PLL._r0[1] = 0x40;
  PLL._r0[2] = 0x00;
  PLL._r0[3] = 0x00;

  /* 08 00 80 11 */
  PLL._r1[0] = 0x08;
  PLL._r1[1] = 0x00;
  PLL._r1[2] = 0x80;
  PLL._r1[3] = 0x11;

  /* 00 00 4E 42 */
  PLL._r2[0] = 0x00;
  PLL._r2[1] = 0x00;
  PLL._r2[2] = 0x4E;
  PLL._r2[3] = 0x42;

  /* 00 00 04 B3 */
  PLL._r3[0] = 0x00;
  PLL._r3[1] = 0x00;
  PLL._r3[2] = 0x04;
  PLL._r3[3] = 0xB3;

  /* 00 CC 80 3C */
  PLL._r4[0] = 0x00;
  PLL._r4[1] = 0xCC;
  PLL._r4[2] = 0x80;
  PLL._r4[3] = 0x3C;

  /* 00 58 00 05 */
  PLL._r5[0] = 0x00;
  PLL._r5[1] = 0x58;
  PLL._r5[2] = 0x00;
  PLL._r5[3] = 0x05;

  // writes registers to device
  PLL.writeRegister(PLL._r5);
  PLL.writeRegister(PLL._r4);
  PLL.writeRegister(PLL._r3);
  PLL.writeRegister(PLL._r2);
  PLL.writeRegister(PLL._r1);
  PLL.writeRegister(PLL._r0);
}

void loop() {
  
}
