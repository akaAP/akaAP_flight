/*
 * \file timebase.c
 *
 * \author Jan
 */

#include "../inc/timebase.h"
#include "../../../libraries/CMSIS/CM3/CoreSupport/core_cm3.h"
#include "../deviceDrivers/inc/deviceDriver_LED_CPP.h"
#include "../../inc/main.h"
#include "../inc/InterruptManager.h"


//global system time [ms]
volatile uint32_t TimeBase::systemTime_mSec = 0;
uint32_t TimeBase::sysTick_reloadValue = 0;
int32_t TimeBase::sysTick_ticksPerMicrosecond = 0;

/**
 *	\brief Constructor, initializes a TimeBase object.
*/
void TimeBase::Init(){
	TimeBase::sysTick_ticksPerMicrosecond = SystemCoreClock/1000000;
	//Setup SysTick Timer for x millisecond interrupts, also enables Systick and Systick interrupt */
	TimeBase::sysTick_reloadValue = SystemCoreClock / 1000;
	if (SysTick_Config(sysTick_reloadValue))					//function defined in core_cm3.h
	{
		//FIXME Capture error, avoid endless loop
		while(1);
	}
	// register the SysTick interrupt handler
	InterruptManager::registerInterruptHandler(&SysTick_Handler_cute, InterruptManager::SysTick_Handler);
	// TODO check if the SysTick interrupt priority is the highest to guarantee that
	// the system time variable is increased even while other interrupt handlers are executed.
	return;
}//eof

/**
 *	\brief Constructor. Private, since there should  be no TimeBase object.
*/
TimeBase::TimeBase(){
	return;
}//eof

/**
 * \brief Destructor.
 */
TimeBase::~TimeBase(){
	 // FIXME free memory?
}//eof

/**
 * \brief Runs a delay of x microseconds.
 * \par uint32_t - delay time [µs]
 */
void TimeBase::waitMicrosec(int32_t t){
	//the SysTick counter runs from its reload value to 0, to calculate the delay
	//in a convenient way, we use the number of counter ticks since the last timer reload
	int32_t startTimeSysTick = (int32_t)( TimeBase::sysTick_reloadValue - SysTick->VAL);
	int32_t startTimeMs  	 = (int32_t) systemTime_mSec;		//overflow after 25 days

	while(1){
		//calculate the time passed since the function has been entered

		int32_t delta_sysTime = ((systemTime_mSec - startTimeMs)*1000);
		int32_t delta_sysTick = ( ((int32_t)(TimeBase::sysTick_reloadValue - SysTick->VAL)) - startTimeSysTick) / TimeBase::sysTick_ticksPerMicrosecond;
		int32_t delayPassed = delta_sysTime + delta_sysTick;
		if(delayPassed >= t){
			break;
		}
	}
	return;
}//eof

/**
 * \brief writes the current system time in an array.
 * array[0] : time in milliseconds
 * array[1] : fractional time in microseconds
 * Note: overflow after
 */
void TimeBase::getSystemTime(uint32_t* t){
	t[0] = (int32_t)systemTime_mSec;
	t[1] = (int32_t)(TimeBase::sysTick_reloadValue - SysTick->VAL)/TimeBase::sysTick_ticksPerMicrosecond;
	return;
}//eof

/**
 * \brief Returns the current system time in [ms].
 * TODO inline function to improve performance ?.
 */
uint32_t TimeBase::getSystemTimeMs(){
	return systemTime_mSec;
}//eof

/**
 * \brief SysTick interrupt handler.
 */
extern "C" void SysTick_Handler_cute(void)
{
	//static uint32_t s=0;
	//switch off the status LED
	//LED_toggle(&led);
	TimeBase::systemTime_mSec += 1;
}//eof
