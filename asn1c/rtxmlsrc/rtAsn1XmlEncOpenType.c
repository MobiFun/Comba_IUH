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

#include "rtsrc/asn1type.h"
#include "rtxmlsrc/asn1xml.h"

static int isBinaryData (const OSOCTET *data, OSUINT32 nocts);

EXTXMLMETHOD int rtAsn1XmlEncOpenType 
(OSCTXT *pctxt, const OSOCTET* data, OSUINT32 nocts, 
 const OSUTF8CHAR* elemName, const OSUTF8CHAR* nsPrefix) 
{
   OSUTF8CHAR* qname = 0;
   int stat;

   if (0 != isBinaryData (data, nocts)) {
      const OSUTF8CHAR *ename = (elemName == 0 || strcmp ("", elemName) == 0 ) ? 
         OSUTF8("binext") : elemName;

      qname = rtXmlNewQName (pctxt, ename, nsPrefix);
      
      if (0 != qname) {
         stat = rtXmlEncStartElement (pctxt, qname, 0, 0, TRUE);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
      else return RTERR_NOMEM;

      if (0 != data && nocts > 0) {
         stat = rtXmlEncHexStrValue (pctxt, nocts, data);
         pctxt->state = OSXMLDATA;

         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      if (0 != qname) {
         stat = rtXmlEncEndElement (pctxt, qname, 0);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         rtxMemFreePtr (pctxt, qname);
      }
   }

   else {
      if (0 != elemName) {
         qname = rtXmlNewQName (pctxt, elemName, nsPrefix);

         if (0 != qname) {
            stat = rtXmlEncStartElement (pctxt, qname, 0, 0, TRUE);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
         else return RTERR_NOMEM;
      }

      if (0 != data && nocts > 0) {
         OSRTSAFEMEMCPY (pctxt, data, nocts);
         pctxt->state = OSXMLDATA;
      }

      if (0 != qname) {
         stat = rtXmlEncEndElement (pctxt, qname, 0);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         rtxMemFreePtr (pctxt, qname);
      }
   }

   return 0;
}

int
isBinaryData (const OSOCTET *data, OSUINT32 nocts)
{
   unsigned int i;

   if (data[0] != 0) return -1;

   for (i = 0; i < nocts; i ++) {
      if (data[i] < 32 || data[i] > 127) {
         return -1;
      }
   }

   return 0;
}

