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

int berDecStrmOpenType (OSCTXT *pctxt, 
                        const OSOCTET** object_p2, 
                        OSUINT32* pnumocts)
{
   int stat, length, ll2;
   size_t savedByteIndex;
   OSOCTET* pvalue = 0;
   ASN1TAG tag;

   /* Mark stream pointer to data in object */

   savedByteIndex = OSRTSTREAM_BYTEINDEX (pctxt);

   rtxStreamMark (pctxt, 32);

   /* Advance decode pointer to the next field */

   if ((stat = berDecStrmTagAndLen (pctxt, &tag, &length)) == 0) {
      if (length >= 0) {              /* fixed length object  */
         if (tag == 0 && length == 0) /* EOC is not allowed as OpenType */
            return LOG_RTERR (pctxt, RTERR_BADVALUE);

         length += (int)(OSRTSTREAM_BYTEINDEX (pctxt) - savedByteIndex);
         *pnumocts = (OSUINT32)length;

         pvalue = (OSOCTET*) rtxMemAlloc (pctxt, length);
         if (pvalue == 0) return LOG_RTERR (pctxt, RTERR_NOMEM);
         
         rtxStreamReset (pctxt);

         ll2 = rtxStreamRead (pctxt, pvalue, length);
         if (ll2 < 0) stat = ll2;
      }                
      else if (length == ASN_K_INDEFLEN) {   /* indefinite length */
         int ilcnt = 1, len, ll, stat = 0, allocated = 256;

         length = (int)(OSRTSTREAM_BYTEINDEX (pctxt) - savedByteIndex);

         pvalue = (OSOCTET*) rtxMemAlloc (pctxt, allocated);
         if (pvalue == 0) return LOG_RTERR (pctxt, RTERR_NOMEM);
         
         rtxStreamReset (pctxt);

         ll2 = rtxStreamRead (pctxt, pvalue, length);
         if (ll2 < 0) stat = ll2;

         while (stat >= 0 && ilcnt > 0) {
            savedByteIndex = OSRTSTREAM_BYTEINDEX (pctxt);
            rtxStreamMark (pctxt, 32);
            
            stat = berDecStrmTagAndLen (pctxt, &tag, &len);
            if (stat != 0) {
               /* It is possible to encouter an EOB condition if the ANY 
                  field was defined as an implicit null field and is the 
                  last field in the buffer.  Assume this is the
                  case if an RTERR_ENDOFBUF status is returned from 
                  xd_tag_len..	*/
               /* if (stat == RTERR_ENDOFBUF) {
                  rtxErrReset(pctxt);
                  stat = 0;
               } */
               break;
            }

            ll = (int)(OSRTSTREAM_BYTEINDEX (pctxt) - savedByteIndex);

            if (len > 0) 
               ll += len;
               
            if (length + ll > allocated) {
               OSOCTET* pnewvalue;

               allocated = (length + ll + 255) & (~0xFF);
               pnewvalue = (OSOCTET*) rtxMemRealloc (pctxt, pvalue, allocated);
               if (pnewvalue == 0) {
                  stat = RTERR_NOMEM;
                  break;
               }
               pvalue = pnewvalue;
            }
            rtxStreamReset (pctxt);

            ll2 = rtxStreamRead (pctxt, pvalue + length, ll);
            if (ll2 < 0) { stat = ll2; break; }

            length += ll;

            if (len == ASN_K_INDEFLEN) ilcnt++;
            else if (tag == 0 && len == 0) ilcnt--;
         }
         if (stat == 0) {
            *pnumocts = length;
            if (length < allocated) {
               OSOCTET* pnewvalue = 
                  (OSOCTET*) rtxMemRealloc (pctxt, pvalue, length);
               if (pnewvalue == 0) {
                  *pnumocts = 0;
                  return LOG_RTERR_AND_FREE_MEM (pctxt, RTERR_NOMEM, pvalue);
               }
               pvalue = pnewvalue;
            }
         }
         else {
            *pnumocts = 0;
            return LOG_RTERR_AND_FREE_MEM (pctxt, stat, pvalue);
         }
      }
   }
   else {
      /* It is possible to encouter an EOB condition if the ANY field was	*/
      /* defined as an implicit null field and is the last field in the	*/
      /* buffer (this is common in X.410 messages).  Assume this is the	*/
      /* case if an RTERR_ENDOFBUF status is returned from xd_tag_len..	*/

      if (stat == RTERR_ENDOFBUF) {
         rtxErrReset(pctxt);
         stat = 0;
      }
   }
   if (stat < 0) return LOG_RTERR_AND_FREE_MEM (pctxt, stat, pvalue);

   *object_p2 = pvalue;

   return 0;
} 

