 /*************************************
 * stm32_gpio.h
 * author: jan
 * last modifications: 
 * 
 * description:
 **************************************/

#ifndef STM32_GPIO_H_
#define STM32_GPIO_H_

//#include "../../CMSIS/Core/CM3/stm32f10x.h"

#include "stm32_memoryMap.h"
#include "stm32_bits.h"
#include "stm32_datatypes.h"
#include "stm32_rcc.h"
 /*Pin configuration******************************/
#include "stm32_gpio_conf.h"
 /*Definitions******************************/



/*Register structure******************************************/

typedef struct
{
	  vu32 CRL;
	  vu32 CRH;
	  vu32 IDR;
	  vu32 ODR;
	  vu32 BSRR;
	  vu32 BRR;
	  vu32 LCKR;
}GPIO_RegisterStructure;

/*peripheral class***************************************/
class GPIO
{
	public:
		GPIO(char gpioID);		//constructor
		~GPIO(void);									//destructor
		void init();									//starts the GPIO peripheral
		void configPin(u8 pinNumber, u8 behavior, u8 speed);
		GPIO_RegisterStructure* reg;					//pointer to the GPIO_RegisterStructure used to access the peripheral's hardware registers
		//bitmasks used to configure the GPIO pin's behaviour
		static const u8 behaviour_analog  	= 0b00;
		static const u8 behaviour_floating 	= 0b01;
		static const u8 behaviour_pullup 	= 0b10;
		static const u8 behaviour_gp_ppull 	= 0b00;
		static const u8 behaviour_gp_odrain = 0b01;
		static const u8 behaviour_af_ppull 	= 0b10;
		static const u8 behaviour_af_odrain = 0b11;
		//bitmasks used to configure the GPIO pin's max speed
		static const u8 speed_input 		= 0b00;
		static const u8 speed_MHZ2 			= 0b01;
		static const u8 speed_MHZ10 		= 0b10;
		static const u8 speed_MHZ50 		= 0b11;
};//eoc


//global GPIO objects; each one represents a peripheral****************
/*
extern GPIO GPIOA;
extern GPIO GPIOB;
extern GPIO GPIOC;
extern GPIO GPIOD;
extern GPIO GPIOE;
extern GPIO GPIOF;
extern GPIO GPIOG;
*/
/*GPIO Function Prototypes*************************************/


















/*GPIO Registers*/
/*PORT A*/
#define GPIOA_CRL 				  		(*((u32 *) (GPIOA_BASE+0x00)))		//configuration register low
#define GPIOA_CRH						(*((u32 *) (GPIOA_BASE+0x04)))		//configuration register high
#define GPIOA_IDR						(*((u32 *) (GPIOA_BASE+0x08)))		//port input data register
#define GPIOA_ODR						(*((u32 *) (GPIOA_BASE+0x0C)))		//port output data register
#define GPIOA_BSRR						(*((u32 *) (GPIOA_BASE+0x10)))		//port bit set/reset register
#define GPIOA_BRR						(*((u32 *) (GPIOA_BASE+0x14)))		//port bit reset register
#define GPIOA_LCKR						(*((u32 *) (GPIOA_BASE+0x18)))		//port configuration lock register
/*PORT B*/
#define GPIOB_CRL 				  		(*((u32 *) (GPIOB_BASE+0x00)))		//configuration register low
#define GPIOB_CRH						(*((u32 *) (GPIOB_BASE+0x04)))		//configuration register high
#define GPIOB_IDR						(*((u32 *) (GPIOB_BASE+0x08)))		//port input data register
#define GPIOB_ODR						(*((u32 *) (GPIOB_BASE+0x0C)))		//port output data register
#define GPIOB_BSRR						(*((u32 *) (GPIOB_BASE+0x10)))		//port bit set/reset register
#define GPIOB_BRR						(*((u32 *) (GPIOB_BASE+0x14)))		//port bit reset register
#define GPIOB_LCKR						(*((u32 *) (GPIOB_BASE+0x18)))		//port configuration lock register
/*PORT C*/
#define GPIOC_CRL 				  		(*((u32 *) (GPIOC_BASE+0x00)))		//configuration register low
#define GPIOC_CRH						(*((u32 *) (GPIOC_BASE+0x04)))		//configuration register high
#define GPIOC_IDR						(*((u32 *) (GPIOC_BASE+0x08)))		//port input data register
#define GPIOC_ODR						(*((u32 *) (GPIOC_BASE+0x0C)))		//port output data register
#define GPIOC_BSRR						(*((u32 *) (GPIOC_BASE+0x10)))		//port bit set/reset register
#define GPIOC_BRR						(*((u32 *) (GPIOC_BASE+0x14)))		//port bit reset register
#define GPIOC_LCKR						(*((u32 *) (GPIOC_BASE+0x18)))		//port configuration lock register

