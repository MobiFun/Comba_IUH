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

/* Run-time converting utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rtsrc/rtconv.h"
#include "rtxsrc/rtxCtype.h"

/* 'toString' functions: these provide a stringified representation in  */
/* ASN.1 value notation format for each of the primitive types..        */

EXTRTMETHOD const char* rtBoolToString (OSBOOL value)
{
   return value ? "TRUE" : "FALSE";
}

EXTRTMETHOD const char* rtIntToString (OSINT32 value, char* buffer, size_t bufsiz)
{
   char lbuf[32];
   sprintf (lbuf, "%d", value);
   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz; 
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';
   return buffer;
}

EXTRTMETHOD const char* rtInt64ToString 
   (OSINT64 value, char* buffer, size_t bufsiz)
{
   char lbuf[32];
   sprintf (lbuf, OSINT64FMT, value);
   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz;
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';
   return buffer;
}

EXTRTMETHOD const char* rtUIntToString 
   (OSUINT32 value, char* buffer, size_t bufsiz)
{
   char lbuf[32];
   sprintf (lbuf, "%u", value);
   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz; 
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';
   return buffer;
}

EXTRTMETHOD const char* rtUInt64ToString 
   (OSUINT64 value, char* buffer, size_t bufsiz)
{
   char lbuf[32];
   sprintf (lbuf, OSUINT64FMT, value);
   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz; 
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';
   return buffer;
}

EXTRTMETHOD const char* rtBitStrToString (OSUINT32 numbits, const OSOCTET* data,
                              char* buffer, size_t bufsiz)
{
   size_t i;
   unsigned char mask = 0x80;

   if (bufsiz > 0) {
      buffer[0] = '\'';
      for (i = 0; i < numbits; i++) {
         if (i < bufsiz - 1) {
            buffer[i+1] = (char) (((data[i/8] & mask) != 0) ? '1' : '0');
            mask >>= 1;
            if (0 == mask) mask = 0x80;
         }
         else break;
      }
     i++;
      if (i < bufsiz - 1) buffer[i++] = '\'';
      if (i < bufsiz - 1) buffer[i++] = 'B';
      if (i < bufsiz - 1) buffer[i] = '\0';
      else buffer[bufsiz - 1] = '\0';
   }

   return buffer;
}

EXTRTMETHOD const char* rtOctStrToString (OSUINT32 numocts, const OSOCTET* data, 
                              char* buffer, size_t bufsiz)
{
   size_t i;
   char lbuf[4];

   if (bufsiz > 0) {
      buffer[0] = '\'';
      if (bufsiz > 1) buffer[1] = '\0';
      for (i = 0; i < numocts; i++) {
         if (i < bufsiz - 1) {
            sprintf (lbuf, "%02x", data[i]);
            strcat (&buffer[(i*2)+1], lbuf);
         }
         else break;
      }
     i = i*2 + 1;
      if (i < bufsiz - 1) buffer[i++] = '\'';
      if (i < bufsiz - 1) buffer[i++] = 'H';
      if (i < bufsiz - 1) buffer[i] = '\0';
      else buffer[bufsiz - 1] = '\0';
   }

   return buffer;
}

EXTRTMETHOD const char* rtOIDToString (OSUINT32 numids, OSUINT32* data, 
                                char* buffer, size_t bufsiz)
{
   size_t ui, cnt;
   char lbuf[16];

   if (bufsiz < 6) return 0;
   strcpy (buffer, "{ ");
   cnt = 2;

   for (ui = 0; ui < numids; ui++) {
      sprintf (lbuf, "%u ", data[ui]);
      if ((strlen(lbuf) + cnt) < bufsiz) {
         strcat (buffer, lbuf);
         cnt += strlen(lbuf);
      }
      else return buffer;
   }

   if ((cnt + 1) < bufsiz) strcat (buffer, "}");

   return buffer;
}

EXTRTMETHOD const char* rtOID64ToString (OSUINT32 numids, OSUINT64* data, 
                             char* buffer, size_t bufsiz)
{
   size_t ui, cnt;
   char lbuf[32];

   if (bufsiz < 6) return 0;
   strcpy (buffer, "{ ");
   cnt = 2;

   for (ui = 0; ui < numids; ui++) {
      sprintf (lbuf, OSUINT64FMT" ", data[ui]);
      if ((strlen(lbuf) + cnt) < bufsiz) {
         strcat (buffer, lbuf);
         cnt += strlen(lbuf);
      }
      else return buffer;
   }

   if ((cnt + 1) < bufsiz) strcat (buffer, "}");

   return buffer;
}

EXTRTMETHOD const char* rtTagToString (ASN1TAG tag, char* buffer, size_t bufsiz)
{
   OSUINT32 idmask = 0xFFFFFFFF >> (((sizeof(ASN1TAG) - 2) * 8) + 3);
   OSUINT32 idcode = ((OSUINT32)tag) & idmask;
   ASN1TAG  tclass = tag & TM_PRIV;
   char lbuf[32];

   switch (tclass) {
   case TM_UNIV: sprintf (lbuf, "[UNIVERSAL %d]", idcode); break;
   case TM_APPL: sprintf (lbuf, "[APPLICATION %d]", idcode); break;
   case TM_CTXT: sprintf (lbuf, "[%d]", idcode); break;
   case TM_PRIV: sprintf (lbuf, "[PRIVATE %d]", idcode); break;
   default:      sprintf (lbuf, "[??? %d]", idcode); break;
   }

   bufsiz = (sizeof (lbuf) < bufsiz) ? sizeof (lbuf) : bufsiz;
   strncpy (buffer, lbuf, bufsiz);
   buffer[bufsiz-1] = '\0';

   return buffer;
}
