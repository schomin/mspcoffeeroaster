//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  flash.c
//      description:  Utilities for utilizing the flash memory on msp430
//  original author:  Andrew Schomin
//    creation date:  05-13-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>
#include "flash.h"
#include "types.h"

// === PUBLIC FUNCTIONS ======================================================

//-----------------------------------------------------------------------------
//
//  FlashErase
//! \brief   Description:  This is a function used to erase a flash erase block
//
//  Entry:
//!   \param[in] : block : This paremter is the address of the erase block
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void FlashErase(uint16 *block)
{

  dint();                              // Disable interrupts. This is important, otherwise,
                                       // a flash operation in progress while interrupt may
                                       // crash the system.
  while(BUSY & FCTL3);                 // Check if Flash being used
  FCTL2 = FWKEY + FSSEL1 + FN2;        // Clk = SMCLK/4
  FCTL1 = FWKEY + ERASE;               // Set Erase bit
  FCTL3 = FWKEY;                       // Clear Lock bit
  *block = 0;                          // Dummy write to erase Flash segment
  while(BUSY & FCTL3);                 // Check if Flash being used
  FCTL1 = FWKEY;                       // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                // Set LOCK bit
  eint();                              // Enable interrupts

} //FlashErase

//-----------------------------------------------------------------------------
//
//  FlashProgram
//! \brief   Description:  This will program data starting at a specified
//!                        page address
//
//  Entry:
//!   \param[in] : page: This paremter is the address of the page to program
//!   \param[in] : data: Data to write to the page address
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void FlashProgram(uint16 *page, uint16 data)
{
  dint();                               // Disable interrupts
  FCTL2 = FWKEY + FSSEL1 + FN2;         // Clk = SMCLK/4
  FCTL3 = FWKEY;                        // Clear Lock bit
  FCTL1 = FWKEY + WRT;                  // Set WRT bit for write operation

  *page = data;                         // copy value to flash

  FCTL1 = FWKEY;                        // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                 // Set LOCK bit
  while(BUSY & FCTL3);
  eint();
} //FlashProgram

//-----------------------------------------------------------------------------
//
//  FlashRead
//! \brief   Description:  This will read data at a specified page address
//
//  Entry:
//!   \param[in] : page : This paremter is the address of the page to Read
//!   \param[in] : data : A pointer to a buffer to read data into
//
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void FlashRead(uint16 *page, uint16 *data)
{

  *data = *addr;

} //FlashRead
