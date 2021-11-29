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

#include "rtxsrc/osMacros.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxStream.h"

static size_t getCtxtBitOffset (OSCTXT* pctxt)
{
   size_t byteIndex = (OSRTISSTREAM (pctxt)) ?
      pctxt->pStream->bytesProcessed : 0;

   byteIndex += pctxt->buffer.byteIndex;

   return ((byteIndex * 8) + (8 - pctxt->buffer.bitOffset));
}

EXTRTMETHOD OSBOOL rtxDiagBitTraceEnabled (OSCTXT* pctxt)
{
   return (OSBOOL)(0 != pctxt && pctxt->flags & OSTRACE);
}

EXTRTMETHOD OSBOOL rtxDiagSetBitTraceEnabled (OSCTXT* pctxt, OSBOOL value)
{
   OSBOOL prevState = rtxDiagBitTraceEnabled (pctxt);
   if (value)
      pctxt->flags |= OSTRACE;
   else {
      /* Need to do it this way because some UNIX compilers will set    */
      /* bits in full 32-bit word..                                     */
      OSRTFLAGS lflags = (pctxt->flags & ~OSTRACE);
      pctxt->flags = lflags;
   }
   return prevState;
}

EXTRTMETHOD void rtxDiagBitFieldListInit 
(OSCTXT* pctxt, OSRTDiagBitFieldList* pBFList)
{
   OSCRTLMEMSET (pBFList, 0, sizeof(OSRTDiagBitFieldList));
   rtxSListInitEx (pctxt, &pBFList->fieldList);

   /* If context is using an input stream, set up capture buffer */
   if (rtxStreamIsReadable (pctxt)) {
      pBFList->pCaptureBuf = rtxMemAllocType (pctxt, OSRTMEMBUF);
      if (0 != pBFList->pCaptureBuf) {
         rtxMemBufInit (pctxt, pBFList->pCaptureBuf, 0);
         rtxStreamSetCapture (pctxt, pBFList->pCaptureBuf);
      }
   }
}

EXTRTMETHOD void rtxDiagInsBitFieldLen (OSRTDiagBitFieldList* pBFList)
{
   OSRTDiagBitField* pCurrField;
   OSRTDiagBitField* pNewField;
   OSRTSListNode* pNode;

   if (pBFList->disabledCount > 0) return;

   if ((pNode = pBFList->fieldList.tail) != 0) {
      OSCTXT* pctxt = pBFList->fieldList.pctxt;
      pCurrField = (OSRTDiagBitField*) pNode->data;

      /* Create a new field and set name to that of current field    */

      pNewField = rtxMemAllocType (pctxt, OSRTDiagBitField);
      if (0 == pNewField) return;

      pNewField->elemName = pCurrField->elemName;
      pNewField->nameSuffix = "length";

      pCurrField->numbits = 
         getCtxtBitOffset(pctxt) - pCurrField->bitOffset;

      /* Append the new field to the field list and initialize the   */
      /* bit offset and count..                                      */

      pNewField->bitOffset = getCtxtBitOffset (pctxt);
      pNewField->numbits   = 0;

      rtxSListAppend (&pBFList->fieldList, pNewField);
   }
}

EXTRTMETHOD OSRTDiagBitField* rtxDiagNewBitField 
(OSRTDiagBitFieldList* pBFList, const char* nameSuffix)
{
   OSRTDiagBitField* pField = 0;

   if (pBFList->disabledCount == 0) {
      OSCTXT* pctxt = pBFList->fieldList.pctxt;

      pField = rtxMemAllocType (pctxt, OSRTDiagBitField);
      if (pField == NULL) return NULL;

      rtxDListToUTF8Str 
         (pctxt, &pctxt->elemNameStack, (OSUTF8CHAR**)&pField->elemName, '.');

      pField->nameSuffix = nameSuffix;
      pField->bitOffset = getCtxtBitOffset (pctxt);
      pField->numbits = 0;

      rtxSListAppend (&pBFList->fieldList, pField);
   }

   return pField;
}

EXTRTMETHOD void rtxDiagSetBitFldOffset (OSRTDiagBitFieldList* pBFList)
{
   OSRTSListNode* pNode = pBFList->fieldList.tail;

   if (pBFList->disabledCount == 0 && 0 != pNode) {
      OSCTXT* pctxt = pBFList->fieldList.pctxt;
      OSRTDiagBitField* pfld = (OSRTDiagBitField*) pNode->data;
      if (0 != pfld && 0 == pfld->numbits) {
         pfld->bitOffset = getCtxtBitOffset (pctxt);
      }
   }
}

EXTRTMETHOD void rtxDiagSetBitFldCount (OSRTDiagBitFieldList* pBFList)
{
   OSRTSListNode* pNode = pBFList->fieldList.tail;

   if (pBFList->disabledCount == 0 && 0 != pNode) {
      OSCTXT* pctxt = pBFList->fieldList.pctxt;
      OSRTDiagBitField* pfld = (OSRTDiagBitField*) pNode->data;
      if (0 != pfld) {
         pfld->numbits = getCtxtBitOffset(pctxt) - pfld->bitOffset;
      }
   }
}

EXTRTMETHOD void rtxDiagSetBitFldNameSuffix 
(OSRTDiagBitFieldList* pBFList, const char* nameSuffix)
{
   OSRTSListNode* pNode = pBFList->fieldList.tail;

   if (pBFList->disabledCount == 0 && 0 != pNode) {
      OSRTDiagBitField* pfld = (OSRTDiagBitField*) pNode->data;
      if (0 != pfld) {
         pfld->nameSuffix = nameSuffix;
      }
   }
}

EXTRTMETHOD OSBOOL rtxDiagSetBitFldDisabled 
(OSRTDiagBitFieldList* pBFList, OSBOOL value)
{
   if (value)
      pBFList->disabledCount++;
   else if (pBFList->disabledCount > 0)
      pBFList->disabledCount--;      

   return (OSBOOL)(pBFList->disabledCount > 0);
}

EXTRTMETHOD void rtxDiagBitFldAppendNamePart
(OSRTDiagBitFieldList* pBFList, const char* namePart)
{
   OSRTSListNode* pNode = pBFList->fieldList.tail;

   if (pBFList->disabledCount == 0 && 0 != pNode) {
      OSCTXT* pctxt = pBFList->fieldList.pctxt;
      OSRTDiagBitField* pfld = (OSRTDiagBitField*) pNode->data;
      if (0 != pfld) {
         if (!OS_ISEMPTY (pfld->elemName)) {
            char* buf = (char*) rtxMemRealloc 
               (pctxt, (void*)pfld->elemName, 
                OSCRTLSTRLEN(pfld->elemName)+OSCRTLSTRLEN(namePart)+2);
            if (0 != buf) {
               OSCRTLSTRCAT (buf, ".");
               OSCRTLSTRCAT (buf, namePart);
               pfld->elemName = buf;
            }
         }
         else {
            rtxDListToUTF8Str (pctxt, 
               &pctxt->elemNameStack, (OSUTF8CHAR**)&pfld->elemName, '.');
         }
      }
   }
}
