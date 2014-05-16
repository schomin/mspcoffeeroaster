//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roast.c
//      description:  the roast process
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include "roast.h"

// === PUBLIC VARIABLES ======================================================

bool RoastStarted = false; // Initialize RoastStarted

// === FUNCTIONS =============================================================

//-----------------------------------------------------------------------------
//
//  InitRoast
//! \brief   Description:  This will Initialize the roast process. Setup the
//!                        device
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitRoast( void ){

  //If roasting is in progress then we don't want to init
  if(!RoastStarted){

    //Roasting is in progress
    RoastStarted = true;

  }

} //InitRoast

//-----------------------------------------------------------------------------
//
//  StartRoast
//! \brief   Description:  This will start the roast process useing a stored
//!                        Useing a stored roast curve.
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void StartRoast( void ){

  // Re-Initialize the CurrentCurve point back to the play back address start
  CurrentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;

  unsigned int CurveSample = 0x0000; //!< A temp sample from the curve (1sec)
  unsigned int ThermSample = 0x0000; //!< Sample from the thermocouple

  // We will now play back the curve as long as we didn't reach the end or run
  // to the end of the curve address space
  while(CurveSample != 0xFFFF
      || (unsigned int)&CurrentCurvePoint <
      (CURVE_START_ADDRESS+ROAST_CURVE_SIZE)){

    // Read the curve point and increment
    CurveSample = FlashRead(CurrentCurvePoint++);

    // Get sample from thermocouple
    ThermSample = SampleTherm();

  }

} //StartRoast
