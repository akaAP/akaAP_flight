/*
 * stm32_rcc_conf.h
 *
 *  Created on: 03.12.2010
 *  Author: janjan
 */

#ifndef STM32_RCC_CONF_H_
#define STM32_RCC_CONF_H_


//TODO use these macros to configure the system e.g. in rcc_Init() in stm32_rcc.c

//************************************************************************************************************************
//constants***************************************************************************************************************
//************************************************************************************************************************
#define HSI_FREQUENCY				8000000								//frequency of the internal oscillator
#define HSE_FREQUENCY				8000000								//frequency of the external oscillator

//************************************************************************************************************************
//possible values for configurable parameters, not to be changed**********************************************************
//************************************************************************************************************************

//possible values for the pll multiplication factor
#define PLL_MULTIPLIKATIONFACTOR_9	(BIT20|BIT19|BIT18)					//bit mask for: multiplication factor = 9

//possible values for the APB1 clock prescaler
#define APB1PRESCALER_IS_1												//TODO define bit mask for: prescaler(main clock --> APB1) clock = 1

//possible values for the APB2 clock prescaler
#define APB2PRESCALER_IS_2												//TODO define bit mask for: prescaler(main clock --> APB2) clock = 2

//possible values for the ADC clock prescaler
#define ADCPRESCALER_IS_6												//TODO define bit mask for: prescaler(PCLK2 -->ADC) clock = 6

//************************************************************************************************************************
//configurable parameters, use the possible values above******************************************************************
//************************************************************************************************************************

#define PLL_MULTIPLIKATIONFACTOR	PLL_MULTIPLIKATIONFACTOR_IS_9		//the input clock of the pll is multiplied by this factor to create the pll output clock
#define APB1PRESCALER 				APB1PRESCALER_IS_					//prescaler(main clock --> APB1) clock
#define APB2PRESCALER 				APB2PRESCALER_IS_2					//prescaler(main clock --> APB2) clock. NOTE: APB2 clock frequency should be 36 MHz or less
#define ADCPRESCALER				ADCPRESCALER_IS_6					//prescaler PCLK2 -->ADC clock

//************************************************************************************************************************
//constants derived from the configuration above************************************************************************
//************************************************************************************************************************

#define PLL_INPUT_FREQUENCY			 HSE_FREQUENCY						//use the external oscillator as input for the pll
#define PLL_OUTPUT_FREQUENCY 		 									//use the external oscillator as input for the pll
#define	CORE_CLOCK_FREQUENCY											//TODO calculate here using the macros above
#define APB1__CLOCK_FREQUENCY											//TODO calculate here using the macros above
#define APB2__CLOCK_FREQUENCY											//TODO calculate here using the macros above
#define ADC_CLOCK_FREQUENCY												//TODO calculate here using the macros above

#endif /* STM32_RCC_CONF_H_ */
