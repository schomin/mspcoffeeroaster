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

interrupt(PORT1_VECTOR) PORT1_ISR(void) {

  if((P1IFG & BTN)){

    LED_OUT |= LED1;

    P1IFG = P1IFG & ~BTN;

    UARTSendArray("Test", 4);

    InitRoast();

    //Disable the interrupt for TACCR0 match. We are now doing somethings
    TACCTL0 = ~(CCIE);

  }

}

interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {

  LED_OUT ^= LED1;

}
