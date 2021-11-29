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

#include "rtbersrc/xd_common.hh"

/***********************************************************************
 *
 *  Routine name: xd_OpenType
 *
 *  Description:  This routine decodes an ASN.1 open type field.
 *                An open type is assumed to be a previously encoded
 *                value which is to be represented in its native
 *                form in the returned C structure.  The user can then
 *                apply subsequent decode routine calls to decode the
 *                value.
 *
 *                This routine stores the current decode pointer in 
 *                the C structure and moves on to the next field.
 *
 *  Inputs:
 *
 *  None
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int	Status of operation.  Returned as function result.
 *  object	struct* Structure containing tag, length, and data pointer.
 *
 **********************************************************************/

int xd_OpenType (OSCTXT *pctxt, 
                 const OSOCTET** object_p2, 
                 OSUINT32* pnumocts)
{
   int	length, status;
   size_t savedByteIndex;
   OSOCTET* pvalue;
   ASN1TAG tag;

   /* Store pointer to data in object */

   pvalue = OSRTBUFPTR (pctxt);
   savedByteIndex = pctxt->buffer.byteIndex;

   /* Advance decode pointer to the next field */

   if ((status = xd_tag_len (pctxt, &tag, &length, XM_ADVANCE)) == 0)
   {
      if (length > 0) {              /* fixed length object  */
         pctxt->buffer.byteIndex += length;
      }                
      else if (length == ASN_K_INDEFLEN) {	/* indefinite length */
         status = xd_MovePastEOC (pctxt);      /* move past EOC marker */
      }
      else if (tag == 0 && length == 0) /* EOC is not allowed as OpenType */
         return LOG_RTERR (pctxt, RTERR_BADVALUE);

      *pnumocts = (int)(pctxt->buffer.byteIndex - savedByteIndex);
   }

   /* It is possible to encouter an EOB condition if the ANY field was	*/
   /* defined as an implicit null field and is the last field in the	*/
   /* buffer (this is common in X.410 messages).  Assume this is the	*/
   /* case if an RTERR_ENDOFBUF status is returned from xd_tag_len..	*/

   if (status == RTERR_ENDOFBUF) {
      rtxErrReset (pctxt);
      status = 0;
   }
   else 
      if (status != 0) return LOG_RTERR (pctxt, status);

   /* If "fast copy" option is not set (ASN1FATSCOPY), copy the open
    * type value into a dynamic memory buffer; otherwise, store the
    * pointer to the value in the decode buffer in the data pointer   
    * argument. */

   if ((pctxt->flags & ASN1FASTCOPY) == 0) {
      *object_p2 = (const OSOCTET*) rtxMemAlloc (pctxt, *pnumocts);
      if (*object_p2 != 0)
         memcpy ((void*)*object_p2, pvalue, *pnumocts);
      else
         return LOG_RTERR (pctxt, RTERR_NOMEM);
   }
   else {
      *object_p2 = pvalue;
   }

   return 0;
} 

