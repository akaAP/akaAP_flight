 /*************************************
 * \file serviceFunctions.h
 * \author: jan
 **************************************/

#ifndef SERVICE_H_
#define SERVICE_H_

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "stm32_bits.h"

 /*Definitions******************************/
class Service
{
public:
	static void Init();
	static void waitCycles(uint32_t t);
	static uint16_t getStringLength(char* string);
	static uint8_t isBitSet(uint32_t registrum, uint8_t bitnumber);
	static void setBit(uint32_t* registerAddress , uint8_t bitnumber);
	static void clearBit(uint32_t* registerAddress , uint8_t bitnumber);
	static uint8_t enablePeripheralClock(uint32_t periphAddress);
	static char reverseBitOrder(char bit);
	static void startCycleCounter();
	static uint32_t getCycleCounterValue();
	//indicates whether the core clock cycle counter has been started and hasn't been stopped yet.
		//used by service_startCycleCounter() and service_getCycleCounterValue() to guarantee that the cycle counter
		//can't be started twice without being evaluated in the meantime since that would cause erroneous values.
	static uint8_t CoreCycleCounterLocked;
	static uint32_t cyclesPerMicrosecond;
	static uint32_t nanosecondsPerAction;
	//CM3 cycle counter register addresses used by service_startCycleCounter() and service_getCycleCounterValue()
	static uint32_t* DWT_CYCCNT;
	static uint32_t* DWT_CONTROL;
	static uint32_t* SCB_DEMCR;
private:
	//constructor is private because there should not exist an instance of this class, since all members are static.
	Service();
	~Service();


};

#endif /* SERVICE_H_ */
