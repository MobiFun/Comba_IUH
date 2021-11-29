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

#include "rtpersrc/pd_common.hh"

/***********************************************************************
 *
 *  Routine name: pd_ConstrainedString
 *
 *  Description:  The following function decodes a constrained
 *                string value.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct* pointer to PER context block structure
 *  data        char**  pointer to pointer to receive null-term string
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     completion status
 *
 **********************************************************************/

EXTPERMETHOD int pd_ConstrainedString (OSCTXT* pctxt, 
                          const char** string, 
                          Asn1CharSet* pCharSet)
{
   if (0 == pCharSet) 
      return LOG_RTERR (pctxt, RTERR_INVPARAM);
   else
      return pd_ConstrainedStringEx (pctxt, string, pCharSet->charSet.data, 
                                     pCharSet->charSetAlignedBits, 
                                     pCharSet->charSetUnalignedBits, 
                                     pCharSet->canonicalSetBits);
}

EXTPERMETHOD int pd_ConstrainedStringEx (OSCTXT* pctxt, 
                            const char** string, 
                            const char* charSet,
                            OSUINT32 abits,  /* aligned bits */
                            OSUINT32 ubits,  /* unaligned bits */
                            OSUINT32 canSetBits)
{
   int   stat;
   char* tmpstr;

   OSUINT32 i, idx, len, nbits = pctxt->buffer.aligned ? abits : ubits;

   /* note: need to save size constraint for use in pu_alignCharStr     */
   /* because it will be cleared in pd_Length from the context..        */
   Asn1SizeCnst* psize = ACINFO(pctxt)->pSizeConstraint;

   /* Decode length */

   stat = pd_Length (pctxt, &len);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Byte-align */

   PU_NEWFIELD (pctxt, "data");

   if (pu_alignCharStr (pctxt, len, nbits, psize)) {
      stat = PD_BYTE_ALIGN (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* Decode data */

   tmpstr = (char*) rtxMemAlloc (pctxt, len+1);
   if (0 != tmpstr) {
      i = 0;
      if (nbits >= canSetBits && canSetBits > 4) {
         for (; i < len; i++) {
            if ((stat = pd_bits (pctxt, &idx, nbits)) == 0) {
               tmpstr[i] = (char) idx;
            }
            else break;
         }
      }
      else if (0 != charSet) {
         size_t nchars = strlen (charSet);
         for (; i < len; i++) {
            if ((stat = pd_bits (pctxt, &idx, nbits)) == 0) {
               if (idx < nchars) {
                  tmpstr[i] = charSet[idx];
               }
               else 
                  return 
                     LOG_RTERR_AND_FREE_MEM (pctxt, RTERR_CONSVIO, tmpstr);
            }
            else break;
         }
      }
      else stat = RTERR_INVPARAM;

      if (stat != 0) 
         return LOG_RTERR_AND_FREE_MEM (pctxt, stat, tmpstr);

      tmpstr[i] = '\0';  /* add null-terminator */
   }
   else
      return LOG_RTERR (pctxt, RTERR_NOMEM);

   *string = tmpstr;

   PU_SETBITCOUNT (pctxt);

   LCHECKPER (pctxt);

   return 0;
}
