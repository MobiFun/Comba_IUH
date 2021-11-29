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

#include "rtxmlsrc/osrtxml.hh"

EXTXMLMETHOD int rtXmlEncStartElement (OSCTXT* pctxt, 
                          const OSUTF8CHAR* elemName, 
                          OSXMLNamespace* pNS, 
                          OSRTDList* pNSAttrs, 
                          OSBOOL terminate)
{
   int stat = 0;

   if (0 != elemName && 0 != *elemName) {
      size_t elemLen = rtxUTF8LenBytes (elemName);
      size_t nsPrefixLen;
      size_t specChars;

      /* Push null entry onto namespace stack */
      stat = rtXmlNSPush (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* Set namespace URI/prefix links */
      stat = rtXmlSetNSPrefixLinks (pctxt, pNSAttrs);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* Set namespace prefix in passed namespace structure */
      if (0 != pNS) {
         if (0 == pNS->prefix) {
            pNS->prefix = rtXmlNSGetPrefix (pctxt, pNS->uri);
         }
         nsPrefixLen = OSUTF8LEN (pNS->prefix);
      }
      else nsPrefixLen = 0;

      specChars = (0 != nsPrefixLen) ? 3 : 2;

      /* Terminate previous element if still open */
      stat = rtXmlEncTermStartElement (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      stat = rtXmlEncIndent (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   
      pctxt->level++;
      pctxt->state = OSXMLSTART;

      /* Verify element will fit in encode buffer */

      stat = rtxCheckBuffer (pctxt, elemLen + nsPrefixLen + specChars);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* Copy data to buffer */

      OSRTPUTCHAR (pctxt, '<');

      if (0 != nsPrefixLen) {
         OSRTMEMCPY (pctxt, pNS->prefix, nsPrefixLen);
         OSRTPUTCHAR (pctxt, ':');
      }
      OSRTMEMCPY (pctxt, elemName, elemLen);

      if (terminate) {
         OSRTPUTCHAR (pctxt, '>');
         pctxt->flags &= ~OSTERMSTART;
      }
      else /* set flag in context indicating terminator needed */
         pctxt->flags |= OSTERMSTART;

#ifndef _COMPACT
      /* Add name to element name stack in context */
      rtxDListAppend (pctxt, &pctxt->elemNameStack, (void*)elemName);
#endif
      if (!terminate && rtxCtxtTestFlag (pctxt, OSXMLC14N))
      stat = rtXmlEncStartAttrC14N (pctxt);
   }
   else if (terminate) {
      stat = rtXmlEncTermStartElement (pctxt);
   }   
   
   if (stat < 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

/* This function will terminate a currently open start element */

EXTXMLMETHOD int rtXmlEncTermStartElement (OSCTXT* pctxt)
{
   if (pctxt->state == OSXMLSTART && pctxt->flags & OSTERMSTART) {
      if (rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
         int stat = rtXmlEncEndAttrC14N (pctxt);
         if (stat < 0) return LOG_RTERRNEW (pctxt, stat);
      }   

      /* If empty element, terminate with '/>', otherwise '>' */
      if (pctxt->flags & OSEMPTYELEM)
         OSRTSAFEPUTCHAR (pctxt, '/');

      OSRTSAFEPUTCHAR (pctxt, '>');

      /* Indicate element is terminated */
      pctxt->flags &= ~(OSTERMSTART | OSEMPTYELEM);
   }
   return 0;
}

