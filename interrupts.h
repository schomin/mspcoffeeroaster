//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  interrupts.h
//      description:  Header file for Device interrupts
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>
#include "deviceinit.h"

// === DEFINES ===============================================================

// === GLOBAL VARIABLES =====================================================

// === FUNCTION PROTOTYPES ==================================================

interrupt(PORT1_VECTOR) PORT1_ISR(void);
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void);
