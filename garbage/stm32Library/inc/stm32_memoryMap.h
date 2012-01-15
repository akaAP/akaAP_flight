 /*************************************
 * stm32_memoryMap.h
 * author: jan
 * last modifications:
 * description: TODO
 **************************************/

#ifndef STM32_MEMORYMAP_H_
#define STM32_MEMORYMAP_H_

#include "stm32_datatypes.h"

/* Exported types ------------------------------------------------------------*/
/******************************************************************************/
/*                         Peripheral registers structures                    */
/******************************************************************************/


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
#define SRAM_BASE             ((u32)0x20000000)
#define PERIPH_BASE           ((u32)0x40000000)

/* Flash registers base address */
#define FLASH_BASE            ((u32)0x40022000)
/* Flash Option Bytes base address */
#define OB_BASE               ((u32)0x1FFFF800)

/* Peripheral memory map */
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0xOC00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define USART4_BASE           (APB1PERIPH_BASE + 0x4C00)
#define USART5_BASE           (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE             (APB1PERIPH_BASE + 0x6800)
#define BKP_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE    		  (APB1PERIPH_BASE + 0x7400)

#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define TIM8_Base			  	  (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define ADC3_BASE             (APB2PERIPH_BASE + 0x3C00)
#define SDIO_BASE             (APB2PERIPH_BASE + 0x8000)

#define DMA1_BASE              (AHBPERIPH_BASE + 0x0000)
#define DMA2_BASE              (AHBPERIPH_BASE + 0x0400)
#define RCC_BASE               (AHBPERIPH_BASE + 0x1000)
#define CRC_BASE       	       (AHPBPERIPH_BASE + 0x3000)


/* System Control Space memory map */
#define SCS_BASE              ((u32)0xE000E000)

#define SysTick_BASE          (SCS_BASE + 0x0010)
#define NVIC_BASE             (SCS_BASE + 0x0100)
#define SCB_BASE              (SCS_BASE + 0x0D00)

/******************************************************************************
 *       Adresses of word registers in the alias region connected to
 *       register bits in the bit-band region
 ******************************************************************************/
/* Peripheral and SRAM base address in the alias region */
#define PERIPH_BASE_ALIAS		((u32)0x42000000)
#define SRAM__BASE_ALIAS		((u32)0x22000000)
/******************************************************************************/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */




#endif /* STM32_MEMORYMAP_H */

