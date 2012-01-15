 /*************************************
 * stm32rbt6_library.cpp
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_library.h"
#include "../inc/stm32_usart.h"
/*Definitions******************************/

//const char* STM32Peripheral::hardwareType = "default";


STM32* STM32::pointerToStm32 = 0;

 /*Functions********************************/
/**
 * @brief constructor.
 */
STM32::STM32()
:nvic(), rcc(), gpioA('A'), gpioB('B'), gpioC('C'), usart1(1)
{	//set pointer to this STM32 object used to access the peripherals interrupt handlers
	STM32::pointerToStm32 = this;
}//eof

/**
 * @brief destructor.
 */
STM32::~STM32(void){

}//eof


//**************************************************************************************
//	Implementation of static Interrupt Handler wrapper functions
//**************************************************************************************

//Cortex M3 core interrupts
void STM32::nmi_IRQHandler(void){
	return;
}

void STM32::hardfault_IRQHandler(void){
	return;
}

void STM32::memManage_IRQHandler(void){
	return;
}

void STM32::busFault_IRQHandler(void){
	return;
}

void STM32::usageFault_IRQHandler(void){
	return;
}

/**
 * @brief handler for reserved interrupts not used in the vector table yet.
 */
void STM32::dummyIRQHandler(void){
	return;
}

void STM32::svc_IRQHandler(void){
	return;
}

void STM32::debugMon_IRQHandler(void){
	return;
}

void STM32::pendSV_IRQHandler(){
	return;
}
void STM32::sysTick_IRQHandler(void){
	STM32::pointerToStm32->rcc.sysTickHandler();
	return;
}

//STM32 interrupts
void STM32::windowWatchdog_IRQHandler(){
	return;
}

void STM32::PVD_IRQHandler(){
	return;
}

void STM32::TAMPER_IRQHandler(){
	return;
}

void STM32::RTC_IRQHandler(){
	return;
}

void STM32::FLASH_IRQHandler(){
	return;
}

void STM32::RCC_IRQHandler(){
	return;
}

void STM32::EXTI0_IRQHandler(){
	return;
}

void STM32::EXTI1_IRQHandler(){
	return;
}

void STM32::EXTI2_IRQHandler(){
	return;
}

void STM32::EXTI3_IRQHandler(){
	return;
}

void STM32::EXTI4_IRQHandler(){
	return;
}

void STM32::DMA1_CH1_IRQHandler(){
	return;
}

void STM32::DMA1_CH2_IRQHandler(){
	return;
}

void STM32::DMA1_CH3_IRQHandler(){
	return;
}

void STM32::DMA1_CH4_IRQHandler(){
	return;
}

void STM32::DMA1_CH5_IRQHandler(){
	return;
}

void STM32::DMA1_CH6_IRQHandler(){
	return;
}

void STM32::DMA1_CH7_IRQHandler(){
	return;
}

void STM32::ADC_1_2_IRQHandler(){
	return;
}

/**
 * this function is called either when the CAN Transmit Mailbox 0,1 or 2 becomes empty
 * or -if USB is used - when something happens to the USB (TODO find out what)
 */
void STM32::USB_HP_CAN_TX_IRQHandler(void){
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
void STM32::USB_LP_CAN_RX0_IRQHandler(void){
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
void STM32::CAN_RX1_IRQHandler(void){
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
void STM32::CAN_SCE_IRQHandler(void){
	//send a byte to show that the interrupt has happened
	//USART3_SendU8(13);
	return;
}//eof

void STM32::EXTI_9_5_IRQHandler(){
	return;
}

void STM32::TIM1_UP_IRQHandler(){
	return;
}//eof

void STM32::TIM1_CC_IRQHandler(){
	return;
}//eof

void STM32::TIM1_BRK_IRQHandler(){
	//clear the break event interrupt bit in the timer Status Register
	//TIMER1_clearBreakInterruptFlag();
	return;
}//eof

void STM32::TIM1_TRG_COM_IRQHandler(void){
	return;
}

void STM32::TIM2_IRQHandler(void){
	return;
}

void STM32::TIM3_IRQHandler(void){
	return;
}

void STM32::TIM4_IRQHandler(void){
	return;
}

void STM32::I2C1_EV_IRQHandler(void){
	return;
}

void STM32::I2C1_ER_IRQHandler(void){
	return;
}

void STM32::I2C2_EV_IRQHandler(void){
	return;
}

void STM32::I2C2_ER_IRQHandler(void){
	return;
}

void STM32::SPI1_IRQHandler(void){
	return;
}

void STM32::SPI2_IRQHandler(void){
	return;
}

void STM32::STM32::USART1_IRQHandler(void){
	STM32::pointerToStm32->usart1.IRQHandler();
}

void STM32::STM32::USART2_IRQHandler(void){
	//STM32::pointerToStm32->usart2.IRQHandler();
}

void STM32::STM32::USART3_IRQHandler(void){
	//STM32::pointerToStm32->usart3.IRQHandler();
}
