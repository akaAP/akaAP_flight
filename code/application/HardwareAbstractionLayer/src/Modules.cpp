/*
 * \file modules.cpp
 * \author Jan
 *
 * \brief A Modules Object is a collection of software modules.
 */

#include "../inc/Modules.h"

// Definition of static members
Modules* Modules::backPointer;

// Method implementations

/**
 * \brief Constructor.
 */
Modules::Modules()
//:messagePort(USART3, 115200)
{
	Modules::backPointer = this;
}//eof

/**
 * \brief Destructor.
 */
Modules::~Modules()
{
}//eof
