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
 * @file rtxBigInt.h 
 */

#ifndef _RTXBIGINT_H_
#define _RTXBIGINT_H_

#include "rtxsrc/rtxContext.h"

/* Big Integer */

typedef struct OSBigInt {
   int       numocts;           /* number of used octets in mag         */
   OSOCTET   *mag;              /* magnitude                            */
   int       sign;              /* sign, can be -1, 0, 1                */

   int       allocated;         /* number of allocated octets for mag   */
   OSBOOL    dynamic;           /* is buffer dynamic?                   */
} OSBigInt;


#ifdef __cplusplus
extern "C" {
#endif

/* BigInt functions */

EXTERNRT void rtxBigIntInit (OSBigInt* pInt);
EXTERNRT int  rtxBigIntSetStr (OSCTXT* pCtxt, OSBigInt* pInt, 
                                const char* value, int radix);
EXTERNRT int  rtxBigIntSetInt64 (OSCTXT* pCtxt, OSBigInt* pInt, 
                                  OSINT64 value);
EXTERNRT int  rtxBigIntSetUInt64 (OSCTXT* pCtxt, OSBigInt* pInt, 
                                   OSUINT64 value);
EXTERNRT int  rtxBigIntSetBytes (OSCTXT* pCtxt, OSBigInt* pInt, 
                                  OSOCTET* value, int vallen);
EXTERNRT int  rtxBigIntGetDataLen (const OSBigInt* pInt);
EXTERNRT int  rtxBigIntGetData (OSCTXT* pCtxt, const OSBigInt* pInt, 
                                 OSOCTET* buffer, int bufSize);
EXTERNRT int  rtxBigIntDigitsNum (const OSBigInt* pInt, int radix);
EXTERNRT int  rtxBigIntCopy (OSCTXT* pCtxt, const OSBigInt* pSrc, OSBigInt* pDst);
EXTERNRT int  rtxBigIntFastCopy (OSCTXT* pCtxt, const OSBigInt* pSrc, OSBigInt* pDst);
EXTERNRT int  rtxBigIntToString (OSCTXT* pCtxt, const OSBigInt* pInt, int radix, 
                                  char* str, int strSize);
EXTERNRT int  rtxBigIntPrint (const OSUTF8CHAR* name, const OSBigInt* bigint, int radix);
EXTERNRT int  rtxBigIntCompare (const OSBigInt* arg1, const OSBigInt* arg2);
EXTERNRT int  rtxBigIntStrCompare (OSCTXT* pCtxt, const char* arg1, 
                                    const char* arg2);
EXTERNRT void rtxBigIntFree (OSCTXT* pCtxt, OSBigInt* pInt);

/* Arithmetic */
EXTERNRT int rtxBigIntAdd 
   (OSCTXT* pctxt, 
    OSBigInt* result, const OSBigInt* arg1, const OSBigInt* arg2);

EXTERNRT int rtxBigIntSubtract 
   (OSCTXT* pctxt, 
    OSBigInt* result, const OSBigInt* arg1, const OSBigInt* arg2);

EXTERNRT int rtxBigIntMultiply 
   (OSCTXT* pctxt, 
    OSBigInt* result, const OSBigInt* arg1, const OSBigInt* arg2);

/* Common */
EXTERNRT unsigned short rtxBigIntBitsPerDigit (int radix);
EXTERNRT short rtxBigIntDigitsPerByte (int halfRadix);
EXTERNRT short rtxBigIntByteRadix (int halfRadix);

#ifdef __cplusplus
}
#endif

#endif /* RTXBIGINT */

