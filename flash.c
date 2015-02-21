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
#include "uart.h"
#include "types.h"

// === PUBLIC FUNCTIONS ======================================================

//-----------------------------------------------------------------------------
//
//  FlashErase
//! \brief   Description:  This is an interrupt for port1.
//
//  Entry:
//!   \param[in] : This paremter is the address of the erase block
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void FlashErase(uint16 *addr)
{

  dint();                              // Disable interrupts. This is important, otherwise,
                                       // a flash operation in progress while interrupt may
                                       // crash the system.
  while(BUSY & FCTL3);                 // Check if Flash being used
  FCTL2 = FWKEY + FSSEL1 + FN2;        // Clk = SMCLK/4
  FCTL1 = FWKEY + ERASE;               // Set Erase bit
  FCTL3 = FWKEY;                       // Clear Lock bit
  *addr = 0;                           // Dummy write to erase Flash segment
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
//!   \param[in] : This paremter is the address of the page to program
//!   \param[in] : Data to write to the page address
//!   \param[in] : Size of buffer passed to the program function
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void FlashProgram(uint16 *addr, uint16 value)
{
  dint();                              // Disable interrupts
  FCTL2 = FWKEY + FSSEL1 + FN2;       // Clk = SMCLK/4
  FCTL3 = FWKEY;                       // Clear Lock bit
  FCTL1 = FWKEY + WRT;                 // Set WRT bit for write operation

  *addr = value;         // copy value to flash

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
//!   \param[in] : This paremter is the address of the page to Read
//
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
unsigned int FlashRead(uint16 *addr)
{

  return *addr;

} //FlashRead
