/*
 * \file MAVLink.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef MAVLINK_H_
#define MAVLINK_H_

//Inclusions
#include "code/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h"
#include "../../mavlink/include/common/common.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_XBee.h"

//Function prototypes

class MAVLink{
public:
	MAVLink(USART_TypeDef* usartToUse);
	~MAVLink();
	void sendHeartbeat();
	void sendAirData();
private:
	mavlink_system_t mavlink_system;		// Helper structure for creating MAVLink messages.
	XBee* xbee;								// The XBee modem this link uses.
};


#endif /* MAVLINK_H_ */
