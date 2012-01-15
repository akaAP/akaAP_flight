/*
 * \file CANTest.c
 * \brief Please give a short description of the file's purpose and content.
 * \author Jan
 */

// Programm:        CAN Funktionen
//                  Achtung! KEINE GLEICHZEITIGE NUTZUNG MIT USB MÖGLICH!!!
// Mikrocontroller: STM32F103RE
// Speicher:        512KB FLASH, 64KB SRAM
// Taktfrequenz:    8MHz, PLL: 72MHz

// System-Inlude
#include <stddef.h>

#include <string.h>             // Stringfunktion
#include <stdio.h>              // Standardfunktion
#include <stdlib.h>             // Standardbibliothek

#include "../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/stm32f10x.h"
#include "../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_can.h"
#include "../inc/serviceFunctions.h"
#include "../inc/InterruptManager.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/deviceDriver_LED_CPP.h"
#include "../../HardwareAbstractionLayer/deviceDrivers/inc/devices.h"

#include "../inc/CANTest.h"
//***********************************************************************************************
// CAN Initialisierung
//***********************************************************************************************
void init_can (void) {
  CAN_InitTypeDef       CAN_InitStructure;
  CAN_FilterInitTypeDef CAN_FilterInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  // CAN RX0 Interrupt
  InterruptManager::registerInterruptHandler(&USB_LP_CAN1_RX0_IRQHandler_cute, InterruptManager::USB_LP_CAN1_RX0_IRQHandler);
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);



  // CAN1 Periph clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);          // CAN1 Takt freigeben
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);          // AFIO Takt freigeben (für Remapping)
	/* GPIO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

  // PB8 als GPIO_Mode_IPU, PB9 als GPIO_Mode_AF_PP definiert (50MHz!)
  // Remapping CANRX und CANTX von PA11 und PA12 auf PB8 und PB9
  // (PA11/12 sind die USB-Pins)
  // GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

	/* Configure CAN pin: RX */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure CAN pin: TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // CAN Register init
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  // CAN cell init
  CAN_InitStructure.CAN_TTCM=DISABLE;
  CAN_InitStructure.CAN_ABOM=DISABLE;
  CAN_InitStructure.CAN_AWUM=DISABLE;
  // No automatic retransmission;
  CAN_InitStructure.CAN_NART=ENABLE;
  CAN_InitStructure.CAN_RFLM=DISABLE;
  CAN_InitStructure.CAN_TXFP=DISABLE;
 // CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

  // CAN Bitrate
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;    // SJW (1 bis 4 möglich)
  CAN_InitStructure.CAN_BS1=CAN_BS1_12tq;   // Samplepoint 72%
  CAN_InitStructure.CAN_BS2=CAN_BS2_5tq;    // Samplepoint 72%

  //CAN_InitStructure.CAN_Prescaler=1;        // 2000 kbit/s
  //CAN_InitStructure.CAN_Prescaler=2;        // 1000 kbit/s
  //CAN_InitStructure.CAN_Prescaler=4;        //  500 kbit/s
  //CAN_InitStructure.CAN_Prescaler=5;        //  400 kbit/s
  //CAN_InitStructure.CAN_Prescaler=8;        //  250 kbit/s
  //CAN_InitStructure.CAN_Prescaler=10;       //  200 kbit/s
  //CAN_InitStructure.CAN_Prescaler=16;       //  125 kbit/s
  CAN_InitStructure.CAN_Prescaler=20;       //  100 kbit/s
  //CAN_InitStructure.CAN_Prescaler=40;       //   50 kbit/s
  //CAN_InitStructure.CAN_Prescaler=80;       //   40 kbit/s
  //CAN_InitStructure.CAN_Prescaler=200;      //   10 kbit/s
  //CAN_InitStructure.CAN_Prescaler=1023;      //    ganz langsam

  CAN_Init(CAN1, &CAN_InitStructure);

  // CAN filter init
  CAN_FilterInitStructure.CAN_FilterNumber=1;
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  // CAN FIFO0 message pending interrupt enable
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

