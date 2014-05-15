//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  interrupts.c
//      description:  interrupts for Device
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include "interrupts.h"

// === PRIVATE VARIABLES =====================================================

bool isLowBits = true;      //!< Used to tell interrupt what bits of the int
                            //!< Being transfered we are on
unsigned int combinedBits = 0;

// === GLOBAL INTERRUPTS =====================================================

//-----------------------------------------------------------------------------
//
//  PORT1_ISR
//! \brief   Description:  This is an interrupt for port1.
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
interrupt(PORT1_VECTOR) PORT1_ISR(void) {

  if((P1IFG & BTN) && !RoastStarted){

    LED_OUT |= LED1;

    P1IFG = P1IFG & ~BTN;

    InitRoast();

    UARTSendArray("Button Pushed\n", 14);

    //Disable the interrupt for TACCR0 match. We are now doing somethings
    TACCTL0 = ~(CCIE);

  }

} //PORT1_ISR

//-----------------------------------------------------------------------------
//
//  TIMERA0_ISR
//! \brief   Description:  This is an interrupt for Timer A0.
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {

  LED_OUT ^= LED1;

} //TIMERA0_ISR

//-----------------------------------------------------------------------------
//
//  USCI0RX_ISR
//! \brief   Description:  This is an interrupt for UART RX. It will interrupt
//!                        when a process is not happening
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void)
{
  char data = UCA0RXBUF;

  if(CurveSaveStarted){

    if(isLowBits){

      combinedBits = (unsigned int)data;

      isLowBits = false;

    }
    else{

      combinedBits |= (unsigned int)data << 8;

      if(combinedBits == 0xFFFF){

        CurveSaveStarted = false;

      }else{

        if(CurveOffset%(ERASE_BLOCK_SIZE/2) == 0){

          UARTSendArray("Eraseing the block", 18);
          FlashErase(CurentCurvePoint);
          //Enable the interrupt for TACCR0 match. We are now doing somethings
          //TACCTL0 = CCIE;
        }

        FlashProgram(CurentCurvePoint++, combinedBits);
        CurveOffset++;

      }

      isLowBits = true;

    }

  }
  else{

    switch(data){
     // Host wants to save a new curve to flash
     case 's': {
       // Respond with k char
       UARTSendArray("k", 1);
       CurveSaveStarted = true;
       CurentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;
       CurveOffset = 0;
       FlashErase(CurentCurvePoint);
       FlashErase(CurentCurvePoint + ERASE_BLOCK_SIZE);
       //Disable the interrupt for TACCR0 match. We are now doing somethings
       //TACCTL0 = ~(CCIE);
       break;
     }
     // Host wants to get a roast curve
     case 'g': {
       // Respond with k char
       UARTSendArray("k", 1);
       GetRoastCurve();
     }
     default: {
       UARTSendArray("Unknown Command: ", 17);
       UARTSendArray(&data, 1);
       UARTSendArray("\n\r", 2);
       break;
     }
     }
   }
} //USCI0RX_ISR
