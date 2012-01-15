/*
 * \file deviceDriver_spektrumSatellite.h
 * \brief This device driver provides functions to receive serial data from
 * 			a Spektrum satellite / remote receiver.
 * \author Jan
 */

#ifndef DEVICEDRIVER_SPEKTRUMSATELLITE_H_
#define DEVICEDRIVER_SPEKTRUMSATELLITE_H_

//Inclusions
#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"


class SpektrumSatellite{
public:
	SpektrumSatellite(USART_TypeDef* usartToUse);
	~SpektrumSatellite();
	void getRcChannels(int16_t* target);
	void getRawData(uint8_t* target);
	uint32_t getTimeOfLastValidFrame();
	void usart_IRQHandler();
	static SpektrumSatellite* satelliteUsingUSART1;
	static SpektrumSatellite* satelliteUsingUSART2;
	static SpektrumSatellite* satelliteUsingUSART3;
	static const uint8_t numberOfChannels = 7;
private:
	void calculate();												// Turns raw data bytes into channel values.
	void setUp(USART_InitTypeDef usartInitStruct);					// This method configures the peripherals used by the driver.
	USART_TypeDef* usart;											// The USART chip peripheral the driver uses for communication.
	GPIO_TypeDef* RXPin_GPIOPort;									//which GPIO port is the USART RX line connected to?
	uint16_t RXPin;													//and to which pin?
	static const uint8_t bufferSize = 18;
	volatile uint8_t inBuffer[SpektrumSatellite::bufferSize];			// Received bytes are stored in this buffer array.

	volatile int16_t channels[SpektrumSatellite::numberOfChannels];		// Array holds the current received RC channel values [-1000, +1000]
	volatile uint8_t numberOfFramebytesReceived;							// Indeicates how many bytes of a frame have been received.
	volatile uint32_t timeOfLastValidFrame;								// Indicates when the last valid data frame has been
																		// received from the Spektrum remote receiver
	// Interrupts
	uint8_t USART_global_interrupt;
	// Fields used for frame synchronization
																	// to the receivers data frames.
	volatile uint32_t timeOfLastFrame;								// The time when the last byte of the last frame has been received
	volatile bool timeOfFirstByteStored;							// Indicates whether the reception time of
																	// the last frame has been stored yet.
};

extern "C" void USART3_IRQHandler_cute();
extern "C" void USART2_IRQHandler_cute();
extern "C" void USART1_IRQHandler_cute();


#endif /* DEVICEDRIVER_SPEKTRUMSATELLITE_H_ */
