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
 *  Routine name: xe_charstr
 *
 *  Description:  The following function encodes a value of a 
 *                useful character string type.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct* pointer to context block structure
 *  data        char*   pointer to null-term string to be encoded
 *  tagging     bool    Explicit or implicit tagging specification.
 *  tag         ASN1TAG ASN.1 tag to be applied to the encoded type.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  aal         int     Overall message length.  Returned as function
 *                      result.  Will be negative if encoding fails.
 *
 **********************************************************************/

int xe_charstr (OSCTXT* pctxt, const char* pvalue, 
                ASN1TagType tagging, ASN1TAG tag)
{
   int len = 0;

   if (0 != pvalue) {
      len = xe_octstr 
         (pctxt, (OSOCTET*)pvalue, (int)strlen(pvalue), ASN1IMPL);
   }
   if (len >= 0 && tagging == ASN1EXPL)
      len = xe_tag_len (pctxt, tag, len);

   return (len);
}

