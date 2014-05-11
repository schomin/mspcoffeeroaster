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

  LED_OUT |= LED1;

  //Disable the interrupt for TACCR0 match
  TACCTL0 = ~(CCIE);

}

interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {

  LED_OUT ^= LED1;

}
