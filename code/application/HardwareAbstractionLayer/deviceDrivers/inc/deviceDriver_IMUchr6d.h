/*
 * \file deviceDriver_IMUchr6d.h
 *\brief This Device driver provides functionality to communicate with the CHR-6D
 * IMU by CH Robotics.
 * * \author Jan
 */

#ifndef DEVICEDRIVER_IMUCHR6D_H_
#define DEVICEDRIVER_IMUCHR6D_H_

//Inclusions
#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../inc/SerialPort.h"
#include "../../inc/Modules.h"
#include "../../inc/timebase.h"


//Structure declaration
class IMU_CHR6D{
public:
	IMU_CHR6D(USART_TypeDef* usart);
	~IMU_CHR6D();
	void testLoop();						// Performs some tests, mainly for development purposes. TODO Make private once the driver works properly.
	static IMU_CHR6D* imu[5];				// Pointer to the first 5 instances of this class. Actually there are not
											// expected to be more than 1-3 IMUs, therefore a maximum of 5 seems to be sufficient.
	SerialPort* serialPort;					// The SerialPort used by this driver.
	volatile bool newPacketWaiting;			// indicates that there has been received the beginning of a new packet by the SerialPort. Has to be
											// volatile since it's changed by functions invoked by a USART interrupt handler;
private:
	void setUp();
	void setChecksum(uint8_t* packet, uint8_t packetSize);	// Calculates the packet checksum and sets the checksum bytes.
	void sendPacket(uint8_t* packet, uint8_t packetSize);	// Sends a data packet to the chr6d
	void extractInertialValues(uint8_t* sensorPacket, uint8_t packetSize);	// Calculates the actual inertial data using the received sensorData packet
	int16_t channelValues[8];								// pitch,roll,gyro_z, gyro_y, gyro_x, accel_z, accel_y, accel_z
	// packets to transmit
	uint8_t packet_setSilentMode[7];
	uint8_t packet_setBroadcastMode[8];
	uint8_t packet_setActiveChannels[8];
	uint8_t packet_getData[7];
	// packets to be received
	uint8_t packet_sensorData[24];
	static char syncChars[3];				// Each packet starts with the character sequence "snp", decimal: 115,110,112.
	static uint8_t numberOfInstances;		// Number indicates how many Instances of this class
											// have been created yet.

};

void serialPortListener_imu0();


#endif /* DEVICEDRIVER_IMUCHR6D_H_ */
