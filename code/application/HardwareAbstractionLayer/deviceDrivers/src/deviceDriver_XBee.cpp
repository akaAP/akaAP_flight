/**
 *\file deviceDriver_XBEE.c
 *\brief Please give information that could be useful for understanding the code here.
 *\author Jan
*/

//Inclusions
#include "../inc/deviceDriver_XBEE.h"

// Static fields:
uint8_t XBee::syncBytes[3] = {0};
XBee* XBee::instances[5] = {0};			// TODO Should not point to memory address 0x0;
uint8_t XBee::numberOfInstances = 0;
/**
 *\brief Constructor.
 */
XBee::XBee(USART_TypeDef* usart)
{
	this->serialPort = new SerialPort(usart, 111111);		// According to [http://forums.digi.com/support/forum/printthread_thread,7255], the XBee modems use 111111 baud when
															// set to 115200 baud. Turned out to significantly reduce transmission errors.

	// TODO: What is the purpose of this array of instances?
	XBee::instances[XBee::numberOfInstances] = this;
	if(XBee::numberOfInstances < 5){
		XBee::numberOfInstances++;
	}
	this->setUp();
}//eof

/**
 * \brief Destructor.
 */
XBee::~XBee()
{
	// TODO Free memory?
}//eof

/**
 * \brief Initialises the XBee
 */
void XBee::setUp()
{
	return;
}//eof

/**
 * Sends an array of bytes.
 */
void XBee::sendData(uint8_t* data, uint16_t numberOfBytes)
{
	for(uint16_t i=0; i<numberOfBytes; i++)
	{
		this->serialPort->add_U8_ToMailbox(data[i]);
	}
	this->serialPort->sendMailbox();
}//eof



/**
 * \brief Listener function for the SerialPort.
 */
void XBee::serialListener_1()
{
	return;
}//eof
