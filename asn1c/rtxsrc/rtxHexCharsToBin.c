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

/* Utility function to convert hex characters to binary form.  The function 
   prototype is in rtxCharStr.h */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rtxsrc/osMacros.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxErrCodes.h"

/* This function returns the number of bytes that a conversion of the 
   given hex string to binary will generate */
EXTRTMETHOD int rtxHexCharsToBinCount (const char* hexstr, size_t nchars)
{
   OSUINT32 nsemiocts = 0;
   size_t i;

   if (0 == nchars) nchars = OSCRTLSTRLEN (hexstr);

   for (i = 0; i < nchars; i++) { 
      char c = hexstr[i];
      if (!OS_ISSPACE (c)) {
         if (!OS_ISXDIGIT (c))
            return RTERR_INVHEXS;
         nsemiocts++;
      }
   }

   return (nsemiocts + 1) / 2;
}

/* This function converts the given hex string to binary.  The result is 
   stored in the given binary buffer */
EXTRTMETHOD int rtxHexCharsToBin 
(const char* hexstr, size_t nchars, OSOCTET* binbuf, size_t bufsize)
{
   size_t i, di = 0;
   OSUINT32 nbits = 0;
   OSOCTET hbyte;

   if (OS_ISEMPTY (hexstr)) return 0;
   if (0 == nchars) nchars = OSCRTLSTRLEN (hexstr);

   /* Handle case of string having odd number of bytes */

   i = 0;
   if ((nchars % 2) != 0) {
      OS_HEXCHARTONIBBLE (hexstr[0], binbuf[di]);
      i++; di++; 
      nbits += 8;
   }

   /* Convert characters to binary */

   for ( ; i < nchars; i++) {
      char c = hexstr[i];
      if (!OS_ISSPACE (c)) {
         if (di >= bufsize) {
            return RTERR_STROVFLW;
         }
         if (c >= '0' && c <= '9')
            hbyte = (OSOCTET)(c - '0');
         else if (c >= 'A' && c <= 'F')
            hbyte = (OSOCTET)(c - 'A' + 10);
         else if (c >= 'a' && c <= 'f')
            hbyte = (OSOCTET)(c - 'a' + 10);
         else
            return RTERR_INVHEXS;

         if (nbits % 8 == 0) 
            binbuf [di] = (OSOCTET)(hbyte << 4);
         else
            binbuf [di++] |= (hbyte & 0xF);

         nbits += 4;
      }
   }

   return (nbits/8);
}
