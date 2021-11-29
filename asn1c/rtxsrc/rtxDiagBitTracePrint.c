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
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxPrintStream.h"
#include "rtxsrc/rtxStream.h"

typedef struct {
   OSUINT8 lb, lbm;
   char fmtBitBuffer[40], fmtHexBuffer[10], fmtAscBuffer[10];
   int  fmtBitCharIdx, fmtHexCharIdx, fmtAscCharIdx;
} BinDumpBuffer;

static void fmtAndPrintBit (OSCTXT* pctxt, int value, BinDumpBuffer* pbuf)
{
   if (value > 0) {
      pbuf->fmtBitBuffer[pbuf->fmtBitCharIdx++] = '1';
      pbuf->lb |= pbuf->lbm;
   }
   else if (value < 0) {
      pbuf->fmtBitBuffer[pbuf->fmtBitCharIdx++] = 'x';
   }
   else
      pbuf->fmtBitBuffer[pbuf->fmtBitCharIdx++] = '0';

   pbuf->lbm >>= 1;

   if (pbuf->lbm == 0) {
      if (pbuf->fmtAscCharIdx < 4)
         pbuf->fmtBitBuffer[pbuf->fmtBitCharIdx++] = ' ';

      os_snprintf (&pbuf->fmtHexBuffer[pbuf->fmtHexCharIdx], 10, "%02x", pbuf->lb);

      os_snprintf (&pbuf->fmtAscBuffer[pbuf->fmtAscCharIdx], 10, "%c", 
               OS_ISPRINT(pbuf->lb) ? pbuf->lb : '.');

      pbuf->fmtHexCharIdx += 2; pbuf->fmtAscCharIdx++; pbuf->lb = 0;

      /* If buffer is full, print to stdout */

      if (pbuf->fmtAscCharIdx >= 4) {
         rtxPrintToStream
            (pctxt, "%-35.35s    %-8.8s    %-4.4s\n", 
             pbuf->fmtBitBuffer, pbuf->fmtHexBuffer, pbuf->fmtAscBuffer);

         OSCRTLMEMSET (pbuf, 0, sizeof(BinDumpBuffer));
      }

      pbuf->lbm = 0x80;
   }
}

static size_t getMaskAndIndex (size_t bitOffset, OSUINT8* pMask)
{
   int relBitOffset = 7 - (int)(bitOffset % 8);
   *pMask = (OSUINT8)(OSUINTCONST(1) << relBitOffset);
   return (bitOffset / 8);  /* byte index */
}

static void dumpBits (OSCTXT* pctxt, const OSOCTET* dataBuffer, 
                      size_t currBitOffset, size_t numbits, 
                      size_t nextBitOffset, BinDumpBuffer* pbuf)
{
   size_t  byteIndex, i, j, bitidx;
   OSUINT8 bitMask;
   OSBOOL  bitValue;

   /* Set start of dump buffer to hyphens */

   for (i = 0, j = 0; i < (size_t)pbuf->fmtBitCharIdx; i++) {
      if (j == 8) {
         pbuf->fmtBitBuffer[i] = ' ';
         j = 0;
      }
      else {
         pbuf->fmtBitBuffer[i] = '-';
         j++;
      }
   }
   for (i = 0; i < (size_t)pbuf->fmtHexCharIdx; i++) {
      pbuf->fmtHexBuffer[i] = '-';
   }
   for (i = 0; i < (size_t)pbuf->fmtAscCharIdx; i++) {
      pbuf->fmtAscBuffer[i] = '-';
   }

   /* Get byte index and mask from field relative bit offset */

   byteIndex = getMaskAndIndex (currBitOffset, &bitMask);

   /* Loop to dump all bits in the field */

   for (i = 0; i < numbits; i++) {
      bitValue = (OSBOOL)((dataBuffer[byteIndex] & bitMask) != 0);

      fmtAndPrintBit (pctxt, bitValue, pbuf);

      if ((bitMask >>= 1) == 0) {
         byteIndex++;
         bitMask = 0x80;
      }

      currBitOffset++;
   }

   /* Print unused bits between this and the next field */

   while (currBitOffset < nextBitOffset) {
      fmtAndPrintBit (pctxt, -1, pbuf);
      currBitOffset++;
   }

   /* If anything remains in the format buffer, print to stdout */

   if (pbuf->fmtBitCharIdx > 0) {

      /* Calculate bit index */

      if (pbuf->fmtBitCharIdx < 8) bitidx = pbuf->fmtBitCharIdx;
      else if (pbuf->fmtBitCharIdx < 17) bitidx = pbuf->fmtBitCharIdx - 1;
      else if (pbuf->fmtBitCharIdx < 26) bitidx = pbuf->fmtBitCharIdx - 2;
      else bitidx = pbuf->fmtBitCharIdx - 3;

      /* Fill to end of bit dump buffer with hyphens */

      for (i = pbuf->fmtBitCharIdx, j = bitidx % 8; i < 35; i++) {
         if (j == 8) {
            pbuf->fmtBitBuffer[i] = ' ';
            j = 0;
         }
         else {
            pbuf->fmtBitBuffer[i] = '-';
            j++;
         }
      }
      for (i = pbuf->fmtHexCharIdx; i < 8; i++) {
         pbuf->fmtHexBuffer[i] = '-';
      }
      for (i = pbuf->fmtAscCharIdx; i < 4; i++) {
         pbuf->fmtAscBuffer[i] = '-';
      }

      rtxPrintToStream 
         (pctxt, "%-35.35s    %-8.8s    %-4.4s\n", 
          pbuf->fmtBitBuffer, pbuf->fmtHexBuffer, pbuf->fmtAscBuffer);
   }

}

