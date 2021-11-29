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
#include "rtsrc/rtPrintToStream.h"
#include "rtxsrc/rtxCtype.h"

#ifndef BITSTR_BYTES_IN_LINE
#define BITSTR_BYTES_IN_LINE 16
#endif

static int rtBitStringDumpToStream (OSCTXT *pctxt, OSUINT32 numbits, 
                                    const OSOCTET* data)
{
   OSUINT32 i, numocts = numbits / 8;
   char buff[9];
   int ret=0;
   
   if (numocts > 8) {
      ret = rtxPrintToStream (pctxt, "\n");
      if (ret != 0) return ret;
   }
   
   for (i = 0; i < numocts; i++) {
      if ((i != 0) && (i % BITSTR_BYTES_IN_LINE == 0)) {
         ret = rtxPrintToStream (pctxt, "\n");
         if (ret != 0) return ret;
      }
      
      if (i % BITSTR_BYTES_IN_LINE == 0)     
         ret = rtxPrintToStream (pctxt, "0x%02X", data[i]);
      else
         ret = rtxPrintToStream (pctxt, " 0x%02X", data[i]);
      
      if (ret != 0) return ret;
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
         ret = rtxPrintToStream (pctxt, "\n%.8s", buff);
      else if (i > 0)
         ret = rtxPrintToStream (pctxt, " %.8s", buff);
      else 
         ret = rtxPrintToStream (pctxt, "%.8s", buff);

      if (ret != 0) return ret;
   }
   
   return ret;
}
 
EXTRTMETHOD int rtPrintToStreamBitStr (OSCTXT *pctxt, const char* name, 
                           OSUINT32 numbits, const OSOCTET* data, 
                           const char* conn)
{
   int ret=0;
   ret = rtxPrintToStream(pctxt, "%s%snumbits = %u\n", name, conn, numbits);
   if(ret != 0) return ret;
   ret = rtxPrintToStream(pctxt, "%s%sdata = ", name, conn);   
   if(ret != 0) return ret;
   ret = rtBitStringDumpToStream (pctxt, numbits, data);
   if (ret != 0) return ret;
   ret = rtxPrintToStream (pctxt, "\n");   
   return ret;
}

EXTRTMETHOD int rtPrintToStreamBitStrBraceText 
(OSCTXT *pctxt, const char* name, OSUINT32 numbits, const OSOCTET* data)
{
   int ret = 0;

   ret = rtxPrintToStream (pctxt, "%s = { %u, ", name, numbits);
   if(ret != 0) return ret;

   ret = rtBitStringDumpToStream (pctxt, numbits, data);
   if(ret != 0) return ret;

   ret = rtxPrintToStream (pctxt, " }\n");   

   return ret;
}

EXTRTMETHOD int rtPrintToStreamOctStr (OSCTXT *pctxt, const char* name, 
                           OSUINT32 numocts, const OSOCTET* data, 
                           const char* conn)
{
   int ret = 0;
   ret = rtxPrintToStream(pctxt, "%s%snumocts = %u\n", name, conn, numocts);
   if(ret != 0) return ret;
   ret = rtxPrintToStream(pctxt, "%s%sdata = \n", name, conn);   
   if(ret != 0) return ret;
   rtxHexDumpToStream (pctxt, data, numocts);
   return ret;
}


EXTRTMETHOD int rtPrintToStream16BitCharStr (OSCTXT *pctxt, const char* name, 
                                 Asn116BitCharString* bstring, 
                                 const char* conn)
{
   int ret = 0;
    
   ret = rtxPrintToStream(pctxt, "%s%snchars = %u\n", name, conn, 
                         bstring->nchars);
   if(ret != 0) return ret;
   ret = rtxPrintToStream(pctxt, "%s%sdata = \n", name, conn);
   if(ret != 0) return ret;
   rtxHexDumpToStreamEx (pctxt, (OSOCTET*)bstring->data, 
                        bstring->nchars * 2, 2);
   return ret;
}


EXTRTMETHOD int rtPrintToStream32BitCharStr (OSCTXT *pctxt, const char* name, 
                                 Asn132BitCharString* bstring, 
                                 const char* conn)
{
   int ret = 0;
    
   ret = rtxPrintToStream(pctxt,"%s%snchars = %u\n", name, conn, 
                         bstring->nchars);
   if(ret != 0) return ret;
   ret = rtxPrintToStream(pctxt, "%s%sdata = \n", name, conn);
   if(ret != 0) return ret;
   rtxHexDumpToStreamEx (pctxt, (OSOCTET*)bstring->data, 
                        bstring->nchars * sizeof (OS32BITCHAR), 4);
   return ret;
}


