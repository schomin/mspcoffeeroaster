//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  main.c
//      description:  Main File
//  original author:  Andrew Schomin
//    creation date:  05-07-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include <msp430.h>
#include <stdlib.h>

#include "deviceinit.h"
#include "interrupts.h"
#include "uart.h"
#include "flash.h"
#include "peripherals.h"

// === MAIN FUNTION ==========================================================


int main(void) {

	//Initialize the device
	InitDevice();

	//Initialize the UART
	InitUART();

	//Enable global interrupts
	eint();

	InitPWM();

	SetFanLevel(FAN_STATE_1);

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}
