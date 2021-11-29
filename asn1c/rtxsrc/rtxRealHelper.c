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

#include <string.h>

#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxReal.h"

#ifndef __SYMBIAN32__

static const OSUINT32 endian = 0x01020304;
static const OSOCTET *pEndian = (OSOCTET*)&endian;
static int initialized = 0;
static OSREAL value;

/***********************************************************************
 *
 *  Routine name: REAL data type functions
 *
 *  Description:  These functions support the encoding and decoding
 *                of floating point data types.
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

/* Utility function to fetch IEEE plus infinity value
 * The bits for PLUS_INFINITY are  0x7ff0000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetPlusInfinity ()
{
   static int initialized = 0;
   static OSREAL value;
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (OSREAL) - 1] = 0x7f;
         c[sizeof (OSREAL) - 2] = 0xf0;
         OSCRTLMEMSET (c, 0, sizeof (OSREAL) - 2); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0x7f;
         c[1] = 0xf0;
         OSCRTLMEMSET (c + 2, 0, sizeof (OSREAL) - 2); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to fetch IEEE minus infinity value
 * The bits for MINUS_INFINITY are  0xfff0000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetMinusInfinity ()
{
   static int initialized = 0;
   static OSREAL value;
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (OSREAL) - 1] = 0xff;
         c[sizeof (OSREAL) - 2] = 0xf0;
         OSCRTLMEMSET (c, 0, sizeof (OSREAL) - 2); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0xff;
         c[1] = 0xf0;
         OSCRTLMEMSET (c + 2, 0, sizeof (OSREAL) - 2); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to fetch IEEE not-a-number value
 * The bits for NaN are  0x7ff8000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetNaN ()
{
   static int initialized = 0;
   static OSREAL value;
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (OSREAL) - 1] = 0x7f;
         c[sizeof (OSREAL) - 2] = 0xf8;
         OSCRTLMEMSET (c, 0, sizeof (OSREAL) - 2); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0x7f;
         c[1] = 0xf8;
         OSCRTLMEMSET (c + 2, 0, sizeof (OSREAL) - 2); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to fetch IEEE minus zero value
 * The bits for minus zero are  0x8000000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetMinusZero ()
{
   unsigned char* c;

   if (!initialized) {
      c = (unsigned char*) &value;
      if (pEndian [0] == 4) { /* LITTLE ENDIAN */
         c[sizeof (OSREAL) - 1] = 0x80;
         OSCRTLMEMSET (c, 0, sizeof (OSREAL) - 1); 
      }
      else {                  /* BIG ENDIAN */
         c[0] = 0x80;
         OSCRTLMEMSET (c + 1, 0, sizeof (OSREAL) - 1); 
      }
      initialized = 1; /* ED, 3/1/02 */
   }

   return (value);
}

/* Utility function to compare value with NaN */

EXTRTMETHOD OSBOOL rtxIsNaN (OSREAL value)
{
   unsigned char* c = (unsigned char*) &value;
   int i;
   
   if (pEndian [0] == 4) { /* LITTLE ENDIAN */
      if((c[sizeof (OSREAL) - 1] & 0x7F) != 0x7F || 
            (c[sizeof (OSREAL) - 2] & 0xF0) != 0xF0)
         return FALSE;   

      c[sizeof (OSREAL) - 2] &= 0xF; 
      
      for (i = 0; i < sizeof (OSREAL) - 1 ; i++)
         if (c[i])
            return TRUE;
   }
   else {                  /* BIG ENDIAN */
      if((c[0] & 0x7F) != 0x7F || 
            (c[1] & 0xF0) != 0xF0)
         return FALSE;   

      c[1] &= 0xF; 
      
      for (i = 1; i < sizeof (OSREAL) ; i++)
         if (c[i])
            return TRUE;
   }

   return FALSE;      
}

#endif

/* Utility function to compare value with -0.0 */

EXTRTMETHOD OSBOOL rtxIsMinusZero (OSREAL value)
{
   OSREAL mz = rtxGetMinusZero();

   return (OSBOOL)(memcmp (&mz, &value, sizeof (OSREAL)) == 0);
}

/* Utility function to compare value with +INF */

EXTRTMETHOD OSBOOL rtxIsPlusInfinity (OSREAL value)
{
   OSREAL inf = rtxGetPlusInfinity();

   return (OSBOOL)(memcmp (&inf, &value, sizeof (OSREAL)) == 0);
}

/* Utility function to compare value with +INF */

EXTRTMETHOD OSBOOL rtxIsMinusInfinity (OSREAL value)
{
   OSREAL inf = rtxGetMinusInfinity();

   return (OSBOOL)(memcmp (&inf, &value, sizeof (OSREAL)) == 0);
}


#ifdef __SYMBIAN32__

/* These defines replace writeable static memory.  We add the ULL to cast
 * the values to expected Symbian types. */
#define OSYS_PLUS_INFINITY   0x7ff0000000000000ULL
#define OSYS_MINUS_INFINITY  0xfff0000000000000ULL
#define OSYS_NAN             0x7ff8000000000000ULL
#define OSYS_MINUS_ZERO      0x8000000000000000ULL

/* Utility function to fetch IEEE plus infinity value
 * The bits for PLUS_INFINITY are  0x7ff0000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetPlusInfinity ()
{
   return OSYS_PLUS_INFINITY;
}

/* Utility function to fetch IEEE minus infinity value
 * The bits for MINUS_INFINITY are  0xfff0000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetMinusInfinity ()
{
   return OSYS_MINUS_INFINITY;
}

/* Utility function to fetch IEEE not-a-number value
 * The bits for NaN are  0x7ff8000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetNaN ()
{
   return OSYS_NAN;
}

/* Utility function to fetch IEEE minus zero value
 * The bits for minus zero are  0x8000000000000000 (note: assumes
 * IEEE double type). */

EXTRTMETHOD OSREAL rtxGetMinusZero ()
{
   return OSYS_MINUS_ZERO;
}

/* Utility function to compare value with NaN */

EXTRTMETHOD OSBOOL rtxIsNaN (OSREAL value)
{
   unsigned char* c = (unsigned char*) &value;
   int i;
   
	if((c[sizeof (OSREAL) - 1] & 0x7F) != 0x7F || 
			(c[sizeof (OSREAL) - 2] & 0xF0) != 0xF0)
		return FALSE;   

	c[sizeof (OSREAL) - 2] &= 0xF; 
	
	for (i = 0; i < sizeof (OSREAL) - 1 ; i++)
		if (c[i])
			return TRUE;

   return FALSE;      
}
#endif

