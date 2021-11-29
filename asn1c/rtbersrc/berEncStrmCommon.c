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

#include "rtbersrc/xse_common.hh"
#include "rtxsrc/rtxStreamDirectBuf.hh"

/***********************************************************************
 *
 *  COMMON ENCODE FUNCTIONS
 *
 **********************************************************************/

int berEncStrmWriteOctet (OSCTXT* pctxt, OSOCTET octet) 
{
   int stat;

   if (OSRTSTREAM_ID (pctxt) == OSRTSTRMID_MEMORY) {
      stat = rtxStreamWrite (pctxt, &octet, 1);
   }
   else {
      stat = rtxCheckBuffer (pctxt, 1);
      if (stat < 0) return LOG_RTERR (pctxt, stat);

      pctxt->buffer.data [pctxt->buffer.byteIndex++] = octet;
   }

   return stat;
}

int berEncStrmWriteOctets 
(OSCTXT* pctxt, const OSOCTET* poctets, size_t numocts) 
{
   int stat;

   if (OSRTSTREAM_ID (pctxt) != OSRTSTRMID_MEMORY) {
      stat = rtxStreamDirectBufCheck (pctxt);
      if (stat < 0) return LOG_RTERR (pctxt, stat);
   }
   stat = rtxStreamWrite (pctxt, poctets, numocts);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return 0;
}

/***********************************************************************
 *
 *  Routine name: berEncStrmIdentifier
 *
 *  Description:  This routine encodes an ASN identifier as used in ASN 
 *                tag and ASN object identifier definitions.  The 
 *                encoding of an identifier is accomplished through a 
 *                series of octets, each of which contains a 7 bit 
 *                unsigned number. The 8th bit (MSB) of each octet is 
 *                used as a continuation flag to indicate that more 
 *                octets follow in the sequence.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  Pointer to ASN.1 context block structure.
 *  ident       uint    Identifier to encode.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  msglen      int     Number of bytes generated to represent given
 *                      identifier value.  Returned as function result.
 *
 **********************************************************************/

int berEncStrmIdentifier (OSCTXT *pctxt, unsigned ident) 
{ 
   unsigned mask = 0x7f;
   int nshifts = 0, stat = 0;

   /* Find starting point in identifier value */
   nshifts = rtxGetIdentByteCount (ident);
   mask <<= (7 * nshifts);

   /* Encode bytes */
   if (nshifts > 0) {
      unsigned lv;
      while (nshifts > 0) {
         mask >>= 7; nshifts--;
         lv = (ident & mask) >> (nshifts * 7);
         if (nshifts != 0) { lv |= 0x80; }
         stat = berEncStrmWriteOctet (pctxt, (OSOCTET)lv);
         if (stat != 0) break;
      }
   }
   else {
      /* encode a single zero byte */
      stat = berEncStrmWriteOctet (pctxt, 0);
   }
   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

int berEncStrmTag (OSCTXT *pctxt, ASN1TAG tag)
{
   int          stat;
   ASN1TAG      ltag;
   OSUINT32     id_code = tag & TM_IDCODE;
   OSOCTET    b, class_form;

   /* Split tag into class/form and ID code components */

   ltag = tag >> ((sizeof(ltag) * 8) - 3);
   class_form = (OSOCTET)(ltag << 5);

   /* Encode components */

   if (id_code < 31) {
      b = (OSOCTET) (class_form + id_code);
      stat = berEncStrmWriteOctet (pctxt, b);
   }
   else {
      b = (OSOCTET) (class_form | TM_B_IDCODE);
      if ((stat = berEncStrmWriteOctet (pctxt, b)) == 0) {
         stat = berEncStrmIdentifier (pctxt, id_code);
      }
   }

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

int berEncStrmLength (OSCTXT *pctxt, int length) 
{ 
   int stat = 0;

   if (length >= 0) {
      int byteCount = rtxIntByteCount (length);
      int shift = 8 * byteCount - 8;

      if (length > 127) { /* extended length */
         
         /* if extended length, add a final byte containing
            number of bytes encoded with bit 8 set .. */
         
         stat = berEncStrmWriteOctet (pctxt, (OSOCTET)(byteCount | 0x80));
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      /* loop to encode length contents */

      for (;shift >= 0; shift -= 8) {
         OSOCTET b = (OSOCTET) ((length >> shift) & 0xff);
         stat = berEncStrmWriteOctet (pctxt, b);
         if (stat != 0) break;
      }
   }
   else if (length == ASN_K_INDEFLEN) {
      /* if indefinite length, write a byte containing
         zero encoded with bit 8 set .. */
      stat = berEncStrmWriteOctet (pctxt, 0x80);
   }
   else stat = length;

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
} 

int berEncStrmTagAndLen (OSCTXT *pctxt, ASN1TAG tag, int length) 
{ 
   int stat;

   if (length < 0 && length != ASN_K_INDEFLEN) return (length);

   stat = berEncStrmTag (pctxt, tag);
   if (stat == 0)
      stat = berEncStrmLength (pctxt, length);

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
} 

int berEncStrmTagAndIndefLen (OSCTXT *pctxt, ASN1TAG tag) 
{ 
   int stat;

   stat = berEncStrmTag (pctxt, tag);
   if (stat == 0) {
      /* if indefinite length, write a byte containing
         zero encoded with bit 8 set .. */
      stat = berEncStrmWriteOctet (pctxt, 0x80);
   }

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
} 

int berEncStrmEOC (OSCTXT *pctxt)
{
   static OSOCTET eoc[] = { 0, 0 };
   int stat = berEncStrmWriteOctets (pctxt, (OSOCTET*)eoc, 2);

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}
