 /*************************************
 * \file serialPort.cpp
 * \brief 	This file provides functions to send and receive data by serial ports (physical device: USART).
 *	 		A serialPort is kind of a USART port with extended capabilities.
 *			The parameters of the instances of serialPort (e.g. baudrate, data format etc.)are still
 *			hard-coded in the constructor.
 *
 *		-- Data Transmission --
 *		--
 * 		How it works:
 *		From the user's point of view
 *		a serialPort has a mailbox accessed by the various 'add_xx_toMailbox(yourData)' functions.
 *		One may just write data to the mailbox and than initiate the transmission of the mailbox content.
 *		After starting the transmission, the mailbox can be loaded with new data immediately since data transfer
 *		is managed by shadow mailboxes in the background. The mailbox content is transferred by DMA from the mailboxes
 *		to the USART.
 *
 * 		-- Data Reception --
  *
 * 		How it works:
 * 		Data reception internally works as following: each serialPort has an input buffer, the rxMailbox. Each rxMailbox has
 * 		a short array of synchronization chars. These chars are supposed to indicate the beginning of a message.
 * 		Once the user has activated the mailbox (by the registerToMailbox(...) function), passing the synchronization chars and
 * 		a pointer to a listener function, the mailbox waits for this exact sequence of chars to be received by its USART.
 * 		The comparison between the received chars and the sequence is done in an interrupt service routine which
 * 		is called whenever a new char has been received. Once the sequence has been found, the USART interrupt is disabled (so the
 * 		mailbox stops looking for the start sequence) and the rxMailboxes listener function is called.
 * 		All the time, a DMA channel is running in circular mode, continuously
 * 		transferring data from the USARTs data register to the rxMailbox. By setting the mailbox  back into 'waitForMessage' state,
 * 		the USART interrupt is re-enabled and the mailbox starts looks for the start sequence again.
 *
 * 		Tests:
 * 		- 25Feb2011: Reception successfully tested with 0, 3 and 10 syncChars, 2400, 115200 and 921600 baud.
 *   	- 25Feb2011: Transmission successfully tested with 2400, 115200 and 921600 baud.
 *
 *   	TODO data are corrupted if the user writes to a mailbox while it's still being transmitted (may happen if the data transmission by USART is much slower than the data are written to the mailboxes).
 *		FIXME: echoing chars sends back an unpredictable number of chars
 *		FIXME: doesn't work for USART2, USART4 and UART5
 * \author: jan bolting
 *
 **************************************/

#include "../inc/SerialPort.h"

// Initialize static members.
SerialPort* SerialPort::serialPortUsingUSART1 = 0;			// FIXME: Pointers shoudn't be initialized to zero
SerialPort* SerialPort::serialPortUsingUSART2 = 0;			// FIXME: Pointer shoudn't be initialized to zero
SerialPort* SerialPort::serialPortUsingUSART3 = 0;			// FIXME: Pointer shoudn't be initialized to zero
// FIXME Integrate USART4 - USART6
SerialPort* SerialPort::serialPortUsingUSART4 = 0;			// FIXME: Pointer shoudn't be initialized to zero
SerialPort* SerialPort::serialPortUsingUSART5 = 0;			// FIXME: Pointer shoudn't be initialized to zero
SerialPort* SerialPort::serialPortUsingUSART6 = 0;			// FIXME: Pointer shoudn't be initialized to zero

//SerialPort::dma_Channelx_TCInterrupt_Handler(SerialPort* sPort);
//***************************************************************************************************************
//*** public functions ******************************************************************************************
//***************************************************************************************************************

/**
 * \brief Constructor. Initializes a serial I/O port.
 * \par USART_TypeDef* - pointer to the actual hardware USART peripheral (USART1, USART2 etc) the SerialPort is supposed
 * to use.
 */
