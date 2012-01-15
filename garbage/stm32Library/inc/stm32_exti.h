 /*************************************
 * stm32_exti.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/
#ifndef STM32_EXTI_H_
#define STM32_EXTI_H_

 /*Includes*********************************/
#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_serv.h"
#include "stm32_rcc.h"
#include "stm32_gpio.h"
#include "stm32_usart.h"
#include "stm32_dma.h"
#include "stm32_adc.h"
#include "stm32_bits.h"
 /*Definitions******************************/
#define EXTI_IMR 				(*((u32 *) (EXTI_BASE+0x00)))		//interrupt mask register
#define EXTI_EMR 				(*((u32 *) (EXTI_BASE+0x04)))		//event mask register
#define EXTI_RTSR 				(*((u32 *) (EXTI_BASE+0x08)))		//rising trigger selection register
#define EXTI_FTSR 				(*((u32 *) (EXTI_BASE+0x0C)))		//falling trigger selection register
#define EXTI_SWIER 				(*((u32 *) (EXTI_BASE+0x10)))		//software interrupt event register
#define EXTI_PR 				(*((u32 *) (EXTI_BASE+0x14)))		//pending register

 /*function prototypes********************************/


#endif /* STM32_EXTI_H_ */
