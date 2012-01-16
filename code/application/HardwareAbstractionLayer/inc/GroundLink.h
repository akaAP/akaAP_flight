/*
 * \file GroundLink.h
 * \brief Provides functionality to send and receive messages by a rf link.
 * \author Jan
 */

#ifndef GROUNDLINK_H_
#define GROUNDLINK_H_

//Inclusions
#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h"
#include "../inc/serviceFunctions.h"
#include "../inc/InterruptManager.h"
#include "../inc/SerialPort.h"
#include "../inc/timebase.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_XBee.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"

#include "../inc/GroundLinkMessages.h"

class GroundLink{
public:
	GroundLink(USART_TypeDef* usartToUse);
	~GroundLink();
	void sendRawInertial();
	void sendHeartbeat();
	void sendValue(int32_t valueToSend);
	void sendText(char* textToSend);
private:
	void setChecksum(uint8_t* messageStructPointer);
	XBee* xbee;								// The XBee modem this link uses.
	static const uint8_t protocolOverhead = 8;	// number of protocol overhead bytes (message id, checksum, etc.)
};

#endif /* GROUNDLINK_H_ */
