 /*************************************
 * stm32_spi.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_spi.h"

 /*Definitions******************************/

 /*Functions********************************/
/**************SPI1*************************/
void SPI1_Init()							//configure for MS5534C sensor
{
	SPI1_ClkInit();							//enable SPI1 clock

	SPI1_I2SCFGR = 0;						//set to default; enable SPI mode
	SPI1_CR1 = 0;							//set to default
	SPI1_CR2 = 0;							//set to default

	SPI1_CR1 |= (BIT5|BIT4|BIT3);			//set baudrate to fpclk/256
	//SPI_CR1 |= BIT11;						//1: 16-bit data frames; 0: 8-bit data frames
	SPI1_CR1 |= BIT0;						//data capture on second SCLK transition; CPHA=1
	//SPI1_CR1 |= BIT1;						//CPOL=1: SPI1_SCLK = high when idle <-> CPOL=0 low when idle
	SPI1_CR1 |= BIT9;						//enable NSS software mode
	SPI1_CR1 |= BIT8;						//set SSI bit
	SPI1_CR1 |=  BIT2;						//select Master mode
	//SPI1_CR1 |= BIT7;						//LSB transmitted first
	SPI1_CR1 |= BIT6;						//enable SPI1
	return;
}

void SPI1_SetTransEdge(u8 a)				//a=1: capture/transmission on 1st transition; a=2: on 2nd transition
{
	if(a=1){
		SPI1_CR1 &= ~BIT0;					//data capture on first SCLK transition; CPHA=0
	}
	if(a=2){
			SPI1_CR1 |= BIT0;				//data capture on second SCLK transition; CPHA=1
		}

return;
}

void SPI1_SetReset_CS(u8 state)
{
	if (state==1)
			{
			GPIOA_BSRR |= BIT4;				//set GPIOA.4 to 1
			}
	else
			{
			GPIOA_BRR |= BIT4;			//reset GPIOA.4 to 0
			}
	return;
}

void SPI1_SendByte(u8 databyte)
{
	SPI1_DR = (u16)databyte;
	while( !((SPI1_SR&BIT1)>0)){}				//wait for SPI1 TX buffer to be empty
	//wait_microsec(1);
	return;
}

void SPI1_SendByte_Display(u8 databyte)
{
	SPI1_DR = (u16)databyte;
	while( !((SPI1_SR&BIT1)>0)){}				//wait for SPI1 TX buffer to be empty
	//wait_microsec(1);
	return;
}
