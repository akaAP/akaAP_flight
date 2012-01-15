/* Includes ------------------------------------------------------------------*/
#include "../inc/main.h"

void toggleLED();

Devices* devices;
Modules* modules;

int main(void)
{
	//Initialize the STM32
	Init();
	// create device class, holding external devices as ADCs, XBee, but also PWM drivers for servos.
	// To use any kind of hardware, just use this global object.
	devices = new Devices();
	testloop();

	//endless loop to prevent return from main()
	while(1){
	}

	return 0;
}//eof

void toggleLED(){
	static uint8_t state = 0;
		if (state==1)
		{
			GPIOC->BSRR |= GPIO_Pin_12;
			state = 0;
		}
		else
		{
			GPIOC->BRR |= GPIO_Pin_12;
			state = 1;
		}
}//eof
