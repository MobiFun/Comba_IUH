/*
 * Copyright (c) 2008 Objective Systems, Inc.
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

#include "rtxsrc/rtxBitDecode.h"
#include "rtxsrc/rtxBuffer.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxStreamCtxtBuf.h"

EXTRTMETHOD int rtxDecBits (OSCTXT* pctxt, OSUINT32* pvalue, OSUINT32 nbits)
{
   OSUINT8 mask;

   RTDIAG2 (pctxt, "~D rtxDecBits: nbits = %d\n", nbits);

   if (nbits == 0) {
      *pvalue = 0;
      return 0;
   }

   if (pctxt->buffer.bitOffset == 0) {
      pctxt->buffer.byteIndex++;
      pctxt->buffer.bitOffset = 8;
   }

   /* If the number of bits is less than the current bit offset, mask   */
   /* off the required number of bits and return..                      */

   if (nbits <= (OSUINT32)pctxt->buffer.bitOffset) {
      /* Check if buffer contains number of bits requested */
      if (pctxt->buffer.byteIndex >= pctxt->buffer.size)
         if (OSRTISSTREAM (pctxt)) {
            int stat = rtxStreamCtxtBufCheck (pctxt);
            if (0 != stat) return LOG_RTERR (pctxt, stat);

            stat = rtxStreamRead (pctxt, 0, 1);
            if (stat < 0) return LOG_RTERR (pctxt, stat);
            else if (stat < 1) 
               return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
         }
         else return LOG_RTERR (pctxt, RTERR_ENDOFBUF);

      pctxt->buffer.bitOffset = (OSINT16)(pctxt->buffer.bitOffset - nbits);

      *pvalue = ((pctxt->buffer.data[pctxt->buffer.byteIndex]) >> 
                 pctxt->buffer.bitOffset) & ((OSINTCONST(1) << nbits) - 1);
   }

   /* Otherwise, we first need to mask off the remaining bits in the    */
   /* current byte, followed by a loop to extract bits from full bytes, */
   /* followed by logic to mask off remaining bits from the start of    */
   /* of the last byte..                                                */

   else {
      /* Check if buffer contains number of bits requested */

      int nbytes = (nbits + (8 - pctxt->buffer.bitOffset) + 7) / 8;
      
      RTDIAG2 (pctxt, "~D rtxDecBits: nbytes = %d\n", nbytes);

      if ((pctxt->buffer.byteIndex + nbytes) > pctxt->buffer.size) {
         if (OSRTISSTREAM (pctxt)) {
            int stat = rtxStreamCtxtBufCheck (pctxt);
            if (0 != stat) return LOG_RTERR (pctxt, stat);

            stat = rtxStreamRead (pctxt, 0, nbytes);
            if (stat < 0) return LOG_RTERR (pctxt, stat);
            else if (stat < nbytes) 
               return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
         }
         else return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
      }

      /* first read current byte remaining bits */
      mask = (OSUINT8)((OSINTCONST(1) << pctxt->buffer.bitOffset) - 1);

      RTDIAG3 (pctxt, "~D rtxDecBits: mask = %x, data[index] = %x\n", 
               (OSUINT32)mask, (OSUINT32)OSRTBUFPTR(pctxt));

      *pvalue = OSRTBUFCUR(pctxt) & mask;

      nbits = (OSUINT32)(nbits - pctxt->buffer.bitOffset);
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.byteIndex++;

      /* second read bytes from next byteIndex */
      while (nbits >= 8) {
         *pvalue = (*pvalue << 8) | 
            (pctxt->buffer.data[pctxt->buffer.byteIndex]);
         pctxt->buffer.byteIndex++;
         nbits -= 8;
      }

      /* third read bits & set bitoffset of the byteIndex */
      if (nbits > 0) {
         pctxt->buffer.bitOffset = (OSUINT16)(8 - nbits);
         *pvalue = (*pvalue << nbits) | 
            ((pctxt->buffer.data[pctxt->buffer.byteIndex]) >> 
             pctxt->buffer.bitOffset);
      }
   }

   return 0;
}

