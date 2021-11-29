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
 *  Routine name: pd_DynOctetString
 *
 *  Description:  The following function decodes an octet string value
 *                into a dynamic buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct* pointer to PER context block structure
 *  octstr      struct* pointer to structure to receive decoded value
 *  lbound      int     lower bound value of string size (0 if unconstrained)
 *  ubound      int     upper bound value of string size (MAX if unconstrained)
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     completion status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pd_DynOctetString (OSCTXT* pctxt, ASN1DynOctStr* pOctStr)
{
   OSOCTET* ptmp;
   int nocts, stat;

   /* If "fast copy" option is not set (ASN1FATSCOPY) or if constructed,
    * copy the octet string value into a dynamic memory buffer;
    * otherwise, store the pointer to the value in the decode 
    * buffer in the data pointer argument. */

   if ((pctxt->flags & ASN1FASTCOPY) && 
      (pctxt->buffer.aligned || (pctxt->buffer.bitOffset & 7) == 0)) 
   {
      /* check is it possible to do optimized decoding */

      OSOCTET bit_;
      size_t byteIndex = pctxt->buffer.byteIndex;  /* save byte index */
      OSUINT16 bitOffset = pctxt->buffer.bitOffset; /* save bit offset */

      if (pctxt->buffer.aligned) {
         stat = PD_BYTE_ALIGN0 (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      stat = PD_BIT (pctxt, &bit_); /* read first bit of length determinant */
      if (bit_ == 1 && stat == 0) 
         stat = PD_BIT (pctxt, &bit_); /* read second bit */
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      pctxt->buffer.byteIndex = byteIndex;  /* restore byte index */
      pctxt->buffer.bitOffset = bitOffset;  /* restore bit offset */

      /* if either first or second bit != 0 - not fragmented */

      if (bit_ == 0) { 
         OSUINT32 octcnt;
         
         stat = pd_Length (pctxt, &octcnt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         PU_NEWFIELD (pctxt, "octets");

         pOctStr->numocts = octcnt;
         if (octcnt > 0) {
            pOctStr->data = ASN1BUFPTR (pctxt);

            stat = pd_moveBitCursor (pctxt, octcnt * 8);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
         else 
            pOctStr->data = 0;
         
         PU_SETBITCOUNT (pctxt);
         
         return 0;
      }
   }
   
   nocts = pd_GetComponentLength (pctxt, 8);

   if (nocts < 0) return LOG_RTERR (pctxt, nocts);
   else if (nocts == 0) {
      pOctStr->numocts = 0;
      ptmp = 0;
   }

   /* Allocate memory for the target string */

   else {
      ptmp = (OSOCTET*) rtxMemAlloc (pctxt, nocts);
      if (0 == ptmp) return LOG_RTERR (pctxt, RTERR_NOMEM);
   }

   /* Call static octet string decode function */

   stat = pd_OctetString (pctxt, &pOctStr->numocts, ptmp, nocts);
   if (stat != 0) return LOG_RTERR_AND_FREE_MEM (pctxt, stat, ptmp);

   pOctStr->data = ptmp;

   LCHECKPER (pctxt);

   return 0;
}
