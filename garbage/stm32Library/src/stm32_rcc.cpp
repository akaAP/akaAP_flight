 /*************************************
 * stm32_rcc.c
 * author: jan
 * last modifications: 
 * 
 * description: service functions for clock configuration
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_rcc.h"
 /*Definitions******************************/
 /*Functions********************************/

//define static members
vu32 RCC::systemTime_ms = 0;
vu32 RCC::systemTime_lastValue = 0;

/**
 * @brief constructor.
 */
RCC::RCC(){
	// initialize the pointer to the RCC register structure
	this->reg = ((RCC_RegisterStructure*)RCC_BASE);
}//eof

/**
 * @brief destructor.
 */
RCC::~RCC(void){

}//eof

/**
 * @brief Configures and starts the System Clock.
 *	-use the external oscillator
 *	-pll output frequency 72 MHz
 * @par : none
 * @return: none
 */
void RCC::init(){

		this->reg->CR |= BIT0; 						// HSION=1:turn internal 8MHz oscillator on
		//while(!isBitSet(RCC_CR , 1)){}			// wait for HSI to run stable
		while(!(this->reg->CR & BIT1)){}			// wait for HSI to run stable
		this->reg->CFGR &= ~(BIT1|BIT0);			//set internal oscillator (HSI) as system clock source (default on reset)

		this->reg->CR |= BIT16; 					// HSEON=1:turn external high speed oscillator on
		//while(!isBitSet(RCC_CR , 17)){}			// wait for HSE to run stable
		while(!(this->reg->CR & BIT17)){}			// wait for HSE to run stable

		this->reg->CFGR = 0;						// set to default

		this->reg->CFGR |= (BIT20|BIT19|BIT18);		// PLL-multiplier=9 ( (external oscillator 8MHz)*9 = 72MHz),
		this->reg->CFGR |=  BIT15;	                // divide PLCK2 by 6: ADC prescaler
		this->reg->CFGR |=  BIT10;	                // divide HCLK by 2 (->36MHz) for APB1 low-speed clock
		this->reg->CFGR &= ~(BIT11|BIT12|BIT13);	// set Bit 13-11 to their default state (000): divide HCLK by 1 (->72MHz) for APB2 high-speed clock
		this->reg->CFGR &= ~(BIT4|BIT5|BIT6|BIT7);	// set Bit 7-4 to their default state (0000): AHB-prescaler = 1

		FLASH_ACR |= BIT1;							// set latency for Flash access to 2 wait states

		this->reg->CFGR |= BIT16;					//select HSE oscillator output as PLL source
		this->reg->CR |= BIT24;						// enable PLL
		//while(!isBitSet(RCC_CR , 25)){}			// wait for PLL to run stable
		while(!(this->reg->CR & BIT25)){}			// wait for PLL to run stable
		this->reg->CFGR |= BIT1;					// select PLL output as system clock
		/*now the system clock is running at 72MHz*/
		//Enable clocks to some peripherals
		this->reg->AHBENR = 0x00000014;				//set to default
		this->reg->APB1ENR |= BIT28;				//enable power interface clock
		this->reg->APB1ENR |= BIT27;				//enable backup interface clock
		//Release peripheral reset line on APB1 and APB2 buses
		//RCC_APB2RSTR= 0x00000000;
		//RCC_APB1RSTR= 0x00000000;
		//RCC_CFGR |= BIT26|BIT25|BIT24; 			//enable output of pll_output/2 clock at MCO-pin; pin configured as output, maximum speed?
		this->APB1Frequency = 36000000;
		this->APB2Frequency = 72000000;
		return;
}//eof

