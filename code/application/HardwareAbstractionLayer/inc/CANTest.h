/*
 * \file CANTest.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef CANTEST_H_
#define CANTEST_H_



//Function prototypes
void init_can (void);
void can_send_test (void);
void USB_LP_CAN1_RX0_IRQHandler_cute(void);

#endif /* CANTEST_H_ */
