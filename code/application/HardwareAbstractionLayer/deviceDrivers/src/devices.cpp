/*
 * \file devices.c
 *
 * \author Jan
 * \brief Class representing external devices as ADCs, LEDs etc.
 */

#include "../inc/devices.h"

static uint32_t servoBankGpioPins[2] = { (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7),
								   (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9)
								};
static GPIO_TypeDef* servoBankGPIOs[2] = {GPIOA, GPIOB};
static TIM_TypeDef* servoBankTimers[1] = {TIM4};
static uint32_t defaultChannelWidths[12] = {1000000, 1000000, 1000000, 1000000,
										1000000, 1000000, 1000000, 1000000,
										1000000, 1000000, 1000000, 1000000, };



//declare static members
Devices* Devices::backPointer;
/**
 * @brief constructor.
 */
Devices::Devices(void)
:statusLED(GPIOC, GPIO_Pin_12, LED::state_ON),
 spektrumSatellite(USART3),
 servoBank(	12,
		 	 servoBankTimers, 1,
		 	 servoBankGPIOs, &servoBankGpioPins[0], 2,
		 	 20000000,
		 	 defaultChannelWidths
			)
{
	Devices::backPointer = this;
}//eof

/**
 * @brief destructor.
 */
Devices::~Devices(void){

}//eof
