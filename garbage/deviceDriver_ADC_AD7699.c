/*
 * \file deviceDriver_AD7699.c
 *
 * \author janjan
 * \brief This file holds functions needed to use the AD7699 ADC by Analog Devices.
 * These functions may be used to initialize the ADC, configure it and to get measured
 * values
 */

//Inclusions
#include "../inc/deviceDriver_ADC_AD7699.h"

#define SET_CNV_TO_1 (ad->gpioPortCNV->BSRR |= ad->gpioPinCNV)
#define SET_CNV_TO_0 (ad->gpioPortCNV->BRR |= ad->gpioPinCNV)

//Functions
/**
* \brief use this function to initialize and configure the ADC. It writes to the
* ADC's configuration register and makes the device ready for conversions.
*/
void AD7699_Init(struct AD7699* ad,
		 GPIO_TypeDef* gpioPortDIN,
		 uint16_t gpioPinDIN,
		 GPIO_TypeDef* gpioPortDOUT,
		 uint16_t gpioPinDOUT,
		 GPIO_TypeDef* gpioPortSCLK,
		 uint16_t gpioPinSCLK,
		 GPIO_TypeDef* gpioPortCNV,
		 uint16_t gpioPinCNV,
		 SPI_TypeDef* spiPeripheralToUse){

	ad->spiPort = spiPeripheralToUse;
	ad->gpioPortDIN = gpioPortDIN;
	ad->gpioPinDIN = gpioPinDIN;
	ad->gpioPortDOUT = gpioPortDOUT;
	ad->gpioPinDOUT = gpioPinDOUT;
	ad->gpioPortSCLK = gpioPortSCLK;
	ad->gpioPinSCLK = gpioPinSCLK;
	ad->gpioPortCNV = gpioPortCNV;
	ad->gpioPinCNV = gpioPinCNV;

	ad->cfg = 0;
	//define what to write to the ADC's 14-Bit configuration register CFG
	ad->cfg |= CFG_CFG_OVERWRITESETTINGS;
	ad->cfg |= CFG_INCC_UNIPOLARREFGND;
	ad->cfg |= CFG_INx_CHANNEL0;
	ad->cfg |= CFG_BW_FULL;
	ad->cfg	|= CFG_REF_EXTERNALREF_TEMPDIS;
	ad->cfg	|= CFG_SEQ_DISABLED;
	ad->cfg	|= CFG_RB_DONOTREADBACK;

	//enable clocks of all involved peripherals
	service_enablePeripheralClock((uint32_t)ad->spiPort);
	service_enablePeripheralClock((uint32_t)ad->gpioPortDOUT);
	service_enablePeripheralClock((uint32_t)ad->gpioPortDIN);
	service_enablePeripheralClock((uint32_t)ad->gpioPortCNV);
	service_enablePeripheralClock((uint32_t)ad->gpioPortSCLK);

	//configure GPIO pins
	 GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	/* Configure SCK and MOSI pins as Alternate Function Push Pull */
	//SCLK:
	GPIO_InitStructure.GPIO_Pin = ad->gpioPinSCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ad->gpioPortSCLK, &GPIO_InitStructure);
	//MOSI:
	GPIO_InitStructure.GPIO_Pin = ad->gpioPinDIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ad->gpioPortDIN, &GPIO_InitStructure);

	//Configure CNV pin as general purpose push-pull
	GPIO_InitStructure.GPIO_Pin = ad->gpioPinCNV;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(ad->gpioPortCNV, &GPIO_InitStructure);

	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Pin = ad->gpioPinDOUT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(ad->gpioPortDOUT, &GPIO_InitStructure);

	/* SPI configuration ------------------------------------------------------*/
	SPI_InitTypeDef  SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				// clock SCLK idle state is low
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//read SPI bit state on the first edge of SCLK
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(ad->spiPort, &SPI_InitStructure);
	SPI_Cmd(ad->spiPort, ENABLE);

}//eof

/**
 * \brief Configures the SPI peripheral as needed by the AD766.
 */
