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

#include "rtbersrc/asn1ber.h"

const char* berTagToString (ASN1TAG tag, char* buffer, size_t bufsiz)
{
   OSUINT32 idmask = 0xFFFFFFFF >> (((sizeof(ASN1TAG) - 2) * 8) + 3);
   OSUINT32 idcode = ((OSUINT32)tag) & idmask;
   ASN1TAG  tclass = tag & TM_PRIV;
   char lbuf[32];

   switch (tclass) {
   case TM_UNIV: sprintf (lbuf, "[UNIVERSAL %d]", idcode); break;
   case TM_APPL: sprintf (lbuf, "[APPLICATION %d]", idcode); break;
   case TM_CTXT: sprintf (lbuf, "[%d]", idcode); break;
   case TM_PRIV: sprintf (lbuf, "[PRIVATE %d]", idcode); break;
   default:      sprintf (lbuf, "[??? %d]", idcode); break;
   }

   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz;
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';

   return buffer;
}

const char* berTagToDynStr (OSCTXT* pctxt, ASN1TAG tag)
{
   char lbuf[32], *pstr;
   int  len;
   berTagToString (tag, lbuf, sizeof(lbuf));
   len = strlen (lbuf);
   pstr = (char*) rtxMemAlloc (pctxt, len+1);
   strcpy (pstr, lbuf);
   pstr[len] = '\0';
   return pstr;
}

