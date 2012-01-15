/*
 * stm32_library.h
 *
 * Author: janjan
 * @brief this header file includes all other header files, so you only have to include
 * this file to include all stm32 library headers
 */

#ifndef STM32_LIBRARY_H_
#define STM32_LIBRARY_H_

//inclusions************************

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"
#include "stm32_can.h"
#include "stm32_dma.h"
#include "stm32_exti.h"
#include "stm32_flash.h"
#include "stm32_gpio.h"
#include "stm32_i2c.h"
#include "stm32_nvic.h"
#include "stm32_math.h"
#include "stm32_spi.h"
#include "stm32_system.h"
#include "stm32_timer.h"
#include "stm32_usart.h"

extern GPIO gpioA;
extern GPIO gpioB;
extern GPIO gpioC;
extern USART usart1;

//function declarations*********************
void stm32_library_Init();


#endif /* STM32_LIBRARY_H_ */
