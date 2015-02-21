//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  uart.c
//      description:  uart code for Device
//  original author:  Andrew Schomin
//    creation date:  05-12-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>
#include "deviceinit.h"
#include "uart.h"
#include "types.h"

// === PUBLIC FUNCTIONS ======================================================

//-----------------------------------------------------------------------------
//
//  InitUART
//! \brief   Description:  This function will init the hardware UART for MSP430
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitUART( void ){

  P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2; // Use SMCLK
  UCA0BR0 = 131; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
  UCA0BR1 = 6; // Set baud rate to 9600 with 1MHz clock
  UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
  IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt

  __bis_SR_register(GIE); // Enter LPM0, interrupts enabled

} //InitUART

//-----------------------------------------------------------------------------
//
//  InitUART
//! \brief   Description:  This function will transmit an array of chars of
//!                        specified length over the hardware UART on the MSP430
//
//  Entry:
//!   \param[in]  TxArray     : An array of char values to be transmitted
//!                             over UART
//!   \param[in]  ArrayLength : The length of the passed array
//
//  Exit:
//!   \return NONE ( Does not return any values )
//
//! USAGE EXAMPLES </B>
//!
//!   Send number of bytes Specified in ArrayLength in the array at using
//!   the hardware UART 0
//!
//!   UARTSendArray("Hello", 5);
//!   int data[2]={1023, 235};
//!   UARTSendArray(data, 4);
//!
//!   Note because the UART transmits bytes it is necessary to send
//!   two bytes for each integer hence the data length is twice the
//!   array length
//-----------------------------------------------------------------------------
void UARTSendArray( uint16 *TxArray, uint16 ArrayLength){


  while(ArrayLength-- != 0){ // Loop until StringLength == 0 and post decrement

    while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data

    UCA0TXBUF = *TxArray; // Write the character at the location specified
                          // by the pointer
    TxArray++; // Increment the TxString pointer to point to the next
               // character

  }

} //UARTSendArray
