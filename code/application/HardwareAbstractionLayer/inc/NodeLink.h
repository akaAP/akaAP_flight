/*
 * \file NodeLink.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef NODELINK_H_
#define NODELINK_H_

//Inclusions
#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h"
#include "../inc/serviceFunctions.h"
#include "../inc/InterruptManager.h"
#include "../inc/timebase.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_LED_CPP.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"

//Structure declaration
class NodeLink{
public:
	NodeLink();
	~NodeLink();
	void testLoop();
private:
	void setUp();
	void testTwoWay();
};

#endif /* NODELINK_H_ */
