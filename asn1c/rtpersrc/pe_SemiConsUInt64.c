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

#ifndef _NO_INT64_SUPPORT

EXTPERMETHOD int pe_SemiConsUInt64 (OSCTXT* pctxt, OSUINT64 value, OSUINT64 lower)
{
   int nbytes, stat;
   int shift = ((sizeof(value) - 1) * 8) - 1;
   // OSUINT64 mask = OSUI64CONST(1) << ((sizeof(value) * 8) - 1);
   OSUINT64 tempValue;

   value -= lower;

   /* If adjusted value is zero, encode a zero length value and return */

   if (0 == value) {
      return pe_Length (pctxt, 0);
   }

   /* Calculate unsigned number value length */

   for ( ; shift > 0; shift -= 8) {
      tempValue = (value >> shift) & 0x1ff;

      RTDIAGSTRM4 (pctxt, "pe_SemiConsUInt64: shift is %d, "
                   "tempValue is 0x%x\n", shift, tempValue);

      if (tempValue == 0) continue;
      else break;
   }

   nbytes = (shift + 9) / 8;
   RTDIAGSTRM3 (pctxt,"pe_SemiConsUInt64: nbytes is %d\n", nbytes);

   /* Encode length */

   if ((stat = pe_Length (pctxt, nbytes)) < 0) {
      return LOG_RTERR (pctxt, stat);
   }

   PU_NEWFIELD (pctxt, "SemiConsUInt64");

   if (pctxt->buffer.aligned) {
      if ((stat = pe_byte_align (pctxt)) != 0)
         return LOG_RTERR (pctxt, stat);
   }

   /* Encode unsigned value */

   stat = pe_NonNegBinInt64 (pctxt, value);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   return 0;
}

EXTPERMETHOD int pe_UnconsUInt64 (OSCTXT* pctxt, OSUINT64 value)
{
   int nbytes, stat;
   int shift = ((sizeof(value) - 1) * 8) - 1;
   OSUINT64 mask = OSUI64CONST(1) << ((sizeof(value) * 8) - 1);
   OSUINT64 tempValue;

   /* Calculate unsigned number value length */

   for ( ; shift > 0; shift -= 8) {
      tempValue = (value >> shift) & 0x1ff;

      RTDIAGSTRM4 (pctxt, "pe_UnconsUInt64: "
                   "shift is %d, tempValue is 0x%x\n", shift, tempValue);

      if (tempValue == 0) continue;
      else break;
   }

   nbytes = (shift + 9) / 8;
   RTDIAGSTRM3 (pctxt,"pe_UnconsUInt64: nbytes is %d\n", nbytes);

   /* If MS bit in unsigned number is set, add an extra zero byte */

   if ((value & mask) != 0) nbytes++;

   /* Encode length */

   if ((stat = pe_Length (pctxt, nbytes)) < 0) {
      return LOG_RTERR (pctxt, stat);
   }

   PU_NEWFIELD (pctxt, "UnconsUInt64");

   if (pctxt->buffer.aligned) {
      if ((stat = pe_byte_align (pctxt)) != 0)
         return LOG_RTERR (pctxt, stat);
   }

   /* Encode additional zero byte if necessary */

   if ((value & mask) != 0) {
      stat = pe_bitsFromOctet (pctxt, 0, 8);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* Encode unsigned value as a signed number */

   stat = pe_2sCompBinInt64 (pctxt, (OSINT64)value);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   return 0;
}

#endif

