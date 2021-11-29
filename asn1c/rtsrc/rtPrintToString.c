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

/* Run-time print to string utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rtsrc/rtPrintToString.h"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxPrint.h"

int rtxItoa(OSINT32 value, char* buffer, int bufSize);
int rtxUitoa(OSUINT32 value, char* buffer, int bufSize);
int rtxRtoa(OSREAL value, char* buffer, int bufSize);
int rtxUi64toa(OSUINT64 value, char* buffer, int bufSize);
int rtxI64toa(OSINT64 value, char* buffer, int bufSize);

EXTRTMETHOD int rtPrintToStringBoolean (const char* name, OSBOOL value, 
                            char* buffer, int bufferSize)
{
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if(value) {
      return rtPrintToString(" = TRUE\n", buffer, bufferSize);
   }
   else {
      return rtPrintToString(" = FALSE\n", buffer, bufferSize);
   }
}

EXTRTMETHOD int rtPrintToStringInteger (const char* name, OSINT32 value, 
                            char* buffer, int bufferSize)
{
   char t[75];
   if (rtPrintToString(name, buffer, bufferSize) < 0) {
      return -1;
   }
   sprintf(t, " = %d\n", value);
   return rtPrintToString(t, buffer, bufferSize);
}

EXTRTMETHOD int rtPrintToStringInt64 (const char* name, OSINT64 value, 
                          char* buffer, int bufferSize)
{
   char t[75];
   if (rtPrintToString(name, buffer, bufferSize) < 0) {
      return -1;
   }
   sprintf(t, " = "OSINT64FMT"\n", value);
   return rtPrintToString(t, buffer, bufferSize);
}

EXTRTMETHOD int rtPrintToStringUnsigned (const char* name, OSUINT32 value, 
                             char* buffer, int bufferSize)
{
   char t[75];
   if (rtPrintToString(name, buffer, bufferSize) < 0) {
      return -1;
   }
   sprintf(t, " = %u\n", value);
   return rtPrintToString(t, buffer, bufferSize);
}

EXTRTMETHOD int rtPrintToStringUInt64 (const char* name, OSUINT64 value, 
                           char* buffer, int bufferSize)
{
   char t[75];
   if (rtPrintToString(name, buffer, bufferSize) < 0) {
      return -1;
   }
   sprintf(t, " = "OSUINT64FMT"\n", value);
   return rtPrintToString(t, buffer, bufferSize);
}

#ifndef BITSTR_BYTES_IN_LINE
#define BITSTR_BYTES_IN_LINE 16
#endif

static int rtBitStringDumpToString (OSUINT32 numbits, const OSOCTET* data,
                                    char* buffer, int bufferSize)
{
   OSUINT32 i, numocts = numbits / 8;
   char buff[9];
   
   if (numocts > 8) {
      if (rtPrintToString("\n", buffer, bufferSize) < 0 ) {
         return -1;
      }
   }
   
   for (i = 0; i < numocts; i++) {
      if ((i != 0) && (i % BITSTR_BYTES_IN_LINE == 0)) {
         if (rtPrintToString("\n", buffer, bufferSize) < 0 ) {
            return -1;
         }
      }
      
      if (i % BITSTR_BYTES_IN_LINE == 0)      
         sprintf (buff, "0x%02X", data[i]);
      else
         sprintf (buff, " 0x%02X", data[i]);

      if (rtPrintToString(buff, buffer, bufferSize) < 0 ) {
         return -1;
      }
   }

   if (i * 8 != numbits) {
      OSOCTET tm = data[i];
      OSUINT32 nmBits = numbits % 8;
      OSUINT32 j; 
               
      if ((i % BITSTR_BYTES_IN_LINE) == (BITSTR_BYTES_IN_LINE - 1)) {
         if (rtPrintToString("\n", buffer, bufferSize) < 0 ) {
            return -1;
         }
      }
      else if (i > 0) {
         if (rtPrintToString(" ", buffer, bufferSize) < 0 ) {
            return -1;
         }
      }
      
      for (j = 0; j < nmBits; j++, tm<<=1)
         buff[j] = ((tm >> 7) & 1) + '0';
      for (; j < 8; j++)
         buff[j] = 'x';
      buff[8] = 0;

      if (rtPrintToString(buff, buffer, bufferSize) < 0 ) {
         return -1;
      }
   }
   
   return 0;
}
 
EXTRTMETHOD int rtPrintToStringBitStr (const char* name, OSUINT32 numbits, 
                           const OSOCTET* data, const char* conn, 
                           char* buffer, int bufferSize)
{
   int bufferIndex;
   char t[50];
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if (rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   sprintf(t, "%snumbits = %u\n", conn, numbits);
   if (rtPrintToString(t, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString("data = ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if (rtBitStringDumpToString (numbits, data, buffer + bufferIndex, 
      bufferSize - bufferIndex) < 0 ) 
   {
      return -1;
   }
   if (rtPrintToString("\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringBitStrBraceText 
(const char* name, OSUINT32 numbits, const OSOCTET* data, 
 char* buffer, int bufferSize)
{
   int bufferIndex;
   char t[16];

   if(buffer == 0 || bufferSize == 0) { return -1; }
   if (rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   sprintf(t, " = { %u, ", numbits);
   if (rtPrintToString(t, buffer, bufferSize) < 0 ) {
      return -1;
   }

   bufferIndex = (int)strlen(buffer);
   if (rtBitStringDumpToString (numbits, data, buffer + bufferIndex, 
      bufferSize - bufferIndex) < 0 ) 
   {
      return -1;
   }

   if (rtPrintToString(" }\n", buffer, bufferSize) < 0 ) {
      return -1;
   }

   return 0;
}

EXTRTMETHOD int rtPrintToStringOctStr (const char* name, OSUINT32 numocts, 
                           const OSOCTET* data, const char* conn, 
                           char* buffer, int bufferSize)
{
   int bufferIndex;
   char t[450];
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if (rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   sprintf(t, "%snumocts = %u\n", conn, numocts);
   if (rtPrintToString(t, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if (rtPrintToString("data = \n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if (rtxHexDumpToString 
      (data, numocts, buffer, bufferIndex, bufferSize) < 0) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringCharStr (const char* name, const char* cstring,
                            char* buffer, int bufferSize)
{
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(" = '", buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(cstring, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("'\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringUTF8Str (const char *name, const OSUTF8CHAR *ustring,
      char *buffer, int bufferSize)
{
   return rtPrintToStringCharStr (name, (const char *)ustring, buffer, 
         bufferSize);
}

EXTRTMETHOD int rtPrintToString16BitCharStr (const char* name, 
   Asn116BitCharString* bstring, const char* conn, 
   char* buffer, int bufferSize)
{
   int bufferIndex;
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("nchars = ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtxUitoa(bstring->nchars, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("data = \n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if( rtxHexDumpToStringEx ((OSOCTET*)bstring->data, 
      bstring->nchars * 2, buffer, bufferIndex, bufferSize, 2) < 0) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToString32BitCharStr (const char* name, 
   Asn132BitCharString* bstring, const char* conn, 
   char* buffer, int bufferSize)
{
   int bufferIndex;
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("nchars = ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtxUitoa(bstring->nchars, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(conn, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString("data = \n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if( rtxHexDumpToStringEx ((OSOCTET*)bstring->data, 
      bstring->nchars * sizeof (OS32BITCHAR), buffer, 
      bufferIndex, bufferSize, 4) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringReal (const char* name, OSREAL value,
                         char* buffer, int bufferSize)
{
   char t[75];
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   sprintf(t, " = %g\n", value);
   return rtPrintToString(t, buffer, bufferSize);
}

EXTRTMETHOD int rtPrintToStringOID (const char* name, ASN1OBJID* pOID,
                        char* buffer, int bufferSize)
{
   int bufferIndex;
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(" = ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if( rtPrintToStringOIDValue (pOID, buffer, bufferSize) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringOIDValue
(ASN1OBJID* pOID, char* buffer, int bufferSize)
{
   OSUINT32 ui;
   if( rtPrintToString("{ ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   for (ui = 0; ui < pOID->numids; ui++) {
      if( rtxUitoa(pOID->subid[ui], buffer, bufferSize) < 0 ) {
         return -1;
      }
      if( rtPrintToString(" ", buffer, bufferSize) < 0 ) {
         return -1;
      }
   }
   if( rtPrintToString("}\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringOID64 (const char* name, ASN1OID64* pOID,
                          char* buffer, int bufferSize)
{
   int bufferIndex;
   if(buffer == 0 || bufferSize == 0) { return -1; }
   if( rtPrintToString(name, buffer, bufferSize) < 0 ) {
      return -1;
   }
   if( rtPrintToString(" = ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   bufferIndex = (int)strlen(buffer);
   if( rtPrintToStringOID64Value (pOID, buffer, bufferSize) < 0) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringOID64Value
(ASN1OID64* pOID, char* buffer, int bufferSize)
{
   OSUINT32 ui;
   if( rtPrintToString("{ ", buffer, bufferSize) < 0 ) {
      return -1;
   }
   for (ui = 0; ui < pOID->numids; ui++) {
      if (rtxUi64toa(pOID->subid[ui], buffer, bufferSize) < 0 ) {
         return -1;
      }
      if (rtPrintToString(" ", buffer, bufferSize) < 0 ) {
         return -1;
      }
   }
   if (rtPrintToString("}\n", buffer, bufferSize) < 0 ) {
      return -1;
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStringOpenType (const char* name, OSUINT32 numocts, 
                             const OSOCTET* data, const char*  conn,
                             char* buffer, int bufferSize)
{
   return rtPrintToStringOctStr(name, numocts, data, conn, buffer, bufferSize);
}

EXTRTMETHOD int rtPrintToStringOpenTypeExt (const char* name, OSRTDList* pElemList,
                              char* buffer, int bufferSize)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            if( rtPrintToStringOpenType (name, pOpenType->numocts,
               pOpenType->data, ".", buffer, bufferSize) < 0) {
               return -1;
            }
         }
         pnode = pnode->next;
      }
   }
   return 0;
}

EXTRTMETHOD int rtPrintToString (const char* namebuf, char* buffer, int bufSize)
{
   int bufIndex;
   if ( buffer == 0 || bufSize == 0 ) { return -1; }
   if ( namebuf == 0 ) { return 0; }
   bufIndex = (int) strlen(buffer);
   if((int)strlen(namebuf) >= (bufSize - bufIndex))
   {
      return -1;
   }
   strcpy(&buffer[bufIndex], namebuf);
   return 0;
}

EXTRTMETHOD int rtPrintToStringUnicodeCharStr 
   (const char* name, Asn116BitCharString* bstring, char* buffer, int bufSize)
{
   char t[450];
   OSUINT32 i;

   sprintf (t, "%s = '", name);
   if(rtPrintToString(t, buffer, bufSize) < 0)
      return -1;
   
   for (i = 0; i < bstring->nchars; i++) {
      if (OS_ISPRINT (bstring->data[i])){
         sprintf (t, "%c", bstring->data[i]);
      }
      else{
         sprintf (t, "0x%04x", bstring->data[i]);
      }
      if(rtPrintToString(t, buffer, bufSize) < 0)
         return -1;
   }
   if(rtPrintToString ("'\n", buffer, bufSize) < 0)
      return -1;
   
   return 0;
}

EXTRTMETHOD int rtPrintToStringUnivCharStr 
   (const char* name, Asn132BitCharString* bstring, char* buffer, int bufSize)
{
   char t[450];
   OSUINT32 i;

   sprintf (t, "%s = '", name);
   if(rtPrintToString(t, buffer, bufSize) < 0)
      return -1;
   
   for (i = 0; i < bstring->nchars; i++) {
      if (OS_ISPRINT (bstring->data[i]))
         sprintf (t, "%c", bstring->data[i]);
      else
         sprintf (t, "0x%08x", bstring->data[i]);

      if(rtPrintToString(t, buffer, bufSize) < 0)
         return -1;
   }

   if(rtPrintToString("'\n", buffer, bufSize) < 0)
      return -1;

   return 0;
}

EXTRTMETHOD int rtPrintToStringHexStr 
   (const char* name, OSUINT32 numocts, const OSOCTET* data, char* buffer, 
    int bufSize)
{
   char t[450];
    
   if (numocts <= 32) {
      OSUINT32 i;
      sprintf(t, "%s = 0x", name);
      if(rtPrintToString(t, buffer, bufSize) < 0)
         return -1;

      for (i = 0; i < numocts; i++) {
         sprintf (t, "%02x", data[i]);
         if(rtPrintToString(t, buffer, bufSize) < 0)
            return -1;
      }
      if(rtPrintToString ("\n", buffer, bufSize) < 0)
         return -1;
   }
   else {
      int bufferIndex = (int)strlen(buffer);
      if(rtxHexDumpToString (data, numocts, buffer, bufferIndex, bufSize) < 0)
         return -1;
   }
   return 0;
}

#ifndef __SYMBIAN32__

EXTRTMETHOD int rtPrintToStringOpenTypeExtBraceText 
   (const char* name, OSRTDList* pElemList, char* buffer, int bufSize)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            if(rtPrintToStringIndent (buffer, bufSize) < 0)
               return -1;
	    if(rtPrintToStringHexStr (name, pOpenType->numocts, 
                                      pOpenType->data, buffer, bufSize) < 0)
               return -1;
	    
         }
         pnode = pnode->next;
      }
   }
   return 0;
}
#endif

int rtxItoa(OSINT32 value, char* buffer, int bufSize) 
{
   char t[64];
   sprintf(t, "%d", value);
   return rtPrintToString(t, buffer, bufSize);
}

int rtxUitoa(OSUINT32 value, char* buffer, int bufSize) 
{
   char t[64];
   sprintf(t, "%u", value);
   return rtPrintToString(t, buffer, bufSize);
}

int rtxRtoa(OSREAL value, char* buffer, int bufSize) 
{
   char t[64];
   sprintf(t, "%g", value);
   return rtPrintToString(t, buffer, bufSize);
}

int rtxUi64toa(OSUINT64 value, char* buffer, int bufSize) 
{
   char t[64];
   sprintf(t, OSUINT64FMT, value);
   return rtPrintToString(t, buffer, bufSize);
}
   
int rtxI64toa(OSINT64 value, char* buffer, int bufSize) 
{
   char t[64];
   sprintf(t, OSINT64FMT, value);
   return rtPrintToString(t, buffer, bufSize);
}

#ifndef __SYMBIAN32__

/* Indentation for brace text printing */

