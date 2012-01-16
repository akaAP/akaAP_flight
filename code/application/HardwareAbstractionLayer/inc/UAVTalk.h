/*
 * \file UAVTalk.h
 * \brief Provides functionality to send and receive messages by a rf link.
 * \author Jan
 */

#ifndef UAVTALK_H_
#define UAVTALK_H_

//Inclusions
#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h"
#include "../inc/serviceFunctions.h"
#include "../inc/InterruptManager.h"
#include "../inc/SerialPort.h"
#include "../inc/timebase.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_XBee.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"

#include "../inc/UAVTalkMessages.h"

class UAVTalk{
public:
	UAVTalk(USART_TypeDef* usartToUse);
	~UAVTalk();
	void sendTestMessage();
private:
	void setUp();							// Does all kinds of initialization.
	void setChecksum(uint8_t* messageStructPointer);
	XBee* xbee;								// The XBee modem this link uses.
	static const uint8_t protocolOverhead = 11;	// number of protocol overhead bytes (message id, checksum, etc.)
};

#endif /* UAVTalk_H_ */
