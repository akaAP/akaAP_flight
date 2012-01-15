 /*************************************
 * mmav_messages.c
 * author: jan
 * last modifications: 27 September 2010
 * 
 * description: This module has functions one may use to
 * send messages defined in messages.h via a serial interface
 **************************************/

 /*Includes*********************************/
#include "../inc/messages.h"
 /*Definitions******************************/

 /*Functions********************************/

/**
 * @brief use this function to send a message
 * @param int identifier
 */
void sendS16Message(u8 identifier, s16 value){
	//send a message frame
	USART1_SendByte(MESSAGE_START_OF_FRAME);
	USART1_SendByte(MESSAGE_START_OF_FRAME);
	USART1_SendByte(identifier);
	USART1_SendS16(value);
	USART1_SendByte(MESSAGE_END_OF_FRAME);
}//eof
