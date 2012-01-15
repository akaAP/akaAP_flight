 /*************************************
 * stm32_adc.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_ADC_H_
#define STM32_ADC_H_

//#include "../../CMSIS/Core/CM3/stm32f10x.h"

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_serv.h"
#include "../inc/stm32_rcc.h"
#include "../inc/stm32_dma.h"

 /*Definitions******************************/
/*Registers*/
#define ADC1_SR						(*((u32 *) (ADC1_BASE+0x00)))			//ADC1 status register
#define ADC1_CR1					(*((u32 *) (ADC1_BASE+0x04)))			//ADC1 control register 1
#define ADC1_CR2					(*((u32 *) (ADC1_BASE+0x08)))			//ADC1 control register 2
#define ADC1_SMPR1					(*((u32 *) (ADC1_BASE+0x0C)))			//ADC1 sample time register 1
#define ADC1_SMPR2					(*((u32 *) (ADC1_BASE+0x10)))			//ADC1 sample time register 2
#define ADC1_JOFR1					(*((u32 *) (ADC1_BASE+0x14)))			//ADC1 injected channel data offset register 1
#define ADC1_JOFR2					(*((u32 *) (ADC1_BASE+0x18)))			//ADC1 injected channel data offset register 2
#define ADC1_JOFR3					(*((u32 *) (ADC1_BASE+0x1C)))			//ADC1 injected channel data offset register 3
#define ADC1_JOFR4					(*((u32 *) (ADC1_BASE+0x20)))			//ADC1 injected channel data offset register 4
#define ADC1_HTR					(*((u32 *) (ADC1_BASE+0x24)))			//ADC1 watchdog high threshold register
#define ADC1_LTR					(*((u32 *) (ADC1_BASE+0x28)))			//ADC1 watchdog low threshold register
#define ADC1_SQR1					(*((u32 *) (ADC1_BASE+0x2C)))			//ADC1 regular sequence register 1
#define ADC1_SQR2					(*((u32 *) (ADC1_BASE+0x30)))			//ADC1 regular sequence register 2
#define ADC1_SQR3					(*((u32 *) (ADC1_BASE+0x34)))			//ADC1 regular sequence register 3
#define ADC1_JSQR					(*((u32 *) (ADC1_BASE+0x38)))			//ADC1 injected sequence register
#define ADC1_JDR1					(*((u32 *) (ADC1_BASE+0x3C)))			//ADC1 injected data register 1
#define ADC1_JDR2					(*((u32 *) (ADC1_BASE+0x40)))			//ADC1 injected data register 2
#define ADC1_JDR3					(*((u32 *) (ADC1_BASE+0x44)))			//ADC1 injected data register 3
#define ADC1_JDR4					(*((u32 *) (ADC1_BASE+0x48)))			//ADC1 injected data register 4
#define ADC1_DR						(*((u32 *) (ADC1_BASE+0x4C)))			//ADC1 regular data register

#define ADC2_SR						(*((u32 *) (ADC2_BASE+0x00)))			//ADC2 status register
#define ADC2_CR1					(*((u32 *) (ADC2_BASE+0x04)))			//ADC2 control register 1
#define ADC2_CR2					(*((u32 *) (ADC2_BASE+0x08)))			//ADC2 control register 2
#define ADC2_SMPR1					(*((u32 *) (ADC2_BASE+0x0C)))			//ADC2 sample time register 1
#define ADC2_SMPR2					(*((u32 *) (ADC2_BASE+0x10)))			//ADC2 sample time register 2
#define ADC2_JOFR1					(*((u32 *) (ADC2_BASE+0x14)))			//ADC2 injected channel data offset register 1
#define ADC2_JOFR2					(*((u32 *) (ADC2_BASE+0x18)))			//ADC2 injected channel data offset register 2
#define ADC2_JOFR3					(*((u32 *) (ADC2_BASE+0x1C)))			//ADC2 injected channel data offset register 3
#define ADC2_JOFR4					(*((u32 *) (ADC2_BASE+0x20)))			//ADC2 injected channel data offset register 4
#define ADC2_HTR					(*((u32 *) (ADC2_BASE+0x24)))			//ADC2 watchdog high threshold register
#define ADC2_LTR					(*((u32 *) (ADC2_BASE+0x28)))			//ADC2 watchdog low threshold register
#define ADC2_SQR1					(*((u32 *) (ADC2_BASE+0x2C)))			//ADC2 regular sequence register 1
#define ADC2_SQR2					(*((u32 *) (ADC2_BASE+0x30)))			//ADC2 regular sequence register 2
#define ADC2_SQR3					(*((u32 *) (ADC2_BASE+0x34)))			//ADC2 regular sequence register 3
#define ADC2_JSQR					(*((u32 *) (ADC2_BASE+0x38)))			//ADC2 injected sequence register
#define ADC2_JDR1					(*((u32 *) (ADC2_BASE+0x3C)))			//ADC2 injected data register 1
#define ADC2_JDR2					(*((u32 *) (ADC2_BASE+0x40)))			//ADC2 injected data register 2
#define ADC2_JDR3					(*((u32 *) (ADC2_BASE+0x44)))			//ADC2 injected data register 3
#define ADC2_JDR4					(*((u32 *) (ADC2_BASE+0x48)))			//ADC2 injected data register 4
#define ADC2_DR						(*((u32 *) (ADC2_BASE+0x4C)))			//ADC2 regular data register
/*constants********************************/
#define ADC1_REGCONVGROUP_NBR_OF_CHANNELS 5
#define ADC1_REGCONVGROUP_BUFFER_DEPTH 1
/*Function Prototypes**********************/
/*ADC1**/
void ADC1_Init(void);
u16 ADC1_Read_Channel_14(void);
void ADC1_Start_ConvGroup_1(u32, u8);
/*filtering*/
void ADC1_Filter_Average(u16 *adc_buffer, u16 *adc_buffer_filtered,u8 nbr_of_channels, u16 adc_buffer_depth);
#endif /* STM32_ADC_H_ */
