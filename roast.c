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

// === GLOBAL VARIABLES ======================================================

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
//! \brief   Description:  This will start the roast process.
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void StartRoast( void ){

  

} //StartRoast
