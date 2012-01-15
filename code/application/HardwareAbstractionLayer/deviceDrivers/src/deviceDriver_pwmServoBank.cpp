/**
 *\file deviceDriver_servoBank.cpp
 *\brief Please provide information that could be useful for understanding the code here.
 *\author Jan
*/

//Inclusions
#include "../inc/deviceDriver_pwmServoBank.h"

/**
 * \brief Constructor;
 */
ServoBank::ServoBank(	uint8_t numberOfChannelsToUse,
							TIM_TypeDef** timerPeripheralsToUse, uint8_t numberOfTimersToUse,
							GPIO_TypeDef** gpioPortPeripherals, uint32_t* GPIOPins, uint8_t numberOfGpioPorts,
							uint32_t interval,
							uint32_t* initialChannelWidths
							)
{
	//configure PWM Timers and related peripherals

	//enable AFIO clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//configure GPIO ports for PWM output
	for(uint8_t i = 0; i<numberOfGpioPorts; i++){
		configureGPIO(gpioPortPeripherals[i], GPIOPins[i]);
	}

	//configure timers for PWM
	for(uint8_t i = 0; i<numberOfTimersToUse; i++){
		//copy pointers to Timer structures
		this->timerPeripherals[i]=timerPeripheralsToUse[i];
		this->timer_nsPerTick = initTimer(timerPeripheralsToUse[i]);
	}

	this->numberOfChannels = numberOfChannelsToUse;
	this->numberOfTimers = numberOfTimersToUse;
	//set pulse interval and pulse width to their initial values
	this->setInterval(interval);
	this->setPWMPulseWidth(initialChannelWidths);

	return;
}//eof

/**
 * \brief Destructor.
 */
ServoBank::~ServoBank(){
	// TODO Free memory?
}//eof


/**
 * @brief Sets the span of time between 2 PWM pulses to the given value.
 * @paramam uint32_t - the desired timer interval [ns]
 */
void ServoBank::setInterval(uint32_t interval)
{
	for(uint8_t i = 0; i<this->numberOfTimers; i++){
		TIM_SetAutoreload(this->timerPeripherals[i], interval/this->timer_nsPerTick);	//change the the Timer's ARR register

	}

	return;
}//eof


/**
 * @brief Sets the servos to the given positions.
 * @param int16_t* ChannelWidths - pointer to an array containing the Positions [-1000, 1000]
 */
