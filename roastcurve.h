//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roastcurve.h
//      description:  header file for the roast curve
//  original author:  Andrew Schomin
//    creation date:  05-14-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "utilities.h"
#include "deviceinit.h"
#include "uart.h"
#include "flash.h"

// === GLOBAL VARIABLES ======================================================


// === FUNCTION PROTOTYPES ===================================================

void GetRoastCurve( void );
