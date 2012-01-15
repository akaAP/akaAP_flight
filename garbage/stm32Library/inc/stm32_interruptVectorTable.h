
/*!\file stm32_interruptVectorTable.h
 * \brief the interrupt vector table.
 * created: 07.10.2010
 */

#ifndef STM32_INTERRUPTVECTORTABLE_H_
#define STM32_INTERRUPTVECTORTABLE_H_

 /*Include*********************************/
#include "stm32_library.h"
/*Definitions******************************/

/*Define the vector table*/
unsigned int * myvectors[56]
   __attribute__ ((section("vectors")))= {
   	(unsigned int *)	0x20000800,						/* stack pointer */
   	(unsigned int *) 	Reset_Handler,					/* code entry point, execution starts here after reset */
   	(unsigned int *)	STM32::nmi_IRQHandler,					/* NMI Handler */
   	(unsigned int *)	STM32::hardfault_IRQHandler,			/* hard fault Handler */
   	(unsigned int *)	STM32::memManage_IRQHandler,			/* MPU fault Handler */
   	(unsigned int *)	STM32::busFault_IRQHandler,			/* Bus fault Handler */
   	(unsigned int *)	STM32::usageFault_IRQHandler,			/* Usage Fault Handler */
   	(unsigned int *)	STM32::dummyIRQHandler,	   				/* reserved Interrupt Vector, not used yet */
   	(unsigned int *)	STM32::dummyIRQHandler,	   				/* reserved Interrupt Vector, not used yet */
   	(unsigned int *)	STM32::dummyIRQHandler,	   				/* reserved Interrupt Vector, not used yet */
   	(unsigned int *)	STM32::dummyIRQHandler,	   				/* reserved Interrupt Vector, not used yet */
   	(unsigned int *)	STM32::svc_IRQHandler,					/* SVCall Handler */
   	(unsigned int *)	STM32::debugMon_IRQHandler,			/* Debug Monitor Handler */
   	(unsigned int *)	STM32::dummyIRQHandler,	   				/* reserved Interrupt Vector, not used yet */
   	(unsigned int *)	STM32::pendSV_IRQHandler,				/* PendSV Handler */
   	(unsigned int *)	STM32::sysTick_IRQHandler,			/* SysTick Handler */
   	(unsigned int *)	STM32::windowWatchdog_IRQHandler,		/* window watchdog interrupt Handler */
   	(unsigned int *)	STM32::PVD_IRQHandler,			    	/* PVD through EXTI Line detection interrupt Handler */
   	(unsigned int *)	STM32::TAMPER_IRQHandler,				/* Tamper interrupt Handler */
   	(unsigned int *)	STM32::RTC_IRQHandler,					/* RTC global interrupt Handler */
   	(unsigned int *)	STM32::FLASH_IRQHandler,				/* Flash global interrupt Handler */
   	(unsigned int *)	STM32::RCC_IRQHandler,					/* RCC global interrupt Handler */
   	(unsigned int *)	STM32::EXTI0_IRQHandler,           	/* EXTI Line0 interrupt Handler */
   	(unsigned int *)	STM32::EXTI1_IRQHandler,           	/* EXTI Line1 interrupt Handler */
   	(unsigned int *)	STM32::EXTI2_IRQHandler,           	/* EXTI Line2 interrupt Handler */
   	(unsigned int *)	STM32::EXTI3_IRQHandler,           	/* EXTI Line3 interrupt Handler */
   	(unsigned int *)	STM32::EXTI4_IRQHandler,           	/* EXTI Line4 interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH1_IRQHandler,        	/* DMA Channel1 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH2_IRQHandler,        	/* DMA Channel2 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH3_IRQHandler,        	/* DMA Channel3 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH4_IRQHandler,        	/* DMA Channel4 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH5_IRQHandler,        	/* DMA Channel5 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH6_IRQHandler,        	/* DMA Channel6 global interrupt Handler */
   	(unsigned int *)	STM32::DMA1_CH7_IRQHandler,        	/* DMA Channel7 global interrupt Handler */
   	(unsigned int *)	STM32::ADC_1_2_IRQHandler,				/* ADC1 and ADC2 global interrupt Handler*/
   	(unsigned int *)	STM32::USB_HP_CAN_TX_IRQHandler,		/* USB High Priority or CAn TX interrupts Handler */
   	(unsigned int *)	STM32::USB_LP_CAN_RX0_IRQHandler,		/* USB LOW Priority or CAN RX0 interrupts Handler */
   	(unsigned int *)	STM32::CAN_RX1_IRQHandler,				/* CAN RX1 interrupt Handler */
   	(unsigned int *)	STM32::CAN_SCE_IRQHandler,				/* CAN SCE interrupt Handler */
   	(unsigned int *)	STM32::EXTI_9_5_IRQHandler,			/* EXTI Line[9:5] interrupts Handler */
   	(unsigned int *)	STM32::TIM1_BRK_IRQHandler,			/* TIMER 1 Break interrupt Handler */
   	(unsigned int *)	STM32::TIM1_UP_IRQHandler,				/* TIMER 1 Updates interrupt Handler */
   	(unsigned int *)	STM32::TIM1_TRG_COM_IRQHandler,		/* TIMER 1 Trigger and Commutation interrupts Handler */
   	(unsigned int *)	STM32::TIM1_CC_IRQHandler,				/* TIMER 1 Capture Compare interrupt Handler */
   	(unsigned int *)	STM32::TIM2_IRQHandler,				/* TIMER 2 global interrupt Handler */
   	(unsigned int *)	STM32::TIM3_IRQHandler,				/* TIMER 3 global interrupt Handler */
   	(unsigned int *)	STM32::TIM4_IRQHandler,				/* TIMER 4 global interrupt Handler */
   	(unsigned int *)	STM32::I2C1_EV_IRQHandler,				/* I2C1 event interrupt Handler */
   	(unsigned int *)	STM32::I2C1_ER_IRQHandler,				/* I2C1 error interrupt Handler */
   	(unsigned int *)	STM32::I2C2_EV_IRQHandler,				/* I2C2 event interrupt Handler */
   	(unsigned int *)	STM32::I2C2_ER_IRQHandler,				/* I2C2 error interrupt Handler */
   	(unsigned int *)	STM32::SPI1_IRQHandler,					/* SPI1 global interrupt Handler */
   	(unsigned int *)	STM32::SPI2_IRQHandler,					/* SPI2 global interrupt Handler */
   	(unsigned int *)	STM32::USART1_IRQHandler,					/* USART1 global interrupt Handler */
   	(unsigned int *)	STM32::USART2_IRQHandler,					/* USART2 global interrupt Handler */
   	(unsigned int *)	STM32::USART3_IRQHandler,					/* USART3 global interrupt Handler */
};
 /*Functions********************************/

#endif /* STM32_INTERRUPTVECTORTABLE_H_ */
