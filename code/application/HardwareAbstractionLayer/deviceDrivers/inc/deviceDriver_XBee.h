/*
 * \file deviceDriver_XBee.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef DEVICEDRIVER_XBEE_H_
#define DEVICEDRIVER_XBEE_H_

//Inclusions
#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../inc/deviceDriver_spektrumSatellite.h"
#include "../../inc/serviceFunctions.h"
#include "../inc/devices.h"
#include "../../inc/InterruptManager.h"
#include "../../inc/timebase.h"
#include "../../inc/SerialPort.h"

//Structure declaration
class XBee{
public:
	XBee(USART_TypeDef* usart);
	~XBee();
	void sendData(uint8_t* data, uint16_t numberOfBytes);
private:
	void setUp();
	SerialPort* serialPort;					// A SerialPort is used to send data by means of a USART.
	static XBee* instances[5];				// Pointers to the first five instances of this class. Actually there are not
											// expected to exist more than 1-3 XBees, so a maximum of 5 seems sufficient.
	static uint8_t numberOfInstances;
	static void serialListener_1();
	static uint8_t syncBytes[3];					 // The bytes indicating the beginning of a message.
};

#endif /* DEVICEDRIVER_XBEE_H_ */
