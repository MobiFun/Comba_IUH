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
 *  Routine name: xd_len
 *
 *  Description:  This routine decodes the length field component of an
 *                ASN.1 message.  It is called by the xd_tag_len routine
 *                which handles the decoding of both the ID and length
 *                fields.
 *
 *  Inputs:
 *
 *  None
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Operation status returned as function result
 *  length      int     Decoded length value returned as function result
 *                      as follows:
 *			>= 0 		fixed length
 *			ASN_K_INDEFLEN	indefinite length
 *
 **********************************************************************/

int xd_len (OSCTXT *pctxt, int *len_p)
{ 
   OSOCTET b = XD_FETCH1 (pctxt);
   register int	i;

   *len_p = 0;

   if (b > 0x80) {
      i = b & 0x7F;

      if (i > 4) 
         return LOG_RTERR (pctxt, ASN_E_INVLEN);

      for (*len_p = 0; i > 0; i--) {
         b = XD_FETCH1 (pctxt);
         *len_p = (*len_p * 256) + b;
      }
   }
   else if (b == 0x80) *len_p = ASN_K_INDEFLEN;
   else *len_p = b;

   /* Length is not indefinite length */
   if (*len_p != ASN_K_INDEFLEN) {
      if (*len_p < 0 || 
          *len_p > (int)(pctxt->buffer.size - pctxt->buffer.byteIndex))
         return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }

   return (0);
} 
