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

/*****************************************************************************\
*
* rtxBigInt
* 
* Routines for manipulating with Big Integers.
*
* Author Artem Bolgar.
* version 2.01   07 May, 2004 - addes some tests for failed memory allocations.
* version 2.00   17 Apr, 2003 - converted to rtx
*
* version 1.60   28 Mar, 2003 - bug in rtxBigIntToString fixed
* version 1.46   02 Nov, 2002 - rtxBigIntSetStr and rtxBigIntToString optimized
* version 1.45   20 Sep, 2002 - some fixes, rtxBigIntNegate added (internal)
* version 1.44   05 Aug, 2002 - some funcs are renamed to rtxBigInt<*>
* version 1.43   17 Jul, 2002 - fixed bug with encoding zero value
* version 1.42   09 Jul, 2002 - rtxCompareBigIntStr is added, rtxSetStrToBigInt is modified
* version 1.41   05 Jun, 2002 - some warnings on Solaris were eliminated
*
* version 1.40   02 Jun, 2002 - added rtxMemRealloc
* version 1.02   14 May, 2002 - some fixes
* version 1.01   11 Apr, 2002 - some fixes
\*****************************************************************************/

#include "rtxsrc/rtxBigInt.hh"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"

/* Initializes OSBigInt structure for further usage */
EXTRTMETHOD void rtxBigIntInit (OSBigInt* pInt) {
   pInt->sign = 0;
   pInt->numocts = pInt->allocated = 0;
   pInt->mag = NULL;
   pInt->dynamic = 0;
}

