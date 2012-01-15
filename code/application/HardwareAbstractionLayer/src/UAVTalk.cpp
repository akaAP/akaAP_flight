 /*************************************
 * \file UAVTalk.cpp
 * \brief
 * \author: jan bolting
 *
 **************************************/

#include "../inc/UAVTalk.h"

/**
 * \brief Constructor.
 * \param the USART peripheral the UAVTalk is supposed to use.
 */
UAVTalk::UAVTalk(USART_TypeDef* usartToUse){
	this->xbee = new XBee(usartToUse);
	this->setUp();
	return;
}//eof

/**
 * Destructor.
 */
UAVTalk::~UAVTalk(){
	// FIXME free memory
}//eof

void UAVTalk::setUp()
{
	return;
}//eof

/**
 * Sends a message.
 */
void UAVTalk::sendTestMessage(){
	struct UAVTalkVelocityMessage vMessage;
	vMessage.header.startByte = 0x3C;
	// Not sure if the type is right, see: http://wiki.openpilot.org/display/Doc/UAVTalk
	vMessage.header.messageType = 0x10;
	// length = number of bytes in header and payload without checksum (Header: 10b, payload: 3x4b).
	vMessage.header.length = 22;
	// openpilot wiki says; Unique object instance ID. Only present in UAVObjects that are NOT of type 'single instance'
	// Could either mean that these bytes are not part of the message at all
	// or that these bytes are 0x0.
	vMessage.header.instanceID = 0;
	vMessage.down = 1;
	vMessage.east = 2;
	vMessage.north = 3;
	this->setChecksum(&(vMessage.header.startByte));
	// FIXME Sending two messages corrupts data.
	//xbee->sendData( (uint8_t*)(&message_heartbeat), message_heartbeat.header.numberOfBytes + UAVTalk::protocolOverhead);
//	xbee->sendData( (uint8_t*)(&attitudeMessage), attitudeMessage.header.numberOfBytes + UAVTalk::protocolOverhead);
	return;
}//eof

/**
 * \brief calculates the checksum of a message and writes it to the checksum bytes of the given message structure.
 * The message is passed as a pointer to is first byte. The function identifies the
 * number of bytes in the message by reading the 6. byte.
 */
void UAVTalk::setChecksum(uint8_t* messageStructPointer)
{

	return;
}//eof
