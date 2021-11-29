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
 *  DECODE FUNCTIONS
 *
 **********************************************************************/

/***********************************************************************
 *
 *  Routine name: pd_moveBitCursor
 *
 *  Description:  This routine moves the bit cursor by the given
 *                relative bit offset (either positive or negative).
 *                It will check boundary conditions to make sure 
 *                the relative move is within the bounds of the
 *                current buffer.
 *                
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  PER context structure
 *  bitOffset   int     Relative bit offset
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Return status of operation
 *
 *
 **********************************************************************/

EXTPERMETHOD int pd_moveBitCursor (OSCTXT* pctxt, int bitOffset)
{
   size_t currBitOffset = PU_GETCTXTBITOFFSET (pctxt);

   RTDIAGSTRM3 (pctxt,"pd_moveBitCursor: bitOffset = %d\n", bitOffset);
   RTDIAGSTRM4 (pctxt,"context before move: bitOffset = %d, byteIndex = %d\n", 
                pctxt->buffer.bitOffset, pctxt->buffer.byteIndex);

   currBitOffset += bitOffset;
   PU_SETCTXTBITOFFSET (pctxt, currBitOffset);

   RTDIAGSTRM4 (pctxt,"context after move: bitOffset = %d, byteIndex = %d\n", 
                pctxt->buffer.bitOffset, pctxt->buffer.byteIndex);

   if (pctxt->buffer.byteIndex > pctxt->buffer.size) {
      return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
   }
      
   return 0;
}

/***********************************************************************
 *
 *  Routine name: pd_bits
 *
 *  Description:  This routine decodes up to sizeof(unsigned) bits
 *                and returns the result in an unsigned integer value.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  PER context structure
 *  value       uint*   Pointer to value to receive decoded result
 *  nbits       uint    Number of bits to extract from buffer
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Return status value
 *
 *
 **********************************************************************/

EXTPERMETHOD int pd_bits (OSCTXT* pctxt, OSUINT32* pvalue, OSUINT32 nbits)
{ 
   unsigned char mask;

   RTDIAGSTRM3 (pctxt, "pd_bits: nbits = %d\n", nbits);

   if (nbits == 0) {
      *pvalue = 0;
      return 0;
   }

   /* If the number of bits is less than the current bit offset, mask   */
   /* off the required number of bits and return..                      */

   if (nbits < (unsigned)pctxt->buffer.bitOffset) {
      /* Check if buffer contains number of bits requested */

      if (pctxt->buffer.byteIndex >= pctxt->buffer.size)
         return LOG_RTERR (pctxt, RTERR_ENDOFBUF);

      pctxt->buffer.bitOffset -= nbits;

      *pvalue = ((pctxt->buffer.data[pctxt->buffer.byteIndex]) >> 
                 pctxt->buffer.bitOffset) & ((OSINTCONST(1) << nbits) - 1);

      return 0;
   }

   /* Otherwise, we first need to mask off the remaining bits in the    */
   /* current byte, followed by a loop to extract bits from full bytes, */
   /* followed by logic to mask of remaining bits from the start of     */
   /* of the last byte..                                                */

   else {
      /* Check if buffer contains number of bits requested */

      int nbytes = (((nbits - pctxt->buffer.bitOffset) + 7) / 8);
      
      RTDIAGSTRM3 (pctxt, "pd_bits: nbytes = %d\n", nbytes);

      if ((pctxt->buffer.byteIndex + nbytes) >= pctxt->buffer.size) {
         return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
      }

      /* first read current byte remaining bits */
      mask = (unsigned char)((OSINTCONST(1) << pctxt->buffer.bitOffset) - 1);

      RTDIAGSTRM4 (pctxt, "pd_bits: mask = %x, data[index] = %x\n", 
              (unsigned)mask, 
              (unsigned)pctxt->buffer.data[pctxt->buffer.byteIndex]);

      *pvalue = (pctxt->buffer.data[pctxt->buffer.byteIndex]) & mask;

      nbits -= pctxt->buffer.bitOffset;
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.byteIndex++;

      /* second read bytes from next byteIndex */
      while (nbits >= 8) {
         *pvalue = (*pvalue << 8) | 
            (pctxt->buffer.data[pctxt->buffer.byteIndex]);
         pctxt->buffer.byteIndex++;
         nbits -= 8;
      }

      /* third read bits & set bitoffset of the byteIndex */
      if (nbits > 0) {
         pctxt->buffer.bitOffset = (OSUINT16)(8 - nbits);
         *pvalue = (*pvalue << nbits) | 
            ((pctxt->buffer.data[pctxt->buffer.byteIndex]) >> 
             pctxt->buffer.bitOffset);
      }

      return 0;
   }
}

