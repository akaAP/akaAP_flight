 /*************************************
 * stm32_timer.c
 * author: jan
 * description: holds all functions concerning
 * timers
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_timer.h"
 /*Definitions******************************/
//this variable is increased every time the timer 1 counter flows over.
//It represents the time [kilo-counts] passed by since the timer 1 counter has been started
//or since the variable has been reset to 0 to avoid overflow
s32 timer1_time_kCounts = 0;
//this variable indicates how much time one counter unit stands for [ns/counterunit]
//has to be initialized in TIMER1_Init()
float timer1_counterUnitTime = 0;
//this variable indicates after what span of time [kilo-counts] the timer 0 counter overflows and generates an update event
//has to be initialized in TIMER1_Init()
s32 timer1_kCountsTilOverflow = 0;
//indicates at which global timer time the last timer 1 channel 1 capture event occured [ms]
s32 timer1_ch1_lastCapture_kCounts;
s32 timer1_ch1_lastCapture_Counts;
 /*Functions********************************/
/*TIMER 1************************************************/

/**
 * @brief configures and enables the Advanced Control Timer 1.
 */
void TIMER1_Init(){
	//timer 1 (channel 1) is supposed to be used to measure ppm input signals;
	//it is configured according to the STM32 reference manual rev.11, page 288
	//rising edges are captured
	//capture register: TIM1_CCR1
	//counter runs as upcounter (default value of TIM1_CR1), counts up from 0 to the
	// auto reload value, generates an overflow/update event and starts anew from 0

	//enable timer 1 clock
	TIM1_ClkInit();
	//set register to default value
	TIM1_CCER = 0;
	//enable Capture/Compare interrupt on channel 3 (channel 3 capture interrupt flag: TIM1_SR:Bit1)
	TIM1_DIER |= BIT16_1;
	//enable update interrupt ((Timer 1 update interrupt flag: TIM1_SR:Bit 0))
	TIM1_DIER |= BIT16_0;
	//configure CC3 channel as input, IC3 is mapped on TI3
	TIM1_CCMR1 |= BIT16_0;
	//configure the input filter
	TIM1_CCMR1 |= (BIT16_4 | BIT16_5);
	//set prescaler value to 8 to achieve (72/9)=8MHz counter frequency
	//(core frequency 72MHz, APB2 frequency 72MHz, f_counter = f_APB2/(prescaler+1)
	//(STM32 reference manual rev.11, 13.4.11) )
	//1 Counter unit = 0,125 탎
	TIM1_PSC = 8;
	//set auto reload value; overflow each 8,0 milliseconds
	TIM1_ARR = 64000;
	//enable input capture for channel 3
	TIM1_CCER |= BIT16_0;
	//enable Counter
	TIM1_CR1 |= BIT16_0;
	//clear interrupt flags, set to reset value
	TIM1_SR = 0;
	//generate timer update to write preload register values to the shadow registers
	TIM1_EGR |= BIT16_0;
	//restart Timer 1 from 0
	//TIM1_CNT = 0;

	//set counter unit [ns/counterunit]
	timer1_counterUnitTime = 125;
	//set time till overflow [ms]
	timer1_kCountsTilOverflow = 64;
	return;
}//eof

/**
 * @brief call this function if an update event has happened, e.g. from the update event interrupt handler.
 */
void TIMER1_notifyOfUpdateEvent(void){
	// increase timer time by x milliseconds since the timer overflow takes place every x ms
	timer1_time_kCounts += timer1_kCountsTilOverflow;
	//toggle_statusLED();
}//eof

/**
 * this interrupt handler function is called each time
 * a Timer 1 update event occurs (if the interrupt is enabled)
 */
void TIM1_UP_IRQhandler(){
	//clear update event interrupt bit in the timer Status Register first
	 TIMER1_clearUpdateInterruptFlag();
	 TIMER1_notifyOfUpdateEvent();
	 //let's take a look into the status register
	 //USART1_SendByte((u8)TIM1_SR);
	return;
}//eof

