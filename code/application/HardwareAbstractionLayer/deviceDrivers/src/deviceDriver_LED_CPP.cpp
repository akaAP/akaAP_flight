 /*************************************
 * \file deviceDriver_LED.c
 * \brief This driver provides functions to control an LED
 * \author: jan bolting
 *
 **************************************/

 /*Includes*********************************/
#include "../inc/deviceDriver_LED_CPP.h"

/**
 * \brief Constructor, just for tests, not recommended.
 */
LED::LED(){
	this->GPIOPort = GPIOC;
	this->GPIOPin = GPIO_Pin_12;

	Service::enablePeripheralClock((uint32_t)this->GPIOPort);
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure GPIO for LED as Output push-pull
	GPIO_InitStructure.GPIO_Pin = this->GPIOPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(this->GPIOPort, &GPIO_InitStructure);

	this->set(0);
}//eof


/**
 * \brief Constructor, instantiates and initializes an LED.
 */
LED::LED(GPIO_TypeDef* port, uint16_t pin, uint8_t initialStatus){

	this->GPIOPort = port;
	this->GPIOPin = pin;

	Service::enablePeripheralClock((uint32_t)port);
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure GPIO for LED as Output push-pull
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(port, &GPIO_InitStructure);

	this->set(initialStatus);
}//eof

/**
 * \brief Destructor.
 */
LED::~LED(){
	// TODO free memory
	return;
}//eof


/**
 * \brief toggles an LED.
 */
void LED::toggle(){
	this->set(!(this->status));
	return;
}//eof

/**
 * \brief Switches an LED on or off. Since the fixed port of the LED is connected to Vcc,
 * state '1' means switching the LED port to GND = 0.
 * \par state - 1: switch LED on, 0: switch LED off
 */

void LED::set(uint8_t state)
{
	if (state==LED::state_OFF)
	{
		this->GPIOPort->BSRR |= this->GPIOPin;
		this->status = LED::state_OFF;
	}
	else
	{
		this->GPIOPort->BRR |= this->GPIOPin;
		this->status = LED::state_ON;
	}
return;
}//eof
