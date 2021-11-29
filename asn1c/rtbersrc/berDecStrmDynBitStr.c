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

#include <limits.h>
#include "rtbersrc/xsd_common.hh"

int berDecStrmDynBitStr (OSCTXT *pctxt, const OSOCTET** ppvalue, 
                         OSUINT32* pnbits, ASN1TagType tagging, int length) 
{ 
   register int stat;
   OSOCTET* pvalue = 0;

   if (tagging == ASN1EXPL) {
      if ((stat = berDecStrmMatchTag (pctxt, ASN_ID_BITSTR, &length, TRUE)) != 0)
      /* RTERR_IDNOTFOU will be logged later, by the generated code, 
         or reset by rtxErrReset (for optional seq elements). */
         return (stat == RTERR_IDNOTFOU) ? stat : LOG_RTERR (pctxt, stat);
   }

   if (pctxt->flags & ASN1CONSTAG) { /* constructed case */
      OSUINT32 totalLen = 0, octidx = 0, oidx = UINT_MAX;
      ASN1CCB ccb;

      ccb.len = length;
      ccb.bytes = OSRTSTREAM_BYTEINDEX (pctxt);
      while (!BS_CHKEND (pctxt, &ccb)) {
         int ll;
         OSOCTET* newbuf;

         if ((stat = berDecStrmMatchTag (pctxt, ASN_ID_BITSTR, &ll, TRUE)) != 0)
            break;
         if (ll <= 0) {
            stat = ASN_E_INVLEN;
            break;
         }

         totalLen += ll;
         newbuf = (OSOCTET*)rtxMemRealloc (pctxt, pvalue, totalLen);
         if (newbuf == NULL) {
            stat = RTERR_NOMEM;
            break;
         }
         pvalue = newbuf;
         oidx = octidx;

         stat = rtxStreamRead (pctxt, pvalue + octidx, ll);
         if (stat < 0) break; else stat = 0;

         octidx = totalLen;
      }

      /* !AB, 07/09/2004 */
      stat = (stat != 0) ? stat : ccb.stat;
      if (stat != 0) 
         return LOG_RTERR_AND_FREE_MEM (pctxt, stat, pvalue);

      if (oidx != UINT_MAX) { 
         
         /* fetch unused bit count and remove it from bit array */
         
         OSOCTET c = pvalue [oidx];
         if (c > 7) /* initial octet should be 0..7 */
            return LOG_RTERR_AND_FREE_MEM (pctxt, RTERR_BADVALUE, pvalue);
         if (octidx - oidx - 1 > 0)
            memcpy (&pvalue [oidx], &pvalue [oidx + 1], octidx - oidx - 1);
         totalLen--;
         *pnbits = totalLen * 8 - c;
      }
      else 
         *pnbits = totalLen * 8;

      if (length == ASN_K_INDEFLEN) {
         stat = berDecStrmMatchEOC (pctxt);
         if (stat != 0) 
            return LOG_RTERR_AND_FREE_MEM (pctxt, stat, pvalue);
      }
   }
   else { /* primitive case */
      if (length < 0) 
         return LOG_RTERR (pctxt, ASN_E_INVLEN);
      if (length > 0) {
         OSOCTET b;
         int c, numToRead = length - 1;

         stat = rtxStreamRead (pctxt, &b, 1);
         if (stat < 0) return LOG_RTERR (pctxt, stat); else c = b;

         if (c > 7) /* initial octet should be 0..7 */
            return LOG_RTERR (pctxt, RTERR_BADVALUE);

         if (numToRead == 0) {
            if (c == 0)
               *pnbits = 0;
            else
               return LOG_RTERR (pctxt, ASN_E_INVLEN);
         }
         else {
            *pnbits = (numToRead * 8) - c;
         
            pvalue = (OSOCTET*)rtxMemAlloc (pctxt, numToRead);
            if (pvalue == 0) return LOG_RTERR (pctxt, RTERR_NOMEM);

            stat = rtxStreamRead (pctxt, pvalue, numToRead);
            if (stat < 0) 
               return LOG_RTERR_AND_FREE_MEM (pctxt, stat, pvalue);
         }
      }
      else {
         *pnbits = 0;
      }
   }
   *ppvalue = pvalue;

   return 0;
} 
