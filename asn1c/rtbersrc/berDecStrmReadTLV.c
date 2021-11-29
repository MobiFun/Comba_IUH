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

#include "rtbersrc/xsd_common.hh"

int berDecStrmGetTLVLength (OSCTXT* pctxt)
{
   int len, stat, totalLen;
   ASN1TAG tag;

   stat = rtxStreamDirectBufCheck (pctxt);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   if ((stat = rtxStreamMark (pctxt, 32)) != 0) {
      return LOG_RTERR (pctxt, stat);
   }

   if ((stat = berDecStrmTagAndLen (pctxt, &tag, &len)) != 0) {
      return LOG_RTERR (pctxt, stat);
   }
   totalLen = (int)(pctxt->pStream->markedBytesProcessed) + len;

   if ((stat = rtxStreamReset (pctxt)) != 0) {
      return LOG_RTERR (pctxt, stat);
   }

   return totalLen;
}

int berDecStrmReadTLV (OSCTXT* pctxt, OSOCTET* buf, size_t bufsiz)
{
   int len;

   if (0 == buf || bufsiz < 2) 
      return LOG_RTERR (pctxt, RTERR_INVPARAM);

   len = berDecStrmGetTLVLength (pctxt);
   if (len < 0) return LOG_RTERR (pctxt, len);
   else if (len <= (int)bufsiz) {
      return rtxStreamBlockingRead (pctxt, buf, bufsiz);
   }
   else return LOG_RTERR (pctxt, RTERR_BUFOVFLW);
}

int berDecStrmReadDynTLV (OSCTXT* pctxt, OSOCTET** ppbuf)
{
   int len;

   if (0 == ppbuf) return LOG_RTERR (pctxt, RTERR_INVPARAM);

   len = berDecStrmGetTLVLength (pctxt);
   if (len < 0) return LOG_RTERR (pctxt, len);

   *ppbuf = (OSOCTET*) rtxMemAlloc (pctxt, len);
   if (0 == *ppbuf) return LOG_RTERR (pctxt, RTERR_NOMEM);

   return rtxStreamBlockingRead (pctxt, *ppbuf, len);
}
