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

#include "rtpersrc/pe_common.hh"

/***********************************************************************
 *
 *  Routine name: pe_OctetString
 *
 *  Description:  The following function encodes an octet string value.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct* pointer to PER context block structure
 *  numocts     int     number of octets in octet string
 *  data        octet*  pointer to buffer containing string to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     completion status of encode operation
 *
 **********************************************************************/

EXTPERMETHOD int pe_OctetString (OSCTXT* pctxt, OSUINT32 numocts, const OSOCTET* data)
{
   int enclen, octidx = 0, stat;
   Asn1SizeCnst* pSizeList = ACINFO(pctxt)->pSizeConstraint;

   for (;;) {
      if ((enclen = pe_Length (pctxt, numocts)) < 0) {
         return LOG_RTERR (pctxt, enclen);
      }

      PU_NEWFIELD (pctxt, "OctetString");

      if (enclen > 0) {
         if (pctxt->buffer.aligned) {
            OSBOOL doAlign;

            stat = pu_BitAndOctetStringAlignmentTest (pSizeList, numocts, 
                                                      FALSE, &doAlign);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            if (doAlign) {
               stat = pe_byte_align (pctxt);
               if (stat != 0) return LOG_RTERR (pctxt, stat);
            }
         }

         stat = pe_octets (pctxt, &data[octidx], enclen * 8);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      PU_SETBITCOUNT (pctxt);

      if (enclen < (int)numocts) {
         numocts -= enclen;
         octidx += enclen;
      }
      else break;
   }

   LCHECKPER (pctxt);

   return 0;
}