/* Fills BigInt by value from string using radix (2, 8, 10 or 16) */
EXTRTMETHOD int rtxBigIntSetStr (OSCTXT* pCtxt, OSBigInt* pInt, 
   const char* value, int radix) 
{
   const char* p = value, *firstDigPtr = 0;
   int len, numDigits, numWords, firstVal;

   while (*p == ' ') p++;

   /* if radix is zero, look into argument string for the radix */
   if (radix == 0) { 
      radix = 10;
      if (*p == '0') {
         if (p[1] == 'x') { /* hexadecimal string */
            p += 2;
            radix = 16;
         }
         else if (p[1] == 'b') { /* binary string */
            p += 2;
            radix = 2;
         }
         else if (p[1] == 'o') { /* octal string */
            p += 2;
            radix = 8;
         }
      }
   }
   else if (radix != 2 && radix != 8 && radix != 10 && radix != 16)
      return LOG_RTERRNEW (pCtxt, RTERR_INVPARAM);

   numDigits = len = (int)OSCRTLSTRLEN (p);
   if (len == 0)
      return LOG_RTERRNEW (pCtxt, RTERR_BADVALUE); 

   if (radix == 2 || radix == 16) {
      OSOCTET* pdata;
      OSOCTET ub;
      int shiftShift, perByte;

      firstDigPtr = p;

      /* set some variables according to radix */

      if (radix == 2) { 
         shiftShift = 1;
         perByte = 8;
      }
      else {
         shiftShift = 4;
         perByte = 2;
      }

      /* determine is the number positive or negative */

      pInt->sign = 1;
      pInt->numocts = numWords = (len + perByte - 1) / perByte;

      if (pInt->allocated < numWords) {
         pInt->allocated = numWords;
         if (pInt->dynamic) {
            OSOCTET* newmag = 
               rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
            if (newmag == NULL) {
               rtxMemFreeArray (pCtxt, pInt->mag);
               return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            }
            pInt->mag = newmag;
         }
         else { 
            pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
            if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            pInt->dynamic = TRUE;
         }
      }

      OSCRTLMEMSET (pInt->mag, 0, sizeof (pInt->mag[0]) * pInt->numocts);
      pdata = pInt->mag;
      
      numDigits = perByte - (len & (perByte - 1));

      /* encode significant part of number */

      for (; *p != 0; p++) {
         HEXCHARTONIBBLE (*p, ub);
         if (ub == 0xFF || (shiftShift == 1 && ub > 1)) 
            return LOG_RTERRNEW (pCtxt, RTERR_BADVALUE);

         *pdata = (OSOCTET)((*pdata << shiftShift) | ub);
         numDigits++;

         if ((numDigits & (perByte - 1)) == 0) {
            pdata++;
            /* *pdata = 0; */
         }
      }
      firstVal = pInt->mag[0];
   }
   else {
      char group[200], *stop;
      int numBits, firstGroupLen, val;
      int superRadix, groupVal = 0, halfRadix;

      halfRadix = radix/2;
      
      /* Check for minus sign */
      pInt->sign = 1;
      if (*p == '-') {
         if (len == 1)
            return LOG_RTERRNEW (pCtxt, RTERR_BADVALUE); 
         pInt->sign = -1;
         p++;
         numDigits--;
      }
      else firstDigPtr = p;

      /* Skip leading zeros and compute number of digits in magnitude */
      while (*p == '0') numDigits--, p++;

      if (!*p) { /* zero-length int */
         pInt->sign = 0;
         pInt->numocts = 0;
         return 0;
      }

      /* Pre-allocate array of expected size. May be too large but can
       * never be too small. Typically exact. */
      numBits = (int)(((numDigits * rtxBigIntBitsPerDigit(halfRadix)) >> 10) + 1);
      numWords = (numBits + 7) / 8;
      pInt->numocts = numWords;
      if (pInt->allocated < numWords) {
         pInt->allocated = numWords;

         if (pInt->dynamic) {
            OSOCTET* newmag = 
               rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
            if (newmag == NULL) {
               rtxMemFreeArray (pCtxt, pInt->mag);
               return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            }
            pInt->mag = newmag;
         }
         else { 
            pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
            if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            pInt->dynamic = TRUE;
         }
      }
      OSCRTLMEMSET (pInt->mag, 0, sizeof (pInt->mag[0]) * pInt->numocts);

      /* Process first (potentially short) digit group */
      firstGroupLen = numDigits % rtxBigIntDigitsPerByte(halfRadix);
      if (firstGroupLen == 0)
         firstGroupLen = rtxBigIntDigitsPerByte(halfRadix);
      rtxStrncpy (group, sizeof(group), (const char*)p, firstGroupLen);
      p += firstGroupLen;
      pInt->mag[pInt->numocts - 1] = 
         (OSOCTET) (val = strtol (group, &stop, radix));
      if (val < 0 || stop - (char*)&group < firstGroupLen)
         return LOG_RTERRNEW (pCtxt, RTERR_BADVALUE);
      firstVal = val;

      /* Process remaining digit groups */
      superRadix = rtxBigIntByteRadix(halfRadix);
      while (*p) {
         len = rtxBigIntDigitsPerByte(halfRadix);
         rtxStrncpy (group, sizeof(group), (const char*)p, len);
         p += len;
         groupVal = (OSOCTET) (val = strtol (group, &stop, radix));

         if (val < 0 || stop - (char*)&group < len)
            return LOG_RTERRNEW (pCtxt, RTERR_BADVALUE);

         rtxBigIntDestructiveMulAdd
            (pInt->mag, pInt->numocts, superRadix, groupVal);
      }
   }

   /* Negate the magnitude if most significant bit is set to 1 and 
    * inverse the sign */
   if (radix != 10) {
      if ((firstVal & 0x80) && firstDigPtr && *firstDigPtr != '0') {
         rtxBigIntNegate (pInt);
      }
   }

   rtxBigIntRemoveLeadingZeroBytes (pInt);

   return 0;   
}

/* Fills BigInt by OSINT64 value */
EXTRTMETHOD int rtxBigIntSetInt64 (OSCTXT* pCtxt, OSBigInt* pInt, OSINT64 value) {
   unsigned int i = 0;
   
   if (value == 0) {
      pInt->sign = 0;
      pInt->numocts = pInt->allocated = 0;
      return 0;
   }
   
   pInt->sign = (value < 0) ? (value = -value, -1) : 1;
   pInt->numocts = sizeof (OSINT64);

   if (pInt->allocated < pInt->numocts) {
      pInt->allocated = pInt->numocts;
      if (pInt->dynamic) {
         OSOCTET* newmag = 
            rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
         if (newmag == NULL) {
            rtxMemFreeArray (pCtxt, pInt->mag);
            return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         }
         pInt->mag = newmag;
      }
      else { 
         pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
         if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         pInt->dynamic = TRUE;
      }
   }

   for (i = 0; i < sizeof (OSINT64); i++, value >>= 8) {
      pInt->mag[sizeof (OSINT64) - i - 1] = (OSOCTET)(value & 0xFF);
   }
   rtxBigIntRemoveLeadingZeroBytes (pInt);
   return 0;   
} 

