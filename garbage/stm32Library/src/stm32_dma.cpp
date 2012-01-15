 /*************************************
 * stm32f103rbt6_dma.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_dma.h"
#include "../inc/stm32_usart.h"
#include "../inc/stm32_rcc.h"
 /*Definitions******************************/

 /*Functions********************************/
void DMA1_Init()
{
	//DMA1_ClkInit();
	//DMA1_Init_Ch1();
	//DMA1_Init_Ch7();
	//DMA1_Init_Ch4();
	return;
}

void DMA1_Init_Ch1(void)
{
	/*Configure DMA1 channel 1 for ADC1*/
	DMA1_CPAR1 = (u32)(ADC1_BASE + 0x4C);						//set the ADC1 Data register as source for DMA transfers
	DMA1_CCR1 = 0;												//set to default
	DMA1_CCR1 |= BIT13;											//set channel priority bits to 10="high"
	DMA1_CCR1 |= BIT10;											//set Memory Size to 16 bit
	DMA1_CCR1 |= BIT8;											//set Peripheral memory size to 16 bit
	DMA1_CCR1 |= BIT7;											//enable memory increment mode
	DMA1_CCR1 |= BIT5;											//enable circular mode
	//DMA1_CCR1 |= BIT4;										//data transfer direction: read from memory
	//DMA1_CNDTR1 = 5;											//number of data to be transmitted; afterwards, DMA1_CNDTR7 is reloaded with this value if circular mode is enabled
	//DMA1_CCR1 |= BIT0;										//enable channel
return;
}

void DMA1_Ch1_SetTargetAddress(u32 address, u16 nod)
{
	DMA1_CCR1 &= ~BIT0;											//disable channel: reset bit 0

	DMA1_CMAR1 = address;										//set memory address to where the DMA will transfer data from the ADC1_DATA register
	DMA1_CNDTR1 = nod;											//set number of data to transfer by DMA

	DMA1_CCR1 |= BIT0;											//enable channel

}

void DMA1_Init_Ch7(void)
{
	/*Configure DMA1 channel 7 for USART2 TX*/
	DMA1_CPAR7 = (u32)(USART2_BASE + 0x04);						//set the USART2 Data register as target for DMA transfers

	DMA1_CCR7 = 0;												//set to default
	//DMA1_CCR7 |= BIT12;										//set channel priority bits to 01="medium"
	//DMA1_CCR7 |= BIT10;										//set Memory Size to 16 bit
	//DMA1_CCR7 |= BIT9;										//set Peripheral memory size to 32 bit
	DMA1_CCR7 |= BIT7;											//enable memory increment mode
	//DMA1_CCR7 |= BIT5;										//enable circular mode
	DMA1_CCR7 |= BIT4;											//data transfer direction: read from memory
	//DMA1_CNDTR7 = 8;											//number of data to be transmitted; afterwards, DMA1_CNDTR7 is reloaded with this value if circular mode is enabled
	//DMA1_CCR7 |= BIT0;										//enable channel
return;
}


void DMA1_Ch7_SetSourceAddress(u32 address, u16 nod)
{
	DMA1_CCR7 &= ~BIT0;											//disable channel: reset bit 0

	DMA1_CMAR7 = address;										//set memory adress from where the DMA will transfer data to the USART2 TX data register
	DMA1_CNDTR7 = nod;											//set number of data to transfer by DMA

	DMA1_CCR7 |= BIT0;											//enable channel

}

void DMA1_Init_Ch4(void)
{
	/*Configure DMA1 channel 4 for USART1 TX*/
	DMA1_CPAR4 = (u32)(USART1_BASE + 0x04);						//set the USART1Data register as target for DMA transfers

	DMA1_CCR4 = 0;												//set to default
	//DMA1_CCR4 |= BIT12;										//set channel priority bits to 01="medium"
	//DMA1_CCR4 |= BIT10;										//set Memory Size to 16 bit
	//DMA1_CCR4 |= BIT9;										//set Peripheral memory size to 32 bit
	DMA1_CCR4 |= BIT7;											//enable memory increment mode
	//DMA1_CCR4 |= BIT5;										//enable circular mode
	DMA1_CCR4 |= BIT4;											//data transfer direction: read from memory
	//DMA1_CNDTR4 = 8;											//number of data to be transmitted; afterwards, DMA1_CNDTR7 is reloaded with this value if circular mode is enabled
	//DMA1_CCR4 |= BIT0;										//enable channel
return;
}


void DMA1_Ch4_SetSourceAddress(u32 address, u16 nod)
{
	DMA1_CCR4 &= ~BIT0;											//disable channel: reset bit 0

	DMA1_CMAR4 = address;										//set memory adress from where the DMA will transfer data to the USART1 TX data register
	DMA1_CNDTR4 = nod;											//set number of data to transfer by DMA

	DMA1_CCR4 |= BIT0;											//enable channel

}
