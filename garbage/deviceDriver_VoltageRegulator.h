/*
 * deviceDriver_LT1461.h
 *
 * Author: janjan
 * @brief short description.
 * Long description.	
 */

#ifndef DEVICEDRIVER_VOLTAGEREGULATOR_H_
#define DEVICEDRIVER_VOLTAGEREGULATOR_H_

#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../inc/serviceFunctions.h"

struct VoltageRegulator{
	uint8_t status;						//indicates if the VoltageRegulator currently is on or off
	GPIO_TypeDef* GPIOPort;				//which GPIO port is the LT1461's ENABLE pin connected to?
	uint16_t GPIOPin;					//and to which pin?
};

/*******Function Declarations*****************************/
void VoltageRegulator_Init(struct VoltageRegulator* lt, GPIO_TypeDef* port, uint16_t pin, uint8_t initialStatus);
void VoltageRegulator_switch(struct VoltageRegulator* lt, uint8_t state);

#endif /* DEVICEDRIVER_VOLTAGEREGULATOR_H_ */
