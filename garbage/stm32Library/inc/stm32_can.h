
/*!\file stm32_can.h
 * \brief -brief description-
 *
 * -detailed description-
 * created: 13.06.2010
 */

#ifndef STM32_CAN_H_
#define STM32_CAN_H_

 /*Include*********************************/
//#include "../../CMSIS/Core/CM3/stm32f10x.h"

#include "stm32_bits.h"
#include "stm32_memoryMap.h"
#include "stm32_datatypes.h"
#include "stm32_rcc.h"
#include "stm32_dma.h"
#include "stm32_serv.h"
#include "stm32_usart.h"
#include "stm32_timer.h"
 /*Definitions******************************/
//CAN1 control and status registers
#define CAN1_MCR						(*((u32 *) (CAN1_BASE+0x00)))			//CAN1 master control register
#define CAN1_MSR						(*((u32 *) (CAN1_BASE+0x04)))			//CAN1 master status register
#define CAN1_TSR						(*((u32 *) (CAN1_BASE+0x08)))			//CAN1 transmit status register
#define CAN1_RF0R						(*((u32 *) (CAN1_BASE+0x0C)))			//CAN1 receive FIFO 0 register
#define CAN1_RF1R						(*((u32 *) (CAN1_BASE+0x10)))			//CAN1 receive FIFO 1 register
#define CAN1_IER						(*((u32 *) (CAN1_BASE+0x14)))			//CAN1 interrupt enable register
#define CAN1_ESR						(*((u32 *) (CAN1_BASE+0x18)))			//CAN1 error status register
#define CAN1_BTR						(*((u32 *) (CAN1_BASE+0x1C)))			//CAN1 bit timing register
//CAN1 mailbox registers
#define CAN1_TI0R						(*((u32 *) (CAN1_BASE+0x180)))			//CAN1 mailbox identifier register 0
#define CAN1_TI1R						(*((u32 *) (CAN1_BASE+0x190)))			//CAN1 mailbox identifier register 1
#define CAN1_TI2R						(*((u32 *) (CAN1_BASE+0x1A0)))			//CAN1 mailbox identifier register 2

#define CAN1_TDT0R						(*((u32 *) (CAN1_BASE+0x184)))			//CAN1 mailbox data length and time stamp register 0
#define CAN1_TDT1R						(*((u32 *) (CAN1_BASE+0x194)))			//CAN1 mailbox data length and time stamp register 1
#define CAN1_TDT2R						(*((u32 *) (CAN1_BASE+0x1A4)))			//CAN1 mailbox data length and time stamp register 2

#define CAN1_TDL0R						(*((u32 *) (CAN1_BASE+0x188)))			//CAN1 mailbox data low register 0
#define CAN1_TDL1R						(*((u32 *) (CAN1_BASE+0x198)))			//CAN1 mailbox data low register 1
#define CAN1_TDL2R						(*((u32 *) (CAN1_BASE+0x1A8)))			//CAN1 mailbox data low register 2

#define CAN1_TDH0R						(*((u32 *) (CAN1_BASE+0x18C)))			//CAN1 mailbox data high register 0
#define CAN1_TDH1R						(*((u32 *) (CAN1_BASE+0x19C)))			//CAN1 mailbox data high register 1
#define CAN1_TDH2R						(*((u32 *) (CAN1_BASE+0x1AC)))			//CAN1 mailbox data high register 2

#define CAN1_RI0R						(*((u32 *) (CAN1_BASE+0x1B0)))			//CAN1 receive FIFO mailbox identifier register 0
#define CAN1_RI1R						(*((u32 *) (CAN1_BASE+0x1C0)))			//CAN1 receive FIFO mailbox identifier register 1

#define CAN1_RDT0R						(*((u32 *) (CAN1_BASE+0x1B4)))			//CAN1 receive FIFO mailbox data length and time stamp register 0
#define CAN1_RDT1R						(*((u32 *) (CAN1_BASE+0x1C4)))			//CAN1 receive FIFO mailbox data length and time stamp register 1

#define CAN1_RDL0R						(*((u32 *) (CAN1_BASE+0x1B8)))			//CAN1 receive FIFO mailbox data low register 0
#define CAN1_RDL1R						(*((u32 *) (CAN1_BASE+0x1C8)))			//CAN1 receive FIFO mailbox data low register 1

#define CAN1_RDH0R						(*((u32 *) (CAN1_BASE+0x1BC)))			//CAN1 receive FIFO mailbox data high register 0
#define CAN1_RDH1R						(*((u32 *) (CAN1_BASE+0x1CC)))			//CAN1 receive FIFO mailbox data high register 1
//CAN1 filter registers
#define CAN1_FMR						(*((u32 *) (CAN1_BASE+0x200)))			//CAN1 filter master register
#define CAN1_FM1R						(*((u32 *) (CAN1_BASE+0x204)))			//CAN1 filter mode register
#define CAN1_FS1R						(*((u32 *) (CAN1_BASE+0x20C)))			//CAN1 filter scale register
#define CAN1_FFA1R						(*((u32 *) (CAN1_BASE+0x214)))			//CAN1 filter FIFO assignment register
#define CAN1_FA1R						(*((u32 *) (CAN1_BASE+0x21C)))			//CAN1 filter activation register
//filter bank registers
#define CAN1_FILTER_BANK_BASE			(CAN1_BASE+0x240)						//address where the CAN1 filter bank registers begin

