/*************************************
 * stm32_nvic.c
 * author: jan
 * last modifications:
 *
 * description: TODO
 **************************************/

/* Includes****************************/
#include "../inc/stm32_nvic.h"
#include "../inc/stm32_serv.h"
#include "../inc/stm32_can.h"
#include "../inc/stm32_rcc.h"

/*Definitions**************************/

//void (NVIC::ptrTo_sysTick_IRQhandler)(void) = &RCC::real_sysTick_IRQHandler;

//**********************************************************************
//implementation of public member functions
//*********************************************************************

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
	//activate interrupts 0-63
	NVIC_ISER_0_TO_31 |= 0xFFFFFFFF;
	NVIC_ISER_32_TO_63 |= 0xFFFFFFFF;

	//set the interrupt priorities to some value just to see what happens
	//NVIC_IPR_24_TO_27 = 0x55555555;
}//eof

