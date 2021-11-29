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

#include "xu_common.hh"

static int  xu_ver_cons_len (ASN1CTXT* ctxt_p, int cons_len);

/***********************************************************************
 *
 *  Routine name: xu_verify_len
 *
 *  Description:  This routine will daisy-chain through an ASN.1 message
 *		  and verify that all constructor lengths are valid.
 *
 *		  Note: This routine does not support indefinite length
 *		  encoding.
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  msg_p	byte*	Pointer to ASN.1 message to verify
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status	int	Return status
 *
 **********************************************************************/

int xu_verify_len (ASN1OCTET *msg_p)
{
   ASN1CTXT lctxt;
   int len, stat;

   if ((stat = rtInitContext2 (&lctxt)) != ASN_OK)
      return (stat);
   stat = xd_setp (&lctxt, msg_p, 0, NULL, &len);
   rtFreeContext (&lctxt);
   if (stat != ASN_OK) return (stat);

   return (xu_ver_cons_len (&lctxt, len));
}

static int xu_ver_cons_len (ASN1CTXT* ctxt_p, int cons_len)
{
   ASN1OCTET	*p;
   ASN1TAG	tag;
   int		len, stat;

   while (cons_len > 0)
   {
      p = ASN1BUF_PTR(ctxt_p);

      stat = xd_tag_len (ctxt_p, &tag, &len, XM_ADVANCE);
      if (stat != ASN_OK) return (stat);

      if (tag & TM_CONS) {
	 stat = xu_ver_cons_len (ctxt_p, len);
	 if (stat != ASN_OK) return (stat);
      }
      else {
	 ctxt_p->buffer.byteIndex -= len;
      }

      cons_len -= (int)(ASN1BUF_PTR(ctxt_p) - p);
    }

    return (cons_len == 0 ? ASN_OK : ASN_E_INVLEN);
}
