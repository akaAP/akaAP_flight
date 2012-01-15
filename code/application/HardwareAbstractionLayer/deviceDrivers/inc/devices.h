/*
 * \file devices.h
 *
 * \author Jan
 * \brief Generic class representing external devices as ADCs, LEDs etc.
 */

#ifndef DEVICES_H_
#define DEVICES_H_

#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"

#include "deviceDriver_LED_CPP.h"
#include "deviceDriver_pwmServoBank.h"
#include "deviceDriver_spektrumSatellite.h"



/**
 * brief Constructor. Class is a singleton, only one should be instantiated.
 */
class Devices{
	public:
		Devices();							// Constructor.
		~Devices();							// Destructor.
		static Devices*		backPointer;			// Pointer to the síngle instance of this class.
		LED 				statusLED;				// Green status LED.
		SpektrumSatellite 	spektrumSatellite;		// Spektrum remote receiver.
		ServoBank 			servoBank;				// Servo connectors.
};
#endif /* DEVICES_H_ */
