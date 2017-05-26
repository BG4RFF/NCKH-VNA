#ifndef __SPI_DRIVER__
#define __SPI_DRIVER__

/*********** Libraries ***********/
#include "stm32f10x.h"
#include "delay.h"

/*********** Variables ***********/

/*********** Methods ***********/
void SPI_init(void);
void SPI_send(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t data);
void SPI_sendStr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, char data[]);

#endif /* __SPI_DRIVER__ */
