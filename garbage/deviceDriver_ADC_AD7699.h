/*
 * deviceDriver_AD7699.h
 *
 * Author: janjan
 * @brief short description.
 * Long description.	
 */

#ifndef DEVICEDRIVER_AD7699_H_
#define DEVICEDRIVER_AD7699_H_

#include "../../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../inc/serviceFunctions.h"

struct AD7699{
		SPI_TypeDef*  spiPort;				//which SPI port (SPI1, SPI2,...) uses the AD7699 to communicate?
		GPIO_TypeDef* gpioPortDIN;			//to which GPIO port the AD7699 SPI data out pin is connected?
		uint16_t	  gpioPinDIN;			//and to which pin?
		GPIO_TypeDef* gpioPortDOUT;			//to which GPIO port the AD7699 SPI data in pin is connected?
		uint16_t	  gpioPinDOUT;			//and to which pin?
		GPIO_TypeDef* gpioPortSCLK;			//to which GPIO port the AD7699 SPI SCLK pin is connected?
		uint16_t	  gpioPinSCLK;			//and to which pin?
		GPIO_TypeDef* gpioPortCNV;			//to which GPIO port the AD7699 CNV pin is connected?
		uint16_t	  gpioPinCNV;			//and to which pin?
		uint16_t 	  cfg;					//buffer structure for writing to the Ad7699's CFG register
};

//Bitmasks for the ADC's 14-Bit configuration register CFG
#define CFG_CFG_KEEPSETTINGS 			( ( (u16) 0b0)<<10)
#define CFG_CFG_OVERWRITESETTINGS		( ( (u16) 0b1)<<13)

#define CFG_INCC_BIPOLARDIFFPAIRS		( ( (u16) 0b000)<<10)
#define CFG_INCC_BIPOLARREFCOM			( ( (u16) 0b010)<<10)
#define CFG_INCC_TEMPSENS				( ( (u16) 0b011)<<10)
#define CFG_INCC_UNIPOLARDIFFPAIRS		( ( (u16) 0b100)<<10)
#define CFG_INCC_UNIPOLARREFCOM			( ( (u16) 0b110)<<10)
#define CFG_INCC_UNIPOLARREFGND			( ( (u16) 0b111)<<10)

#define CFG_INx_CHANNEL0				( ( (u16) 0)<<7)
#define CFG_INx_CHANNEL1				( ( (u16) 1)<<7)
#define CFG_INx_CHANNEL2				( ( (u16) 2)<<7)
#define CFG_INx_CHANNEL3				( ( (u16) 3)<<7)
#define CFG_INx_CHANNEL4				( ( (u16) 4)<<7)
#define CFG_INx_CHANNEL5				( ( (u16) 5)<<7)
#define CFG_INx_CHANNEL6				( ( (u16) 6)<<7)
#define CFG_INx_CHANNEL7				( ( (u16) 7)<<7)

#define CFG_BW_AFOURTH						( ( (u16) 0b0)<<6)
#define CFG_BW_FULL							( ( (u16) 0b1)<<6)

#define CFG_REF_INTERNALREF					( ( (u16) 0b001)<<3)
#define CFG_REF_EXTERNALREF_TEMPEN			( ( (u16) 0b010)<<3)
#define CFG_REF_EXTERNALREF_TEMPEN_BUFFER  	( ( (u16) 0b011)<<3)
#define CFG_REF_EXTERNALREF_TEMPDIS			( ( (u16) 0b110)<<3)
#define CFG_REF_EXTERNALREF_TEMPDIS_BUFFER	( ( (u16) 0b111)<<3 )

#define CFG_SEQ_DISABLED					( ( (u16)0b00)<<1 )
#define CFG_SEQ_UPDATE_CONF_DURING_SEQ		( ( (u16)0b01)<<1 )
#define CFG_SEQ_SCAN_IN0TOIN7_THEN_TEMP		( ( (u16)0b10)<<1 )
#define CFG_SEQ__SCAN_IN0TOIN7				( ( (u16)0b11)<<1 )

#define CFG_RB_READBACK						( (u16) 0b0)
#define CFG_RB_DONOTREADBACK				( (u16) 0b1)

/*Timing constants in [ns]********************************/
#define T_Data 1200
#define T_CONV 1600
#define T_ACQU 400

/*******Function Declarations*****************************/
void AD7699_Init(struct AD7699* ad,
				 GPIO_TypeDef* gpioPortDIN,
				 uint16_t gpioPinDIN,
				 GPIO_TypeDef* gpioPortDOUT,
				 uint16_t gpioPinDOUT,
				 GPIO_TypeDef* gpioPortSCLK,
				 uint16_t gpioPinSCLK,
				 GPIO_TypeDef* gpioPortCNV,
				 uint16_t gpioPinCNV,
				 SPI_TypeDef* spiPeripheralToUse);
u32 AD7699_getChannelVoltage(struct AD7699* ad, u8 channel);
void AD7699_getRawBytes(struct AD7699* ad, uint8_t channel, uint8_t* rawBytes);
uint16_t AD7699_pollOnce(struct AD7699* ad, uint8_t channel);
void AD7699_getChannelVoltages(struct AD7699* ad, u32* values);
void setChannelInCFG(struct AD7699* ad, uint8_t channel);
void setCNVPin(struct AD7699* ad, uint8_t state);




#endif /* DEVICEDRIVER_AD7699_H_ */
