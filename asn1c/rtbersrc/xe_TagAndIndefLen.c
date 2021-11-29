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

int xe_TagAndIndefLen (OSCTXT *pctxt, ASN1TAG tag, int length)
{
   int aal, ll;

   /* Encode indefinite length marker */

   aal = xe_len (pctxt, ASN_K_INDEFLEN);
   if (aal < 0) return aal; else aal += length;
         
   /* Encode tag */

   ll = xe_tag (pctxt, tag);
   if (ll < 0) return ll; else aal += ll;

   return aal;
}

