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

// === MAIN FUNTION ==========================================================


int main(void) {

	//Initialize the device
	InitDevice();

	//Initialize the UART
	InitUART();

	FlashErase(CurentCurvePoint);

	unsigned int test = 1;

	FlashProgram(CurentCurvePoint++, test);

	test = 2;

	FlashProgram(CurentCurvePoint++, test);

	CurentCurvePoint = (unsigned int *)CURVE_START_ADDRESS;

	test = FlashRead(CurentCurvePoint++);

	UARTSendArray(&test, 2);

	test = FlashRead(CurentCurvePoint++);

	UARTSendArray(&test, 2);



	//Enable global interrupts
	eint();

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}