EXTRTMETHOD int rtPrintToStreamOIDValue (OSCTXT *pctxt, ASN1OBJID* pOID)
{
   OSUINT32 ui;

   rtxPrintToStream(pctxt, "{ ");
   for (ui = 0; ui < pOID->numids; ui++) {
      rtxPrintToStream(pctxt, "%d ", pOID->subid[ui]);
   }
   rtxPrintToStream(pctxt, "}\n");
   return 0;
}

EXTRTMETHOD int rtPrintToStreamOID (OSCTXT *pctxt, const char* name, 
                        ASN1OBJID* pOID)
{
   int ret = 0;
   ret = rtxPrintToStream(pctxt,"%s = ", name);
   if(ret != 0) return ret;
   ret = rtPrintToStreamOIDValue (pctxt, pOID);
   return ret;
}

EXTRTMETHOD int rtPrintToStreamOID64Value (OSCTXT *pctxt, ASN1OID64* pOID)
{
   OSINT64 ui;
   rtxPrintToStream (pctxt, "{ ");
   for (ui = 0; ui < pOID->numids; ui++) {
      rtxPrintToStream (pctxt, OSINT64FMT" " , 
                       pOID->subid[(unsigned int)ui]);
   }
   rtxPrintToStream (pctxt, "}\n");
   return 0;
}

/* OID with subid of 64 bit */
EXTRTMETHOD int rtPrintToStreamOID64 (OSCTXT *pctxt, const char* name, 
                          ASN1OID64* pOID)
{
   int ret = 0;
   ret = rtxPrintToStream(pctxt, "%s = ", name);
   if(ret != 0) return ret;
   ret = rtPrintToStreamOID64Value (pctxt, pOID);
   return ret;
}

EXTRTMETHOD int rtPrintToStreamOpenType (OSCTXT *pctxt,const char* name, 
                             OSUINT32 numocts, const OSOCTET* data,
                             const char*  conn)
{
   int ret = 0;
   ret =  rtxPrintToStream(pctxt, "%s%snumocts = %u\n", name, conn, numocts);
   if(ret != 0) return ret;
   ret = rtxPrintToStream(pctxt, "%s%sdata = \n", name, conn);
   if(ret != 0) return ret;
   rtxHexDumpToStream (pctxt, data, numocts);
   return ret;
}

EXTRTMETHOD int rtPrintToStreamOpenTypeExt (OSCTXT *pctxt, const char* name,
                                OSRTDList* pElemList)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            rtPrintToStreamOpenType (pctxt, name, pOpenType->numocts, 
                                     pOpenType->data, ".");
         }
         pnode = pnode->next;
      }
   }
   return 0;
}

EXTRTMETHOD int rtPrintToStreamUnicodeCharStr 
   (OSCTXT *pctxt, const char* name, Asn116BitCharString* bstring)
{
   OSUINT32 i;
   if(rtxPrintToStream (pctxt, "%s = '", name) < 0)
      return -1;
   
   for (i = 0; i < bstring->nchars; i++) {
      if (OS_ISPRINT (bstring->data[i])){
         if(rtxPrintToStream (pctxt, "%c", bstring->data[i]) < 0)
            return -1;
      }
      else{
         if(rtxPrintToStream (pctxt, "0x%04x", bstring->data[i]) < 0)
            return -1;
       }
   }
   if(rtxPrintToStream (pctxt, "'\n") < 0)
      return -1;
   
   return 0;
}

EXTRTMETHOD int rtPrintToStreamUnivCharStr 
   (OSCTXT *pctxt, const char* name, Asn132BitCharString* bstring)
{
   OSUINT32 i;

   if(rtxPrintToStream (pctxt, "%s = '", name) < 0)
      return -1;
   
   for (i = 0; i < bstring->nchars; i++) {
      if (OS_ISPRINT (bstring->data[i])){
         if(rtxPrintToStream (pctxt, "%c", bstring->data[i]) < 0)
            return -1;
      }
      else{
         if(rtxPrintToStream (pctxt, "0x%08x", bstring->data[i]) < 0)
            return -1;
      }
   }
   if(rtxPrintToStream (pctxt, "'\n") < 0)
      return -1;

   return 0;
}

EXTRTMETHOD int rtPrintToStreamOpenTypeExtBraceText 
   (OSCTXT *pctxt, const char* name, OSRTDList* pElemList)
{
   ASN1OpenType* pOpenType;
   if (0 != pElemList) {
      OSRTDListNode* pnode = pElemList->head;
      while (0 != pnode) {
         if (0 != pnode->data) {
            pOpenType = (ASN1OpenType*) pnode->data;
            /* Symbian builds for some reason don't include 
             * rtxPrintToStreamIndent, so I've left this out. */
#ifndef __SYMBIAN32__
            rtPrintToStreamIndent (pctxt);
#endif
            rtPrintToStreamHexStr 
               (pctxt, name, pOpenType->numocts, pOpenType->data);
         }
         pnode = pnode->next;
      }
   }
   return 0;
}


   

