 /*************************************
 * stm32_init_peripherals.h
 * author: jan
 * last modifications:
 *
 * description:
 **************************************/

#ifndef STM32_INIT_PERIPHERALS_H_
#define STM32_INIT_PERIPHERALS_H_

/*included header files***************/
#include "../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"
#include "../HardwareAbstractionLayer/inc/modules.h"
#include "../HardwareAbstractionLayer/inc/serviceFunctions.h"

/*function prototypes*****************/

void Init(void);
void Init_externalDevices();

/* Private function prototypes -----------------------------------------------*/
void PeripheralClockConfiguration(void);

void GPIO_Configuration(void);

void USART_Configuration(void);
void NVIC_Configuration(void);


#endif /* STM32_INIT_PERIPHERALS_H_ */
