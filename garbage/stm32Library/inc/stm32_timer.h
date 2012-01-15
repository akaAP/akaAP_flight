 /*************************************
 * stm32_timer.h
 * author: jan
 * last modifications: 
 * 24.08.2009: created
 * description: 
 **************************************/

#ifndef STM32_TIMER_H_
#define STM32_TIMER_H_

#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_serv.h"
#include "stm32_rcc.h"
#include "stm32_gpio.h"
#include "stm32_usart.h"
#include "stm32_dma.h"
#include "stm32_adc.h"
#include "stm32_bits.h"

/*Definitions******************************/
/*Registers*/
/*************SysTick Timer*****************/
#define SYSTICK_CSR						(*((u32 *)(0xE000E010)))				//Systick control and status register
#define SYSTICK_RVR						(*((u32 *)(0xE000E014)))				//SysTick reload value register
#define SYSTICK_CVR						(*((u32 *)(0xE000E018)))				//Systick current value register
#define SYSTICK_CALVR					(*((u32 *)(0xE000E01C)))				//Systick calibration value register

/************general purpose timers TIMx****/
/*TIMER2*/
#define TIM2_CR1						(*((u16 *) (TIM2_BASE+0x00)))			//TIM2 control register 1
#define TIM2_CR2						(*((u16 *) (TIM2_BASE+0x04)))			//TIM2 control register 2
#define TIM2_SMCR						(*((u16 *) (TIM2_BASE+0x08)))			//TIM2 slave mode control register
#define TIM2_DIER						(*((u16 *) (TIM2_BASE+0x0C)))			//TIM2 DMA/interrupt enable register
#define TIM2_SR							(*((u16 *) (TIM2_BASE+0x10)))			//TIM2 status register
#define TIM2_EGR						(*((u16 *) (TIM2_BASE+0x14)))			//TIM2 event generation register
#define TIM2_CCMR1						(*((u16 *) (TIM2_BASE+0x18)))			//TIM2 capture/compare mode register 1
#define TIM2_CCMR2						(*((u16 *) (TIM2_BASE+0x1C)))			//TIM2 capture/compare mode register 2
#define TIM2_CCER						(*((u16 *) (TIM2_BASE+0x20)))			//TIM2 capture/compare enable register
#define TIM2_CNT						(*((u16 *) (TIM2_BASE+0x24)))			//TIM2 counter
#define TIM2_PSC						(*((u16 *) (TIM2_BASE+0x28)))			//TIM2 prescaler
#define TIM2_ARR						(*((u16 *) (TIM2_BASE+0x2C)))			//TIM2 auto-reload register
#define TIM2_CCR1						(*((u16 *) (TIM2_BASE+0x34)))			//TIM2 capture/compare register 1
#define TIM2_CCR2						(*((u16 *) (TIM2_BASE+0x38)))			//TIM2 capture/compare register 2
#define TIM2_CCR3						(*((u16 *) (TIM2_BASE+0x3C)))			//TIM2 capture/compare register 3
#define TIM2_CCR4						(*((u16 *) (TIM2_BASE+0x40)))			//TIM2 capture/compare register 4
#define TIM2_DCR						(*((u16 *) (TIM2_BASE+0x48)))			//TIM2 DMA control register
#define TIM2_DMAR						(*((u16 *) (TIM2_BASE+0x4C)))			//TIM2 DMA address for full transfer
/*TIMER 3*/
#define TIM3_CR1						(*((u16 *) (TIM3_BASE+0x00)))			//TIM3control register 1
#define TIM3_CR2						(*((u16 *) (TIM3_BASE+0x04)))			//TIM3control register 2
#define TIM3_SMCR						(*((u16 *) (TIM3_BASE+0x08)))			//TIM3slave mode control register
#define TIM3_DIER						(*((u16 *) (TIM3_BASE+0x0C)))			//TIM3DMA/interrupt enable register
#define TIM3_SR							(*((u16 *) (TIM3_BASE+0x10)))			//TIM3status register
#define TIM3_EGR						(*((u16 *) (TIM3_BASE+0x14)))			//TIM3event generation register
#define TIM3_CCMR1						(*((u16 *) (TIM3_BASE+0x18)))			//TIM3capture/compare mode register 1
#define TIM3_CCMR2						(*((u16 *) (TIM3_BASE+0x1C)))			//TIM3capture/compare mode register 2
#define TIM3_CCER						(*((u16 *) (TIM3_BASE+0x20)))			//TIM3capture/compare enable register
#define TIM3_CNT						(*((u16 *) (TIM3_BASE+0x24)))			//TIM3counter
#define TIM3_PSC						(*((u16 *) (TIM3_BASE+0x28)))			//TIM3prescaler
#define TIM3_ARR						(*((u16 *) (TIM3_BASE+0x2C)))			//TIM3auto-reload register
#define TIM3_CCR1						(*((u16 *) (TIM3_BASE+0x34)))			//TIM3capture/compare register 1
#define TIM3_CCR2						(*((u16 *) (TIM3_BASE+0x38)))			//TIM3capture/compare register 2
#define TIM3_CCR3						(*((u16 *) (TIM3_BASE+0x3C)))			//TIM3capture/compare register 3
#define TIM3_CCR4						(*((u16 *) (TIM3_BASE+0x40)))			//TIM3capture/compare register 4
#define TIM3_DCR						(*((u16 *) (TIM3_BASE+0x48)))			//TIM3DMA control register
#define TIM3_DMAR						(*((u16 *) (TIM3_BASE+0x4C)))			//TIM3DMA address for full transfer
/*TIMER4*/
#define TIM4_CR1						(*((u16 *) (TIM4_BASE+0x00)))			//TIM4 control register 1
#define TIM4_CR2						(*((u16 *) (TIM4_BASE+0x04)))			//TIM4 control register 2
#define TIM4_SMCR						(*((u16 *) (TIM4_BASE+0x08)))			//TIM4 slave mode control register
#define TIM4_DIER						(*((u16 *) (TIM4_BASE+0x0C)))			//TIM4 DMA/interrupt enable register
#define TIM4_SR							(*((u16 *) (TIM4_BASE+0x10)))			//TIM4 status register
#define TIM4_EGR						(*((u16 *) (TIM4_BASE+0x14)))			//TIM4 event generation register
#define TIM4_CCMR1						(*((u16 *) (TIM4_BASE+0x18)))			//TIM4 capture/compare mode register 1
#define TIM4_CCMR2						(*((u16 *) (TIM4_BASE+0x1C)))			//TIM4 capture/compare mode register 2
#define TIM4_CCER						(*((u16 *) (TIM4_BASE+0x20)))			//TIM4 capture/compare enable register
#define TIM4_CNT						(*((u16 *) (TIM4_BASE+0x24)))			//TIM4 counter
#define TIM4_PSC						(*((u16 *) (TIM4_BASE+0x28)))			//TIM4 prescaler
#define TIM4_ARR						(*((u16 *) (TIM4_BASE+0x2C)))			//TIM4 auto-reload register
#define TIM4_CCR1						(*((u16 *) (TIM4_BASE+0x34)))			//TIM4 capture/compare register 1
#define TIM4_CCR2						(*((u16 *) (TIM4_BASE+0x38)))			//TIM4 capture/compare register 2
#define TIM4_CCR3						(*((u16 *) (TIM4_BASE+0x3C)))			//TIM4 capture/compare register 3
#define TIM4_CCR4						(*((u16 *) (TIM4_BASE+0x40)))			//TIM4 capture/compare register 4
#define TIM4_DCR						(*((u16 *) (TIM4_BASE+0x48)))			//TIM4 DMA control register
#define TIM4_DMAR						(*((u16 *) (TIM4_BASE+0x4C)))			//TIM4 DMA address for full transfer

