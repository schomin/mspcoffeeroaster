//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  peripherals.c
//      description:  Initialize and utilize peripherals for roasting
//  original author:  Andrew Schomin
//    creation date:  05-16-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "peripherals.h"
#include "types.h"
#include "constants.h"

// === PUBLIC VARIABLES ======================================================

uint8 dutyCycles[ NUM_FAN_LEVELS ] = {
          FAN_OFF, FAN_STATE_1, FAN_STATE_2,
          FAN_STATE_3, FAN_MAX
          };

// === FUNCTIONS =============================================================

//-----------------------------------------------------------------------------
//
//  InitPWM
//! \brief   Description:  This will Initialize the Pulse width modulator for
//!                        controlling the fan
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitPWM( void )
{
  P2DIR |= PWM;                             // Configure output direction
  P2SEL |= PWM;                             // Select peripheral option
  TA1CCR0 = PERIOD050USEC;                  // Set up the PWM Period
  TA1CTL = TASSEL_2 + MC_1;                 // Use SMCLK, count up mode
  TA1CCTL1 = OUTMOD_1;                      // Keep fan(s) off initially
} //InitPWM

//-----------------------------------------------------------------------------
//
//  InitTherm
//! \brief   Description:  This will Initialize the thermocouple input for
//!                        sampling temperature
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitTherm( void )
{
  P1SEL &= ~(REF+THERM);                    // Select I/O function
  P1DIR |=  (REF+THERM);                    // Change R(ref) pin for output
  P1OUT &= ~(REF+THERM);                    // Clear resistor outputs
  CAPD = (REF+THERM+CA_IN);                 // Disable sensor inputs
  CACTL2 = P2CA0;                           // Set up comparator
} // InitTherm

//-----------------------------------------------------------------------------
//
//  SampleTherm
//! \brief   Description:  This will sample the thermocouple
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return
//!    Returns the sampled temperature in degrees F
//-----------------------------------------------------------------------------
uint16 SampleTherm( void )
{

  //!!!!!!!!Code here is an example but may not work!!!!!!!!!!!

  uint16 i;
  uint16 value;

  P1OUT ^= CS;
//CS low to enable device

  P1OUT |= REF;
  P1OUT ^= REF;
//strobe SCK to trash dummy bit

  for (i=11; i>=0; i--)
  {
      P1OUT |= REF;
	//SCK goes high
      value += ((P1IN & THERM) > 0) << i;
	//read value of SO into bit i stored in value
      P1OUT ^= REF;
	//SCK goes low
  }
//strobe SCK to read bits 14 through 3

  P1OUT |= REF;
  P1OUT ^= REF;
//strobe SCK to grab thermocouple input bit

  P1OUT |= CS;
//CS high to disable device

  value >>= 2;
//use a bitshift to divide value by 4, truncating the LSBs
  return value;

} //SampleTherm

//-----------------------------------------------------------------------------
//
//  SetFanLevel
//! \brief   Description:  This will set the PWM to change fan speed
//
//  Entry:
//!   \param[in] FanLevel : The speed you want to set the fan at
///
//  Exit:
//!   \return NONE
//-----------------------------------------------------------------------------
void SetFanLevel( FanLevel fanLevel )
{
  float dutyCycle = ((float)(dutyCycles[fanLevel]))/100;

  if (dutyCycle > 0.99)

    TA1CCTL1 = OUTMOD_5;                  // Output constant LOW signal

  else {

    TA1CCR1 = (dutyCycle * PERIOD050USEC);  // Update the compare register
    TA1CCTL1 = OUTMOD_3;                    // Generate PWM via out mode 3

  }
} //SetFanLevel

//-----------------------------------------------------------------------------
//
//  SetCoilEnabled
//! \brief   Description:  This will set the coil on or off
//
//  Entry:
//!   \param[in] coilEnabled : Do you want to turn the coil on or off?
///
//  Exit:
//!   \return NONE
//-----------------------------------------------------------------------------
void SetCoilEnabled( bool coilEnabled )
{
  return;
} //SetCoilEnabled
