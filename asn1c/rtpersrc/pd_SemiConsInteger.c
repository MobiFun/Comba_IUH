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

EXTPERMETHOD int pd_SemiConsInteger (OSCTXT* pctxt, OSINT32* pvalue, OSINT32 lower)
{
   OSUINT32 tempValue;
   int stat = pd_SemiConsUnsigned (pctxt, &tempValue, OSUINTCONST(0));
   
   if (stat >= 0) {
      *pvalue = lower + (OSINT32) tempValue;
   }

   return stat;
}

EXTPERMETHOD int pd_UnconsInteger (OSCTXT* pctxt, OSINT32* pvalue)
{
   signed char b;
   unsigned char ub;
   OSUINT32 nbytes;
   int stat;

   RTDIAGSTRM2 (pctxt,"pd_UnconsInteger: start\n");

   stat = pd_Length (pctxt, &nbytes);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   RTDIAGSTRM3 (pctxt,"pd_UnconsInteger: nbytes is %d\n", nbytes);

   PU_NEWFIELD (pctxt, "UnconsInteger");

   if (nbytes > 0) {

      /* Align buffer */

      if (pctxt->buffer.aligned) {
         stat = PD_BYTE_ALIGN (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      /* Decode first byte into a signed byte value and assign to integer. */
      /* This should handle sign extension..                               */

      stat = pd_octets (pctxt, (OSOCTET*)&b, 1, 8);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      *pvalue = b;
      nbytes--;

      /* Decode remaining bytes and add to result */

      while (nbytes > 0) {
         stat = pd_octets (pctxt, (OSOCTET*)&ub, 1, 8);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         *pvalue = (*pvalue * 256) + ub;
         nbytes--;
      }
   }
   else {  /* nbytes == 0 */
      *pvalue = 0;
   }

   PU_SETBITCOUNT (pctxt);
   RTDIAGSTRM3 (pctxt,"pd_UnconsInteger: decoded value is "OSINT64FMT"\n", *pvalue);

   return 0;
}
