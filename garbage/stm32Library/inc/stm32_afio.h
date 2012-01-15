 /*************************************
 * stm32_afio.h
 * author: jan
 * last modifications: 
 * 
 * description:
 * Things to fix and to improve:
 * - TODO: test this AFIO module, e.g. register access
 **************************************/

#ifndef STM32_AFIO_H_
#define STM32_AFIO_H_

#include "stm32_datatypes.h"
#include "stm32_bits.h"
#include "stm32_memoryMap.h"

/*Definitions************************************************/

/*Register structure******************************************/
typedef struct
{
	  vu32 EVCR;		//event control register
	  vu32 MAPR;		//AF remap and debug I/O configuration register
	  vu32 EXTICR1;		//external interrupt configuration register 1
	  vu32 EXTICR2;		//external interrupt configuration register 2
	  vu32 EXTICR3;		//external interrupt configuration register 3
	  vu32 EXTICR4;		//external interrupt configuration register 4
}AFIO_RegisterStructure;

/*Peripheral class**********************************************/
class AFIO
{
	public:
		AFIO();		//constructor
		~AFIO(void);									//destructor
		void init();									//starts the AFIO peripheral
		AFIO_RegisterStructure* reg;					//pointer to the AFIO_RegisterStructure used to access the peripheral's hardware registers

};//eoc

/*Declarations************************************************/
extern AFIO AFIO1;

 /*Function Prototypes*****************************************/

#endif /* AFIO_H_ */
