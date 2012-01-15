/*
 * stm32_library.h
 *
 * Author: janjan
 * @brief this header file includes all other header files, so you only have to include
 * this file to include all stm32 library headers
 */

#ifndef STM32_LIBRARY_H_
#define STM32_LIBRARY_H_

//inclusions************************

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"
#include "stm32_can.h"
#include "stm32_dma.h"
#include "stm32_exti.h"
#include "stm32_flash.h"
#include "stm32_gpio.h"
#include "stm32_i2c.h"
#include "stm32_nvic.h"
#include "stm32_math.h"
#include "stm32_spi.h"
#include "stm32_timer.h"
#include "stm32_usart.h"

/**
 * brief Definition of a STM32 class. A STM32 represents a STM32 microcontroller and all of
 * its peripherals
 */
class STM32{
	public:
		STM32();							//constructor
		~STM32();							//destructor
	   	static STM32 *pointerToStm32;		//pointer to the STM32 object (is a singleton. Only one instance is allowed to
	   										//exist) used to access the peripherals' interrupt handlers
		NVIC	nvic;						//Nested Vectored Interrupt Controller
		RCC		rcc;						//Reset and Clock Control
		GPIO 	gpioA;						//GPIO port A
		GPIO 	gpioB;						//GPIO port B
		GPIO 	gpioC;						//GPIO port C
		USART 	usart1;						//USART1
		//Wrapper functions for interrupt service routines
	   	static void	dummyIRQHandler(void);	   					/* reserved Interrupt Vector(void); not used yet */
	   	static void	nmi_IRQHandler(void);					/* NMI handler */
	   	static void	hardfault_IRQHandler(void);				/* hard fault handler */
	   	static void	memManage_IRQHandler(void);				/* MPU fault handler */
	   	static void	busFault_IRQHandler(void);				/* Bus fault handler */
	   	static void	usageFault_IRQHandler(void);			/* Usage Fault handler */
	   	static void	svc_IRQHandler(void);					/* SVCall handler */
	   	static void	debugMon_IRQHandler(void);				/* Debug Monitor handler */
	   	static void	pendSV_IRQHandler(void);				/* PendSV handler */
	   	static void	sysTick_IRQHandler(void);				/* SysTick handler */
	   	static void	windowWatchdog_IRQHandler(void);		/* window watchdog interrupt handler */
	   	static void	PVD_IRQHandler(void);			    	/* PVD through EXTI Line detection interrupt handler */
	   	static void	TAMPER_IRQHandler(void);				/* Tamper interrupt handler */
	   	static void	RTC_IRQHandler(void);					/* RTC global interrupt handler */
	   	static void	FLASH_IRQHandler(void);					/* Flash global interrupt handler */
	   	static void	RCC_IRQHandler(void);					/* RCC global interrupt handler */
	   	static void	EXTI0_IRQHandler(void);           	/* EXTI Line0 interrupt handler */
	   	static void	EXTI1_IRQHandler(void);           	/* EXTI Line1 interrupt handler */
	   	static void	EXTI2_IRQHandler(void);           	/* EXTI Line2 interrupt handler */
	   	static void	EXTI3_IRQHandler(void);           	/* EXTI Line3 interrupt handler */
	   	static void	EXTI4_IRQHandler(void);           	/* EXTI Line4 interrupt handler */
	   	static void	DMA1_CH1_IRQHandler(void);        	/* DMA Channel1 global interrupt handler */
	   	static void	DMA1_CH2_IRQHandler(void);        	/* DMA Channel2 global interrupt handler */
	   	static void	DMA1_CH3_IRQHandler(void);        	/* DMA Channel3 global interrupt handler */
	   	static void	DMA1_CH4_IRQHandler(void);        	/* DMA Channel4 global interrupt handler */
	   	static void	DMA1_CH5_IRQHandler(void);        	/* DMA Channel5 global interrupt handler */
	   	static void	DMA1_CH6_IRQHandler(void);        	/* DMA Channel6 global interrupt handler */
	   	static void	DMA1_CH7_IRQHandler(void);        	/* DMA Channel7 global interrupt handler */
	   	static void	ADC_1_2_IRQHandler(void);				/* ADC1 and ADC2 global interrupt handler*/
	   	static void	USB_HP_CAN_TX_IRQHandler(void);		/* USB High Priority or CAn TX interrupts handler */
	   	static void	USB_LP_CAN_RX0_IRQHandler(void);		/* USB LOW Priority or CAN RX0 interrupts handler */
	   	static void	CAN_RX1_IRQHandler(void);				/* CAN RX1 interrupt handler */
	   	static void	CAN_SCE_IRQHandler(void);				/* CAN SCE interrupt handler */
	   	static void	EXTI_9_5_IRQHandler(void);			/* EXTI Line[9:5] interrupts handler */
	   	static void	TIM1_BRK_IRQHandler(void);			/* TIMER 1 Break interrupt handler */
	   	static void	TIM1_UP_IRQHandler(void);				/* TIMER 1 Updates interrupt handler */
	   	static void	TIM1_TRG_COM_IRQHandler(void);		/* TIMER 1 Trigger and Commutation interrupts handler */
	   	static void	TIM1_CC_IRQHandler(void);				/* TIMER 1 Capture Compare interrupt handler */
	   	static void	TIM2_IRQHandler(void);				/* TIMER 2 global interrupt handler */
	   	static void	TIM3_IRQHandler(void);				/* TIMER 3 global interrupt handler */
	   	static void	TIM4_IRQHandler(void);				/* TIMER 4 global interrupt handler */
	   	static void	I2C1_EV_IRQHandler(void);				/* I2C1 event interrupt handler */
	   	static void	I2C1_ER_IRQHandler(void);				/* I2C1 error interrupt handler */
	   	static void	I2C2_EV_IRQHandler(void);				/* I2C2 event interrupt handler */
	   	static void	I2C2_ER_IRQHandler(void);				/* I2C2 error interrupt handler */
	   	static void	SPI1_IRQHandler(void);					/* SPI1 global interrupt handler */
	   	static void	SPI2_IRQHandler(void);					/* SPI2 global interrupt handler */
	   	static void	USART1_IRQHandler(void);					/* USART1 global interrupt handler */
	   	static void	USART2_IRQHandler(void);					/* USART2 global interrupt handler */
	   	static void	USART3_IRQHandler(void);					/* USART3 global interrupt handler */

};

#endif /* STM32_LIBRARY_H_ */