//***********************************************************************************************
// CAN Message senden
//***********************************************************************************************
void can_send_test (void) {
  uint8_t CanMailBox;
  uint8_t CanTxStatus;

 // printf_tft(1,60,"CAN Test: Senden einer Message");
   CanTxMsg CanTxMessage;

  // CAN Message senden
  CanTxMessage.StdId=0x00;
  CanTxMessage.ExtId=0x1234;
  CanTxMessage.IDE=CAN_ID_EXT;
  CanTxMessage.RTR=CAN_RTR_DATA;
  CanTxMessage.DLC=3;
  CanTxMessage.Data[0] = 'P';
  CanTxMessage.Data[1] = 'R';
  CanTxMessage.Data[2] = 'O';
  CanMailBox = CAN_Transmit(CAN1, &CanTxMessage);   // Rückgabe Mailbox-Nr. 0,1,3 (4=keine Mailbox frei)
  if (CanMailBox == CAN_NO_MB) {
    // Mailboxen voll mit ungesendeten Messages
//    printf_tft(1,75,"--> keine Mailbox frei");
  } else {
    // Mailbox verfügbar
    // Sendevorgang läuft
//    sprintf(tft.buffer,"--> Mailbox-Nr.: %u",CanMailBox);
//    printf_tft(1,75,tft.buffer);
    while(1) {

      CanTxStatus = CAN_TransmitStatus(CAN1, CanMailBox);   // Rückgabe 0=Fehler, 1=ok, 2=senden läuft noch

//      sprintf(tft.buffer,"--> TxStatus: %u",CanTxStatus);
//      printf_tft(1,90,tft.buffer);
      if (CanTxStatus == CANTXPENDING) {
        // Message Sendevorgang läuft gerade
 //       printf_tft(1,105,"--> Sendevorgang aktiv!");

//        sprintf(tft.buffer,"EWG:%u EPV:%u BOF:%u TEC:%u",CAN_GetFlagStatus(CAN1, CAN_FLAG_EWG),CAN_GetFlagStatus(CAN1, CAN_FLAG_EPV), CAN_GetFlagStatus(CAN1, CAN_FLAG_BOF), (uint16_t)(CAN1->ESR >> 16) & 0x000000FF);
//        printf_tft(1,120,tft.buffer);
    //	  break;

      }
      if (CanTxStatus == CANTXFAILE) { // CANTXFAILED bis V3.4.0 - V3.5.0 dann CANTXFAILE

        // Fehler Message nicht gesendet
   //     printf_tft(1,135,"--> Senden nicht erfolgreich");
        break;
      }
      if (CanTxStatus == CANTXOK) {


        // Message gesendet und bestätigt
     //   printf_tft(1,135,"--> Senden OK");
        break;
      }
    }
  }
  return;
}

// Interrupt Handler
/*******************************************************************************
* USB_LP_CAN1_RX0_IRQHandler
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler_cute(void) {

  if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) == SET) {
    // CAN Fifo0 Receive
    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
  }
  if (CAN_GetITStatus(CAN1, CAN_IT_FOV0) == SET) {
    // CAN Fifo0 Receive Overrun
    CAN_ClearITPendingBit(CAN1, CAN_IT_FOV0);
  }
  if (CAN_GetITStatus(CAN1, CAN_IT_FF0) == SET) {
    // CAN Fifo0 Receive Buffer full
    CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
  }
  CanRxMsg CanRxMessage;
  CAN_Receive(CAN1, CAN_FIFO0, &CanRxMessage);
	Devices::backPointer->statusLED.toggle();

  // if((CanRxMessage.ExtId==0x1234) && (CanRxMessage.IDE==CAN_ID_EXT) && (CanRxMessage.DLC==3)) {
  //  CanRxReady = 1;
  // }

}