void AD7699_configureSPI(struct AD7699* ad){

	return;
}//eof


/**
 * \brief Puts the two bytes the ADC returns for the given input channel in in the given array.
 * Low byte -> array[0];
*/
void AD7699_getRawBytes(struct AD7699* ad, uint8_t channel, uint8_t* rawBytes){
	setChannelInCFG(ad, channel);
	uint16_t received16Bit = 0;

	//start 2 dummy conversions and one real conversion since the first 2 conversions are not reliable (see datasheet AD7699)
	for(u8 i=0; i<3; i++){
		received16Bit = AD7699_pollOnce(ad, channel);
	}
	rawBytes[0] = (uint8_t)(received16Bit);		//lower byte
	rawBytes[1] = (uint8_t)(received16Bit>>8);			//higher byte
	return;
}//eof


/**
 * \brief polls the data for one channel once.
*/
uint16_t AD7699_pollOnce(struct AD7699* ad, uint8_t channel){
	setChannelInCFG(ad, channel);
	uint16_t received16Bit = 0;

		//the variable a is used to generate very short delays by incrementing it
		uint32_t a = 0;
		//start conversion by a rising edge of CNV
		SET_CNV_TO_1;
		//now the conversion runs
		a++;
		SET_CNV_TO_0;
		a++;
		a++;
		a++;
		//set CNV to high again to avoid generation of the busy indicator
		SET_CNV_TO_1;
		//create a delay
		service_waitNanosec(3000);

		//conversion should be done by now (max. 1.6µs)
		//send the cfg register content by spi; the conversion result is received simultaneously
		//Note: the cfg register determines the ADC behaviour for the NEXT conversion, not the current one
		//wait until the SPI_DR register is free by checking the TXE flag
		while((ad->spiPort->SR && BIT1) == 0){
			a++;		//to prevent the compiler from optimizing away this loop
		}
		uint16_t cfgShifted = (ad->cfg)<<2;
		//set CNV pin back to low to indicate that the data transfer is about to start
		SET_CNV_TO_0;
		ad->spiPort->DR = (cfgShifted);
		service_waitNanosec(18000);
		//wait until the SPI_DR register has received data by checking the RXE flag
		while((ad->spiPort->SR && BIT0) == 0){
					a++;		//to prevent the compiler from optimizing away this loop
		}
		received16Bit = ad->spiPort->DR;
	return received16Bit;
}//eof


/**
 * \brief Returns the measured voltage of the given input channel in [µV].
 * TODO doesn't work yet.
*/
uint32_t AD7699_getChannelVoltage(struct AD7699* ad, u8 channel){
	static uint32_t result = 0;
	uint8_t rawBytes[2] = {0};
	AD7699_getRawBytes(ad, channel, rawBytes);
	return result;
}//eof

/**
 * \brief Writes the measured voltages [µV] of ADC channel IN0 - IN7 to the array
 * given as a parameter.
 * TODO doesn't work yet.
 */
void AD7699_getChannelVoltages(struct AD7699* ad, u32* values){
	//how it works: start a complete sequence of conversions of channel 0 to channel 7
	//set channel to convert in a CFG register
	setChannelInCFG(ad, 0);
}//eof

/**
 * \brief Sets the channel in the given AD7699 structure's cfg register.
 *
 */
void setChannelInCFG(struct AD7699* ad, uint8_t channel){
   //clear the relevant bits
   ad->cfg &= (uint16_t)~(BIT7|BIT8|BIT9);
   ad->cfg |= (channel << 7);
   return;
}//eof

/**
 * \brief Sets the CNV pin voltage level.
 */
void setCNVPin(struct AD7699* ad, uint8_t state){
	if(state == 1)
		{
		ad->gpioPortCNV->BSRR |= ad->gpioPinCNV;				//set CNV pin to 1
		}
	else if(state == 0)
		{
		ad->gpioPortCNV->BRR |= ad->gpioPinCNV;					//reset CNV pin to 0
		}
	return;
}//eof