EXTRTMETHOD int rtxBigIntSetUInt64 (OSCTXT* pCtxt, OSBigInt* pInt, OSUINT64 value) {
   unsigned int i = 0;
   
   if (value == 0) {
      pInt->sign = 0;
      pInt->numocts = pInt->allocated = 0;
      return 0;
   }

   pInt->sign = 1;
   pInt->numocts = sizeof (OSUINT64);
   if (pInt->allocated < pInt->numocts) {
      pInt->allocated = pInt->numocts;
      if (pInt->dynamic) {
         OSOCTET* newmag = 
            rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
         if (newmag == NULL) {
            rtxMemFreeArray (pCtxt, pInt->mag);
            return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         }
         pInt->mag = newmag;
      }
      else { 
         pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
         if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         pInt->dynamic = TRUE;
      }
   }
   for (i = 0; i < sizeof (OSUINT64); i++, value >>= 8) {
      pInt->mag[sizeof (OSUINT64) - i - 1] = (OSOCTET)(value & 0xFF);
   }
   rtxBigIntRemoveLeadingZeroBytes (pInt);
   return 0;   
} 

/* Fills BigInt by octets' array */
EXTRTMETHOD int rtxBigIntSetBytes (OSCTXT* pCtxt, OSBigInt* pInt, 
   OSOCTET* value, int vallen) 
{
   int i, j, extra, keep;
   OSOCTET *p = value;

   if (*p & 0x80) { /* negative case */
      pInt->sign = -1;
      for (i = 0; i < vallen && *p == 0xFF; i++, p++)
         ; 
      /* Allocate output array.  If all non-sign ints are 0x00, we must
       * allocate space for one extra output int. */
      for (j = i; j < vallen && *p == 0; j++, p++)
         ;
      extra = (j == vallen ? 1 : 0);
      pInt->numocts = vallen - i + extra;
      if (pInt->allocated < pInt->numocts) {
         pInt->allocated = pInt->numocts;
         if (pInt->dynamic) {
            OSOCTET* newmag = 
               rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
            if (newmag == NULL) {
               rtxMemFreeArray (pCtxt, pInt->mag);
               return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            }
            pInt->mag = newmag;
         }
         else { 
            pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
            if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            pInt->dynamic = TRUE;
         }
      }
      OSCRTLMEMSET (pInt->mag, 0, sizeof (pInt->mag[0]) * pInt->numocts);

      /* Copy one's complement of input into output, leaving extra
       * int (if it exists) == 0x00 */
      p = value + i;
      for (keep = i; i < vallen; i++, p++)
         pInt->mag[i - keep + extra] = (OSOCTET)(~(*p));

      /* Add one to one's complement to generate two's complement */
      for (i = pInt->numocts - 1; ++pInt->mag[i] == 0; i--)
         ;
   }
   else { /* positive or zero case */
      for (i = 0; i < vallen && *p == 0; i++, p++)
         ;

      pInt->numocts = vallen - i;
      if (pInt->numocts == 0) {
         pInt->sign = 0;
         return 0;
      }
      pInt->sign = 1;
      if (pInt->allocated < pInt->numocts) {
         pInt->allocated = pInt->numocts;
         if (pInt->dynamic) {
            OSOCTET* newmag = 
               rtxMemReallocArray (pCtxt, pInt->mag, pInt->allocated, OSOCTET);
            if (newmag == NULL) {
               rtxMemFreeArray (pCtxt, pInt->mag);
               return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            }
            pInt->mag = newmag;
         }
         else { 
            pInt->mag = rtxMemAllocArray (pCtxt, pInt->allocated, OSOCTET);
            if (pInt->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
            pInt->dynamic = TRUE;
         }
      }
      OSCRTLMEMCPY (pInt->mag, p, pInt->numocts);
   }
   rtxBigIntRemoveLeadingZeroBytes (pInt);
   return 0;
}

/* Returns number of octets necessary for storing BigInt */
EXTRTMETHOD int rtxBigIntGetDataLen (const OSBigInt* pInt) {
   if (pInt->sign == 0) return 1; /* for only one zero byte */
   /* check the most significant bit, then add one octet (0xFF or 0x00), 
      if necessary */
   if (pInt->sign > 0 && (pInt->mag[0] & 0x80)) 
      return pInt->numocts + 1;
   if (pInt->sign < 0) {
      OSOCTET oct = pInt->mag[0];
      if (pInt->numocts == 1 || (pInt->numocts > 1 && pInt->mag[1] == 0)) 
         oct = (OSOCTET)(~(oct - 1));
      else 
         oct = (OSOCTET)(~oct);
      if (!(oct & 0x80))
         return pInt->numocts + 1;
   }
   return pInt->numocts;
}

/* Copies bytes of the specified BigInt to the array */
EXTRTMETHOD int rtxBigIntGetData (OSCTXT* pCtxt, const OSBigInt* pInt, OSOCTET* buffer, int bufSize) {
   int len = rtxBigIntGetDataLen (pInt), i;
   OSOCTET* dp = buffer + len - 1, *sp = pInt->mag + pInt->numocts - 1;

   if (bufSize < len)
      return LOG_RTERRNEW (pCtxt, RTERR_STROVFLW); 
   if (pInt->sign == 0) {
      *dp = 0;
      return 1;
   }
   if (pInt->sign < 0) {
      for (i = pInt->numocts - 1; i >= 0; i--) {
         *dp-- = (OSOCTET)(-(*sp));
         if (*sp-- != 0) {
            i--;
            break;
         }
      }
      for (; i >= 0; i--, sp--, dp--) {
         *dp = (OSOCTET)(~(*sp));
      }
      if (len - pInt->numocts > 0) { /* we need to add sign byte */
         *dp = 0xFF; 
      }
   }
   else {
      for (i = pInt->numocts - 1; i >= 0; i--) 
         *dp-- = *sp--;
      if (len - pInt->numocts > 0) { /* we need to add sign byte */
         *dp = 0; 
      }
   }
   return len;
}

/* Aproximately returns the number of digits in bigInt */
EXTRTMETHOD int rtxBigIntDigitsNum (const OSBigInt* pInt, int radix) {
   return ((pInt->numocts + 1)*8 << 10)/rtxBigIntBitsPerDigit(radix/2);
}

/* Copies one BigInt to another. Destination BigInt should not be initialized yet */
EXTRTMETHOD int rtxBigIntCopy (OSCTXT* pCtxt, const OSBigInt* pSrc, OSBigInt* pDst) {
   if (pSrc->numocts) {
      pDst->mag = rtxMemAllocArray (pCtxt, pSrc->numocts, OSOCTET);
      if (pDst->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
      OSCRTLMEMCPY (pDst->mag, pSrc->mag, pSrc->numocts);
   }
   else 
      pDst->mag = NULL;
   pDst->dynamic = TRUE;
   pDst->allocated = pSrc->numocts;
   pDst->numocts = pSrc->numocts;
   pDst->sign = pSrc->sign;
   return 0;
}

/* Copies one BigInt to another. This method will not allocate memory for
 * byte buffer if destination BigInt already has allocated enough array.
 * Destination BigInt should be initialized, or at least filled with zeros. */
EXTRTMETHOD int rtxBigIntFastCopy (OSCTXT* pCtxt, const OSBigInt* pSrc, OSBigInt* pDst) {
   if (pDst->allocated < pSrc->numocts) { /* no allocation needed */
      pDst->allocated = pSrc->numocts;
      if (pDst->dynamic) {
         OSOCTET* newmag =
            rtxMemReallocArray (pCtxt, pDst->mag, pDst->allocated, OSOCTET);
         if (newmag == NULL) {
            rtxMemFreeArray (pCtxt, pDst->mag);
            return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         }
         pDst->mag = newmag;
      }
      else {
         pDst->mag = rtxMemAllocArray (pCtxt, pDst->allocated, OSOCTET);
         if (pDst->mag == NULL) return LOG_RTERRNEW (pCtxt, RTERR_NOMEM);
         pDst->dynamic = TRUE;
      }
   }
   OSCRTLMEMCPY (pDst->mag, pSrc->mag, pSrc->numocts);
   pDst->numocts = pSrc->numocts;
   pDst->sign = pSrc->sign;
   return 0;
}

/* An analog of the C/C++ function itoa, but itoa is not in ANSI
 * standard, that's way this function is developed */
static char* intToStr (long value, char *strP, int radix) {
   char buf [34];
   char c, *p, *bufp;

   p = strP;

   /* If the requested radix is invalid, generate an empty result.*/
   if (radix >= 2 && radix <= 16) {
      bufp = buf;
      for (;;) {
         *bufp++ = (char)((unsigned long)value % radix);
         if ((value = (unsigned long)value / radix) == 0)
            break;
      }

      while (bufp != buf) {
         if ((c = *--bufp) < 10)
            *p++ = (char)(c + '0');
         else
            *p++ = (char)((c - 10) + 'A');
      }
   }

   *p = '\0';
   return strP; 
}

/* Converts OSBigInt into string, 
 * Parameter str should points to buffer with strSize size.
 * Use rtxBigIntDigitsNum function to get aproximate digits number
 * and allocate buffer with size rtxBigIntDigitsNum() + 1. It might be
 * slightly greater than necessary, but not less. */

EXTRTMETHOD int rtxBigIntToString (OSCTXT* pCtxt, const OSBigInt* pInt, int radix, 
   char* str, int strSize) 
{
   int stat = 0;

   if (radix == 2 || radix == 16) {
      OSOCTET *pe = pInt->mag + pInt->numocts - 1, shiftShift;
      int perByte, len, sign = pInt->sign;
      char* pstr;

      /* set some variables according to radix */

      if (radix == 2) {
         perByte = 8;
         shiftShift = 1;
      }
      else {
         perByte = 2;
         shiftShift = 4;
      }

      /* check the size of target string */

      len = perByte * rtxBigIntGetDataLen (pInt);
      if (strSize < len + 1)
         return LOG_RTERRNEW (pCtxt, RTERR_STROVFLW);

      pstr = str + len;
      *pstr-- = 0;

      /* convert octets to string */

      while (pe >= pInt->mag) {
         OSOCTET oct;
         int i, shift;

         /* fetch octet */

         if (pInt->sign < 0) {
            
            /* negate octet and make it 2's compliant if necessary */

            oct = (OSOCTET)(~(*pe));
            if (sign < 0) {
               if (++oct != 0) sign = 0;
            }
         }
         else 
            oct = *pe;

         /* convert octet */

         for (i = shift = 0; i < perByte; i++, pstr--, shift += shiftShift) {
            OSINT32 ub = (oct >> shift) & ((OSINTCONST(1) << shiftShift) - 1);
            NIBBLETOHEXCHAR (ub, *pstr);
         }
         pe--;
      }

      /* add leading zeros, if necessary (AB, 03/28/03) */

      while (pstr >= str) {
         *pstr-- = '0';
      }
   }
   else {
      OSBigInt d, q;
      int r, halfRadix = radix/2, ls, i, n = strSize;
      char s[33], *p = str + strSize;

      OSCRTLMEMSET (&q, 0, sizeof (q)); 
      if (radix == 10) 
         rtxBigIntCopy (pCtxt, pInt, &d);
      else 
         rtxBigIntCopyAndInverse (pCtxt, pInt, &d);

      do {
         rtxBigIntDivideByInt (pCtxt, &d, rtxBigIntByteRadix(halfRadix), &q, &r);
         intToStr (r, s, radix);
         ls = (int)OSCRTLSTRLEN (s);
         n -= ls;
         if (n <= 0) {
            stat = RTERR_STROVFLW; 
            break;
         }
         OSCRTLMEMCPY ((p -= ls), s, ls);
         if (q.numocts != 0 || radix != 10) { 
            /* prepend by leading zeros if necessary*/
            for (i = ls; i < rtxBigIntDigitsPerByte(halfRadix); i++) {
               *--p = '0';   
               if (--n <= 0) {
                  stat = RTERR_STROVFLW; 
                  break;
               }
            }
            rtxBigIntFastCopy (pCtxt, &q, &d);
            if (q.numocts == 0 && pInt->sign > 0 && radix != 10 && (r & 0x80)) {
               *--p = '0';
               if (--n <= 0) {
                  stat = RTERR_STROVFLW; 
                  break;
               }
            } 
         }
         else { /* do not add leading zeros, and add sign */
            if (pInt->sign < 0 && radix == 10) {
               *--p = '-';
               if (--n <= 0) {
                  stat = RTERR_STROVFLW; 
                  break;
               }
            }
         }
      } while (q.numocts != 0);

      if (stat == 0) {
         ls = (int)(str + strSize - p);
         if (ls > 0) {
            OSCRTLMEMCPY (str, p, ls);
            str[ls] = 0;
         }
         else *str = 0;
      }
      rtxBigIntFree (pCtxt, &d);
      rtxBigIntFree (pCtxt, &q);
   }
   if (stat != 0) return LOG_RTERRNEW (pCtxt, stat);
   return 0;
}

EXTRTMETHOD int rtxBigIntPrint (const OSUTF8CHAR* name, const OSBigInt* bigint, int radix)
{
   OSCTXT ctxt;
   const char* form = "";
   char *s;
   int dnum, stat;
   
   if ((stat = rtxInitContext (&ctxt)) != 0)
      return (stat);
   dnum = rtxBigIntDigitsNum (bigint, radix) + 1;
   s = rtxMemAllocArray (&ctxt, dnum, char);
   if (s == NULL) return RTERR_NOMEM;
   if (rtxBigIntToString (&ctxt, bigint, radix, s, dnum) == 0) {
      switch (radix) {
         case 16: form = "0x"; break;
         case 8: form = "0o"; break;
         case 2: form = "0b"; break;
      }
      printf ("%s = '%s%s'\n", name, form, s);
   }
   rtxFreeContext (&ctxt);
   return 0;
}

/*
 * Returns -1, 0 or +1 as big-endian unsigned int array arg1 is
 * less than, equal to, or greater than arg2.
 */
EXTRTMETHOD int rtxBigIntCompare (const OSBigInt* arg1, const OSBigInt* arg2) {
   int i;   

   if (arg1->sign == arg2->sign) {
      if (arg1->numocts < arg2->numocts)
         return -arg1->sign;
      if (arg1->numocts > arg2->numocts)
         return arg1->sign;

      /* Argument lengths are equal; compare the values */
      for (i = 0; i < arg1->numocts; i++) {
         long b1 = arg1->mag[i] & LONG_MASK;
         long b2 = arg2->mag[i] & LONG_MASK;
         if (b1 < b2)
            return -arg1->sign;
         if (b1 > b2)
            return arg1->sign;
      }
      return 0;
   }
   return (arg1->sign > arg2->sign) ? 1 : -1;
}

/*
 * Returns -1, 0 or +1 as big integer string arg1 is
 * less than, equal to, or greater than arg2.
 */
EXTRTMETHOD int rtxBigIntStrCompare (OSCTXT* pCtxt, const char* arg1, const char* arg2) {
   OSBigInt a1, a2;
   OSOCTET magbuf1[256], magbuf2[256];
   int rv;

   rtxBigIntInit (&a1);
   a1.mag = (OSOCTET*) magbuf1;
   a1.allocated = sizeof (magbuf1);

   rtxBigIntInit (&a2);
   a2.mag = (OSOCTET*) magbuf2;
   a2.allocated = sizeof (magbuf2);

   rtxBigIntSetStr (pCtxt, &a1, arg1, 0);
   rtxBigIntSetStr (pCtxt, &a2, arg2, 0);
   
   rv = rtxBigIntCompare (&a1, &a2);
   
   rtxBigIntFree (pCtxt, &a1);
   rtxBigIntFree (pCtxt, &a2);
   return rv;
}

EXTRTMETHOD void rtxBigIntFree (OSCTXT* pCtxt, OSBigInt* pInt) {
   if (pInt == 0 || !pInt->dynamic || pInt->mag == 0 || pInt->allocated == 0)
      return;
   rtxMemFreeArray (pCtxt, pInt->mag);
}
