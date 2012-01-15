/*
 * deviceDriver_LT1461.c
 *
 * Author: janjan
 * @brief Device Driver for the voltage reference LT1461 by National Semiconductors.
 * This file holds functions you need to control the LT1461 e.g. switch it on or off
 */

#include "../inc/deviceDriver_VoltageRegulator.h"

/**
 * @brief Initializes a VoltageRegulator.
 * The parameter 'initialState' (0 or 1) determines if the regulator is supposed to be switched on.
 */
void VoltageRegulator_Init(struct VoltageRegulator* lt, GPIO_TypeDef* enablePort, uint16_t enablePin, uint8_t initialState){
	lt->status = 0;
	lt->GPIOPort = enablePort;
	lt->GPIOPin = enablePin;

	service_enablePeripheralClock((uint32_t)lt->GPIOPort);
	GPIO_InitTypeDef GPIO_InitStructure;
	// Configure GPIO for ENABLE pin as Output push-pull
	GPIO_InitStructure.GPIO_Pin = lt->GPIOPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(lt->GPIOPort, &GPIO_InitStructure);

	VoltageRegulator_switch(lt, initialState);
	return;
}//eof

/**
 * @brief switches the regulator ON or OFF depending on the parameter 'state' (1=on, 0=off).
 */
void VoltageRegulator_switch(struct VoltageRegulator* lt, uint8_t state){
	if (state==1)
	{
		GPIO_SetBits(lt->GPIOPort, lt->GPIOPin);
		lt->status = 1;
	}
	else if(state == 0)
	{
		GPIO_ResetBits(lt->GPIOPort, lt->GPIOPin);
		lt->status = 0;
	}
	return;
}//eof

/*Functions*************************************/
