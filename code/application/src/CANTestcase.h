/*
 * \file CANTestcase.h
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

#ifndef CANTESTCASE_H_
#define CANTESTCASE_H_

class CANTestcase{
public:
	CANTestcase();
	~CANTestcase();
	void sendTestMessageInALoop();
private:
	void setUp();
	void toggleLED();
	void toggleCANTx();
};

#endif /* CANTESTCASE_H_ */
