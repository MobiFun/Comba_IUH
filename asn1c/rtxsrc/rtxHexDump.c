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

/* Run-time utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rtxsrc/osMacros.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxErrCodes.h"

/* Hex dump function */

static char* strTrim (char *s)
{
   int i = (int)OSCRTLSTRLEN(s) - 1;
   while (s[i] == ' ') i--;
   s[i+1] = '\0';
   return (s);
}

EXTRTMETHOD int rtxByteToHexChar (OSOCTET byte, char* buf, size_t bufsize)
{
   OSUINT32 tmpval = byte;
   if (bufsize < 3) return RTERR_BUFOVFLW;
   tmpval >>= 4;   
   buf[0] = (char)((tmpval <= 9) ? tmpval + '0' : tmpval - 10 + 'a');
   tmpval = byte & 0x0F;  /* shave off MS nibble */
   buf[1] = (char)((tmpval <= 9) ? tmpval + '0' : tmpval - 10 + 'a');
   buf[2] = '\0';
   return 0;
}

EXTRTMETHOD void rtxHexDumpToNamedFile 
(const char* filename, const OSOCTET* data, OSUINT32 numocts)
{
   FILE* fp = fopen (filename, "w");
   if (0 != fp) {
      rtxHexDumpToFileEx (fp, data, numocts, 1);
      fclose (fp);
   }
}

EXTRTMETHOD void rtxHexDumpToFile (FILE* fp, const OSOCTET* data, OSUINT32 numocts)
{
   rtxHexDumpToFileEx (fp, data, numocts, 1);
}

EXTRTMETHOD void rtxHexDumpToFileEx 
(FILE* fp, const OSOCTET* data, OSUINT32 numocts, int bytesPerUnit)
{
   OSUINT32 i;
   OSUINT32 val; 
   OSOCTET  b, dumpstr = 1;
   char     hexstr[49], ascstr[17], buf[20], *pbuf;
   int      k, unitsPerLine = 16 / bytesPerUnit, ai, shift;

   OSCRTLMEMSET (hexstr, ' ', 48); hexstr[48] = '\0';
   OSCRTLMEMSET (ascstr, ' ', 16); ascstr[16] = '\0';
   ai = 0;

   if (bytesPerUnit > 4) bytesPerUnit = 4;

   for (i = 0; i < numocts / bytesPerUnit; i++)
   {
      pbuf = (char*)buf;
      buf [bytesPerUnit * 2] = 0;
      if (bytesPerUnit == 1) {
         val = *data++;
         shift = 0;
      }
      else if (bytesPerUnit == 2) {
         val = *((const OSUINT16*)data);
         data += sizeof (OSUINT16);
         shift = 8;
      }
      else { /* greater than 2 */
         val = *((const OSUINT32*)data);
         data += sizeof (OSUINT32);
         shift = (sizeof (OSUINT32) - 1) * 8;
      }
      for (k = 0; k < bytesPerUnit; k++, pbuf += 2, shift -= 8) {
         b = (OSOCTET)((val >> shift) & 0xFF);
         rtxByteToHexChar (b, pbuf, 20);
         ascstr[ai++] = (char) (OS_ISPRINT(b) ? b : '.');
      }
      *pbuf = 0;

      k = i % unitsPerLine * (bytesPerUnit * 2 + 1);
      OSCRTLMEMCPY (&hexstr[k], buf, bytesPerUnit * 2);

      if ((dumpstr = (OSOCTET) ((i + 1) % unitsPerLine == 0)) != 0)
      {
         fprintf (fp, "%48s %16s\n", hexstr, ascstr);
         if (i < (numocts - 1)) {
            OSCRTLMEMSET (hexstr, ' ', 48);
            OSCRTLMEMSET (ascstr, ' ', 16);
            ai = 0;
         }
      }
   }

   if (!dumpstr) fprintf (fp, "%48s %s\n", hexstr, strTrim(ascstr));
}

EXTRTMETHOD void rtxHexDumpToRedirectPrint
(const OSOCTET* data, OSUINT32 numocts, int bytesPerUnit)
{
   OSUINT32 i;
   OSUINT32 val; 
   OSOCTET  b, dumpstr = 1;
   char     hexstr[49], ascstr[17], buf[20], *pbuf;
   int      k, unitsPerLine = 16 / bytesPerUnit, ai, shift;

   OSCRTLMEMSET (hexstr, ' ', 48); hexstr[48] = '\0';
   OSCRTLMEMSET (ascstr, ' ', 16); ascstr[16] = '\0';
   ai = 0;

   if (bytesPerUnit > 4) bytesPerUnit = 4;

   for (i = 0; i < numocts / bytesPerUnit; i++)
   {
      pbuf = (char*)buf;
      buf [bytesPerUnit * 2] = 0;
      if (bytesPerUnit == 1) {
         val = *data++;
         shift = 0;
      }
      else if (bytesPerUnit == 2) {
         val = *((const OSUINT16*)data);
         data += sizeof (OSUINT16);
         shift = 8;
      }
      else { /* greater than 2 */
         val = *((const OSUINT32*)data);
         data += sizeof (OSUINT32);
         shift = (sizeof (OSUINT32) - 1) * 8;
      }
      for (k = 0; k < bytesPerUnit; k++, pbuf += 2, shift -= 8) {
         b = (OSOCTET)((val >> shift) & 0xFF);
         rtxByteToHexChar (b, pbuf, 20);
         ascstr[ai++] = (char) (OS_ISPRINT(b) ? b : '.');
      }
      *pbuf = 0;

      k = i % unitsPerLine * (bytesPerUnit * 2 + 1);
      OSCRTLMEMCPY (&hexstr[k], buf, bytesPerUnit * 2);

      if ((dumpstr = (OSOCTET) ((i + 1) % unitsPerLine == 0)) != 0)
      {
         rtxRedirectPrint ( "%48s %16s\n", hexstr, ascstr);
         if (i < (numocts - 1)) {
            OSCRTLMEMSET (hexstr, ' ', 48);
            OSCRTLMEMSET (ascstr, ' ', 16);
            ai = 0;
         }
      }
   }

   if (!dumpstr) rtxRedirectPrint ( "%48s %s\n", hexstr, strTrim(ascstr));
}