SerialPort::SerialPort(USART_TypeDef* usartToUse, uint32_t baudrate){

	if(usartToUse == USART1){
		SerialPort::serialPortUsingUSART1 = this;
		this->hardware = usartToUse;							//uses #usartToUse as physical device to send and receive data
		this->USART_global_interrupt = USART1_IRQn;
		this->Tx_DMA_Channel = DMA1_Channel4;				//triggered by USARTy Tx event
		this->DMA_TransmissionCompleteInterrupt_NVIC_ID = DMA1_Channel4_IRQn;
		this->Rx_DMA_Channel = DMA1_Channel5;				//triggered by USARTy Rx event
		this->TXPin_GPIOPort = GPIOA;
		this->TXPin = GPIO_Pin_9;
		this->RXPin_GPIOPort = GPIOA;
		this->RXPin = GPIO_Pin_10;
		InterruptManager::registerInterruptHandler(&USART1_IRQHandler_sPort, InterruptManager::USART1_Handler);
		InterruptManager::registerInterruptHandler(&DMA1_Channel4_IRQHandler_sPort, InterruptManager::DMA1_Channel4_Handler);
	}
	else if(usartToUse == USART2){
		SerialPort::serialPortUsingUSART2 = this;
		this->hardware = USART2;
		this->USART_global_interrupt = USART2_IRQn;
		this->Tx_DMA_Channel = DMA1_Channel7;				//triggered by USARTy Tx event
		this->DMA_TransmissionCompleteInterrupt_NVIC_ID = DMA1_Channel7_IRQn;				// FIXME not tested yet
		this->Rx_DMA_Channel = DMA1_Channel6;				//triggered by USARTy Rx event
		this->TXPin_GPIOPort = GPIOA;
		this->TXPin = GPIO_Pin_2;
		this->RXPin_GPIOPort = GPIOA;
		this->RXPin = GPIO_Pin_3;
		InterruptManager::registerInterruptHandler(&USART2_IRQHandler_sPort, InterruptManager::USART2_Handler);
		InterruptManager::registerInterruptHandler(&DMA1_Channel7_IRQHandler_sPort, InterruptManager::DMA1_Channel7_Handler);
	}
	else if(usartToUse == USART3){
		SerialPort::serialPortUsingUSART3 = this;
		this->hardware = USART3;
		this->USART_global_interrupt = USART3_IRQn;
		this->Tx_DMA_Channel = DMA1_Channel2;				//triggered by USARTy Tx event
		this->DMA_TransmissionCompleteInterrupt_NVIC_ID = DMA1_Channel2_IRQn;
		this->Rx_DMA_Channel = DMA1_Channel3;				//triggered by USARTy Rx event
		this->TXPin_GPIOPort = GPIOB;
		this->TXPin = GPIO_Pin_10;
		this->RXPin_GPIOPort = GPIOB;
		this->RXPin = GPIO_Pin_11;
		InterruptManager::registerInterruptHandler(&USART3_IRQHandler_sPort, InterruptManager::USART3_Handler);
		InterruptManager::registerInterruptHandler(&DMA1_Channel2_IRQHandler_sPort, InterruptManager::DMA1_Channel2_Handler);
	}

	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = baudrate;										//baudrate = 115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							//use 8-Bit words
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								//use 1 stopbit
	USART_InitStructure.USART_Parity = USART_Parity_No;									//don't use parity
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//don't use hardware flow control
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//use bidirectional mode

	this->setUp(USART_InitStructure);

	return;
}//eof

/**
 * Destructor.
 */
SerialPort::~SerialPort(){
	// FIXME free memory
}//eof

