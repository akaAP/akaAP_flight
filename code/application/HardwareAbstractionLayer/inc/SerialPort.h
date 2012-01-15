 /*************************************
 * \file serialPort.h
 * \brief 	This file provides functions to send and receive data by serial ports (USART).
 *	 		A serialPort is kind of a USART port with extended capabilities.
 * 			Until now the parameters of a SerialPort (e.g. baudrate, data format etc.) are
 * 			still hard-coded in the constructor.
 *
 *		-- Data Transmission --
 * 		How to use it:
 * 		To send data, proceed as following:
 * 		1.) add your data to the TX mailbox by one of the 'add_xx_toMailbox(yourData)' functions
 * 	    2.) Once you're done, start message transmission by calling the function 'sendMailbox()'
 * 		Note: given the case the number of data you write to a mailbox exceeds its maximum capacity, the mailbox transmission
 * 		starts automatically and the following data are written to the next empty mailbox, which has still to be transmitted by calling
 *		'sendMailbox()'.
 *		Example:
 *		Let's assume a mailboxes max capacity amounts to 100 byte (you may find out by calling the 'serialPort_getTxMailboxCapacity()' function)
 *		and you are writing 110 bytes to it before calling the send-function. In this case once you wrote the 100th
 *		byte to the mailbox, the transmission of the mailbox is started internally. The next byte you pass to a 'addToMailbox' function
 *		is written to a new mailbox, since the other one is currently being transmitted. Once you're done with the 110
 *		bytes, you would call the 'sendMailbox' function to initiate the transmission of the second mailbox.
 *
 * 		-- Data Reception --
 * 		How to use it:
 * 		The serialPort assumes that each data packet begins with a certain sequence of characters. However, it is
 * 		also possible to wait for any character (see documentation of the serialPort_registerToMailbox(...) function).
 * 		To be able to receive data, proceed as following:
 * 		1.) call the serialPort_registerToMailbox(...) function. Done that, the serialPort looks for the
 * 			character sequence you passed to the function and calls the listener function once the sequence
 * 			occurs ('waitForMessage state'). If you want the listener funcion be called once any byte is received, that's
			also possible (see serialPort_registerToMailbox(...) function documentation)
 * 		3.) Note: inside the listener function shouldn't be too much code since it is called out of an interrupt service
 * 			routine, potentially blocking other interrupts. It is recommended just to set a flag indicating that there
 *			are new data.
 *		4.) To read the received data, one may use the getNumberOfReceivedData(...) function, since the call to the
 *			listener function only indicates that the start sequence has been received; the reception of the full message
 *			may still be going on.
 *		5.) Finally, to get the received data, use the serialPort_getRxData(...) function. It copies as many bytes of the last
 *			received message as you want to a given array. Note: this means that in order to avoid loss of data, data
 *			should be read before setting the mailbox back into 'waitForMessage' state (either by just setting
 * 			it back into 'waitForMessage' state or by setting it up anew, possibly setting a new start sequence
 * 			and/or a new listener). Also be aware of the fact that incoming data are continuously transferred to the
 * 			mailbox ring buffer by DMA, so if you wait too long and there is a steady stream of data the message is overwritten.
 * 			It should be easy to avoid that by reading out the relevant data just after the listener has been called and
 * 			the message has been received completely.
 *
 * 		Note: for data rates exceeding 1MBit/s, the time may become to short between two incoming bytes to compare them
 * 		to the synchronization chars. Hasn't been tested yet.
 *
 * 		Tests:
 * 		- 25Feb2011: Reception successfully tested with 0, 3 and 10 syncChars, 2400, 115200 and 921600 baud.
 *   	- 25Feb2011: Transmission successfully tested with 2400, 115200 and 921600 baud.
 *
 *   	TODO data are corrupted if the user writes to a mailbox while it's still being transmitted (may happen if the data transmission by USART is much slower than the data been written to the mailboxes).
 *
 * resources:
 * - 1 USART peripheral per serialPort
 * - 2 DMA channels per serialPort
 *
 * \author: jan bolting
 *
 **************************************/

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../inc/serviceFunctions.h"
#include "../inc/InterruptManager.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_LED_CPP.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"
#include "TxMailbox.h"


class SerialPort;		//Declaration just here since pointers to SerialPorts are used in the structures

struct RxMailbox{
	static const uint8_t rxMailboxMaxNumberOfSyncChars = 10;
	static const uint16_t mailboxLength = 1024;
	volatile char data[RxMailbox::mailboxLength];					// Volatile, since it's changed by DMA.
	volatile uint16_t indexStartOfLastMessage;						// Indicates where the message received at last begins (array index); volatile, since it's changed in ISRs.
	volatile uint8_t waitingForMessage;								// Indicates whether this mailbox waits for a message start sequence; volatile, since it's changed in ISRs.
	char syncChars[RxMailbox::rxMailboxMaxNumberOfSyncChars];		// This array is used to store the chars indicating the beginning of.
																	// The message the serialPort is waiting for.
	uint8_t numberOfSyncChars; 										// Indicates how many chars in the syncChars array are supposed to be used.
	void (*listener)();												// This function is called once the mailbox has received the beginning of the message it is waiting for.
};

class SerialPort{
public:

	/**
	 * \brief Constructor.
	 */
	SerialPort(USART_TypeDef* usart, uint32_t baudrate);

