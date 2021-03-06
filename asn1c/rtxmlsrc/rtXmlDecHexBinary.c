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

#include "rtxmlsrc/osrtxml.h"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxErrCodes.h"

EXTXMLMETHOD int rtXmlDecHexBinary (OSRTMEMBUF* pMemBuf, 
                       const OSUTF8CHAR* inpdata, 
                       int length)
{
   int        i, stat, di;
   OSUINT32   nsemiocts = 0, numocts;
   OSOCTET*   pdest;
   OSUINT32   nbits = 0;
   OSOCTET    hbyte;

   /* Count octets */
   for (i = 0; i < length; i++) { 
      char c = (char)inpdata[i];
      if (!OS_ISSPACE (c)) {
         if (!OS_ISXDIGIT (c))
            return LOG_RTERR (pMemBuf->pctxt, RTERR_INVHEXS);
         nsemiocts++;
      }
   }

   numocts = (nsemiocts + 1) / 2;

   stat = rtxMemBufPreAllocate (pMemBuf, numocts);
   if (stat != 0) return LOG_RTERR (pMemBuf->pctxt, stat);

   pdest = OSMEMBUFENDPTR (pMemBuf);
   nbits = pMemBuf->bitOffset;
   if (nbits != 0) {
      pdest--;
      pMemBuf->usedcnt--;
   }

   /* Convert Unicode characters to a bit string value */

   for (i = di = 0; i < length; i++) {
      char c = (char)inpdata[i];
      if (!OS_ISSPACE (c)) {
         if (c >= '0' && c <= '9')
            hbyte = (OSOCTET)(c - '0');
         else if (c >= 'A' && c <= 'F')
            hbyte = (OSOCTET)(c - 'A' + 10);
         else if (c >= 'a' && c <= 'f')
            hbyte = (OSOCTET)(c - 'a' + 10);
         else
            return LOG_RTERR (pMemBuf->pctxt, RTERR_INVHEXS);

         if (nbits % 8 == 0) 
            pdest [di] = (OSOCTET)(hbyte << 4);
         else
            pdest [di++] |= (hbyte & 0xF);

         nbits += 4;
      }
   }

   pMemBuf->bitOffset = (nbits % 8);
   pMemBuf->usedcnt += (nbits + 7) / 8;

   return (0);
}


