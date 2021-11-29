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

/* Run-time print utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxCtype.h"

#ifndef BITSTR_BYTES_IN_LINE
#define BITSTR_BYTES_IN_LINE 16
#endif

static void rtBitStringDump (OSUINT32 numbits, const OSOCTET* data)
{
   OSUINT32 i, numocts = numbits / 8;
   char buff[9];
   
   if (numocts > 8)
      printf ("\n");

   for (i = 0; i < numocts; i++) {
      if ((i != 0) && (i % BITSTR_BYTES_IN_LINE == 0)) {
         printf ("\n");
      }
      
      if (i % BITSTR_BYTES_IN_LINE == 0)      
         printf ("0x%02X", data[i]);
      else
         printf (" 0x%02X", data[i]);
   }

   if (i * 8 != numbits) {
      OSOCTET tm = data[i];
      OSUINT32 nmBits = numbits % 8;
      OSUINT32 j; 
               
      for (j = 0; j < nmBits; j++, tm<<=1)
         buff[j] = ((tm >> 7) & 1) + '0';
      for (; j < 8; j++)
         buff[j] = 'x';

      if ((i % BITSTR_BYTES_IN_LINE) == (BITSTR_BYTES_IN_LINE - 1))
         printf ("\n%.8s", buff);
      else if (i > 0)
         printf (" %.8s", buff);
      else 
         printf ("%.8s", buff);
   }
}
 
EXTRTMETHOD void rtPrintBitStr (const char* name, OSUINT32 numbits, 
                    const OSOCTET* data, const char* conn)
{
   printf ("%s%snumbits = %u\n", name, conn, numbits);
   printf ("%s%sdata = ", name, conn);
   rtBitStringDump (numbits, data);
   printf ("\n");
}

EXTRTMETHOD void rtPrintBitStrBraceText 
(const char* name, OSUINT32 numbits, const OSOCTET* data)
{
   printf ("%s = { %u, ", name, numbits);
   rtBitStringDump (numbits, data);
   printf (" }\n");
}

EXTRTMETHOD void rtPrintOctStr (const char* name, OSUINT32 numocts, 
                    const OSOCTET* data, const char* conn)
{
   printf ("%s%snumocts = %u\n", name, conn, numocts);
   printf ("%s%sdata = \n", name, conn);
   rtxHexDump (data, numocts);
}

EXTRTMETHOD void rtPrint16BitCharStr 
(const char* name, Asn116BitCharString* bstring)
{
   rtxPrintUnicodeCharStr (name, bstring->data, bstring->nchars);
}

EXTRTMETHOD void rtPrint32BitCharStr 
(const char* name, Asn132BitCharString* bstring, const char* conn)
{
   printf ("%s%snchars = %u\n", name, conn, bstring->nchars);
   printf ("%s%sdata = \n", name, conn);
   rtxHexDumpEx ((OSOCTET*)bstring->data, 
                 bstring->nchars * sizeof (OSUINT32), 4);
}

EXTRTMETHOD void rtPrintOID (const char* name, ASN1OBJID* pOID)
{
   printf ("%s = ", name);
   rtPrintOIDValue (pOID);
}

EXTRTMETHOD void rtPrintOIDValue (ASN1OBJID* pOID)
{
   OSUINT32 ui;
   printf ("{ ");
   for (ui = 0; ui < pOID->numids; ui++) {
      printf ("%d ", pOID->subid[ui]);
   }
   printf ("}\n");
}

/* OID with subid of 64 bit */
EXTRTMETHOD void rtPrintOID64 (const char* name, ASN1OID64* pOID)
{
   printf ("%s = ", name);
   rtPrintOID64Value (pOID);
}

EXTRTMETHOD void rtPrintOID64Value (ASN1OID64* pOID)
{
   OSINT64 ui;
   printf ("{ ");
   for (ui = 0; ui < pOID->numids; ui++) {
      printf (OSINT64FMT" " , pOID->subid[(unsigned int)ui]);
   }
   printf ("}\n");
}

EXTRTMETHOD void rtPrintOpenType (const char* name, OSUINT32 numocts, 
                      const OSOCTET* data, const char*  conn)
{
   printf ("%s%snumocts = %u\n", name, conn, numocts);
   printf ("%s%sdata = \n", name, conn);
   rtxHexDump (data, numocts);
}

EXTRTMETHOD void rtPrintOpenTypeExt (const char* name, OSRTDList* pElemList)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            rtPrintOpenType (name, pOpenType->numocts, pOpenType->data, ".");
         }
         pnode = pnode->next;
      }
   }
}

EXTRTMETHOD void rtPrintUnivCharStr (const char* name, Asn132BitCharString* bstring)
{
   OSUINT32 i;
   printf ("%s = '", name);
   for (i = 0; i < bstring->nchars; i++) {
      if (OS_ISPRINT (bstring->data[i]))
         putc (bstring->data[i], stdout);
      else
         printf ("0x%08x", bstring->data[i]);
   }
   printf ("'\n");
}

#ifndef __SYMBIAN32__
EXTRTMETHOD void rtPrintOpenTypeExtBraceText (const char* name, OSRTDList* pElemList)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            rtxPrintIndent ();
            rtxPrintHexStr (name, pOpenType->numocts, pOpenType->data);
         }
         pnode = pnode->next;
      }
   }
}
#endif