/************advanced-control timers ****/
/*TIMER 1*/
#define TIM1_CR1						(*((u16 *) (TIM1_BASE+0x00)))			//TIM1 control register 1
#define TIM1_CR2						(*((u16 *) (TIM1_BASE+0x04)))			//TIM1 control register 2
#define TIM1_SMCR						(*((u16 *) (TIM1_BASE+0x08)))			//TIM1 slave mode control register
#define TIM1_DIER						(*((u16 *) (TIM1_BASE+0x0C)))			//TIM1 DMA/interrupt enable register
#define TIM1_SR							(*((u16 *) (TIM1_BASE+0x10)))			//TIM1 status register
#define TIM1_EGR						(*((u16 *) (TIM1_BASE+0x14)))			//TIM1 event generation register
#define TIM1_CCMR1						(*((u16 *) (TIM1_BASE+0x18)))			//TIM1 capture/compare mode register 1
#define TIM1_CCMR2						(*((u16 *) (TIM1_BASE+0x1C)))			//TIM1 capture/compare mode register 2
#define TIM1_CCER						(*((u16 *) (TIM1_BASE+0x20)))			//TIM1 capture/compare enable register
#define TIM1_CNT						(*((u16 *) (TIM1_BASE+0x24)))			//TIM1 counter
#define TIM1_PSC						(*((u16 *) (TIM1_BASE+0x28)))			//TIM1 prescaler
#define TIM1_ARR						(*((u16 *) (TIM1_BASE+0x2C)))			//TIM1 auto-reload register
#define TIM1_RCR						(*((u16 *) (TIM1_BASE+0x30)))			//TIM1 repetition counter register
#define TIM1_CCR1						(*((u16 *) (TIM1_BASE+0x34)))			//TIM1 capture/compare register 1
#define TIM1_CCR2						(*((u16 *) (TIM1_BASE+0x38)))			//TIM1 capture/compare register 2
#define TIM1_CCR3						(*((u16 *) (TIM1_BASE+0x3C)))			//TIM1 capture/compare register 3
#define TIM1_CCR4						(*((u16 *) (TIM1_BASE+0x40)))			//TIM1 capture/compare register 4
#define TIM1_BDTR						(*((u16 *) (TIM1_BASE+0x44)))			//TIM1 break and dead-time register
#define TIM1_DCR						(*((u16 *) (TIM1_BASE+0x48)))			//TIM1 DMA control register
#define TIM1_DMAR						(*((u16 *) (TIM1_BASE+0x4C)))			//TIM1 DMA address for full transfer
/*TIMER 8*/
#define TIM8_CR1						(*((u16 *) (TIM8_BASE+0x00)))			//TIM8 control register 1
#define TIM8_CR2						(*((u16 *) (TIM8_BASE+0x04)))			//TIM8 control register 2
#define TIM8_SMCR						(*((u16 *) (TIM8_BASE+0x08)))			//TIM8 slave mode control register
#define TIM8_DIER						(*((u16 *) (TIM8_BASE+0x0C)))			//TIM8 DMA/interrupt enable register
#define TIM8_SR							(*((u16 *) (TIM8_BASE+0x10)))			//TIM8 status register
#define TIM8_EGR						(*((u16 *) (TIM8_BASE+0x14)))			//TIM8 event generation register
#define TIM8_CCMR1						(*((u16 *) (TIM8_BASE+0x18)))			//TIM8 capture/compare mode register 1
#define TIM8_CCMR2						(*((u16 *) (TIM8_BASE+0x1C)))			//TIM8 capture/compare mode register 2
#define TIM8_CCER						(*((u16 *) (TIM8_BASE+0x20)))			//TIM8 capture/compare enable register
#define TIM8_CNT						(*((u16 *) (TIM8_BASE+0x24)))			//TIM8 counter
#define TIM8_PSC						(*((u16 *) (TIM8_BASE+0x28)))			//TIM8 prescaler
#define TIM8_ARR						(*((u16 *) (TIM8_BASE+0x2C)))			//TIM8 auto-reload register
#define TIM8_RCR						(*((u16 *) (TIM8_BASE+0x30)))			//TIM8 repetition counter register
#define TIM8_CCR1						(*((u16 *) (TIM8_BASE+0x34)))			//TIM8 capture/compare register 1
#define TIM8_CCR2						(*((u16 *) (TIM8_BASE+0x38)))			//TIM8 capture/compare register 2
#define TIM8_CCR3						(*((u16 *) (TIM8_BASE+0x3C)))			//TIM8 capture/compare register 3
#define TIM8_CCR4						(*((u16 *) (TIM8_BASE+0x40)))			//TIM8 capture/compare register 4
#define TIM8_BDTR						(*((u16 *) (TIM8_BASE+0x44)))			//TIM8 break and dead-time register
#define TIM8_DCR						(*((u16 *) (TIM8_BASE+0x48)))			//TIM8 DMA control register
#define TIM8_DMAR						(*((u16 *) (TIM8_BASE+0x4C)))			//TIM8 DMA address for full transfer

