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
#include "rtxsrc/rtxCommonDefs.h"

/***********************************************************************
 *
 *  COMMON ENCODE FUNCTIONS
 *
 **********************************************************************/

/***********************************************************************
 *
 *  Routine name: pe_CheckBuffer
 *
 *  Description:  This routine checks to see if the given buffer
 *                needs to be expanded to hold the given number of
 *                octets.  If so, pe_ExpandBuffer is called to
 *                attempt to expand the buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  nbytes      uint    Number of bytes of additional space required
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pe_CheckBuffer (OSCTXT* pctxt, size_t nbytes)
{
   int stat;

   /* Add one to required bytes because increment logic will always     */
   /* init the byte at the incremented index to zero..                  */

   if ( ( pctxt->buffer.byteIndex + nbytes + 1 ) >= pctxt->buffer.size ) {
      if ((stat = pe_ExpandBuffer (pctxt, nbytes+1)) != 0) {
         return LOG_RTERR (pctxt, stat);
      }
   }

   return 0;
}

/***********************************************************************
 *
 *  Routine name: pe_ExpandBuffer
 *
 *  Description:  This routine expands the given encode buffer if
 *                it is a dynamic buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  nbytes      uint    Number of bytes of additional space required
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pe_ExpandBuffer (OSCTXT* pctxt, size_t nbytes)
{
   if (pctxt->buffer.dynamic) {
      OSOCTET* newbuf;
      size_t newsize;

      /* If dynamic encoding is enabled, expand the current buffer to   */
      /* allow encoding to continue.                                    */

      newsize = pctxt->buffer.size + OSRTMAX (ASN_K_ENCBUFSIZ, nbytes);

      newbuf = (OSOCTET *)rtxMemRealloc (pctxt, pctxt->buffer.data, newsize);
      if (newbuf == NULL) return LOG_RTERR (pctxt, RTERR_NOMEM);

      pctxt->buffer.data = newbuf;
      pctxt->buffer.size = newsize;

      return (0);
   }

   return LOG_RTERR (pctxt, RTERR_BUFOVFLW);
}

/***********************************************************************
 *
 *  Routine name: pe_GetMsgBitCnt
 *
 *  Description:  This routine returns the number of bits in the 
 *                encoded PER message.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  length      int     Length (in bits) of encoded message
 *
 *
 **********************************************************************/

EXTPERMETHOD size_t pe_GetMsgBitCnt (OSCTXT* pctxt)
{
   int numBitsInLastByte = 8 - pctxt->buffer.bitOffset;
   return ((pctxt->buffer.byteIndex * 8) + numBitsInLastByte);
}


/***********************************************************************
 *
 *  Routine name: pe_GetMsgPtr
 *
 *  Description:  This routine returns a pointer to the start of the
 *                encoded message and the length of the message.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  nbytes      uint    Number of bytes of additional space required
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 **********************************************************************/

EXTPERMETHOD OSOCTET* pe_GetMsgPtr (OSCTXT* pctxt, OSINT32* pLength)
{
   if (pLength) *pLength = (OSUINT32)pe_GetMsgLen (pctxt);
   return pctxt->buffer.data;
}

EXTPERMETHOD OSOCTET* pe_GetMsgPtrU (OSCTXT* pctxt, OSUINT32* pLength)
{
   if (pLength) *pLength = (OSUINT32)pe_GetMsgLen (pctxt);
   return pctxt->buffer.data;
}

