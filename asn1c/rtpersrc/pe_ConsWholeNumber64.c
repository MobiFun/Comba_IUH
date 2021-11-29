#include "rtpersrc/pe_common.hh"

/***********************************************************************
 *
 *  Routine name: pe_ConsWholeNumber64
 *
 *  Description:  This routine encompasses the rules to encode a
 *                constrained whole number as specified in section 
 *                10.5 of the X.691 standard.
 *
 *  Inputs:
 *
 *  Name             Type    Description
 *  ----             ----    -----------
 *  pctxt           struct* Pointer to ASN.1 PER context structure
 *  adjusted_value   uint    Value to be encoded
 *  range_value      uint    Lower - Upper + 1
 *
 *  Outputs:
 *
 *  Name             Type    Description
 *  ----             ----    -----------
 *  status           int     Completion status of encode operation
 *
  **********************************************************************/

#ifndef _NO_INT64_SUPPORT

EXTPERMETHOD int pe_ConsWholeNumber64 (OSCTXT* pctxt, 
                          OSUINT64 adjusted_value, OSUINT64 range_value)
{ 
   int stat;

   if (adjusted_value >= range_value && range_value != OSUINT64MAX) {
      return LOG_RTERR (pctxt, RTERR_BADVALUE);
   }

   if (range_value <= OSUINT32_MAX) {
      stat = pe_ConsWholeNumber (pctxt, (OSUINT32)adjusted_value, 
         (OSUINT32)range_value);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   else {
      OSUINT32 nocts, range_bitcnt = pu_bitcnt64 (range_value - 1);

      /* If unaligned, encode as a non-negative binary integer in the      */
      /* minimum number of bits necessary to represent the range (10.5.6)  */

      if (!pctxt->buffer.aligned) {
         stat = pe_bits64 (pctxt, adjusted_value, range_bitcnt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      /* If aligned, encoding depended on range value (10.5.7) */

      else {  /* aligned */

         /* If range > 64k, indefinite-length case (10.5.7d) */
         /* Encode length determinant as a constrained whole number.    */
         /* Constraint is 1 to max number of bytes needed to hold       */
         /* the target integer value..                                  */

         if (adjusted_value == 0) nocts = 1;
         else nocts = (pu_bitcnt64 (adjusted_value) + 7) /8;
         

         stat = pe_bits (pctxt, nocts - 1, 3);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         PU_INSLENFLD (pctxt);

         stat = pe_byte_align (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         stat = pe_NonNegBinInt64 (pctxt, adjusted_value);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }
   return 0;
}

#endif 

