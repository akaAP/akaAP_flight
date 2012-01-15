  /*************************************
 * \file TxMailbox.h
 * \brief 	Transmission Mailbox class used by SerialPOrt.
 *
 * \author: jan bolting
 *
 *
 **************************************/

#ifndef TXMAILBOX_H_
#define TXMAILBOX_H_

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../inc/serviceFunctions.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_LED_CPP.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"


class TxMailbox{
public:
	TxMailbox();
	~TxMailbox();
	static const uint8_t txMailboxLength = 100;
	char data[TxMailbox::txMailboxLength];
	uint16_t numberOfDataToBeSent;						//
	volatile uint16_t indexOfNextWrite;					//Indicates at which index the next byte should be written and implicitly shows; volatile, since it's changed in ISRs.
														//how many bytes are supposed to be sent by DMA once the mailbox is full or is sent by the user.
	volatile uint8_t wantsToBeSent;						//Indicates whether this mailbox has to be sent yet; volatile, since it's changed in ISRs.
	uint8_t number;										//Index of the mailbox in an array.
};

#endif /* TXMAILBOX_H_ */
