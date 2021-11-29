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
 *  Routine name: pe_<integer>
 *
 *  Description:  The following functions encode integers.  Different
 *                routines handle signed/unsigned and constrained/
 *                unconstrained variations.  There is also a function 
 *                to handle big (> 32 bit) integers.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  value       int     Integer value to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  length      uint    Number of octets required
 *
 **********************************************************************/

EXTPERMETHOD int pe_ConsInteger (OSCTXT* pctxt, 
                    OSINT32 value, OSINT32 lower, OSINT32 upper)
{ 
   OSUINT32 range_value; /*!AB,9/16/02  chgd from UINT to INT to track<0 cond */
   OSUINT32 adjusted_value;
   int stat;

   PU_NEWFIELD (pctxt, "ConsInteger");

   /* Check value against given range */

   if (value < lower || value > upper) {
      rtxErrAddStrParm (pctxt, "'value'");
      rtxErrAddIntParm (pctxt, value);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   /* Adjust range value based on lower/upper signed values and */
   /* other possible conflicts (ED, 6/5/01)..                   */

   if ((upper > 0 && lower >= 0) || (upper <= 0 && lower < 0)) {
      range_value = upper - lower;
      adjusted_value = value - lower;
   }
   else {
      range_value = upper + abs(lower);
      adjusted_value = value + abs(lower);
   }      

   if (range_value != OSUINT32_MAX) { range_value += 1; }

   /* end ED, 6/5/01 */

   if (range_value == 0 || lower > upper)
      return LOG_RTERR (pctxt, RTERR_BADVALUE);
   else if (lower != upper) {
      stat = pe_ConsWholeNumber (pctxt, adjusted_value, range_value);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   PU_SETBITCOUNT (pctxt);

   LCHECKPER (pctxt);

   return 0;
}

