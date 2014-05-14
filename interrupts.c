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



interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void)
{
  char data = UCA0RXBUF;

  switch(data){
   case 's': {
     int stuff[4] = {0x10, 0x11, 0x12, 0xFFFF};
     UARTSendArray(&stuff, 8);
     break;
   }
   default: {
     UARTSendArray("Unknown Command: ", 17);
     UARTSendArray(&data, 1);
     UARTSendArray("\n\r", 2);
     break;
   }
   }
}