/*Basic Timers******************************/
#define TIM6_CR1						(*((u16 *) (TIM6_BASE+0x00)))			//TIM6 control register 1
#define TIM6_CR2						(*((u16 *) (TIM6_BASE+0x04)))			//TIM6 control register 2
#define TIM6_DIER						(*((u16 *) (TIM6_BASE+0x0C)))			//TIM6 DMA/interrupt enable register
#define TIM6_SR							(*((u16 *) (TIM6_BASE+0x10)))			//TIM6 status register
#define TIM6_EGR						(*((u16 *) (TIM6_BASE+0x14)))			//TIM6 event generation register
#define TIM6_CNT						(*((u16 *) (TIM6_BASE+0x24)))			//TIM6 counter
#define TIM6_PSC						(*((u16 *) (TIM6_BASE+0x28)))			//TIM6 prescaler
#define TIM6_ARR						(*((u16 *) (TIM6_BASE+0x2C)))			//TIM6 auto-reload register

#define TIM7_CR1						(*((u16 *) (TIM8_BASE+0x00)))			//TIM7 control register 1
#define TIM7_CR2						(*((u16 *) (TIM8_BASE+0x04)))			//TIM7 control register 2
#define TIM7_DIER						(*((u16 *) (TIM8_BASE+0x0C)))			//TIM7 DMA/interrupt enable register
#define TIM7_SR							(*((u16 *) (TIM8_BASE+0x10)))			//TIM7 status register
#define TIM7_EGR						(*((u16 *) (TIM8_BASE+0x14)))			//TIM7 event generation register
#define TIM7_CNT						(*((u16 *) (TIM8_BASE+0x24)))			//TIM7 counter
#define TIM7_PSC						(*((u16 *) (TIM8_BASE+0x28)))			//TIM7 prescaler
#define TIM7_ARR						(*((u16 *) (TIM8_BASE+0x2C)))			//TIM7 auto-reload register


 /*Function Prototypes**********************/
