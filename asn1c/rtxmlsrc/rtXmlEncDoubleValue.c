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

#include <math.h>
#include "rtxmlsrc/osrtxml.h"

#define LG2 0.30102999566398119521373889472449

EXTXMLMETHOD int rtXmlEncDoubleValue (OSCTXT* pctxt, OSREAL value,
                         const OSDoubleFmt* pFmtSpec,
                         int defaultPrecision)
{
   char lbuf[512];
   double mantissa;
   int exp, sign = 1;
   int ch, stat;
   char *p = lbuf, *firstZeroInFractionPtr = 0;
   int totalDigits = -1, integerMaxDigits = INT_MAX, integerMinDigits = 1;
   int fractionDigitsNow = 0, fractionMinDigits = 0;
   int fractionDigits = INT_MAX;
   int expMinValue = OSINT16_MIN, expMaxValue = OSINT16_MAX;
   int intPartLen = 1, expMod, expDig;
   char expSymbol = 'E';

   /* special values */
   
   if (rtxIsPlusInfinity (value)) {
      stat = rtxCopyAsciiText (pctxt, "INF");
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      return 0;
   }
   else if (rtxIsMinusInfinity (value)) {
      stat = rtxCopyAsciiText (pctxt, "-INF");
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      return 0;
   }
   else if (rtxIsNaN (value)) {
      stat = rtxCopyAsciiText (pctxt, "NaN");
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      return 0;
   }

   if (value < 0 || rtxIsMinusZero (value)) {
      sign = -1;
      value = -value;
   }

   if (pFmtSpec != 0) {
      if (pFmtSpec->totalDigits > 0)
         totalDigits = pFmtSpec->totalDigits;
      if (pFmtSpec->fractionDigits >= 0)
         fractionDigits = pFmtSpec->fractionDigits;
      if (pFmtSpec->integerMaxDigits >= 0)
         integerMaxDigits = pFmtSpec->integerMaxDigits;
      if (pFmtSpec->integerMinDigits >= 0)
         integerMinDigits = pFmtSpec->integerMinDigits;
      if (pFmtSpec->fractionMinDigits >= 0)
         fractionMinDigits = pFmtSpec->fractionMinDigits;
      if (pFmtSpec->expMinValue > OSINT16_MIN)
         expMinValue = pFmtSpec->expMinValue;
      if (pFmtSpec->expMaxValue < OSINT16_MAX)
         expMaxValue = pFmtSpec->expMaxValue;
      if (pFmtSpec->expSymbol == 'E' || pFmtSpec->expSymbol == 'e')
         expSymbol = (char)pFmtSpec->expSymbol;
   }

   mantissa = frexp (value, &exp);
   
   /* value = mantissa * 2^exp */
   /* We need convert it to mantissa2 * 10^exp2 */

   /* calculate new exponent first. 
      Assume, 2^exp = 10^exp2. In this case exp2 = n*lg 2 */

   exp = (int)(LG2 * (double)exp);

   /* calculate new mantissa. mantissa2 = value/(10^exp2) */

   if (exp == 0)
      mantissa = value; /* 10^0 = 1 */
   else
      mantissa = value/pow (10.0, exp);

   /* now, normalize the mantissa, if necessary*/

   if (mantissa != 0.0) {

      while (mantissa >= 10.0) {
         mantissa = mantissa / 10.0;
         exp ++;
      }
      while (mantissa < 1.0) {
         mantissa = 10.0 * mantissa;
         exp --;
      }
   }

   if (totalDigits < 0)
      totalDigits = defaultPrecision + 1;

   /* Handle sign */

   if (sign < 0 || (pFmtSpec != 0 && pFmtSpec->signPresent)) {
      *p++ = (char)((sign < 0) ? '-' : '+');
   }

   if (pFmtSpec != 0 && pFmtSpec->integerMinDigits >= 0) {

      /* correct exponent accordingly to integer part len */

      intPartLen = integerMinDigits;
      exp -= (intPartLen - 1);
   }
   else {

      /* or, correct integer length accordingly to exponent's 
         min and max values */
      
      if (expMinValue > OSINT16_MIN && exp < expMinValue) {
         intPartLen -= (expMinValue - exp);
         exp = expMinValue;
      }
      else if (expMaxValue < OSINT16_MAX && exp > expMaxValue) {
         intPartLen += (exp - expMaxValue);
         exp = expMaxValue;
      }
      /* modify intPartLen to show small floats without exponent  */
      else if (exp > 0 && exp < 10)  {
         intPartLen = exp + 1;
         exp = 0;
      }

   }
   intPartLen--;
   
   /* round up the mantissa accordingly to precission */

   if (mantissa != 0.0) {
      double correndum;
      int corrpow;

      if (intPartLen > totalDigits - 1) 
         corrpow = -totalDigits + 1;
      else if (fractionDigits == INT_MAX) {
         corrpow = -defaultPrecision;
      }
      else if (intPartLen > 0) 
         corrpow = -((fractionDigits + intPartLen < totalDigits) ? 
                   fractionDigits + intPartLen : totalDigits - 1);
      else
         corrpow = -((fractionDigits < totalDigits) ? fractionDigits : totalDigits - 1);
      correndum = 0.5 * pow (10.0, corrpow);
      mantissa += correndum;

      /* here we need to perform one-step normalization of the mantissa.
         It might be necessary in some cases, when mantissa becomes
         greater than 1.0 after addition of correndum. For example, it
         happens, if value == 0.01 */

      if (mantissa >= 10.0) {
         mantissa = mantissa / 10.0;
         exp ++;
      }
      if (mantissa < 1.0) {
         mantissa = 10.0 * mantissa;
         exp --;
      }
   }

   /* Handle leading zeroes */
   
   if (intPartLen < 0) {

      if (integerMaxDigits > 0) {
         *p++ = '0';
      }
      *p++ = '.';

      while (++intPartLen) {
         fractionDigitsNow++;
         *p++ = '0'; 
      }
      intPartLen--;
   }
   else {
      int i = integerMinDigits - (intPartLen + 1);
      for (; i > 0; i--) {
         *p++ = '0'; 
      }
   }

   /* The real work */
   do {

      ch = (int)mantissa; 
      mantissa = mantissa - ch;

      *p++ = (char)(ch + '0');

      mantissa = 10.0 * mantissa;

      if (intPartLen < 0) {
         fractionDigitsNow++;
         if (ch == 0) {
            if   (firstZeroInFractionPtr == 0)
               firstZeroInFractionPtr = p - 1;
         }
         else firstZeroInFractionPtr = 0;
      }
      if (0 == intPartLen--) { 
         *p++ = '.';
      }

   } while (--totalDigits > 0 && fractionDigitsNow < fractionDigits);

   /* handle trailing zeroes */
   while (intPartLen >= 0) {

      *p++ = '0';

      if (0 == intPartLen--) {
         *p++ = '.';
      }
   }

   /* remove extra zeros in fraction part */

   if (firstZeroInFractionPtr != 0 && fractionDigitsNow > fractionMinDigits) {
      int z = fractionDigitsNow - (int)(p - firstZeroInFractionPtr);
      if (fractionMinDigits > z) {
         firstZeroInFractionPtr += (fractionMinDigits - z);
         fractionDigitsNow -= (int)(p - firstZeroInFractionPtr);
      }
      intPartLen += (int)(p - firstZeroInFractionPtr);
      p = firstZeroInFractionPtr;
   } 

   /* handle trailing zeros in fraction part, if necessary */

   while (fractionDigitsNow < fractionMinDigits) {
      *p++ = '0';
      fractionDigitsNow++;
      intPartLen--;
   }

   /* Handle isolated '.' at end */

   if (-1 == intPartLen) {
      if (pFmtSpec == 0 || !pFmtSpec->pointPresent)
         p--; /* eliminate the decimal point */
   }

   /* exponent's symbol and sign */

   if (exp != 0 || (pFmtSpec != 0 && pFmtSpec->expPresent)) {

      *p++ = expSymbol;
      if (exp < 0 || (pFmtSpec != 0 && pFmtSpec->expSignPresent)) {
         *p++ = (char)((exp < 0) ? '-' : '+');
         exp = -exp;
      }

      /* handle exponent */

      if (exp >= 1000)     { expDig = 4; expMod = 10000; }
      else if (exp >= 100) { expDig = 3; expMod = 1000; }
      else if (exp >= 10)  { expDig = 2; expMod = 100; }
      else                 { expDig = 1; expMod = 10; }

      /* handle leading zeros of exp if necessary */

      if (pFmtSpec != 0) {
         int expDigits = pFmtSpec->expDigits;
         while (expDigits > expDig) {
            *p++ = '0';
            expDigits--;
         }
      }

      while (expMod > 1) {
         int expDiv = expMod/10;
         *p++ = (char)(exp % expMod/expDiv + '0');
         expMod /= 10;
      }
   }
   *p = '\0';
   
   stat = rtxCopyAsciiText (pctxt, lbuf);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (0);
}

