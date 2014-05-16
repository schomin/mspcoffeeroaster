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

// === DEFINES ===============================================================

#define CURVE_START_ADDRESS FLASH_START_ADDRESS //!< The starting address for
                                                //!< the curve to play back
#define ROAST_CURVE_SIZE ERASE_BLOCK_SIZE*3     //!< Size of a roast curve in
                                                //!< Bytes (1536 bytes or 3 EBs)
                                                //!< This should be enough for
                                                //!< About 10 mins of roast time
#define CURVE_RECORD_START_ADDRESSS CURVE_START_ADDRESS+ROAST_CURVE_SIZE //!<
                                                //!< The starting address to
                                                //!< save the curve being
                                                //!< recorded


// === GLOBAL VARIABLES ======================================================

extern unsigned int *CurrentCurvePoint;    //!< Current memory address of the
                                          //!< accessed curve
extern bool CurveSaveStarted;             //!< A curve save has been initiated

// === FUNCTION PROTOTYPES ===================================================

void GetRoastCurve( void );
