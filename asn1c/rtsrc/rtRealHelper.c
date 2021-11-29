/*
 * Copyright (c) 1997-2009 Objective Systems, Inc.
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

#include "rt_common.hh"

#ifdef __SYMBIAN32__
#include "asn1compat.h"
#endif

static ASN1UINT endian = 0x01020304;
static ASN1OCTET *pEndian = (ASN1OCTET*)&endian;

/***********************************************************************
 *
 *  Routine name: REAL data type functions
 *
 *  Description:  These functions support the encoding and decoding
 *                of the ASN.1 REAL data type.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *
 **********************************************************************/

/* Utility function to fetch IEEE not-a-number value
 * The bits for NaN are  0x7ff8000000000000 (note: assumes
 * IEEE double type). */

ASN1REAL rtGetNaN ()
{
   static int initialized = 0;
   static ASN1REAL value;
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (ASN1REAL) - 1] = 0x7f;
         c[sizeof (ASN1REAL) - 2] = 0xf8;
         memset (c, 0, sizeof (ASN1REAL) - 2); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0x7f;
         c[1] = 0xf8;
         memset (c + 2, 0, sizeof (ASN1REAL) - 2); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to fetch IEEE minus zero value
 * The bits for minus zero are  0x8000000000000000 (note: assumes
 * IEEE double type). */

ASN1REAL rtGetMinusZero ()
{
   static int initialized = 0;
   static ASN1REAL value;
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (ASN1REAL) - 1] = 0x80;
         memset (c, 0, sizeof (ASN1REAL) - 1); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0x80;
         memset (c + 1, 0, sizeof (ASN1REAL) - 1); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to compare value with NaN */

ASN1BOOL rtIsNaN (ASN1REAL value)
{
   ASN1REAL nan = rtGetNaN();

   return (ASN1BOOL)(memcmp (&nan, &value, sizeof (ASN1REAL)) == 0);
}

/* Utility function to compare value with -0.0 */

ASN1BOOL rtIsMinusZero (ASN1REAL value)
{
   ASN1REAL mz = rtGetMinusZero();

   return (ASN1BOOL)(memcmp (&mz, &value, sizeof (ASN1REAL)) == 0);
}

/* Utility function to compare value with +INF */

ASN1BOOL rtIsPlusInfinity (ASN1REAL value)
{
   ASN1REAL inf = rtGetPlusInfinity();

   return (ASN1BOOL)(memcmp (&inf, &value, sizeof (ASN1REAL)) == 0);
}

/* Utility function to compare value with +INF */

ASN1BOOL rtIsMinusInfinity (ASN1REAL value)
{
   ASN1REAL inf = rtGetMinusInfinity();

   return (ASN1BOOL)(memcmp (&inf, &value, sizeof (ASN1REAL)) == 0);
}
