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

EXTXMLMETHOD int rtXmlpDecHexStr 
(OSCTXT* pctxt, OSOCTET* pvalue, OSUINT32* pnocts, OSINT32 bufsize)
{
   OSXMLDataCtxt dataCtxt;
   OSXMLCtxtInfo* xmlCtxt;
   struct OSXMLReader* pXmlReader;
   size_t oldsize = 0;
   int stat = 0;

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   if (pnocts)
      *pnocts = 0;

   rtXmlRdSetWhiteSpaceMode (pXmlReader, OSXMLWSM_COLLAPSE);

   if ((stat = rtXmlRdFirstData (pXmlReader, &dataCtxt)) > 0) {
      do {
         const OSUTF8CHAR* const inpdata = dataCtxt.mData.value;
         size_t nbytes = dataCtxt.mData.length;
         size_t newsize = oldsize + nbytes;
         size_t i;

         if ((newsize + 1) / 2 > (size_t)bufsize) {
            rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
            stat = LOG_RTERRNEW (pctxt, RTERR_STROVFLW);
         }
         else {
            for (i = 0; i < nbytes; i++, oldsize++) {
               OSUTF8CHAR c = inpdata[i];
               if (c >= '0' && c <= '9')
                  c -= '0';
               else if (c >= 'a' && c <= 'f')
                  c -= 'a' - 10;
               else if (c >= 'A' && c <= 'F')
                  c -= 'A' - 10;
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVHEXS);
                  break;
               }
                  
               if (pvalue) {
                  if ((oldsize & 1) == 0)
                     pvalue[oldsize >> 1] = (OSOCTET) (c << 4);  
                  else 
                     pvalue[oldsize >> 1] |= c;  
               }
            }
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

      if (pvalue) {
         if ((oldsize & 1) != 0) {/* shift hex str (211 -> 0211) */
            OSUTF8CHAR* p = pvalue + oldsize / 2; 
            
            for (;p != pvalue; p--) {
               *p = (OSOCTET) ((p[-1] << 4) | (*p >> 4));
            }

            *p >>= 4;
         }   
      }   
      
      if (pnocts)
         *pnocts = (OSUINT32) ((oldsize + 1) / 2);
   }
   
   return stat;
}