void TIM1_CC_IRQhandler(){
	//check which timer channel has caused the interrupt
	u8 channel = TIMER1_getCaptureCompareInterruptSource();
	//clear the corresponding capture/compare event interrupt flag
	TIMER1_clearCaptureCompareInterruptFlag(channel);

	//check which timer channel has caused the interrupt
	   if(channel==1){
		   //if it's channel 1
		   //add ; (gcc compiler bug c/37231 workaround: declarations right after labels don't work)
		   ;
		   //toggle_statusLED();
		   //read the capture compare register
		   s32 capturedValue = (u32)TIMER1_getCaptureValueOfChannel1();

		   //calculate interval length in counts
		   s32 interval_kCounts = timer1_time_kCounts - timer1_ch1_lastCapture_kCounts;
		   s32 interval_Counts = (interval_kCounts*1000) + (capturedValue - timer1_ch1_lastCapture_Counts);

		   //set new reference values
		   //TODO check if the interval is a valid one before setting new reference values to avoid shifting channels
		   timer1_ch1_lastCapture_kCounts = timer1_time_kCounts;
		   timer1_ch1_lastCapture_Counts = capturedValue;

		   //calculate the interval in nanoseconds
		   s32 interval = interval_Counts*timer1_counterUnitTime;

		   //FIXME function has been commented out during the C++ integration
		   //ppm_notifyOfPulseInterval(interval);
	   }
	   else if(channel==2){
		   //if it's channel 2
	   }
	   else if(channel==2){
		   //if it's channel 3
	   }
	   else if(channel==2){
		   //if it's channel 4
	   }

	return;
}//eof


/**
 * @brief creates an update event.
 */
void TIMER1_forceUpdateEvent(void){
	//create an update event by setting the related bit in the Event Generation Register
	TIM1_EGR |= BIT0;
}//eof

/**
 * @brief this function returns the channel which has caused a capture/compare interrupt.
 * It returns the number (1-4) of the channel. If no interrupt flag is set it returns 0.
 * TODO find out why sometimes all four channel interrupt flags are set though only one channel capture
 * interrupt is enabled
 */
u8 TIMER1_getCaptureCompareInterruptSource(void){
	// if no interrupt flag is set return 0
	u8 channel = 0;
	//TODO fix: return 1 until it is clear why the other capture flags are set too
	channel = 1;

	/*
	//check which interrupt flag is set

	//is it channel 1?
	if( ((TIM1_SR) & BIT16_1)==BIT1 ){
		channel = 1;
		//set_statusLED(1);
	}
	//or channel 2?
	if( (TIM1_SR & BIT16_2)==BIT2 ){
		channel = 2;
		//set_statusLED(1);
	}
	//or channel 3?
	if( (TIM1_SR & BIT16_3)==BIT3 ){
		channel = 3;
		//set_statusLED(1);
	}
	//or channel 4?
	if( (TIM1_SR & BIT16_4)==BIT4 ){
		channel = 4;
		//set_statusLED(1);
	}
	*/
	return channel;
}//eof

/**
 * @brief this function clears the corresponding timer 1 capture/compare interrupt flag (Bit)
 * of a given timer channel.
 */
void TIMER1_clearCaptureCompareInterruptFlag(u8 channel){
	switch(channel)
	{
	   case 1:
		   //if it's channel 1
		   TIM1_SR &= ~BIT16_1;
		   break;
	   case 2:
		   //if it's channel 2
		   TIM1_SR &= ~BIT16_2;
		   break;
	   case 3:
		   //if it's channel 3
		   TIM1_SR &= ~BIT16_3;
		   break;
	   case 4:
		   //if it's channel 4
		   TIM1_SR &= ~BIT16_4;
		   break;
	}
   return;
}//eof

/**
 * @brief this function clears the timer 1 update event interrupt flag.
 */
void TIMER1_clearUpdateInterruptFlag(void){
	TIM1_SR &= ~(BIT16_0);
	return;
}//eof

/**
 * @brief this function clears the timer 1 Break event interrupt flag.
 */
void TIMER1_clearBreakInterruptFlag(void){
	TIM1_SR &= ~(BIT16_7);
}//eof

/**
 * @brief this function returns the value of the capture/compare register of timer channel 3.
 */
u16 TIMER1_getCaptureValueOfChannel1(void){
	return TIM1_CCR1;
}//eof

/*TIMER 2************************************************/

//pwm pulse lengths[탎]
#define PWM_WIDTH_MAX		2000
#define PWM_WIDTH_NEUTRAL	1500
#define PWM_WIDTH_MIN		1000

