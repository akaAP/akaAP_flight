 /*************************************
 * stm32_can.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_can.h"

/*Definitions******************************/

/*Functions********************************/
/**************CAN1*************************/
/**
 * initialize the CAN1 peripheral to work as following:
 * - baudrate 1MBit/s
 * - 11 bit identifier
 * - Loop back mode
 * - normal mode, time triggered communication mode to be tested later
 * - no automatic retransmission after a transmission has failed
 * Can clock is APB1, 36MHz
 */
void CAN1_Init()
{
	//activate CAN1 clock
	CAN1_ClkInit();
	//leave sleep mode, clear SLEEP bit
	CAN1_MCR &= ~BIT1;
	//wait for the CAN to acknowledge that it has left sleep mode (SLAK bit is cleared by hardware)
    while(isBitSet(CAN1_MSR, 1)){}
	//enter initialization mode*****************************************************************************************************
	CAN1_MCR |= BIT0;
	//wait for the CAN to acknowledge that it has entered initialization mode
    while(!isBitSet(CAN1_MSR,  0)){}

	//set: CAN works during debugging
	clearBit(&CAN1_MCR, 16);

	//set up bit timing
	//set Time Segment 1 and Time Segment 2 to 1 [ (tBS1 = tCAN x (CAN1_BTR[19:16] + 1)), (tBS2 = tCAN x (CAN1_BTR[22:20] + 1)) ]
    CAN1_BTR = 0;				//default value: 0x01230000
	setBit(&CAN1_BTR, 16);
	setBit(&CAN1_BTR, 20);
	//set Resynchronization Jump Width to 2 ( tRJW = tCAN x (SJW[1:0] + 1) )
	CAN1_BTR |= BIT24;
	//set length of a time quantum to (1/(36MHz))*359+1 = 10µs to
	//CAN1 clock is APB1 clock = 36MHz
	u16 baudratePrescaler = 359;
	CAN1_BTR |= (baudratePrescaler-1);		//since timequantum = (CAN1_BTR[9:0]+1)*APB1clock


	//enable silent mode
	//CAN1_BTR |= BIT31;
	//enable loop-back mode
	//CAN1_BTR |= BIT30;

	//disable automatic retransmission
	CAN1_MCR |= BIT4;

	//set Transmit FIFO priority: driven by the request order (chronologically)
	CAN1_MCR |= BIT2;

	//set up interrupts
	//enable Error interrupt
	//CAN1_IER |= BIT15;
	//enable Transmit Mailbox Empty interrupt
	CAN1_IER |= BIT0;
	//enable receive FIFO pending_1 state interrupt
	CAN1_IER |= BIT1;
	//enable receive FIFO pending_2 state interrupt
	CAN1_IER |= BIT4;

	//enter filter initialization mode to set up the filter banks*******************************************************************
	CAN1_FMR |= BIT0;

	//set up filter No. 0
	CAN1_F0R1 = 100;				//identifier = 100
	CAN1_F0R1 = 0xFFFFFFFF;			//all bits are relevant, the bits of the incoming identifier must have the same level as specified in the corresponding identifier register
	//leave filter initialization mode
	CAN1_FMR &= ~BIT0;
	//activate filters
	CAN1_FA1R|= BIT0;
	/*
	CAN1_FA1R|= BIT2;  CAN1_FA1R|= BIT3;  CAN1_FA1R|= BIT4;
	CAN1_FA1R|= BIT5;  CAN1_FA1R|= BIT6;  CAN1_FA1R|= BIT7;
	CAN1_FA1R|= BIT8;  CAN1_FA1R|= BIT9;  CAN1_FA1R|= BIT10;
	CAN1_FA1R|= BIT11; CAN1_FA1R|= BIT12; CAN1_FA1R|= BIT13;
	*/

	// enter Normal mode
	CAN1_MCR &= ~BIT0;
	//wait for the CAN to acknowledge that it has entered normal mode (INAK bit in CAN1_MSR)
	while( isBitSet(CAN1_MSR, 0) ){}

	return;
}//eof

/**
 * @brief sends a message by CAN bus.
 * @param identifier : CAN message ID
 * @param payloadBytes : array containing the bytes to send; 0-8 byte, 0-6 using time-triggered mode (last 2 bytes: message timestamp)
 * @param numberOfPayloadBytes : how many bytes are supposed to be sent
 */
void CAN1_SendMessage(u16 identifier,  char* payloadBytes, u8 numberOfPayloadBytes){
	//TODO check whether the mailbox is empty
	//transmit message, use Transmit Mailbox 0

	//set data length code
	if(numberOfPayloadBytes<9){
		CAN1_TDT0R = 0;								//set to default (register value undefined after reset)
		CAN1_TDT0R |= (u32)numberOfPayloadBytes;

	// set up the identifier
	CAN1_TI0R = 0;									//set to default (register value undefined after reset)
	u32 identifierMask = ((u32)identifier)<<21;		//identifier starts at bit 21 in CAN1_TI0R
	CAN1_TI0R |= identifierMask;

	//set up payload data bytes
	u32 dataRegLow = 0;
	u32 dataRegHigh = 0;
	//if both the data low and the data high register have to be filled
	if(numberOfPayloadBytes>4){
		for(u8 i=0; i<4; i++){
			dataRegLow = dataRegLow<<8*i;
			dataRegLow |= payloadBytes[i];
		}

		for(u8 i=3; i<numberOfPayloadBytes; i++){
					dataRegHigh = dataRegLow<<8*i;
					dataRegHigh |= payloadBytes[i];
				}
	}//eoif
	else{
		for(u8 i=0; i<numberOfPayloadBytes; i++){
			dataRegLow = dataRegLow<<(8*i);
			dataRegLow |= payloadBytes[i];
		}
	}//eoelse
	//write to data low and data high register
	CAN1_TDL0R = dataRegLow;
	CAN1_TDH0R = dataRegHigh;

	//set transmission request bit to start the Transmission
	CAN1_TI0R |= BIT0;

	}//eoif
}//eof
