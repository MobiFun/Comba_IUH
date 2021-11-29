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

#ifndef _COMPACT
static int checkElement (OSCTXT* pctxt, const OSUTF8CHAR* elemName)
{
   /* Verify element name on the stack is the element being terminated */
   const OSUTF8CHAR* stkElemName;
   OSRTASSERT (pctxt->elemNameStack.count > 0);
   stkElemName = OSUTF8 (pctxt->elemNameStack.tail->data);
   if (!rtxUTF8StrEqual (elemName, stkElemName)) {
      rtxErrAddStrParm (pctxt, (const char*)stkElemName);
      rtxErrAddStrParm (pctxt, (const char*)elemName);
      return LOG_RTERR (pctxt, RTERR_IDNOTFOU);
   }
   return 0;
}
#endif

EXTXMLMETHOD int rtXmlEncEndElement (OSCTXT* pctxt, 
                        const OSUTF8CHAR* elemName, 
                        OSXMLNamespace* pNS)
{
   int stat = 0;

   /* If current state is OSXMLSTART, can end element by replacing '>'  */
   /* at end with '/>'                                                  */

   if (0 != elemName && 0 != *elemName) { 
#ifndef _COMPACT
      stat = checkElement (pctxt, elemName);
      if (0 != stat) LOG_RTERR (pctxt, stat);
#endif

      if (pctxt->state == OSXMLSTART && !rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
         /* start tag may be closed as empty tag */
         if (pctxt->buffer.byteIndex > 0) {
            if ((pctxt->flags & OSTERMSTART) == 0)
            pctxt->buffer.byteIndex--;

            if (rtxCheckBuffer (pctxt, 3) == 0) {
                  OSRTPUTCHAR (pctxt, '/');
                  OSRTPUTCHAR (pctxt, '>');
                  OSRTZTERM (pctxt);
               }
               else stat = RTERR_BUFOVFLW;
            }
         else stat = RTERR_XMLSTATE;

         if (stat < 0) return LOG_RTERRNEW (pctxt, stat);
         else {
            pctxt->flags &= ~(OSTERMSTART | OSEMPTYELEM);
            pctxt->state = OSXMLEND;
            pctxt->level--;
         }
      }
      else {
         size_t nsPrefixLen = (0 != pNS && 0 != pNS->prefix) ? 
            rtxUTF8LenBytes(pNS->prefix) : 0;
         size_t specChars = (0 != nsPrefixLen) ? 5 : 4;
         size_t elemLen = rtxUTF8LenBytes (elemName);

         if (pctxt->state == OSXMLSTART && pctxt->flags & OSTERMSTART) {
            stat = rtXmlEncTermStartElement (pctxt);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }   

         pctxt->level--;

         /* If last element was an end element, indent */
         if (OSXMLEND == pctxt->state) {
            stat = rtXmlEncIndent (pctxt);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
         pctxt->state = OSXMLEND;

         /* Verify element will fit in encode buffer */

         stat = rtxCheckBuffer (pctxt, elemLen + nsPrefixLen + specChars);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         /* Copy data to buffer */

         OSRTPUTCHAR (pctxt, '<');
         OSRTPUTCHAR (pctxt, '/');

         if (0 != nsPrefixLen) {
            OSRTMEMCPY (pctxt, pNS->prefix, nsPrefixLen);
            OSRTPUTCHAR (pctxt, ':');
         }
         OSRTMEMCPY (pctxt, elemName, elemLen);

         OSRTPUTCHAR (pctxt, '>');
         OSRTZTERM (pctxt);
      }

      /* Pop entry from namespace stack */
      stat = rtXmlNSPop (pctxt);
      if (stat < 0) return LOG_RTERR (pctxt, stat);
#ifndef _COMPACT
      rtxDListFreeNode 
         (pctxt, &pctxt->elemNameStack, pctxt->elemNameStack.tail);
#endif   
   }
   return 0;
}

