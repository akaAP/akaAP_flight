/*
 * \file GroundLinkMessages.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef GROUNDLINKMESSAGES_H_
#define GROUNDLINKMESSAGES_H_

//Inclusions

// Necessary to enable sending structures reading them byte by byte. Otherwise, the compiler adds
// bytes to achieve proper memory alignment.
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

//Message declarations.
struct MessageHeader{
	// FIXME why not make the start bytes constant and statically defined?
	// TODO According to the pixhawk wiki, more than one startbyte is unnecessary - understand why.
	uint8_t start1;
	uint8_t start2;
	uint8_t start3;
	uint16_t messageID;
	uint8_t numberOfBytes;
};

struct MessageEnd{
	uint8_t checksum1;
	uint8_t checksum2;
};

struct HeartBeatMessage{
	struct MessageHeader header;
	struct MessageEnd end;
};

struct UavHealthMessage{
	struct MessageHeader header;
	static const uint32_t healthFlags = 77;
	struct MessageEnd end;
};

struct RcChannelMessage{
	struct MessageHeader header;
	int16_t channels[12];
	struct MessageEnd end;
};

struct SingleValueMessage{
	struct MessageHeader header;
	int32_t value;
	struct MessageEnd end;
};

struct AttitudeMessage{
	struct MessageHeader header;
	int16_t phi;				// roll
	int16_t theta;				// pitch
	int16_t psi;				// yaw
	int16_t phi_dot;			// droll/dt
	int16_t theta_dot;			// dpitch/dt
	int16_t psi_dot;			// dyaw/dt
	struct MessageEnd end;
};

struct RawInertialMessage{
	struct MessageHeader header;
	int16_t gyro[3];
	int16_t acc[3];
	struct MessageEnd end;
};

#pragma pack(pop)   /* restore original alignment from stack */


#endif /* GROUNDLINKMESSAGES_H_ */