/***********************************************************************
 *
 *  Routine name: pe_bit
 *
 *  Description:  This routine encodes a single bit in the output
 *                buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  value       bool    Value of bit to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

EXTPERMETHOD int pe_bit (OSCTXT* pctxt, OSBOOL value)
{ 
   int stat;

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Adjust bit offset and determine if at end of current byte */

   if (--pctxt->buffer.bitOffset < 0) {
      if (++pctxt->buffer.byteIndex >= pctxt->buffer.size) {
         if ((stat = pe_ExpandBuffer (pctxt, 1)) != 0) {
            return LOG_RTERR (pctxt, stat);
         }
      }
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      pctxt->buffer.bitOffset = 7;
   }

   /* Set single-bit value */

   if (value) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( OSINTCONST(1) << pctxt->buffer.bitOffset );
   }

   /* If last bit in octet, set offsets to start new byte (ED, 9/7/01) */

   if (pctxt->buffer.bitOffset == 0) {
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.byteIndex++;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   return 0;
}


/***********************************************************************
 *
 *  Routine name: pe_bits
 *
 *  Description:  This routine encodes multiple bits into the 
 *                output buffer.  Up to the number of bits included
 *                in an unsigned integer can be encoded in a single
 *                call.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  value       uint    Value of bits to be encoded
 *  nbits       uint    Number of bits to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

EXTPERMETHOD int pe_bits (OSCTXT* pctxt, OSUINT32 value, OSUINT32 nbits)
{ 
   int nbytes = (nbits + 7)/ 8, stat;

   if (nbits == 0) return 0;

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Mask off unused bits from the front of the value */

   if (nbits < (sizeof(OSUINT32) * 8))
      value &= ((OSINTCONST(1) << nbits) - 1);

   /* If bits will fit in current byte, set them and return */

   if (nbits < (unsigned)pctxt->buffer.bitOffset) {
      pctxt->buffer.bitOffset -= nbits;
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( value << pctxt->buffer.bitOffset );
      return 0;
   }

   /* Check buffer space and allocate more memory if necessary */

   stat = pe_CheckBuffer (pctxt, nbytes);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Set bits in remainder of the current byte and then loop   */
   /* to set bits in subsequent bytes..                         */

   nbits -= pctxt->buffer.bitOffset;
   pctxt->buffer.data[pctxt->buffer.byteIndex++] |= 
      (OSOCTET)( value >> nbits );
   pctxt->buffer.data[pctxt->buffer.byteIndex] = 0; 

   while (nbits >= 8) {
      nbits -= 8;
      pctxt->buffer.data[pctxt->buffer.byteIndex++] = 
         (OSOCTET)( value >> nbits );
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0; 
   }

   /* copy final partial byte */

   pctxt->buffer.bitOffset = (OSUINT16)(8 - nbits);
   if (nbits > 0) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 
         (OSOCTET)((value & ((OSINTCONST(1) << nbits)-1)) << 
pctxt->buffer.bitOffset);
   }
   else
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;

   return 0;
}


/***********************************************************************
 *
 *  Routine name: pe_bitsFromOctet
 *
 *  Description:  This routine encodes bits from a given octet to 
 *                the output buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  value       octet   Value of bits to be encoded
 *  nbits       uint    Number of bits to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

int pe_bitsFromOctet (OSCTXT* pctxt, OSOCTET value, OSUINT32 nbits)
{ 
   int lshift = pctxt->buffer.bitOffset;
   int rshift = 8 - pctxt->buffer.bitOffset;
   OSOCTET mask;

   if (nbits == 0) return 0;

   /* Mask off unused bits from the end of the value */

   if (nbits < 8) {
      switch (nbits) {
      case 1: mask = 0x80; break;
      case 2: mask = 0xC0; break;
      case 3: mask = 0xE0; break;
      case 4: mask = 0xF0; break;
      case 5: mask = 0xF8; break;
      case 6: mask = 0xFC; break;
      case 7: mask = 0xFE; break;
      default: mask = 0; /* should never happen */
      }
      value &= mask;
   }

   /* If we are on a byte boundary, we can do a direct assignment */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = value;
      if (nbits == 8) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      }
      else
         pctxt->buffer.bitOffset -= nbits;
   }

   /* Otherwise, need to set some bits in the first octet and   */
   /* possibly some bits in the following octet..               */

   else {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         (OSOCTET)(value >> rshift);

      pctxt->buffer.bitOffset -= nbits;

      if (pctxt->buffer.bitOffset < 0) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 
            (OSOCTET)(value << lshift);
         pctxt->buffer.bitOffset += 8;
      }
   }

   return 0;
}

