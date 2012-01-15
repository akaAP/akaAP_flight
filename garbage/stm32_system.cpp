
/*!\file stm32_interrupts.c
 * \brief this file holds global variables and system constants
 * e.g. the main clock frequency and the current system time
 */

#include "../inc/stm32_rcc.h"

//Define global variables
vu32 systemTime_ms = 0;					//global system time [milliseconds since reset]
vu32 systemTime_lastValue = 0;			//a variable the system timer uses, for example, to perform tasks each 2s

//Functions


u32 getSystemTime(){
	return RCC::systemTime_ms;
}//eof
