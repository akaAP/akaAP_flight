
/*=====GPIOx, AFIO=============*/
void RCC::GPIOA_ClkInit(void)
{
	RCC_APB2ENR |= BIT2;					//enable IO-Port A clock
	return;
}

void RCC::GPIOB_ClkInit(void)
{
	RCC_APB2ENR |= BIT3;					//enable IO-Port C clock
	return;
}
void RCC::GPIOC_ClkInit(void)
{
	RCC_APB2ENR |= BIT4;					//enable IO-Port C clock
	return;
}
void RCC

arm-none-eabi-size -A  ./bin/main.elf
./bin/main.elf  :
section            size        addr
.text              5128   134217728
.rodata             184   134222856
.data                 8   536870912
.bss                 16   536870920
._usrstack          256   536870936
.comment            602           0
.debug_aranges     1488           0
.debug_pubnames    3383           0
.debug_info       22998           0
.debug_abbrev      5382           0
.debug_line        5572           0
.debug_frame       5056           0
.debug_str         7489           0
.debug_loc         7104           0
.debug_ranges      1376           0
.ARM.attributes      37           0
Total             66079


--------  end  --------



::GPIOD_ClkInit(void)
{
	RCC_APB2ENR |= BIT5;					//enable IO-Port C clock
	return;
}
void RCC::GPIOE_ClkInit(void)
{
	RCC_APB2ENR |= BIT6;					//enable IO-Port C clock
	return;
}
void RCC::GPIOF_ClkInit(void)
{
	RCC_APB2ENR |= BIT7;					//enable IO-Port C clock
	return;
}
void RCC::GPIOG_ClkInit(void)
{
	RCC_APB2ENR |= BIT8;					//enable IO-Port C clock
	return;
}

void RCC:: AFIO_ClkInit(void)
{
RCC_APB2ENR |= BIT0;						//enable AFIO clock
return;
}
/*===USARTx, SPIx==========================*/
void RCC::USART1_ClkInit(void)
{
	RCC_APB2ENR |= BIT14;					//enable USART1 clock
	return;
}

void RCC::USART2_ClkInit(void)
{
	RCC_APB1ENR |= BIT17;					//enable USART2 clock
	return;
}

void RCC::USART3_ClkInit(void)
{
	RCC_APB1ENR |= BIT18;					//enable USART3 clock
	return;
}


void RCC::SPI1_ClkInit(void)
{
	RCC_APB2ENR |= BIT12;					//enable SPI1 clock
	return;
}

/*===CANx========================*/
void RCC::CAN1_ClkInit(){
	RCC_APB1ENR |= BIT25;					//enable CAN1 clock
	return;
}//eof

/*===DMAx========================*/
void RCC::DMA1_ClkInit(void)
{
	RCC_AHBENR |= BIT0;						//enable DMA1 clock
	return;
}
/*===ADCx=========================*/
void RCC::ADC1_ClkInit(void)
{
	RCC_APB2ENR |= BIT9;					//enable ADC1 clock
	wait(1);
	RCC_APB2RSTR |= BIT9;					//reset ADC1
	wait(1);
	RCC_APB2RSTR &= ~BIT9;					//clear ADC1 reset bit

	return;
}

/*===Timerx=========================*/
void RCC::TIM1_ClkInit()
{
	RCC_APB2ENR|= BIT11;					//enable Timer 1 clock
	return;

}///eof

/**
 * resets the TIMER 1 peripheral
 */
void RCC::TIM1_Reset(){
	RCC_APB2RSTR |= BIT16_11;
	return;
}//eof

void RCC::TIM2_ClkInit()
{
	RCC_APB1ENR |= BIT0;					//enable Timer 2 clock
	return;
}
