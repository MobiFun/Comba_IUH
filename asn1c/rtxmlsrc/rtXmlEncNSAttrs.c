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

#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxErrCodes.h"
#include "rtxmlsrc/osrtxml.h"

typedef enum { encAttrs, setPfxLinks } Action;

static OSBOOL previouslyEncoded (OSRTDList* pEncNSList, OSXMLNamespace* pNS)
{
   OSRTDListNode* pNode;
   OSXMLNamespace* pEncNS;

   for (pNode = pEncNSList->head; 0 != pNode; pNode = pNode->next) {
      pEncNS = (OSXMLNamespace*) pNode->data;
      if (rtXmlNSEqual (pEncNS, pNS)) return TRUE;
   }

   return FALSE;
}

static int procNSAttrs (OSCTXT* pctxt, OSRTDList* pNSAttrs, Action action)
{
   int stat = 0;
   OSRTDList* pEncNSAttrs;
   OSRTDListNode* pNode;
   OSXMLNamespace* pNS;
   OSBOOL ctxtNSList = FALSE;
   size_t prefixLen, uriLen;
   OSXMLCtxtInfo* pXMLCtxtInfo = (OSXMLCtxtInfo*) pctxt->pXMLInfo;
   OSRTASSERT (0 != pXMLCtxtInfo);

   pEncNSAttrs = &pXMLCtxtInfo->encodedNSList;

   /* If namespace list not provided or no attributes in list, use list 
      in context */
   if (0 == pNSAttrs || 0 == pNSAttrs->count) {
      OSXMLCtxtInfo* pXMLCtxtInfo = (OSXMLCtxtInfo*) pctxt->pXMLInfo;
      if (0 != pXMLCtxtInfo) {
         pNSAttrs = &pXMLCtxtInfo->namespaceList;
         ctxtNSList = TRUE;
      }
      else return 0;
   }

   for (pNode = pNSAttrs->head; 0 != pNode; pNode = pNode->next) {
      pNS = (OSXMLNamespace*) pNode->data;
      if (0 == pNS->uri) 
         return LOG_RTERRNEW (pctxt, RTERR_BADVALUE);

      prefixLen = (!OS_ISEMPTY (pNS->prefix)) ?
         rtxUTF8LenBytes (pNS->prefix) : 0;

      /* If prefix is 'xsi', assume that this is the XML Schema Instance 
         (XSI) built-in namespace.  Do not encode that namespace here; it 
         will be done later in rtXmlEncXSIAttrs. */

      if (3 == prefixLen && pNS->prefix[0] == 'x' && 
          pNS->prefix[1] == 's' && pNS->prefix[2] == 'i')
         continue;

      if (action == encAttrs) {
         if (!previouslyEncoded (pEncNSAttrs, pNS)) {
            uriLen = OSUTF8LEN (pNS->uri);

            /* Verify attribute will fit in encode buffer */

            stat = rtxCheckBuffer (pctxt, prefixLen + uriLen + 9);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            /* Copy data to buffer */

            OSRTMEMCPY (pctxt, (const OSUTF8CHAR*)" xmlns", 6);
            if (prefixLen > 0) {
               OSRTPUTCHAR (pctxt, ':');
               OSRTMEMCPY (pctxt, pNS->prefix, prefixLen);
            }
            OSRTPUTCHAR (pctxt, '=');
            OSRTPUTCHAR (pctxt, '\"');
            OSRTMEMCPY (pctxt, pNS->uri, uriLen);
            OSRTSAFEPUTCHAR (pctxt, '\"');

            if (rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
               stat = rtXmlEncAttrC14N (pctxt);     
               if (0 != stat) return LOG_RTERR (pctxt, stat);
            }

            /* Add namespace record to encoded list */

            rtxDListAppend (pctxt, pEncNSAttrs, pNS);
         }
      }
      else if (action == setPfxLinks) {
         /* Add the namespace URI/prefix mapping to stack */
         stat = rtXmlNSAddPrefixLink (pctxt, pNS->prefix, pNS->uri, 
            pXMLCtxtInfo->nsURITable.data, pXMLCtxtInfo->nsURITable.nrows);
      }
   }

   return 0;
}

/* Encode namespace attributes */

EXTXMLMETHOD int rtXmlEncNSAttrs (OSCTXT* pctxt, OSRTDList* pNSAttrs)
{
   return procNSAttrs (pctxt, pNSAttrs, encAttrs);
}

EXTXMLMETHOD int rtXmlSetNSPrefixLinks (OSCTXT* pctxt, OSRTDList* pNSAttrs)
{
   return (procNSAttrs (pctxt, pNSAttrs, setPfxLinks));
}

