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

#include "types.h"

// === DEFINES ===============================================================

// Port 1 pins
#define CS          BIT3
#define THERM       BIT4    //!< Bit for thermocouple input
#define REF         BIT5    //!< Reference voltage bit
#define CA_IN       BIT6    //!<

// Port 2 pins
#define TACH        BIT0    //!< TACH bit define
#define PWM         BIT1    //!< PWM bit define

#define FAN_MAX     100     //!< Max duty cycle for PWM
#define FAN_STATE_3 80
#define FAN_STATE_2 60
#define FAN_STATE_1 35
#define FAN_OFF     0       //!< Fan off state

#define NUM_FAN_LEVELS  6   //!< The number of fam levels available

#define SAMPLE_RATE 16000000//!< 1 sec for 16Mhz clock

// === TYPEDEF ===============================================================

typedef enum FanLevel {
  FANSLEVEL0, FANSLEVEL1, FANSLEVEL2, FANSLEVEL3, FANSLEVEL4
} FanLevel;

// === PUBLIC VARIABLES ======================================================

extern uint8 dutyCycles[ NUM_FAN_LEVELS ];
              //!< Lookup table for fan duty cycles

// === FUNCTION PROTOTYPES ===================================================
void InitPWM( void );
void InitTherm( void );
uint16 SampleTherm( void );
void SetFanLevel( FanLevel fanLevel );
void SetCoilEnabled( bool CoilEnabled );
