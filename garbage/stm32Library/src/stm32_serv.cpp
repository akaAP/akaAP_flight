 /*************************************
 * stm32rbt6_serv.c
 * author: jan
 * last modifications: 
 * 
 * description: 
 **************************************/

 /*Includes*********************************/
#include "../inc/stm32_serv.h"
 /*Definitions******************************/
//indicates which I/O pin is connected to the status LED e.g. PB12 means GPIO Port B, Pin Nr. 12
#define STATUSLEDPIN PB12
 /*Functions********************************/

void toggle_statusLED(){
	//check pin state in GPIOC InputDataRegister
	if((GPIOC_IDR & BIT12) > 0){
	set_statusLED(ON);
	}
	else{
		set_statusLED(OFF);
	}
	return;
}

//TODO does 1 or 0 represent on-state?
void set_statusLED(u8 state)
{
	if (state==OFF)
		{
		GPIOC_BSRR |= BIT12;				//set GPIOC.12 to 1
		}
	else
		{
		GPIOC_BRR |= BIT12;					//reset GPIOC.12 to 0
		}
return;
}

void wait(u16 t)
{	t *= 100000;

	while(t>1){t--;}				//create a delay by decrementing t (t-1) times
}
void wait_millisec(u32 t)
{
	u32 startTime = RCC::systemTime_ms;						//use 1ms global system time
	while( (RCC::systemTime_ms - startTime) < t){}			//wait until t milliseconds have passed

	return;
}

/**
 * @brief returns the number of characters in string
 */
u16 stringlength(char *string)
{
	u16 length=0;
	while(string[length]!='\0')
	{
		length++;
	}
return length;
}//eof

/**
 * @brief returns TRUE if the given bit in the given 32-Bit register equals 1.
 * returns FALSE if the given bit in the given register equals 0
 * @tested function tested, works as expected
 */
boolean isBitSet(u32 registrum, u8 bitnumber){
		u32 mask = 1;
		mask = mask << bitnumber;
		if( (registrum & mask) > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
}//eof

/**
 * @brief sets the bit of the specified number[0,31] in the given 32-Bit register to 1.
 * @param u32* pointer to the register
 * @param u8 numebr of the bit to be set
 * TODO this function should be used only in e.g. initialization routines since it
 * need much more cycles than setting a bit in a direct way ("register |= BITx")
 */
void setBit(u32* registerAddress , u8 bitnumber){
	u32 mask = 1;
	mask = mask << bitnumber;
	*registerAddress |= mask;
}//eof

/**
 * @brief sets the bit of the specified number[0,31] in the given 32-Bit register to 0.
 * @param u32* pointer to the register
 * @param u8 number of the bit to be cleared
 * TODO this function should be used only in e.g. initialization routines since it
 * needs much more cycles than clearing a bit in a direct way ("register &= ~BITx")
 */
void clearBit(u32* registerAddress, u8 bitnumber){
	u32 mask = 1;
	mask = mask << bitnumber;
	*registerAddress &= ~mask;
}//eof
