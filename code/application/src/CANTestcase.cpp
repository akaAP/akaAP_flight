/*
 * \file CANTestcase.cpp
 * \brief Test case to figure out why the CAN bus works on a STM32F103RBT6 (medium-density device) but not
 * on a STM32RET6 (high-density device). Just create an instance of CANTestcase and call the
 * sendTestMessageInALoop() method.
 */

//Inclusions
#include "CANTestcase.h"
#include "../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h"

/**
 * \brief Constructor implementation.
 */
CANTestcase::CANTestcase(){

	this->setUp();
	return;
}//eof

/**
 * \brief Destructor implementation.
 */
CANTestcase::~CANTestcase(){
	// FIXME free memory
}//eof

/**
 * \brief Call this method to make the CANTestcase driver configure pins,
 * set up the CAN peripheral et cetera.
 */
void CANTestcase::setUp()
{
	// Enable CAN1 peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	// Enable GPIO clock of CAN_Tx and CAN_Rx pins.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/* Configure CAN pin: RX */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure CAN pin: TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure CAN peripheral:
	CAN_InitTypeDef        CAN_InitStructure;
	/* CAN register init */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

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
  * \brief  Transmits a test message just to see some
  * bits on the bus lines.
  */
void CANTestcase::sendTestMessageInALoop()
{
	while(true)
	{
		// Wait for ~10ms.
		// TODO why has the loop variable to be marked as volatile? It's just a standard for-loop, the actual value
		// of the variable should be evaluated without that.
		for(volatile uint32_t a=0; a<60000;a++)
		{
			;
		}
		// Toggle the status LED.
		this->toggleLED();
		// Toggle CANTx to see if the pin'S state can be set. To do so, Configure pin as generel-purpose push pull in the setUp([...]) method.
		//this->toggleCANTx();

		// Variable to take the return value of the CAN_Transmit([...]) function.
		uint8_t TransmitMailbox = 0;
		// Define message.
		CanTxMsg TxMessage;
		TxMessage.StdId=0x11;
		TxMessage.RTR=CAN_RTR_DATA;
		TxMessage.IDE=CAN_ID_STD;
		TxMessage.DLC=2;
		TxMessage.Data[0]=0xCA;
		TxMessage.Data[1]=0xFE;
		// Send Message.
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
	return;
}//eof

void CANTestcase::toggleLED()
{
	static bool state;
	if (state==true)
	{
		GPIOC->BSRR |= GPIO_Pin_12;
		state = false;
	}
	else
	{
		GPIOC->BRR |= GPIO_Pin_12;
		state = true;
	}
return;
}//eof

void CANTestcase::toggleCANTx()
{
	static bool state;
	if (state==true)
	{
		GPIOA->BSRR |= GPIO_Pin_12;
		state = false;
	}
	else
	{
		GPIOA->BRR |= GPIO_Pin_12;
		state = true;
	}
return;
}//eof
