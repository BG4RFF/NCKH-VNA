#include "SPI_Driver.h"

void SPI_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	/* RCC CONFIG */
	/* PCLK2 = HCLK/2 */
  RCC_PCLK2Config(RCC_HCLK_Div2);

  /* Enable GPIO clock for SPI1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE);
	
	/* GPIO CONFIG */
	/* Configure SPIz pins: SCK, MISO and MOSI ---------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* SPI CONFIG */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	/* Enable SPI_MASTER */
  SPI_Cmd(SPI1, ENABLE);
}

void SPI_send(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t data)
{
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, (uint16_t) data);
	delay_us(10000ul);
	
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
}

void SPI_sendStr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, char data[])
{
	uint8_t index = 0;
	
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET);
	
	while (data[index] != '\0')
	{
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, (uint16_t) data[index]);
		index++;
	}
	
	delay_us(10000ul);
	
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET);
}
