/*
 * \file InterruptManager.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef INTERRUPTMANAGER_H_
#define INTERRUPTMANAGER_H_

//Inclusions
#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"

//Structure declaration
class InterruptManager{
public:
	static void registerInterruptHandler(void(*interruptHandler)(), uint32_t interruptID);
	// Memory addresses of interrupt vectors, used to identify the Interrupt source
	// when calling the registerInterruptHandler([...]) function.
	// TODO use memory offsets of the vector entries and check wether the
	// table is located in SRAM or FLASH
	// TODO provide a checkIfAlreadyInUse(interruptID) to enable modules
	// check if another module is already using an interrupt. Multiple handlers possible?
	// FIXME complete list of handlers.
	static const uint32_t SysTick_Handler 				= 0x2000003C;
	static const uint32_t USART1_Handler 				= 0x200000D4;		// TODO test
	static const uint32_t USART2_Handler 				= 0x200000D8;		// TODO test
	static const uint32_t USART3_Handler 				= 0x200000DC;
	static const uint32_t USB_LP_CAN1_RX0_IRQHandler 	= 0x20000090;		// TODO test
	// TODO test all of these.
	static const uint32_t DMA1_Channel1_Handler 	= 0x2000006C;
	static const uint32_t DMA1_Channel2_Handler 	= 0x20000070;
	static const uint32_t DMA1_Channel3_Handler 	= 0x20000074;
	static const uint32_t DMA1_Channel4_Handler 	= 0x20000078;
	static const uint32_t DMA1_Channel5_Handler 	= 0x2000007C;
	static const uint32_t DMA1_Channel6_Handler 	= 0x20000080;
	static const uint32_t DMA1_Channel7_Handler 	= 0x20000084;

private:
	InterruptManager();
	~InterruptManager();
};

#endif /* INTERRUPTMANAGER_H_ */
