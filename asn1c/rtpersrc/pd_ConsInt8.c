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
 *  Routine name: pd_<integer>
 *
 *  Description:  The following functions decode integers.  Different
 *                routines handle signed/unsigned and constrained/
 *                unconstrained variations.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pvalue      int*    Pointer to value to receive decoded result
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Completion status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pd_ConsInt8 (OSCTXT* pctxt, 
                 OSINT8* pvalue, OSINT32 lower, OSINT32 upper)
{ 
   OSUINT32 range_value = upper - lower;
   OSUINT32 adjusted_value;
   int stat;
   OSINT32 value;

   PU_NEWFIELD (pctxt, "ConsInteger");

   /* Adjust range value (ED, 6/5/01) */
   if (range_value != OSUINT32_MAX) { range_value += 1; }

   if (lower > upper)
      return LOG_RTERR (pctxt, RTERR_BADVALUE);
   else if (lower != upper) {
      OSUINT32 range_bitcnt = 0;

      /* If unaligned, decode non-negative binary integer in the minimum   */
      /* number of bits necessary to represent the range (10.5.6)          */

      if (!pctxt->buffer.aligned) {
         range_bitcnt = pu_bitcnt (range_value - 1);
      }

      /* If aligned, encoding depended on range value (10.5.7) */

      else {  /* aligned */

         /* If range is <= 255, bit-field case (10.5.7a) */

         if (range_value <= 255) {
            range_bitcnt = pu_bitcnt (range_value - 1);
         }

         /* If range is exactly 256, one-octet case (10.5.7b) */

         else if (range_value == 256) {
            stat = PD_BYTE_ALIGN (pctxt);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            range_bitcnt = 8;
         }
      }
      stat = pd_bits (pctxt, &adjusted_value, range_bitcnt);
      if (stat == 0) {
         value = adjusted_value + lower;

         /* Verify value is within given range (ED, 1/15/2002) */
         if (value < lower || value > upper)
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         *pvalue = (OSINT8)value;
      }
      else return LOG_RTERR (pctxt, stat);
   }
   else {
      *pvalue = (OSINT8)lower;
   }

   PU_SETBITCOUNT (pctxt);
   RTDIAGSTRM3 (pctxt,"pd_ConsInt8: decoded value is %d\n", *pvalue);

   return 0;
}
