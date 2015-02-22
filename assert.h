//****************************************************************************
//*                    MSP430 Popcorn Popper Coffee Roaster                  *
//****************************************************************************
//
//           module:  assert.h
//      description:  header file for asserts
//  original author:  Andrew Schomin
//    creation date:  02-21-2015
//
//****************************************************************************

// === MACRO DEFS ============================================================

#ifndef FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDLIB
#define FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDLIB 1

#ifdef __cplusplus
#include <stdlib.h>
#endif
#ifndef FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDIO
#define FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDIO 1

#include <stdio.h>


//#if defined( ALPHA___ASSERT_CHECK )
extern void __assert(const char *, const char *, int);
//#endif  /* ALPHA___ASSERT_CHECK */


//#if defined( ALPHA_ASSERT_CHECK )
#define assert(EX) ((EX) ? (void)0 : __assert(#EX, __FILE__, __LINE__))
//#endif  /* ALPHA_ASSERT_CHECK */


#if defined( BROKEN_ASSERT_STDIO_CHECK )
extern FILE* stderr;
#endif  /* BROKEN_ASSERT_STDIO_CHECK */


#if defined( BROKEN_ASSERT_STDLIB_CHECK )
extern void exit ( int );
#endif  /* BROKEN_ASSERT_STDLIB_CHECK */

#endif  /* FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDIO */

#endif  /* FIXINC_WRAP_ASSERT_H_BROKEN_ASSERT_STDLIB */