void SerialPort::setUp(USART_InitTypeDef usartInitStruct){

		//***********************************************************************
		//set up GPIO pins
		//***********************************************************************
		Service::enablePeripheralClock( (uint32_t)this->RXPin_GPIOPort );
		Service::enablePeripheralClock( (uint32_t)this->TXPin_GPIOPort );

		GPIO_InitTypeDef GPIO_InitStructure;

		  /* Configure USART TX pin as alternate function push-pull */
		  GPIO_InitStructure.GPIO_Pin = this->TXPin;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		  GPIO_Init(this->TXPin_GPIOPort, &GPIO_InitStructure);

		  /* Configure USART RX pin as input floating */
		  GPIO_InitStructure.GPIO_Pin = this->RXPin;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		  GPIO_Init(this->RXPin_GPIOPort, &GPIO_InitStructure);

		  //***********************************************************************
		  //set up USART
		  //***********************************************************************

		  Service::enablePeripheralClock((uint32_t)this->hardware);

	USART_DeInit(this->hardware);
	USART_Init(this->hardware, &usartInitStruct);
	this->hardware->CR3 |= BIT7;							//enable DMA event generation	TODO check if necessary since it's done by the USART_Init function too

	USART_DMACmd(this->hardware, USART_DMAReq_Tx, ENABLE);						//enable the generation of Tx DMA events
	USART_DMACmd(this->hardware, USART_DMAReq_Rx, ENABLE);						//enable the generation of Rx DMA events

	USART_ITConfig(this->hardware, USART_IT_RXNE, ENABLE);						//enable USART's 'Rx register not empty' interrupt
	USART_Cmd(this->hardware, ENABLE);

	for(uint16_t i=0; i<RxMailbox::mailboxLength; i++){
		// set every byte to a arbitrary number to make recognizing errors more easy
		this->rxMailbox.data[i]	= 77;
	}

	for(uint8_t i=0; i<5; i++){
		// set every byte to a arbitrary number to make recognizing errors more easy
		this->txMailbox[i]= new TxMailbox();
	}

	this->indexOfTxMailboxToWriteTo = 0;

	this->rxMailbox.indexStartOfLastMessage = 0;
	this->rxMailbox.numberOfSyncChars = 0;
	this->rxMailbox.waitingForMessage = 0;
	this->numberOfSyncCharsHavingPassedTheTest = 0;


	//***********************************************************************
	//set up DMA
	//***********************************************************************
	Service::enablePeripheralClock((uint32_t)DMA1);			//TODO is it always DMA1?

	  /*Configure DMA for USART*/
	  DMA_InitTypeDef DMA_InitStructure;

	  //set up for data Reception
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(this->hardware->DR));
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(&(this->rxMailbox.data[0]));		//start to write received chars to the beginning of the first mailbox
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;									//move data from peripheral to (buffer) memory
	  DMA_InitStructure.DMA_BufferSize = RxMailbox::mailboxLength;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	  DMA_Init(this->Rx_DMA_Channel, &DMA_InitStructure);


	  //set up for data transmission
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(this->hardware->DR));
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)this->txMailbox[0]->data;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	  DMA_InitStructure.DMA_BufferSize = 0;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

	  //DMA_DeInit(sPort->Tx_DMA_Channel);			//Don't do this to avoid side effects on other modules using the same DMA
	  DMA_Init(this->Tx_DMA_Channel, &DMA_InitStructure);
	  //enable Transmission complete interrupt
	  DMA_ITConfig(this->Tx_DMA_Channel, DMA_IT_TC, ENABLE);

	  //enable DMA Channels
	  DMA_Cmd(this->Rx_DMA_Channel, ENABLE);
	  DMA_Cmd(this->Tx_DMA_Channel, ENABLE);

	  //************************************
	  //set up NVIC
	  //***********************************
	  NVIC_InitTypeDef NVIC_InitStructure;
	  // Enable the USART's 'Received data ready to be read' interrupt / USART global interrupt
	  NVIC_InitStructure.NVIC_IRQChannel = this->USART_global_interrupt;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  // Enable the DMA1 Transmission complete Interrupt
	  NVIC_InitStructure.NVIC_IRQChannel = this->DMA_TransmissionCompleteInterrupt_NVIC_ID;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  return;
}//eof

//********************************
// functions for data transmission
//********************************
uint16_t SerialPort::getMaxTxMailboxCapacity(){
	return TxMailbox::txMailboxLength;
}

void SerialPort::sendTestMessage()
{
     char testMessage[42] = "sending serialPort.c module Teststring\n\r";
	 this->add_String_ToMailbox(testMessage, 42);
	 this->sendMailbox();
	 return;
}//eof

void SerialPort::sendMailbox(){
	TxMailbox* txMailboxToTransmit;
	uint16_t dmaNumberOfDataLeft = 0;
	txMailboxToTransmit = ( this->txMailbox[this->indexOfTxMailboxToWriteTo] );

	//Check if the DMA is still transmitting data. Since the DMA channel's CNDTR register is decreased after
	//the data transfer has been completed, one can be sure that there are no ongoing data transfers
	//once the CNDTR register == 0.
	dmaNumberOfDataLeft = this->Tx_DMA_Channel->CNDTR;
	if(dmaNumberOfDataLeft == 0){
		SerialPort::setUpDMAForNewTransmission(this, txMailboxToTransmit);
	}
	else{
		txMailboxToTransmit->wantsToBeSent = 1;
	}
	//switch to the next mailbox
	this->indexOfTxMailboxToWriteTo++;
	if(this->indexOfTxMailboxToWriteTo >= SerialPort::numberOfTxMailboxes){
		//start over with the first mailbox
		this->indexOfTxMailboxToWriteTo = 0;
	}
	return;
}//eof

void SerialPort::add_String_ToMailbox(char* data, uint16_t numberOfChars)
{
	for(uint16_t i=0; i<numberOfChars; i++){
		this->addToMailbox(data[i]);
	}
	 return;
}//eof