static void dumpField 
(OSCTXT* pctxt, const OSOCTET* dataBuffer, OSRTDiagBitField* pField, 
 const char* varname, size_t nextBitOffset, BinDumpBuffer* pbuf)
{
   char lbuf[400];

   /* Print field name */

   lbuf[0] = '\0';
   if (!OS_ISEMPTY(varname))
      OSCRTLSTRCAT (lbuf, varname);

   if (!OS_ISEMPTY(pField->elemName)) {
      if ('\0' != lbuf[0])
         OSCRTLSTRCAT (lbuf, ".");

      OSCRTLSTRCAT (lbuf, pField->elemName);
   }

   if (!OS_ISEMPTY(pField->nameSuffix)) {
      if ('\0' != lbuf[0])
         OSCRTLSTRCAT (lbuf, " ");

      OSCRTLSTRNCAT (lbuf, pField->nameSuffix, 32);
   }
   rtxPrintToStream (pctxt, "%s\n", lbuf);

   /* Print bit offsets and counts */

   RTDIAG4 (pctxt, "bit offset: %d\tbit count: %d\tnext bit offset: %d\n\n", 
            pField->bitOffset, pField->numbits, nextBitOffset);

   /* Print bits */

   dumpBits (pctxt, dataBuffer, pField->bitOffset, 
             pField->numbits, nextBitOffset, pbuf);

   rtxPrintToStream (pctxt, "\n");
}

EXTRTMETHOD void rtxDiagBitTracePrint 
(OSRTDiagBitFieldList* pBFList, const char* varname)
{
   size_t nextBitOffset;
   BinDumpBuffer binDumpBuffer;
   OSRTSListNode* pNode;
   OSCTXT* pctxt = pBFList->fieldList.pctxt;
   const OSOCTET* dataBuffer;

   OSCRTLMEMSET (&binDumpBuffer, 0, sizeof(binDumpBuffer));
   binDumpBuffer.lbm = 0x80; 

   /* If stream, set data buffer to point at capture buffer; otherwise 
      use context buffer */
   if (OSRTISSTREAM (pctxt)) {
      OSRTMEMBUF* pmembuf = rtxStreamGetCapture (pctxt);
      if (0 != pmembuf) {
         dataBuffer = rtxMemBufGetData (pmembuf, 0);
      }
      else {
         printf ("ERROR: capture buffer was not assigned to stream\n");
         return;
      }
   }
   else dataBuffer = pctxt->buffer.data;

   /* Loop through the field list and dump fields */

   pNode = pBFList->fieldList.head;
   while (pNode) {
      nextBitOffset = (pNode->next) ?
         ((OSRTDiagBitField*)pNode->next->data)->bitOffset : 0;

      dumpField (pctxt, dataBuffer, (OSRTDiagBitField*)pNode->data, varname, 
                 nextBitOffset, &binDumpBuffer);

      pNode = pNode->next;
   }
}

