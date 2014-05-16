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
#include "roastcurve.h"
#include "peripherals.h"

// === STRUCTURES ============================================================

struct ST_RoastScenario
{
  //!< This is a struct that will hold a number of thresholds and how to adjust
  //!< the peripherals accordingly for a scenario
  unsigned char TemperatureOffset;  //!< The offset between measured and curve t
  float         FanLevel;           //!< Fan level to use in this scenario
  bool          CoilEnabled;        //!< Coil needs to be on or off for scenario
};

// === PUBLIC VARIABLES ======================================================

extern bool RoastStarted;	//!< Variable to track when roast has started

// === FUNCTION PROTOTYPES ===================================================

void InitRoast( void );
void StartRoast( void );
