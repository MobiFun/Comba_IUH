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
#include "rtxmlsrc/rtXmlPull.h"
#include "rtxsrc/rtxBitString.h"

EXTXMLMETHOD int rtXmlpDecBitString 
(OSCTXT* pctxt, OSOCTET* pvalue, OSUINT32* pnbits, OSUINT32 bufsize)
{
   OSXMLDataCtxt dataCtxt;
   OSXMLCtxtInfo* xmlCtxt;
   struct OSXMLReader* pXmlReader;
   OSUINT32 bitIndex = 0;
   OSUINT32 numbits = bufsize * 8;
   int stat = 0;

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   if (pnbits)
      *pnbits = 0;

   rtXmlRdSetWhiteSpaceMode (pXmlReader, OSXMLWSM_COLLAPSE);

   if ((stat = rtXmlRdFirstData (pXmlReader, &dataCtxt)) > 0) {
      do {
         const OSUTF8CHAR* const inpdata = dataCtxt.mData.value;
         size_t nbytes = dataCtxt.mData.length;
         size_t i;

         if (bitIndex + (OSUINT32)nbytes > numbits) {
            rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
            stat = LOG_RTERRNEW (pctxt, RTERR_STROVFLW);
         }
         
         for (i = 0; i < nbytes && stat >= 0; i++) {
            OSUTF8CHAR c = inpdata[i];
            
            if (pvalue) {
               if (bitIndex % 8 == 0)
                  pvalue[bitIndex / 8] = 0;
                  
               if (c == '1')
                  rtxSetBit (pvalue, numbits, bitIndex);
               else if (c != '0') {  
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }   
            }
            else if (c != '0' && c != '1') {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
               stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
            }
               
            bitIndex++;   
         }

         if (stat >= 0) {
            stat = rtXmlRdNextData (pXmlReader, &dataCtxt);
            if (stat < 0)
               LOG_RTERR (pctxt, stat);
         }   
      } while (stat > 0);
   }
   else if (stat < 0)
      LOG_RTERR (pctxt, stat);

   if (stat >= 0) {
      stat = 0;
      if (pnbits)
         *pnbits = bitIndex;
   }
   
   return stat;
}


