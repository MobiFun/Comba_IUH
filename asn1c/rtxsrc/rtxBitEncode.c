/*
 * Copyright (c) 2008 Objective Systems, Inc.
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

#include "rtxsrc/rtxBitEncode.h"
#include "rtxsrc/rtxBuffer.h"
#include "rtxsrc/rtxError.h"

EXTRTMETHOD int rtxEncBit (OSCTXT* pctxt, OSBOOL value)
{
   int stat = 0;

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Adjust bit offset and determine if at end of current byte */

   if (--pctxt->buffer.bitOffset < 0) {
      stat = rtxCheckBuffer (pctxt, 1);
      if (stat < 0) return LOG_RTERR (pctxt, stat);

      pctxt->buffer.byteIndex++;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      pctxt->buffer.bitOffset = 7;
   }

   /* Set single-bit value */

   if (value) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( 1 << pctxt->buffer.bitOffset );
   }

   /* If last bit in octet, set offsets to start new byte */

   if (pctxt->buffer.bitOffset == 0) {
      pctxt->buffer.bitOffset = 8;
      pctxt->buffer.byteIndex++;
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   return stat;
}

EXTRTMETHOD int rtxEncBits (OSCTXT* pctxt, OSUINT32 value, OSUINT32 nbits)
{ 
   int stat = 0;
   int nbytes = (nbits + (8 - pctxt->buffer.bitOffset) + 7) / 8;

   if (nbits == 0) return stat;

   if (pctxt->buffer.bitOffset == 0) {
      pctxt->buffer.byteIndex++;
      pctxt->buffer.bitOffset = 8;
   }

   /* Check buffer space and allocate more memory if necessary */

   stat = rtxCheckBuffer (pctxt, nbytes);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* If start of new byte, init to zero */

   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
   }

   /* Mask off unused bits from the front of the value */

   if (nbits < (sizeof(OSUINT32) * 8))
      value &= ((1 << nbits) - 1);

   /* If bits will fit in current byte, set them and return */

   if (nbits < (unsigned)pctxt->buffer.bitOffset) {
      pctxt->buffer.bitOffset = (short)
         (pctxt->buffer.bitOffset - (short)nbits);

      pctxt->buffer.data[pctxt->buffer.byteIndex] |= 
         ( value << pctxt->buffer.bitOffset );

      return stat;
   }

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

   pctxt->buffer.bitOffset = (short)(8 - nbits);
   if (nbits > 0) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 
         (OSOCTET)((value & ((1 << nbits)-1)) << pctxt->buffer.bitOffset);
   }
   else
      pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;

   return stat;
}
