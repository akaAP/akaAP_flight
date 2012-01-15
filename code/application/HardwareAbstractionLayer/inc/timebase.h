/*
 * \file timebase.h
 *
 * \author Jan
 */

#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"

class TimeBase{
	public:
		static void Init();
		static void waitMicrosec(int32_t t);
		static void getSystemTime(uint32_t* t);
		static uint32_t getSystemTimeMs();
		static volatile uint32_t systemTime_mSec;
		static int32_t sysTick_ticksPerMicrosecond;
		static uint32_t sysTick_reloadValue;
	private:
		TimeBase();
		~TimeBase();
};

extern "C" void SysTick_Handler_cute(void);

#endif /* TIMEBASE_H_ */