	/**
	 * \brief Destructor.
	 */

	~SerialPort();

	// data transmission methods;

	/**
	 * \brief returns the number of bytes that fits into a transmission mailbox
	 */
	uint16_t getMaxTxMailboxCapacity();

	/**
	 * \brief Transmitts the mailbox the user has written to at last by a serial port.
	 * \param struct serialPort* pointer to the serialPort you want to use.
	 */
	void sendMailbox();

	/**
	 * \brief Transmits a test String.
	 */
	void sendTestMessage();

	/**
	 * \brief Writes a String to the SerialPort's mailbox.
	 */
	void add_String_ToMailbox(char* data, uint16_t numberOfChars);
	void add_U8_ToMailbox(uint8_t data);
	void add_S8_ToMailbox(int8_t data);
	void add_U16_ToMailbox(uint16_t u16tosend);
	void add_S16_ToMailbox(int16_t s16tosend);
	void add_u32_ToMailbox(uint32_t u32tosend);

	//data reception methods

	/**
	 * \brief Use this function to register as a listener to a serialPort's Rx mailbox. This mailbox waits for the sequence of chars
	 * given as a parameter.This chars indicate the beginning of a message. Once the mailbox has
	 * received the beginning of the message, the given function 'listener' is called passing
	 * a pointer to the serialPort.
	 *
	 * \parameter *newListener 					- function pointer to the function which is supposed to be called
	 * \parameter char* syncChars   			- first bytes of the message
	 * \parameter unint8_t numberOfSynChars 	- the length of the syncChars array; has to be <= serialPort_TX_MAILBOX_MAXNOFSYNCCHARS (see serialIO.h)
	 * 										  	   If it's 0 the mailbox considers each received char as the beginning of a message
	 */
	void registerToMailbox(void(*newListener)(), char* syncChars, uint8_t numberOfSyncChars);

	/**
	 * \brief Use this function to make the given serialPort's mailbox wait for a message.
	 *
	 */
	void setMailboxBackToWaitState();

	/**
	 * \brief Copies a given number of bytes from the last received message to the given array.
	 *
	 * \parameter uint8_t*				 - the function interpretes this as a pointer to an array where it copies the message bytes
	 * \parameter const uint16_t 	 - indicates how many bytes the function is supposed to copy to the target array
	 */
	void getRxData(uint8_t* target, const uint16_t nofBytes);

	/**
	 * \brief This function returns the number of bytes of the last message that already have been received.
	 *
	 * \return - uint8_t number of received bytes
	*/
	uint16_t getNumberOfReceivedBytes();

	static const uint8_t numberOfTxMailboxes = 5;
	TxMailbox* txMailbox[SerialPort::numberOfTxMailboxes];						// FIXME hack
														//mailbox buffers, used for transmission
	volatile uint8_t indexOfTxMailboxSentLast;								//array index of the txMailbox sent last

	void usart_IRQHandler();
	void dma_Channelx_TCInterrupt_Handler();
	static SerialPort* serialPortUsingUSART1;
	static SerialPort* serialPortUsingUSART2;
	static SerialPort* serialPortUsingUSART3;
	static SerialPort* serialPortUsingUSART4;
	static SerialPort* serialPortUsingUSART5;
	static SerialPort* serialPortUsingUSART6;

private:
	//fields

	struct RxMailbox rxMailbox;										//mailbox buffer, used for reception
	USART_TypeDef* hardware;										//pointer to the peripheral the port actually uses; e.g. USART1
	DMA_Channel_TypeDef* Tx_DMA_Channel;							//DMA channel used by the serialPort's USART to transmit
	DMA_Channel_TypeDef* Rx_DMA_Channel;							//DMA channel used by the serialPort's USART to receive
	volatile uint8_t indexOfTxMailboxToWriteTo;								//index of the mailbox written to at last, supposed to be sent;
	GPIO_TypeDef* TXPin_GPIOPort;									//which GPIO port is the USART RX line connected to?
	uint16_t TXPin;													//and to which pin?
	GPIO_TypeDef* RXPin_GPIOPort;									//which GPIO port is the USART RX line connected to?
	uint16_t RXPin;													//and to which pin?
	//some Interrupts
	uint8_t DMA_TransmissionCompleteInterrupt_NVIC_ID;
	uint8_t USART_global_interrupt;
	volatile uint8_t numberOfSyncCharsHavingPassedTheTest; 				//indicates how many received chars have passed the synchronization test.
																		//E.g. if "xxsabc" has been received and the syncChars are "abcd" this variable is 3.
																		//if the received chars continue as "xxsabcp" the variable should go back to 0
	//methods
	void setUp(USART_InitTypeDef usartInitStruct);
	//data transmission
	void addToMailbox(char data);
	static void setUpDMAForNewTransmission(SerialPort* sPort, struct TxMailbox* mBox);
};


extern "C" void USART1_IRQHandler_sPort();
extern "C" void USART2_IRQHandler_sPort();
extern "C" void USART3_IRQHandler_sPort();
extern "C" void DMA1_Channel2_IRQHandler_sPort();
extern "C" void DMA1_Channel4_IRQHandler_sPort();
extern "C" void DMA1_Channel7_IRQHandler_sPort();

#endif /* SERIALPORT_H_ */
