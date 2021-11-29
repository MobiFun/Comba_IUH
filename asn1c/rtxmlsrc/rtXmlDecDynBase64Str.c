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

EXTXMLMETHOD int rtXmlDecDynBase64Str (OSCTXT* pctxt, OSDynOctStr* pvalue)
{
   const OSUTF8CHAR* const inpdata = (const OSUTF8CHAR*) OSRTBUFPTR (pctxt);
   int stat;
   size_t nocts = 0;
   size_t encLen;
   OSOCTET* data;

   /* Count octets */
   stat = rtXmlGetBase64StrDecodedLen 
      (inpdata, pctxt->buffer.size, &nocts, &encLen);
   if (stat < 0) return LOG_RTERRNEW (pctxt, stat);

   pvalue->numocts = (OSUINT32)nocts;
   data = (OSOCTET*) rtxMemAlloc (pctxt, nocts);
   if (data != 0) {
      pvalue->data = data;

      stat = rtXmlDecBase64StrValue 
         (pctxt, data, 0, nocts, encLen);
   }
   else
      stat = LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   return (stat);
}


