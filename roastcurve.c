//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roastcurve.c
//      description:  Initialize the roast curve
//  original author:  Andrew Schomin
//    creation date:  05-14-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>

#include "types.h"
#include "deviceinit.h"
#include "uart.h"
#include "flash.h"
#include "roastcurve.h"

// === PRIVATE VARIABLES ======================================================

uint16 *currentCurvePoint = (uint16 *)FLASH_START_ADDRESS;
bool curveSaveStarted = false;

// === FUNCTIONS =============================================================

//-----------------------------------------------------------------------------
//
//  GetRoastCurve
//! \brief   Description:  This will send the stored roast curve back to the
//!                        host.
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void GetRoastCurve( void ){

  currentCurvePoint = (uint16 *)CURVE_START_ADDRESS;

  while (1){

    uint16 temp = FlashRead(currentCurvePoint++);

    UARTSendArray(&temp, 2);

    if(temp == 0xFFFF){

      break;

    }

  }

}