/*PORT D*/
#define GPIOD_CRL 				  		(*((u32 *) (GPIOD_BASE+0x00)))		//configuration register low
#define GPIOD_CRH						(*((u32 *) (GPIOD_BASE+0x04)))		//configuration register high
#define GPIOD_IDR						(*((u32 *) (GPIOD_BASE+0x08)))		//port input data register
#define GPIOD_ODR						(*((u32 *) (GPIOD_BASE+0x0C)))		//port output data register
#define GPIOD_BSRR						(*((u32 *) (GPIOD_BASE+0x10)))		//port bit set/reset register
#define GPIOD_BRR						(*((u32 *) (GPIOD_BASE+0x14)))		//port bit reset register
#define GPIOD_LCKR						(*((u32 *) (GPIOD_BASE+0x18)))		//port configuration lock register
/*PORT E*/
#define GPIOE_CRL 				  		(*((u32 *) (GPIOE_BASE+0x00)))		//configuration register low
#define GPIOE_CRH						(*((u32 *) (GPIOE_BASE+0x04)))		//configuration register high
#define GPIOE_IDR						(*((u32 *) (GPIOE_BASE+0x08)))		//port input data register
#define GPIOE_ODR						(*((u32 *) (GPIOE_BASE+0x0C)))		//port output data register
#define GPIOE_BSRR						(*((u32 *) (GPIOE_BASE+0x10)))		//port bit set/reset register
#define GPIOE_BRR						(*((u32 *) (GPIOE_BASE+0x14)))		//port bit reset register
#define GPIOE_LCKR						(*((u32 *) (GPIOE_BASE+0x18)))		//port configuration lock register
/*PORT F*/
#define GPIOF_CRL 				  		(*((u32 *) (GPIOF_BASE+0x00)))		//configuration register low
#define GPIOF_CRH						(*((u32 *) (GPIOF_BASE+0x04)))		//configuration register high
#define GPIOF_IDR						(*((u32 *) (GPIOF_BASE+0x08)))		//port input data register
#define GPIOF_ODR						(*((u32 *) (GPIOF_BASE+0x0C)))		//port output data register
#define GPIOF_BSRR						(*((u32 *) (GPIOF_BASE+0x10)))		//port bit set/reset register
#define GPIOF_BRR						(*((u32 *) (GPIOF_BASE+0x14)))		//port bit reset register
#define GPIOF_LCKR						(*((u32 *) (GPIOF_BASE+0x18)))		//port configuration lock register
/*PORT G*/
#define GPIOG_CRL 				  		(*((u32 *) (GPIOG_BASE+0x00)))		//configuration register low
#define GPIOG_CRH						(*((u32 *) (GPIOG_BASE+0x04)))		//configuration register high
#define GPIOG_IDR						(*((u32 *) (GPIOG_BASE+0x08)))		//port input data register
#define GPIOG_ODR						(*((u32 *) (GPIOG_BASE+0x0C)))		//port output data register
#define GPIOG_BSRR						(*((u32 *) (GPIOG_BASE+0x10)))		//port bit set/reset register
#define GPIOG_BRR						(*((u32 *) (GPIOG_BASE+0x14)))		//port bit reset register
#define GPIOG_LCKR						(*((u32 *) (GPIOG_BASE+0x18)))		//port configuration lock register


 /*Function Prototypes********************/
void GPIOA_Init(void);
void GPIOB_Init(void);
void GPIOC_Init(void);
void GPIOD_Init(void);
void GPIOE_Init(void);
void GPIOF_Init(void);
void GPIOG_Init(void);

void set_GPIOC_10(u8 state);

#endif /* STM32_GPIO_H_ */