static OSUINT32 g_indent = 0;

EXTRTMETHOD int rtPrintToStringIndent (char* buffer, int bufSize)
{
   OSUINT32 i;
   for (i = 0; i < g_indent; i++){
      if(rtPrintToString (" ", buffer, bufSize) < 0)
         return -1;
   }
   return 0;
       
}

EXTRTMETHOD void rtPrintToStringIncrIndent ()
{
   g_indent += OSRTINDENTSPACES;
}

EXTRTMETHOD void rtPrintToStringDecrIndent ()
{
   if (g_indent > 0) 
      g_indent -= OSRTINDENTSPACES;
}

EXTRTMETHOD int rtPrintToStringCloseBrace (char* buffer, int bufSize)
{
   rtPrintToStringDecrIndent ();
   if(rtPrintToStringIndent (buffer, bufSize) < 0)
      return -1;
   
   if(rtPrintToString ("}\n", buffer, bufSize) < 0)
      return -1;
   
   return 0;
}

EXTRTMETHOD int rtPrintToStringOpenBrace (const char* name, char* buffer, int bufSize)
{
   if(rtPrintToStringIndent (buffer, bufSize) < 0)
      return -1;
    
   if(rtPrintToString(name, buffer, bufSize) < 0)
      return -1;
   
   if(rtPrintToString (" {\n", buffer, bufSize) < 0)
      return -1;
   
   rtPrintToStringIncrIndent ();
   return 0;
}
#endif
