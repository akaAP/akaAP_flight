 /*************************************
 * stm32_usart.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_USART_H_
#define STM32_USART_H_

//#include "../../CMSIS/Core/CM3/stm32f10x.h"

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"

/*Register structure******************************************/
typedef struct
{
  vu16 SR;
  u16 RESERVED0;
  vu16 DR;
  u16 RESERVED1;
  vu16 BRR;
  u16 RESERVED2;
  vu16 CR1;
  u16 RESERVED3;
  vu16 CR2;
  u16 RESERVED4;
  vu16 CR3;
  u16 RESERVED5;
  vu16 GTPR;
  u16 RESERVED6;
} USART_RegisterStructure;

/*peripheral class***************************************/

class USART
{
	public:
		USART(u8 hardwareID);							//constructor
		~USART(void);									//destructor
		static const char* hardwareType;				//string describing the hardware the object represents;
		static const u8 test = 0;
		u8 hardwareID;									//indicates which Peripheral this object represents; e.g. for USART-> hardwareID = 1
		void init();									//starts the USART peripheral
		u32 clockFrequency;								//frequency of the USARTs peripheral clock [Hz]
		void sendU8(u8 data);							//sends a u8 by USART
		void sendString(char* string);					//sends a char array / string by USART
		USART_RegisterStructure* reg;					//pointer to the USART_RegisterStructure used to access the peripheral's registers
		void IRQHandler(void);							//usart global interrupt handler
		static u8 foo(u8 foovar);
	private:
		void sendByte(char data);
		//transmit buffer variables and constants*******/
		static u16 const txBufferLength = 300;			//USART Transmit Buffer length (max. (2^16)-1
		char txBuffer[txBufferLength];					//the transmit buffer
		u16 txBuffer_indexOfNextWrite;					//indicates at which index the next byte should be written to the buffer
		u16 txBuffer_sendNextAtIndex;					//indicates which buffer byte should be transmitted next
		u16 txBuffer_nofBytesLeftToSend;				//indicates how many bytes are left to send. Is increased by the sendX functions and decreased by
														//the Interrupt function writing bytes to the usart data register
		boolean transmitting;							//indicates that the USART is transmitting
		/*configuration variables and constants********/

};//eoc


//global USART objects; each one represents a peripheral****************
/*
extern USART USART1;
extern USART USART2;
extern USART USART3;
*/
/*USART Function Prototypes*************************************/
void USART1_IRQhandler();
void USART2_IRQhandler();
void USART3_IRQhandler();

#endif /* STM32_USART_H_ */
