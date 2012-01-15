 /*************************************
 * stm32f103rbt6_usart.c
 * author: jan
 * last modifications: 
 * 
 * description:
 *
 * Things to fix and to improve:
 * FIXME some characters are lost during transmission, check buffer handling
 **************************************/
 /*Includes*********************************/
#include "../inc/stm32_usart.h"

//initialize hardware identifiers
const char* USART::hardwareType= "USART";

//**********************************************************************
//implementation of public member functions
//*********************************************************************

u8 USART::foo(u8 foovar){
	return (foovar+1);
}

/**
 * @brief constructor.
 * @par u8 numberOfPeripheral: the number of the particular USART you want to instantiate;
 * may  be 1-5 (USART1-USART5)
 */
USART::USART(u8 numberOfUSART){
	//initialize the pointer to the USART register structure
	//check which USART out of USART1-USART5 is supposed to be represented by this object
	if(numberOfUSART==1){
		this->reg = (USART_RegisterStructure*)USART1_BASE;
		this->hardwareID = numberOfUSART;
	}
	else if(numberOfUSART==2){
		this->reg = (USART_RegisterStructure*)USART2_BASE;
		this->hardwareID = numberOfUSART;
	}
	else if(numberOfUSART==3){
			this->reg = (USART_RegisterStructure*)USART3_BASE;
			this->hardwareID = numberOfUSART;
		}
	else if(numberOfUSART==4){
			this->reg = (USART_RegisterStructure*)USART4_BASE;
			this->hardwareID = numberOfUSART;
		}
	else if(numberOfUSART==5){
			this->reg = (USART_RegisterStructure*)USART5_BASE;
			this->hardwareID = numberOfUSART;

		}
	else{
		//TODO throw an exception or something?
	}

	//initialize buffer variables
	//write zeros to tx buffer
	for(u16 i=0; i<this->txBufferLength; i++){
	this->txBuffer[i] = 0;
	}
	this->txBuffer_indexOfNextWrite		= 0;
	this->txBuffer_sendNextAtIndex		= 0;
	this->txBuffer_nofBytesLeftToSend	= 0;
	this->transmitting 					= FALSE;
}//eof

/**
 * @brief destructor.
 */
USART::~USART(void){
	//USART::test = 0;
}//eof

/**
 * @brief This function initializes and starts the USART peripheral.
 */
void USART::init(void)
{
	this->reg->BRR = 0;				//set to default
	this->reg->CR1 = 0;				//set to default
	this->reg->CR2 = 0;				//set to default
	this->reg->CR3 = 0;				//set to default
	this->reg->GTPR = 0;				//set to default

	this->reg->CR1 |= BIT13;			//enable USART1

	this->reg->BRR = 0x271;			//baudrate 115200 bei 72MHz. TODO doesn't work yet for USART2-USART5 since they get the slower APB1 clock

	//USART1_CR3 |= BIT7;				//enable DMA mode for transmissions
	//USART1_CR3 |= BIT6;				//enable DMA mode for receptions

	this->reg->CR1 |= BIT6;			//enable Transmission Complete interrupt

	this->reg->CR1 |= BIT3;			//enable Transmitter
	this->reg->CR1 |= BIT2;			//enable Receiver

	//initialize variables


	return;

}//eof

/**
 * @brief sends a u8 by USART.
 */
void USART::sendU8(u8 data)
{
	this->sendByte((char) data);
	 return;
}//eof

/**
 * @brief sends a char arry / string by USART.
 */
void USART::sendString(char* stringToSend ){
	u16 stringLength = stringlength(stringToSend);
	for(u16 i=0; i< stringLength; i++){
		this->sendByte(stringToSend[i]);
	}

	return;
}//eof


/**
 * @brief This function is called when a global USARTx interrupt occurs (There is one global interrupt for
 * each USARTx peripheral)
 */
void USART::IRQHandler(void){
	//check what has caused the interrupt
	//a) is it the Transmission Complete interrupt?
	if( (this->reg->SR & BIT6)>0 ){
		//toggle_statusLED();
		//interrupt flag is cleared by reading USART_SR and writing to USART_DR
		//or by the following line since writing to USART_DR is not guaranteed if there are no bytes to send
		this->reg->SR &= ~BIT6;
		this->transmitting = FALSE;
		//if there are bytes to send in the buffer:
		if((this->txBuffer_nofBytesLeftToSend>0)){
			//check if we're at the end of the buffer
			if(this->txBuffer_sendNextAtIndex>this->txBufferLength-1){
				//go to the beginning of the buffer
				this->txBuffer_sendNextAtIndex = 0;
			}
			u16 tmp = 0;
			this->reg->DR = (tmp|this->txBuffer[this->txBuffer_sendNextAtIndex]);
			this->txBuffer_sendNextAtIndex++;
			this->txBuffer_nofBytesLeftToSend--;
		}
	}
	return;
}//eof

//**********************************************************************
//*implementation of private member functions
//**********************************************************************

/**
 * @brief transmits a byte by a USART.
 * Parameter of type char to avoid casting issues e.g. signed integer->integer
 */
void USART::sendByte(char data){
		//if the buffer has been empty and no Transmission is going on send the byte directly
		if( this->txBuffer_nofBytesLeftToSend==0 && this->transmitting==FALSE ){
			u16 tmp = 0;
			this->reg->DR = (tmp|data);
			this->transmitting = TRUE;
		}
		//otherwise write it to the buffer
		else{
			//let's see if there is an sufficient amount of space in the buffer, otherwise write to the beginning of the buffer
			if((this->txBufferLength-1) < (this->txBuffer_indexOfNextWrite) ){
				this->txBuffer_indexOfNextWrite = 0;
			}
			this->txBuffer[this->txBuffer_indexOfNextWrite] = data;
			this->txBuffer_nofBytesLeftToSend++;
			this->txBuffer_indexOfNextWrite++;
		}
		return;
}//eof


//**********************************************************************
//*functions used to access the classes interrupt handler functions
//*********************************************************************

/**
 * @brief This Function is used as a kind of a mask for the interrupt vector table. Since this table
 * has to contain pointers to functions and getting a pointer to a classes member function
 * turned out to be quite hard this function just calls the appropriate interrupt handler member function.
 */
void USART1_IRQhandler(){
	//TODO uncomment USART1.irqHandler();
return;
}//eof

/**
 * @brief This Function is used as a kind of a mask for the interrupt vector table. Since this table
 * has to contain pointers to functions and getting a pointer to a classes member function
 * turned out to be quite hard this function just calls the appropriate interrupt handler member function.
 */
void USART2_IRQhandler(){
	//TODO uncomment USART2.irqHandler();
return;
}//eof

/**
 * @brief This Function is used as a kind of a mask for the interrupt vector table. Since this table
 * has to contain pointers to functions and getting a pointer to a classes member function
 * turned out to be quite hard this function just calls the appropriate interrupt handler member function.
 */
void USART3_IRQhandler(){
	//TODO uncomment USART3.irqHandler();
return;
}//eof
