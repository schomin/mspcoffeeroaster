//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  utilities.h
//      description:  header file for utilities
//  original author:  Andrew Schomin
//    creation date:  05-12-2014
//
//****************************************************************************

// === TYPEDEFs ==============================================================

#ifndef bool
#define bool unsigned char 	//!< typedef for bool
#endif //bool

// === VALUE DEFS ============================================================

#ifndef false
#define false 0		//!< Define value for false
#endif //false
#ifndef true
#define true  1		//!< Define value for true
#endif //true

#define PERIOD5MSEC 80000   //!< 5 msec worth of SMCLK tics @ DCO = 16 MHz
                            //!< is 80000 cycles
#define PERIOD050USEC 80    // assuming ~16 MHz DCO clock
