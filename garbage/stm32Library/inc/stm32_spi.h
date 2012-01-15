 /*************************************
 * stm32_spi.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_SPI_H_
#define STM32_SPI_H_


 /*Includes*********************************/
#include "stm32_bits.h"
#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"
#include "stm32_usart.h"

 /*Definitions******************************/
/*Registers*/
/************SPI1************************/
#define SPI1_CR1						(*((u16 *) (SPI1_BASE+0x00)))		//SPI1 Control Register 1
#define SPI1_CR2						(*((u16 *) (SPI1_BASE+0x04)))		//SPI1 Control Register 2
#define SPI1_SR							(*((u16 *) (SPI1_BASE+0x08)))		//SPI1 Status Register
#define SPI1_DR							(*((u16 *) (SPI1_BASE+0x0C)))		//SPI1 Data Register
#define SPI1_CRCPR						(*((u16 *) (SPI1_BASE+0x10)))		//SPI1 CRC Polynomial Register
#define SPI1_RXCRCR						(*((u16 *) (SPI1_BASE+0x14)))		//SPI1 RX CRC Register
#define SPI1_TXCRCR						(*((u16 *) (SPI1_BASE+0x18)))		//SPI1 TX CRC Register
#define SPI1_I2SCFGR					(*((u16 *) (SPI1_BASE+0x1C)))		//SPI1_I2S Configuration Register
#define SPI1_I2SPR						(*((u16 *) (SPI1_BASE+0x20)))		//SPI1_I2S Prescaler Register

/************SPI2************************/
#define SPI2_CR1						(*((u16 *) (SPI2_BASE+0x00)))		//SPI2 Control Register 1
#define SPI2_CR2						(*((u16 *) (SPI2_BASE+0x04)))		//SPI2 Control Register 2
#define SPI2_SR							(*((u16 *) (SPI2_BASE+0x08)))		//SPI2 Status Register
#define SPI2_DR							(*((u16 *) (SPI2_BASE+0x0C)))		//SPI2 Data Register
#define SPI2_CRCPR						(*((u16 *) (SPI2_BASE+0x10)))		//SPI2 CRC Polynomial Register
#define SPI2_RXCRCR						(*((u16 *) (SPI2_BASE+0x14)))		//SPI2 RX CRC Register
#define SPI2_TXCRCR						(*((u16 *) (SPI2_BASE+0x18)))		//SPI2 TX CRC Register
#define SPI2_I2SCFGR					(*((u16 *) (SPI2_BASE+0x1C)))		//SPI2_I2S Configuration Register
#define SPI2_I2SPR						(*((u16 *) (SPI2_BASE+0x20)))		//SPI2_I2S Prescaler Register

/************SPI3************************/
#define SPI3_CR1						(*((u16 *) (SPI3_BASE+0x00)))		//SPI3 Control Register 1
#define SPI3_CR2						(*((u16 *) (SPI3_BASE+0x04)))		//SPI3 Control Register 2
#define SPI3_SR							(*((u16 *) (SPI3_BASE+0x08)))		//SPI3 Status Register
#define SPI3_DR							(*((u16 *) (SPI3_BASE+0x0C)))		//SPI3 Data Register
#define SPI3_CRCPR						(*((u16 *) (SPI3_BASE+0x10)))		//SPI3 CRC Polynomial Register
#define SPI3_RXCRCR						(*((u16 *) (SPI3_BASE+0x14)))		//SPI3 RX CRC Register
#define SPI3_TXCRCR						(*((u16 *) (SPI3_BASE+0x18)))		//SPI3 TX CRC Register
#define SPI3_I2SCFGR					(*((u16 *) (SPI3_BASE+0x1C)))		//SPI3_I2S Configuration Register
#define SPI3_I2SPR						(*((u16 *) (SPI3_BASE+0x20)))		//SPI3_I2S Prescaler Register
/*Functions********************************/
/************SPI1*************************/
void SPI1_Init();
void SPI1_SetReset_CS(u8 state);
void SPI1_SendByte(u8 databyte);
void SPI1_SetTransEdge(u8 a);				//a=1: capture/transmission on 1st transition; a=2: on 2nd transition
/*++++++++++Display DOGM-128x64***********/
void SPI1_SendByte_Display(u8 databyte);
void Device_DogDisplayInit();


#endif /* STM32_SPI_H_ */
