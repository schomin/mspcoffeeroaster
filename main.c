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
#include <stdio.h>

#include "deviceinit.h"
#include "interrupts.h"
#include "uart.h"

// === MAIN FUNTION ==========================================================


int main(void) {

	//Initialize the device
	InitDevice();

	//Initialize the UART
	InitUART();

	//Enable global interrupts
	eint();

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}
