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

#include "flash.h"

// === PRIVATE VARIABLES =====================================================

int *FlashAddress = (int *)FLASH_START_ADDRESS; //!< pointer to flash for use below

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
void FlashErase(int *addr)
{

  dint();                              // Disable interrupts. This is important, otherwise,
                                       // a flash operation in progress while interrupt may
                                       // crash the system.
  while(BUSY & FCTL3);                 // Check if Flash being used
  FCTL2 = FWKEY + FSSEL_1 + FN3;       // Clk = SMCLK/4
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
void FlashProgram(int *addr)
{
  dint();                              // Disable interrupts
  FCTL2 = FWKEY + FSSEL_1 + FN0;       // Clk = SMCLK/4
  FCTL3 = FWKEY;                       // Clear Lock bit
  FCTL1 = FWKEY + WRT;                 // Set WRT bit for write operation

  *addr++ = 0x50;         // copy value to flash
  //*addr++ = 51;         // copy value to flash

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
int FlashRead(int *addr)
{

  return *addr;

} //FlashRead
