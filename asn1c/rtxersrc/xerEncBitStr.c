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

#include "xee_common.hh"

int xerEncBitStr (OSCTXT* pctxt, OSUINT32 nbits, 
                  const OSOCTET* data, 
                  const char* elemName, 
                  ASN1StrType outputType)
{
   const char* attributes = 0;
   int stat;

   if (0 == elemName) elemName = "BIT_STRING";

   if (ASN1HEX == outputType) {
      attributes = "form=\"hex\"";
   }

   if (nbits == 0) {
      stat = xerEncIndent (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      
      stat = xerEncEmptyElement (pctxt, elemName, attributes);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      pctxt->state = XEREND;
   }
   else {
      stat = xerEncStartElement (pctxt, elemName, attributes);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      switch (outputType) {
      case ASN1BIN:
         stat = xerEncBinStrValue (pctxt, nbits, data);
         break;
      case ASN1HEX:
         stat = xerEncHexStrValue (pctxt, nbits, data);
         break;
      default:
         stat = RTERR_INVPARAM;
      }
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      stat = xerEncEndElement (pctxt, elemName);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   return (0);
}
