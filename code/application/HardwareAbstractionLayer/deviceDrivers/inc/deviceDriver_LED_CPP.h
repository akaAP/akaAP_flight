/*
 * deviceDriver_LED.h
 *
 * \file deviceDriver_LED.h
 * \brief This driver provides functions to control a LED
 * \author: jan bolting
 */
#ifndef DEVICEDRIVER_LED_H_
#define DEVICEDRIVER_LED_H_


#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../inc/serviceFunctions.h"

class LED
{
	public:
		LED();
		LED(GPIO_TypeDef* port, uint16_t pin, uint8_t initialStatus);							//constructor
		~LED(void);									//destructor
		void toggle();
		void set(uint8_t newState);
		static const uint8_t state_ON = 1;
		static const uint8_t state_OFF = 0;
	private:
		uint8_t status;						//indicates if the LED currently is on or off
		GPIO_TypeDef* GPIOPort;				//which GPIO port is the LED connected to?
		uint16_t GPIOPin;					//and to which pin?
};//eoc


/*
void LED_Init(struct LED* led, GPIO_TypeDef* port, uint16_t pin, uint8_t initialStatus);
void LED_toggle(struct LED* led);
void LED_set(struct LED* led, uint8_t state);
*/

#endif /* DEVICEDRIVER_LED_H_ */
