//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roastinit.c
//      description:  Initialize the roast process
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include "roastinit.h"

// === GLOBAL VARIABLES ======================================================

bool RoastStarted = false; // Initialize RoastStarted

// === FUNCTIONS =============================================================

void InitRoast(){

  //If roasting is in progress then we don't want to init
  if(!RoastStarted){

    //Roasting is in progress
    RoastStarted = true;

  }

} //InitRoast
