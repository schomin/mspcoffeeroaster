//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roast.h
//      description:  header file toInitialize the roast process
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include "types.h"
#include "peripherals.h"

// === DEFINES ===============================================================

#define NUMBER_OF_ROAST_SCENARIOS 8

#define ROAST_SCENARIO_0 0    //!< Offset is greater than 127
#define ROAST_SCENARIO_1 1    //!< Offset is between 63 and 127
#define ROAST_SCENARIO_2 2    //!< Offset is between 31 and 63
#define ROAST_SCENARIO_3 3    //!< Offset is between 7 and 31
#define ROAST_SCENARIO_4 4    //!< Offset is between -7 and 7
#define ROAST_SCENARIO_5 5    //!< Offset is between -7 and -31
#define ROAST_SCENARIO_6 6    //!< Offset is between -31 and -63
#define ROAST_SCENARIO_7 7    //!< Offset is between -63 and -127

#define SCENARIO_0_THRESHOLD 127
#define SCENARIO_1_THRESHOLD 63
#define SCENARIO_2_THRESHOLD 31
#define SCENARIO_3_THRESHOLD 7
#define SCENARIO_4_THRESHOLD -7
#define SCENARIO_5_THRESHOLD -31
#define SCENARIO_6_THRESHOLD -63
#define SCENARIO_7_THRESHOLD -127

// === STRUCTURES ============================================================

struct  __attribute__((__packed__)) ST_RoastScenario
{
  //!< This is a struct that will hold a number of thresholds and how to adjust
  //!< the peripherals accordingly for a scenario
  int8 stTemperatureOffset  :  8;     //!< The offset between measured and curve t
  uint8         stFanLevel  :  7;     //!< Fan level to use in this scenario
  bool       stCoilEnabled  :  1;     //!< Coil needs to be on or off for scenario
};

// === INITIALIZE STRUCTS ====================================================

struct ST_RoastScenario roastScenarios[8];
            //!< Array of predefined ST_RoastScenario structs

// === PUBLIC VARIABLES ======================================================

extern bool roastStarted;	 //!< Variable to track when roast has started
extern bool hostStarted;   //!< The roast process was started by the a host

// === FUNCTION PROTOTYPES ===================================================

void InitRoast( void );
void StartRoast( void );