void SerialPort::add_U8_ToMailbox(uint8_t data)
{
	this->addToMailbox((char) data);
	 return;
}//eof

void SerialPort::add_S8_ToMailbox(int8_t data)
{
	this->addToMailbox((char) data);
	return;
}//eof

void SerialPort::add_U16_ToMailbox(uint16_t u16tosend){
	//send 2 bytes, MSB first
		char partByte	= (char)(u16tosend>>8);
		this->addToMailbox(partByte);
		partByte	= (char)u16tosend;
		this->addToMailbox(partByte);
	return;
}//eof

void SerialPort::add_S16_ToMailbox(int16_t s16tosend){
	//send 2 bytes, MSB first
	char partByte	= (char)(s16tosend>>8);
	this->addToMailbox((char) partByte);
	partByte	= (s16tosend & 0xFF);
	this->addToMailbox((char) partByte);
	return;
}//eof

void SerialPort::add_u32_ToMailbox(uint32_t u32tosend){
	//send 4 bytes, LSB first
		char partByte	= 0;
		for(int i=0; i<4; i++){
			partByte = (char)(u32tosend >>(8*i));
			this->addToMailbox((char) partByte);
		}
	return;
}//eof

//*****************************
// functions for data reception
//*****************************

extern "C" void USART1_IRQHandler_sPort()
{
	SerialPort::serialPortUsingUSART1->usart_IRQHandler();
	return;
}//eof

extern "C" void USART2_IRQHandler_sPort()
{
	SerialPort::serialPortUsingUSART2->usart_IRQHandler();
//	Devices::backPointer->statusLED.toggle();
	return;
}//eof

extern "C" void USART3_IRQHandler_sPort()
{
	SerialPort::serialPortUsingUSART3->usart_IRQHandler();
	return;
}//eof

/**
 * \brief Waits for a certain sequence of chars indicating the beginning of a message;
 * once the sequence has been received it calls a listener function.
 */
void SerialPort::usart_IRQHandler(){
	char receivedByte;												//helper variable
	struct RxMailbox* mBox;											//helper pointer;
	uint16_t dmaCount;												//helper variable

	//check the interrupt's source (accessing registers directly to improve performance).
	//a) is it a 'Received data ready to be read' interrupt?
	if((this->hardware->SR && BIT5) > 0){

		//reset interrupt flag; may also be done by just reading the USART->DR Register, says the reference manual.
		//this->hardware->SR &= ~BIT5;		//isn't necessary since the bit is cleared by the DMA permanently running in circular mode
		//check if the SerialPort's inbox is waiting for a message
		if(this->rxMailbox.waitingForMessage == 1){
			//this->rxMailbox.listener();		// FIXME hack
			//first get the current DMA data  counter, assuming that it already has been decreased by one for this byte
			 dmaCount = this->Rx_DMA_Channel->CNDTR;
			//get the received byte
			receivedByte = this->hardware->DR;
			mBox = &(this->rxMailbox);

			// Check if the received char fits the mailboxes syncChars.
			// Check if there are any syncChars to compare.
			if(mBox->numberOfSyncChars == 0){

				// Since the mailbox listener wants to be informed at the beginning of any message (because mBox->numberOfSyncChars == 0)
				// regardless of how the the first characters look like just call it.
				USART1->CR1 &= ~BIT5;								//disable the USART's 'Received data ready to be read' interrupt
				this->rxMailbox.waitingForMessage = 0;				//we're no longer waiting for sync chars
				this->numberOfSyncCharsHavingPassedTheTest = 0;	//set back to zero in preparation for the next message
				if(dmaCount == RxMailbox::mailboxLength){
					dmaCount = 0;								// Since the DMAs NumberOfDataLeftToTransfer register becomes
																// serialPort_RX_MAILBOXLENGTH immediately when it counts to zero and
																// it's easier to detect a data array crossing this way.
					}
					mBox->indexStartOfLastMessage = RxMailbox::mailboxLength - dmaCount - 1;
					// Check if the synChar sequence has crossed the end of the RxMailboxes data array because in this case
					// we have to calculate mBox->indexStartOfLastMessage in a different way
					if(mBox->numberOfSyncChars > (RxMailbox::mailboxLength - dmaCount)){
						mBox->indexStartOfLastMessage = (RxMailbox::mailboxLength) - (1 - (RxMailbox::mailboxLength - dmaCount));
					}
					mBox->listener();
			}
			else if(mBox->syncChars[this->numberOfSyncCharsHavingPassedTheTest] == receivedByte){
				//another char has passed the test
				this->numberOfSyncCharsHavingPassedTheTest++;
				if(this->numberOfSyncCharsHavingPassedTheTest == mBox->numberOfSyncChars) {
					// set_statusLED(1);
					//the full synchronization sequence has been received: inform the mailbox listener.
					this->hardware->CR1 &= ~BIT5;									//disable the USART's 'Received data ready to be read' interrupt
					this->rxMailbox.waitingForMessage = 0;							//we're no longer waiting for sync chars
					this->numberOfSyncCharsHavingPassedTheTest = 0;				//prepare for the next message
					if(dmaCount == RxMailbox::mailboxLength){
											dmaCount = 0;							//since the DMAs NumberOfDataLeftToTransfer register becomes
																					//serialPort_RX_MAILBOXLENGTH immediately when it counts to zero and
																					//it's easier to detect a data array crossing this way
					}
					mBox->indexStartOfLastMessage = RxMailbox::mailboxLength - dmaCount - mBox->numberOfSyncChars;
					//check if the synChar sequence has crossed the end of the mailboxes data array since in this case
					//we have to calculate mBox->indexStartOfLastMessage in a different way
					if(mBox->numberOfSyncChars > (RxMailbox::mailboxLength - dmaCount)){
						//set_statusLED(1);
						mBox->indexStartOfLastMessage = (RxMailbox::mailboxLength) - (mBox->numberOfSyncChars - (RxMailbox::mailboxLength - dmaCount));
					}
					mBox->listener();
				}
			}
			else{
					this->numberOfSyncCharsHavingPassedTheTest = 0;
				}
		}
	}
	return;
}//eof

