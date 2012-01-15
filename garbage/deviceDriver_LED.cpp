 /*************************************
 * \file deviceDriver_LED.c
 * \brief This driver provides functions to control a LED
 * \author: jan bolting
 *
 **************************************/

 /*Includes*********************************/
#include "../inc/deviceDriver_LED.h"

/**
 * \brief Initializes an LED.
 */
void LED_Init(struct LED* led, GPIO_TypeDef* port, uint16_t pin, uint8_t initialStatus){
	led->GPIOPort = port;
	led->GPIOPin = pin;

	service_enablePeripheralClock((uint32_t)led->GPIOPort);
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure GPIO for LED as Output push-pull
	GPIO_InitStructure.GPIO_Pin = led->GPIOPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(led->GPIOPort, &GPIO_InitStructure);

	LED_set(led, initialStatus);

	return;
}//eof

/**
 * \brief toggles an LED.
 */
void LED_toggle(struct LED* led){
	LED_set(led, !(led->status));
	return;
}//eof

/**
 * \brief switches an LED on or off.
 * \par led - pointer to the LED structure
 * \par state - 1: switch LED on, 0: switch LED off
 */

void LED_set(struct LED* led, uint8_t state)
{
	if (state==1)
	{
		GPIO_SetBits(led->GPIOPort, led->GPIOPin);
		led->status = 1;
	}
	else
	{
		GPIO_ResetBits(led->GPIOPort, led->GPIOPin);
		led->status = 0;
	}
return;
}//eof
