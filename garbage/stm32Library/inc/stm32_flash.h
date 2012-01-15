 /*************************************
 * stm32_flash.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_FLASH_H_
#define STM32_FLASH_H_

#include "stm32_memoryMap.h"
#include "stm32_bits.h"
#include "stm32_datatypes.h"
 /*Definitions******************************/
#define FLASH_ACR						(*((u32 *) (FLASH_BASE+0x00)))		//flash access control register (e.g. to set wait states)

 /*Function Prototypes**********************/

#endif /* STM32_FLASH_H_ */
