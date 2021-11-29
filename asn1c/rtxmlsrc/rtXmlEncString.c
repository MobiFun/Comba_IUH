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

#include "rtxsrc/rtxErrCodes.h"
#include "rtxmlsrc/osrtxml.hh"

/* Encode CDATA value.  Check for "]]>" in string wrapped in CDATA, which 
   is illegal. */
EXTXMLMETHOD int rtXmlEncCDATAStringValue
   (OSCTXT* pctxt, const OSUTF8CHAR* value, size_t valueLen)
{
   size_t i;
   enum { 
      OSXMLCDATA_CHARS,
      OSXMLCDATA_ONE_BRACKET,
      OSXMLCDATA_TWO_BRACKETS 
   } state = OSXMLCDATA_CHARS;
   
   for (i = 0; i < valueLen; i++) {
      /* Caller must ensure buffer is big enough. */
      OSRTPUTCHAR (pctxt, value[i]);
      switch (state) {
      case OSXMLCDATA_CHARS:
         if (value[i] == ']')
            state = OSXMLCDATA_ONE_BRACKET;
         break;
      case OSXMLCDATA_ONE_BRACKET:
         if (value[i] == ']')
            state = OSXMLCDATA_TWO_BRACKETS;
         else
            state = OSXMLCDATA_CHARS;
         break;
      case OSXMLCDATA_TWO_BRACKETS:
         if (value[i] == '>')
            return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);
         else if (value[i] != ']')
            state = OSXMLCDATA_CHARS;
         break;
      }
   }
   return 0;
}

EXTXMLMETHOD int rtXmlEncStringValue2 
   (OSCTXT* pctxt, const OSUTF8CHAR* value, size_t valueLen)
{
   if (0 != value && 0 != *value) {
      size_t i;      
      if (rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
         /* C14N text node */
         if (pctxt->state == OSXMLDATA) {
            for (i = 0; i < valueLen; i++) {
               switch (value[i]) {
               case '&':
                  OSRTSAFEMEMCPY (pctxt, "&amp;", 5);
                  break;
               case '<': 
                  OSRTSAFEMEMCPY (pctxt, "&lt;", 4);
                  break;
               case '>': 
                  OSRTSAFEMEMCPY (pctxt, "&gt;", 4);
                  break;
               case 0xD:
                  OSRTSAFEMEMCPY (pctxt, "&#xD;", 5);
                  break;
               default:
                  OSRTSAFEPUTCHAR (pctxt, value[i]);
               }
            }
         }
         else { /* C14N attribute node */
            for (i = 0; i < valueLen; i++) {
               switch (value[i]) {
               case '&':
                  OSRTSAFEMEMCPY (pctxt, "&amp;", 5);
                  break;
               case '"':
                  OSRTSAFEMEMCPY (pctxt, "&quot;", 6);
                  break;
               case 0x9:
                  OSRTSAFEMEMCPY (pctxt, "&#x9;", 5);
                  break;
               case 0xA:
                  OSRTSAFEMEMCPY (pctxt, "&#xA;", 5);
                  break;
               case 0xD:
                  OSRTSAFEMEMCPY (pctxt, "&#xD;", 5);
                  break;
               case '<': 
                  OSRTSAFEMEMCPY (pctxt, "&lt;", 4);
                  break;
               default:
                  OSRTSAFEPUTCHAR (pctxt, value[i]);
               }
            }
         }
      }
      else { /* not C14N */
         for (i = 0; i < valueLen; i++) {
            switch (value[i]) {
            case '<': 
               OSRTSAFEMEMCPY (pctxt, "&lt;", 4);
               break;
            case '>': 
               OSRTSAFEMEMCPY (pctxt, "&gt;", 4);
               break;
            case '&': 
               OSRTSAFEMEMCPY (pctxt, "&amp;", 5);
               break;
            case '\'': 
               OSRTSAFEMEMCPY (pctxt, "&apos;", 6);
               break;
            case '"': 
               OSRTSAFEMEMCPY (pctxt, "&quot;", 6);
               break;
            default:
               OSRTSAFEPUTCHAR (pctxt, value[i]);
            }
         }
      }
   }   
   OSRT_CHECK_EVAL_DATE1(pctxt);

   return 0;
}

EXTXMLMETHOD int rtXmlEncStringValue (OSCTXT* pctxt, const OSUTF8CHAR* value)
{
   if (0 != value && 0 != *value) {
      return rtXmlEncStringValue2 (pctxt, value, rtxUTF8LenBytes (value));
   }
   return 0;
}

EXTXMLMETHOD int rtXmlEncString (OSCTXT* pctxt, 
                    OSXMLSTRING* pxmlstr, 
                    const OSUTF8CHAR* elemName, 
                    OSXMLNamespace* pNS)
{
   int stat = 0;
   if (0 != elemName) {
      stat = rtXmlEncStartElement (pctxt, elemName, pNS, 0, TRUE);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   else if (pctxt->state != OSXMLATTR) {
      stat = rtXmlEncTermStartElement (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* Encode string content */

   if (0 != pxmlstr) {
      /* Do not change state if encoding attr */
      if (!(pctxt->state == OSXMLATTR && 0 == elemName))
         pctxt->state = OSXMLDATA;
      /* C14N specifies CDATA sections are to be replaced with their
         character content.  Disregard CDATA in C14N mode. */
      if (pxmlstr->cdata && !rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
         /* Encode CDATA section */
         size_t len = rtxUTF8LenBytes (pxmlstr->value);

         /* Verify string will fit in encode buffer */
         stat = rtxCheckBuffer (pctxt, len + 12);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         /* Copy data to buffer or stream */
         OSRTMEMCPY (pctxt, "<![CDATA[", 9);
         stat = rtXmlEncCDATAStringValue (pctxt, pxmlstr->value, len);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         OSRTMEMCPY (pctxt, "]]>", 3);
      }
      else {
         stat = rtXmlEncStringValue (pctxt, pxmlstr->value);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }

   if (0 != elemName) {
      stat = rtXmlEncEndElement (pctxt, elemName, pNS);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return 0;
}

EXTXMLMETHOD int rtXmlEncUTF8Str (OSCTXT* pctxt, 
                     const OSUTF8CHAR* pvalue,
                     const OSUTF8CHAR* elemName, 
                     OSXMLNamespace* pNS)
{
   OSXMLSTRING xmlstr;
   xmlstr.cdata = FALSE;
   xmlstr.value = pvalue;
   return rtXmlEncString (pctxt, &xmlstr, elemName, pNS);
}

