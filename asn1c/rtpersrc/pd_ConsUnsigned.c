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

#ifndef PD_CONSINTFUNC
#define PD_CONSINTFUNC pd_ConsUnsigned
#define OSINTTYPE  OSUINT32
#define OSINTMAX   OSUINT32_MAX
#define PD_CONSWHOLENUMBER pd_ConsWholeNumber
#define RTXERRADDINTPARM rtxErrAddUIntParm
#endif

EXTPERMETHOD int PD_CONSINTFUNC 
(OSCTXT* pctxt, OSINTTYPE* pvalue, OSINTTYPE lower, OSINTTYPE upper)
{ 
   OSINTTYPE range_value;
   OSINTTYPE adjusted_value;
   int stat;

   /* Check for special case: if lower is 0 and upper is OSINTMAX,  */
   /* set range to OSINTMAX; otherwise to upper - lower + 1         */

   range_value = (lower == 0 && upper == OSINTMAX) ?
      OSINTMAX : upper - lower + 1;

   PU_NEWFIELD (pctxt, "ConsUnsigned");

   if (lower != upper) {
      stat = PD_CONSWHOLENUMBER (pctxt, &adjusted_value, range_value);
      if (stat == 0) {
         *pvalue = adjusted_value + lower;

         /* Verify value is within given range */
         if (*pvalue < lower || *pvalue > upper) {
            rtxErrAddElemNameParm (pctxt);
            RTXERRADDINTPARM (pctxt, *pvalue);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }
      }
      else return LOG_RTERR (pctxt, stat);
   }
   else *pvalue = lower;

   PU_SETBITCOUNT (pctxt);

   return 0;
}
