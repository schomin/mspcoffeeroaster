//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roast.h
//      description:  header file toInitialize the roast process
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "utilities.h"

// === GLOBAL VARIABLES ======================================================

extern bool RoastStarted;	//!< Variable to track when roast has started

// === FUNCTION PROTOTYPES ===================================================

void InitRoast( void );
void StartRoast( void );
