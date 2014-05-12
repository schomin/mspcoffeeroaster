//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  deviceinit.h
//      description:  Header file for Device init on boot up
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>

// === DEFINES ===============================================================

#define MCLK_IS_16MHZ  1    //!< Specify that clock is set at 16MHz
#define LED0 			BIT0		 //!< Definition for led 0
#define LED1 			BIT6		 //!< Definition for led 1
#define LED_DIR		P1DIR		//!< Definition for led dir
#define LED_OUT 	 P1OUT		//!< Definition for led out
#define BTN        BIT3		 //!< Definition for the button on launchpad

#ifndef	TACTL
  #define TACTL TA0CTL 			 //!< For MSP430 Controller compatability
  #define TACCTL0 TA0CCTL0		//!< For MSP430 Controller compatability
#endif  //TACTL

// === GLOBAL VARIABLES =====================================================


// === FUNCTION PROTOTYPES ==================================================
void InitLEDs( void );
void LowLevelInit( void );
void InitBtnInterrupt( void );
void ConfigureClocks( void );
void InitDevice( void );
