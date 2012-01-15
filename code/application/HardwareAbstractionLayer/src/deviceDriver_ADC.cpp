/**
 *\file deviceDriver_ADC.cpp
 *\brief
 *\author Jan
*/

//Inclusions
#include "../inc/deviceDriver_IMUchr6d.h"

// Static members:
char IMU_CHR6D::syncChars[3] = {115, 110, 112};			// character sequence "snp"
uint8_t IMU_CHR6D::numberOfInstances = 0;
IMU_CHR6D* IMU_CHR6D::imu[] = {0};						// FIXME should not point to memory location 0x0;

/**
 * \brief Constructor, configures the IMU and the necessary peripherals.
 */
IMU_CHR6D::IMU_CHR6D(USART_TypeDef* usart)
{

	IMU_CHR6D::imu[IMU_CHR6D::numberOfInstances] = this;
	this->numberOfInstances++;
	this->serialPort = new SerialPort(usart, 115200);
	this->newPacketWaiting = false;
	// set up packets
	this->packet_setBroadcastMode[0] = this->syncChars[0];
	this->packet_setBroadcastMode[1] = this->syncChars[1];
	this->packet_setBroadcastMode[2] = this->syncChars[2];
	this->packet_setBroadcastMode[3] = 0x84;					// Packet type PT.
	this->packet_setBroadcastMode[4] = 1;						// Number of bytes in the packet.
	this->packet_setBroadcastMode[5] = 100;						// Broadcast frequency; f = ((280/255)*x + 20) Hz (see datasheet).
	this->packet_setBroadcastMode[6] = 0;						// Checksum, first byte.
	this->packet_setBroadcastMode[7] = 0;						// Checksum, second byte.

	this->packet_setSilentMode[0] = this->syncChars[0];
	this->packet_setSilentMode[1] = this->syncChars[1];
	this->packet_setSilentMode[2] = this->syncChars[2];
	this->packet_setSilentMode[3] = 0x83;					// Packet type PT.
	this->packet_setSilentMode[4] = 0;						// 'number of bytes' byte.
	this->packet_setSilentMode[5] = 0;						// Checksum, first byte.
	this->packet_setSilentMode[6] = 0;						// Checksum, second byte.

	this->packet_setActiveChannels[0] = this->syncChars[0];
	this->packet_setActiveChannels[1] = this->syncChars[1];
	this->packet_setActiveChannels[2] = this->syncChars[2];
	this->packet_setActiveChannels[3] = 0x82;					// Packet type PT.
	this->packet_setActiveChannels[4] = 1;						// Number of bytes in the packet.
	this->packet_setActiveChannels[5] = 0xff;				// active channels, bits specify active/not active in this order: pitch,roll,gyro_z,gyro_y,gyro_x,accel_z,accel_y,accel_x
	this->packet_setActiveChannels[6] = 0;						// Checksum, first byte.
	this->packet_setActiveChannels[7] = 0;						// Checksum, second byte.

	this->packet_getData[0] = this->syncChars[0];
	this->packet_getData[1] = this->syncChars[1];
	this->packet_getData[2] = this->syncChars[2];
	this->packet_getData[3] = 0x01;						// Packet type PT.
	this->packet_getData[4] = 0;						// 'number of bytes' byte.
	this->packet_getData[5] = 0;						// Checksum, first byte.
	this->packet_getData[6] = 0;						// Checksum, second byte.

	this->packet_sensorData = {0};
	this->packet_sensorData[0] = this->syncChars[0];
	this->packet_sensorData[1] = this->syncChars[1];
	this->packet_sensorData[2] = this->syncChars[2];
	this->packet_sensorData[3] = 0xB7;					// Packet type PT.
	this->packet_sensorData[4] = 16;					// 'number of bytes' byte.

	//make the chr6d listen for packet requests instead of broadcasting packets on its own.
	this->sendPacket(this->packet_setActiveChannels, 8);
	this->sendPacket(this->packet_setSilentMode, 7);

}//eof

/**
 *\brief Destructor.
 */
IMU_CHR6D::~IMU_CHR6D()
{
	// TODO	Free memory?
}//eof

/**
 * \brief Driver development and testing takes place here.
 */
