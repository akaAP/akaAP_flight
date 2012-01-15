/*************************************
 * stm32f103rbt6_afio.c
 * author: jan
 * last modifications:
 *
 * description: TODO
 **************************************/

/* Includes****************************/
#include "../inc/stm32_afio.h"
/*Definitions**************************/

//**********************************************************************
//implementation of public member functions
//*********************************************************************

/**
 * @brief constructor.
 */
AFIO::AFIO(){
	this->reg = (AFIO_RegisterStructure*)AFIO_BASE;
}//eof

/**
 * @brief destructor.
 */
AFIO::~AFIO(){

}//eof

/**
 * @brief initializes the AFIO peripheral
 */

void AFIO::init(){
	this->reg->MAPR |= BIT26;				//disable JTAG and serial wire debug in order to be able to use Timer2 Channel1
}//eof