/*TIMER 1**********/
void TIMER1_Init();
void TIMER1_forceUpdateEvent();
void TIMER1_clearBreakInterruptFlag(void);
void TIMER1_clearUpdateInterruptFlag(void);
void TIMER1_clearCaptureCompareInterruptFlag(u8 channel);
u8 TIMER1_getCaptureCompareInterruptSource(void);
u16 TIMER1_getCaptureValueOfChannel3(void);
void TIMER1_notifyOfUpdateEvent(void);
u16 TIMER1_getCaptureValueOfChannel1(void);
float TIMER1_getCounterUnit(void);
float TIMER1_getTimerTime(void);
//interrupt handler
void TIM1_UP_IRQhandler();
void TIM1_CC_IRQhandler();
/*TIMER 2**********/
void TIMER2_Init();
void TIMER2_Ch1_setServoPosition(s16);
void TIMER2_Ch2_setServoPosition(s16);
void TIMER2_Ch3_setServoPosition(s16);
void TIMER2_Ch4_setServoPosition(s16);

void TIMER2_Ch1_setPWMPulseLength(u16);
void TIMER2_Ch2_setPWMPulseLength(u16);
void TIMER2_Ch3_setPWMPulseLength(u16);
void TIMER2_Ch4_setPWMPulseLength(u16);
u16 TIMER2_convertPositionToPulsewidth(s16 position);
/* SysTick Timer**********/
void Init_SysTick(void);
u32 sysTick_getValue(void);


#endif /* STM32_TIMER_H_ */
