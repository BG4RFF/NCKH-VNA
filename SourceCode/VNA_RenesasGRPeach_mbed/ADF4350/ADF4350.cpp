#include "ADF4350.h"

void __ADF4350_WriteRegister32(const uint32_t value) // Program a 32bits register
{
    le = 0;

    for (int i = 3; i >= 0; i--)             // loop on 4 x 8 bits
        adf.sendData((value >> 8 * i) & 0xFF); // offset, byte masking and sending via SPI

    le = 1;
    le = 0;
}

void __ADF4350_SetADF(void) // Program all the registers of the ADF4351
{
    int i = 5;
    for (; i >= 0; i--) { // Programming ADF4351 starting with R5
        __ADF4350_WriteRegister32(registers[i]);
    }
}

void __ADF4350_bitSet(uint32_t *destination, int position)
{
    *destination |= (1 << position);
}

void __ADF4350_bitClear(uint32_t *destination, int position)
{
    *destination &= ~(1 << position);
}

void __ADF4350_bitWrite(uint32_t *destination, int position, int value)
{
    if (value == 0) {
        __ADF4350_bitClear(destination, position);
    } else if (value == 1) {
        __ADF4350_bitSet(destination, position);
    }
}

void ADF4350_reset(void)
{
    __ADF4350_WriteRegister32(0x18004E62);
}

void ADF4350_Init(void)
{
    le = 1;
    ce = 1;
    
    ADF4350_reset();
    
    delay_ms(1);
}

void ADF4350_SetFrequency(double RFout)
{
    if (RFout >= 2200) {
        OutputDivider = 1;
        __ADF4350_bitWrite(&registers[4], 22, 0);
        __ADF4350_bitWrite(&registers[4], 21, 0);
        __ADF4350_bitWrite(&registers[4], 20, 0);
    }
    if (RFout < 2200) {
        OutputDivider = 2;
        __ADF4350_bitWrite(&registers[4], 22, 0);
        __ADF4350_bitWrite(&registers[4], 21, 0);
        __ADF4350_bitWrite(&registers[4], 20, 1);
    }
    if (RFout < 1100) {
        OutputDivider = 4;
        __ADF4350_bitWrite(&registers[4], 22, 0);
        __ADF4350_bitWrite(&registers[4], 21, 1);
        __ADF4350_bitWrite(&registers[4], 20, 0);
    }
    if (RFout < 550) {
        OutputDivider = 8;
        __ADF4350_bitWrite(&registers[4], 22, 0);
        __ADF4350_bitWrite(&registers[4], 21, 1);
        __ADF4350_bitWrite(&registers[4], 20, 1);
    }
    if (RFout < 275) {
        OutputDivider = 16;
        __ADF4350_bitWrite(&registers[4], 22, 1);
        __ADF4350_bitWrite(&registers[4], 21, 0);
        __ADF4350_bitWrite(&registers[4], 20, 0);
    }
    if (RFout < 137.5) {
        OutputDivider = 32;
        __ADF4350_bitWrite(&registers[4], 22, 1);
        __ADF4350_bitWrite(&registers[4], 21, 0);
        __ADF4350_bitWrite(&registers[4], 20, 1);
    }
    if (RFout < 68.75) {
        OutputDivider = 64;
        __ADF4350_bitWrite(&registers[4], 22, 1);
        __ADF4350_bitWrite(&registers[4], 21, 1);
        __ADF4350_bitWrite(&registers[4], 20, 0);
    }

    INTA = (RFout * OutputDivider) / PFDRFout;
    MOD = (PFDRFout / OutputChannelSpacing);
    FRACF = (((RFout * OutputDivider) / PFDRFout) - INTA) * MOD;
    FRAC = floor(FRACF);

    registers[0] = 0;
    registers[0] = INTA << 15; // OK
    FRAC = FRAC << 3;
    registers[0] = registers[0] + FRAC;

    registers[1] = 0;
    registers[1] = MOD << 3;
    registers[1] = registers[1] + 1; // Adding the address "001"
    __ADF4350_bitSet(&registers[1], 27);        // Prescaler on 8/9

    __ADF4350_bitSet(&registers[2], 28);   // Digital lock == "110" sur b28 b27 b26
    __ADF4350_bitSet(&registers[2], 27);   // digital lock
    __ADF4350_bitClear(&registers[2], 26); // digital lock

    __ADF4350_SetADF(); // Program all the registers of the ADF4351

}
