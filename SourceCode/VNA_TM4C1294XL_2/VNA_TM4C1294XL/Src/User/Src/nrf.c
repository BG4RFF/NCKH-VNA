#include "nrf.h"

void NRF_Init(void)
{
	__nrf_gpio_init();

	__software_reset();

	NRF_SetChannel(0);
	__ce_write(1);
}

void __nrf_gpio_init(void)
{
	SysCtlPeripheralEnable(NRF_CE_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(NRF_CE_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOOutput(NRF_CE_PORT_BASE, NRF_CE_PIN);

	SysCtlPeripheralEnable(NRF_CSN_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(NRF_CSN_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOOutput(NRF_CSN_PORT_BASE, NRF_CSN_PIN);

	SysCtlPeripheralEnable(NRF_SCK_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(NRF_SCK_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOOutput(NRF_SCK_PORT_BASE, NRF_SCK_PIN);

	SysCtlPeripheralEnable(NRF_MOSI_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(NRF_MOSI_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOOutput(NRF_MOSI_PORT_BASE, NRF_MOSI_PIN);

	SysCtlPeripheralEnable(NRF_MISO_SYSCTL_PERIPH);
	while (!SysCtlPeripheralReady(NRF_MISO_SYSCTL_PERIPH))
	{
	}
	GPIOPinTypeGPIOInput(NRF_MISO_PORT_BASE, NRF_MISO_PIN);

	__csn_write(1);
	__ce_write(0);
}

void __ce_write(int state)
{
	GPIOPinWrite(NRF_CE_PORT_BASE, NRF_CE_PIN, state ? NRF_CE_PIN : 0);
}
void __csn_write(int state)
{
	GPIOPinWrite(NRF_CSN_PORT_BASE, NRF_CSN_PIN, state ? NRF_CSN_PIN : 0);
}
void __sck_write(int state)
{
	GPIOPinWrite(NRF_SCK_PORT_BASE, NRF_SCK_PIN, state ? NRF_SCK_PIN : 0);
}
void __mosi_write(int state)
{
	GPIOPinWrite(NRF_MOSI_PORT_BASE, NRF_MOSI_PIN, state ? NRF_MOSI_PIN : 0);
}
void __miso_write(int state)
{
	GPIOPinWrite(NRF_MISO_PORT_BASE, NRF_MISO_PIN, state ? NRF_MISO_PIN : 0);
}
void __spi_write(char data)
{
	uint8_t bit;

	for (bit = 0x80; bit; bit >>= 1)
	{
		__mosi_write((data & bit) ? 1 : 0);

		// delay
		delay_ms(5);

		__sck_write(1);

		// delay
		delay_ms(5);

		__sck_write(0);
	}
}
void __nrf_write_register(char reg, char data)
{
	__csn_write(0);

	__spi_write(reg & 0x20);
	__spi_write(data);

	__csn_write(1);
}

void __nrf_write_multi_register(char reg, uint8_t *data, int count)
{
	int i = 0;

	__csn_write(0);

	__spi_write(reg & 0x20);
	for (i = 0; i < count; i++)
	{
		__spi_write(data[i]);
	}

	__csn_write(1);
}

void __software_reset(void)
{
	// uint8_t data[5];

	// __nrf_write_register(NRF24L01_REG_CONFIG, NRF24L01_REG_DEFAULT_VAL_CONFIG);
	// __nrf_write_register(NRF24L01_REG_EN_AA, NRF24L01_REG_DEFAULT_VAL_EN_AA);
	// __nrf_write_register(NRF24L01_REG_EN_RXADDR, NRF24L01_REG_DEFAULT_VAL_EN_RXADDR);
	// __nrf_write_register(NRF24L01_REG_SETUP_AW, NRF24L01_REG_DEFAULT_VAL_SETUP_AW);
	// __nrf_write_register(NRF24L01_REG_SETUP_RETR, NRF24L01_REG_DEFAULT_VAL_SETUP_RETR);
	// __nrf_write_register(NRF24L01_REG_RF_CH, NRF24L01_REG_DEFAULT_VAL_RF_CH);
	__nrf_write_register(NRF24L01_REG_RF_SETUP, NRF24L01_REG_DEFAULT_VAL_RF_SETUP | 0x70); // Continue wave
	// __nrf_write_register(NRF24L01_REG_STATUS, NRF24L01_REG_DEFAULT_VAL_STATUS);
	// __nrf_write_register(NRF24L01_REG_OBSERVE_TX, NRF24L01_REG_DEFAULT_VAL_OBSERVE_TX);
	// __nrf_write_register(NRF24L01_REG_RPD, NRF24L01_REG_DEFAULT_VAL_RPD);

	// data[0] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P0_0;
	// data[1] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P0_1;
	// data[2] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P0_2;
	// data[3] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P0_3;
	// data[4] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P0_4;
	// __nrf_write_multi_register(NRF24L01_REG_RX_ADDR_P1, data, 5);

	// data[0] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P1_0;
	// data[1] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P1_1;
	// data[2] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P1_2;
	// data[3] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P1_3;
	// data[4] = NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P1_4;
	// __nrf_write_multi_register(NRF24L01_REG_RX_ADDR_P1, data, 5);

	// __nrf_write_register(NRF24L01_REG_RX_ADDR_P2, NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P2);
	// __nrf_write_register(NRF24L01_REG_RX_ADDR_P3, NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P3);
	// __nrf_write_register(NRF24L01_REG_RX_ADDR_P4, NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P4);
	// __nrf_write_register(NRF24L01_REG_RX_ADDR_P5, NRF24L01_REG_DEFAULT_VAL_RX_ADDR_P5);

	// data[0] = NRF24L01_REG_DEFAULT_VAL_TX_ADDR_0;
	// data[1] = NRF24L01_REG_DEFAULT_VAL_TX_ADDR_1;
	// data[2] = NRF24L01_REG_DEFAULT_VAL_TX_ADDR_2;
	// data[3] = NRF24L01_REG_DEFAULT_VAL_TX_ADDR_3;
	// data[4] = NRF24L01_REG_DEFAULT_VAL_TX_ADDR_4;
	// __nrf_write_multi_register(NRF24L01_REG_TX_ADDR, data, 5);

	// __nrf_write_register(NRF24L01_REG_RX_PW_P0, NRF24L01_REG_DEFAULT_VAL_RX_PW_P0);
	// __nrf_write_register(NRF24L01_REG_RX_PW_P1, NRF24L01_REG_DEFAULT_VAL_RX_PW_P1);
	// __nrf_write_register(NRF24L01_REG_RX_PW_P2, NRF24L01_REG_DEFAULT_VAL_RX_PW_P2);
	// __nrf_write_register(NRF24L01_REG_RX_PW_P3, NRF24L01_REG_DEFAULT_VAL_RX_PW_P3);
	// __nrf_write_register(NRF24L01_REG_RX_PW_P4, NRF24L01_REG_DEFAULT_VAL_RX_PW_P4);
	// __nrf_write_register(NRF24L01_REG_RX_PW_P5, NRF24L01_REG_DEFAULT_VAL_RX_PW_P5);
	// __nrf_write_register(NRF24L01_REG_FIFO_STATUS, NRF24L01_REG_DEFAULT_VAL_FIFO_STATUS);
	// __nrf_write_register(NRF24L01_REG_DYNPD, NRF24L01_REG_DEFAULT_VAL_DYNPD);
	// __nrf_write_register(NRF24L01_REG_FEATURE, NRF24L01_REG_DEFAULT_VAL_FEATURE);
}

void NRF_SetChannel(uint8_t channel)
{
	__nrf_write_register(NRF24L01_REG_RF_CH, channel);
}
