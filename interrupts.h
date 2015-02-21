//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  interrupts.h
//      description:  Header file for Device interrupts
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************


// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>

#include "deviceinit.h"
#include "roastcurve.h"
#include "roast.h"
#include "uart.h"
#include "flash.h"
#include "types.h"
#include "constants.h"

// === PRIVATE VARIABLES =====================================================

bool isLowBits = true;      //!< Used to tell interrupt what bits of the int
                            //!< Being transfered we are on
uint16 combinedBits = 0;

// === GLOBAL INTERRUPTS =====================================================

//-----------------------------------------------------------------------------
//
//  PORT1_ISR
//! \brief   Description:  This is an interrupt for port1.
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
#pragma vector=PORT1_VECTOR
__interrupt PORT1_ISR (void)
{
// interrupt(PORT1_VECTOR) PORT1_ISR(void)
// {

  if((P1IFG & BTN) && !roastStarted){

    LED_OUT |= LED1;

    P1IFG = P1IFG & ~BTN;

    dint();

    InitRoast();
    hostStarted = false;
    StartRoast();

    eint();

  }

} //PORT1_ISR

//-----------------------------------------------------------------------------
//
//  TIMERA0_ISR
//! \brief   Description:  This is an interrupt for Timer A0.
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
#pragma vector=TIMER0_A0_VECTOR
__interrupt TIMERA0_ISR (void)
{
// interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void)
// {

  LED_OUT ^= LED1;

} //TIMERA0_ISR

//-----------------------------------------------------------------------------
//
//  USCI0RX_ISR
//! \brief   Description:  This is an interrupt for UART RX. It will interrupt
//!                        when a process is not happening
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
#pragma vector=USCIAB0RX_VECTOR
__interrupt USCI0RX_ISR (void)
{
// interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void)
// {
  unsigned char data = UCA0RXBUF;

  //UARTSendArray(&data, 1);

  if(curveSaveStarted){

    if(isLowBits){

      combinedBits = (unsigned int)data;

      isLowBits = false;

    }
    else{

      combinedBits = (data << 8) | combinedBits;
      UARTSendArray(&combinedBits, 2);


      //UARTSendArray(&combinedBits, 2);

      if(combinedBits == 0xFFFF){

        curveSaveStarted = false;
        //Enable the interrupt for TACCR0 match. We are now doing somethings
        //TACCTL0 = CCIE;

      }else{

        // Check if the current address is a multiple of 0x200 for eraseing
        if((uint16)(&currentCurvePoint)%(ERASE_BLOCK_SIZE) == 0){

          FlashErase(currentCurvePoint);
        }

        FlashProgram(currentCurvePoint++, combinedBits);

      }

      isLowBits = true;

    }

  }
  else{

    switch(data){
     // Host wants to save a new curve to flash
     case 's': {
       // Respond with k char
       UARTSendArray("k", 1);
       curveSaveStarted = true;
       currentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;
       //Disable the interrupt for TACCR0 match. We are now doing somethings
       //TACCTL0 = ~(CCIE);
       break;
     }
     // Host wants to get a roast curve
     case 'g': {
       dint();
       // Respond with k char
       UARTSendArray("k", 1);
       GetRoastCurve();
       eint();
     }
     // Host wants to start the roast
     case 'r': {
       // Respond with k char
       UARTSendArray("k", 1);
       dint();
       InitRoast();
       //Disable the interrupt for TACCR0 match. We are now doing somethings
       TACCTL0 = ~(CCIE);
       hostStarted = false;
       StartRoast();
       eint();
     }
     default: {
       UARTSendArray("Unknown Command: ", 17);
       UARTSendArray(&data, 1);
       UARTSendArray("\n\r", 2);
       break;
     }
     }
   }
} //USCI0RX_ISR