EXTRTMETHOD void rtxHexDump (const OSOCTET* data, OSUINT32 numocts)
{
   rtxHexDumpToRedirectPrint (data, numocts, 1);
}

EXTRTMETHOD void rtxHexDumpEx (const OSOCTET* data, OSUINT32 numocts, int bytesPerUnit)
{
   rtxHexDumpToFileEx (stdout, data, numocts, bytesPerUnit);
}

EXTRTMETHOD int rtxHexDumpToString 
(const OSOCTET* data, OSUINT32 numocts, char* buffer, 
 int bufferIndex, int bufferSize)
{
   return rtxHexDumpToStringEx 
      (data, numocts, buffer, bufferIndex, bufferSize, 1);
}

EXTRTMETHOD int rtxHexDumpToStringEx (const OSOCTET* data, OSUINT32 numocts, char* buffer, 
                          int bufferIndex, int bufferSize, int bytesPerUnit)
{
   OSUINT32    i;
   OSUINT32    val; 
   int         k, unitsPerLine = 16 / bytesPerUnit;
   OSOCTET     b, dumpstr = 1;
   char        hexstr[49], ascstr[17], buf[20], *pbuf;
   int         ai, shift;

   /* Check no of octets to be copied */
   if(numocts == 0) {
      return 0;
   }

   if ((bytesPerUnit != 1 && bytesPerUnit != 2 && 
        bytesPerUnit != 4 && bytesPerUnit != 8) ||
       numocts % bytesPerUnit != 0)
      return 0;
   OSCRTLMEMSET (hexstr, ' ', 48); hexstr[48] = '\0';
   OSCRTLMEMSET (ascstr, ' ', 16); ascstr[16] = '\0';
   ai = 0;

   if (bytesPerUnit > 4) bytesPerUnit = 4;

   for (i = 0; i < numocts / bytesPerUnit; i++)
   {
      pbuf = (char*)buf;
      buf [bytesPerUnit * 2] = 0;
      if (bytesPerUnit == 1) {
         val = *data++;
         shift = 0;
      }
      else if (bytesPerUnit == 2) {
         val = *((const OSUINT16*)data);
         data += sizeof (OSUINT16);
         shift = 8;
      }
      else { /* greater than 2 */
         val = *((const OSUINT32*)data);
         data += sizeof (OSUINT32);
         shift = (sizeof (OSUINT32) - 1) * 8;
      }
      for (k = 0; k < bytesPerUnit; k++, pbuf += 2, shift -= 8) {
         b = (OSOCTET)((val >> shift) & 0xFF);
         rtxByteToHexChar (b, pbuf, 20);
         ascstr[ai++] = (char) (OS_ISPRINT(b) ? b : '.');
      }
      *pbuf = 0;

      k = i % unitsPerLine * (bytesPerUnit * 2 + 1);
      OSCRTLMEMCPY (&hexstr[k], buf, bytesPerUnit * 2);

      if ((dumpstr = (OSOCTET) ((i + 1) % unitsPerLine == 0)) != 0)
      {
         if((bufferSize - bufferIndex) < (48+1+16+1)) {
            return -1;
         }
         rtxStrcat (buffer, (bufferSize - bufferIndex), hexstr);
         rtxStrcat (buffer, (bufferSize - bufferIndex), " ");
         rtxStrcat (buffer, (bufferSize - bufferIndex), ascstr);
         rtxStrcat (buffer, (bufferSize - bufferIndex), "\n");
         bufferIndex = OSCRTLSTRLEN (buffer);
         if (i < (numocts - 1)) {
            OSCRTLMEMSET (hexstr, ' ', 48);
            OSCRTLMEMSET (ascstr, ' ', 16);
            ai = 0;
         }
      }
   }

   if (!dumpstr) {
      char* tascstr =  strTrim(ascstr);
      if((bufferSize - bufferIndex) < (int)(48+1+OSCRTLSTRLEN(tascstr)+1)) {
         return -1;
      }
      rtxStrcat (buffer, (bufferSize - bufferIndex), hexstr);
      rtxStrcat (buffer, (bufferSize - bufferIndex), " ");
      rtxStrcat (buffer, (bufferSize - bufferIndex), ascstr);
      rtxStrcat (buffer, (bufferSize - bufferIndex), "\n");
   }
   return OSCRTLSTRLEN (buffer);
}
