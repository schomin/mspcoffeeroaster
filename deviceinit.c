//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  deviceinit.c
//      description:  Functions for Device init on boot up
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "peripherals.h"
#include "deviceinit.h"

// === PUBLIC FUNCTIONS ======================================================

//-----------------------------------------------------------------------------
//
//  InitLEDs
//! \brief   Description:  This function will init LEDs for MSP430
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitLEDs( void ){

  LED_DIR |= LED0 + LED1;  	// Set LED pins as outputs
  LED_OUT &= ~(LED0 + LED1);	// Turn off both LEDs

} // InitLEDs

//-----------------------------------------------------------------------------
//
//  LowLevelInit
//! \brief   Description:  This function will init the watchdog controller
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void LowLevelInit( void ){

  // Halt the watchdog timer - According to the datasheet the watchdog timer
  // starts automatically after powerup. It must be configured or halted at
  // the beginning of code execution to avoid a system reset. Furthermore,
  // the watchdog timer register (WDTCTL) is password protected, and requires
  // the upper byte during write operations to be 0x5A, which is the value
  // associated with WDTPW.
  WDTCTL = WDTPW + WDTHOLD;

} // LowLevelInit

//-----------------------------------------------------------------------------
//
//  InitBtnInterrupt
//! \brief   Description:  This function will init the interupt for the btn on
//!												launchpad dev board
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitBtnInterrupt( void ){

  P1IE |= BTN;	 //Enable the interrupt for btn (P1.3)

  P1IFG &= ~BTN; //Clear the interupt flag for the btn (P1.3)

} // InitBtnInterrupt

//-----------------------------------------------------------------------------
//
//  ConfigureClocks
//! \brief   Description:  This function will init the clocks for the processor
//!							at 16MHz
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void ConfigureClocks( void ){

  //Set the basic clock system controller 1 for 16MHz
  BCSCTL1 = CALBC1_16MHZ;
  //Set the Digitaly controlled oscillator to 16 MHz
  DCOCTL = CALDCO_16MHZ;

  //Set basic clock system control 3 to use internal VLO 12kHz
  BCSCTL3 |= LFXT1S_2;

} // ConfigureClocks

//-----------------------------------------------------------------------------
//
//  InitDevice
//! \brief   Description:  This function will init the device
//
//  Entry:
//!   \param
//!   This routine does not have any input parameters.
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitDevice( void ){

  //Stop watchdog
  LowLevelInit();

  //Setup LEDs
  InitLEDs();

  //Configure clocks at 16MHz
  ConfigureClocks();

  //Initialize the button interupt for forcing last/saved roast curve
  InitBtnInterrupt();

  //Initialize PWM for fan
  InitPWM();

  //Initialize thermocouple for sampleing temp
  InitTherm();

  //Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_2;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;

  // Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be
	TACCR0 = 3000;

} //InitDevice
