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

#include "rtxmlsrc/osrtxml.h"

EXTXMLMETHOD int rtXmlEncReal10 
(OSCTXT *pctxt, const OSUTF8CHAR *pvalue, const OSUTF8CHAR* elemName, 
 OSXMLNamespace* pNS) 
{
   int  stat;
   const char* p;
   const char* mantBeg = 0;
   const char* mantEnd = 0;
   int digits = 0;
   int trailZeros = 0;
   int mantExpVal = 0;
   int expVal = 0;
   char mantMinus = 0;
   char expMinus = 0;
   char flFrac = 0;
   char c;

   stat = rtXmlEncStartElement (pctxt, elemName, pNS, 0, TRUE);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (pctxt->state != OSXMLATTR)
      pctxt->state = OSXMLDATA;

   /* skip ws and leading zeros and plus */
   for (p = (const char*)pvalue; (c = *p) != 0; p++) {
      if (c == '-')
         mantMinus = 1;
      else if (c != ' ' && c != '0' && c != '+') 
         break;
   }

   mantBeg = mantEnd = p;

   /* count mantissa digits */
   for (; (c = *p) != 0; p++) {
      if (c == '0')
         trailZeros++;
      else if (c > '0' && c <= '9') {
         if (digits == 0 && flFrac) {
            mantExpVal = -trailZeros;
            digits = 1;
            mantBeg = p;
         }
         else
            digits += trailZeros + 1;

         trailZeros = 0;
         mantEnd = p + 1;
      }
      else if (c == '.') {
         mantExpVal = digits + trailZeros;
         flFrac = 1;
      }
      else if (c == 'e' || c == 'E') {
         p++;
         break;
      }
      else if (c != ' ')
         break;
   }

   if (digits == 0) {
      OSRTPUTCHAR (pctxt, '0');
   }
   else {
      if (!flFrac)
         mantExpVal = digits + trailZeros;

      /* skip ws and leading zeros and plus */
      for (; (c = *p) != 0; p++) {
         if (c == '-')
            expMinus = 1;
         else if (c != ' ' && c != '0' && c != '+') 
            break;
      }

      /* get exponent */
      for (; (c = *p) != 0; p++) {
         if (c >= '0' && c <= '9')
            expVal = expVal * 10 + (c - '0');
         else if (c != ' ')
            break;
      }

      if (expMinus)
         expVal = -expVal;

      expVal += mantExpVal;

      if (mantMinus) OSRTPUTCHAR (pctxt, '-');
      if (expVal <= 0) {
         OSRTPUTCHAR (pctxt, '0');

         if (digits > 0) 
            OSRTPUTCHAR (pctxt, '.');
      }

      while (expVal < 0) {
         expVal++;
         OSRTPUTCHAR (pctxt, '0');
      }

      while (mantBeg != mantEnd) {
         c = *mantBeg++;
         if (c >= '0' && c <= '9') {
            OSRTPUTCHAR (pctxt, c);
            if (--expVal == 0 && mantBeg != mantEnd)
               OSRTPUTCHAR (pctxt, '.');
         }
      }

      while (expVal > 0) {
         expVal--;
         OSRTPUTCHAR (pctxt, '0');
      }
   }
   
   if (0 != elemName) {
      stat = rtXmlEncEndElement (pctxt, elemName, pNS);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   
   return (0);
}