/**
 * configures and activates general purpose Timer 2
 */
 void TIMER2_Init()
{
	//TODO set registers not written to to their default values
	//set up timer
	TIM2_ClkInit();												//enable Timer 2 clock
	TIM2_CR1 = 0;												//set to default: upcounter, AutoReloadvalueRegister not buffered, Edge-Aligned mode
	TIM2_PSC = 72;										  		//set prescaler value, timer should run on 1MHz now
	TIM2_ARR = 20000;											//counter counts up until it reaches the AutoReloadRegister value

	//set up channel 1
	TIM2_CCMR1 |= ( BIT5 | BIT6 );								//select channel 1 mode: pwm mode 1
	TIM2_CCMR1 |= BIT3;											//enable preload of channel 1 CaptureCompareRegister; changes to this register are taken into account at the next timer update event
	TIM2_CCR1 = 1500;											//set compare value for channel 1
	TIM2_CCER |= ( BIT0 );										//capture/compare output enable
	//set up channel 2
	TIM2_CCMR1 |= ( BIT14 | BIT13 );							//select channel2 mode: pwm mode 1
	TIM2_CCMR1 |= BIT11;										//enable preload of channel 2 CaptureCompareRegister; changes to this register are taken into account at the next timer update event
	TIM2_CCR2 = 1500;											//set compare value for channel 2
	TIM2_CCER |=  BIT4 ;										//capture/compare output enable
	//set up channel 3
	TIM2_CCMR2 |= ( BIT5 | BIT6 );								//select channel 1 mode: pwm mode 1
	TIM2_CCMR2 |= BIT3;											//enable preload of channel 1 CaptureCompareRegister; changes to this register are taken into account at the next timer update event
	TIM2_CCR3 = 1500;											//set compare value for channel 1
	TIM2_CCER |= ( BIT8 );										//capture/compare output enable
	//set up channel 4
	TIM2_CCMR2 |= ( BIT14 | BIT13 );							//select channel2 mode: pwm mode 1
	TIM2_CCMR2 |= BIT11;										//enable preload of channel 2 CaptureCompareRegister; changes to this register are taken into account at the next timer update event
	TIM2_CCR4 = 1500;											//set compare value for channel 2
	TIM2_CCER |=  BIT12 ;										//capture/compare output enable


	TIM2_EGR |= BIT0;											//generate timer update to write preload register values to the shadow registers
	TIM2_CR1 |= BIT0; 											//enable Counter

return;
}

 /**

  * sets the servo position to the given value
  * @param position between -1000 and +1000[1]
  */
 void TIMER2_Ch1_setServoPosition(s16 position)
{
	 //set compare value for channel 1
	 u16 w = TIMER2_convertPositionToPulsewidth(position);
	 TIMER2_Ch1_setPWMPulseLength(w);
	 return;
}
 /**

  * sets the servo position to the given value
  * @param position between -1000 and +1000[1]
  */
 void TIMER2_Ch2_setServoPosition(s16 position)
{
	 //set compare value for channel 1
	 u16 w = TIMER2_convertPositionToPulsewidth(position);
	 TIMER2_Ch2_setPWMPulseLength(w);
	 return;
}
 /**

  * sets the servo position to the given value
  * @param position between -1000 and +1000[1]
  */
 void TIMER2_Ch3_setServoPosition(s16 position)
{
	 //set compare value for channel 1
	 u16 w = TIMER2_convertPositionToPulsewidth(position);
	 TIMER2_Ch3_setPWMPulseLength(w);
	 return;
}
 /**

  * sets the servo position to the given value
  * @param position between -1000 and +1000[1]
  */
 void TIMER2_Ch4_setServoPosition(s16 position)
{
	 //set compare value for channel 1
	 u16 w = TIMER2_convertPositionToPulsewidth(position);
	 TIMER2_Ch4_setPWMPulseLength(w);
	 return;
}

 /**
  * sets the pwm pulse width to the given value
  * @param span of time between 1000 and 2000 [탎]
  */
 void TIMER2_Ch1_setPWMPulseLength(u16 width)
{
	 TIM2_CCR1 = width;											//set compare value for channel 1
	 return;
}
 /**
  * sets the pwm pulse width to the given value
  * @param span of time between 1000 and 2000 [탎]
  */
 void TIMER2_Ch2_setPWMPulseLength(u16 width)
{
	 TIM2_CCR2 = width;											//set compare value for channel 2
	 return;
}

 /**
  * sets the pwm pulse width to the given value
  * @param span of time between 1000 and 2000 [탎]
  */
 void TIMER2_Ch3_setPWMPulseLength(u16 width)
{
	 TIM2_CCR3 = width;											//set compare value for channel 2
	 return;
}

 /**
  * sets the pwm pulse width to the given value
  * @param span of time between 1000 and 2000 [탎]
  */
 void TIMER2_Ch4_setPWMPulseLength(u16 width)
{
	 TIM2_CCR4 = width;											//set compare value for channel 2
	 return;
}

 u16 TIMER2_convertPositionToPulsewidth(s16 position){
	 if(position < -1000){position = -1000;}
	 if(position > 1000){position = 1000;}
	 u32 pulseWidth = 0;
	 if(position>=0){
		 pulseWidth = PWM_WIDTH_NEUTRAL +  ( ( (PWM_WIDTH_MAX-PWM_WIDTH_NEUTRAL)*((s32)position) )/1000);
	 }
	 else if(position<0){
		 pulseWidth = PWM_WIDTH_NEUTRAL +  ( ( (PWM_WIDTH_NEUTRAL-PWM_WIDTH_MIN)*((s32)position) )/1000);
	 }
	 return pulseWidth;
 }

