 /*************************************
 * stm32_afio.h
 * author: jan
 * last modifications:
 *
 * description:
 * Things to fix and to improve:
 * - TODO: test this NVIC module, e.g. register access.
 **************************************/

#ifndef STM32_NVIC_H_
#define STM32_NVIC_H_

class RCC;
/*Definitions************************************************/


/*Register structure******************************************/
typedef struct
{

}NVIC_RegisterStructure;

/*Peripheral class**********************************************/
class NVIC
{
	public:
		NVIC();		//constructor
		~NVIC(void);									//destructor
		void init();									//starts the NVIC
		NVIC_RegisterStructure* reg;					//pointer to the NVIC_RegisterStructure used to access the peripheral's hardware registers

};//eoc


/*Nested Vectored Interrupt Controller (NVIC) registers*/
#define NVIC_ISER_0_TO_31						(*((u32 *) (0xE000E100)))			//Interrupt 0-31 set-enable register
#define NVIC_ISER_32_TO_63						(*((u32 *) (0xE000E104)))			//Interrupt 32-63 set-enable register

#define NVIC_IPR_0_TO_3						     (*((u32 *) (0xE000E400)))			//Interrupt 0-3 priority register
#define NVIC_IPR_4_TO_7						     (*((u32 *) (0xE000E400)))			//Interrupt 4-7 priority register
#define NVIC_IPR_8_TO_11						 (*((u32 *) (0xE000E400)))			//Interrupt 8-11 priority register
#define NVIC_IPR_12_TO_15						 (*((u32 *) (0xE000E400)))			//Interrupt 12-15 priority register
#define NVIC_IPR_16_TO_19						 (*((u32 *) (0xE000E400)))			//Interrupt 16-19 priority register
#define NVIC_IPR_20_TO_23						 (*((u32 *) (0xE000E400)))			//Interrupt 20-23 priority register
#define NVIC_IPR_24_TO_27						 (*((u32 *) (0xE000E400)))			//Interrupt 24-27 priority register



#endif /* STM32_NVIC_H_ */
