/*************************************
 * stm32f103rbt6_gpio.c
 * author: jan
 * last modifications:
 *
 * description: service functions for GPIOs
 **************************************/

/* Includes****************************/
#include "../inc/stm32_gpio.h"
/*Definitions**************************/

/**
 * @brief constructor.
 * @par char gpioID: the number of the particular GPIO you want to instantiate;
 * may  be 1-5 (GPIOA-GPIOB)
 */
GPIO::GPIO(char gpioID){
	//initialize the pointer to the GPIO register structure
	//check which GPIO out of GPIOA-GPIOG is supposed to be represented by this object
	if(gpioID=='A'){
	this->reg = (GPIO_RegisterStructure*)GPIOA_BASE;
	}
	else if(gpioID=='B'){
		this->reg = (GPIO_RegisterStructure*)GPIOB_BASE;
	}
	else if(gpioID=='C'){
		this->reg = (GPIO_RegisterStructure*)GPIOC_BASE;
	}
	else if(gpioID=='D'){
		this->reg = (GPIO_RegisterStructure*)GPIOD_BASE;
	}
	else if(gpioID=='E'){
		this->reg = (GPIO_RegisterStructure*)GPIOE_BASE;
	}
	else if(gpioID=='F'){
		this->reg = (GPIO_RegisterStructure*)GPIOF_BASE;
	}
	else if(gpioID=='G'){
		this->reg = (GPIO_RegisterStructure*)GPIOG_BASE;
	}
	else{
		//TODO throw an Exception or something?
	}
}//eof

/**
 * @brief destructor.
 */
GPIO::~GPIO(){

}

/**
 * @brief initializes the GPIO port
 */
void GPIO::init(void){

		//set both configuration registers to their default value: all pins are configured as floating inputs
		u32 gpio_defaultConfReg = 0x44444444;
	//	this->reg->CRL = gpio_defaultConfReg; 						//write configuration to gpio control register low
	//	this->reg->CRH = gpio_defaultConfReg; 						//write configuration to gpio control register high

	return;
}

/**
 * @brief Configures a certain GPIO pin.
 * @par : u8 pinNumber: the number of the pin you want to configure; may be 0-15
 * @par : u8 behaviour: determines the behaviour of the pin, may be: one of the behavior_xxxx static constants of the GPIO class
 * @par : u8 speed: may be one of the speed_xxxx static constants of the GPIO class
 */
void GPIO::configPin(u8 pinNumber, u8 behaviour, u8 speed){

	u32 tempReg = 0;
	//check if the configuration should be written to the ConfigurationRegisterLow (pins 0-7), ConfigurationRegisterHigh (pins 8-15)
	if(pinNumber<=7){
		//erase the register bits we want to write to
		u32 eraseReg = 0b1111;
		eraseReg = ~( eraseReg<<(pinNumber*4) );
		this->reg->CRL &= eraseReg;
		//write configuration to GPIO registers
		tempReg |= behaviour;
		tempReg = tempReg<<2;
		tempReg |= speed;
		tempReg = tempReg<<(4*pinNumber);
		this->reg->CRL |= tempReg;
	}
	else if(pinNumber>=8 && pinNumber<=15){
				//erase the register bits we want to write to
				u8 n = pinNumber-8;
				u32 eraseReg = 0b1111;
				eraseReg = ~( eraseReg<<(n*4) );
				this->reg->CRH &= eraseReg;
				//write configuration to GPIO registers
				tempReg |= behaviour;
				tempReg = tempReg<<2;
				tempReg |= speed;
				tempReg = tempReg<<(4*n);
				this->reg->CRH |= tempReg;
	}
	return;
}//eof
