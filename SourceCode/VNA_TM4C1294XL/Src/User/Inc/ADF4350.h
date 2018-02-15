#ifndef __ADF4350__
#define __ADF4350__

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include "SoftwareSPI.h"
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

/* Methods */
void __ADF4350_WriteRegister32(const uint32_t value);
void __ADF4350_SetADF(void);
void __ADF4350_bitSet(uint32_t *destination, int position);
void __ADF4350_bitClear(uint32_t *destination, int position);
void __ADF4350_bitWrite(uint32_t *destination, int position, int value);
void ADF4350_Init(void);
void ADF4350_SetFrequency(double RFout);
void ADF4350_reset(void);

#endif /* __ADF4350__ */
