 /*************************************
 * stm32_dma.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_DMA_H_
#define STM32_DMA_H_
//#include "../../CMSIS/Core/CM3/stm32f10x.h"

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"

 /*Definitions******************************/
/*Registers*/
	/*general registers*/
#define DMA1_ISR 				  	(*((u32 *) (DMA1_BASE+0x000)))				//DMA1 interrupt status register
#define DMA1_IFCR 				  	(*((u32 *) (DMA1_BASE+0x004)))				//DMA1 interrupt flag clear register
/*channel registers*/
/*channel 1*/
#define DMA1_CCR1 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x0))))		//DMA1 channel 1 configuration register
#define DMA1_CNDTR1					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x0))))		//DMA1 channel 1 number of data register
#define DMA1_CPAR1					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x0))))		//DMA1 channel 1 peripheral address register
#define DMA1_CMAR1					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x0))))		//DMA1 channel 1 memory address register
/*channel 2*/
#define DMA1_CCR2 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x1))))		//DMA1 channel 2 configuration register
#define DMA1_CNDTR2					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x1))))		//DMA1 channel 2 number of data register
#define DMA1_CPAR2					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x1))))		//DMA1 channel 2 peripheral address register
#define DMA1_CMAR2					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x1))))		//DMA1 channel 2 memory address register
/*channel 3*/
#define DMA1_CCR3 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x2))))		//DMA1 channel 3 configuration register
#define DMA1_CNDTR3					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x2))))		//DMA1 channel 3 number of data register
#define DMA1_CPAR3					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x2))))		//DMA1 channel 3 peripheral address register
#define DMA1_CMAR3					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x2))))		//DMA1 channel 3 memory address register
/*channel 4*/
#define DMA1_CCR4 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x3))))		//DMA1 channel 4 configuration register
#define DMA1_CNDTR4					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x3))))		//DMA1 channel 4 number of data register
#define DMA1_CPAR4					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x3))))		//DMA1 channel 4 peripheral address register
#define DMA1_CMAR4					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x3))))		//DMA1 channel 4 memory address register
/*channel 5*/
#define DMA1_CCR5 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x4))))		//DMA1 channel 5 configuration register
#define DMA1_CNDTR5					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x4))))		//DMA1 channel 5 number of data register
#define DMA1_CPAR5					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x4))))		//DMA1 channel 5 peripheral address register
#define DMA1_CMAR5					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x4))))		//DMA1 channel 5 memory address register
/*channel 6*/
#define DMA1_CCR6 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x5))))		//DMA1 channel 6 configuration register
#define DMA1_CNDTR6					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x5))))		//DMA1 channel 6 number of data register
#define DMA1_CPAR6					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x5))))		//DMA1 channel 6 peripheral address register
#define DMA1_CMAR6					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x5))))		//DMA1 channel 6 memory address register
/*channel 7*/
#define DMA1_CCR7 				  	(*((u32 *) (DMA1_BASE+0x008+(0x14*0x6))))		//DMA1 channel 7 configuration register
#define DMA1_CNDTR7					(*((u32 *) (DMA1_BASE+0x00C+(0x14*0x6))))		//DMA1 channel 7 number of data register
#define DMA1_CPAR7					(*((u32 *) (DMA1_BASE+0x010+(0x14*0x6))))		//DMA1 channel 7 peripheral address register
#define DMA1_CMAR7					(*((u32 *) (DMA1_BASE+0x014+(0x14*0x6))))		//DMA1 channel 7 memory address register
/*Function Prototypes**********************/
/*general functions*/
void DMA1_Init(void);
/*Channel 1 functions*/
void DMA1_Init_Ch1(void);
void DMA1_Ch1_SetTargetAddress(u32 address, u16 nod);
/*Channel 1 functions*/
void DMA1_Init_Ch4(void);
void DMA1_Ch4_SetSourceAddress(u32 address, u16 nod);
/*Channel 7 functions*/
void DMA1_Init_Ch7(void);
void DMA1_Ch7_SetSourceAddress(u32 address, u16 nod);


#endif /* STM32_DMA_H_ */
