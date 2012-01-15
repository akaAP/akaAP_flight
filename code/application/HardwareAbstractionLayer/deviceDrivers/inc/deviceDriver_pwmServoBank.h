/*
 * \file deviceDriver_servoBank.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef DEVICEDRIVER_SERVOBANK_H_
#define DEVICEDRIVER_SERVOBANK_H_

//Inclusions
#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
//#include "../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_tim.h"

//class declaration
// A ServoBank represents a set of servo connectors.
class ServoBank{
	public:
		//methods
		ServoBank(	uint8_t numberOfChannels,
				TIM_TypeDef** timerPeripherals, uint8_t numberOfTimers,
				GPIO_TypeDef** gpioPortPeripherals, uint32_t* GPIOPins, uint8_t numberOfGpioPorts,
				uint32_t interval,
				uint32_t* initialChannelWidths
				);
		~ServoBank();
		void setInterval(uint32_t interval);
		void setPWMPulseWidth(uint32_t* ChannelWidths);		//sets the PWM pulsewidths to the values in the array given as a pointer
		void setPositions(int16_t* ChannelWidths);			//sets the servo position to the given values [-1000, 1000]
		uint8_t numberOfChannels;
	private:
		//methods
		uint32_t initTimer(TIM_TypeDef* timer);
		void configureGPIO(GPIO_TypeDef* gpio, uint16_t pins);
		void enableGPIOClockForPWM(GPIO_TypeDef* gpio);
		void enableTIMERClockForPWM(TIM_TypeDef* timer);
		uint32_t getTimerClock(TIM_TypeDef* timer);
		//fields
		uint8_t numberOfTimers;
		TIM_TypeDef* timerPeripherals[4];	//Pointer to the timer peripheral structures used by the ST firmware library
		uint32_t timer_nsPerTick;		// \brief indicates how many ns a timer counter cycle represents
};

#endif /* DEVICEDRIVER_SERVOBANK_H_ */
