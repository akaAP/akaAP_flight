 /*************************************
 * stm32rbt6_adc.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_adc.h"
 /*Definitions******************************/

 /*Functions********************************/
/*ADC1*/
void ADC1_Init(void)							//initializes, starts and configures ADC1
{
	ADC1_ClkInit();								//start ADC1 clock, reset and restart ADC1
	ADC1_CR2 |= BIT0;							//set ADON bit; activate ADC1
	wait(1);									//ADC has to run a few cycles before calibration starts
	ADC1_CR2 |= BIT2;							//set CAL bit; start calibration of ADC1
	//wait(1);									//give ADC time to calibrate
	while((ADC1_CR2 & BIT2)>0){}				//wait until CAL bit has been reset to 0 by hardware after calibration has passed

	/*configure channels*/
	ADC1_SMPR1 |= 0x00ffffff;						//set sample time to 239,5 cycles for ADC1 channels 10 to 17
//	ADC1_SMPR2 |= 0;								//set to default

	//ADC1_CR2 &= ~BIT0;							//reset ADON bit; disable ADC1

return;
}

u16 ADC1_Read_Channel_14(void)					//configures the ADC1 to do a single conversion and returns the voltage at ADC1 input 14
{
u16 voltage = 0;
ADC1_SQR3 |= (BIT1 | BIT2 | BIT3);				//select channel 14 as first one to convert in regular conversion
//ADC1_CR2 |= BIT20;							//enable external trigger mode
//ADC1_CR2 |= 0x000E0000;						//select SWSTART bit as trigger for conversion of regular group of ADC channels
//ADC1_CR2 |= BIT22;							//start single conversion by setting SWSTART bit
ADC1_CR2 |= BIT0;								//start single conversion by setting ADON bit
//ADC1_CR1 |= BIT8;								//activate scan mode
while (!(ADC1_SR & BIT1)){}					    // wait until END OF CONVERSION bit is set to 1 by hardware
voltage = ADC1_DR;								//ADC1 Data Register contains the result of the conversion
//voltage = 0x55CC;
return voltage;
}

void ADC1_Start_ConvGroup_1(u32 buffer_startaddress, u8 adc1_buffer_length)					//starts continuous conversion of a group of regular channels; results are stored in buffer by DMA
{
	//ADC1_SQR3 |= (BIT1 | BIT2 | BIT3);							//select channel 14 as first one to convert in regular conversion
	ADC1_SQR3 |= (BIT1 | BIT3);										//set channel 10 as first one to convert in regular conversion
	//ADC1_SQR3 |= (BIT2 | BIT3);									//select channel 12 as first one to convert in regular conversion
	ADC1_SQR3 |= (BIT5 | BIT6 | BIT8);								//set channel 11 as second one to convert
	ADC1_SQR3 |= (BIT12 | BIT13);									//set channel 12 as third one to convert
	ADC1_SQR3 |= (BIT15 | BIT17 | BIT18);							//set channel 13 as fourth one to convert
	ADC1_SQR3 |= (BIT21 | BIT22 | BIT23);							//set channel 14 as fifth one to convert
	ADC1_SQR1 |= BIT22;									    		//set length of group of channels to convert to 5
	DMA1_Ch1_SetTargetAddress(buffer_startaddress, (u16) adc1_buffer_length);			//give start address of ADC1 conversion results buffer to DMA1
	//ADC1_SR &= ~BIT1;												//clear END OF CONVERSION bit to avoid DMA request
	ADC1_CR2 |= BIT8;												//enable DMA mode
	ADC1_CR2 |= BIT1;												//enable continuous mode
	ADC1_CR1 |= BIT8;												//enable scan mode
	ADC1_CR2 |= BIT0;												//start conversion by setting ADON bit
return;
}


void ADC1_Filter_Average(u16 *adc_buffer, u16 *adc_buffer_filtered,u8 nbr_of_channels, u16 adc_buffer_depth )
{
	u32 sum=0;

	for(u16 p=0; p<nbr_of_channels; p++)
	{
	for(u16 i=0; i<adc_buffer_depth; i++)
	{
		sum+=adc_buffer[i*nbr_of_channels + p];
	}
	adc_buffer_filtered[p]=sum/adc_buffer_depth;
	sum=0;
	}
return;
}