void IMU_CHR6D::testLoop()
{
	//this->serialPort->sendTestMessage();
	uint8_t buffer[24] = {0};
	this->serialPort->registerToMailbox(&serialPortListener_imu0, this->syncChars, 3);
	while(true){
		TimeBase::waitMicrosec(1000000);
		for(uint8_t i=0; i<8; i++)
		{
			Modules::backPointer->messagePort.add_S16_ToMailbox(this->channelValues[i]);
		}
		Modules::backPointer->messagePort.sendMailbox();
		// Request a sensor data packet.
		this->sendPacket(this->packet_getData, 7);
		// wait until a package has been received

		while(this->newPacketWaiting == false)			// TODO Add timeout functionality to ensure that the program doesn't stall e.g. in case of loss of link.
		{
		}
			// Wait until the packet type and 'number of data' have been received.
			while(this->serialPort->getNumberOfReceivedBytes()<6)
			{

			}
			this->serialPort->getRxData(buffer, 5);
			// Check if it is a sensorData packet (Packet Type = 0xB7).
			if(buffer[3] == 0xB7)
			{
				// Check packet payload size
				uint8_t payloadSize = buffer[4];
				// Wait until the entire packet has been received
				uint8_t packetOverhead = 7;
				while(this->serialPort->getNumberOfReceivedBytes()<(packetOverhead + payloadSize))
				{
				}
					// Get the whole package.
					this->serialPort->getRxData(this->packet_sensorData, (packetOverhead + payloadSize));
					// calculate attitude data
					this->extractInertialValues(this->packet_sensorData, (packetOverhead + payloadSize));

				Devices::backPointer->statusLED.toggle();
			}

			this->newPacketWaiting = false;
			this->serialPort->setMailboxBackToWaitState();

	}
	return;
}//eof

/**
 * \brief Calculates the actual inertial data using the received sensorData packet.
 */
void IMU_CHR6D::extractInertialValues(uint8_t* sensorDataPacket, uint8_t packetSize)
{	// Verify checksum.
	// First get the received checksum byte.
	uint8_t checksum_1 = sensorDataPacket[packetSize-2];
	uint8_t checksum_2 = sensorDataPacket[packetSize-1];
	// Now calculate checksum of the packet:
	this->setChecksum(sensorDataPacket, packetSize);
	// Compare:
	if((checksum_1 == sensorDataPacket[packetSize-2]) && (checksum_2 == sensorDataPacket[packetSize-1]))
	{
		// Temporay buffer for the raw channel values.
		// This byte indicates which sensor channels are transmitted.
		uint8_t activeChannels = sensorDataPacket[5];
		// Used to run through the channel value bytes.
		uint8_t channelIndex = 6;				// Start with the first byte of the first active channel;
		for(uint8_t i=0; i<8; i++)
		{
			// If the channel is active, read two bytes of the sensorData packet.
			if((activeChannels & 1<<i) > 0)
			{
				uint16_t temp = ( (uint16_t)sensorDataPacket[channelIndex] )<<8;
				this->channelValues[i] = (int16_t)(temp | sensorDataPacket[channelIndex + 1]);
			}
			//otherwise set the channel value to 0
			else
			{
				this->channelValues[i] = 0;
			}
			channelIndex += 2;
		}

		// -> values to scale.
		//attitude [degree]
		// Pitch
		this->channelValues[0] /= 91;
		// Roll
		this->channelValues[1] /= 91;
		// Angular rates [degree/s]
		// Gyro_z
		this->channelValues[2] /= 50;
		// Gyro_y
		this->channelValues[3] /= 50;
		// Gyro_x
		this->channelValues[4] /= 50;
		// Acceleration [m/s²]
		// Accel_z
		this->channelValues[5] /= 6;
		// Accel_y
		this->channelValues[6] /= 6;
		// Accel_x
		this->channelValues[7] /= 6;
	}
	else
	{
		// TODO Throw Exception, error message.
	}

}//eof

/**
 * \brief The message checksum is calculated based on the given pointer to an array containing the
 * bytes of a packet and the given packet size (number of bytes of the packet including synchronization chars and checksum).
 */
void IMU_CHR6D::setChecksum(uint8_t* packet, uint8_t packetSize)
{
	uint16_t sum = 0;
	// Sum up all bytes except of the two checksum bytes.
	for(uint8_t i=0; i< packetSize-2; i++){
		sum += packet[i];
	}
	packet[packetSize-1] = (uint8_t)(sum & 0xFF);		// set the second byte of the checksum to the lowest 8 bits of the sum
	packet[packetSize-2] = (uint8_t)(sum>>8);			// set the first byte of the checksum to the highest 8 bits of the sum

	return;
}//eof

/**
 * Sends a given packet by the SerialPort to the imu.
 */
void IMU_CHR6D::sendPacket(uint8_t* packet, uint8_t packetSize)
{
	this->setChecksum(packet, packetSize);
	for(uint8_t i=0; i<packetSize; i++)
	{
		this->serialPort->add_U8_ToMailbox(packet[i]);
	}
	this->serialPort->sendMailbox();

	return;
}//eof

/**
 * \brief This function is called by the SerialPort once a fitting byte sequence has been received.
 */
void serialPortListener_imu0()
{
	IMU_CHR6D::imu[0]->newPacketWaiting = true;
	return;
}//eof
