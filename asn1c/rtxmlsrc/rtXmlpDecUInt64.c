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

static const OSUINT64 maxUInt64 = OSUI64CONST(0xFFFFFFFFFFFFFFFF);
static const OSUINT64 maxUInt64_10 = OSUI64CONST(0x1999999999999999); 

EXTXMLMETHOD int rtXmlpDecUInt64 (OSCTXT* pctxt, OSUINT64* pvalue) 
{
   size_t i;
   OSBOOL minus = FALSE;
   register OSUINT64 value = 0;
   struct OSXMLReader* pXmlReader;
   OSXMLCtxtInfo* xmlCtxt;
   OSXMLDataCtxt dataCtxt;
   int stat = 0;

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   if (pvalue)
      *pvalue = 0;

   rtXmlRdSetWhiteSpaceMode (pXmlReader, OSXMLWSM_COLLAPSE);

   if ((stat = rtXmlRdFirstData (pXmlReader, &dataCtxt)) > 0) {
      do {
         const OSUTF8CHAR* const inpdata = dataCtxt.mData.value;
         size_t nbytes = dataCtxt.mData.length;

         i = 0;
         if (dataCtxt.mnChunk == 0) {
            /* Skip '+' */
            if (inpdata[i] == '+') {
               i++;
            }
            /* Skip '-' for '-0' */
            else if (inpdata[0] == '-') {
               i++;
               minus = TRUE;
            }
         }
       
         /* Convert Unicode characters to an integer value */

         for ( ; i < nbytes; i++) {
            if (!minus && OS_ISDIGIT (inpdata[i])) {
               OSUINT32 tm = inpdata[i] - '0';
               
               if (value > maxUInt64_10) {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_TOOBIG);
                  break;
               }   
               
               value *= 10;
               
               if (value > maxUInt64 - tm) {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_TOOBIG);
                  break;
               }   
               
               value += tm;
            }   
            else if (minus && inpdata[i] == '0') ; /* -0000... */
            else {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
               stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               break;
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
   else { /* empty content */
      rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
      stat = LOG_RTERRNEW (pctxt, RTERR_INVFORMAT);
   }
   
   if (stat >= 0) {
      stat = 0;
      if (pvalue)
         *pvalue = value;
   }

   return stat;
}


