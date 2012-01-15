 /*************************************
 * \file NodeLink.cpp
 * \brief
 * \author: jan bolting
 *
 **************************************/

#include "../inc/NodeLink.h"
/**
 * \brief Constructor.
 */
NodeLink::NodeLink(){

	this->setUp();
	return;
}//eof

/**
 * Destructor.
 */
NodeLink::~NodeLink(){
	// FIXME free memory
}//eof

/**
 * \brief Call this method to make the NodeLink driver configure pins,
 * set up the CAN peripheral et cetera.
 * TODO The Driver should not assume the Pins and which CANx is used
 * but these parameters should be given to the constructor to avoid hiding
 * hardware specifics deep in the code.
 */
void NodeLink::setUp()
{
	// Enable CAN1 peripheral clock.
	Service::enablePeripheralClock((uint32_t)CAN1);

	// Configure Interrupt Controller
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable CAN1 RX0 interrupt IRQ channel */						// TODO There are different interrupt names for connectivity line and xl-density devices
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// FIXME Set priority; CAN should have highest priority to make the node react to data requests as fast as possible
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* GPIO clock enable */
	Service::enablePeripheralClock((uint32_t)GPIOA);

	/* Configure CAN pin: RX */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure CAN pin: TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	CAN_InitTypeDef        CAN_InitStructure;
	/* CAN register init */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	/* CAN cell init */
	  CAN_InitStructure.CAN_TTCM = DISABLE;
	  CAN_InitStructure.CAN_ABOM = DISABLE;
	  CAN_InitStructure.CAN_AWUM = DISABLE;
	  CAN_InitStructure.CAN_NART = ENABLE;
	  CAN_InitStructure.CAN_RFLM = DISABLE;
	  CAN_InitStructure.CAN_TXFP = DISABLE;
	  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
	  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
	  CAN_InitStructure.CAN_Prescaler = 20;
	  CAN_Init(CAN1, &CAN_InitStructure);

	  /* CAN filter init */
	  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	  CAN_FilterInitStructure.CAN_FilterNumber=0;
	  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
	  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	  CAN_FilterInit(&CAN_FilterInitStructure);

}//eof

 /**
  * \brief  Transmits and receives a message.
  */
void NodeLink::testLoop()
{
	while(true)
	{
		TimeBase::waitMicrosec(10000);
		Devices::backPointer->statusLED.toggle();
		this->testTwoWay();
	}
}//eof


/**
 * Sends a Message.
 */
void NodeLink::testTwoWay()
{
	  uint8_t TransmitMailbox = 0;
	  CanTxMsg TxMessage;
	  // Define message.
	  TxMessage.StdId=0x11;
	  TxMessage.RTR=CAN_RTR_DATA;
	  TxMessage.IDE=CAN_ID_STD;
	  TxMessage.DLC=2;
	  TxMessage.Data[0]=0xCA;
	  TxMessage.Data[1]=0xFE;

	  TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	  return;
}//eof


/**
  * \brief  CAN1 receive interrupt Handler. Compares the received message to
  * the sent one and toggles the status LED if both are identical.
  */
/*
extern "C" void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	if (RxMessage.StdId==0x11
			&& RxMessage.IDE == CAN_ID_STD
			&& RxMessage.DLC == 2
			&& (RxMessage.Data[0]<<8|RxMessage.Data[1]) == 0xCAFE)
	{
		Devices::backPointer->statusLED.toggle();
	}
 }//eof
*/



