#ifndef __PIN_CONFIGURATION_H__
#define __PIN_CONFIGURATION_H__

/*********** HC-05 ***********/
#define HC05_SYSCTL_PERIPH_UARTx SYSCTL_PERIPH_UART3 // Clock for UART
#define HC05_SYSCTL_PERIPH_GPIOx SYSCTL_PERIPH_GPIOA // Clock for Tx, Rx GPIO
#define HC05_UART_BASE UART3_BASE

#define HC05_UART_RX_GPIO_PORT_BASE GPIO_PORTA_BASE
#define HC05_UART_RX_GPIO_PIN GPIO_PIN_4
#define HC05_UART_RX_GPIO_AF GPIO_PA4_U3RX

#define HC05_UART_TX_GPIO_PORT_BASE GPIO_PORTA_BASE
#define HC05_UART_TX_GPIO_PIN GPIO_PIN_5
#define HC05_UART_TX_GPIO_AF GPIO_PA5_U3TX

#define HC05_STATE_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOK
#define HC05_STATE_PORT_BASE GPIO_PORTK_BASE
#define HC05_STATE_PIN GPIO_PIN_7

/*********** AD8302 ***********/
#define AD_868_ADC_SYSCTL_PERIPH SYSCTL_PERIPH_ADC0
#define AD_868_ADC_AIN_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOD
#define AD_868_ADC_BASE ADC0_BASE
#define AD_868_ADC_CHANNEL ADC_CTL_CH13
#define AD_868_AIN_PORT_BASE GPIO_PORTD_BASE
#define AD_868_AIN_PIN GPIO_PIN_2

#define AD_2400_ADC_SYSCTL_PERIPH SYSCTL_PERIPH_ADC1
#define AD_2400_ADC_AIN_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOE
#define AD_2400_ADC_BASE ADC1_BASE
#define AD_2400_ADC_CHANNEL ADC_CTL_CH0
#define AD_2400_AIN_PORT_BASE GPIO_PORTE_BASE
#define AD_2400_AIN_PIN GPIO_PIN_3

/*********** LED ***********/
#define LED_RED_BUILTIN_PERIPHERAL SYSCTL_PERIPH_GPIOK
#define LED_RED_BUILTIN_PORT GPIO_PORTK_BASE
#define LED_RED_BUILTIN_PIN GPIO_PIN_2

#define LED_BLUE_BUILTIN_PERIPHERAL SYSCTL_PERIPH_GPIOB
#define LED_BLUE_BUILTIN_PORT GPIO_PORTB_BASE
#define LED_BLUE_BUILTIN_PIN GPIO_PIN_3

#define LED_GREEN_BUILTIN_PERIPHERAL SYSCTL_PERIPH_GPIOK
#define LED_GREEN_BUILTIN_PORT GPIO_PORTK_BASE
#define LED_GREEN_BUILTIN_PIN GPIO_PIN_3

/* LORA IM881A */
// LORA_TX     74 - PA0 - U0
// LORA_RX     76 - PA1 - U0
// LORA_RST    72 - PF3
#define LORA_RESET_PERIPHERAL SYSCTL_PERIPH_GPIOF
#define LORA_RESET_PORT GPIO_PORTF_BASE
#define LORA_RESET_PIN GPIO_PIN_3

/* nRF24L01 */

#endif /* __PIN_CONFIGURATION_H__ */