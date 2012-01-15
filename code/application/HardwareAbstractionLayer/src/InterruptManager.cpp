/**
 *\file InterruptHandler.cpp
 *\brief Please provide all information necessary for understanding the code here.
 *\author Jan
*/

//Inclusions
#include "../inc/InterruptManager.h"

/**
 * Constructor, is private.
 */
InterruptManager::InterruptManager()
{
}//eof

/**
 * Destructor, is private.
 */
InterruptManager::~InterruptManager()
{
}//eof

/**
 * Inserts a given function pointer into the interrupt vector table.
 * The interrupt ID specifies at which interrupt the given function
 * is supposed to be invoked. Take one of the IDs provided as static
 * members of the InterruptManager class.
 * FIXME Takes for granted that the vector table is located at the very beginning of SRAM;
 * should check the SCB->VTOR register first to check whether the vector table
 * is in flash or RAM and if there is an offset.
 */
void InterruptManager::registerInterruptHandler(void(*interruptHandler)(), uint32_t interruptID)
{
	// Put address of interrupt handler function into the vector table. The address of
	// the appropriate interrupt vector in the table is given by the
	// interrupt ID
	uint32_t* ptr = (uint32_t*)interruptID;
	*ptr = (uint32_t)(interruptHandler);
}//eof
