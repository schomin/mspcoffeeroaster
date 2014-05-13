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

	UARTSendArray("Test:\n", 6);

	int *addr = (int *)FLASH_START_ADDRESS;

	FlashErase(addr);


	FlashProgram(addr);

	int data[2]={*addr, 20};
	UARTSendArray(&data, 4);

	//Enable global interrupts
	eint();

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}
