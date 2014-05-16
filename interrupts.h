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
#include "roastcurve.h"
#include "roast.h"
#include "uart.h"
#include "flash.h"

// === DEFINES ===============================================================

// === GLOBAL VARIABLES ======================================================

// === INTERRUPT PROTOTYPES ==================================================

interrupt(PORT1_VECTOR) PORT1_ISR(void);
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void);
