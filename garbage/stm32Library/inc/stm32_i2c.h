 /*************************************
 * stm32_i2c.h
 * author: jan
 * last modifications: 
 *
 * description: 
 **************************************/

#ifndef STM32_TIMER_H_
#define STM32_TIMER_H_

#include "stm32_map.h"
#include "stm32_datatypes.h"
#include "stm32_serv.h"
#include "stm32_rcc.h"
#include "stm32_gpio.h"
#include "stm32_usart.h"
#include "stm32_dma.h"
#include "stm32_adc.h"
#include "stm32_init.h"
#include "stm32_test.h"
#include "stm32_bits.h"
 /*Definitions******************************/
/*Registers*/
/*I2C1**************************************/
#define I2C1_CR1					(*((u16 *) (I2C1_BASE+0x00)))			//I2C1 control register 1
#define I2C1_CR2					(*((u16 *) (I2C1_BASE+0x04)))			//I2C1 control register 2
#define I2C1_OAR1					(*((u16 *) (I2C1_BASE+0x08)))			//I2C1 Own address register 1
#define I2C1_OAR2					(*((u16 *) (I2C1_BASE+0x0C)))			//I2C1 Own address register 2
#define I2C1_DR						(*((u16 *) (I2C1_BASE+0x10)))			//I2C1 Data register
#define I2C1_SR1					(*((u16 *) (I2C1_BASE+0x14)))			//I2C1 Status register 1
#define I2C1_SR2					(*((u16 *) (I2C1_BASE+0x18)))			//I2C1 Status register 2
#define I2C1_CCR					(*((u16 *) (I2C1_BASE+0x1C)))			//I2C1 Clock control register
#define I2C1_TRISE					(*((u16 *) (I2C1_BASE+0x20)))			//I2C1 TRISE register

/*I2C2**************************************/
#define I2C2_CR1					(*((u16 *) (I2C2_BASE+0x00)))			//I2C2 control register 1
#define I2C2_CR2					(*((u16 *) (I2C2_BASE+0x04)))			//I2C2 control register 2
#define I2C2_OAR1					(*((u16 *) (I2C2_BASE+0x08)))			//I2C2 Own address register 1
#define I2C2_OAR2					(*((u16 *) (I2C2_BASE+0x0C)))			//I2C2 Own address register 2
#define I2C2_DR						(*((u16 *) (I2C2_BASE+0x10)))			//I2C2 Data register
#define I2C2_SR1					(*((u16 *) (I2C2_BASE+0x14)))			//I2C2 Status register 1
#define I2C2_SR2					(*((u16 *) (I2C2_BASE+0x18)))			//I2C2 Status register 2
#define I2C2_CCR					(*((u16 *) (I2C2_BASE+0x1C)))			//I2C2 Clock control register
#define I2C2_TRISE					(*((u16 *) (I2C2_BASE+0x20)))			//I2C2 TRISE register

/*Function Prototypes**********************/
void I2C_Init();
#endif /* STM32_TIMER_H_ */
