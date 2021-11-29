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

/* Run-time compare utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "asn1type.h"
#include "rtPrint.h"
#include "rtCompare.h"
#include "rtPrintToString.h"

/* compare functions */

EXTRTMETHOD OSBOOL rtCmpBoolean (const char* name, OSBOOL value, OSBOOL compValue, 
   char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringBoolean(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringBoolean(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutBoolean (const char* name, OSBOOL value, 
   OSBOOL compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintBoolean(name, value);
   printf("Received: ");
   rtPrintBoolean(name, compValue);
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpInt8 (const char* name, OSINT8 value, OSINT8 compValue,
   char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpUInt8 (const char* name, OSUINT8 value, 
   OSUINT8 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpSInt (const char* name, OSINT16 value, 
   OSINT16 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpUSInt (const char* name, OSUINT16 value, 
   OSUINT16 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpInteger (const char* name, OSINT32 value, OSINT32 compValue,
   char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInteger(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpInt64 (const char* name, OSINT64 value, 
   OSINT64 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringInt64(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringInt64(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpToStdoutInteger (const char* name, OSINT32 value, 
   OSINT32 compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      printf("%s: value is not equal\n", name);
      printf("Expected: ");
      rtPrintInteger(name, value);
      printf("Received: ");
      rtPrintInteger(name, compValue);
      printf("\n");
      return FALSE;
   }
#else
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpToStdoutInt64 (const char* name, 
   OSINT64 value, OSINT64 compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      printf("%s: value is not equal\n", name);
      printf("Expected: ");
      rtPrintInt64(name, value);
      printf("Received: ");
      rtPrintInt64(name, compValue);
      printf("\n");
      return FALSE;
   }
#else
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpUnsigned (const char* name, OSUINT32 value, 
   OSUINT32 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringUnsigned(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringUnsigned(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpUInt64 (const char* name, OSUINT64 value, 
   OSUINT64 compValue, char* errBuff, int errBuffSize)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringUInt64(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringUInt64(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      return FALSE;
   }
#else
   if(errBuff) { *errBuff = 0; }
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpToStdoutUnsigned (const char* name, OSUINT32 value, 
   OSUINT32 compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      printf("%s: value is not equal\n", name);
      printf("Expected: ");
      rtPrintUnsigned(name, value);
      printf("Received: ");
      rtPrintUnsigned(name, compValue);
      printf("\n");
      return FALSE;
   }
#else
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpToStdoutUInt64 (const char* name, 
   OSUINT64 value, OSUINT64 compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   else 
   {
      printf("%s: value is not equal\n", name);
      printf("Expected: ");
      rtPrintUInt64(name, value);
      printf("Received: ");
      rtPrintUInt64(name, compValue);
      printf("\n");
      return FALSE;
   }
#else
   return FALSE;
#endif
}

EXTRTMETHOD OSBOOL rtCmpBitStr (const char* name, OSUINT32 numbits, 
   const OSOCTET* data, OSUINT32 compNumbits, const OSOCTET* compData, 
   char* errBuff, int errBuffSize)
{
   if (numbits == compNumbits) {
      register int i, wholeBytesNum = numbits/8;
      OSOCTET mask;

      for (i = 0; i < wholeBytesNum; i++) {
         if (data[i] != compData[i])
            break;
      }

      /* compare the bits in the last octet */
      if (i >= wholeBytesNum) {
         if (numbits % 8 == 0) 
            return TRUE;

         mask = (OSOCTET)((OSINTCONST(1) << (8 - numbits % 8)) - 1);
         if ((data[i] & (~mask)) == (compData[i] & (~mask)))
            return TRUE;
      }
   }

#ifndef _COMPACT
   {
   int bufIndex;
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: \n", errBuff, errBuffSize);
   if(errBuff != 0 && errBuffSize != 0) {
      bufIndex = (int)strlen(errBuff);
      rtBitStrToString(numbits, data, errBuff + bufIndex, numbits + 4);
   }
   rtPrintToString("\n", errBuff, errBuffSize);
   rtPrintToString("Received: \n", errBuff, errBuffSize);
   if(errBuff != 0 && errBuffSize != 0) {
      bufIndex = (int)strlen(errBuff);
      rtBitStrToString(compNumbits, compData, errBuff + bufIndex, 
         compNumbits + 4);
   }
   rtPrintToString("\n", errBuff, errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutBitStr (const char* name, OSUINT32 numbits, 
   const OSOCTET* data, OSUINT32 compNumbits, const OSOCTET* compData)
{
   if (numbits == compNumbits) {
      register int i, wholeBytesNum = numbits/8;
      OSOCTET mask;

      for (i = 0; i < wholeBytesNum; i++) {
         if (data[i] != compData[i])
            break;
      }

      /* compare the bits in the last octet */
      if (i >= wholeBytesNum) {
         if (numbits % 8 == 0) 
            return TRUE;

         mask = (OSOCTET)((OSINTCONST(1) << (8 - numbits % 8)) - 1);
         if ((data[i] & (~mask)) == (compData[i] & (~mask)))
            return TRUE;
      }
   }

#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: \n");
   rtPrintBitStr (name, numbits, data, ".");
   printf("Received: \n");
   rtPrintBitStr (name, compNumbits, compData, ".");
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpOctStr (const char* name, OSUINT32 numocts, 
   const OSOCTET* data, OSUINT32 compNumocts, const OSOCTET* compData, 
   char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(numocts == compNumocts)
   {
      unsigned int i;
      for(i=0; i < numocts; i++)
      {
         /* comparing unsigned char (Octet String octets) */
         if(data[i] != compData[i])    
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: \n", errBuff, errBuffSize);
   rtPrintToStringOctStr(name, numocts, data, ".", errBuff, errBuffSize);
   rtPrintToString("Received: \n", errBuff, errBuffSize);
   rtPrintToStringOctStr(name, compNumocts, compData, ".", errBuff, 
      errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOctStr (const char* name, OSUINT32 numocts, 
   const OSOCTET* data, OSUINT32 compNumocts, const OSOCTET* compData)
{
   OSBOOL rel = TRUE;
   if(numocts == compNumocts)
   {
      unsigned int i;
      for(i=0; i < numocts; i++)
      {
         /* comparing unsigned char (Octet String octets) */
         if(data[i] != compData[i])    
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintOctStr(name, numocts, data, ".");
   printf("Received: ");
   rtPrintOctStr(name, compNumocts, compData, ".");
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpCharStr (const char* name, const char* cstring, 
   const char* compCstring, char* errBuff, int errBuffSize)
{
   if (!strcmp(cstring, compCstring)) {
      return TRUE;
   }
#ifndef _COMPACT
   else {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringCharStr(name, cstring, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringCharStr(name, compCstring, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutCharStr (const char* name, 
   const char* cstring, const char* compCstring)
{
   if(! strcmp(cstring, compCstring))
   {
      return TRUE;
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintCharStr(name, cstring);
   printf("Received: ");
   rtPrintCharStr(name, compCstring);
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmp16BitCharStr (const char* name, 
   Asn116BitCharString* bstring, Asn116BitCharString* compBstring, 
   char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(bstring->nchars == compBstring->nchars)
   {
      unsigned int i;
      for(i=0; i< bstring->nchars; i++)
      {
         /* BMPString charcters are 'unsigned short' */
         if(bstring->data[i] != compBstring->data[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: ", errBuff, errBuffSize);
   rtPrintToString16BitCharStr(name, bstring, ".", errBuff, errBuffSize);
   rtPrintToString("Received: ", errBuff, errBuffSize);
   rtPrintToString16BitCharStr(name, compBstring, ".", errBuff, errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

/* BMP String */
EXTRTMETHOD OSBOOL rtCmpToStdout16BitCharStr (const char* name, 
   Asn116BitCharString* bstring, Asn116BitCharString* compBstring)
{
   OSBOOL rel = TRUE;
   if(bstring->nchars == compBstring->nchars)
   {
      unsigned int i;
      for(i=0; i< bstring->nchars; i++)
      {
         /* BMPString charcters are 'unsigned short' */
         if(bstring->data[i] != compBstring->data[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrint16BitCharStr(name, bstring);
   printf("Received: ");
   rtPrint16BitCharStr(name, compBstring);
   printf("\n");
#endif
   return FALSE;
}

/* Universal string */
EXTRTMETHOD OSBOOL rtCmp32BitCharStr (const char* name, 
   Asn132BitCharString* bstring, Asn132BitCharString* compBstring, 
   char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(bstring->nchars == compBstring->nchars)
   {
      unsigned int i;
      for(i=0; i< bstring->nchars; i++)
      {
         /* Universal String charcters are 'unsigned integer' */
         if(bstring->data[i] != compBstring->data[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: ", errBuff, errBuffSize);
   rtPrintToString32BitCharStr(name, bstring, ".", errBuff, errBuffSize);
   rtPrintToString("Received: ", errBuff, errBuffSize);
   rtPrintToString32BitCharStr(name, compBstring, ".", errBuff, errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

/* Universal string */
EXTRTMETHOD OSBOOL rtCmpToStdout32BitCharStr (const char* name, 
   Asn132BitCharString* bstring, Asn132BitCharString* compBstring)
{
   OSBOOL rel = TRUE;
   if(bstring->nchars == compBstring->nchars)
   {
      unsigned int i;
      for(i=0; i< bstring->nchars; i++)
      {
         /* Universal String charcters are 'unsigned integer' */
         if(bstring->data[i] != compBstring->data[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrint32BitCharStr(name, bstring, ".");
   printf("Received: ");
   rtPrint32BitCharStr(name, compBstring, ".");
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpReal (const char* name, OSREAL value, OSREAL compValue, 
   char* errBuff, int errBuffSize)
{
   if(value == compValue) {
      return TRUE;
   }
#ifndef _COMPACT
   else {
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: ", errBuff, errBuffSize);
      rtPrintToStringReal(name, value, errBuff, errBuffSize);
      rtPrintToString("Received: ", errBuff, errBuffSize);
      rtPrintToStringReal(name, compValue, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutReal (const char* name, 
   OSREAL value, OSREAL compValue)
{
   if(value == compValue)
   {
      return TRUE;
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintReal(name, value);
   printf("Received: ");
   rtPrintReal(name, compValue);
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpOID (const char* name, ASN1OBJID* pOID, ASN1OBJID* pcompOID,
   char* errBuff, int errBuffSize)
{
   return rtCmpOIDValue (name, pOID, pcompOID, errBuff, errBuffSize);
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOID (const char* name, ASN1OBJID* pOID, 
   ASN1OBJID* pcompOID)
{
   return rtCmpToStdoutOIDValue (name, pOID, pcompOID);
}

EXTRTMETHOD OSBOOL rtCmpOIDValue (const char* name, ASN1OBJID* pOID, 
   ASN1OBJID* pcompOID, char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(pOID->numids == pcompOID->numids)
   {
      unsigned int i;
      for(i=0; i< pOID->numids; i++)
      {
         if(pOID->subid[i] != pcompOID->subid[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: ", errBuff, errBuffSize);
   rtPrintToStringOID(name, pOID, errBuff, errBuffSize);
   rtPrintToString("Received: ", errBuff, errBuffSize);
   rtPrintToStringOID(name, pcompOID, errBuff, errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOIDValue (const char* name, ASN1OBJID* pOID, 
   ASN1OBJID* pcompOID)
{
   OSBOOL rel = TRUE;
   if(pOID->numids == pcompOID->numids)
   {
      unsigned int i;
      for(i=0; i< pOID->numids; i++)
      {
         if(pOID->subid[i] != pcompOID->subid[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintOID(name, pOID);
   printf("Received: ");
   rtPrintOID(name, pcompOID);
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpOID64 (const char* name, ASN1OID64* pOID, 
   ASN1OID64* pcompOID, char* errBuff, int errBuffSize)
{
   return rtCmpOID64Value (name, pOID, pcompOID, errBuff, errBuffSize);
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOID64 (const char* name, ASN1OID64* pOID, 
   ASN1OID64* pcompOID)
{
   return rtCmpToStdoutOID64Value (name, pOID, pcompOID);
}

EXTRTMETHOD OSBOOL rtCmpOID64Value (const char* name, ASN1OID64* pOID, 
   ASN1OID64* pcompOID, char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(pOID->numids == pcompOID->numids)
   {
      unsigned int i;
      for(i=0; i< pOID->numids; i++)
      {
         if(pOID->subid[i] != pcompOID->subid[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: ", errBuff, errBuffSize);
   rtPrintToStringOID64(name, pOID, errBuff, errBuffSize);
   rtPrintToString("Received: ", errBuff, errBuffSize);
   rtPrintToStringOID64(name, pcompOID, errBuff, errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOID64Value (const char* name, ASN1OID64* pOID, 
   ASN1OID64* pcompOID)
{
   OSBOOL rel = TRUE;
   if(pOID->numids == pcompOID->numids)
   {
      unsigned int i;
      for(i=0; i< pOID->numids; i++)
      {
         if(pOID->subid[i] != pcompOID->subid[i])
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintOID64(name, pOID);
   printf("Received: ");
   rtPrintOID64(name, pcompOID);
   printf("\n");
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpOpenType (const char* name, 
                  OSUINT32 numocts, const OSOCTET* data, 
                  OSUINT32 compNumocts, const OSOCTET* compData, 
                  char* errBuff, int errBuffSize)
{
   OSBOOL rel = TRUE;
   if(numocts == compNumocts)
   {
      unsigned int i;
      for(i=0; i< numocts; i++)
      {
         /* comparing unsigned char (Octet String octets) */
         if(data[i] != compData[i])    
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   {
   rtPrintToString(name, errBuff, errBuffSize);
   rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
   rtPrintToString("Expected: ", errBuff, errBuffSize);
   rtPrintToStringOpenType(name, numocts, data, ".", errBuff, errBuffSize);
   rtPrintToString("Received: ", errBuff, errBuffSize);
   rtPrintToStringOpenType(name, compNumocts, compData, ".", errBuff, 
      errBuffSize);
   rtPrintToString("\n", errBuff, errBuffSize);
   }
#else
   if(errBuff) { *errBuff = 0; }
#endif
   return FALSE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOpenType (const char* name, 
                  OSUINT32 numocts, const OSOCTET* data, 
                  OSUINT32 compNumocts, const OSOCTET* compData)
{
   OSBOOL rel = TRUE;
   if(numocts == compNumocts)
   {
      unsigned int i;
      for(i=0; i< numocts; i++)
      {
         /* comparing unsigned char (Octet String octets) */
         if(data[i] != compData[i])    
         {
            rel = FALSE;
            break;
         }
      }
      if(rel) {
         return TRUE;
      }
   }
#ifndef _COMPACT
   printf("%s: value is not equal\n", name);
   printf("Expected: ");
   rtPrintOpenType(name, numocts, data, ".");
   printf("Received: ");
   rtPrintOpenType(name, compNumocts, compData, ".");
   printf("\n");
#endif
   return FALSE;
}

extern int rtxItoa(OSINT32 value, char* buffer, int bufSize);

EXTRTMETHOD OSBOOL rtCmpOpenTypeExt (const char* name, OSRTDList* pElemList, 
   OSRTDList* pCompElemList, char* errBuff, int errBuffSize)
{
   if (0 != pElemList && 0 != pCompElemList) {
      ASN1OpenType* pOpenType;
      ASN1OpenType* pCompOpenType;
      OSRTDListNode* pnode = pElemList->head;
      OSRTDListNode* pCompNode = pCompElemList->head;
      /* First check that Both list has equal count */
      if( pElemList->count != pCompElemList->count)
      {
#ifndef _COMPACT
         rtPrintToString(name, errBuff, errBuffSize);
         rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
         rtPrintToString("Expected: No. of extension elements ", errBuff, errBuffSize);
         rtxItoa(pElemList->count, errBuff, errBuffSize);
         rtPrintToString("\n", errBuff, errBuffSize);
         rtPrintToString("Received: No. of extension elements ", errBuff, errBuffSize);
         rtxItoa(pCompElemList->count, errBuff, errBuffSize);
         rtPrintToString("\n", errBuff, errBuffSize);
         rtPrintToString("\n", errBuff, errBuffSize);
#else
         if(errBuff) { *errBuff = 0; }
#endif
         return FALSE;
      }
      /* Check Both has 0 elements */
      if( pElemList->count == 0 )
      {
         return TRUE;
      }
      /* Check all the octets are equal */
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            pCompOpenType = (ASN1OpenType*) pCompNode->data;
            if(rtCmpOpenType (name, pOpenType->numocts, pOpenType->data,
               pCompOpenType->numocts, pCompOpenType->data, errBuff, 
               errBuffSize) == FALSE)
            {
               return FALSE;
            }
         }
         pnode = pnode->next;
         pCompNode = pCompNode->next;
      }
      return TRUE;
   }
   /* Check one of the list is empty */
   if(!(pElemList == 0 && pCompElemList == 0))
   {
#ifndef _COMPACT
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString(
         "No. of extension parameters is not equal, "
         "Missing extension parameters in one of the value\n", errBuff, errBuffSize);
#else
      if(errBuff) { *errBuff = 0; }
#endif
      return FALSE;
   }
   /* Both list are empty pElemList == 0 && pCompElemList == 0 */
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOpenTypeExt (const char* name, 
   OSRTDList* pElemList, OSRTDList* pCompElemList)
{
   if (0 != pElemList && 0 != pCompElemList) {
      ASN1OpenType* pOpenType;
      ASN1OpenType* pCompOpenType;
      OSRTDListNode* pnode = pElemList->head;
      OSRTDListNode* pCompNode = pCompElemList->head;
      /* First check that Both list has equal count */
      if( pElemList->count != pCompElemList->count)
      {
#ifndef _COMPACT
         printf("%s: value is not equal\n", name);
         printf("Expected: No. of extension elements %d\n"
                "Received: No. of extension elements %d\n\n", 
                   pElemList->count, pCompElemList->count);
#endif
         return FALSE;
      }
      /* Check Both has 0 elements */
      if( pElemList->count == 0 )
      {
         return TRUE;
      }
      /* Check all the octets are equal */
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            pCompOpenType = (ASN1OpenType*) pCompNode->data;
            if(rtCmpToStdoutOpenType (name, pOpenType->numocts, 
               pOpenType->data, pCompOpenType->numocts, 
               pCompOpenType->data) == FALSE)
            {
               return FALSE;
            }
         }
         pnode = pnode->next;
         pCompNode = pCompNode->next;
      }
      /* Both has no Elements(i.e. count) OR Both has equal elements */
      return TRUE;
   }
   /* Check one of the list is empty */
   if(!(pElemList == 0 && pCompElemList == 0))
   {
#ifndef _COMPACT
      printf("%s: value is not equal\n", name);
      printf("No. of extension parameters is not equal, "
             "Missing extension parameters in one of the value\n");
#endif
      return FALSE;
   }
   /* Both list are empty pElemList == 0 && pCompElemList == 0 */
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpTag (const char* name, int tag, int compTag, char* errBuff, 
   int errBuffSize)
{
   if(tag != compTag)
   {
#ifndef _COMPACT
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: Tag = ", errBuff, errBuffSize);
      rtxItoa(tag, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("Received: Tag = ", errBuff, errBuffSize);
      rtxItoa(compTag, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
#else
      if(errBuff) { *errBuff = 0; }
#endif
      return FALSE;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpSeqOfElements (const char* name, int noOfElems, 
   int compNoOfElems, char* errBuff, int errBuffSize)
{
   if(noOfElems != compNoOfElems )
   {
#ifndef _COMPACT
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: No of Elements = ", errBuff, errBuffSize);
      rtxItoa(noOfElems, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("Received: No of Elements = ", errBuff, errBuffSize);
      rtxItoa(compNoOfElems, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
#else
      if(errBuff) { *errBuff = 0; }
#endif
      return FALSE;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpOptional (const char* name, unsigned presentBit, 
   unsigned compPresentBit, char* errBuff, int errBuffSize)
{
   if (presentBit  != compPresentBit)
   {
#ifndef _COMPACT
      rtPrintToString(name, errBuff, errBuffSize);
      rtPrintToString(": value is not equal\n", errBuff, errBuffSize);
      rtPrintToString("Expected: present bit ", errBuff, errBuffSize);
      rtxItoa(presentBit, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("Received: present bit ", errBuff, errBuffSize);
      rtxItoa(compPresentBit, errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
      rtPrintToString("\n", errBuff, errBuffSize);
#else
      if(errBuff) { *errBuff = 0; }
#endif
      return FALSE;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutTag (const char* name, int tag, int compTag)
{
   if(tag != compTag)
   {
#ifndef _COMPACT
      printf("%s: value is not equal\n", name);
      printf("Expected: Tag = %d\nReceived: Tag = %d\n\n", tag, compTag);
#endif
      return FALSE;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutSeqOfElements (const char* name, int noOfElems, 
   int compNoOfElems)
{
   if(noOfElems != compNoOfElems )
   {
#ifndef _COMPACT
      printf ("%s : value is not equal\n", name);
      printf (
         "Expected: No of Elements = %d\n"
         "Received: No of Elements = %d\n\n", noOfElems, compNoOfElems);
#endif
      return FALSE;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCmpToStdoutOptional (const char* name, unsigned presentBit, 
   unsigned compPresentBit)
{
   if (presentBit  != compPresentBit)
   {
#ifndef _COMPACT
      printf ("%s: value is not equal\n", name);
      printf ("Expected: present bit %d\nReceived: present bit %d\n\n", 
         presentBit, compPresentBit);
#endif
      return FALSE;
   }
   return TRUE;
}
