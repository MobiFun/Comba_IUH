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

#include "rtpersrc/pu_common.hh"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxPrintStream.h"

/***********************************************************************
 *
 *  Routine name: pu_bindump
 *
 *  Description:  This routine dumps an encoded PER buffer to the
 *                given file.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct  PER context structure
 *
 *  Outputs:
 *
 *  None
 *
 *
 **********************************************************************/

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

      sprintf (&pbuf->fmtHexBuffer[pbuf->fmtHexCharIdx], "%02x", pbuf->lb);

      sprintf (&pbuf->fmtAscBuffer[pbuf->fmtAscCharIdx], "%c", 
               OS_ISPRINT(pbuf->lb) ? pbuf->lb : '.');

      pbuf->fmtHexCharIdx += 2; pbuf->fmtAscCharIdx++; pbuf->lb = 0;

      /* If buffers full, print to stdout */

      if (pbuf->fmtAscCharIdx >= 4) {
         rtxPrintToStream
            (pctxt, "%-35.35s    %-8.8s    %-4.4s\n", 
             pbuf->fmtBitBuffer, pbuf->fmtHexBuffer, pbuf->fmtAscBuffer);

         memset (pbuf, 0, sizeof(BinDumpBuffer));
      }

      pbuf->lbm = 0x80;
   }
}

static void pu_dumpBits (OSCTXT* pctxt, size_t currBitOffset, size_t numbits, 
                         size_t nextBitOffset, BinDumpBuffer* pbuf)
{
   size_t byteIndex, i, j, bitidx;
   unsigned char bitMask;
   OSBOOL bitValue;

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

   byteIndex = pu_getMaskAndIndex (currBitOffset, &bitMask);

   /* Loop to dump all bits in the field */

   for (i = 0; i < numbits; i++) {
      bitValue = ((pctxt->buffer.data[byteIndex] & bitMask) != 0);

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

EXTPERMETHOD void pu_dumpField 
(OSCTXT* pctxt, PERField* pField, const char* varname,
 size_t nextBitOffset, BinDumpBuffer* pbuf)
{
   char lbuf[400];

   /* Print field name */

   lbuf[0] = '\0';
   if (varname) strcat (lbuf, varname);
   if (pField->name) strcat (lbuf, pField->name);
   rtxPrintToStream (pctxt, "%s\n", lbuf);

   RTDIAGSTRM5 (pctxt,"bit offset: %d\tbit count: %d\tnext bit offset: %d\n", 
                pField->bitOffset, pField->numbits, nextBitOffset);

   /* Print bits */

   pu_dumpBits (pctxt, pField->bitOffset, pField->numbits,
                nextBitOffset, pbuf);

   rtxPrintToStream (pctxt, "\n");
}

static void dumpFields 
(OSCTXT* pctxt, const char* varname, OSRTSList* pFieldList)
{
   size_t nextBitOffset;
   BinDumpBuffer binDumpBuffer;
   OSRTSListNode* pNode;
   PERField* pField;

   memset (&binDumpBuffer, 0, sizeof(binDumpBuffer));
   binDumpBuffer.lbm = 0x80; 

   /* Loop through the field list and dump fields */

   pNode = pFieldList->head;
   while (pNode) {
      nextBitOffset = (pNode->next) ?
         ((PERField*)pNode->next->data)->bitOffset : 0;

      pField = (PERField*)pNode->data;
      pu_dumpField (pctxt, pField, varname, nextBitOffset, &binDumpBuffer);

      if (0 != pField->openTypeFields) {
         OSOCTET* savedData = pctxt->buffer.data;
         size_t byteIndex = pField->bitOffset/8;
         rtxPrintToStream (pctxt, "*** Open Type Data ***\n");
         pctxt->buffer.data = &pctxt->buffer.data[byteIndex];

         /* Make recursive call */
         dumpFields (pctxt, varname, pField->openTypeFields);

         rtxPrintToStream (pctxt, "***\n");
         pctxt->buffer.data = savedData;
      }

      pNode = pNode->next;
   }
}

EXTPERMETHOD void pu_bindump (OSCTXT* pctxt, const char* varname)
{
   dumpFields (pctxt, varname, &ACINFO(pctxt)->fieldList);
}

/***********************************************************************
 *
 *  Routine name: pu_hexdump
 *
 *  Description:  This routine dumps an encoded PER buffer in 
 *                standard hex format to the given file.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct  PER context structure
 *
 *  Outputs:
 *
 *  None
 *
 *
 **********************************************************************/

EXTPERMETHOD void pu_hexdump (OSCTXT* pctxt)
{
   register size_t i;
   char      hexstr[49], ascstr[17], buf[3];
   size_t    numocts;
   OSOCTET b, dumpstr = 1;

   memset (hexstr, ' ', 48); hexstr[48] = '\0';
   memset (ascstr, ' ', 16); ascstr[16] = '\0';

   rtxPrintToStream (pctxt, "\n");
   rtxPrintToStream 
      (pctxt, "HEX                                              ASCII\n");

   numocts = (pctxt->buffer.bitOffset == 8) ?
      pctxt->buffer.byteIndex : pctxt->buffer.byteIndex + 1;

   for (i = 0; i < numocts; i++)
   {
      b = pctxt->buffer.data[i];
      sprintf (buf, "%02x", b);
      hexstr[i%16*3]   = buf[0];
      hexstr[i%16*3+1] = buf[1];
      hexstr[i%16*3+2] = ' ';
      ascstr[i%16] = (b > 31 && b < 128) ? b : '.';
      if ((dumpstr = (OSOCTET)((i + 1) % 16 == 0)) != 0)
      {
         rtxPrintToStream (pctxt, "%48s %16s\n", hexstr, ascstr);
         if (i < (numocts - 1))
         {
            memset (hexstr, ' ', 48);
            memset (ascstr, ' ', 16);
         }
      }
   }

   if (!dumpstr) rtxPrintToStream (pctxt, "%48s %16s\n", hexstr, ascstr);
}
