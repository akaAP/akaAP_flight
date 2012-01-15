/**
 ******************************************************************************
 * @file      startup_stm32f10x_md.c
 * @author    MCD Application Team, modified by Martin Thomas
 * @version   V3.0.0-mthomas2
 * @date      5. Dec. 2009
 *            This module:
 *                - writes the the .data section (initialized data) fom Flash to RAM where the program expects to find it
 *                - calls the constructors of all static/global objects to initialize them
 *                - branches to main()
 *            After Reset the Cortex-M3 processor is in Thread mode,
 *            priority is Privileged, and the Stack is set to Main.
 *******************************************************************************


/* Includes ------------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
extern unsigned long _etext;

/* start address for the initialization values of the .data section.
defined in linker script */
extern unsigned long _start_of_ini_data_section;

/* start address for the .data section. defined in linker script */
extern unsigned long _start_of_data_section;

/* end address for the .data section. defined in linker script */
extern unsigned long _end_of_data_section;

/* start address for the .data section. defined in linker script */
extern unsigned long _start_of_data_section_in_flash;
/* start address for the .data section. defined in linker script */
extern unsigned long _start_of_data_section_in_ram;

/* end address for the .data section. defined in linker script */
extern unsigned long _end_of_data_section_in_ram;


/* start address for the .bss section. defined in linker script */
extern unsigned long _start_of_bss_section_in_ram;

/* end address for the .bss section. defined in linker script */
extern unsigned long _end_of_bss_section_in_ram;

/* init value for the stack pointer. defined in linker script */
extern unsigned long _estack;

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));




/*Define the vector table*/
unsigned int * myvectors[56]
   __attribute__ ((section("vectors")))= {
   	(unsigned int *)	&_estack,						/* stack pointer */
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
   	(unsigned int *)	SysTick_Handler,			/* SysTick Handler */
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


/* Private functions ---------------------------------------------------------*/

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @par    :  none
 * @return : none
*/
void Reset_Handler(void)
{
/*
	//startup delay
	volatile unsigned long i, a;
	for (i=0;i<500000;i++) {
		a++;			//do something to prevent the compiler from optimizing this loop away
	}
*/

//**********************************************************************
 /* Initialize .data and .bss section */
//**********************************************************************

	// Copy the .data section initializers from flash to SRAM
	unsigned long* source_inFlash  	= &_start_of_data_section_in_flash;			//defined in the linker script
	unsigned long* destination_inRam 	= &_start_of_data_section_in_ram;			//defined in the linker script

	if ( source_inFlash != destination_inRam )
	{
		while( destination_inRam < &_end_of_data_section_in_ram )
		{
			*(destination_inRam++) = *(source_inFlash++);
		}
	}

	// Zero fill the bss segment.
	destination_inRam = &_start_of_bss_section_in_ram;
	while(destination_inRam < &_end_of_bss_section_in_ram)
	{
		*(destination_inRam++) = 0;
	}

//**********************************************************************
  /* Call constructors of static objects */
//**********************************************************************
	// __libc_init_array();		  //this function was'nt part of the libc.a,
		  	  	  	  	  	  	  //the  code below is the content of the __libc_init_array() function in the newLib 1.19.0
	u32 count;
	u32 i;

	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; i++){
		__preinit_array_start[i] ();
	}

	//_init ();

	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++){
		__init_array_start[i] ();
	}

//**********************************************************************
/* Call the application's entry point.*/
//**********************************************************************
		    main();

		    while(1) { ; }
}//eof
