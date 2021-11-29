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

/* This function assumes that inpdata is stream of Unicode chars. 
 * Characters are already decoded from UTF-8 to Unicode by SAX parser. */
int xerDecBMPStr (OSCTXT* pctxt, 
                  ASN1BMPString* outdata)
{
   OSUTF8CHAR* inpdata = (OSUTF8CHAR*) ASN1BUFPTR (pctxt);
   int i, nchars;
   OSUNICHAR* data;

   /* Decode source as an UTF8 string */
   int ch, j;

   nchars = rtxUTF8Len (inpdata);
   if (nchars < 0)
      return LOG_RTERR (pctxt, nchars);

   /* Allocate memory for output data */

   data = (OSUNICHAR*)rtxMemAlloc 
      (pctxt, nchars * sizeof (OSUNICHAR));

   /* Convert Unicode characters to ASCII */

   for (i = j = 0; i < nchars; i++) {
      int sz = INT_MAX;

      ch = rtxUTF8DecodeChar (pctxt, inpdata + j, &sz);

      if (ch < 0)
         return LOG_RTERR_AND_FREE_MEM (pctxt, ch, data);
      j += sz;

      data[i] = (OSUNICHAR) ch;
   }

   outdata->nchars = nchars;
   outdata->data = data; 
   return (0);
}

