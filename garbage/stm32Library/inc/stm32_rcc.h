 /*************************************
 * stm32_rcc.h
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

#ifndef STM32_RCC_H_
#define STM32_RCC_H_

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_flash.h"
#include "stm32_serv.h"

#define GPIOA 1
#define GPIOB 2
#define GPIOC 3
#define GPIOD 4
#define GPIOE 5
#define GPIOF 6
#define GPIOG 7

/*Register structure******************************************/
typedef struct
{
	  vu32 CR;
	  vu32 CFGR;
	  vu32 CIR;
	  vu32 APB2RSTR;
	  vu32 APB1RSTR;
	  vu32 AHBENR;
	  vu32 APB2ENR;
	  vu32 APB1ENR;
	  vu32 BDCR;
	  vu32 CSR;
	  /*
	  #ifdef STM32F10X_CONNECTIVITYLINE
	  vu32 AHBRSTR;
	  vu32 CFGR2;
	  #endif //STM32F10X_CONNECTIVITYLINE
	  */
} RCC_RegisterStructure;

/*peripheral class***************************************/
class RCC
{
	public:
		RCC();										//constructor
		~RCC(void);									//destructor
		void init();								//initializes the RCC: configures clock prescalers etc.
		RCC_RegisterStructure* reg;					//pointer to the RCC_RegisterStructure, used to access the peripheral's registers
		void RCC_Init();
		u32 getPeripheralClockFrequency(u16 hardwareID);
		void enablePeripheralClock(u16 hardwareID);
		static const u16 useExternalOscillator = 1;
		static const u16 useInternalOscillator = 2;

		static const u16 hardwareID_USART1 = 1;
		static const u16 hardwareID_USART2 = 2;
		static const u16 hardwareID_USART3 = 3;
		static const u16 hardwareID_USART4 = 4;
		static const u16 hardwareID_USART5 = 5;

		static const u16 hardwareID_GPIOA  = 11;
		static const u16 hardwareID_GPIOB  = 12;
		static const u16 hardwareID_GPIOC  = 13;
		static const u16 hardwareID_GPIOD  = 14;
		static const u16 hardwareID_GPIOE  = 15;
		static const u16 hardwareID_GPIOF  = 16;
		static const u16 hardwareID_GPIOG  = 17;

		static const u16 hardwareID_AFIO   = 21;

		u32 APB1Frequency;
		u32 APB2Frequency;
		u32 sysTick_getValue(void);
		void init_SysTick(void);

		void sysTickHandler(void);
		static vu32 systemTime_ms;
		static vu32 systemTime_lastValue;
};//eoc


 /*Definitions******************************/
/*Registers*/
#define RCC_CR 				  	(*((u32 *) (RCC_BASE+0x000)))		//clock control register
#define RCC_CFGR 				(*((u32 *) (RCC_BASE+0x004)))		//clock configuration register
#define RCC_CIR 				(*((u32 *) (RCC_BASE+0x008)))		//clock interrupt register
#define RCC_APB2RSTR 			(*((u32 *) (RCC_BASE+0x00C)))		//APB2 peripheral reset register
#define RCC_APB1RSTR 			(*((u32 *) (RCC_BASE+0x010)))		//APB1 peripheral reset register
#define RCC_AHBENR 				(*((u32 *) (RCC_BASE+0x014)))		//AHP peripheral clock register
#define RCC_APB2ENR 			(*((u32 *) (RCC_BASE+0x018)))		//APB2 peripheral clock register
#define RCC_APB1ENR 			(*((u32 *) (RCC_BASE+0x01C)))		//APB1 peripheral clock register
#define RCC_BDCR 				(*((u32 *) (RCC_BASE+0x020)))		//backup domain control register
#define RCC_CSR 				(*((u32 *) (RCC_BASE+0x024)))		//control/status register

/*Function Prototypes**********************/

#endif /* STM32_RCC_H_ */
