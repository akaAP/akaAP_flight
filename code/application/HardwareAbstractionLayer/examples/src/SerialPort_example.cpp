/**
 *\file SerialPort_example.cpp
 *\brief Please provide information useful for understanding the code.
 *\author Jan
*/

//Inclusions
#include "../inc/SerialPort_example.h"


static volatile uint8_t newMessageReceived = 0;

void listener(){
	 	 newMessageReceived = 1;
}//eof

void SerialPort_example(){

#define nofSynChars 10
char syncChars[nofSynChars] = {1,2,3,4,5,6,7,8,9,10};
uint8_t buffer[1024] = {0};
char waitMessage[38] = "Waiting for message to be received...";
char gotMessage[21] = "\n\rMessage received: ";

SerialPort* sPort = new SerialPort(USART1, 115200);

sPort->registerToMailbox(&listener, syncChars, 0);
sPort->sendTestMessage();
sPort->add_String_ToMailbox( waitMessage , 37);
sPort->sendMailbox();

while(1){
	//check if a message has been received
	if(newMessageReceived != 0){
		 TimeBase::waitMicrosec(10000);				// wait for all characters to have been received
	 	 uint16_t nofBytes = sPort->getNumberOfReceivedBytes();
	 	 sPort->getRxData( buffer, nofBytes );
		 sPort->add_String_ToMailbox(gotMessage, 21);
		 // write received bytes back to the SerialPort
	 	 for(uint16_t i=0; i<nofBytes; i++){
			 sPort->add_U8_ToMailbox( buffer[i] );
		 }
		 sPort->sendMailbox();
		 newMessageReceived = 0;
		 // Make the SerialPort wait for a message again
		 sPort->setMailboxBackToWaitState();
	}
}


}//eof
