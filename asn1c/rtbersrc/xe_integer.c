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

#include "rtbersrc/xe_common.hh"

/***********************************************************************
 *
 *  Routine name: xe_integer
 *
 *  Description:  This routine encodes the ASN.1 universal integer field.
 *                It adds the given integer value to the data buffer
 *                and then, if explicit tagging is specified, adds
 *                the universal tag.  The overall length of the encoded
 *                field is returned.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct  Pointer to ASN.1 context block structure
 *  object      int*    Pointer to integer value to be encoded.
 *  tagging     enum    Explicit or implicit tagging specification.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  aal         int     Overall message length.  Returned as function
 *                      result.  Will be negative if encoding fails.
 *
 **********************************************************************/

int xe_integer (OSCTXT* pctxt, OSINT32 *object_p, ASN1TagType tagging)
{
   OSOCTET lb;
   int  aal = 0;
   OSINT32 temp;

   if (0 == object_p) return LOG_RTERR(pctxt, RTERR_BADVALUE);

   temp = *object_p;

   do {
      lb = (OSOCTET) (temp % 256);
      temp /= 256;
      if (temp < 0 && lb != 0) temp--; /* two's complement adjustment */
      XE_SAFEPUT1 (pctxt, lb);
      aal++;
   } while (temp != 0 && temp != -1 && aal >= 0);

   /* If the value is positive and bit 8 of the leading byte is set,    */
   /* copy a zero byte to the contents to signal a positive number..    */

   if (*object_p > 0 && ((lb & 0x80) == 0x80))
   {
      lb  = 0;
      XE_SAFEPUT1 (pctxt, lb);
      aal++;
   }

   /* If the value is negative and bit 8 of the leading byte is clear,  */
   /* copy a -1 byte (0xFF) to the contents to signal a negative        */
   /* number..                                                          */

   else if (*object_p < 0 && ((lb & 0x80) == 0))
   {
      lb  = 0xFF;
      XE_SAFEPUT1 (pctxt, lb);
      aal++;
   }

   if (tagging == ASN1EXPL && aal > 0) {
      XE_CHKBUF (pctxt, 2);
      XE_PUT2 (pctxt, ASN_ID_INT, (OSOCTET)aal);
      aal += 2;
   }

   LCHECKBER (pctxt);

   return (aal);
}

