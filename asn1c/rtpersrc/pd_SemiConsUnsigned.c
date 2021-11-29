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

EXTPERMETHOD int pd_SemiConsUnsigned (OSCTXT* pctxt, OSUINT32* pvalue, OSUINT32 lower)
{
   OSUINT32 nbytes;
   int stat;

   RTDIAGSTRM2 (pctxt,"pd_SemiConsUnsigned: start\n");

   stat = pd_Length (pctxt, &nbytes);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   RTDIAGSTRM3 (pctxt,"pd_SemiConsUnsigned: nbytes is %d\n", nbytes);

   PU_NEWFIELD (pctxt, (lower == 0) ? "UnconsUnsigned" : "SemiConsUnsigned");

   if (nbytes > 0) {
      if (pctxt->buffer.aligned) {
         if ((stat = PD_BYTE_ALIGN (pctxt)) != 0)
            return LOG_RTERR (pctxt, stat);
      }

      stat = pd_bits (pctxt, pvalue, nbytes * 8);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   else
      *pvalue = 0;
   *pvalue += lower;

   PU_SETBITCOUNT (pctxt);
   RTDIAGSTRM3 (pctxt,"pd_UnconsUnsigned: decoded value is %u\n", *pvalue);

   return 0;
}
