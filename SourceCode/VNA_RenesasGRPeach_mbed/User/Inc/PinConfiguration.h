#ifndef __PIN_CONFIGURATION__
#define __PIN_CONFIGURATION__

/* Pin configuration */
#define AD8302_MAGNITUDE_PIN A4 // P1_8
#define AD8302_PHASE_PIN     A5 // P1_9

#define BUTTON_0_PIN         A1//P7_15
#define BUTTON_1_PIN         A0//P8_1
#define BUTTON_2_PIN         A2//P2_9

#define LED_0_PIN            LED1
#define LED_1_PIN            LED2
#define LED_2_PIN            LED3

#define ADF435x_DAT_PIN      D11//P10_14
#define ADF435x_CLK_PIN      D13//P10_12
#define ADF435x_LE_PIN       D15//P8_11
#define ADF435x_MUXOUT_PIN   D0//P8_13
#define ADF435x_CE_PIN       D14

#define HC05_TX_PIN          D9//P8_15
#define HC05_RX_PIN          D8//P8_14
#define HC05_EN              D7
#define HC05_STATE           D10

#define LCD5110_CLK_PIN     D2
#define LCD5110_DIN_PIN     D3
#define LCD5110_CE_PIN      D5
#define LCD5110_RST_PIN     D6
#define LCD5110_DC_PIN      D4
#define LCD5110_LIGHT_PIN   D1

#endif /* __PIN_CONFIGURATION__ */