void SerialPort::registerToMailbox(void(*newListener)(), char* syncChars, uint8_t numberOfSyncChars){
	//pointer to the serialPort's mailbox
	struct RxMailbox* mBox = &(this->rxMailbox);
	//copy listener function
	mBox->listener = newListener;
	//copy sync Chars
	for(uint8_t i=0; (i<numberOfSyncChars) || (i == RxMailbox::rxMailboxMaxNumberOfSyncChars); i++){
		mBox->syncChars[i] = syncChars[i];
	}
	mBox->numberOfSyncChars = numberOfSyncChars;
	mBox->waitingForMessage = 1;

	return;
}//eof

void SerialPort::setMailboxBackToWaitState(){
	this->rxMailbox.waitingForMessage = 1;
	//re-enable USART's 'Received data ready to be read' interrupt
	this->hardware->CR1 |= BIT5;
return;
}//eof



uint16_t SerialPort::getNumberOfReceivedBytes(){
	static uint16_t nofBytes = 0;
	static uint16_t startIndex = 0;
	static uint16_t dmaCount = 0;

	dmaCount = this->Rx_DMA_Channel->CNDTR;
	startIndex =  this->rxMailbox.indexStartOfLastMessage;

	//check if the message crosses the mailboxes limit, continuing at its beginning
	// (RX mailboxLength - startIndex)  = number of bytes left in the mailbox data array following the message
	if( dmaCount >= (RxMailbox::mailboxLength - startIndex) ){
		nofBytes = (RxMailbox::mailboxLength - startIndex) + (RxMailbox::mailboxLength - dmaCount);
		return nofBytes;
	}
	nofBytes = RxMailbox::mailboxLength - startIndex - dmaCount;

	return nofBytes;
}//eof


void SerialPort::getRxData(uint8_t* target, const uint16_t nofBytes){
	static char* source = 0;
	static uint16_t sourceIndex = 0;
	static uint16_t targetIndex = 0;
	static uint16_t overshoot = 0;

	source = (char*)this->rxMailbox.data;
	sourceIndex = this->rxMailbox.indexStartOfLastMessage;

	//check if the message crosses the mailbox data array's border
	if((sourceIndex + nofBytes) >= RxMailbox::mailboxLength){
		overshoot = (sourceIndex + nofBytes) - RxMailbox::mailboxLength;
		//copy the part below the border
		for( targetIndex = 0; sourceIndex<RxMailbox::mailboxLength; sourceIndex++, targetIndex++){
			target[targetIndex] = source[sourceIndex];
		}
		//copy the part at the beginning of the mailbox data array
		for( sourceIndex=0; sourceIndex<overshoot; sourceIndex++, targetIndex++){
			target[targetIndex] = source[sourceIndex];
		}
	 //	 set_statusLED(1);

	}
	else{
		for(targetIndex=0; targetIndex<nofBytes; targetIndex++, sourceIndex++){
			target[targetIndex] = source[sourceIndex];
		}
	}
	return;

}//eof


