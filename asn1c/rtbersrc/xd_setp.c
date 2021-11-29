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
 *  Routine name: xd_setp
 *
 *  Description:  This routine initializes the internal buffer pointer
 *                and message length for decoding a BER message.  It
 *                must be called prior to calling any of the other low
 *                level decode routines.  A call to this routine is
 *                included within each of the high level decode
 *                routines.
 *
 *                The routine takes the given message pointer value and
 *                stores it on a module wide common variable.  It then
 *                parses the message length field to get the overall
 *                length of the message to be decoded and stores it on
 *                a common variable as well.  This length value is
 *                returned to the caller as the function result.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  msgptr      char*   Pointer to the BER message to be decoded.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Status of operation.  Returned as function result.
 *  tag		struct	ASN.1 BER tag located at message pointer.
 *  length      int     Length of message component.  Returned as follows:
 *			>= 0 		component is fixed length
 *			ASN_K_INDEFLEN	component is indefinite length
 *
 **********************************************************************/

int xd_setp (OSCTXT *pctxt, const OSOCTET* msg_p, 
             int msglen, ASN1TAG *tag_p, int *len_p)
{ 
   int	stat, ll;
   ASN1TAG ltag;

   /* Initialize the context for decoding */

   stat = rtxInitContextBuffer 
      (pctxt, (OSOCTET*)msg_p, (msglen > 0) ? msglen : INT_MAX);

   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Reset BER indefinite length and last EOC flags (ED, 1/29/2002) */

   pctxt->flags &= (~(ASN1INDEFLEN | ASN1LASTEOC));

   /* If message is fixed length, add length of ID and length fields 	*/
   /* onto contents field length to get total message length; else set	*/
   /* global message length to indefinite length indicator value...	*/

   stat = xd_tag_len (pctxt, &ltag, &ll, XM_ADVANCE);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (ll == ASN_K_INDEFLEN) {
      pctxt->flags |= ASN1INDEFLEN;
      if (len_p) *len_p = ASN_K_INDEFLEN;
   }
   else {
      pctxt->buffer.size = (size_t)ll + pctxt->buffer.byteIndex;
      if (len_p) *len_p = (int)pctxt->buffer.size;
      if (msglen > 0 && pctxt->buffer.size > (OSUINT32)msglen) {
         stat = ASN_E_INVLEN;
      }
   }

   pctxt->buffer.byteIndex = 0;

   if (tag_p) *tag_p = ltag;

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
} 
