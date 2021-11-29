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

#include "rtxsrc/rtxCtype.h"
#include "rtxmlsrc/osrtxml.hh"

EXTXMLMETHOD int rtXmlDecDynHexStr (OSCTXT* pctxt, OSDynOctStr* pvalue)
{
   const OSUTF8CHAR* inpdata = (const OSUTF8CHAR*) OSRTBUFPTR (pctxt);
   const size_t nbytes = OSRTBUFSIZE(pctxt);
   size_t i;
   int stat;
   OSUINT32 nsemiocts = 0;
   OSOCTET* data;

   /* Count octets */
   for (i = 0; i < nbytes; i++) { 
      char c = (char)inpdata[i];
      if (!OS_ISSPACE (c)) {
         if (!OS_ISXDIGIT (c))
            return LOG_RTERRNEW (pctxt, RTERR_INVHEXS);
         nsemiocts++;
      }
   }

   pvalue->numocts = (nsemiocts + 1) / 2;
   data = (OSOCTET*) rtxMemAlloc (pctxt, pvalue->numocts);
   if (data != 0) {
      pvalue->data = data;

      stat = rtXmlDecHexStrValue 
         (pctxt, OSRTBUFPTR (pctxt), OSRTBUFSIZE(pctxt), 
          data, 0, pvalue->numocts);
      if (stat < 0) LOG_RTERR (pctxt, stat); 
   }
   else {
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   }
   return 0;
}


