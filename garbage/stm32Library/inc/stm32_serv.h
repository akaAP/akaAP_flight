 /*************************************
 * stm32_serv.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_SERV_H_
#define STM32_SERV_H_

#include "stm32_bits.h"
#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"
#include "stm32_usart.h"
#include "stm32_timer.h"

//#include "../../CMSIS/Core/CM3/stm32f10x.h"

 /*Definitions******************************/

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

 /*Function Prototypes**********************/
void toggle_statusLED();
void set_statusLED(u8);
void wait(u16 t);
void wait_millisec(u32 t);
u16 stringlength(char *string);
boolean isBitSet(u32 registrum, u8 bitnumber);
void setBit(u32* registerAddress , u8 bitnumber);
void clearBit(u32* registerAddress , u8 bitnumber);
#endif /* STM32_SERV_H_ */