/***********************************************************************
 *
 *  Routine name: pe_octets
 *
 *  Description:  This routine encodes full octets into the 
 *                output buffer.  An arbitray string of octets can
 *                be added.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  value       uint    Value of bits to be encoded
 *  nocts       uint    Number of octets to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

EXTPERMETHOD int pe_octets (OSCTXT* pctxt, const OSOCTET* pvalue, OSUINT32 nbits)
{ 
   int i = 0, stat;
   int numFullOcts = nbits / 8;

   if (nbits == 0) return 0;

   /* Check buffer space and allocate more memory if necessary */

   stat = pe_CheckBuffer (pctxt, numFullOcts + 1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (numFullOcts > 0) {

      /* If the current bit offset is 8 (i.e. we don't have a      */
      /* byte started), can copy the string directly to the        */
      /* encode buffer..                                           */

      if (pctxt->buffer.bitOffset == 8) {
         memcpy (&pctxt->buffer.data[pctxt->buffer.byteIndex], pvalue, 
                 numFullOcts);
         pctxt->buffer.byteIndex += numFullOcts;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
         i = numFullOcts;
      }

      /* Else, copy bits */

      else {
         for (i = 0; i < numFullOcts; i++) {
            stat = pe_bitsFromOctet (pctxt, pvalue[i], 8);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
      }
   }

   /* Move remaining bits from the last octet to the output buffer */

   if (nbits % 8 != 0) {
      stat = pe_bitsFromOctet (pctxt, pvalue[i], nbits % 8);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return 0;
}


/***********************************************************************
 *
 *  Routine name: pe_byte_align
 *
 *  Description:  Align the encode buffer on the next byte boundary.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

EXTPERMETHOD int pe_byte_align (OSCTXT* pctxt)
{
   if (pctxt->buffer.aligned && pctxt->buffer.bitOffset != 8) {
      if ((pctxt->buffer.byteIndex + 1) >= pctxt->buffer.size) {
         int stat = pe_ExpandBuffer (pctxt, 1);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
      pctxt->buffer.byteIndex++;
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      PU_SETBITOFFSET (pctxt);
   }

   return 0;
}

/***********************************************************************
 *
 *  Routine name: pe_ConsWholeNumber
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

EXTPERMETHOD int pe_ConsWholeNumber (OSCTXT* pctxt, 
                        OSUINT32 adjusted_value, OSUINT32 range_value)
{ 
   OSUINT32 nocts, range_bitcnt = pu_bitcnt (range_value - 1);
   int stat;

   if (adjusted_value >= range_value && range_value != OSUINT32_MAX) {
      return LOG_RTERR (pctxt, RTERR_BADVALUE);
   }

   /* If unaligned, encode as a non-negative binary integer in the      */
   /* minimum number of bits necessary to represent the range (10.5.6)  */

   if (!pctxt->buffer.aligned) {
      return pe_bits (pctxt, adjusted_value, range_bitcnt);
   }

   /* If aligned, encoding depended on range value (10.5.7) */

   else {  /* aligned */

      /* If range is <= 255, bit-field case (10.5.7a) */

      if (range_value <= 255) {
         return pe_bits (pctxt, adjusted_value, range_bitcnt);
      }

      /* If range is exactly 256, one-octet case (10.5.7b) */

      else if (range_value == 256) {
         stat = pe_byte_align (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         return pe_bits (pctxt, adjusted_value, 8);
      }

      /* If range > 256 and <= 64k (65536), two-octet case (10.5.7c) */

      else if (range_value <= OSINTCONST(65536)) {
         stat = pe_byte_align (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         return pe_bits (pctxt, adjusted_value, 16);
      }

      /* If range > 64k, indefinite-length case (10.5.7d) */

      else {
         /* Encode length determinant as a constrained whole number.    */
         /* Constraint is 1 to max number of bytes needed to hold       */
         /* the target integer value..                                  */

         if (adjusted_value < 256) nocts = 1;
         else if (adjusted_value < OSINTCONST(65536)) nocts = 2;
         else if (adjusted_value < OSINTCONST(0x1000000)) nocts = 3;
         else nocts = 4;

         stat = pe_bits (pctxt, nocts - 1, 2);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         PU_INSLENFLD (pctxt);

         stat = pe_byte_align (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         return pe_NonNegBinInt (pctxt, adjusted_value);
      }
   }
}

/***********************************************************************
 *
 *  Routine name: pe_Length
 *
 *  Description:  This routine encodes a length determinant value
 *                as described in section 10.9 or the X.691 standard.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *  value       uint    Length value to be encoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Completion status of encode operation
 *
 **********************************************************************/

EXTPERMETHOD int pe_Length (OSCTXT* pctxt, OSUINT32 value)
{ 
   OSBOOL extendable;
   Asn1SizeCnst* pSize = 
      pu_checkSize (ACINFO(pctxt)->pSizeConstraint, value, &extendable);
   OSUINT32 lower = (pSize) ? pSize->lower : 0;
   OSUINT32 upper = (pSize) ? pSize->upper : OSUINT32_MAX;
   int enclen, stat;

   /* If size constraints exist and the given length did not fall       */
   /* within the range of any of them, signal constraint violation      */
   /* error..                                                           */

   if (ACINFO(pctxt)->pSizeConstraint && !pSize) {
      rtxErrAddStrParm (pctxt, "'value'");
      rtxErrAddIntParm (pctxt, value);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   /* Reset the size constraint in the context block structure */

   ACINFO(pctxt)->pSizeConstraint = 0;

   /* If size constraint is present and extendable, encode extension    */
   /* bit..                                                             */

   if (extendable) {
      PU_NEWFIELD (pctxt, "length extension");

      stat = (pSize) ?
         pe_bit (pctxt, pSize->extended) : pe_bit (pctxt, 1);

      if (stat != 0) return LOG_RTERR (pctxt, stat);

      PU_SETBITCOUNT (pctxt);
   }

   PU_NEWFIELD (pctxt, "length");

   /* If upper limit is less than 64k, constrained case */

   if (upper < OSINTCONST(65536)) {
      stat = (lower == upper) ? 0 :
         pe_ConsWholeNumber (pctxt, value - lower, upper - lower + 1);
      enclen = (stat == 0) ? value : stat;
   }
   else {
      /* unconstrained case or Constrained with upper bound >= 64K*/
      enclen = pe_UnconsLength (pctxt, value);
   }

   PU_SETBITCOUNT (pctxt);

   if (enclen < 0) return LOG_RTERR (pctxt, enclen);

   return enclen;

}

/* Unconstrained length */

EXTPERMETHOD int pe_UnconsLength (OSCTXT* pctxt, OSUINT32 value)
{
   int enclen, stat;

   if (pctxt->buffer.aligned) {
      stat = pe_byte_align (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* 1 octet case */
   if (value < 128) {
      stat = pe_bits (pctxt, value, 8);
      enclen = (stat == 0) ? value : stat;
   }
   /* 2 octet case */
   else if (value < 16384) {
      if ((stat = pe_bit (pctxt, 1)) == 0)
         stat = pe_bits (pctxt, value, 15);
      enclen = (stat == 0) ? value : stat;
   }
   /* fragmentation case */
   else {
      int multiplier = OSRTMIN (value/16384, 4);
      pe_bit (pctxt, 1);  /* set bit 8 of first octet */
      pe_bit (pctxt, 1);  /* set bit 7 of first octet */
      stat = pe_bits (pctxt, multiplier, 6);
      enclen = (stat == 0) ? 16384 * multiplier : stat;
   }
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return enclen;
}

