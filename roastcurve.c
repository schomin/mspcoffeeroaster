//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  roastcurve.c
//      description:  Initialize the roast curve
//  original author:  Andrew Schomin
//    creation date:  05-14-2014
//
//****************************************************************************

// === INCLUDES ==============================================================

#include "roastcurve.h"

// === GLOBAL VARIABLES ======================================================


// === FUNCTIONS =============================================================

void GetRoastCurve( void ){

  CurentCurvePoint = (int *)FLASH_START_ADDRESS;

  while (1){

    int temp = FlashRead(CurentCurvePoint++);

    UARTSendArray(&temp, 2);

  }

}

void SaveRoastCurve( void ){

  dint();

  while (1){

    char lowbits = UCA0RXBUF;
    char highbits = UCA0RXBUF;

    int highbitsint = (int)highbits << 8;
    int lowbitsint = (int)lowbits;
    int combined = (int)highbits << 8 | (int)lowbits;

    int data[3] = { highbitsint, lowbitsint, combined};

    UARTSendArray("In Roast Curve Loop\n", 21);
    UARTSendArray(&data, 6);

    if(data == 0xFFFF){

      //reached end of data
      LED_OUT ^= LED0;

    }

  }

  eint();

}