void ServoBank::setPositions(int16_t* positions)
{
	for(uint8_t i = 0; i<this->numberOfTimers; i++){
		this->timerPeripherals[i]->CCR1 = (uint16_t)((1500000 + (positions[(i*4)+0]*1000/2 ))/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR2 = (uint16_t)((1500000 + (positions[(i*4)+1]*1000/2 ))/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR3 = (uint16_t)((1500000 + (positions[(i*4)+2]*1000/2 ))/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR4 = (uint16_t)((1500000 + (positions[(i*4)+3]*1000/2 ))/this->timer_nsPerTick);
	}
	return;
}//eof

/**
 * @brief Sets the PWM pulsewidths to the given values [ns].
 * @param uint32_t* ChannelWidths - pointer to an array containing the PWM pulseWidths [ns]
 */
void ServoBank::setPWMPulseWidth(uint32_t* ChannelWidths)
{
	for(uint8_t i = 0; i<this->numberOfTimers; i++){
		this->timerPeripherals[i]->CCR1 = (uint16_t)(ChannelWidths[(i*4)+0]/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR2 = (uint16_t)(ChannelWidths[(i*4)+1]/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR3 = (uint16_t)(ChannelWidths[(i*4)+2]/this->timer_nsPerTick);
		this->timerPeripherals[i]->CCR4 = (uint16_t)(ChannelWidths[(i*4)+3]/this->timer_nsPerTick);
	}
	return;
}//eof

/**
 *
 * @brief Configures and starts a General Purpose Timer as standard PWM Timer
 * (initial setting: generate a pulse every 20ms, initial pulswidth 1,5ms).
 * @return uint32_t - the time interval of one timer tick [ns/tick]
 */
uint32_t ServoBank::initTimer(TIM_TypeDef* timer){
	// FIXME a certain option has to be set for advanced timers as TIM1, TIM8 to make them work; something like 'output activation'.
	#define CCDEFAULTVALUE 1500
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	//enable timer clock and get Timer clock frequency
	enableTIMERClockForPWM(timer);
	uint32_t timer_clockFrequency = getTimerClock(timer);
    uint32_t prescaler = (timer_clockFrequency/2000000);				//counter frequency = 2 MHz
	uint32_t counterFrequency = timer_clockFrequency/prescaler;
	uint32_t nsPerTick = 1000000000/counterFrequency;				//10^6 ns divided by the counter frequency

	//set registers to their default values
	TIM_DeInit(timer);

	/* Time Base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;							//indicates the division ratio between the timer clock (CK_INT) frequency and
																					//sampling clock used by the digital filters (ETR, TIx),
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 20000000/nsPerTick;							//sets the ARR register: timer is reloaded once it has reached x
	TIM_TimeBaseStructure.TIM_Prescaler = 2*prescaler;								//FIXME check why it has to be "2*"  to set counter frequency to 1MHz
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;								//only applies to TIM1 and TIM8
	TIM_TimeBaseInit(timer, &TIM_TimeBaseStructure);
	//done

	TIM_OCStructInit(&TIM_OCInitStructure);

	/* configure Channel 1, 2,3 and 4 in PWM 1 mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;							//only applies to TIM1 and TIM8
	TIM_OCInitStructure.TIM_Pulse = CCDEFAULTVALUE;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;								//only applies to TIM1 and TIM8
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;							//only applies to TIM1 and TIM8
	TIM_OC1Init(timer, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = CCDEFAULTVALUE;
	TIM_OC2Init(timer, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = CCDEFAULTVALUE;
	TIM_OC3Init(timer, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = CCDEFAULTVALUE;
	TIM_OC4Init(timer, &TIM_OCInitStructure);

	//create timer update event to start transfer from preload registers to shadow registers
	TIM_GenerateEvent(timer, TIM_EventSource_Update);

	/* timer counter enable */
	TIM_Cmd(timer, ENABLE);

	return nsPerTick;
}//eof

/**
 * @brief Configures a GPIO port to be used for PWM output.
 * @param GPIO_TypeDef* gpio - the identifier of the port, e.g. GPIOB.
 * @param uint16_t pins - a 16Bit (since there are 16 pins per GPIO port) binary number expressing
 * which pins are supposed to be configured;
 * e.g. (0b0001 | 0b0100 ) means pin 0 and pin 2
 */
void ServoBank::configureGPIO(GPIO_TypeDef* gpio, uint16_t pins){
	GPIO_InitTypeDef GPIO_InitStructure;

	enableGPIOClockForPWM(gpio);
	GPIO_InitStructure.GPIO_Pin = pins;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(gpio, &GPIO_InitStructure);

}//eof

/**
 *
 * @brief Enables the clock of a GPIO peripheral.
 * @param GPIO_TypeDef* gpio - identifier of the GPIOx supposed to be enabled. May be GPIOA - GPIOG.
 */
void ServoBank::enableGPIOClockForPWM(GPIO_TypeDef* gpio){

	if(gpio==GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(gpio==GPIOB){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(gpio==GPIOC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if(gpio==GPIOD){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if(gpio==GPIOE){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	}
	else if(gpio==GPIOF){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else if(gpio==GPIOG){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	}
	return;
}//eof


/**
 *
 * @brief Enables the clock of a TIMER peripheral.
 * @param TIM_TypeDef* timer - identifier of the TIMERx supposed to be enabled.
 */
void ServoBank::enableTIMERClockForPWM(TIM_TypeDef* timer){

	//timers connected to APB1
	if(timer==TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	else if(timer==TIM8){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	}
	else if(timer==TIM9){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	}
	else if(timer==TIM10){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	}
	else if(timer==TIM11){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	}
	//timers connected to APB2
	else if(timer==TIM2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if(timer==TIM3){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(timer==TIM4){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	else if(timer==TIM5){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
	else if(timer==TIM6){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	}
	else if(timer==TIM7){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	}
	else if(timer==TIM12){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	}
	else if(timer==TIM13){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	}
	else if(timer==TIM14){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	}

	return;
}//eof

/**
 * @brief returns the clock frequency of the given TIMER peripheral.
 * @param TIM_Typedef* timer - the identifier of the TIMEr peripheral, e.g. TIM2.
 */
uint32_t ServoBank::getTimerClock(TIM_TypeDef* timer){
	RCC_ClocksTypeDef rccClock;
	RCC_GetClocksFreq(&rccClock);
	uint32_t timer_clockFrequency = 0;
	//timers connected to APB1
	if(timer==TIM1 || timer==TIM8 || timer==TIM9 || timer==TIM10 || timer==TIM11 )
	{
		timer_clockFrequency = rccClock.PCLK2_Frequency;
	}
	else if(timer==TIM2 || timer==TIM3 || timer==TIM4 || timer==TIM5 || timer==TIM6 || timer==TIM7  || timer==TIM12 || timer==TIM13 || timer==TIM14 )
	{
			timer_clockFrequency = rccClock.PCLK1_Frequency;
	}
	return timer_clockFrequency;
}//eof