#define CAN1_F0R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+0*4)))			//CAN1 Filter bank 0 register 1
#define CAN1_F0R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+1*4)))			//CAN1 Filter bank 0 register 2

#define CAN1_F1R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+2*4)))			//CAN1 Filter bank 1 register 1
#define CAN1_F1R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+3*4)))			//CAN1 Filter bank 1 register 2

#define CAN1_F2R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+4*4)))			//CAN1 Filter bank 2 register 1
#define CAN1_F2R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+5*4)))			//CAN1 Filter bank 2 register 2

#define CAN1_F3R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+6*4))				//CAN1 Filter bank 3 register 1
#define CAN1_F3R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+7*4)))			//CAN1 Filter bank 3 register 2

#define CAN1_F4R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+8*4)))			//CAN1 Filter bank 4 register 1
#define CAN1_F4R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+9*4)))			//CAN1 Filter bank 4register 2

#define CAN1_F5R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+10*4)))			//CAN1 Filter bank 5 register 1
#define CAN1_F5R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+11*4)))			//CAN1 Filter bank 5 register 2

#define CAN1_F6R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+12*4)))			//CAN1 Filter bank 6 register 1
#define CAN1_F6R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+13*4)))			//CAN1 Filter bank 6 register 2

#define CAN1_F7R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+14*4)))			//CAN1 Filter bank 7 register 1
#define CAN1_F7R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+15*4)))			//CAN1 Filter bank 7 register 2

#define CAN1_F8R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+16*4)))			//CAN1 Filter bank 8 register 1
#define CAN1_F8R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+17*4)))			//CAN1 Filter bank 8 register 2

#define CAN1_F9R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+18*4)))			//CAN1 Filter bank 9 register 1
#define CAN1_F9R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+19*4)))			//CAN1 Filter bank 9 register 2

#define CAN1_F10R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+20*4)))			//CAN1 Filter bank 10 register 1
#define CAN1_F10R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+21*4)))			//CAN1 Filter bank 10 register 2

#define CAN1_F11R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+22*4)))			//CAN1 Filter bank 11 register 1
#define CAN1_F11R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+23*4)))			//CAN1 Filter bank 11 register 2

#define CAN1_F12R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+24*4)))			//CAN1 Filter bank 12 register 1
#define CAN1_F12R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+25*4)))			//CAN1 Filter bank 12 register 2

#define CAN1_F13R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+26*4)))			//CAN1 Filter bank 13 register 1
#define CAN1_F13R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+27*4)))			//CAN1 Filter bank 13 register 2

#define CAN1_F14R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+28*4)))			//CAN1 Filter bank 14 register 1
#define CAN1_F14R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+29*4)))			//CAN1 Filter bank 14 register 2

#define CAN1_F15R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+30*4)))			//CAN1 Filter bank 15 register 1
#define CAN1_F15R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+31*4)))			//CAN1 Filter bank 15 register 2

#define CAN1_F16R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+32*4)))			//CAN1 Filter bank 16 register 1
#define CAN1_F16R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+33*4)))			//CAN1 Filter bank 16 register 2

#define CAN1_F17R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+34*4)))			//CAN1 Filter bank 17 register 1
#define CAN1_F17R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+35*4)))			//CAN1 Filter bank 17 register 2

#define CAN1_F18R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+36*4)))			//CAN1 Filter bank 18 register 1
#define CAN1_F18R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+37*4)))			//CAN1 Filter bank 18 register 2

#define CAN1_F19R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+38*4)))			//CAN1 Filter bank 19 register 1
#define CAN1_F19R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+39*4)))			//CAN1 Filter bank 19 register 2

#define CAN1_F20R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+40*4)))			//CAN1 Filter bank 20 register 1
#define CAN1_F20R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+41*4)))			//CAN1 Filter bank 20 register 2

#define CAN1_F21R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+42*4)))			//CAN1 Filter bank 21 register 1
#define CAN1_F21R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+43*4)))			//CAN1 Filter bank 21 register 2

#define CAN1_F22R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+44*4)))			//CAN1 Filter bank 22 register 1
#define CAN1_F22R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+45*4)))			//CAN1 Filter bank 22 register 2

#define CAN1_F23R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+46*4)))			//CAN1 Filter bank 23 register 1
#define CAN1_F23R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+47*4)))			//CAN1 Filter bank 23 register 2

#define CAN1_F24R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+48*4)))			//CAN1 Filter bank 24 register 1
#define CAN1_F24R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+49*4)))			//CAN1 Filter bank 24 register 2

#define CAN1_F25R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+50*4)))			//CAN1 Filter bank 25 register 1
#define CAN1_F25R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+51*4)))			//CAN1 Filter bank 25 register 2

#define CAN1_F26R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+52*4)))			//CAN1 Filter bank 26 register 1
#define CAN1_F26R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+53*4)))			//CAN1 Filter bank 26 register 2

#define CAN1_F27R1						(*((u32 *) (CAN1_FILTER_BANK_BASE+54*4)))			//CAN1 Filter bank 27 register 1
#define CAN1_F27R2						(*((u32 *) (CAN1_FILTER_BANK_BASE+55*4)))			//CAN1 Filter bank 27 register 2

 /*Functions********************************/
void CAN1_Init(void);
void CAN1_SendMessage(u16 identifier,  char* payloadBytes, u8 numberOfPayloadBytes);

#endif /* STM32_CAN_H_ */
