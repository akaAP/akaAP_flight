/*
 * deviceDriver_LEA4T.h
 *
 * \file deviceDriver_LEA4T.h
 * \brief This driver provides functions to get data out of the
 * ublox LEA4-T GPS receiver.
 *
 * Notes:
 * Messages are polled by sending the desired message without a payload.
 * Messages are preceded by two synchronization characters: 0xB5 0x62
 * \author: jan bolting
 */
#ifndef DEVICEDRIVER_LEA4T_H_
#define DEVICEDRIVER_LEA4T_H_

//message definitions for the proprietary ublox Antaris 4 GPS protocol; In case of an upgrade
//e.g. to Antaris 6 just copy the definition block, make your modifications and change
//the line below to 'UBLOX_PROTOCOL_IS_ANT6'
#define UBLOX_PROTOCOL_IS_ANTARIS_4
#ifdef UBLOX_PROTOCOL_IS_ANTARIS_4
	#define FRAME_SYNCBYTE_1 0xB5
	#define FRAME_SYNCBYTE_2 0x62
	//ublox Antaris 4 protocol message class IDs
	#define UBX_CLASSID_NAV 0x01 		// Navigation Results: Position, Speed, Time, Acc, Heading, DOP, SVs used
	#define UBX_CLASSID_RXM 0x02 		// Receiver Manager Messages: Pseudo Ranges, avg C/N0, Channel Status
	#define UBX_CLASSID_INF 0x04 		// Informative Messages: Printf-Style Messages, with Ids such as Error, Warning, Notice
	#define UBX_CLASSID_ACK 0x05 		// Ack/Nack Messages as replies to CFG Input Messages
	#define UBX_CLASSID_CFG 0x06 		// Configuration Input Messages: Set Dynamic Model, Set DOP Mask
	#define UBX_CLASSID_UPD 0x09 		// Firmware Update Messages
	#define UBX_CLASSID_MON 0x0A 		// Monitor: Stack Usage, Comunication Status, CPU Load, IPC Status, Task Status
	#define UBX_CLASSID_AID 0x0B 		// Navigation Aiding: Ephemeris, Almanac feeds
	#define UBX_CLASSID_TIM 0x0D 		// Timing: Timepulse Output, Timemark Results

	//some necessary ublox Antaris 4 protocol message IDs
	#define MESSAGEID_NAV_POSLLLH 0x02	//message ID of message POSLLH in class NAV
#endif

/* inclusions *******/

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"

/**
 * \brief defines a message of the ublox Antaris 4 protocol.
 */

struct lea4t_message{
	uint8_t classID;					/** \brief the message class, e.g. CLASSID_NAV, CLASSID_RXM */
	uint8_t messageID;					/** \brief the message ID, e.g. MESSAGEID_NAV_POSLLLH */
	uint16_t length;					/** \brief the payload length in bytes*/
	uint8_t* payloadPointer;			/** \brief pointer to an array of payload bytes */
	uint8_t checksum_A;					/** \brief the message checksum byte A*/
	uint8_t checksum_B;					/** \brief the message checksum byte B*/
};

/** function prototypes **/
void calculateChecksum(struct lea4t_message* messageStructPointer);
void sendMessage(struct lea4t_message* messageStructPointer);


#endif /* DEVICEDRIVER_LEA4T_H_ */
