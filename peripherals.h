//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  peripherals.h
//      description:  header file for peripherals used in roast proccess
//  original author:  Andrew Schomin
//    creation date:  05-16-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "utilities.h"

// === DEFINES ===============================================================

// Port 1 pins
#define CS          BIT3
#define THERM       BIT4    //!< Bit for thermocouple input
#define REF         BIT5    //!< Reference voltage bit
#define CA_IN       BIT6    //!<

// Port 2 pins
#define TACH        BIT0    //!< TACH bit define
#define PWM         BIT1    //!< PWM bit define

#define FAN_MAX     128     //!< Max duty cycle for PWM
#define FAN_STATE_3 96
#define FAN_STATE_2 64
#define FAN_STATE_1 32
#define FAN_OFF     0       //!< Fan off state

// === GLOBAL VARIABLES ======================================================


// === FUNCTION PROTOTYPES ===================================================

void InitPWM( void );
void InitTherm( void );
unsigned int SampleTherm( void );
void SetFanLevel( float FanLevel );
void SetCoilEnabled( bool CoilEnabled );
