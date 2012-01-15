 /*************************************
 * \file TxMailbox.cpp
 * \brief 	Transmission Mailbox class used by SerialPOrt.
 *
 * \author: jan bolting
 *
 *
 **************************************/

#include "../inc/TxMailbox.h"

/**
 * Constructor.
 */
TxMailbox::TxMailbox(){
	//initialize members
	this->indexOfNextWrite = 0;
	this->number = 0;
	this->numberOfDataToBeSent = 0;
	this->wantsToBeSent = 0;
}//eof

/**
 * Destructor.
 */
TxMailbox::~TxMailbox(){

}//eof
