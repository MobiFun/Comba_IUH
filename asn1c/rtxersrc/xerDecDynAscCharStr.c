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

#include "xed_common.hh"

int xerDecDynAscCharStr (OSCTXT* pctxt, 
                         const char** outdata)
{
   OSUTF8CHAR* inpdata = (OSUTF8CHAR*) ASN1BUFPTR (pctxt);
   char* pbuf;
   int i, nchars = 0;

   /* Decode source as an UTF8 string */
   int ch, j;

   nchars = rtxUTF8Len (inpdata);
   if (nchars < 0)
      return LOG_RTERR (pctxt, nchars);

   /* Allocate memory for output data */

   pbuf = (char*)rtxMemAlloc (pctxt, nchars + 1);
   if (pbuf != 0) {
      /* Convert Unicode characters to ASCII */

      for (i = j = 0; i < nchars; i++) {
         int sz = INT_MAX;

         ch = rtxUTF8DecodeChar (pctxt, inpdata + j, &sz);

         if (ch < 0)
            return LOG_RTERR_AND_FREE_MEM (pctxt, ch, pbuf);
         j += sz;

         /* TODO: add logic to validate character */
         pbuf[i] = (char) ch;
      }
   }
   else
      return LOG_RTERR (pctxt, RTERR_NOMEM);

   pbuf[i] = '\0';
   *outdata = pbuf;

   LCHECKXER (pctxt);

   return (0);
}