/***********************************************************************
 *
 *  Routine name: pd_octets
 *
 *  Description:  This routine transfers bits from the decode
 *                stream to the octet buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  PER context structure
 *  buffer      octet*  Buffer to receive decoded data
 *  bufsiz      unit    Size of buffer (in octets)
 *  nbits       uint    Number of bits to extract from decode stream
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Return status value
 *
 *
 **********************************************************************/

int pd_octets (OSCTXT* pctxt, OSOCTET* pbuffer, OSUINT32 bufsiz,
               OSUINT32 nbits)
{ 
   OSUINT32 nbytes = (nbits + 7) / 8 ;
   OSUINT32 i = 0, j;
   OSUINT32 rshift = pctxt->buffer.bitOffset;
   OSUINT32 lshift = 8 - rshift;
   OSUINT32 nbitsInLastOctet;
   OSOCTET mask;
   int stat;

   /* Check to make sure buffer contains number of bits requested */

   if ((pctxt->buffer.byteIndex + nbytes) > pctxt->buffer.size) {
      return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
   }

/*   if ((pctxt->buffer.byteIndex + nbytes) == pctxt->buffer.size 
       && (rshift + nbits) > 8 ) { 
      return LOG_RTERR (pctxt, RTERR_ENDOFBUF); 
   } */

   /* Check to make sure buffer is big enough to hold requested         */
   /* number of bits..                                                  */

   if (nbytes > bufsiz) {
      return LOG_RTERR (pctxt, RTERR_STROVFLW);
   }

   /* If on a byte boundary, can do a direct memcpy to target buffer */

   if (pctxt->buffer.bitOffset == 8) {
      memcpy (pbuffer, &pctxt->buffer.data[pctxt->buffer.byteIndex], nbytes);
      stat = pd_moveBitCursor (pctxt, nbits);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      i = nbytes - 1; nbits %= 8;
   }
   else {
      while (nbits >= 8) {

         /* Transfer lower bits from stream octet to upper bits of      */
         /* target octet..                                              */

         pbuffer[i] = (OSOCTET)(pctxt->buffer.data[pctxt->buffer.byteIndex++]
            << lshift);

         /* Transfer upper bits from next stream octet to lower bits    */
         /* target octet..                                              */

         pbuffer[i++] |= pctxt->buffer.data[pctxt->buffer.byteIndex]
            >> rshift;

         nbits -= 8;
      }

      /* Copy last partial byte */

      if (nbits >= rshift) {
         pbuffer[i] = (OSOCTET)
            (pctxt->buffer.data[pctxt->buffer.byteIndex++] << lshift);

         nbitsInLastOctet = nbits - rshift;

         if (nbitsInLastOctet > 0) {
            pbuffer[i] |= 
               pctxt->buffer.data[pctxt->buffer.byteIndex] >> rshift;
         }

         pctxt->buffer.bitOffset = (OSUINT16)(8 - nbitsInLastOctet);
      }
      else if (nbits > 0) {  /* nbits < rshift */
         pbuffer[i] = (OSOCTET)
            (pctxt->buffer.data[pctxt->buffer.byteIndex] << lshift);
         pctxt->buffer.bitOffset = (OSUINT16) (rshift - nbits);
      }
   }

   /* Mask unused bits off of last byte */

   if (nbits > 0) {
      mask = 0;
      for (j = 0; j < nbits; j++) {
         mask >>= 1;
         mask |= 0x80;
      }
      pbuffer[i] &= mask;
   }

   return 0;
}

