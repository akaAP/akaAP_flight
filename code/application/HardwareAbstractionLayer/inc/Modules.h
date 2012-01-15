/*
 * \file modules.h
 *
 * \author Jan
 */

#ifndef MODULES_H_
#define MODULES_H_

#include "serialPort.h"
#include "timebase.h"

//structure declarations
class Modules{
	public:
		Modules();
		~Modules();
		static Modules* backPointer;
	//	SerialPort messagePort;				// a USART port to send status and debug messages
};

#endif /* MODULES_H_ */