u32 RCC::getPeripheralClockFrequency(u16 hardwareID){
	u32 freq = 0;
	//check which peripheral has asked for its clock frequency

			//is it one of the USART peripherals?
			if(hardwareID==RCC::hardwareID_USART1){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_USART2){
				freq = this->APB1Frequency;
			}
			else if (hardwareID == RCC::hardwareID_USART3){
				freq = this->APB1Frequency;
			}
			else if (hardwareID == RCC::hardwareID_USART4){
				freq = this->APB1Frequency;
			}
			else if (hardwareID == RCC::hardwareID_USART5){
				freq = this->APB1Frequency;
			}

			//is it one of the GPIO peripherals?
			else if(hardwareID==RCC::hardwareID_GPIOA){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOB){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOC){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOD){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOE){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOF){
				freq = this->APB2Frequency;
			}
			else if (hardwareID == RCC::hardwareID_GPIOG){
				freq = this->APB2Frequency;
			}

			//is it the AFIO peripheral?
			else if(hardwareID == RCC::hardwareID_AFIO){
				freq = this->APB2Frequency;
			}
	return freq;
}

void RCC::enablePeripheralClock(u16 hardwareID){
	//check which peripheral's clock is supposed to be enabled

		//is it one of the USART peripherals?
		if(hardwareID==RCC::hardwareID_USART1){
			this->reg->APB2ENR |= BIT14;					//enable USART1 clock
		}
		else if (hardwareID == RCC::hardwareID_USART2){
			this->reg->APB1ENR |= BIT17;					//enable USART2 clock
		}
		else if (hardwareID == RCC::hardwareID_USART3){
			this->reg->APB1ENR |= BIT18;					//enable USART3 clock
		}
		else if (hardwareID == RCC::hardwareID_USART4){
			this->reg->APB1ENR |= BIT19;					//enable USART4 clock
		}
		else if (hardwareID == RCC::hardwareID_USART5){
			this->reg->APB1ENR |= BIT20;					//enable USART5 clock
		}

		//is it one of the GPIO peripherals?
		else if(hardwareID==RCC::hardwareID_GPIOA){
			this->reg->APB2ENR |= BIT2;					//enable GPIOA clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOB){
			this->reg->APB2ENR |= BIT3;					//enable GPIOB clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOC){
			this->reg->APB2ENR |= BIT4;					//enable GPIOC clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOD){
			this->reg->APB2ENR |= BIT5;					//enable GPIOD clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOE){
			this->reg->APB2ENR |= BIT6;					//enable GPIOE clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOF){
			this->reg->APB2ENR |= BIT7;					//enable GPIOF clock
		}
		else if (hardwareID == RCC::hardwareID_GPIOG){
			this->reg->APB2ENR |= BIT8;					//enable GPIOG clock
		}

		//is it the AFIO peripheral?
		else if(hardwareID == RCC::hardwareID_AFIO){
			this->reg->APB2ENR |= BIT0;						//enable AFIO clock
		}
}

/* SysTick timer************************************************/
/**
 * @brief this function configures and starts the system timer
 */
void RCC::init_SysTick(void)
{
	//TODO set registers not written to to their default values
	SYSTICK_CSR = 0;							// set to default
	SYSTICK_RVR = 72000;					   	// set SysTick reload value; 72000: underflow each ms if HCLK=72MHz
	SYSTICK_CSR |= BIT2;						// 1: select core clock as clock source 0: select external reference clock HCLK/8
	SYSTICK_CSR |= BIT1;						// underflow of SysTick counter calls SysTick handler
	SYSTICK_CSR |= BIT0;						// enable SysTick counter
	return;
}

u32 RCC::sysTick_getValue(void)
{
	u32 countervalue = SYSTICK_CVR;					//read SysTick current value register
	countervalue &= 0x00FFFFFF;						//set reserved bits to 0(see SYSTICK_CVR description in the stm32 reference manual)
	return countervalue;
}


void RCC::sysTickHandler(void){
	//TODO is there an interrupt flag that should be cleared?

	//do this each second
	if( (RCC::systemTime_ms - RCC::systemTime_lastValue) > 1000){
		//toggle_statusLED();
		//store current time as new reference time
		RCC::systemTime_lastValue = RCC::systemTime_ms;
	}
	//toggle_statusLED();
	RCC::systemTime_ms += 1;							//increase global system time variable by 1 millisecond
	return;

}//eof
