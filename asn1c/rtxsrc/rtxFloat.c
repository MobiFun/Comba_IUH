/*
 * Copyright (c) 2003-2009 Objective Systems, Inc.
 *
 * This software is furnished under a license and may be used and copied
 * only in accordance with the terms of such license and with the
 * inclusion of the above copyright notice. This software or any other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of the software is hereby
 * transferred.
 *
 * The information in this software is subject to change without notice
 * and should not be construed as a commitment by Objective Systems, Inc.
 *
 * PROPRIETARY NOTICE
 *
 * This software is an unpublished work subject to a confidentiality agreement
 * and is protected by copyright and trade secret law.  Unauthorized copying,
 * redistribution or other use of this work is prohibited.
 *
 * The above notice of copyright on this source code product does not indicate
 * any actual or intended publication of such source code.
 *
 *****************************************************************************/
/**
 * @file rtxFloat.c
 *
 * Implements the IEEE 754 float/double equality tests using ULPs
 * (Units in the Last Place) as proposed by Bruce Dawson
 * in "Comparing floating point numbers".
 * http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
 */

#include "osSysTypes.h"
#include "rtxFloat.h"

/* We tolerate at most one ULP as we want to test if
 * a given real number is close to a boundary. */
#define MAXULPS 1

/* Float: sign[31] exp[30:23] fraction[22:0] */
#define SIGN_MASK_32 ((OSINT32)1 << 31)
#define  EXP_MASK_32 ((OSINT32)255 << 23)
#define FRAC_MASK_32 (~(SIGN_MASK_32|EXP_MASK_32))

#ifndef __SYMBIAN32__
/* Double: sign[63] exp[62:52] fraction[51:0] */
#define SIGN_MASK_64 ((OSINT64)1 << 63)
#define  EXP_MASK_64 ((OSINT64)2047 << 52)
#define FRAC_MASK_64 (~(SIGN_MASK_64|EXP_MASK_64))
#endif

OSBOOL rtxFloatIsInfinite(float A)
{
    /* All exponent bits set to 1, fraction bits to 0 */
    if ((*(OSINT32*)&A & ~SIGN_MASK_32) == EXP_MASK_32) return TRUE;
    else return FALSE;
}

OSBOOL rtxFloatIsNan(float A)
{
    /* All exponent bits set to 1, non-zero fraction */
    OSINT32 exp = *(OSINT32*)&A & EXP_MASK_32;
    OSINT32 frac = *(OSINT32*)&A & FRAC_MASK_32;
    if (exp == EXP_MASK_32 && frac != 0) return TRUE;
    else return FALSE;
}

int rtxFloatSign(float A)
{
    return (int)((*(OSINT32*)&A) & SIGN_MASK_32);
}

#ifndef __SYMBIAN32__
OSBOOL rtxDoubleIsInfinite(double A)
{
    /* All exponent bits set to 1, fraction bits to 0 */
    if ((*(OSINT64*)&A & ~SIGN_MASK_64) == EXP_MASK_64) return TRUE;
    else return FALSE;
}

OSBOOL rtxDoubleIsNan(double A)
{
    /* All exponent bits set to 1, non-zero fraction */
    OSINT64 exp = *(OSINT64*)&A & EXP_MASK_64;
    OSINT64 frac = *(OSINT64*)&A & FRAC_MASK_64;
    if (exp == EXP_MASK_64 && frac != 0) return TRUE;
    else return FALSE;
}

int rtxDoubleSign(double A)
{
    return (int)((*(OSINT64*)&A) & SIGN_MASK_64);
}
#endif

EXTRTMETHOD OSBOOL rtxFloatEqualImpl(float a, float b)
{
   OSINT32 delta;
   OSINT32 aInt = *(OSINT32*)&a;
   OSINT32 bInt = *(OSINT32*)&b;

   /* FLT_MAX is not equal to Infinity */
   if (rtxFloatIsInfinite(a) || rtxFloatIsInfinite(b)) return (OSBOOL)(a == b);

   /* NaN is equal to nothing, not even itself */
   if (rtxFloatIsNan(a) || rtxFloatIsNan(b)) return FALSE;

   /* Only zero can be equal to another real number of opposite sign */
   if (rtxFloatSign(a) != rtxFloatSign(b)) return (OSBOOL)(a == b);

   /* Make a and b lexicographically ordered as a 2s-complement integer */
   if (aInt < 0) aInt = SIGN_MASK_32 - aInt;
   if (bInt < 0) bInt = SIGN_MASK_32 - bInt;

   delta = aInt - bInt;
   if (delta < 0) delta = -delta;
   if (delta <= MAXULPS) return TRUE;
   else return FALSE;
}

#ifndef __SYMBIAN32__
EXTRTMETHOD OSBOOL rtxDoubleEqualImpl(double a, double b)
{
   OSINT64 delta;
   OSINT64 aInt = *(OSINT64*)&a;
   OSINT64 bInt = *(OSINT64*)&b;

   /* FLT_MAX is not equal to Infinity */
   if (rtxDoubleIsInfinite(a) || rtxDoubleIsInfinite(b)) 
      return (OSBOOL)(a == b);

   /* NaN is equal to nothing, not even itself */
   if (rtxDoubleIsNan(a) || rtxDoubleIsNan(b)) return FALSE;

   /* Only zero can be equal to another real number of opposite sign */
   if (rtxDoubleSign(a) != rtxDoubleSign(b)) return (OSBOOL)(a == b);

   /* Make a and b lexicographically ordered as a 2s-complement integer */
   if (aInt < 0) aInt = SIGN_MASK_64 - aInt;
   if (bInt < 0) bInt = SIGN_MASK_64 - bInt;

   delta = aInt - bInt;
   if (delta < 0) delta = -delta;
   if (delta <= MAXULPS) return TRUE;
   else return FALSE;
}
#endif

