/*
 * \file GroundLinkMessages.h
 * \brief Implementation of the Openpilot UAVTalk protocol.
 * \author Jan
 */

#ifndef UAVTALKMESSAGES_H_
#define UAVTALKMESSAGES_H_

//Inclusions

// Necessary to enable sending structures reading them byte by byte. Otherwise, the compiler adds
// bytes to achieve proper memory alignment.
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

//Message declarations.
struct UAVTalkMessageHeader{
	uint8_t startByte;
	uint8_t messageType;
	uint16_t length;
	uint32_t objectID;
	uint16_t instanceID;
};

struct UAVTalkMessageEnd{
	uint8_t checksum;
};

struct UAVTalkVelocityMessage{
	struct UAVTalkMessageHeader header;
	int32_t north;
	int32_t east;
	int32_t down;
	struct UAVTalkMessageEnd end;
};

#pragma pack(pop)   /* restore original alignment from stack */


#endif /* UAVTALKMESSAGES_H_ */
