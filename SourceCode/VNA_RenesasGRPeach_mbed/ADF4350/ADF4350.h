#ifndef __ADF4350__
#define __ADF4350__

/* Libraries */
#include "mbed.h"
#include "software_SPI.h"
#include <math.h>
#include "PinConfiguration.h"
#include "delay.h"

/* Defines */
#define PFDRFout (double)25
#define OutputChannelSpacing (double)0.01

/* Variables */
static uint32_t registers[6] = {0x4580A8, 0x80080C9, 0x18004E42, 0x4B3, 0x8C803C, 0x580005}; // 437 MHz with ref to 25 MHz
static int8_t OutputDivider;
static unsigned int long INTA, MOD, FRAC;
static float FRACF;
static DigitalOut le(ADF435x_LE_PIN), ce(ADF435x_CE_PIN);
static software_SPI adf(ADF435x_DAT_PIN, ADF435x_CLK_PIN);

/* Methods */
void __ADF4350_WriteRegister32(const uint32_t value);
void __ADF4350_SetADF(void);
void __ADF4350_bitSet(uint32_t *destination, int position);
void __ADF4350_bitClear(uint32_t *destination, int position);
void __ADF4350_bitWrite(uint32_t *destination, int position, int value);
void ADF4350_Init(void);
void ADF4350_SetFrequency(double RFout);
void ADF4350_reset();

#endif /* __ADF4350__ */
