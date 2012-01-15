 /*************************************
 * \file deviceDriver_LEA4T.c
 * \brief This driver provides functions to get navigation data out of the
 * ublox LEA4-T GPS receiver.
 * \author: jan bolting
 *
 **************************************/

 /*Includes*********************************/
#include "../inc/deviceDriver_LEA4T.h"
#include "../../inc/serialPort.h"

// defines which serialPort the driver uses to communicate (for serialPort code please have a look at serialIO.h/.c)
#define SERIALPORT serialPort1

//structures for received messages
static struct lea4t_message bufferMessage_nav_posllh;			//NAV_POSLLH message structure
static uint8_t payload_nav_posllh[1];							//NAV_POSLLH payload array

//structure used to poll messages
static struct lea4t_message pollMessage;
 /*Functions********************************/

void LEA4T_Init(){
	//connect the arrays for the payload data to the message structures
	bufferMessage_nav_posllh.payloadPointer = &payload_nav_posllh[0];
	return;
}//eof


/**
 * \brief requests the GPS chip to send a message.
 * \param TODO documentation
 */
void poll_message(char messageClassID, char messageID){
	pollMessage.classID = messageClassID;
	pollMessage.messageID = messageID;
	pollMessage.length = 0;										//in order to poll a message it's just required to send an empty message of the same type
	calculateChecksum(&pollMessage);
	sendMessage(&pollMessage);
	return;
}//eof

void sendMessage(struct lea4t_message* messageStructPointer){
	sendByte(&SERIALPORT, FRAME_SYNCBYTE_1);
	sendByte(&SERIALPORT, FRAME_SYNCBYTE_2);
	sendByte(&SERIALPORT, messageStructPointer->classID);
	sendByte(&SERIALPORT, messageStructPointer->messageID);
	sendByte(&SERIALPORT, service_reverseBitOrder((uint8_t)messageStructPointer->length));			//send lower byte LSB first
	sendByte(&SERIALPORT, service_reverseBitOrder((uint8_t)((messageStructPointer->length)>>8)));	//send higher byte LSB first
	sendByte(&SERIALPORT, messageStructPointer->checksum_A);
	sendByte(&SERIALPORT, messageStructPointer->checksum_B);
}//eof


/**
 * \brief calculates the checksum of a message as defined in the ublox Antaris 4 protocol specification
 * and writes it to the fields of the given message structure.
 */
void calculateChecksum(struct lea4t_message* messageStructPointer)
{
	uint8_t CK_A = 0, CK_B = 0;
	//calculate over class ID, message ID and length
	CK_A += messageStructPointer->classID;
	CK_B += CK_A;

	CK_A += messageStructPointer->messageID;
	CK_B += CK_A;

	CK_A += messageStructPointer->length;
	CK_B += CK_A;

	//calculate over the payload
	for(uint8_t i=0; i<messageStructPointer->length; i++)
	{
		CK_A += (messageStructPointer->payloadPointer)[i];
		CK_B += CK_A;
	}

	messageStructPointer->checksum_A = CK_A;
	messageStructPointer->checksum_B = CK_B;
	//write the two bytes into one 16-bit variable

	return;
}//eof


