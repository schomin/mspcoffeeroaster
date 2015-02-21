//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roast.c
//      description:  the roast process
//  original author:  Andrew Schomin
//    creation date:  05-09-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include "types.h"
#include "constants.h"
#include "roastcurve.h"
#include "peripherals.h"
#include "roast.h"
#include "flash.h"

// === PUBLIC VARIABLES ======================================================

bool roastStarted = false; // Initialize roastStarted
bool hostStarted = false;  // Initialize hostStarted

// === FUNCTIONS =============================================================

//-----------------------------------------------------------------------------
//
//  InitRoast
//! \brief   Description:  This will Initialize the roast process. Setup the
//!                        device
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void InitRoast( void ){

  //If roasting is in progress then we don't want to init
  if(!roastStarted){

    //Roasting is in progress
    roastStarted = true;

    // Setup ROAST_SCENARIO_0
    roastScenarios[ROAST_SCENARIO_0].stTemperatureOffset = SCENARIO_0_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_0].stFanLevel = FAN_STATE_1;
    roastScenarios[ROAST_SCENARIO_0].stCoilEnabled = true;

    // Setup ROAST_SCENARIO_1
    roastScenarios[ROAST_SCENARIO_1].stTemperatureOffset = SCENARIO_1_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_1].stFanLevel = FAN_STATE_2;
    roastScenarios[ROAST_SCENARIO_1].stCoilEnabled = true;

    // Setup ROAST_SCENARIO_2
    roastScenarios[ROAST_SCENARIO_2].stTemperatureOffset = SCENARIO_2_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_2].stFanLevel = FAN_STATE_3;
    roastScenarios[ROAST_SCENARIO_2].stCoilEnabled = true;

    // Setup ROAST_SCENARIO_3
    roastScenarios[ROAST_SCENARIO_3].stTemperatureOffset = SCENARIO_3_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_3].stFanLevel = FAN_MAX;
    roastScenarios[ROAST_SCENARIO_3].stCoilEnabled = true;

    // Setup ROAST_SCENARIO_4
    roastScenarios[ROAST_SCENARIO_4].stTemperatureOffset = SCENARIO_4_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_4].stFanLevel = FAN_STATE_1;
    roastScenarios[ROAST_SCENARIO_4].stCoilEnabled = false;

    // Setup ROAST_SCENARIO_5
    roastScenarios[ROAST_SCENARIO_5].stTemperatureOffset = SCENARIO_5_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_5].stFanLevel = FAN_STATE_2;
    roastScenarios[ROAST_SCENARIO_5].stCoilEnabled = false;

    // Setup ROAST_SCENARIO_6
    roastScenarios[ROAST_SCENARIO_6].stTemperatureOffset = SCENARIO_6_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_6].stFanLevel = FAN_STATE_3;
    roastScenarios[ROAST_SCENARIO_6].stCoilEnabled = false;

    // Setup ROAST_SCENARIO_7
    roastScenarios[ROAST_SCENARIO_7].stTemperatureOffset = SCENARIO_7_THRESHOLD;
    roastScenarios[ROAST_SCENARIO_7].stFanLevel = FAN_MAX;
    roastScenarios[ROAST_SCENARIO_7].stCoilEnabled = false;

  }

} //InitRoast

//-----------------------------------------------------------------------------
//
//  StartRoast
//! \brief   Description:  This will start the roast process useing a stored
//!                        Useing a stored roast curve.
//
//  Entry:
//!   \param NONE
///
//  Exit:
//!   \return NONE ( Does not return any values )
//-----------------------------------------------------------------------------
void StartRoast( void ){

  // Re-Initialize the CurrentCurve point back to the play back address start
  currentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;

  uint16 *saveCurvePoint = (unsigned int *)CURVE_RECORD_START_ADDRESSS;

  uint16 curveSample = 0x0000; //!< A temp sample from the curve (1sec)
  uint16 thermSample = 0x0000; //!< Sample from the thermocouple

  // We will now play back the curve as long as we didn't reach the end or run
  // to the end of the curve address space
  while(curveSample != 0xFFFF
      || (uint16)&currentCurvePoint <
      (CURVE_START_ADDRESS+ROAST_CURVE_SIZE)){

    // Read the curve point and increment
    curveSample = FlashRead(currentCurvePoint++);

    // Get sample from thermocouple
    thermSample = SampleTherm();

    // Check if the current address is a multiple of 0x200 for eraseing
    if((uint16)(&saveCurvePoint)%(ERASE_BLOCK_SIZE) == 0){

      FlashErase(saveCurvePoint);
    }

    // Save the roast point to flash
    FlashProgram(saveCurvePoint++, thermSample);

    // If the host started the roast then send sampled temp via uart
    if(hostStarted){

      UARTSendArray(&thermSample, 2);

    }

    uint16 curveDelta = curveSample - thermSample;  //!< Delta between curve
                                                          //!< and thermocouple

    uint8 currentScenario = ROAST_SCENARIO_4; //!< Used to store current
                                                      //!< scenario (default 4)

    // Check what schenario we are currently in
    if(curveDelta > SCENARIO_0_THRESHOLD){
      currentScenario = ROAST_SCENARIO_0;
    }else if(curveDelta > SCENARIO_1_THRESHOLD){
      currentScenario = ROAST_SCENARIO_1;
    }else if(curveDelta > SCENARIO_2_THRESHOLD){
      currentScenario = ROAST_SCENARIO_2;
    }else if(curveDelta > SCENARIO_3_THRESHOLD){
      currentScenario = ROAST_SCENARIO_3;
    }else if(curveDelta > SCENARIO_4_THRESHOLD){
      currentScenario = ROAST_SCENARIO_4;
    }else if(curveDelta > SCENARIO_5_THRESHOLD){
      currentScenario = ROAST_SCENARIO_5;
    }else if(curveDelta > SCENARIO_6_THRESHOLD){
      currentScenario = ROAST_SCENARIO_6;
    }else{
      currentScenario = ROAST_SCENARIO_7;
    }

    struct ST_RoastScenario *currentScenarioInfo =
                        &(roastScenarios[currentScenario]);
                        //!< Pointer to the info for the current scenario

    SetFanLevel(currentScenarioInfo->stFanLevel);
    SetCoilEnabled(currentScenarioInfo->stCoilEnabled);

    __delay_cycles(SAMPLE_RATE);

  }

} //StartRoast
