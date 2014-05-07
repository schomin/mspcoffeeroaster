//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  main.c
//      description:  main File
//  original author:  Andrew Schomin
//    creation date:  05-07-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <legacymsp430.h>

// === DEFINES ===============================================================

#define LED0 		BIT0		//!< Definition for led 0
#define LED1 		BIT6		//!< Definition for led 1
#define LED_DIR		P1DIR		//!< Definition for led dir
#define LED_OUT 	P1OUT		//!< Definition for led out

#ifndef	TACTL
#define TACTL TA0CTL 			//!< For MSP430 Controller compatability 
#define TACCTL0 TA0CCTL0		//!< For MSP430 Controller compatability 
#endif  //TACTL

unsigned char twink = 0;


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
	BCSCTL3 |= LFXT1S_2

} // ConfigureClocks

int main(void) {
 
	//Stop watchdog
	LowLevelInit();	
 
	//Setup LEDs
	InitLEDs();
 
 	ConfigureClocks();
 
	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;
 
	// Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be
	TACCR0 = 3000;
 
	//Enable global interrupts
	eint();
 
	while(1) {
		//Loop forever, interrupts take care of the rest
	}
 
}

// Interrupt Service Routine for Timer A0. We need to use preprocessor
// directives in order to place the interrupt at the correct address for
// the current mcu.
#ifdef TIMER0_A0_VECTOR
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {
#else
interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
#endif
	twink = !twink;
	// Doing it like this will set all other pins low, which is ok for this
	// example. If you got other things going for the other pins on this port
	// you should use bitwise operations.
	LED_OUT = (twink)?LED0:LED1;
 
}