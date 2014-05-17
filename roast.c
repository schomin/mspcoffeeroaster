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

#include "roast.h"

// === PUBLIC VARIABLES ======================================================

bool RoastStarted = false; // Initialize RoastStarted
bool HostStarted = false;  // Initialize HostStarted

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
  if(!RoastStarted){

    //Roasting is in progress
    RoastStarted = true;

    // Setup ROAST_SCENARIO_0
    RoastScenarios[ROAST_SCENARIO_0].TemperatureOffset = SCENARIO_0_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_0].FanLevel = FAN_STATE_1;
    RoastScenarios[ROAST_SCENARIO_0].CoilEnabled = true;

    // Setup ROAST_SCENARIO_1
    RoastScenarios[ROAST_SCENARIO_1].TemperatureOffset = SCENARIO_1_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_1].FanLevel = FAN_STATE_2;
    RoastScenarios[ROAST_SCENARIO_1].CoilEnabled = true;

    // Setup ROAST_SCENARIO_2
    RoastScenarios[ROAST_SCENARIO_2].TemperatureOffset = SCENARIO_2_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_2].FanLevel = FAN_STATE_3;
    RoastScenarios[ROAST_SCENARIO_2].CoilEnabled = true;

    // Setup ROAST_SCENARIO_3
    RoastScenarios[ROAST_SCENARIO_3].TemperatureOffset = SCENARIO_3_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_3].FanLevel = FAN_MAX;
    RoastScenarios[ROAST_SCENARIO_3].CoilEnabled = true;

    // Setup ROAST_SCENARIO_4
    RoastScenarios[ROAST_SCENARIO_4].TemperatureOffset = SCENARIO_4_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_4].FanLevel = FAN_STATE_1;
    RoastScenarios[ROAST_SCENARIO_4].CoilEnabled = false;

    // Setup ROAST_SCENARIO_5
    RoastScenarios[ROAST_SCENARIO_5].TemperatureOffset = SCENARIO_5_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_5].FanLevel = FAN_STATE_2;
    RoastScenarios[ROAST_SCENARIO_5].CoilEnabled = false;

    // Setup ROAST_SCENARIO_6
    RoastScenarios[ROAST_SCENARIO_6].TemperatureOffset = SCENARIO_6_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_6].FanLevel = FAN_STATE_3;
    RoastScenarios[ROAST_SCENARIO_6].CoilEnabled = false;

    // Setup ROAST_SCENARIO_7
    RoastScenarios[ROAST_SCENARIO_7].TemperatureOffset = SCENARIO_7_THRESHOLD;
    RoastScenarios[ROAST_SCENARIO_7].FanLevel = FAN_MAX;
    RoastScenarios[ROAST_SCENARIO_7].CoilEnabled = false;

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
  CurrentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;

  unsigned int *SaveCurvePoint = (unsigned int *)CURVE_RECORD_START_ADDRESSS;

  unsigned int CurveSample = 0x0000; //!< A temp sample from the curve (1sec)
  unsigned int ThermSample = 0x0000; //!< Sample from the thermocouple

  // We will now play back the curve as long as we didn't reach the end or run
  // to the end of the curve address space
  while(CurveSample != 0xFFFF
      || (unsigned int)&CurrentCurvePoint <
      (CURVE_START_ADDRESS+ROAST_CURVE_SIZE)){

    // Read the curve point and increment
    CurveSample = FlashRead(CurrentCurvePoint++);

    // Get sample from thermocouple
    ThermSample = SampleTherm();

    // Check if the current address is a multiple of 0x200 for eraseing
    if((unsigned int)(&SaveCurvePoint)%(ERASE_BLOCK_SIZE) == 0){

      FlashErase(SaveCurvePoint);
    }

    // Save the roast point to flash
    FlashProgram(SaveCurvePoint++, ThermSample);

    // If the host started the roast then send sampled temp via uart
    if(HostStarted){

      UARTSendArray(&ThermSample, 2);

    }

    unsigned int CurveDelta = CurveSample - ThermSample;  //!< Delta between curve
                                                          //!< and thermocouple

    unsigned char CurrentScenario = ROAST_SCENARIO_4; //!< Used to store current
                                                      //!< scenario (default 4)

    // Check what schenario we are currently in
    if(CurveDelta > SCENARIO_0_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_0;
    }else if(CurveDelta > SCENARIO_1_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_1;
    }else if(CurveDelta > SCENARIO_2_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_2;
    }else if(CurveDelta > SCENARIO_3_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_3;
    }else if(CurveDelta > SCENARIO_4_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_4;
    }else if(CurveDelta > SCENARIO_5_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_5;
    }else if(CurveDelta > SCENARIO_6_THRESHOLD){
      CurrentScenario = ROAST_SCENARIO_6;
    }else{
      CurrentScenario = ROAST_SCENARIO_7;
    }

    struct ST_RoastScenario *CurrentScenarioInfo =
                        &(RoastScenarios[CurrentScenario]);
                        //!< Pointer to the info for the current scenario

    SetFanLevel(CurrentScenarioInfo->FanLevel);
    SetCoilEnabled(CurrentScenarioInfo->CoilEnabled);

    __delay_cycles(SAMPLE_RATE);

  }

} //StartRoast
