//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  flash.h
//      description:  Header file for flash utilities
//  original author:  Andrew Schomin
//    creation date:  05-13-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>
#include "uart.h"
#include "utilities.h"

// === DEFINES ===============================================================

#define FLASH_START_ADDRESS 0xE000    //!< The starting memory address of usable
                                      //!< Flash space
#define CURVE_START_ADDRESS FLASH_START_ADDRESS //!< Use start address to store
                                                //!< curve for now
#define ERASE_BLOCK_SIZE    0x200               //!< Size of an erase block

// === GLOBAL VARIABLES ======================================================

extern int *CurentCurvePoint;    //!< Current memory address of the accessed curve
extern bool CurveSaveStarted;    //!< A curve save has been initiated

// === FUNCTION PROTOTYPES ===================================================

void FlashErase(int *addr);
void FlashProgram(int *addr, int value);
int FlashRead(int *addr);