/***********************************************************************
 *
 *  Routine name: pd_ConsWholeNumber
 *
 *  Description:  This routine encompasses the rules to decode a
 *                constrained whole number as specified in section 
 *                10.5 of the X.691 standard.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pdbuf       struct  Pointer to PER decode buffer structure
 *  value       uint*   Pointer to value to receive decoded result
 *  lower       uint    Lower constraint value
 *  upper       uint    Upper constraint value
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Completion status of encode operation
 *
 **********************************************************************/

EXTPERMETHOD int pd_ConsWholeNumber (OSCTXT* pctxt, 
                        OSUINT32* padjusted_value, OSUINT32 range_value)
{ 
   OSUINT32 nocts, range_bitcnt;
   int stat;

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

      /* If range > 256 and <= 64k (65535), two-octet case (10.5.7c) */

      else if (range_value <= OSINTCONST(65536)) {
         stat = PD_BYTE_ALIGN (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         range_bitcnt = 16;
      }

      /* If range > 64k, indefinite-length case (10.5.7d) */

      else {
         stat = pd_bits (pctxt, &nocts, 2);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         PU_INSLENFLD (pctxt);

         stat = PD_BYTE_ALIGN (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         range_bitcnt = (nocts + 1) * 8;
      }
   }

   return pd_bits (pctxt, padjusted_value, range_bitcnt);
}

/***********************************************************************
 *
 *  Routine name: pd_SmallNonNegWholeNumber
 *
 *  Description:  This routine encompasses the rules to decode a
 *                small non-negative whole number as specified in 
 *                section 10.6 of the X.691 standard.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pdbuf       struct  Pointer to PER decode buffer structure
 *  pvalue      uint*   Value to be decoded
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Completion status of encode operation
 *
  **********************************************************************/

EXTPERMETHOD int pd_SmallNonNegWholeNumber (OSCTXT* pctxt, OSUINT32* pvalue)
{ 
   OSBOOL bitValue;
   OSUINT32 len;
   int ret;

   if ((ret = PD_BIT (pctxt, &bitValue)) != 0)
      return ret;

   if (bitValue == 0) {
      return pd_bits (pctxt, pvalue, 6);   /* 10.6.1 */
   }
   else {
      if ((ret = pd_Length (pctxt, &len)) < 0)
         return ret;

      if ((ret = PD_BYTE_ALIGN (pctxt)) != 0)
         return ret;

      return pd_bits (pctxt, pvalue, len*8);
   }
}

/***********************************************************************
 *
 *  Routine name: pd_Length
 *
 *  Description:  This routine encompasses the rules to decode a
 *                length determinant as specified in section 
 *                10.9 of the X.691 standard.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  Pointer to PER decode buffer structure
 *  value       uint*   Pointer to value to receive decoded result
 *  lower       uint    Lower constraint value
 *  upper       uint    Upper constraint value
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Completion status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pd_Length (OSCTXT* pctxt, OSUINT32* pvalue)
{
   Asn1SizeCnst* pSize;
   OSUINT32 lower, upper;
   OSBOOL bitValue, extbit;
   int      stat;

   /* If size constraint is present and extendable, decode extension    */
   /* bit..                                                             */

   if (pu_isExtendableSize(ACINFO(pctxt)->pSizeConstraint)) {
      PU_NEWFIELD (pctxt, "length extension");

      stat = PD_BIT (pctxt, &extbit);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      PU_SETBITCOUNT (pctxt);
   }
   else extbit = 0;

   /* Now use the value of the extension bit to select the proper       */
   /* size constraint range specification..                             */

   pSize = PU_GETSIZECONSTRAINT (pctxt, extbit, pSize);

   lower = (pSize) ? pSize->lower : 0;
   upper = (pSize) ? pSize->upper : OSUINT32_MAX;

   /* Reset the size constraint in the context block structure */

   ACINFO(pctxt)->pSizeConstraint = 0;

   PU_NEWFIELD (pctxt, "length");

   /* If upper limit is less than 64k, constrained case */

   if (upper < OSINTCONST(65536)) {
      if (lower == upper) {
         *pvalue = 0;
         stat = 0;
      }
      else
         stat = pd_ConsWholeNumber (pctxt, pvalue, (upper - lower + 1));

      if (stat == 0) *pvalue += lower;
      else return LOG_RTERR (pctxt, stat);
   }
   else {
      /* unconstrained case OR Constrained with upper bound >= 64K*/

      if (pctxt->buffer.aligned) {
         stat = PD_BYTE_ALIGN (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      stat = PD_BIT (pctxt, &bitValue);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      if (bitValue == 0) {
         stat = pd_bits (pctxt, pvalue, 7);   /* 10.9.3.6 */
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
      else {
         stat = PD_BIT (pctxt, &bitValue);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         if (bitValue == 0) {
            stat = pd_bits (pctxt, pvalue, 14);  /* 10.9.3.7 */
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
         else {
            OSUINT32 multiplier;

            stat = pd_bits (pctxt, &multiplier, 6);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            *pvalue = 16384 * multiplier;

            stat = RT_OK_FRAG;
         }
      }
   }

   PU_SETBITCOUNT (pctxt);

   return stat;
}

EXTPERMETHOD int pd_GetComponentLength (OSCTXT* pctxt, OSUINT32 itemBits)
{
   OSCTXT lctxt;
   OSUINT32 len, totalLen = 0;
   int stat;

   stat = rtInitSubContext (&lctxt, pctxt);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pu_initContextBuffer (&lctxt, pctxt);
   if (stat != 0) return LOG_RTERR_AND_FREE (pctxt, stat, &lctxt);

   ACINFO(&lctxt)->pSizeConstraint = ACINFO(pctxt)->pSizeConstraint;

   for (;;) {
      stat = pd_Length (&lctxt, &len);
      if (stat < 0) return LOG_RTERR_AND_FREE (pctxt, stat, &lctxt);

      totalLen += len;

      if (stat == RT_OK_FRAG) {
         stat = pd_moveBitCursor (&lctxt, len * itemBits);
         if (stat != 0) 
            return LOG_RTERR_AND_FREE (pctxt, stat, &lctxt);
      }
      else break;
   }

   rtFreeContext (&lctxt);

   return totalLen;
}

/***********************************************************************
 *
 *  Routine name: pu_checkSizeConstraint
 *
 *  Description:  This routine called for SeqOf/SetOf has size constraint
 *                range upper bound >= 64K, to check at the end size is not
 *                greater than defined constraint.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  Pointer to PER decode buffer structure
 *  int         size    Decoded length of SeqOf/SetOf data
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Completion status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pu_checkSizeConstraint(OSCTXT* pctxt, int size)
{
   Asn1SizeCnst* pSize;
   OSUINT32 lower, upper;
   OSBOOL extbit;
   int      stat;

   /* If size constraint is present and extendable, decode extension    */
   /* bit..                                                             */

   if (pu_isExtendableSize(ACINFO(pctxt)->pSizeConstraint)) {
      PU_NEWFIELD (pctxt, "length extension");

      stat = PD_BIT (pctxt, &extbit);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      PU_SETBITCOUNT (pctxt);
   }
   else extbit = 0;

   /* Now use the value of the extension bit to select the proper       */
   /* size constraint range specification..                             */

   pSize = pu_getSizeConstraint (pctxt, extbit);

   lower = (pSize) ? pSize->lower : 0;
   upper = (pSize) ? pSize->upper : OSUINT32_MAX;

   if (upper < (OSUINT32)size) {
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   return 0;
}
