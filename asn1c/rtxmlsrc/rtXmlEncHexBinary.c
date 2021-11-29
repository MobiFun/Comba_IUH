/*
 * Copyright (c) 2003-2009 Objective Systems, Inc.
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

EXTXMLMETHOD int rtXmlEncHexStrValue (OSCTXT* pctxt, 
                         OSUINT32 nocts, 
                         const OSOCTET* data)
{
   OSUINT32 i, lbufx = 0;
   int  stat, ub;
   char lbuf[80];

   if (pctxt->state != OSXMLATTR)
      pctxt->state = OSXMLDATA;

   /* Verify indentation whitespace will fit in encode buffer */

   stat = rtxCheckBuffer (pctxt, nocts*2);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   for (i = 0; i < nocts; i++) {
      if (lbufx >= sizeof(lbuf)) {
         /* flush buffer */
         OSRTMEMCPY (pctxt, lbuf, sizeof(lbuf));
         lbufx = 0;
      }

      ub = (data[i] >> 4) & 0x0f; 
      if ((pctxt->flags & OSUPCASE) != 0)
         NIBBLETOUCHEXCHAR (ub, lbuf[lbufx++]);
      else
         NIBBLETOHEXCHAR (ub, lbuf[lbufx++]);

      ub = (data[i] & 0x0f);
      if ((pctxt->flags & OSUPCASE) != 0)
         NIBBLETOUCHEXCHAR (ub, lbuf[lbufx++]);
      else
         NIBBLETOHEXCHAR (ub, lbuf[lbufx++]);
   }

   /* flush remaining characters from local buffer */
   
   if (lbufx > 0) {
      OSRTMEMCPY (pctxt, lbuf, lbufx);
   }

   return 0;
}

EXTXMLMETHOD int rtXmlEncHexBinary (OSCTXT* pctxt, OSUINT32 nocts, 
                       const OSOCTET* value, 
                       const OSUTF8CHAR* elemName, 
                       OSXMLNamespace* pNS)
{
   int stat = 0;

   if (nocts == 0) {
      if (0 != elemName) {
         stat = rtXmlEncEmptyElement (pctxt, elemName, pNS, 0, TRUE);
         pctxt->state = OSXMLEND;
      }
   }
   else {
      stat = rtXmlEncStartElement (pctxt, elemName, pNS, 0, TRUE);

      if (0 == stat)
         stat = rtXmlEncHexStrValue (pctxt, nocts, value);

      if (0 != elemName && 0 == stat) {
         stat = rtXmlEncEndElement (pctxt, elemName, pNS);
      }
   }

   return (stat != 0) ? LOG_RTERR (pctxt, stat) : 0;
}

