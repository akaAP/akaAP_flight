/*************************************
 * stm32_nvic.c
 * author: jan
 * last modifications:
 *
 * description: TODO
 **************************************/

/* Includes****************************/
#include "../inc/stm32_nvic.h"
/*Definitions**************************/

//void (NVIC::ptrTo_sysTick_IRQhandler)(void) = &RCC::real_sysTick_IRQHandler;

//**********************************************************************
//implementation of public member functions
//*********************************************************************

void NVIC::dummy(void){
	return;
}//eof

/**
 * @brief constructor.
 */
NVIC::NVIC(){
	//FIXME set proper register address this->reg = (NVIC_RegisterStructure*) (0x0);
	//this->ptrTo_sysTick_IRQhandler = &NVIC::dummy;
}//eof

/**
 * @brief destructor.
 */
NVIC::~NVIC(){

}//eof

/**
 * @brief initializes the NVIC
 */

void NVIC::init(){
}//eof

/**
 * @brief this function configures the NVIC by enabling interrupts etc.
 */
void NVIC_Init(){
	//activate interrupts
	//interrupts 24-27
	NVIC_ISER_0_TO_31 |= 0xFFFFFFFF;
	NVIC_ISER_32_TO_63 |= 0xFFFFFFFF;
	//set the interrupt priorities to some value just to see what happens
	//NVIC_IPR_24_TO_27 = 0x55555555;
}//eof

//*****************************************************************************************************
//Interrupt Service Routines; some other ISR's may be defined in the peripheral files e.g stm32_usart.c
//******************************************************************************************************
//Cortex M3 core interrupts
void nmi_IRQhandler(void){return;}
void hardfault_IRQhandler(void){return;}
void memManage_IRQhandler(){return;}
void busFault_IRQhandler(){return;}
void usageFault_IRQhandler(){return;}
void dummyHandler(){return;}					//handler for reserved interrupts not used in the vector table yet
void svc_IRQhandler(){return;}
void debugMon_IRQhandler(){return;}
void pendSV_IRQhandler(){return;}

// @brief SysTick interrupt handler
void sysTick_IRQhandler(){
	// NVIC::ptrTo_sysTick_IRQhandler();
}//eof

//STM32 interrupts
void windowWatchdog_IRQhandler(){return;}
void PVD_IRQhandler(){return;}
void TAMPER_IRQhandler(){return;}
void RTC_IRQhandler(){return;}
void FLASH_IRQhandler(){return;}
void RCC_IRQhandler(){return;}
void EXTI0_IRQhandler(){return;}
void EXTI1_IRQhandler(){return;}
void EXTI2_IRQhandler(){return;}
void EXTI3_IRQhandler(){return;}
void EXTI4_IRQhandler(){return;}
void DMA1_CH1_IRQhandler(){return;}
void DMA1_CH2_IRQhandler(){return;}
void DMA1_CH3_IRQhandler(){return;}
void DMA1_CH4_IRQhandler(){return;}
void DMA1_CH5_IRQhandler(){return;}
void DMA1_CH6_IRQhandler(){return;}
void DMA1_CH7_IRQhandler(){return;}
void ADC_1_2_IRQhandler(){return;}

/**
 * this function is called either when the CAN Transmit Mailbox 0,1 or 2 becomes empty
 * or -if USB is used - when something happens to the USB (TODO find out what)
 */
void USB_HP_CAN_TX_IRQhandler(){
	//check out what has caused the interrupt
	//has the first mailbox been transmitted?
	if(isBitSet(CAN1_TSR ,0)){
		clearBit(&CAN1_TSR ,26);		// clear Transmit Mailbox 0 empty bit
		clearBit(&CAN1_TSR ,0);
	}
	//or the second one?
	if(isBitSet(CAN1_TSR ,8)){
		clearBit(&CAN1_TSR ,27);		// clear Transmit Mailbox 1 empty bit
		clearBit(&CAN1_TSR ,8);
	}
	//or the third one?
	if(isBitSet(CAN1_TSR ,16)){
		clearBit(&CAN1_TSR ,28);		// clear Transmit Mailbox 2 empty bit
		clearBit(&CAN1_TSR ,16);
	}
	//USART1_SendU8(10);
	return;
}//eof

/**
 * this function is called either when
 * 	- the CAN FIFO1 has received a new message
 *  - the CAN FIFO1 is full
 *  - a CAN FIFO1 overrun occurred
 * or -if USB is used - when something happens to the USB (TODO find out what)
 * and -of course- if the related interrupt is enabled in the CAN/USB peripheral and the NVIC
 */
void USB_LP_CAN_RX0_IRQhandler(){
	//send a byte to show that the interrupt has happened
	//USART3_SendU8(11);
	return;
}//eof

/**
 * this function is called either when
 * 	- the CAN FIFO1 has received a new message
 *  - the CAN FIFO1 is full
 *  - a CAN FIFO1 overrun occurred
 * or -if USB is used - when something happens to the USB (TODO find out what)
 * and -of course- if the related interrupt is enabled in the CAN7USB peripheral and the NVIC
 */
void CAN_RX1_IRQhandler(){
	//send a byte to show that the interrupt has happened
	//usart1.sendU8(12);
	return;
}//eof

/**
 * this function is called either when
 * 	- a CAN Error condition occurred
 *	- a Wakeup condition occurred or
 *	- the CAN entered Sleep Mode
 */
void CAN_SCE_IRQhandler(){
	//send a byte to show that the interrupt has happened
	//USART3_SendU8(13);
	return;
}//eof

void EXTI_9_5_IRQhandler(){return;}
void TIM1_BRK_IRQhandler(){
	//clear the break event interrupt bit in the timer Status Register
	TIMER1_clearBreakInterruptFlag();
	return;
}//eof
void TIM1_TRG_COM_IRQhandler(){return;}
void TIM2_IRQhandler(){return;}
void TIM3_IRQhandler(){return;}
void TIM4_IRQhandler(){return;}
void I2C1_EV_IRQhandler(){return;}
void I2C1_ER_IRQhandler(){return;}
void I2C2_EV_IRQhandler(){return;}
void I2C2_ER_IRQhandler(){return;}
void SPI1_IRQhandler(){return;}
void SPI2_IRQhandler(){return;}