//***************************************************************************************************************
//*** private functions *****************************************************************************************
//***************************************************************************************************************
//********************************
// functions for data transmission
//********************************

void SerialPort::addToMailbox(char data){
	TxMailbox *txMailboxToTransmit;
	txMailboxToTransmit = ( this->txMailbox[this->indexOfTxMailboxToWriteTo] );
	//check if there is still free memory in the mailbox
	if(	txMailboxToTransmit->indexOfNextWrite < TxMailbox::txMailboxLength){
		txMailboxToTransmit->data[txMailboxToTransmit->indexOfNextWrite] = data;
		(txMailboxToTransmit->indexOfNextWrite)++;
	}
	//if the mailbox reaches its limits, close the current mailbox, send it and - by this - open a new one.
	else{
		this->sendMailbox();
		this->addToMailbox(data);
	}

	return;
}//eof

void SerialPort::setUpDMAForNewTransmission(SerialPort* sPort, TxMailbox* mBox)
{
		//first disable the DMA channel to be able to change its configuration
		DMA_Cmd(sPort->Tx_DMA_Channel, DISABLE);
		//now change the memory address and the number of data to be transfered by the DMA
		sPort->Tx_DMA_Channel->CMAR = (uint32_t)(mBox->data);		//DMA: read from buffer
		sPort->Tx_DMA_Channel->CNDTR = mBox->indexOfNextWrite;		//DMA: read x bytes from buffer
		//re-enable the DMA channel; starts transmission
		DMA_Cmd(sPort->Tx_DMA_Channel, ENABLE);

		sPort->indexOfTxMailboxSentLast = mBox->number;
		mBox->wantsToBeSent = 0;
		mBox->indexOfNextWrite = 0;
	return;
}//eof

/**
 * Wrapper interrupt handler.
 */
extern "C" void DMA1_Channel4_IRQHandler_sPort(void){
	//check which event has caused the interrupt
	//a) is it a Transmission complete interrupt?
	if(DMA_GetITStatus(DMA1_IT_TC4) != RESET){
			DMA_ClearITPendingBit(DMA1_IT_TC4);
			SerialPort::serialPortUsingUSART1->dma_Channelx_TCInterrupt_Handler();
		}
	return;
}//eof

/**
 * Wrapper interrupt handler;
 */
extern "C" void DMA1_Channel2_IRQHandler_sPort(void){
	//check which event has caused the interrupt
	//a) is it a Transmission complete interrupt?
	if(DMA_GetITStatus(DMA1_IT_TC2) != RESET){
			DMA_ClearITPendingBit(DMA1_IT_TC2);
			SerialPort::serialPortUsingUSART3->dma_Channelx_TCInterrupt_Handler();
		}
	return;
}//eof

/**
 * Wrapper interrupt handler;
 */
extern "C" void DMA1_Channel7_IRQHandler_sPort(void){
	//check which event has caused the interrupt
	//a) is it a Transmission complete interrupt?
	if(DMA_GetITStatus(DMA1_IT_TC7) != RESET){
			DMA_ClearITPendingBit(DMA1_IT_TC7);
			SerialPort::serialPortUsingUSART2->dma_Channelx_TCInterrupt_Handler();
		}
	return;
}//eof


void SerialPort::dma_Channelx_TCInterrupt_Handler(){
	TxMailbox* mBox;					//pointer to a txMailbox; used to set up the DMA
	uint8_t index = 0;									//a helper variable

	//identify the next mailbox which is waiting for transmission
	index = this->indexOfTxMailboxSentLast + 1;
	//check if we have reached the end of the mailbox array
	if(index >= SerialPort::numberOfTxMailboxes){
		index = 0;
	}
	// This is the mailbox which would have been used (since we do not know
	// if there has been set up one ore more new mailboxes)
	// to store new data while the DMA has been transmitting.
	mBox = ( this->txMailbox[index]);
	//check if there has been written any new data while the DMA was transmitting
	if( (mBox->wantsToBeSent) == 1)
	{
		//set up the DMA for a new mailbox transmission
		SerialPort::setUpDMAForNewTransmission(this, mBox);
	}

	return;
}//eof
