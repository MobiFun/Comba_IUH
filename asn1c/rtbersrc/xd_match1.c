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
 *  Routine name: xd_match1
 *
 *  Description:  This routine compares the tag ID field located at
 *                the current message pointer position with the given
 *                class and ID value. It is an optimized version of xd_match
 *                function, it always assumes single-byte tag and always
 *                advances the buffer cursor.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  Pointer to ASN.1 context block structure
 *  tag         ushort  Tag to match
 *  len_p       int*    Pointer to length
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation.  Returned as function result.
 *  length      int     Length of message component.  Returned as follows:
 *	                     >= 0 		component is fixed length
 *                      ASN_K_INDEFLEN	component is indefinite length   
 *
 ***********************************************************************/

int xd_match1 (OSCTXT *pctxt, OSOCTET tag, int *len_p) 
{
   int stat, len;
   OSRTBuffer *pbuffer = &pctxt->buffer;
   register OSOCTET rtag = pbuffer->data[pbuffer->byteIndex];

   if ((rtag & (~TM_FORM)) != (tag & (~TM_FORM))) {
      return berErrUnexpTag (pctxt, _GENASN1TAG(tag));
   }

   /* Advance the cursor */

   pbuffer->byteIndex++;

   SET_ASN1CONSTAG_BYTE(pctxt, rtag);
   
   if ((stat = XD_LEN (pctxt, &len)) != 0)
      return LOG_RTERR (pctxt, stat);
   
   if (len_p && len == ASN_K_INDEFLEN) {

      /* Verify form of tag is constructed.  If not, indefinite   */
      /* length is invalid (ED, 4/12/02)..                        */

      if (0 == (pctxt->flags & ASN1CONSTAG))
         return LOG_RTERR (pctxt, ASN_E_INVLEN);

   }
   if (len_p) *len_p = len;

  
   return 0;
}
