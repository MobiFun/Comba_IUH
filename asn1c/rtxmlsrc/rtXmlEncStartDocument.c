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

EXTXMLMETHOD int rtXmlEncStartDocument (OSCTXT* pctxt)
{
   if (pctxt->state == OSXMLINIT) {
      pctxt->level = 0;
      /* If fragment, do not add header */
      if (!rtxCtxtTestFlag (pctxt, OSXMLFRAG)) {
         int stat;
         OSXMLCtxtInfo* pXmlInfo = (OSXMLCtxtInfo*)pctxt->pXMLInfo;
         if (pXmlInfo == 0) return LOG_RTERR (pctxt, RTERR_NOTINIT);

         /* clear the encoded namespace attributes list */
         rtxDListFreeNodes (pctxt, &pXmlInfo->encodedNSList);
         
         /* C14N specifies no header, no BOM */
         if (!rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
            /* encode Unicode byte order mark */
            stat = rtXmlEncBOM (pctxt);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            stat = rtxCopyAsciiText 
               (pctxt, "<?xml version=\"1.0\" encoding=\"");
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            if (pXmlInfo->encodingStr != 0) {
               stat = rtxCopyAsciiText 
                  (pctxt, (const char*)pXmlInfo->encodingStr);
            }
            else {
               stat = rtxCopyAsciiText (pctxt, "UTF-8");
            }
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            stat = rtxCopyAsciiText (pctxt, "\"?>");
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            pctxt->state = OSXMLHEADER;
         }
      }
   }

   return 0;
}

EXTXMLMETHOD int rtXmlEncBOM (OSCTXT* pctxt)
{
   int stat;
   OSOCTET* bomBytes = 0;
   size_t bomLen = 0;  
   OSXMLCtxtInfo* pXmlInfo = (OSXMLCtxtInfo*)pctxt->pXMLInfo;
   if (pXmlInfo == 0) return LOG_RTERR (pctxt, RTERR_NOTINIT); 

   switch (pXmlInfo->byteOrderMark) {
   case OSXMLBOM_NO_BOM:
      bomLen = 0;
      break;
   case OSXMLBOM_UTF8:
      bomBytes = (OSOCTET*)"\xEF\xBB\xBF";
      bomLen = 3;
      break;
   case OSXMLBOM_UTF16_BE:
      bomBytes = (OSOCTET*)"\xFE\xFF";
      bomLen = 2;
      break;
   case OSXMLBOM_UTF16_LE:
      bomBytes = (OSOCTET*)"\xFF\xFE";
      bomLen = 2;
      break;   
   case OSXMLBOM_UTF32_BE:
      bomBytes = (OSOCTET*)"\0\0\xFE\xFF";
      bomLen = 4;
      break;
   case OSXMLBOM_UTF32_LE:
      bomBytes = (OSOCTET*)"\xFF\xFE\0\0";
      bomLen = 4;
      break;        
   }
   if (bomLen > 0) {
      stat = rtxCheckBuffer (pctxt, bomLen);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
      OSRTMEMCPY (pctxt, bomBytes, bomLen);
   }
   return 0;
}

