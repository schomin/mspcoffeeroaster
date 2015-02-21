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

#include "types.h"

// === DEFINES ===============================================================

#define FLASH_START_ADDRESS 0xE000    //!< The starting memory address of usable
                                      //!< Flash space
#define ERASE_BLOCK_SIZE    0x200               //!< Size of an erase block
#define ERASE_BLOCK_INT_SIZE ERASE_BLOCK_SIZE/2 //!< Size of erase blocks in
                                                //!< ints (2 bytes or 16 bits)

// === GLOBAL VARIABLES ======================================================

// === FUNCTION PROTOTYPES ===================================================

void FlashErase(uint16 *addr);
void FlashProgram(uint16 *addr, uint16 value);
unsigned int FlashRead(uint16 *addr);
