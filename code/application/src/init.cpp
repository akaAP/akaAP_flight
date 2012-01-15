/*************************************
 * stm32_rcc.c
 * author: jan
 * last modifications:
 *
 * description: functions to initialize and configure the chip peripherals
 **************************************/
 /*Includes*********************************/
//#include <stdint.h>
#include "../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../inc/init.h"
#include "../inc/main.h"
#include "../HardwareAbstractionLayer/inc/serviceFunctions.h"

void disable_JTAG_and_SWD();
/*Definitions******************************/


 /*Functions********************************/
/**
 * Initializes the STM32.
 */
void Init(void)
{
	//set up NVIC
	NVIC_Configuration();

	disable_JTAG_and_SWD();	// since JTAG and SWD share some pins with a USART
								// TODO integrate remapping/JTAG,SWD disabling; maybe use a PinManager module where
								// each module/driver has to request access to a pin (throwing an exception if a pin is accessed twice)?
	/*initialize device Drivers for external devices (ADCs, GPS, IMU etc.)*/
	//devices_Init(&devices);
	//initialize program modules as serialPort, canPort, spiPort etc.
	//modules_Init(&modules);
	// Initialize classes which have only static members and are not instantiated.
	TimeBase::Init();
	Service::Init();
}//eof

void disable_JTAG_and_SWD(){
	Service::enablePeripheralClock((uint32_t)AFIO);
	//disable JTAG and SWD
	AFIO->MAPR &= ~BIT24;
	AFIO->MAPR &= ~BIT25;
	AFIO->MAPR |= BIT26;
}//eof


// Use this to place vector table in RAM

	// vector-offset (TBLOFF) from bottom of SRAM. Defined in the linker script.
	extern uint32_t _isr_vectorsram_offs;
	void NVIC_Configuration(void)
	{
	  // Set the Vector Table base location at 0x20000000+_isr_vectorsram_offs
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, (uint32_t)&_isr_vectorsram_offs);
	}



// Use this to place vector table in flash
/*
	// defined by the linker (see linker script)
	extern unsigned long _isr_vectorsflash_offs;
	void NVIC_Configuration(void)
	{
	  // Set the Vector Table base location at 0x08000000(start of Flash memory) +_isr_vectorsflash_offs
	  //NVIC_SetVectorTable(NVIC_VectTab_FLASH, (uint32_t)&_isr_vectorsflash_offs);
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

	}
*/
