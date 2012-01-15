 /*************************************
 * stm32_devices.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_devices.h"
#include "../inc/stm32_devices_ms5534c.h"
 /*Definitions******************************/

 /*Functions********************************/
/*******pressure sensor MS5534C*************/
void Device_MS5534C_Init()
{
return;
}

/***********Display DOGM 128x64************/
void Device_DogDisplayInit()
{

	Device_DogDisplay_Reset();						//reset display
	SPI1_SetReset_CS(0);							//set CS to low
	Device_DogDisplay_SetReset_A0(0);				//set AO to low: command mode

	SPI1_SendByte_Display(0x40);					// Display start line=0
	SPI1_SendByte_Display(0xA1);					// ADC reverse, 6 o'clock viewing direction
	SPI1_SendByte_Display(0xC0);					//COM0-COM63 in normal scan mode
	SPI1_SendByte_Display(0xA6);					//display not mirrored
	SPI1_SendByte_Display(0xA2);					//set bias 1/9 (duty 1/65)
	SPI1_SendByte_Display(0x2F);					//booster, regulator, follower on
	SPI1_SendByte_Display(0xF8);					//set internal booster to 4x
	SPI1_SendByte_Display(0x00);					//set internal booster to 4x
	SPI1_SendByte_Display(0x27);					//contrast set
	SPI1_SendByte_Display(0x81);					//contrast set
	SPI1_SendByte_Display(0x16);					//contrast set
	SPI1_SendByte_Display(0xAC);					//?
	SPI1_SendByte_Display(0x00);					//?
	SPI1_SendByte_Display(0xAF);					//?

	SPI1_SetReset_CS(1);				//set CS to high level


//write the letter "R", format 5x8
	SPI1_SetReset_CS(0);				//set CS to low
	Device_DogDisplay_SetReset_A0(1);				//set A0 to high - write display data mode

		SPI1_SendByte_Display(0x00);					//
		SPI1_SendByte_Display(0x7F);					//
		SPI1_SendByte_Display(0x09);					//
		SPI1_SendByte_Display(0x09);					//
		SPI1_SendByte_Display(0x76);					//
		SPI1_SetReset_CS(1);		//set CS to high level

return;
}

void Device_DogDisplay_SetReset_A0(u8 state)
{
	if (state==1)
		{
		GPIOA_BSRR |= BIT11;				//set GPIOA.11 to 1
		}
	else
		{
		GPIOA_BRR |= BIT11;			//reset GPIOA.11 to 0
		}
return;
}

void Device_DogDisplay_Reset()
{
			GPIOA_BSRR |= BIT12;			//set GPIOA.12 to 1
			wait_millisec(1);
			GPIOA_BRR |= BIT12;				//reset GPIOA.12 to 0 - reset pulse
			wait_millisec(10);
			GPIOA_BSRR |= BIT12;			//set GPIOA.12 to 1
			wait_millisec(1);					//give time to complete internal reset process

	return;
}
