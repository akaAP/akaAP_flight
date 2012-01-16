 /*************************************
 * \file GroundLink.cpp
 * \brief
 * \author: jan bolting
 *
 **************************************/

#include "../inc/GroundLink.h"

/**
 * \brief Constructor.
 * \param the USART peripheral the GroundLink is supposed to use.
 */
GroundLink::GroundLink(USART_TypeDef* usartToUse){
	this->xbee = new XBee(usartToUse);
	return;
}//eof

/**
 * Destructor.
 */
GroundLink::~GroundLink(){
	// FIXME free memory
}//eof

void GroundLink::sendHeartbeat(){
	struct HeartBeatMessage message_heartbeat;
	message_heartbeat.header.start1 		= 1;
	message_heartbeat.header.start2 		= 2;
	message_heartbeat.header.start3 		= 3;
	message_heartbeat.header.messageID		= 1;
	message_heartbeat.header.numberOfBytes	= 0;
	this->setChecksum(&(message_heartbeat.header.start1));

	xbee->sendData( (uint8_t*)(&message_heartbeat), message_heartbeat.header.numberOfBytes + GroundLink::protocolOverhead);
	return;
}//eof

/**
 * \brief Sends a signed 32 bit value to the ground station.
 * \param int32_t - the value that is supposed to be sent.
 */
void GroundLink::sendValue(int32_t valueToSend){
	struct SingleValueMessage  valueMessage;
	 valueMessage.header.start1 		= 1;
	 valueMessage.header.start2 		= 2;
	 valueMessage.header.start3 		= 3;
	 valueMessage.header.messageID 		= 3;
	 valueMessage.header.numberOfBytes	= 4;
	 valueMessage.value = valueToSend;
	this->setChecksum(&( valueMessage.header.start1));
	xbee->sendData( (uint8_t*)(&valueMessage),  valueMessage.header.numberOfBytes + GroundLink::protocolOverhead);
	return;
}//eof

void GroundLink::sendRawInertial(){
	struct RawInertialMessage message;
	message.header.start1 					= 1;
	message.header.start2 					= 2;
	message.header.start3 					= 3;
	message.header.messageID				= 5;
	message.header.numberOfBytes	= 12;
	// payload
	message.acc[0]							= 1;
	message.acc[1]							= 2;
	message.acc[2]							= 3;
	message.gyro[0]							= 11;
	message.gyro[1]							= 12;
	message.gyro[2]							= 13;
	this->setChecksum( (uint8_t*)(&message));

	// FIXME Sending two messages directly one after another corrupts data.
//	xbee->sendData( (uint8_t*)(&message_heartbeat), message_heartbeat.header.numberOfBytes + GroundLink::protocolOverhead);
	xbee->sendData( (uint8_t*)(&message), message.header.numberOfBytes + GroundLink::protocolOverhead);
	return;
}//eof


/**
 * \brief calculates the checksum of a message and writes it to the checksum bytes of the given message structure.
 * The message is passed as a pointer to is first byte. The function identifies the
 * number of bytes in the message by reading the 6. byte.
 */
void GroundLink::setChecksum(uint8_t* messageStructPointer)
{
	// get the number of payload bytes in the message
	uint8_t payloadSize = messageStructPointer[5];
	uint8_t CK_A = 0;
	uint8_t CK_B = 0;
	//calculate over syncChars (3 bytes), MessageID (2 bytes), numberOfBytes (1 byte) and payload
	for(uint8_t i=0; i<(payloadSize + 6); i++)
	{
		CK_A += messageStructPointer[i];
		CK_B += CK_A;
	}
	//set checksum bytes
	messageStructPointer[6+payloadSize] = CK_A;
	messageStructPointer[7+payloadSize] = CK_B;
	return;
}//eof
